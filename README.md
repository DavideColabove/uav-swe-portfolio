# UAV Software Engineering Portfolio

[![Portfolio Website](https://img.shields.io/badge/Deep--Dive_Docs-Visit_Site-38bdf8?style=for-the-badge&logo=github)](https://davidecolabove.github.io/uav-swe-portfolio/)

[![UAV CI Pipeline](https://github.com/DavideColabove/uav-swe-portfolio/actions/workflows/ci.yml/badge.svg)](https://github.com/DavideColabove/uav-swe-portfolio/actions/workflows/ci.yml)
[![LaTeX Documentation](https://github.com/DavideColabove/uav-swe-portfolio/actions/workflows/latex.yml/badge.svg)](https://davidecolabove.github.io/uav-swe-portfolio/)


## About This Project
This repository documents my 3-month intensive journey to master software engineering for Unmanned Aerial Vehicles (UAVs). The ultimate goal is to build a robust skill set for the autonomous last-mile delivery sector (medical and commercial logistics) and prepare for a 6-month internship in Europe.

## Tech Stack
* **Languages:** C++ (17/20), Python
* **Frameworks & Middleware:** ROS 2 (Humble), DDS Protocol
* **Avionics & Simulation:** PX4 Autopilot, MAVSDK, Gazebo, QGroundControl
* **AI & Vision:** PyTorch, OpenCV
* **Infrastructure:** Linux (Ubuntu 22.04), Docker, CMake

## Project Roadmap & Structure

### Phase 1: Systems & ROS 2 Fundamentals (Month 1)
* `01_cpp_robotics/`: Memory management (Smart Pointers), concurrency (`std::thread`), and asynchronous logging in modern C++.
* `02_ros2_telemetry/`: Custom nodes, Client/Server services, and QoS (Quality of Service) configurations for reliable sensor data transmission.

### Phase 2: Avionics & SITL Simulation (Month 2)
* `03_px4_sitl/`: Integration of the PX4 flight stack with the Gazebo simulator.
* `04_mavsdk_control/`: Python/C++ scripts for offboard autonomous flight control (takeoff, waypoint navigation, landing).

### Phase 3: Vision & Precision Landing (Month 3)
* `05_vision_landing/`: A complete pipeline where the simulated drone detects a visual marker using PyTorch/OpenCV and executes an autonomous precision landing.

## Industrial Validation & CI/CD

To ensure the reliability required for mission-critical UAV software, this repository enforces strict Continuous Integration pipelines on every commit:

* **Automated Build System:** Out-of-source CMake orchestration compiling multiple independent modules into a centralized binary directory.
* **Static Analysis:** `clang-tidy` enforces modern C++17 best practices, catching implicit conversions and logical vulnerabilities before execution.
* **Dynamic Memory & Thread Safety:** Automated runtime testing of all executable nodes instrumented with AddressSanitizer (ASan) and ThreadSanitizer (TSan). This guarantees zero memory leaks (via strict RAII) and prevents data races in highly concurrent publisher/subscriber environments.

## How to Build

To configure and compile the entire project, run the following commands from the repository root:

```bash
cmake -B build -S .
cmake --build build -j$(nproc)
```

## How to Run Tests

This repository uses GoogleTest and CTest for automated unit testing and algorithmic validation. After building the project, you can execute the full test suite by running:

```bash
cd build
ctest --output-on-failure
```