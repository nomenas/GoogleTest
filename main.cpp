#include <gtest/gtest.h>

// https://github.com/google/googletest/blob/master/googletest/docs/Primer.md

// Usefull switches
// -h -? /? --help          - show help
// --gtest_list_tests       - list all tests
// --gtest_filter           - select which tests should be executed using regex

// User may filter which tests/test cases will be executed by specifying --gtest_filter=. For example used:
//    --gtest_filter=SimpleTestCase.* in order to execute all test methods from this SimpleTestCase suite
//    --gtest_filter=SimpleTestCase.SimpleTestMethod1 in order to execute just specified test case

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
