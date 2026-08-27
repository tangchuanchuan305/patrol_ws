cmake_minimum_required(VERSION 3.8)
project(patrol_manager)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_srvs REQUIRED)



add_executable(velocity_publisher src/velocity_publisher.cpp)
add_executable(odom_monitor src/odom_monitor.cpp)

target_compile_features(
  odom_monitor PUBLIC cxx_std_17
)

ament_target_dependencies(
  odom_monitor
  rclcpp
  nav_msgs
  std_srvs
)


target_include_directories(velocity_publisher PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(velocity_publisher PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  velocity_publisher
  "rclcpp"
  "geometry_msgs"
)

install(
  TARGETS
    velocity_publisher
    odom_monitor
  DESTINATION lib/${PROJECT_NAME}
)




if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
