# *****************************************************
#    Copyright 2022 Videonetics Technology Pvt Ltd
# *****************************************************
cmake_minimum_required(VERSION 3.15)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(logutil REQUIRED)

add_executable(vulkan_glfw_exe
    src/main.cpp
    src/window.cpp
)

target_include_directories(vulkan_glfw_exe
    PRIVATE inc
    PUBLIC include
)

target_link_libraries(vulkan_glfw_exe
    PRIVATE glfw
    PRIVATE glm::glm
    PRIVATE Vulkan::Vulkan
    PRIVATE logutil::core
)

target_compile_features(vulkan_glfw_exe
    PRIVATE cxx_std_17
)