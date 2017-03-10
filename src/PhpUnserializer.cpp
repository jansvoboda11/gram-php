#include <gram-php/PhpUnserializer.h>

#include <regex>

using namespace std;

PhpLiteral PhpUnserializer::unserialize(string serializedLiteral) const {
  regex booleanPattern("^b:([01]);$");
  regex integerPattern("^i:(-?[1-9]+\\d*);$");
  regex decimalPattern("^d:(-?[0-9]+(?:.[0-9]*(?:[eE][+-][1-9]+\\d*)?)?);$"); // handle 0.
  regex stringPattern("^s:[1-9]+\\d*:\"(.*)\";$");

  smatch matches;

  if (regex_match(serializedLiteral, matches, booleanPattern)) {
    if (matches[1] == "0") {
      return PhpLiteral(false);
    }

    if (matches[1] == "1") {
      return PhpLiteral(true);
    }

    throw logic_error("Could not parse serialized boolean.");
  }

  if (regex_match(serializedLiteral, matches, integerPattern)) {
    try {
      int value = stoi(matches[1]);
      return PhpLiteral(value);
    } catch (...) {
      throw logic_error("Could not parse serialized integer.");
    }
  }

  if (regex_match(serializedLiteral, matches, decimalPattern)) {
    try {
      double value = stod(matches[1]);
      return PhpLiteral(value);
    } catch (...) {
      throw logic_error("Could not parse serialized decimal number.");
    }
  }

  if (regex_match(serializedLiteral, matches, stringPattern)) {
    return PhpLiteral(matches[1]);
  }

  throw logic_error("Could not parse serialized literal.");
}
