#ifndef GRAM_PHP_COMMAND_LINE
#define GRAM_PHP_COMMAND_LINE

#include <string>

class CommandLine {
 public:
  std::string execute(const std::string& command) const;
};

#endif // GRAM_PHP_COMMAND_LINE
