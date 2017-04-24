#include <fstream>
#include <iostream>

#include <gram/evaluation/driver/SingleThreadDriver.h>
#include <gram/individual/comparer/LowFitnessComparer.h>
#include <gram/individual/crossover/OnePointCrossover.h>
#include <gram/individual/mutation/NaiveCodonMutation.h>
#include <gram/language/parser/BnfRuleParser.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <gram/population/initializer/RandomInitializer.h>
#include <gram/population/reproducer/PassionateReproducer.h>
#include <gram/population/selector/TournamentSelector.h>
#include <gram/random/bool_generator/BoolGenerator.h>
#include <gram/random/number_generator/StdNumberGenerator.h>
#include <gram/util/logger/NullLogger.h>
#include <gram/Evolution.h>

#include <gram-php/PhpUnitEvaluator.h>
#include <random>

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

  auto numberGenerator1 = make_unique<StdNumberGenerator<mt19937>>();
  auto numberGenerator2 = make_unique<StdNumberGenerator<mt19937>>();
  auto numberGenerator3 = make_unique<StdNumberGenerator<mt19937>>();
  auto numberGenerator4 = make_unique<StdNumberGenerator<mt19937>>();
  auto numberGenerator5 = make_unique<StdNumberGenerator<mt19937>>();
  auto boolGenerator = make_unique<BoolGenerator>(move(numberGenerator5), 0.15);

  auto comparer = make_unique<LowFitnessComparer>();

  auto selector = make_unique<TournamentSelector>(10, move(numberGenerator1), move(comparer));
  auto mutation = make_unique<NaiveCodonMutation>(move(boolGenerator), move(numberGenerator2));
  auto crossover = make_unique<OnePointCrossover>(move(numberGenerator3));
  auto reproducer = make_shared<PassionateReproducer>(move(selector), move(crossover), move(mutation));

  BnfRuleParser parser;

  auto grammar = make_shared<ContextFreeGrammar>(parser.parse(grammarString));
  auto mapper = make_shared<ContextFreeMapper>(grammar, 3);

  RandomInitializer initializer(move(numberGenerator4), 50);

  CommandLine commandLine;

  auto evaluator = make_unique<PhpUnitEvaluator>(commandLine, mapper, argv[2], argv[3], argv[4]);

  auto evaluationDriver = make_unique<SingleThreadDriver>(move(evaluator));
  auto logger = make_unique<NullLogger>();

  Evolution evolution(move(evaluationDriver), move(logger));

  Population population = initializer.initialize(200, reproducer);

  function<bool(Population&)> successCondition = [](Population& currentPopulation) {
    return currentPopulation.lowestFitness() < 0.1;
  };

  Population result = evolution.run(population, successCondition);

  cout << result.individualWithLowestFitness().serialize(*mapper) << endl;

  return 0;
}
