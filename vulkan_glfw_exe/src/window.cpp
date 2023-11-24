// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#include "window.h"
#include <logging.h>
#include <sstream>
#include <vector>
#include <vulkan/vulkan.hpp>

Window::Window()
{
    initWindow();
    initVulcan();
}

Window::~Window() { cleanup(); }

void Window::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window_ = glfwCreateWindow(WIDTH_, HEIGHT_, window_name_, nullptr, nullptr);
}

void Window::createInstance()
{
    vk::ApplicationInfo appInfo = vk::ApplicationInfo(window_name_, VK_MAKE_VERSION(1, 0, 0), "No engine",
                                                      VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_3);
    uint32_t            glfwExtensionCount = 0;
    const char**        glfwExtensions = nullptr;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    // "VK_KHR_surface"
    // "VK_KHR_win32_surface"
    // "VK_EXT_debug_utils"

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    std::vector<const char*> layers;

    vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(vk::InstanceCreateFlags(), &appInfo, layers.size(),
                                                               layers.data(), extensions.size(), extensions.data());
    vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    try
    {
        instance_ = vk::createInstance(createInfo);
        std::stringstream ss;
        ss << "Instance created with: " << std::endl;
        ss << "Extensions:" << std::endl;
        for (auto&& i : extensions)
        {
            ss << i << std::endl;
        }
        ss << "Layers: " << std::endl;
        for (auto&& i : layers)
        {
            ss << i << std::endl;
        }
        RAY_LOG_INF << ss.str();
    }
    catch (vk::SystemError err)
    {
        RAY_LOG_ERR << "Failed to create instance!";
    }
}

void Window::initVulcan() { createInstance(); }

void Window::cleanup()
{
    instance_.destroy(nullptr);
    glfwDestroyWindow(window_);
    glfwTerminate();
}

bool Window::doEventLoop()
{
    if (glfwWindowShouldClose(window_) != 0)
        return false;
    glfwPollEvents();
    return true;
}