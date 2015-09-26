.section .text.boot
.globl _start
_start:
	ldr pc, resetHandlerAddress
	ldr pc, undefinedInstructionHandlerAddress
	ldr pc, softwareInterruptHandlerAddress
	ldr pc, prefetchAbortHandlerAddress
	ldr pc, dataAbortHandlerAddress
	ldr pc, unusedHandlerAddress
	ldr pc, interruptHandlerAddress
	ldr pc, fastInterruptHandlerAddress

	resetHandlerAddress:
		.word resetHandler
	undefinedInstructionHandlerAddress:
		.word 0x0
	softwareInterruptHandlerAddress:
		.word softwareInterruptHandler
	prefetchAbortHandlerAddress:
		.word 0x0
	dataAbortHandlerAddress:
		.word 0x0
	unusedHandlerAddress:
		.word 0x0
	interruptHandlerAddress:
		.word 0x0
	fastInterruptHandlerAddress:
		.word 0x0

.section .text
resetHandler:
	mov r0, #0x8000
	mov r1, #0x0000
	ldmia r0!, {r2, r3, r4, r5, r6, r7 ,r8, r9}
	stmia r1!, {r2, r3, r4, r5, r6, r7 ,r8, r9}
	ldmia r0!, {r2, r3, r4, r5, r6, r7 ,r8, r9}
	stmia r1!, {r2, r3, r4, r5, r6, r7 ,r8, r9}
	mov sp, #0x8000
	bl kernel_main
	bl kernel_hangLoop
	hang:
		b hang

.globl stack1
.fill 0x8000, 0x0, 4
stack1: // label comes at end of allocated stack memory

.globl stack2
.fill 0x8000, 0x0, 4
stack2: // label comes at end of allocated stack memory

.globl yield
yield:
	swi #0x0
	mov pc, lr

softwareInterruptHandler:
	mov sp, #0x8000
	// need to store all current registers to the current task
	push {r0-r3}
	bl getCurrentTask
	str r4, [r0, #4]
	str r5, [r0, #5]
	str r6, [r0, #6]
	str r7, [r0, #7]
	str r8, [r0, #8]
	str r9, [r0, #9]
	str r10, [r0, #10]
	str r11, [r0, #11]
	str r12, [r0, #12]
	mov r4, r0
	pop {r0-r3}
	str r0, [r4, #0]
	str r1, [r4, #1]
	str r2, [r4, #2]
	str r3, [r4, #3]
	mov r0, r4
	// at this point, r0-r12 are saved to the task
	mrs r1, cpsr
	bic r1, #0x1f
	orr r1, #0x1f
	msr cpsr, r1
	str r13, [r0, #13] // sp
	str r14, [r0, #14] // lr
	mrs r1, cpsr
	bic r1, #0x1f
	orr r1, #0x13
	msr cpsr, r1
	// at this point, r0-r14 are saved to the task
	str lr, [r0, #15] // pc saved from svc's lr
	mrs r1, spsr
	str r1, [r0, #16] // cpsr saved from svc's spsr
	// at this point, all registers are saved to the task
	bl runNextTask

.globl runTask
runTask:
	bl getCurrentTask
	ldr r1, [r0, #64]
	msr spsr, r1 // store task's cpsr in svc's spsr
	ldr lr, [r0, #60] // store task's pc in svc's lr
	// at this point, pc (from svc's lr) and cpsr (from svc's spsr) are ready
	mrs r1, cpsr
	bic r1, #0x1f
	orr r1, #0x1f
	msr cpsr, r1
	ldr r13, [r0, #56] // sp
	ldr r14, [r0, #52] // lr
	mrs r1, cpsr
	bic r1, #0x1f
	orr r1, #0x13
	msr cpsr, r1
	// at this point, r13-cpsr are ready
	ldr r1, [r0, #4]
	ldr r2, [r0, #8]
	ldr r3, [r0, #12]
	ldr r4, [r0, #16]
	ldr r5, [r0, #20]
	ldr r6, [r0, #24]
	ldr r7, [r0, #28]
	ldr r8, [r0, #32]
	ldr r9, [r0, #36]
	ldr r10, [r0, #40]
	ldr r11, [r0, #44]
	ldr r12, [r0, #48]
	ldr r0, [r0, #0] // important to load this last!
	// at this point, all registers are ready
	// KAAAA
	// MEEEEEE
	// HAAAAAAAAAAA
	// MEEEEEEEEEEEEEEEE
	movs pc, lr // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
