.section .text.boot
.globl _start
_start:
	mov sp, #0x00010000
	bl kernel_main
	bl kernel_hangLoop
hang:
	b hang
