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
	// most handlers are wrapped to save the registers from
	// the interrupted code, then restore them when the handler
	// finishes.
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

resetHandler:
	// build the vector table
	ldr r0, _start // first load the address of the start of the table
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

undefinedInstructionHandlerWrapper:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	bl undefinedInstructionHandler
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
softwareInterruptHandlerWrapper:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	bl softwareInterruptHandler
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
prefetchAbortHandlerWrapper:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	bl prefetchAbortHandler
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
dataAbortHandlerWrapper:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	bl dataAbortHandler
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
interruptHandlerWrapper:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	bl interruptHandler
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
fastInterruptHandlerWrapper:
	push {r0, r1, r2, r3, r4, r5, r6, r7}
	bl fastInterruptHandler
	pop {r0, r1, r2, r3, r4, r5, r6, r7}

undefinedInstructionHandler:
softwareInterruptHandler:
prefetchAbortHandler:
dataAbortHandler:
interruptHandler:
fastInterruptHandler:
