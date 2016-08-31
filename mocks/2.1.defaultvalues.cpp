#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::DefaultValue;
using testing::NiceMock;
using testing::Return;

unsigned UnsignedFactory()
{
    return 100;
}

struct DefaultValuesFixture : testing::Test
{
    void SetUp() override
    {
        DefaultValue<int>::Set(5);
        DefaultValue<unsigned>::SetFactory(UnsignedFactory);
    }

    void TearDown() override
    {
        DefaultValue<int>::Clear();
        DefaultValue<unsigned>::Clear();
    }
};

struct DefaultValuesFoo
{
    MOCK_CONST_METHOD0(intMethod, int());
    MOCK_CONST_METHOD0(unsignedMethod, unsigned());
    MOCK_CONST_METHOD0(intMethod1, int());
};

TEST_F(DefaultValuesFixture, TestDefaultValue)
{
    DefaultValuesFoo foo;
    EXPECT_CALL(foo, intMethod());

    ASSERT_EQ(5, foo.intMethod());
}

TEST_F(DefaultValuesFixture, TestDefaultFactory)
{
    NiceMock<DefaultValuesFoo> foo;
    ASSERT_EQ(100, foo.unsignedMethod());
}

TEST_F(DefaultValuesFixture, TestDefaultMethodCall)
{
    NiceMock<DefaultValuesFoo> foo;
    ON_CALL(foo, intMethod1()).WillByDefault(Return(2));
    ASSERT_EQ(2, foo.intMethod1());
}
