MEMORY {
	ram : ORIGIN = 0x10000, LENGTH = 0x40000
}

SECTIONS {
	.text.boot : { *(.text.boot*) } > ram
	.text : { *(.text*) } > ram
	.bss : { *(.bss*) } > ram
}
