cmake_minimum_required(VERSION 3.10)
project(Serialization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

if(NOT DEFINED ENV{WORKSDK})
    message(FATAL_ERROR "Environment variable WORKSDK is not set.")
endif()

set(BOOST_ROOT "$ENV{WORKSDK}/boost_1_80_0")
file(TO_CMAKE_PATH "${BOOST_ROOT}" BOOST_ROOT)
set(BOOST_LIB_DIR "${BOOST_ROOT}/stage/lib")

if(NOT EXISTS "${BOOST_ROOT}/boost/version.hpp")
    message(FATAL_ERROR "Boost headers not found in ${BOOST_ROOT}.")
endif()

add_compile_definitions(BOOST_ALL_NO_LIB)

set(SER_DBG_LIB "${BOOST_LIB_DIR}/libboost_serialization-vc143-mt-gd-1_80.lib")
set(SER_REL_LIB "${BOOST_LIB_DIR}/libboost_serialization-vc143-mt-1_80.lib")
set(WSER_DBG_LIB "${BOOST_LIB_DIR}/libboost_wserialization-vc143-mt-gd-1_80.lib")
set(WSER_REL_LIB "${BOOST_LIB_DIR}/libboost_wserialization-vc143-mt-1_80.lib")
set(UTF_DBG_LIB "${BOOST_LIB_DIR}/libboost_unit_test_framework-vc145-mt-gd-x64-1_80.lib")
set(UTF_REL_LIB "${BOOST_LIB_DIR}/libboost_unit_test_framework-vc145-mt-x64-1_80.lib")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${BOOST_ROOT}"
)

add_library(SerializationCore STATIC
    src/HttpServerSettings.cpp
)
target_link_libraries(SerializationCore PUBLIC
    $<$<CONFIG:Debug>:${SER_DBG_LIB}>
    $<$<NOT:$<CONFIG:Debug>>:${SER_REL_LIB}>
    $<$<CONFIG:Debug>:${WSER_DBG_LIB}>
    $<$<NOT:$<CONFIG:Debug>>:${WSER_REL_LIB}>
)

add_executable(SerializationUTRunner
    test/main.cpp
    test/HttpServerSettingsTest.cpp
)
target_link_libraries(SerializationUTRunner PRIVATE
    SerializationCore
    $<$<CONFIG:Debug>:${UTF_DBG_LIB}>
    $<$<NOT:$<CONFIG:Debug>>:${UTF_REL_LIB}>
)
add_test(NAME SerializationUnitTests COMMAND SerializationUTRunner)

add_executable(SerializationDemo
    demo/main.cpp
)
target_link_libraries(SerializationDemo PRIVATE
    SerializationCore
)