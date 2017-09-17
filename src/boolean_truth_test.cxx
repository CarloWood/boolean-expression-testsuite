#include "sys.h"
#include "debug.h"
#include "boolean-expression/TruthProduct.h"

int main()
{
  using namespace boolean;

  TruthProduct tp;

  Variable vA{Context::instance().create_variable("A", 0)};
  Variable vB{Context::instance().create_variable("B", 0)};
  Variable vC{Context::instance().create_variable("C", 0)};
  Variable vD{Context::instance().create_variable("D", 0)};

  Product const A(vA);
  Product const B(vB);
  Product const C(vC);
  Product const D(vD);
  Product const not_A(vA, true);
  Product const not_B(vB, true);
  Product const not_C(vC, true);
  Product const not_D(vD, true);

  Expression e;

  e  = A * D;
  e += not_A * B * not_D;
  e += not_B * C;

  std::cout << "e = " << e << std::endl;

  tp *= B;
  tp *= C;

  TruthProduct const end(tp);
  do
  {
    std::cout << "tp = " << tp << " --> e = " << e(tp) << std::endl;
  }
  while(++tp != end);
}
