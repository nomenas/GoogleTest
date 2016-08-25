#include <gtest/gtest.h>

template <typename T>
struct Default
{
    static const T Value;
};

template <>
const int Default<int>::Value = 0;
template <>
const char Default<char>::Value = 0;
template <>
const unsigned int Default<unsigned int>::Value = 0;
template <>
const double Default<double>::Value = 0;

template <typename T>
class TypedTestFixture : public ::testing::Test {
public:
    T value;

    void SetUp() override
    {
        value = Default<T>::Value;
        ++value;
    }
};

typedef ::testing::Types<char, int, unsigned int, double> MyTypes;
TYPED_TEST_CASE(TypedTestFixture, MyTypes);

TYPED_TEST(TypedTestFixture, test1)
{
    // To visit static members of the fixture, add the 'TestFixture::' prefix.
    ASSERT_EQ(TestFixture::value, 1);
}
