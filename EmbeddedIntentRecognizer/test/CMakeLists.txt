include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(
    unit_tests
    test_csvrow.cpp
    test_csv.cpp
    test_input.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    intent
    gtest_main
  )
add_compile_definitions(TEST_PATH="${PROJECT_SOURCE_DIR}/test")
add_compile_definitions(DATA_PATH="${PROJECT_SOURCE_DIR}/data")
set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")



# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )
