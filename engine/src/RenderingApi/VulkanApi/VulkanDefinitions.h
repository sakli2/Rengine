#pragma once
#include "pch.h"
#include "vulkan/vulkan.hpp"


namespace RENGINE
{
    class VulkanLogicalDevice;


    namespace VulkanAPI
    {
        class VulkanManager;
        class VulkanPhysicalDevice;
        class VulkanLogicalDevice;
        class VulkanQueueFamily; 
        class VulkanSurface;
        class VulkanSwapChain;

        struct VulkanQueueSettings;
        struct VulkanSwapChainConfig;
    }
}


//TODOS
/*
1.make smart queue selection for logical device
2.make vulkanManager independent of Glfw
3.make vulkanManager configable with extensions

*/