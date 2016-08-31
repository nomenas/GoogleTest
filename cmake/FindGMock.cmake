find_path(GMOCK_INCLUDE_DIRS gmock/gmock.h
    HINTS
        $ENV{GTEST_ROOT}/include
        ${GTEST_ROOT}/include
)
mark_as_advanced(GMOCK_INCLUDE_DIRS)

find_library(GMOCK_LIBRARY
    NAMES gmock
    PATHS
        $ENV{GTEST_ROOT}/lib
        ${GTEST_ROOT}/lib
        /usr/local/lib
)


