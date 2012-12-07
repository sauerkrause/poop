#ifndef __CONTINUATION_H__
#define __CONTINUATION_H__

#include <vector>
#include <string>
#include <map>

struct continuation {
  std::vector<char>::iterator pc;
  std::vector<char> program;
  std::vector<std::map<std::string, int> > stack;
  std::map<std::string, int> registers;
  int accumulator;

  continuation();
  continuation(const continuation & cont);
};
#endif
