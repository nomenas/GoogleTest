#include <gtest/gtest.h>

TEST(LoggingTests, TestLoggingCapabilitiesInXML) {
    RecordProperty("log integer", 0);
    RecordProperty("log string", "test");
}

TEST(LoggingTests, TestLoggingCapabilitiesInConsole) {
    std::cout << "[          ] log integer = " << 0 << std::endl;
    std::cout << "[          ] log string  = " << "string" << std::endl;
}
