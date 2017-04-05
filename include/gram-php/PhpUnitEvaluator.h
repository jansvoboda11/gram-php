#ifndef GRAM_PHPUNIT_EVALUATOR
#define GRAM_PHPUNIT_EVALUATOR

#include <memory>
#include <unordered_map>

#include <gram/language/Evaluator.h>

#include <gram-php/CommandLine.h>

class PhpUnitEvaluator : public gram::Evaluator {
 public:
  PhpUnitEvaluator(CommandLine commandLine, const std::string& path, const std::string& file, const std::string& test);
  double evaluate(std::string program);
 private:
  double calculateFitness();
  CommandLine commandLine;
  std::string path;
  std::string file;
  std::string test;
  std::unordered_map<std::string, double> storedFitness;
};

#endif // GRAM_PHPUNIT_EVALUATOR
