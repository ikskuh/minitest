# minitest
A minimal C++ testing framework in 100 LOC

## Example

Your tests in `tests.hpp`:
```cpp
TEST("this must succeed")
{
  assert(2 == 2);
  assert_eq(2, 2); // shortcut for "(a) == (b)"
}

TEST_FAIL("this must fail")
{
  assert_eq(2, 3);
}

TEST("this will fail")
{
  assert_eq(2, 3);
}

TEST_FAIL("this must fail as well")
{
  assert_eq(2, 2);
}
```

The output:
```
main.cpp:106  	this must succeed                       	SUCCESS
main.cpp:111  	this must fail                          	SUCCESS
main.cpp:116  	this will fail                          	FAILED (Assertion (2) == (3) failed!)
main.cpp:121  	this must fail as well                  	FAILED (Code did not throw!)
2/4 tests successful
```

## Usage
Just copy `test-runner.cpp` and `tests.hpp` into your project and include your tests in `tests.hpp`.
The system will automatically collect all `TEST` and `TEST_FAIL` blocks and will execute them after run.

### Compiling

Just compile the test file to your requirements and run the executable:
```sh
g++ -o test-runner test-runner.cpp && ./test-runner
```

## Notes
The output will right now emit colored text via ANSI escape codes. If you want to use this code on Windows,
adjust the code in test-runner.cpp


