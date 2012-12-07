#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "continuation.h"
#include "lang.h"

// The map of global variables.
std::map<std::string, int> globals;

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cout << "Please supply an argument file!" << std::endl;
    return 0;
  }

  continuation cc;
    
  std::ifstream fin(argv[1]);
  std::copy(std::istream_iterator<char>(fin), std::istream_iterator<char>(), std::back_inserter(cc.program));
  cc.pc = cc.program.begin();
  evaluate(cc);

  return 0;
}

void zeroAccumulator(continuation & cont) {
  cont.accumulator = 0;
}

void evaluate(continuation & cont) {
  for(cont.pc; cont.pc != cont.program.end(); ++cont.pc) {
    char currentOp = *cont.pc;
    switch (currentOp) {
    case '`':
      readName(cont);
      break;
    case '^':
      ++cont.accumulator;
      break;
    case '-':
      cont.accumulator = -cont.accumulator;
      break;
    case '>':
      setRegister(cont);
      break;
    case '{':
      cont.stack.push_back(cont.registers);
      ++cont.pc;
      evaluate(cont);
      break;
    case '}':
      cont.registers = std::map<std::string, int>(cont.stack.back());
      cont.stack.pop_back();
      return;
    default:
      //      std::cout << currentOp;
      break;
    }
  }
}


// Sets the value of a register on the current frame.
void setRegister(continuation & cont) {
  ++cont.pc;
  std::string name;
  int c = *cont.pc;
  switch(c) {
  case '1':
    std::cout << (char)cont.accumulator;
    goto doneSetRegister;
  case '2':
    std::cerr << (char)cont.accumulator;
    goto doneSetRegister;
  case '`':
    ++cont.pc;
    break;
  default:
    goto doneSetRegister;
  }
  while(cont.pc != cont.program.end() && *cont.pc != '\'') {
    int c = *cont.pc;
    name.push_back(c);
    ++cont.pc;
  }
  cont.registers[name] = cont.accumulator;
 doneSetRegister:
  zeroAccumulator(cont);
  return;
}

// Reads a value of a register off the current frame.
void readName(continuation & cont) {
  std::string name;
  for(++cont.pc; cont.pc != cont.program.end(); ++cont.pc) {
    char currentOp = *cont.pc;
    switch(currentOp) {
    case '\'':
      goto escapeReadNameLoop;
    default:
      name.push_back(currentOp);
      break;
    }
  }
 escapeReadNameLoop:
  if(name.size()) {
    cont.accumulator = cont.registers[name];
  }
  return;
}

