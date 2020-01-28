#include <iostream>
#include <iomanip>

using TestRunner = void (*)();
struct Test
{
  Test * next;
  static Test * first;
  static Test * last;

  char const * file;
  int line;
  char const * name;
  TestRunner runner;
  bool expectException;

  explicit Test(char const * _file, int _line, char const * _name, TestRunner _runner, bool _expectException) :
      next(nullptr),
      file(_file),
      line(_line),
      name(_name),
      runner(_runner),
      expectException(_expectException)
  {
    if (first == nullptr)
      first = this;
    if (last != nullptr)
      last->next = this;
    last = this;
  }

  bool run()
  {
    std::cout << this->file << ":" << std::setw(5) << std::left << this->line << "\t" << std::setw(40) << std::left
              << this->name << "\t";
    try {
      this->runner();
      if (this->expectException) {
        std::cout << "\x1B[91mFAILED\x1B[0m (Code did not throw!)" << std::endl;
        return false;
      }
      else {
        std::cout << "\x1B[92mSUCCESS\x1B[0m" << std::endl;
        return true;
      }
    }
    catch (const std::exception & e) {
      if (this->expectException) {
        std::cout << "\x1B[92mSUCCESS\x1B[0m" << std::endl;
        return true;
      }
      else {
        std::cout << "\x1B[91mFAILED\x1B[0m (" << e.what() << ")" << std::endl;
        return false;
      }
    }
  }
};
Test * Test::first = nullptr;
Test * Test::last = nullptr;

#define GENNAME2(_Name, _Line) _Name##_Line
#define GENNAME(_Name, _Line) GENNAME2(_Name, _Line)

#define IMPL_TEST(_Name, _ExpectExcept)                                                                                \
  static void GENNAME(test_runner_, __LINE__)();                                                                       \
  static Test GENNAME(test_, __LINE__){                                                                                \
      __FILE__, __LINE__, _Name, &GENNAME(test_runner_, __LINE__), _ExpectExcept,                                      \
  };                                                                                                                   \
  static void GENNAME(test_runner_, __LINE__)()

#define TEST(_Name) IMPL_TEST(_Name, false)
#define TEST_FAIL(_Name) IMPL_TEST(_Name, true)

#undef assert
#define assert(_Cond)                                                                                                  \
  do {                                                                                                                 \
    if (not(_Cond))                                                                                                    \
      throw std::logic_error("Assertion " #_Cond " failed!");                                                          \
  } while (false)

#define assert_eq(_A, _B) assert((_A) == (_B))

int main()
{
  bool ok = true;
  unsigned int total = 0;
  unsigned int success = 0;
  for (auto * test = Test::first; test != nullptr; test = test->next) {
    auto const g = test->run();
    ok &= g;
    if (g)
      success += 1;
    total += 1;
  }

  std::cout << (ok ? "\x1B[92m" : "\x1B[91m") << success << "/" << total << " tests successful\x1B[0m" << std::endl;

  return ok ? 0 : 1;
}
#include "tests.hpp"

