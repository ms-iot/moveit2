set(MOVEIT_LIB_NAME moveit_collision_detection_fcl)

add_library(${MOVEIT_LIB_NAME} SHARED
  src/collision_common.cpp
  src/collision_env_fcl.cpp
)
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
ament_target_dependencies(${MOVEIT_LIB_NAME}
  rclcpp
  rmw_implementation
  urdf
  urdfdom
  urdfdom_headers
  LIBFCL
  LIBCCD
  Boost
  visualization_msgs
)
target_link_libraries(${MOVEIT_LIB_NAME}
  moveit_collision_detection
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${MOVEIT_LIB_NAME}
  PRIVATE "COLLISION_DETECTION_FCL_BUILDING_LIBRARY")

add_library(collision_detector_fcl_plugin SHARED src/collision_detector_fcl_plugin_loader.cpp)
set_target_properties(collision_detector_fcl_plugin PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(collision_detector_fcl_plugin PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(collision_detector_fcl_plugin
  PRIVATE "COLLISION_DETECTION_FCL_PLUGIN_BUILDING_LIBRARY")


ament_target_dependencies(collision_detector_fcl_plugin
  rclcpp
  urdf
  visualization_msgs
  pluginlib
  rmw_implementation
)
target_link_libraries(collision_detector_fcl_plugin
  ${MOVEIT_LIB_NAME}
  moveit_planning_scene
)

install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  if(WIN32)
    # set(append_library_dirs "$<TARGET_FILE_DIR:${PROJECT_NAME}>;$<TARGET_FILE_DIR:${PROJECT_NAME}_TestPlugins1>")
  else()
    set(append_library_dirs "${CMAKE_CURRENT_BINARY_DIR};${CMAKE_CURRENT_BINARY_DIR}/../collision_detection;${CMAKE_CURRENT_BINARY_DIR}/../robot_state;${CMAKE_CURRENT_BINARY_DIR}/../robot_model;${CMAKE_CURRENT_BINARY_DIR}/../utils")
  endif()

  ament_add_gtest(test_fcl_collision_env test/test_fcl_env.cpp)
  target_link_libraries(test_fcl_collision_env moveit_test_utils ${MOVEIT_LIB_NAME})

  ament_add_gtest(test_fcl_collision_detection test/test_fcl_collision_detection_pr2.cpp)
  target_link_libraries(test_fcl_collision_detection moveit_test_utils ${MOVEIT_LIB_NAME})
  if (NOT WIN32)  
    # TODO: remove if transition to gtest's new API TYPED_TEST_SUITE_P is finished
    target_compile_options(test_fcl_collision_detection PRIVATE -Wno-deprecated-declarations)
  endif()

  ament_add_gtest(test_fcl_collision_detection_panda test/test_fcl_collision_detection_panda.cpp)
  target_link_libraries(test_fcl_collision_detection_panda moveit_test_utils ${MOVEIT_LIB_NAME})

  if (NOT WIN32)  
    # TODO: remove if transition to gtest's new API TYPED_TEST_SUITE_P is finished
    target_compile_options(test_fcl_collision_detection PRIVATE -Wno-deprecated-declarations)
  endif()
endif()
