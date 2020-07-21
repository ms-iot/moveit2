cmake_minimum_required(VERSION 3.10.2)
project(moveit_planners_ompl)

# At least C++11 required for OMPL
if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(ASSIMP QUIET)
if(NOT ASSIMP_FOUND)
  find_package(PkgConfig REQUIRED)
  # assimp is required, so REQUIRE the second attempt
  pkg_check_modules(ASSIMP_PC REQUIRED assimp)
  set(ASSIMP_INCLUDE_DIRS ${ASSIMP_PC_INCLUDE_DIRS})
endif()

# find *absolute* paths to ASSIMP_LIBRARIES
# Both, pkg-config and assimp's cmake-config don't provide an absolute library path.
# For, pkg-config the path is in ASSIMP_PC_LIBRARY_DIRS, for cmake in ASSIMP_LIBRARY_DIRS.
find_library(ASSIMP_ABS_LIBRARIES NAMES ${ASSIMP_LIBRARIES} assimp HINTS ${ASSIMP_LIBRARY_DIRS} ${ASSIMP_PC_LIBRARY_DIRS})
set(ASSIMP_LIBRARIES "${ASSIMP_ABS_LIBRARIES}")

find_package(Boost REQUIRED system filesystem date_time thread serialization)
find_package(moveit_core REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pluginlib REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(ompl REQUIRED)

include_directories(ompl_interface/include)
include_directories(SYSTEM
                    ${Boost_INCLUDE_DIRS}
                    ${OMPL_INCLUDE_DIRS})

add_subdirectory(ompl_interface)

ament_export_include_directories(include)
ament_export_libraries(moveit_ompl_interface moveit_ompl_planner_plugin)
ament_export_dependencies(moveit_core ompl)

pluginlib_export_plugin_description_file(moveit_core ompl_interface_plugin_description.xml)

ament_package()
