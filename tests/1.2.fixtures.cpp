#include "../src/cut.h"

#include <gtest/gtest.h>
#include <iostream>


struct Fixture : public testing::Test
{
    static int SharedData;
    static int Data;

    static void SetUpTestCase()
    {
        std::cout << "[          ] SetUpTestCase" << std::endl;
        ++SharedData;
    }

    void SetUp() override
    {
        const auto* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        std::cout << "[          ] SetUp " << test_info->test_case_name() << "." << test_info->name() << std::endl;
        ++Data;
    }

    void TearDown() override
    {
        std::cout << "[          ] TearDown" << std::endl;
        ++Data;
    }

    static void TearDownTestCase()
    {
        std::cout << "[          ] TearDownTestCase" << std::endl;
        ++SharedData;
    }
};

int Fixture::SharedData = 0;
int Fixture::Data = 0;

TEST_F(Fixture, test1)
{
    std::cout << "[          ] run test1" << std::endl;
    ASSERT_EQ(SharedData, 1);
    ASSERT_EQ(Data, 1);
}

TEST_F(Fixture, test2)
{
    std::cout << "[          ] run test2" << std::endl;
    ASSERT_EQ(SharedData, 1);
    ASSERT_EQ(Data, 3);
}

struct FixtureFailInSetUp : testing::Test
{
    void SetUp() override
    {
        FAIL() << "* no test should be executed in this case";
    }
};

TEST_F(FixtureFailInSetUp, test1)
{
    std::cout << "[          ] run test1" << std::endl;
}

TEST_F(FixtureFailInSetUp, test2)
{
    std::cout << "[          ] run test2" << std::endl;
}
