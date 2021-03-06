.section .text.boot
.globl _start
_start:
	ldr pc, reset_handler_address
	ldr pc, undefined_instruction_handler_address
	ldr pc, software_interrupt_handler_address
	ldr pc, prefetch_abort_handler_address
	ldr pc, data_abort_handler_address
	ldr pc, unused_handler_address
	ldr pc, interrupt_handler_address
	ldr pc, fast_interrupt_handler_address

reset_handler_address:                 .word reset_handler
undefined_instruction_handler_address: .word 0x0
software_interrupt_handler_address:    .word software_interrupt_handler
prefetch_abort_handler_address:        .word 0x0
data_abort_handler_address:            .word 0x0
unused_handler_address:                .word 0x0
interrupt_handler_address:             .word interrupt_handler
fast_interrupt_handler_address:        .word 0x0

.section .text
reset_handler:
	/* copy the interrupt vector table from the load point to address 0 */
	mov r0, #0x10000
	mov r1, #0x0
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	/* set the stack address to the last available address */
	ldr sp, =0x07ffffff
	/* run the kernel initializer */
	bl kernel_init
	/* activate the first task */
	b activate_task

