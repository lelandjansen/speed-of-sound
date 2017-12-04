cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(speed-of-sound)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(clang_tidy_executable NAMES
  clang-tidy
  clang-tidy-5.0)
set(clang_tidy_line_filters "[{'name': 'external/*'}]")
set(base_clang_tidy
  "${clang_tidy_executable};-line-filter=${clang_tidy_line_filters}")

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
  message("DEBUG mode")
  set(build_type_flags "-g -Og --coverage -fno-exceptions")
  set(CMAKE_CXX_CLANG_TIDY "${base_clang_tidy}")
else()
  message("RELEASE mode")
  set(build_type_flags "-O3 -Werror -fno-exceptions")
  set(CMAKE_CXX_CLANG_TIDY "${base_clang_tidy};-warnings-as-errors=*")
endif()


set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} ${build_type_flags}")
include_directories(
  ${PROJECT_SOURCE_DIR}/src)
add_library(
  speed_of_sound
  src/environment.cc
  src/speed-of-sound.cc
  src/speed-of-sound-theory.cc)

if(BUILD_TESTS)
  set(googletest_root external/googletest/googletest)
  include_directories(
    ${PROJECT_SOURCE_DIR}/${googletest_root}
    ${PROJECT_SOURCE_DIR}/${googletest_root}/include)
  set(googletest_sources
    ${PROJECT_SOURCE_DIR}/${googletest_root}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${googletest_root}/src/gtest_main.cc)
  foreach(_source ${googletest_sources})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
  endforeach()
  add_library(googletest ${googletest_sources})
  add_executable(unit_tests
    test/test.cc
    test/speed-of-sound_test.cc
    test/speed-of-sound-theory_test.cc)
  add_dependencies(unit_tests googletest)
  target_link_libraries(
    unit_tests
    googletest
    speed_of_sound
    pthread)

  include(CTest)
  enable_testing()
  add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)
endif()
