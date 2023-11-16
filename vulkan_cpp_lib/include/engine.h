// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#pragma once
#ifndef engine_h
#define engine_h
#include <vulkan/vulkan.hpp>
class Engine
{

public:
    Engine();
    ~Engine();

private:
    // whether to print debug messages in functions
    bool debugMode = true;

    // // glfw-related variables
    // int width{640};
    // int height{480};
    // GLFWwindow *window{nullptr};

    // instance-related variables
    vk::Instance instance{nullptr};
    vk::DebugUtilsMessengerEXT debugMessenger{nullptr};
    vk::DispatchLoaderDynamic dldi;

    // device-related variables
    vk::PhysicalDevice physicalDevice{nullptr};

    // glfw setup
    void build_glfw_window();

    // instance setup
    void make_instance();

    // device setup
    void make_device();
};
#endif // engine_h
