cmake_minimum_required(VERSION 2.8.3)
project(fuzzy-yaml)

add_compile_options(-std=c++17)

find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)

add_subdirectory(fuzzy)

set(COMMON_LINK_LIBRARIES 
  ${YAML_CPP_LIBRARIES}
  fuzzy_lib
)

set(COMMON_INCLUDE_DIRECTORIES
  ${PROJECT_BINARY_DIR}
  ${YAML_CPP_INCLUDE_DIR}
)

add_subdirectory(examples)
