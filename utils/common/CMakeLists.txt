add_library(common INTERFACE definitions.hpp)

target_include_directories(common PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/utils)
