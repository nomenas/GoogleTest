#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::Return;
using testing::NiceMock;

template <typename Elem>
class Stack
{
public:
    MOCK_CONST_METHOD0_T(GetSize, int());
    MOCK_METHOD1_T(Push, void(const Elem& x));
};

TEST(TemplateClassMock, SimpleTest)
{
    NiceMock<Stack<int> > stack;

    // set default function call;
    ON_CALL(stack, GetSize())
            .WillByDefault(Return(2));

    // set expect and check just push
    EXPECT_CALL(stack, Push(5));

    ASSERT_EQ(2, stack.GetSize());
    stack.Push(5);
}

template <typename T>
class List
{
public:
    int GetSize() const {return 0;}
    void Push(const T& elem) {}
};

template<>
class List<int>
{
public:
    MOCK_CONST_METHOD0(GetSize, int());
    MOCK_METHOD1(Push, void(const int& x));
};

TEST(TemplateClassMock, ParametrizedTemplateTest)
{
    List<int> list;

    // set expect and check just push
    EXPECT_CALL(list, GetSize()).WillOnce(Return(1));
    EXPECT_CALL(list, Push(5));

    ASSERT_EQ(1, list.GetSize());
    list.Push(5);
}
