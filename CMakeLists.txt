cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(speed-of-sound)

enable_language(C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

add_library(
  speed_of_sound
  src/speed_of_sound.cc
  src/speed_of_sound_theory.cc
)

set(GOOGLETEST_ROOT external/googletest/googletest)

include_directories(
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

set(GOOGLETEST_SOURCES
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
)

foreach(_source ${GOOGLETEST_SOURCES})
  set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})

add_executable(
  unit_tests
  test/test.cc
  test/speed_of_sound_test.cc
  test/speed_of_sound_theory_test.cc
)

add_dependencies(unit_tests googletest)

target_link_libraries(
  unit_tests
  googletest
  speed_of_sound
  pthread
)

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)
