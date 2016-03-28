.section .text

.globl yield
yield:
	push {r7}
	mov r7, #0
	svc 0
	pop {r7}
	mov pc, lr

.globl launch
launch:
	push {r7}
	mov r7, #1
	svc 0
	pop {r7}
	mov pc, lr

