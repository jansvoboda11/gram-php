#include <gram-php/PhpUnitEvaluator.h>

#include <fstream>
#include <regex>

#include <pugixml.hpp>

#include <gram-php/DiffCalculator.h>
#include <gram-php/PhpLiteral.h>
#include <gram-php/PhpSerializer.h>

using namespace pugi;
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

  sourceFile << program << endl;

  commandLine.execute("cd " + path + " && vendor/phpunit/phpunit/phpunit");

  return calculateFitness();
}

double PhpUnitEvaluator::calculateFitness() const {
  DiffCalculator calculator;
  PhpSerializer serializer;

  string documentPath(path + "phpunit-result.xml");

  xml_document document;

  if (!document.load_file(documentPath.c_str())) {
    throw logic_error("Could not open file with PhpUnit results.");
  }

  vector<pair<PhpLiteral, PhpLiteral>> failures;

  auto testCases = document.child("testsuites").child("testsuite").child("testsuite").children("testcase");

  for (auto &testCase : testCases) {
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
