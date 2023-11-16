// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#include "engine.h"
#include "core_context.h"
#include "device.h"
#include "instance.h"
#include "vulkan_logging.h"
#include <logging.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>

Engine::Engine()
{
    vtpl::CoreContext::instance();
    if (debugMode)
    {
        RAY_LOG_INF << "Making a graphics engine";
    }
    make_instance();
    make_device();
}
Engine::~Engine()
{
    if (debugMode)
    {
        RAY_LOG_INF << "Removing the graphics engine";
        instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
    }
    /*
    * from vulkan_funcs.hpp:
    *
    * void Instance::destroy( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator = nullptr,
                                            Dispatch const & d = ::vk::getDispatchLoaderStatic())
    */
    instance.destroy();

    // terminate glfw
    //  glfwTerminate();    // FIXME
}

/*
* Including the prebuilt header from the lunarg sdk will load
* most functions, but not all.
*
* Functions can also be dynamically loaded, using the call
*
* PFN_vkVoidFunction vkGetInstanceProcAddr(
    VkInstance                                  instance,
    const char*                                 pName);

 or

 PFN_vkVoidFunction vkGetDeviceProcAddr(
    VkDevice                                    device,
    const char*                                 pName);

    We will look at this later, once we've created an instance and device.
*/

void Engine::make_instance()
{
    instance = vtpl::make_instance(debugMode, "ID Tech 12");
    dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);
    if (debugMode)
    {
        debugMessenger = vtpl::make_debug_messenger(instance, dldi);
    }
}

void Engine::make_device() { physicalDevice = vtpl::choose_physical_device(instance, debugMode); }