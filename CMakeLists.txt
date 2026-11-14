cmake_minimum_required(VERSION 3.10)
project(SDK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)


if(NOT DEFINED ENV{WORKSDK})
    message(FATAL_ERROR "Environment variable WORKSDK is not set.")
endif()


set(BOOST_VERSION "1.80.0")
set(BOOST_ROOT "$ENV{WORKSDK}/boost_1_80_0")
file(TO_CMAKE_PATH "${BOOST_ROOT}" BOOST_ROOT)


set(BOOST_COMPONENTS)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost ${BOOST_VERSION} EXACT CONFIG QUIET
    COMPONENTS ${BOOST_COMPONENTS}
    HINTS
        "${BOOST_ROOT}/stage"
        "${BOOST_ROOT}"
    NO_DEFAULT_PATH
)

if(Boost_FOUND)
    message(STATUS "Boost ${Boost_VERSION} found: ${Boost_DIR}")
elseif(NOT BOOST_COMPONENTS AND EXISTS "${BOOST_ROOT}/boost/version.hpp")
    message(STATUS "Boost compiled libraries not found, header-only mode: ${BOOST_ROOT}")
    add_library(Boost::headers INTERFACE IMPORTED)
    target_include_directories(Boost::headers INTERFACE "${BOOST_ROOT}")
else()
    message(FATAL_ERROR "Boost ${BOOST_VERSION} not found in ${BOOST_ROOT}.")
endif()

add_executable(SDK src/main.cpp)

target_link_libraries(SDK
    PRIVATE
        Boost::headers
)