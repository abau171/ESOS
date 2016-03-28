.section .text

.globl software_interrupt_handler
software_interrupt_handler:
	/* TODO: make sure all interrupts are disabled in svc mode */
	/* store user pc and cpsr to task */
	srsia #0x13
	/* store remaining user registers to task */
	stmdb sp, {r0-lr}^
	/* set the stack address to the last available address */
	ldr sp, =0x07ffffff
	/* move the syscall id to first argument */
	mov r0, r7

	/* handle the system call */
	bl handle_syscall

	/* activate task (see activate_task) */
	ldr r0, =cur_task
	ldr sp, [r0]
	add sp, sp, #60
	ldmdb sp, {r0-lr}^
	rfeia sp

.globl interrupt_handler
interrupt_handler:
	/* save user state (see software_interrupt_handler) */
	srsia #0x13
	/* switch to svc mode after saving user pc and cpsr */
	msr CPSR_c, #0xd3
	stmdb sp, {r0-lr}^
	ldr sp, =0x07ffffff

	/* handle the interrupt */
	bl handle_interrupt

	/* activate task (see activate_task) */
	ldr r0, =cur_task
	ldr sp, [r0]
	add sp, sp, #60
	ldmdb sp, {r0-lr}^
	rfeia sp

.globl activate_task
activate_task:
	/* load the current task pointer */
	ldr r0, =cur_task
	ldr sp, [r0]
	add sp, sp, #60
	/* load user registers */
	ldmdb sp, {r0-lr}^
	/* load user pc and cpsr */
	rfeia sp

