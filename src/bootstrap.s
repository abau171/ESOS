.section .text.boot
.globl _start
_start:
	// defines the vector table
	// each vector branches to the address of its handler
	ldr pc, resetHandlerAddress
	ldr pc, undefinedInstructionHandlerAddress
	ldr pc, softwareInterruptHandlerAddress
	ldr pc, prefetchAbortHandlerAddress
	ldr pc, dataAbortHandlerAddress
	ldr pc, unusedHandlerAddress
	ldr pc, interruptHandlerAddress
	ldr pc, fastInterruptHandlerAddress
	// the handler addresses are stored as constants.
	// most handlers are wrapped by functions using gcc's interrupt
	// attribute.
	// this is probably inefficient, but simplifies the C code.
	resetHandlerAddress:
		// the reset handler isn't wrapped because by definition
		// a reset does not save anything.
		.word resetHandler
	undefinedInstructionHandlerAddress:
		.word undefinedInstructionHandlerWrapper
	softwareInterruptHandlerAddress:
		.word softwareInterruptHandlerWrapper
	prefetchAbortHandlerAddress:
		.word prefetchAbortHandlerWrapper
	dataAbortHandlerAddress:
		.word dataAbortHandlerWrapper
	unusedHandlerAddress:
		.word resetHandler // should be unused
	interruptHandlerAddress:
		.word interruptHandlerWrapper
	fastInterruptHandlerAddress:
		.word fastInterruptHandlerWrapper

.section .text
resetHandler:
	// build the vector table
	mov r0, #0x00008000 // first load the address of the start of the table
	mov r1, #0x00000000 // then load the destination
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9} // move the branches into place
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9} // move the handler addresses into place
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	// initialize the stack
	mov sp, #0x00010000
	// run the main function
	bl kernel_main
	// if main function returns, a custom hang loop can be given
	bl kernel_hangLoop
	// otherwise, just hang while doing nothing at all
	hang:
		b hang

.globl enableInterrupts
enableInterrupts:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
	mov pc, lr

.globl disableInterrupts
disableInterrupts:
	mrs r0, cpsr
	orr r0, r0, #0x80
	msr cpsr_c, r0
	mov pc, lr

// This implementation assumes the interrupt is a timer interrupt signaling the end of a time slice.
// The current task's state is saved (on its own stack for now), and its pc and sp are given to the
// scheduler code (calls C function).
irqHandlerASM: // TODO make sure important registers aren't used for mode changing!

	/* STEP 1: PUSH ALL USER TASK REGISTERS ONTO USER'S STACK */

	// switch to SYS mode (uses sp_irq as general purpose register since irq mode has no stack)
	mrs r13, cpsr
	bic r13, #0x1f
	orr r13, #0x1f
	msr cpsr, r13

	// save USR registers to current task
	push {r0-r12, lr} // save all except pc and sp

	// switch to IRQ mode (r0 is safe on stack)
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x12
	msr cpsr, r0

	// prepare return SPSR for storage on USR stack
	mrs r1, spsr

	// switch to SYS mode
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x1f
	msr cpsr, r0

	// push return SPSR onto USR stack
	push {r1}

	/* STEP 2: STORE TASK STATE AND LOAD NEXT TASK TO EXECUTE */

	// prepare final stack pointer to be stored in task state
	mov r1, sp

	// switch to IRQ mode (r0 is safe on stack)
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x12
	msr cpsr, r0

	// prepare return address (the task's current pc) to be stored in task state
	mov r0, lr

	// switch to SVC mode (stack should be empty)
	mrs r2, cpsr
	bic r2, #0x1f
	orr r2, #0x13
	msr cpsr, r2

	// handle interrupt in C
	// long long timeSliceExpired(unsigned int pc, unsigned int sp);
	// The function may do what it wishes with the pc and sp (ie store them and load the
	// pc and sp of the next task somehow).  It should probably set the next timer interrupt too.
	// The return long long is a fancy way to get C to return two values to r0 and r1.
	// That way, it can return the pc and sp of the task to run next.
	bl timeSliceExpired

	/* STEP 3: RELOAD THE STATE OF THE NEW TASK AND RESUME ITS EXECUTION */
	// essentially steps 1 & 2 in reverse

	// switch to IRQ mode
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x12
	msr cpsr, r0

	// restore return address
	mov lr, r0

	// switch to SYS mode
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x1f
	msr cpsr, r0

	// reload stack pointer for user task
	mov sp, r1

	// get user task's CPSR
	pop {r1}

	// switch to IRQ mode
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x12
	msr cpsr, r0

	// save user task's CPSR in SPSR_irq in preparation for resume
	msr spsr, r1

	// switch to SYS mode (uses sp_irq as general purpose register since irq mode has no stack)
	mrs r13, cpsr
	bic r13, #0x1f
	orr r13, #0x1f
	msr cpsr, r13

	// reload all stored registers
	pop {r0-r12, lr} // restore all except pc and sp (sp is already restored)

	// PROBLEM: WE REALLY NEED R0!!!
	// switch to IRQ mode
	mrs r0, cpsr
	bic r0, #0x1f
	orr r0, #0x12
	msr cpsr, r0

	// finally, call the magic return instruction to resume the user task!
	sub pc, lr, #4
