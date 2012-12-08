#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "continuation.h"
#include "poop.h"


// The map of global variables.
std::map<std::string, int> globals;
std::map<std::string, continuation> continuations;

static void readSomeName(continuation & cont, bool global);

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cout << "Please supply an argument file!" << std::endl;
    return 0;
  }

  continuation cc;
    
  std::ifstream fin(argv[1]);
  std::copy(std::istream_iterator<char>(fin), std::istream_iterator<char>(), std::back_inserter(cc.program));
  evaluate(cc);

  return 0;
}

void zeroAccumulator(continuation & cont) {
  cont.accumulator = 0;
}

void evaluate(continuation & cont) {
  for(; cont.pc < cont.program.size(); ++cont.pc) {
    char currentOp = cont.program[cont.pc];
    switch (currentOp) {
    case '`':
      readName(cont);
      break;
    case ';':
      readGlobalName(cont);
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
      break;
    case '}':
      cont.registers = std::map<std::string, int>(cont.stack.back());
      cont.stack.pop_back();
      break;
    case '*':
      stuffContinuation(cont);
      break;
    case '?':
      takeContinuation(cont);
      break;
    default:
      // It's a comment!
      break;
    }
  }
}

// Stuffs the current continuation into a named global.
void stuffContinuation(continuation & cont) {
  std::string name;
  while(++cont.pc < cont.program.size()) {
    char c = cont.program[cont.pc];
    if(c == '|')
      break;
    name.push_back(c);
  }
  continuations[name] = cont;
  zeroAccumulator(cont);
}

// Takes the current continuation and shoves it in the trash
void takeContinuation(continuation & cont) {
  std::string name;
  while(++cont.pc < cont.program.size()) {
    char c = cont.program[cont.pc];
    if(c == '|')
      break;
    name.push_back(c);
  }
  if(continuations.count(name) && cont.accumulator)
    cont = continuation(continuations[name]);
}
// Sets the value of a register on the current frame.
void setRegister(continuation & cont) {
  ++cont.pc;
  std::string name;
  bool global = false;
  int c = cont.program[cont.pc];
  switch(c) {
  case '1':
    std::cout << (char)cont.accumulator;
    goto doneSetRegister;
  case '2':
    std::cerr << (char)cont.accumulator;
    goto doneSetRegister;
  case '`':
    break;
  case ';':
    global = true;
    break;
  default:
    goto doneSetRegister;
  }
  while(++cont.pc < cont.program.size() && cont.program[cont.pc] != '\'') {
    char c = cont.program[cont.pc];
    name.push_back(c);
  }
  if(global)
    globals[name] = cont.accumulator;
  else
    cont.registers[name] = cont.accumulator;
 doneSetRegister:
  zeroAccumulator(cont);
  return;
}

// Reads a value of a register off the global frame.
void readGlobalName(continuation & cont) {
  readSomeName(cont, true);
}
// Reads a value of a register off the current frame.
void readName(continuation & cont) {
  readSomeName(cont, false);
}

void readSomeName(continuation & cont, bool global) {
  std::string name;
  ++cont.pc;
  bool add = false;
  for(; cont.pc < cont.program.size(); ++cont.pc) {
    char currentOp = cont.program[cont.pc];
    switch(currentOp) {
    case '\'':
      goto escapeReadNameLoop;
    case '+':
      add = true;
      goto escapeReadNameLoop;
    default:
      name.push_back(currentOp);
      break;
    }
  }
 escapeReadNameLoop:
  if(name.size()) {
    if(global)
      cont.accumulator = add ? cont.accumulator + globals[name] : globals[name];
    else
      cont.accumulator = add ? cont.accumulator + cont.registers[name] : cont.registers[name];
  }
  return;
}

