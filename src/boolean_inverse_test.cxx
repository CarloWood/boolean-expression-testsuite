#include "sys.h"
#include "debug.h"
#include "boolean-expression/BooleanExpression.h"
#include <random>

using namespace boolean;

int constexpr number_of_variables = 6;

std::string variable_name(int n)
{
  return std::string(1, 'A' + n);
}

struct Random
{
 private:
  std::random_device m_random_device;
  std::mt19937 m_generator;
  std::uniform_int_distribution<> m_some_variable;
  std::uniform_int_distribution<> m_zero_or_one;

 public:
  Random() : m_generator(m_random_device()), m_some_variable(0, number_of_variables - 1), m_zero_or_one(0, 1) { }

  Product product(std::vector <Product> const& variables);

 private:
  // Return a random number in the interval [1, number_of_variables].
  int var() { return m_some_variable(m_generator); }
};

Product Random::product(std::vector <Product> const& variables)
{
  int nv = var() + 1;           // The number of variables in the product.
  Product result{true};
  int count = 0;
  std::array<bool, number_of_variables> u = { { 0 } };
  while (count < nv)
  {
    int v = var();
    if (!u[v])
    {
      if (m_zero_or_one(m_generator))
        result *= variables[v];
      else
      {
        Product v_inverse{variables[v]};
        v_inverse.negate();     // negate() only inverses a Product when that product is a single variable (which is the case here).
        result *= v_inverse;
      }
      u[v] = true;
      ++count;
    }
  }
  return result;
}

struct MyExpression : public Expression
{
  using Expression::Expression;
  size_t terms() const { return m_sum_of_products.size(); }
};

int main()
{
#ifdef DEBUGGLOBAL
  GlobalObjectManager::main_entered();
#endif
  Debug(NAMESPACE_DEBUG::init());

  Random random;

  std::vector <Product> variables;
  for (int n = 0; n < number_of_variables; ++n)
    variables.emplace_back(Context::instance().create_variable(variable_name(n)));

  for (unsigned int number_of_terms = 1; number_of_terms < 6; ++number_of_terms)
  {
    Dout(dc::notice, "With " << number_of_terms << " terms:");
    for (int i = 0; i < 100;)
    {
      MyExpression sum{false};
      for (unsigned int tn = 0; tn < number_of_terms; ++tn)
        sum += random.product(variables);
      if (sum.terms() == number_of_terms)
      {
        Expression sum_inverse{sum.inverse()};
        Dout(dc::notice, "The inverse of " << sum << " = " << sum_inverse);
        // Sanity checks:
        Expression ORed = sum + sum_inverse;
        ASSERT(ORed.equivalent(Expression::one()));
        Expression ANDed = sum.times(sum_inverse);
        ASSERT(ANDed.is_zero());
        ++i;
      }
    }
  }
}
