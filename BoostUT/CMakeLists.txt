cmake_minimum_required(VERSION 3.10)
project(BoostUT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

if(NOT DEFINED ENV{WORKSDK})
    message(FATAL_ERROR "Environment variable WORKSDK is not set.")
endif()

set(BOOST_COMPONENTS
    unit_test_framework
)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.80.0 EXACT CONFIG QUIET
    COMPONENTS ${BOOST_COMPONENTS}
    HINTS
        "$ENV{WORKSDK}/boost_1_80_0/stage/lib/cmake/Boost-1.80.0"
        "$ENV{WORKSDK}/boost_1_80_0/stage"
        "$ENV{WORKSDK}/boost_1_80_0"
        "$ENV{WORKSDK}"
    NO_DEFAULT_PATH
)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost 1.80.0 with components (unit_test_framework) not found in WORKSDK ($ENV{WORKSDK}).")
endif()

add_library(BoostUT_Calendar STATIC
    include/Calendar.h
    src/Calendar.cpp
)

target_include_directories(BoostUT_Calendar
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(BoostUT_Calendar
    PUBLIC
        Boost::headers
)

add_executable(BoostUTRunner
    tests/testCalendar.cpp
)

target_link_libraries(BoostUTRunner
    PRIVATE
        BoostUT_Calendar
        Boost::unit_test_framework
)

add_test(NAME BoostUTTests COMMAND BoostUTRunner)