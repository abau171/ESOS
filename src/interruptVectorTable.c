#include <interruptHandlers.h>

void __attribute__((interrupt("UNDEF"))) undefinedInstructionHandlerWrapper() {
	undefinedInstructionHandler();
}

void __attribute__((interrupt("SWI"))) softwareInterruptHandlerWrapper() {
	softwareInterruptHandler();
}

void __attribute__((interrupt("ABORT"))) prefetchAbortHandlerWrapper() {
	prefetchAbortHandler();
}

void __attribute__((interrupt("ABORT"))) dataAbortHandlerWrapper() {
	dataAbortHandler();
}

void __attribute__((interrupt("IRQ"))) interruptHandlerWrapper() {
	interruptHandler();
}

void __attribute__((interrupt("FIQ"))) fastInterruptHandlerWrapper() {
	fastInterruptHandler();
}