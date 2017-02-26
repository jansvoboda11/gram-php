#include <fstream>

#include <gram/individual/crossover/OnePointCrossover.h>
#include <gram/individual/mutation/NumberMutation.h>
#include <gram/language/parser/BnfRuleParser.h>
#include <gram/population/initializer/RandomInitializer.h>
#include <gram/population/selector/TournamentSelector.h>
#include <gram/util/bool_generator/TwisterBoolGenerator.h>
#include <gram/util/number_generator/TwisterNumberGenerator.h>
#include <gram/Evolution.h>

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

bool putFile(const string& name, const string& content) {
  ofstream outputFile(name);

  if (!outputFile.is_open()) {
    return false;
  }

  outputFile << content;

  return true;
}

string execute(const string& command) {
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

class FakeEvaluator : public Evaluator {
 public:
  FakeEvaluator(const string& path) : path(path) {};

  double evaluate(string program) const {
    putFile(path + "src/Calculator.php", "<?php namespace Examples; " + program);

    string result = execute("cd " + path + " && vendor/phpunit/phpunit/phpunit");

    return 0.0;
  }

 private:
  string path;
};

int main(int argc, char* argv[]) {
  if (argc != 2) {
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

  unique_ptr<Evaluator> evaluator = make_unique<FakeEvaluator>("/cygdrive/c/Code/gram-php/example/calculator/");

  Evolution evolution(move(evaluator));

  Population population = initializer.initialize(60, reproducer);

  Individual result = evolution.run(population);

  return 0;
}
