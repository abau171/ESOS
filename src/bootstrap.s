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

.globl yield
yield:
	swi #0x0
	mov pc, lr

softwareInterruptHandler:
	mov sp, #0x8000
	bl runNextTask
	bl kernel_hangLoop
	b hang
