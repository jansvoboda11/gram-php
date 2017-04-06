#include <fstream>
#include <iostream>

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
  if (argc != 5) {
    return 1;
  }

  string grammarString = loadFile(argv[1]);

  auto numberGenerator1 = make_unique<TwisterNumberGenerator>();
  auto numberGenerator2 = make_unique<TwisterNumberGenerator>();
  auto numberGenerator3 = make_unique<TwisterNumberGenerator>();
  auto numberGenerator4 = make_unique<TwisterNumberGenerator>();
  auto boolGenerator = make_unique<TwisterBoolGenerator>(0.1);

  auto selector = make_unique<TournamentSelector>(10, move(numberGenerator1));
  auto mutation = make_unique<NumberMutation>(move(boolGenerator), move(numberGenerator2));
  auto crossover = make_unique<OnePointCrossover>(move(numberGenerator3));
  auto reproducer = make_shared<Reproducer>(move(selector), move(crossover), move(mutation));

  BnfRuleParser parser;

  auto grammar = make_shared<ContextFreeGrammar>(parser.parse(grammarString));

  RandomInitializer initializer(move(numberGenerator4), grammar, 50);

  CommandLine commandLine;

  auto evaluator = make_unique<PhpUnitEvaluator>(commandLine, argv[2], argv[3], argv[4]);

  Evolution evolution(move(evaluator));

  Population population = initializer.initialize(200, reproducer);

  Individual result = evolution.run(population);

  cout << result.serialize() << endl;

  return 0;
}
