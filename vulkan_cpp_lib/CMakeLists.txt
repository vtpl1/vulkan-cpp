# *****************************************************
#    Copyright 2023 Videonetics Technology Pvt Ltd
# *****************************************************

find_package(Vulkan REQUIRED)
find_package(logutil REQUIRED)

add_library(vulkan_cpp_lib
    src/engine.cpp
    src/core_context.cpp
)

target_include_directories(vulkan_cpp_lib
    PRIVATE inc
    PUBLIC include
)

target_link_libraries(vulkan_cpp_lib
    PRIVATE logutil::core
    PUBLIC Vulkan::Vulkan
)

