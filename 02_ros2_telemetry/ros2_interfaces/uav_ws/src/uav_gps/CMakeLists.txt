cmake_minimum_required(VERSION 3.10) project(uav_gps)

# 1. Trova le macro di ament e le librerie necessarie
    find_package(ament_cmake REQUIRED) find_package(rclcpp REQUIRED)
        find_package(sensor_msgs REQUIRED) find_package(rclcpp_components REQUIRED)
            find_package(uav_interfaces REQUIRED)

# 2. Crea il Componente GPS(Libreria condivisa.so)
                add_library(gps_component SHARED src / gps_publisher.cpp)
                    target_compile_definitions(gps_component PRIVATE "GPS_COMPONENT_BUILDING_DLL")
                        target_link_libraries(
                            gps_component PUBLIC rclcpp::rclcpp sensor_msgs::sensor_msgs
                                rclcpp_components::component_manager uav_interfaces::uav_interfaces)

# 3. Registra il nodo componente e genera l'eseguibile automatico
                            rclcpp_components_register_node(gps_component PLUGIN
                                                            "GpsPublisher" EXECUTABLE gps_node)

# 4. Subscriber(nodo tradizionale)
                                add_executable(flight_node src / flight_controller.cpp)
                                    target_link_libraries(
                                        flight_node PUBLIC rclcpp::rclcpp sensor_msgs::sensor_msgs
                                            uav_interfaces::uav_interfaces)

#-- - REGOLA DI INSTALLAZIONE CORRETTA -- -
                                        install(TARGETS gps_component DESTINATION lib)

                                            install(TARGETS gps_node flight_node DESTINATION lib /
                                                    ${PROJECT_NAME})

# 5. Esporta le dipendenze dei componenti per il workspace
                                                ament_export_dependencies(
                                                    rclcpp_components rclcpp sensor_msgs)

# 6. Chiude la configurazione del pacchetto(DEVE stare rigorosamente alla fine)
                                                    ament_package()