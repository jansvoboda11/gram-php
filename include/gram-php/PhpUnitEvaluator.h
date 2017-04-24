#ifndef GRAM_PHPUNIT_EVALUATOR
#define GRAM_PHPUNIT_EVALUATOR

#include <memory>
#include <unordered_map>

#include <gram/individual/Genotype.h>
#include <gram/evaluation/Evaluator.h>
#include <gram/language/mapper/ContextFreeMapper.h>

#include <gram-php/CommandLine.h>

class PhpUnitEvaluator : public gram::Evaluator {
 public:
  PhpUnitEvaluator(CommandLine commandLine, std::shared_ptr<gram::ContextFreeMapper> mapper, const std::string& path, const std::string& file, const std::string& test);
  double evaluate(const gram::Genotype& genotype) noexcept;
 private:
  double calculateFitness();
  CommandLine commandLine;
  std::shared_ptr<gram::ContextFreeMapper> mapper;
  std::string path;
  std::string file;
  std::string test;
  std::unordered_map<std::string, double> storedFitness;
};

#endif // GRAM_PHPUNIT_EVALUATOR
