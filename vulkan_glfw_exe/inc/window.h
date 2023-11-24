// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#pragma once
#ifndef window_h
#define window_h
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan.hpp>

class Window
{
  private:
    const uint32_t WIDTH_ = 800;
    const uint32_t HEIGHT_ = 600;
    const char*    window_name_ = "Vulkan";

    GLFWwindow* window_{nullptr};

    vk::Instance instance_;

    void initWindow();
    void initVulcan();
    void cleanup();
    void createInstance();

  public:
    Window();
    bool doEventLoop();
    ~Window();
};

#endif // window_h
