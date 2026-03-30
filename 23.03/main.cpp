#include "vector-top-it.hpp"
#include <iostream>
#include <iomanip>

using topit::Vector;

bool test1()
{
  Vector< int > v;
  return v.isEmpty();
}

bool test2()
{
  Vector< int > v;
  return v.getSize() == 0;
}

bool test3()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  return v.getSize() == size;
}

bool test4()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try {
    int &value = v.at(0);
    return value == 1;
  } catch(...) {
    return false;
  }
}

bool test5()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  try {
    v.at(size + 1);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch(...) {
    return false;
  }
}

bool test6()
{
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 1);
  try {
    const int &value = v.at(0);
    return value == 1;
  } catch(...) {
    return false;
  }
}

bool test7()
{
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 0);
  try {
    v.at(size + 1);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch(...) {
    return false;
  }
}

bool test8()
{
  const Vector< int > v1(3, 0);
  const Vector< int > v2(3, 0);
  return v1 == v2;
}

bool test9()
{
  const Vector< int > v1(3, 0);
  const Vector< int > v2(3, 1);
  return v1 != v2;
}

bool test10()
{
  constexpr size_t size = 5;
  const Vector< int > v(size, 0);
  return v.getCapacity() == size;
}

bool test11()
{
  constexpr size_t size = 3;
  Vector< int > v(size, 0);
  const int newValue = 10;
  v.pushBack(newValue);
  return v.getSize() == (size + 1);
}

bool test12()
{
  constexpr size_t size = 3;
  Vector< int > v(size, 0);
  const int newValue = 10;
  v.pushBack(newValue);
  return v[size + 1] == newValue;
}

bool test13()
{
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);
  
  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);

  v.swap(yav);

  return cpy_v == yav && cpy_yav == v;
}

int main()
{
  using test_t = bool(*)();
  using case_t = std::pair< test_t, const char* >;
  case_t tests[] = {
    { test1, "Default constructed vector must is empty" },
    { test2, "Default constructed vector size is zero" },
    { test3, "Vector constructed with size has non-zero size" },
    { test4, "In-range access does not generate exceptions" },
    { test5, "Out-of-range access generates std::out_of_range exception" },
    { test6, "In-range access for const vector: same as non-const" },
    { test7, "Out-of-range access for const vector: same as non-const" },
    { test8, "Vectors with equal content are equal" },
    { test9, "Vectors with inequal content are inequal" },
    { test10, "Capacity of vector is correct"},
    { test11, "Size of vector increased after adding value" },
    { test12, "Added value is correct" },
    { test13, "Swap works correctly" }
  };

  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  bool result = true;
  size_t successes = 0, fails = 0;
  for (size_t i = 0; i < count; i++) {
    bool case_result = tests[i].first();
    successes += case_result;
    fails += !case_result;
    result = result && case_result;
    std::cout << case_result;
    std::cout << ": ";
    std::cout << tests[i].second << "\n";
  }

  std::cout << "SUMMARY\n";
  std::cout << result << ": TEST RESULTS\n";
  std::cout << fails << ": failed tests\n";
  std::cout << successes << ": passed tests\n";
}