cmake_minimum_required(VERSION 2.8.3)
project(fuzzy-yaml_examples)

add_executable(anklePitch anklePitch.cpp)
target_link_libraries(anklePitch PUBLIC
  ${COMMON_LINK_LIBRARIES}
)
target_include_directories(anklePitch PUBLIC
  ${COMMON_INCLUDE_DIRECTORIES}
)
