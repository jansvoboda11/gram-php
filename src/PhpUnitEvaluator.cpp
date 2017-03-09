#include <gram-php/PhpUnitEvaluator.h>

#include <fstream>
#include <regex>

#include <pugixml.hpp>

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

  string testOutput = commandLine.execute("cd " + path + " && vendor/phpunit/phpunit/phpunit");

  return calculateFitness(testOutput);
}

double PhpUnitEvaluator::calculateFitness(string testOutput) const {
  string documentPath(path + "phpunit-result.xml");

  xml_document document;

  if (!document.load_file(documentPath.c_str())) {
    return 0.0;
  }

  string name = document
      .child("testsuites")
      .child("testsuite")
      .child("testsuite")
      .child("testcase")
      .child("failure")
      .child("expected")
      .text()
      .get(); // first failure, expected value

  return 0.0;
}
