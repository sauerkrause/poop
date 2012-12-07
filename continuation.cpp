#include "continuation.h"
#include <algorithm>
#include <ostream>

continuation::continuation() : program(), pc(0), stack(), registers(), accumulator(0) {}

continuation::continuation(const continuation & cont) : 
  program(cont.program), pc(cont.pc), stack(cont.stack), registers(cont.registers),
  accumulator(cont.accumulator) {}

continuation& continuation::operator=(continuation other) {
  swap(other);
  return *this;
}

void continuation::swap(continuation & other) {
  std::swap(other.program,program);
  std::swap(other.pc, pc);
  std::swap(other.stack, stack);
  std::swap(other.registers, registers);
  std::swap(other.accumulator, accumulator);
}

std::ostream& operator<<(std::ostream& out, continuation& cont) {
  out << "Program counter: " << cont.pc << std::endl;
  out << "Accumulator value: " << cont.accumulator << std::endl;
  out << "Registers: " << std::endl;
  for(std::map<std::string, int>::iterator mit = cont.registers.begin();
      mit != cont.registers.end(); ++mit) {
    out << "\t" << mit->first << ": " << mit->second << std::endl;
  }
  out << "Stack is " << cont.stack.size() << " levels deep" << std::endl;
  out << "Accumulator: " << cont.accumulator << std::endl;
  return out;
}
