#include "sys.h"
#include "debug.h"
#include "boolean-expression/BooleanExpression.h"

using namespace boolean;

int main()
{
  // Creating variables.

  Context& context{Context::instance()};
  Variable vA{context.create_variable("A")};
  Variable vB{context.create_variable("B")};
  Variable vC{context.create_variable("C")};
  Variable vD{context.create_variable("D")};

  // Construct single variable "Products" from variables.

  Product a(vA);
  Product _a(vA, true);
  Product b, _b;
  b = vB;
  _b = !vB;

  // Multiplying Products.

  Product _ab{_a};
  _ab *= b;
  Product ab_c;
  ab_c = vA * b * !vC;
  assert(_ab * ab_c == 0);

  // // Expressions.

  Expression e{true};           // True
  Expression f(_ab);            // !A * B.
  Expression g(f.copy());       // Must explicitely use copy().

  e  = vA * vD;                 // A * D.
  e += g * !vD;                 // A * D + !A * B * !D.
  e += !vB * vC;                // A * D + !A * B * !D + !B * C.
  f = e.times(f);               // !A * B * !D. Must explicitely use 'times()' to multiply two Expressions.
  e = !_ab;                     // A + !B
  f = f.inverse();              // A + !B + D. Must explicitely use 'inverse()' to calculate the inverse of an Expression.

  std::cout << "e = " << e << std::endl;
  std::cout << "f = " << f << std::endl;
}
