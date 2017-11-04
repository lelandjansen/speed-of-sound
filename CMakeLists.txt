cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(speed-of-sound)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(clang_tidy_line_filters "[{'name': 'external/*'}]")
set(base_clang_tidy "clang-tidy-5.0;-line-filter=${clang_tidy_line_filters}")
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
  message("DEBUG mode")
  set(build_type_flags "-g -Og --coverage")
  set(CMAKE_CXX_CLANG_TIDY "${base_clang_tidy}")
else()
  message("RELEASE mode")
  set(build_type_flags "-O3 -Werror")
  set(CMAKE_CXX_CLANG_TIDY "${base_clang_tidy};-warnings-as-errors=*")
endif()

set(CMAKE_CXX_FLAGS
  "${build_type_flags}")
include_directories(
  ${PROJECT_SOURCE_DIR}/src)
add_library(
  speed_of_sound
  src/environment.cc
  src/speed-of-sound.cc
  src/speed-of-sound-theory.cc)

# Unit tests
set(GOOGLETEST_ROOT external/googletest/googletest)
include_directories(
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include)
set(GOOGLETEST_SOURCES
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc)
foreach(_source ${GOOGLETEST_SOURCES})
  set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()
add_library(googletest ${GOOGLETEST_SOURCES})
add_executable(
  unit_tests
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
