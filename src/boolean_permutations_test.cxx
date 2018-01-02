#include "sys.h"
#include "debug.h"
#include "boolean-expression/BooleanExpression.h"
#include "boolean-expression/TruthProduct.h"
#include "utils/MultiLoop.h"
#include <iostream>
#include <bitset>
#include <algorithm>

class TruthTable
{
  boolean::TruthProduct const m_truth_product;
  uint64_t m_table;

 public:
  TruthTable(int number_of_booleans) : m_truth_product(number_of_booleans)
  {
    ASSERT(number_of_booleans <= 6);
  }

  void operator=(boolean::Expression const& expression);
  friend bool operator<(TruthTable const& truth_table1, TruthTable const& truth_table2) { return truth_table1.m_table < truth_table2.m_table; }
  bool operator==(TruthTable const& truth_table) { return m_table == truth_table.m_table; }
  bool operator!=(TruthTable const& truth_table) { return m_table != truth_table.m_table; }
  friend std::ostream& operator<<(std::ostream& os, TruthTable const& truth_table);
};

void TruthTable::operator=(boolean::Expression const& expression)
{
  boolean::TruthProduct tp(m_truth_product);
  m_table = 0;
  uint64_t bit = 1;
  do
  {
    boolean::Expression evaluated_expression{expression(tp)};
    ASSERT(evaluated_expression.is_literal());
    m_table |= evaluated_expression.is_one() ? bit : 0;
    bit <<= 1;
  }
  while(++tp != m_truth_product);
}

std::ostream& operator<<(std::ostream& os, TruthTable const& truth_table)
{
  std::bitset<64> bs(truth_table.m_table);
  os << bs;
  return os;
}

int main()
{
#ifdef DEBUGGLOBAL
  GlobalObjectManager::main_entered();
#endif
  Debug(NAMESPACE_DEBUG::init());

  // Turn debug output off when compiled with optimization.
#ifdef __OPTIMIZE__
  Dout(dc::notice, "Compiled with optimization... turning debug output off to speed up execution.");
  Debug(libcw_do.off());
#endif

  using namespace boolean;

  int const number_of_variables = 3;
  std::vector<Variable> v;
  char const* const names[] = { "w", "x", "y", "z" };
  for (int i = 0; i < number_of_variables; ++i)
    v.emplace_back(Context::instance().create_variable(names[i], i * i));

  TruthTable truth_table(number_of_variables);

  std::vector<Product> products;
  //products.push_back(0);
  //products.push_back(1);

  for (int n = 1; n <= number_of_variables; ++n)
  {
    for (MultiLoop variable(n); !variable.finished(); variable.next_loop())
      for(; variable() < number_of_variables; variable.start_next_loop_at(0))
      {
        if (*variable > 0 && variable() <= variable[*variable - 1])
        {
          variable.breaks(0);
          break;
        }
        if (variable.inner_loop())
        {
          for (MultiLoop inverted(n); !inverted.finished(); inverted.next_loop())
            for(; inverted() < 2; inverted.start_next_loop_at(0))
            {
              if (inverted.inner_loop())
              {
                Product product(v[variable[0]], inverted[0]);
                for (int i = 1; i < n; ++i)
                {
                  Product next_factor(v[variable[i]], inverted[i]);
                  product *= next_factor;
                }
                products.push_back(product);
              }
            }
        }
      }
  }

  Dout(dc::notice, "Products:");
  for (auto&& p : products)
    Dout(dc::notice, p);

  int const number_of_products = products.size();

  std::vector<Expression> expressions;
  int index = -1;
  std::map<TruthTable, int> m;

  expressions.emplace_back(false);
  truth_table = Expression::zero();
  m.emplace(truth_table, ++index);
  expressions.emplace_back(true);
  truth_table = Expression::one();
  m.emplace(truth_table, ++index);

  Dout(dc::notice, "Expressions:");
  for (int n = 1; n <= number_of_products; ++n)
  {
    for (MultiLoop term(n); !term.finished(); term.next_loop())
      for(; term() < number_of_products; term.start_next_loop_at(0))
      {
        if (*term > 0 && term() <= term[*term - 1])
        {
          term.breaks(0);
          break;
        }
        if (term.inner_loop())
        {
          Expression original(products[term[0]]);
          bool need_simplify = false;
          for (int i = 1; i < n; ++i)
            need_simplify |= original.add(products[term[i]]);
          if (!need_simplify)
            Dout(dc::notice, "Does not need simplify: " << original);
          expressions.emplace_back(original.copy());
          truth_table = original;
          Dout(dc::notice, original << ": " << truth_table);
          m.emplace(truth_table, ++index);
          expressions.back().simplify();
          expressions.back().simplify();
          ASSERT(need_simplify || original == expressions.back());
          if (original != expressions.back())
          {
            Dout(dc::notice, "simplify(" << original << ") --> " << expressions.back());
            ASSERT(expressions.back().equivalent(original));
          }
          if (expressions.back() != expressions[m[truth_table]])
          {
            std::cout << ' ' << original << " --> " << expressions.back() << " should be " << expressions[m[truth_table]] << '\n';
          }
        }
      }
  }
}
