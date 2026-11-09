cmake_minimum_required(VERSION 3.10)
project(OOP_Telemetry)

add_executable(oop_telemetry_node oop_telemetry_node.cpp)
target_link_libraries(oop_telemetry_node pthread)