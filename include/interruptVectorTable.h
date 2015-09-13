#ifndef INTERRUPT_VECTOR_TABLE_H
#define INTERRUPT_VECTOR_TABLE_H

void undefinedInstructionHandler();

void softwareInterruptHandler();

void prefetchAbortHandler();

void dataAbortHandler();

void interruptHandler();

void fastInterruptHandler();

#endif
