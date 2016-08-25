#include <gtest/gtest.h>

struct MyClass
{
    int arg1 = 0;
    int arg2 = 0;
};

bool operator==(const MyClass& obj1, const MyClass& obj2)
{
    return obj1.arg1 == obj2.arg1 && obj1.arg2 == obj2.arg2;
}

std::ostream& operator<<(std::ostream& os, const MyClass& obj)
{
    // whatever needed to print bar to os
    return os << "{" << obj.arg1 << ", " << obj.arg2 << "}";
}

// if operator << is olready used for other purpouse you can override
// it behavior by implementing PrintTo method
void PrintTo(const MyClass& obj, std::ostream* os)
{
    *os << "[*" << obj.arg1 << ", " << obj.arg2 << "*]";  // whatever needed to print bar to os
}

TEST(ExtendPrinterTests, PrintMyClass)
{
    MyClass obj1{1, 2};
    MyClass obj2{2, 2};

    EXPECT_EQ(obj1, obj2);
}
