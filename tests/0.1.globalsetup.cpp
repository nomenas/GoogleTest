#include <gtest/gtest.h>

struct GlobalFixture : public testing::Environment
{
    // Override this to define how to set up the environment.
    void SetUp() override
    {
        std::cout << "[----------] Global::SetUp" << std::endl;

        // FAIL() << "in case of failure assert in global setup function no test is executed at all";
    }

    // Override this to define how to tear down the environment.
    void TearDown() override
    {
        std::cout << "[----------] Global::TearDown" << std::endl;
    }
};

static auto const GlobalFixtureObj = ::testing::AddGlobalTestEnvironment(new GlobalFixture);
