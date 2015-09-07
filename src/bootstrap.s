.globl _start
_start:
	mov sp, #0x00010000
	bl kernel_main
hang:
	b hang
