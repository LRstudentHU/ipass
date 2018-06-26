cmake_minimum_required(VERSION 3.10)
project(ipass)

set(CMAKE_CXX_STANDARD 17)
add_executable(main demo/main.cpp demo/mpu6050.cpp demo/mpu6050.hpp library/motion_sensor.hpp library/vector3.hpp library/motion_sensor.cpp library/motion_rule.hpp library/motion_rule.cpp)
add_executable(main_test library/motion_sensor.hpp library/vector3.hpp library/motion_sensor.cpp library/motion_rule.hpp library/motion_rule.cpp library/tests/main.test.cpp library/tests/mock_sensor.cpp library/tests/mock_sensor.hpp)

include_directories(C:/ti-software/hwlib/library)
target_include_directories(main_test PUBLIC C:/ti-software/Catch2/single_include)