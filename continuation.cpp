#include "continuation.h"

continuation::continuation() : program(), pc(program.begin()), stack(), registers(), accumulator(0) {}

continuation::continuation(const continuation & cont) : 
  program(cont.program), pc(cont.pc), stack(cont.stack), registers(cont.registers),
  accumulator(cont.accumulator) {}
