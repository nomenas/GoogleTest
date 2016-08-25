#include <gtest/gtest.h>
#include <signal.h>

void Foo(int* value)
{
    *value = 0;
}

void NormalExit()
{
    exit(0);
}

void KillMyself()
{
    raise(SIGTERM);
}

TEST(MyDeathTest, Foo) {
  // This death test uses a compound statement.
  ASSERT_DEATH({ int n = 5; Foo(&n); }, "Error on line .* of Foo()");
}
TEST(MyDeathTest, NormalExit) {
  EXPECT_EXIT(NormalExit(), ::testing::ExitedWithCode(0), "Success");
}
TEST(MyDeathTest, KillMyself) {
  EXPECT_EXIT(KillMyself(), ::testing::KilledBySignal(SIGKILL), "Sending myself unblockable signal");
}
