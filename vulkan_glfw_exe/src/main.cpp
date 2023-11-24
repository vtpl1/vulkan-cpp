// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <logging.h>
#include <memory>

#include "window.h"

int main(int argc, char const* argv[])
{
    std::string name_of_app = "VulkanGlfwExe";
    ::ray::RayLog::StartRayLog(name_of_app, ::ray::RayLogLevel::INFO);
    std::unique_ptr<Window> window(new Window());
    RAY_LOG_INF << "Start";
    while (window->doEventLoop())
    {
        ;
    }
    RAY_LOG_INF << "Exiting";
    return 0;
}
