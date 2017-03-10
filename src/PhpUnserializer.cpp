#include <gram-php/PhpUnserializer.h>

#include <regex>

using namespace std;

PhpLiteral PhpUnserializer::unserialize(string serializedLiteral) const {
  regex booleanPattern("^b:([01]);$");
  regex integerPattern("^i:(-?(?:0|[1-9]+\\d*));$");
  regex decimalPattern("^d:(-?(?:0|[1-9]+\\d*)(?:.[0-9]*(?:[eE][+-][1-9]+\\d*)?)?);$");
  regex stringPattern("^s:(0|[1-9]+\\d*):\"(.*)\";$");

  smatch matches;

  if (regex_match(serializedLiteral, matches, booleanPattern)) {
    string match = matches[1];

    if (match == "0") {
      return PhpLiteral(false);
    }

    if (match == "1") {
      return PhpLiteral(true);
    }

    throw logic_error("Could not unserialize boolean value \"" + match + "\".");
  }

  if (regex_match(serializedLiteral, matches, integerPattern)) {
    string match = matches[1];

    try {
      int value = stoi(match);
      return PhpLiteral(value);
    } catch (out_of_range exception) {
      throw logic_error("Could not unserialize too large integer \"" + match + "\".");
    } catch (invalid_argument exception) {
      throw logic_error("Could not unserialize integer \"" + match + "\".");
    }
  }

  if (regex_match(serializedLiteral, matches, decimalPattern)) {
    string match = matches[1];

    try {
      double value = stod(match);
      return PhpLiteral(value);
    } catch (out_of_range exception) {
      throw logic_error("Could not unserialize too large decimal number \"" + match + "\".");
    } catch (invalid_argument exception) {
      throw logic_error("Could not unserialize decimal number \"" + match + "\".");
    }
  }

  if (regex_match(serializedLiteral, matches, stringPattern)) {
    string promisedLength = matches[1];
    string value = matches[2];
    int length;

    try {
      length = stoi(promisedLength);
    } catch (out_of_range exception) {
      throw logic_error("Could not unserialize too large string length \"" + promisedLength + "\".");
    } catch (invalid_argument exception) {
      throw logic_error("Could not unserialize string length \"" + promisedLength + "\".");
    }

    if (length != value.length()) {
      throw logic_error("Length of string \"" + value + "\" does not match promised length \"" + promisedLength + "\".");
    }

    return PhpLiteral(value);
  }

  throw logic_error("Could not recognize serialized literal.");
}
