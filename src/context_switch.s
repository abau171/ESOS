.globl software_interrupt_handler
software_interrupt_handler:
	# save user pc
	push {lr}
	# load user task pointer
	ldr lr, [sp, #4]
	# store general user registers in task
	stmia lr, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	# move task pointer to r0
	mov r0, lr
	# switch to system mode
	msr CPSR_c, #0xdf
	# store user sp and lr
	str sp, [r0, #52]
	str lr, [r0, #56]
	# return to svc mode
	msr CPSR_c, #0xd3
	# reload user pc
	pop {r1}
	#save user pc
	str r1, [r0, #60]
	# load user CPSR
	mrs r1, SPSR
	# save user CPSR
	str r1, [r0, #64]
	# load svc registers
	pop {r0, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	# return from activate call
	bx lr

.globl activate
activate:
	# save svc registers
	push {r0, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
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

