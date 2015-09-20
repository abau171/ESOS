#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

void undefinedInstructionHandler();

void softwareInterruptHandler();

void prefetchAbortHandler();

void dataAbortHandler();

void interruptHandler();

void fastInterruptHandler();

#endif
