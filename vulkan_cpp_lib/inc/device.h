// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#pragma once
#ifndef device_h
#define device_h
#include <vulkan/vulkan.hpp>
#include <vector>
#include <logging.h>
#include "vulkan_logging.h"
#include <sstream>
#include <set>

namespace vtpl
{

    /**
        Print out the properties of the given physical device.

        \param device the physical device to investigate
    */
    void log_device_properties(const vk::PhysicalDevice &device)
    {
        /*
        * void vkGetPhysicalDeviceProperties(
            VkPhysicalDevice                            physicalDevice,
            VkPhysicalDeviceProperties*                 pProperties);
        */

        vk::PhysicalDeviceProperties properties = device.getProperties();

        /*
        * typedef struct VkPhysicalDeviceProperties {
            uint32_t                            apiVersion;
            uint32_t                            driverVersion;
            uint32_t                            vendorID;
            uint32_t                            deviceID;
            VkPhysicalDeviceType                deviceType;
            char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
            uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
            VkPhysicalDeviceLimits              limits;
            VkPhysicalDeviceSparseProperties    sparseProperties;
            } VkPhysicalDeviceProperties;
        */

        std::stringstream ss;
        ss << "Device name: " << properties.deviceName << '\n';

        ss << "Device type: ";
        switch (properties.deviceType)
        {

        case (vk::PhysicalDeviceType::eCpu):
            ss << "CPU\n";
            break;

        case (vk::PhysicalDeviceType::eDiscreteGpu):
            ss << "Discrete GPU\n";
            break;

        case (vk::PhysicalDeviceType::eIntegratedGpu):
            ss << "Integrated GPU\n";
            break;

        case (vk::PhysicalDeviceType::eVirtualGpu):
            ss << "Virtual GPU\n";
            break;

        default:
            ss << "Other\n";
        }
        RAY_LOG_INF << ss.str();
    }
    /**
        Check whether the physical device can support the given extensions.

        \param device the physical device to check
        \param requestedExtensions a list of extension names to check against
        \param debug whether the system is running in debug mode
        \returns whether all of the extensions are requested
    */
    bool checkDeviceExtensionSupport(
        const vk::PhysicalDevice &device,
        const std::vector<const char *> &requestedExtensions,
        const bool &debug)
    {

        /*
         * Check if a given physical device can satisfy a list of requested device
         * extensions.
         */

        std::set<std::string> requiredExtensions(requestedExtensions.begin(), requestedExtensions.end());
        std::stringstream ss;

        if (debug)
        {
            ss << "Device can support extensions:\n";
        }

        for (vk::ExtensionProperties &extension : device.enumerateDeviceExtensionProperties())
        {

            if (debug)
            {
                ss << "\t\"" << extension.extensionName << "\"\n";
            }

            // remove this from the list of required extensions (set checks for equality automatically)
            requiredExtensions.erase(extension.extensionName);
        }
        if (debug)
        {
            RAY_LOG_INF << ss.str();
        }

        // if the set is empty then all requirements have been satisfied
        return requiredExtensions.empty();
    }
    /**
        Check whether the given physical device is suitable for the system.

        \param device the physical device to check.
        \debug whether the system is running in debug mode.
        \returns whether the device is suitable.
    */
    bool isSuitable(const vk::PhysicalDevice &device, const bool debug)
    {

        if (debug)
        {
            RAY_LOG_INF << "Checking if device is suitable";
        }

        /*
         * A device is suitable if it can present to the screen, ie support
         * the swapchain extension
         */
        const std::vector<const char *> requestedExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        std::stringstream ss;
        if (debug)
        {
            ss << "We are requesting device extensions:\n";

            for (const char *extension : requestedExtensions)
            {
                ss << "\t\"" << extension << "\"\n";
            }
            RAY_LOG_INF << ss.str();
        }

        if (bool extensionsSupported = checkDeviceExtensionSupport(device, requestedExtensions, debug))
        {

            if (debug)
            {
                RAY_LOG_INF << "Device can support the requested extensions!";
            }
            return true;
        }
        else
        {

            if (debug)
            {
                RAY_LOG_INF << "Device can't support the requested extensions!";
            }

            return false;
        }
    }

    /**
            Choose a physical device for the vulkan instance.

            \param instance the vulkan instance to use
            \param debug whether the system is running in debug mode
            \returns the chosen physical device
        */
    vk::PhysicalDevice choose_physical_device(const vk::Instance &instance, const bool debug)
    {
        /*
         * Choose a suitable physical device from a list of candidates.
         * Note: Physical devices are neither created nor destroyed, they exist
         * independently to the program.
         */
        if (debug)
        {
            RAY_LOG_INF << "Choosing Physical Device";
        }

        /*
        * ResultValueType<std::vector<PhysicalDevice, PhysicalDeviceAllocator>>::type
            Instance::enumeratePhysicalDevices( Dispatch const & d )

          std::vector<vk::PhysicalDevice> instance.enumeratePhysicalDevices( Dispatch const & d = static/default )
        */
        std::vector<vk::PhysicalDevice> availableDevices = instance.enumeratePhysicalDevices();

        if (debug)
        {
            RAY_LOG_INF << "There are " << availableDevices.size() << " physical devices available on this system";
        }

        /*
         * check if a suitable device can be found
         */
        for (vk::PhysicalDevice device : availableDevices)
        {

            if (debug)
            {
                log_device_properties(device);
            }
            if (isSuitable(device, debug))
            {
                return device;
            }
        }

        return nullptr;
    }
} // namespace vtpl

#endif // device_h
