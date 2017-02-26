#include "../include/CommandLine.h"

#include <stdexcept>

using namespace std;

string CommandLine::execute(const string& command) const {
  FILE *pipe = popen(command.c_str(), "r");

  if (!pipe) {
    throw runtime_error("Could not open command line.");
  }

  string result;
  char buffer[128];

  while (fgets(buffer, 128, pipe)) {
    result += buffer;
  }

  pclose(pipe);
  return result;
}
