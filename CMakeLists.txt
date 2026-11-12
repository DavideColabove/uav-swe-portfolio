cmake_minimum_required(VERSION 3.10) project(UAV_Software_Portfolio)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} / out)

        add_subdirectory(01_cpp_robotics / memory_management / src)
            add_subdirectory(01_cpp_robotics / concurrency / src)