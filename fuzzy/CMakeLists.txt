find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)

# cpp files
set(FUZZY_SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/fuzzyManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mathUtils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/membership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/inputMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/inputMembershipFactory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/outputMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/outputMembershipFactory.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/trapezoidMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/trapezoidInputMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/trapezoidOutputMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/triangleMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/triangleInputMembership.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memberships/triangleOutputMembership.cpp
  # TODO: Add new memberships *.cpp here
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ruleBase/ruleBase.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ruleBase/ruleBaseFactory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ruleBase/ruleTable.cpp
  # TODO: Add new rule bases *.cpp here

  ${CMAKE_CURRENT_SOURCE_DIR}/src/defuzzifier/defuzzifier.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/defuzzifier/defuzzifierFactory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/defuzzifier/centroid.cpp
  # TODO: Add new defuzzifiers *.cpp here
)

add_library(fuzzy_lib ${FUZZY_SOURCE_FILES})

target_include_directories(fuzzy_lib PUBLIC
  ${YAML_CPP_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/memberships
  ${CMAKE_CURRENT_SOURCE_DIR}/include/defuzzifier
  ${CMAKE_CURRENT_SOURCE_DIR}/include/ruleBase
)

target_link_libraries(fuzzy_lib PUBLIC
  ${YAML_CPP_LIBRARIES}
  # Boost::headers Boost::system Boost::filesystem
)