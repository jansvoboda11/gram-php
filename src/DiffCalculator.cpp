#include <gram-php/DiffCalculator.h>

using namespace std;

double DiffCalculator::calculate(PhpLiteral first, PhpLiteral second) const {
  if (first.type() != second.type()) {
    return TYPE_DIFF;
  }

  return 0.0;
}
