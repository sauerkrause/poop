#ifndef __CONTINUATION_H__
#define __CONTINUATION_H__

#include <vector>
#include <string>
#include <map>
#include <ostream>

struct continuation {
  size_t pc;
  std::vector<char> program;
  std::vector<std::map<std::string, int> > stack;
  std::map<std::string, int> registers;
  int accumulator;

  continuation();
  continuation(const continuation & cont);
  continuation& operator=(continuation cont);

  friend std::ostream& operator<<(std::ostream& out, continuation &cont);
private:
  void swap(continuation &);
};
#endif
