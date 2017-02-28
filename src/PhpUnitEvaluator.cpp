#include "../include/PhpUnitEvaluator.h"

#include <fstream>
#include <regex>

using namespace std;

PhpUnitEvaluator::PhpUnitEvaluator(CommandLine commandLine, const string& path)
    : commandLine(commandLine), path(path) {
  //
}

double PhpUnitEvaluator::evaluate(string program) const {
  ofstream sourceFile(path + "src/Calculator.php", ofstream::trunc);

  if (!sourceFile.is_open()) {
    return 0.0;
  }

  sourceFile << "<?php namespace Examples; " + program << endl;

  string testOutput = commandLine.execute("cd " + path + " && vendor/phpunit/phpunit/phpunit");

  return calculateFitness(testOutput);
}

double PhpUnitEvaluator::calculateFitness(string testOutput) const {

  return 0.0;
}
