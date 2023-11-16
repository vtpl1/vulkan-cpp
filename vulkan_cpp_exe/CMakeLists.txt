# *****************************************************
#    Copyright 2023 Videonetics Technology Pvt Ltd
# *****************************************************

add_executable(vulkan_cpp_exe
    src/main.cpp
)

target_include_directories(vulkan_cpp_exe
    PRIVATE inc
    PUBLIC include
)

target_link_libraries(vulkan_cpp_exe
    PRIVATE vulkan_cpp_lib
)

