project(googletest)
cmake_minimum_required(VERSION 3.1)
find_package(GTEST REQUIRED)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SRC_LIST src/*.cpp tests/*.cpp main.cpp)
file(GLOB HEADER_LIST src/*.h tests/*.h)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
