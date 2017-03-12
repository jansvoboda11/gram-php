#include <gram-php/PhpSerializer.h>

#include <regex>

using namespace std;

PhpLiteral PhpSerializer::deserialize(string serializedLiteral) const {
  regex nullPattern("^[nN];$");
  regex booleanPattern("^b:([01]);$");
  regex integerPattern("^i:(-?(?:0|[1-9]+\\d*));$");
  regex decimalPattern("^d:(-?(?:0|[1-9]+\\d*)(?:.[0-9]*(?:[eE][+-][1-9]+\\d*)?)?);$");
  regex stringPattern("^s:(0|[1-9]+\\d*):\"(.*)\";$");

  smatch matches;

  if (regex_match(serializedLiteral, matches, nullPattern)) {
    return PhpLiteral();
  }

  if (regex_match(serializedLiteral, matches, booleanPattern)) {
    return deserializeBoolean(matches[1]);
  }

  if (regex_match(serializedLiteral, matches, integerPattern)) {
    return deserializeInteger(matches[1]);
  }

  if (regex_match(serializedLiteral, matches, decimalPattern)) {
    return deserializeDecimal(matches[1]);
  }

  if (regex_match(serializedLiteral, matches, stringPattern)) {
    return deserializeString(matches[2], matches[1]);
  }

  throw logic_error("Could not recognize serialized literal.");
}

PhpLiteral PhpSerializer::deserializeBoolean(string value) const {
  if (value == "0") {
    return PhpLiteral(false);
  }

  if (value == "1") {
    return PhpLiteral(true);
  }

  throw logic_error("Could not unserialize boolean value \"" + value + "\".");
}

PhpLiteral PhpSerializer::deserializeInteger(string value) const {
  try {
    return PhpLiteral(stoi(value));
  } catch (out_of_range exception) {
    throw logic_error("Could not unserialize too large integer \"" + value + "\".");
  } catch (invalid_argument exception) {
    throw logic_error("Could not unserialize integer \"" + value + "\".");
  }
}

PhpLiteral PhpSerializer::deserializeDecimal(string value) const {
  try {
    return PhpLiteral(stod(value));
  } catch (out_of_range exception) {
    throw logic_error("Could not unserialize too large decimal number \"" + value + "\".");
  } catch (invalid_argument exception) {
    throw logic_error("Could not unserialize decimal number \"" + value + "\".");
  }
}

PhpLiteral PhpSerializer::deserializeString(string value, string promisedLength) const {
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
