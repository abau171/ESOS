.globl software_interrupt_handler
software_interrupt_handler:
	pop {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	bx lr

.globl activate
activate:
	# save svc registers
	push {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	# load CPSR, save in SPSR
	ldr r1, [r0, #64]
	msr SPSR, r1
	#switch to system mode
	msr CPSR_c, #0xdf
	# load user sp and lr
	ldr sp, [r0, #52]
	ldr lr, [r0, #56]
	# return to svc mode
	msr CPSR_c, #0xd3
	# load user pc to svc lr
	ldr lr, [r0, #60]
	# load general user registers
	ldmia r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	# make final context-switch to user mode
	movs pc, lr

.globl svc
svc:
	svc 0
	mov pc, lr

