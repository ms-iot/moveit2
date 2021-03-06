set(MOVEIT_LIB_NAME moveit_planning_scene_monitor)

add_library(${MOVEIT_LIB_NAME} SHARED
  src/planning_scene_monitor.cpp
  src/current_state_monitor.cpp
  src/trajectory_monitor.cpp
)
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${MOVEIT_LIB_NAME}
  PRIVATE "PLANNING_SCENE_MONITOR_BUILDING_LIBRARY")

ament_target_dependencies(${MOVEIT_LIB_NAME}
  moveit_ros_occupancy_map_monitor
  message_filters
  urdf
  pluginlib
  rclcpp
  Boost
  moveit_msgs
)
target_link_libraries(${MOVEIT_LIB_NAME}
  moveit_robot_model_loader
  moveit_collision_plugin_loader
)

add_executable(demo_scene demos/demo_scene.cpp)
ament_target_dependencies(demo_scene
  rclcpp
  Boost
  moveit_msgs
  urdf
  message_filters
  pluginlib
)
target_link_libraries(demo_scene ${MOVEIT_LIB_NAME})

install(TARGETS demo_scene
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/ DESTINATION include)
