// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#include "engine.h"
#include <logging.h>
#include "core_context.h"
#include "vulkan_logging.h"
#include "instance.h"
#include "device.h"

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

void Engine::make_instance()
{
    instance = vtpl::make_instance(debugMode, "ID Tech 12");
    dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);
    if (debugMode)
    {
        debugMessenger = vtpl::make_debug_messenger(instance, dldi);
    }
}

void Engine::make_device()
{

    physicalDevice = vtpl::choose_physical_device(instance, debugMode);
}