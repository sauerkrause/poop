#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include <map>

// Zeros the accumulator.
void zeroAccumulator(int & accumulator) {
  accumulator = 0;
  return;
}

// Sets a register to the value of the accumulator.
void setRegister(std::vector<char>::iterator & pc, std::vector<char> & program, std::map<std::string, int> & registers, int & accumulator);

// Sets the accumulator to the value of the register.
void readName(std::vector<char>::iterator & pc, std::vector<char> & program, std::map<std::string, int> & registers, int & accumulator);

void evaluate(std::vector<char>::iterator & pc,
              std::vector<char> & program,
              std::map<std::string, int> & registers,
              std::vector<std::map<std::string, int> > & stack,
              int & accumulator);

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cout << "Please supply an argument file!" << std::endl;
    return 0;
  }
    
  std::ifstream fin(argv[1]);
    
  std::vector<char> program;
  int accumulator;
  zeroAccumulator(accumulator);
  std::copy(std::istream_iterator<char>(fin), std::istream_iterator<char>(), std::back_inserter(program));
  std::vector<std::map<std::string, int> > programStack;
  std::map<std::string, int> programRegisters;
    
  std::vector<char>::iterator pc = program.begin();
  evaluate(pc, program, programRegisters, programStack, accumulator);
  return 0;
}

void evaluate(std::vector<char>::iterator & pc,
              std::vector<char> & program,
              std::map<std::string, int> & registers,
              std::vector<std::map<std::string, int> > & stack,
              int & accumulator) {
    
  for(pc; pc != program.end(); ++pc) {
    char currentOp = *pc;
    switch (currentOp) {
    case '`':
      readName(pc, program, registers, accumulator);
      break;
    case '^':
      ++accumulator;
      break;
    case '-':
      accumulator = -accumulator;
      break;
    case '>':
      setRegister(pc, program, registers, accumulator);
      break;
    case '{':
      stack.push_back(std::map<std::string, int>(registers));
      evaluate(++pc, program, registers, stack, accumulator);
      break;
    case '}':
      registers = std::map<std::string, int>(stack.back());
      stack.pop_back();
      return;
    default:
      //      std::cout << currentOp;
      break;
    }
  }
}


// Sets the value of a register on the current frame.
void setRegister(std::vector<char>::iterator & pc, std::vector<char> & program, std::map<std::string, int> & registers, int & accumulator) {
  ++pc;
  std::string name;
  int c = *pc;
  switch(c) {
  case '1':
    std::cout << (char)accumulator;
    goto doneSetRegister;
  case '2':
    std::cerr << (char)accumulator;
    goto doneSetRegister;
  case '`':
    ++pc;
    break;
  default:
    goto doneSetRegister;
  }
  while(pc != program.end() && *pc != '\'') {
    int c = *pc;
    name.push_back(c);
    ++pc;
  }
  registers[name] = accumulator;
 doneSetRegister:
  zeroAccumulator(accumulator);
  return;
}

// Reads a value of a register off the current frame.
void readName(std::vector<char>::iterator & pc, std::vector<char> & program, std::map<std::string, int> & registers, int & accumulator) {
  bool done = false;
  std::string name;
  for(++pc; !done && pc != program.end(); ++pc) {
    char currentOp = *pc;
    switch(currentOp) {
    case '\'':
      done = true;
      goto escapeReadNameLoop;
    default:
      name.push_back(currentOp);
      break;
    }
  }
 escapeReadNameLoop:
  if(name.size()) {
    accumulator = registers[name];
  }
  return;
}

