.globl software_interrupt_handler
software_interrupt_handler:
	srsia #0x13
	stmdb sp, {r0-lr}^
	ldr sp, =0x07ffffff

	bl handle_syscall

	ldr r0, =cur_task
	ldr sp, [r0]
	add sp, sp, #60
	ldmdb sp, {r0-lr}^
	rfeia sp

.globl activate_task
activate_task:
	ldr r0, =cur_task
	ldr sp, [r0]
	add sp, sp, #60
	ldmdb sp, {r0-lr}^
	rfeia sp

.globl svc
svc:
	svc 0
	mov pc, lr

