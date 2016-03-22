.globl _start
_start:
	ldr sp, =0x07ffffff
	bl main
	b _end

_end:
	wfi
	b _end
