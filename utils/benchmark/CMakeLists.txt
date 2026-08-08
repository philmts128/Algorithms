add_library(benchmark stopwatch.hpp stopwatch.cpp)

target_include_directories(benchmark PUBLIC ${PROJECT_SOURCE_DIR}/utils)
