#include <gram-php/PhpUnitEvaluator.h>

#include <fstream>

#include <pugixml.hpp>

#include <gram-php/DiffCalculator.h>
#include <gram-php/PhpSerializer.h>

using namespace pugi;
using namespace std;

PhpUnitEvaluator::PhpUnitEvaluator(CommandLine commandLine, const string& path, const string& file, const string& test)
    : commandLine(commandLine), path(path), file(file), test(test) {
  //
}

double PhpUnitEvaluator::evaluate(string program) {
  double& fitness = storedFitness[program];

  if (fitness) {
    return fitness;
  }

  ofstream sourceFile(file, ofstream::trunc);

  if (!sourceFile.is_open()) {
    return 0.0;
  }

  sourceFile << program << endl;

  commandLine.execute("cd " + path + " && vendor/phpunit/phpunit/phpunit " + test);

  return calculateFitness();;
}

double PhpUnitEvaluator::calculateFitness() {
  DiffCalculator calculator;
  PhpSerializer serializer;

  string documentPath(path + "phpunit-result.xml");

  xml_document document;

  if (!document.load_file(documentPath.c_str())) {
    return 10000.0;
  }

  vector<pair<PhpLiteral, PhpLiteral>> failures;

  auto testCases = document.child("testsuites").child("testsuite").children("testcase");

  for (auto &testCase : testCases) {
    if (!testCase.child("error").empty()) {
      return 10000.0;
    }

    for (auto &failure : testCase.children("failure")) {
      PhpLiteral expected = serializer.deserialize(failure.child("expected").text().get());
      PhpLiteral actual = serializer.deserialize(failure.child("actual").text().get());

      failures.push_back(make_pair(expected, actual));
    }
  }

  double fitness = 0.0;

  for (auto &failure : failures) {
    fitness += calculator.calculate(failure.first, failure.second);
  }

  return fitness;
}
