#include "../include/PhpUnitEvaluator.h"

#include <fstream>

using namespace std;

PhpUnitEvaluator::PhpUnitEvaluator(CommandLine commandLine, const string& path)
    : commandLine(commandLine), path(path) {
  //
}

double PhpUnitEvaluator::evaluate(string program) const {
  ofstream outputFile(path + "src/Calculator.php", ofstream::trunc);

  if (!outputFile.is_open()) {
    return 0.0;
  }

  outputFile << "<?php namespace Examples; " + program << endl;

  string result = commandLine.execute("cd " + path + " && vendor/phpunit/phpunit/phpunit");

  // parse the result and calculate fitness

  return 0.0;
}
