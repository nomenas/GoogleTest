#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

#include <string>
#include <map>

// use ASSERT_THAT for fatal failures

struct UsingMatchersMock
{
    MOCK_CONST_METHOD1(testMethod, std::string(int type));
};

TEST(MatchersTests, UsingMatchers)
{
    UsingMatchersMock foo;
    EXPECT_CALL(foo, testMethod(Eq(5))).WillOnce(Return("0"));
    EXPECT_CALL(foo, testMethod(Gt(5))).WillOnce(Return("1"));
    EXPECT_CALL(foo, testMethod(Lt(5))).WillOnce(Return("-1"));

    EXPECT_EQ("-1", foo.testMethod(4));
    EXPECT_EQ("0", foo.testMethod(5));
    EXPECT_EQ("1", foo.testMethod(6));
}

TEST(MatchersTests, GenericComparison)
{
    // value checkers
    EXPECT_THAT(1, Eq(1));
    EXPECT_THAT(2, Ge(1));
    EXPECT_THAT(1, Le(1));
    EXPECT_THAT(1, Lt(2));
    EXPECT_THAT(2, Gt(1));
    EXPECT_THAT(2, Ne(1));
    EXPECT_THAT(nullptr, IsNull());
    int value;
    EXPECT_THAT(&value, NotNull());
}

TEST(MatchersTests, DataTypeMatchers)
{
    int value;;
    const int& ref = value;

    // type checkers
    EXPECT_THAT(ref, Ref(value));
    EXPECT_THAT(value, A<int>());
    EXPECT_THAT(value, An<int>());
}

TEST(MatchersTests, FloatingPointComparison)
{
    EXPECT_THAT(1.0, DoubleEq(1.0));
    EXPECT_THAT((float) 1.0, FloatEq(1.0));
    EXPECT_THAT(1.0, NanSensitiveDoubleEq(1.0));
    EXPECT_THAT((float) 1.0, NanSensitiveFloatEq(1.0));
    EXPECT_THAT(1.0, NanSensitiveDoubleEq(1.0));
    EXPECT_THAT(1.0, DoubleNear(1.0, 0.1));
    EXPECT_THAT((float) 1.0, FloatNear(1.0, 0.1));
    EXPECT_THAT(1.0, NanSensitiveDoubleNear(1.0, 0.1));
    EXPECT_THAT((float) 1.0, NanSensitiveFloatNear(1.0, 0.1));
}

TEST(MatchersTests, StringMatchers)
{
    EXPECT_THAT("test", ContainsRegex("^te"));
    EXPECT_THAT("test", EndsWith("st"));
    EXPECT_THAT("test", HasSubstr("es"));
    EXPECT_THAT("test", HasSubstr("es"));
    EXPECT_THAT("test", MatchesRegex("^test"));
    EXPECT_THAT("test", StartsWith("test"));
    EXPECT_THAT("test", StrCaseEq("TEST"));
    EXPECT_THAT("test", StrCaseNe("TEST1"));
    EXPECT_THAT("test", StrEq("test"));
    EXPECT_THAT("test", StrNe("TEST"));
}

TEST(MatchersTests, ContainerMatchers)
{
    std::vector<int> test = {1, 2, 5, 6, 3, 4};
    EXPECT_THAT(test, ContainerEq(std::vector<int>{1, 2, 5, 6, 3, 4}));
    EXPECT_THAT(test, ElementsAreArray({1, 2, 5, 6, 3, 4}));
    EXPECT_THAT(test, Contains(3));
    EXPECT_THAT(test, SizeIs(6));
    EXPECT_THAT(std::vector<int>{}, IsEmpty());
    EXPECT_THAT(test, Pointwise(Le(), std::vector<int>{1, 2, 5, 6, 3, 4}));
    EXPECT_THAT(test, UnorderedElementsAreArray({1, 2, 3, 4, 5, 6}));
    EXPECT_THAT(test, WhenSortedBy(std::greater<int>(), ElementsAre(6, 5, 4, 3, 2, 1)));
}

struct MemberMatchersStruct
{
    int method() const
    {
        return 5;
    }

    int value;
};

TEST(MatchersTests, MemberMatchers)
{
    MemberMatchersStruct test{3};
    EXPECT_THAT(test, Field(&MemberMatchersStruct::value, 3));
    EXPECT_THAT(&test, Field(&MemberMatchersStruct::value, 3));

    EXPECT_THAT(test, Property(&MemberMatchersStruct::method, 5));
    EXPECT_THAT(&test, Property(&MemberMatchersStruct::method, 5));

    std::map<int, int> testMap = {{1, 4}};
    EXPECT_THAT(testMap, Contains(Key(Le(5))));

    std::pair<int, int> testPair{1, 4};
    EXPECT_THAT(testPair, Pair(Le(1), Gt(3)));
}

class Base
{
public:
    virtual ~Base() = default;
};
class Derived : public Base {};

TEST(MatchersTests, PointerMatchers)
{
    int value = 5;
    EXPECT_THAT(&value, Pointee(5));

    Derived derived;
    EXPECT_THAT((Base*) &derived, WhenDynamicCastTo<Derived*>(NotNull()));
}

TEST(MatchersTests, CompositeMatchers)
{
    EXPECT_THAT(5, AllOf(Le(6), Gt(4), A<int>()));
    EXPECT_THAT(5, AnyOf(Le(1), Gt(10), A<int>()));
    EXPECT_THAT(5, Not(Le(1)));
}

MATCHER(IsEven, "") { return (arg % 2) == 0; }
MATCHER_P(IsDivisibleBy, n, "") { *result_listener << "where the remainder is " << (arg % n); return (arg % n) == 0; }
MATCHER_P2(IsBetween, a, b, std::string(negation ? "isn't" : "is") + " between " + PrintToString(a) + " and " + PrintToString(b)) { return a <= arg && arg <= b; }
TEST(MatchersTests, CustomMatchers)
{
    EXPECT_THAT(2, IsEven());
    EXPECT_THAT(6, IsDivisibleBy(3));
    EXPECT_THAT(6, IsBetween(3, 9));
}
