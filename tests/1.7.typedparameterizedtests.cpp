#include <gtest/gtest.h>

template <typename T>
struct TypeParameterizedTests : public ::testing::Test
{
};

TYPED_TEST_CASE_P(TypeParameterizedTests);

TYPED_TEST_P(TypeParameterizedTests, ParameterizedTest1)
{
    // Inside a test, refer to TypeParam to get the type parameter.
    TypeParam n = 0;
    std::vector<TypeParam> vector;
    vector.push_back(n);

    ASSERT_EQ(n, vector[0]);
}

TYPED_TEST_P(TypeParameterizedTests, ParameterizedTest2)
{
    // Inside a test, refer to TypeParam to get the type parameter.
    TypeParam n = 0;
    auto initializerList = {n};
    ASSERT_EQ(initializerList.size(), 1);
    ASSERT_EQ(*initializerList.begin(), 0);

}

// Register test methods
REGISTER_TYPED_TEST_CASE_P(TypeParameterizedTests, ParameterizedTest1, ParameterizedTest2);

// Instantie with list
typedef ::testing::Types<char, int, unsigned int, double> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(My1, TypeParameterizedTests, MyTypes);

// Instantiate with type
INSTANTIATE_TYPED_TEST_CASE_P(My2, TypeParameterizedTests, float);
