#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::Return;
using testing::NiceMock;
using testing::StrictMock;

#include <string>
using std::string;

class Foo
{
public:
    virtual ~Foo() = default;

    virtual int GetSize() const = 0;
    virtual string Describe(const char* name) = 0;
    virtual string Describe(int type) = 0;
};

class MockFoo : public Foo
{
public:
    MOCK_CONST_METHOD0(GetSize, int());
    MOCK_METHOD1(Describe, string(const char* name));
    MOCK_METHOD1(Describe, string(int type));
};

void productionCode(Foo& foo, int inputValue)
{
    auto size = foo.GetSize();
    for (int i = 0; i < size; ++i)
    {
        std::cout << "[          ] mock.Describe(" << inputValue << ") returns " << foo.Describe(inputValue) << std::endl;
    }
}

TEST(AbstractClassMock, NiceMockTest)
{
    NiceMock<MockFoo> foo;

    // set default function return value
    ON_CALL(foo, GetSize())
            .WillByDefault(Return(2));

    productionCode(foo, 5);
}

TEST(AbstractClassMock, StrictMockTest)
{
    StrictMock<MockFoo> foo;

    // without specifying expectations test fails
    EXPECT_CALL(foo, GetSize())
            .WillOnce(Return(4));
    EXPECT_CALL(foo, Describe(8))
            .Times(4)
            .WillRepeatedly(Return("Category 8"));

    productionCode(foo, 8);
}
