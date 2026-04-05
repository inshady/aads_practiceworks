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
  return v.getSize() == (size + 1) && v[size] == newValue;
}

bool test12()
{
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);

  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);

  v.swap(yav);

  return cpy_v == yav && cpy_yav == v;
}

bool test13()
{
  Vector< int > v(2, 0);
  Vector< int > cpy_v(v);

  Vector< int > yav = std::move(v);

  return yav == cpy_v;
}

bool test14()
{
  Vector< int > v(2, 0);
  Vector< int > cpy(v);
  Vector< int > yav;

  yav = std::move(v);

  return yav == cpy;
}

bool test15()
{
  constexpr size_t size = 3;
  Vector< int > v(size, 0);
  int val = 10;
  v.pushFront(val);
  return v[0] == val && v.getSize() == size + 1;
}

bool test16()
{
  constexpr size_t size = 3;
  Vector< int > v(size, 0);
  int val = 10;

  v.insert(2, val);

  return v[2] == val && v.getSize() == size + 1;
}

bool test17()
{
  constexpr size_t size = 3;
  Vector< int > v(size, 0);
  Vector< int > v2(5, 1);

  v.insert(3, v2, 2, 3);

  return v[3] == 1 && v[4] == 1 && v.getSize() == size + 1;
}

bool test18()
{
  constexpr size_t size = 3;
  Vector< int > v(size, 0);
  v.erase(1);
  return v.getSize() == size - 1;
}

bool test19()
{
  Vector< int > v(3, 0);
  auto it = v.begin();

  return *it == 0;
}

bool test20()
{
  Vector< int > v(3, 0);
  auto it = v.begin();
  ++it;
  return it.getPos() == 1;
}

bool test21()
{
  Vector< int > v(3, 0);
  auto it = v.end();
  --it;
  return it.getPos() == 2;
}

bool test22()
{
  Vector< int > v(5, 0);
  auto it = v.begin();
  it = it + 3;
  return it.getPos() == 3;
}

bool test23()
{
  Vector< int > v(5, 0);
  auto it = v.end();
  it = it - 2;
  return it.getPos() == 3;
}

bool test24()
{
  Vector< int > v(5, 0);
  auto it = v.begin();
  auto it2 = v.end() - 5;
  return it == it2;
}

bool test25()
{
  Vector< int > v(5, 0);
  auto it = v.begin();
  auto it2 = v.end() - 4;
  return it != it2;
}

bool test26()
{
  constexpr size_t size = 5;
  Vector< int > v(size, 0);
  auto it = v.begin() + 1;
  v.insert(it, 10);
  return v[1] == 10 && v.getSize() == size + 1;
}

bool test27()
{
  constexpr size_t size = 5;
  Vector< int > v(size, 0);
  auto it = v.begin() + 1;
  Vector< int > v2(3, 1);
  v.insert(it, v2);
  return v[1] == 1 && v[2] == 1 && v[3] == 1 && v.getSize() == size + 3;
}

bool test28()
{
  constexpr size_t size = 5;
  Vector< int > v(size, 0);
  auto it = v.begin() + 1;
  Vector< int > v2(3, 1);
  v.insert(it, v2, v2.begin(), v2.end());
  return v[1] == 1 && v[2] == 1 && v[3] == 1 && v.getSize() == size + 3;
}

bool test29()
{
  constexpr size_t size = 5;
  Vector< int > v(size, 0);
  auto it = v.begin() + 1;
  v.erase(it);
  return v.getSize() == size - 1;
}

bool test30()
{
  constexpr size_t size = 5;
  Vector< int > v(size, 0);
  auto it = v.begin() + 1;
  auto it2 = v.begin() + 4;
  v.erase(it, it2);
  return v.getSize() == size - 3;
}

bool test31()
{
  constexpr size_t size = 5;
  Vector< int > v(size, 0);
  auto it = v.begin() + 1;
  v.erase(it, 3);
  return v.getSize() == size - 3;
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
    { test11, "Push back works correctly" },
    { test12, "Swap works correctly" },
    { test13, "Move constructor" },
    { test14, "Move-assignment" },
    { test15, "Push front" },
    { test16, "Insert by position" },
    { test17, "Insert by range" },
    { test18, "Erase by position" },
    { test19, "Begin iterator" },
    { test20, "Iterator increment" },
    { test21, "Iterator decrement" },
    { test22, "Iterator addition" },
    { test23, "Iterator subtraction" },
    { test24, "Iterator equality" },
    { test25, "Iterator inequality" },
    { test26, "Insert by iterator" },
    { test27, "Insert vector by iterator" },
    { test28, "Insert range by iterator" },
    { test29, "Erase by iterator" },
    { test30, "Erase range by iterator" },
    { test31, "Erase range by iterator and count" },
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
