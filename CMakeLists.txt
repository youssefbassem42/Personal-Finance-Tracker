cmake_minimum_required(VERSION 3.10)
project(PersonalFinanceTracker)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find PostgreSQL and libpqxx
find_package(PostgreSQL REQUIRED)

# Try to find libpqxx using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${PostgreSQL_INCLUDE_DIRS}
    ${LIBPQXX_INCLUDE_DIRS}
)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Create executable
add_executable(finance_tracker ${SOURCES})

# Link libraries
target_link_libraries(finance_tracker
    ${PostgreSQL_LIBRARIES}
    ${LIBPQXX_LIBRARIES}
)

# Print configuration info
message(STATUS "PostgreSQL version: ${PostgreSQL_VERSION}")
message(STATUS "PostgreSQL include dir: ${PostgreSQL_INCLUDE_DIRS}")
message(STATUS "PostgreSQL libraries: ${PostgreSQL_LIBRARIES}")
message(STATUS "libpqxx include dirs: ${LIBPQXX_INCLUDE_DIRS}")
message(STATUS "libpqxx libraries: ${LIBPQXX_LIBRARIES}")
