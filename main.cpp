#include <fstream>

#include <gram/individual/crossover/OnePointCrossover.h>
#include <gram/individual/mutation/NumberMutation.h>
#include <gram/language/parser/BnfRuleParser.h>
#include <gram/population/initializer/RandomInitializer.h>
#include <gram/population/selector/TournamentSelector.h>
#include <gram/util/bool_generator/TwisterBoolGenerator.h>
#include <gram/util/number_generator/TwisterNumberGenerator.h>
#include <gram/Evolution.h>

#include <gram-php/PhpUnitEvaluator.h>

using namespace gram;
using namespace std;

string loadFile(const string& name) {
  ifstream grammarFile(name);

  if (!grammarFile.is_open()) {
    return "";
  }

  string content((istreambuf_iterator<char>(grammarFile)), istreambuf_iterator<char>());

  return content;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    return 1;
  }

  string grammarString = loadFile(argv[1]);

  unique_ptr<NumberGenerator> numberGenerator1 = make_unique<TwisterNumberGenerator>();
  unique_ptr<NumberGenerator> numberGenerator2 = make_unique<TwisterNumberGenerator>();
  unique_ptr<NumberGenerator> numberGenerator3 = make_unique<TwisterNumberGenerator>();
  unique_ptr<NumberGenerator> numberGenerator4 = make_unique<TwisterNumberGenerator>();
  unique_ptr<BoolGenerator> boolGenerator = make_unique<TwisterBoolGenerator>(1.0);

  auto selector = make_unique<TournamentSelector>(move(numberGenerator1));
  auto mutation = make_unique<NumberMutation>(move(boolGenerator), move(numberGenerator2));
  auto crossover = make_unique<OnePointCrossover>(move(numberGenerator3));
  auto reproducer = make_shared<Reproducer>(move(selector), move(crossover), move(mutation));

  BnfRuleParser parser;

  auto grammar = make_shared<ContextFreeGrammar>(parser.parse(grammarString));

  RandomInitializer initializer(move(numberGenerator4), grammar, 50);

  CommandLine commandLine;

  unique_ptr<Evaluator> evaluator = make_unique<PhpUnitEvaluator>(commandLine, argv[2]);

  Evolution evolution(move(evaluator));

  Population population = initializer.initialize(60, reproducer);

  Individual result = evolution.run(population);

  return 0;
}