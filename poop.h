#ifndef __LANG_H__
#define __LANG_H__

// Zeros the accumulator.
void zeroAccumulator(continuation & cont);

// Accept a character from stdin
void acceptInput(continuation & cont);

// Sets a register to the value of the accumulator.
void setRegister(continuation & cont);

// Sets the accumulator to the value of the register.
void readName(continuation & cont);

// Sets the accumulator to the value of the global register.
void readGlobalName(continuation & cont);

// Trashes the current continuation in favor of the passed continuation.
void takeContinuation(continuation & cont);

// Stuffs the current continuation into a named global.
void stuffContinuation(continuation & cont);

// Evaluates the continuation passed.
void evaluate(continuation & cont);

// Adds a name to accumulator.
void add(continuation & cont);

#endif
