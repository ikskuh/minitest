// PUT YOUR TESTS AND INCLUDES HERE!

TEST("this must succeed")
{
  assert_eq(2, 2);
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
