#ifndef GRAM_PHPUNIT_EVALUATOR
#define GRAM_PHPUNIT_EVALUATOR

#include <memory>

#include <gram/language/Evaluator.h>

#include "CommandLine.h"

class PhpUnitEvaluator : public gram::Evaluator {
 public:
  PhpUnitEvaluator(CommandLine commandLine, const std::string& path);
  double evaluate(std::string program) const;
 private:
  CommandLine commandLine;
  std::string path;
};

#endif // GRAM_PHPUNIT_EVALUATOR
