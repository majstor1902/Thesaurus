include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(
    ThesaurusUnitTests
    ThesaurusTests.cpp
    )

target_link_libraries(ThesaurusUnitTests
  PRIVATE
    ThesaurusLib
    gtest_main
    gmock
  )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(ThesaurusUnitTests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )
