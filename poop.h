#ifndef __LANG_H__
#define __LANG_H__

// Zeros the accumulator.
void zeroAccumulator(continuation & cont);

// Sets a register to the value of the accumulator.
void setRegister(continuation & cont);

// Sets the accumulator to the value of the register.
void readName(continuation & cont);

// Evaluates the continuation passed.
void evaluate(continuation & cont);

#endif
