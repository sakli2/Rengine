#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"

namespace RENGINE
{

    namespace VulkanAPI
    {
        class VulkanSwapChain
        {
        public:
            VulkanSwapChain(VkSwapchainKHR swapChain, VulkanSurface& surface);
            ~VulkanSwapChain();
            VulkanSwapChain(const VulkanSwapChain& device) = delete;
            VulkanSwapChain(VulkanSwapChain& device) = delete;
            VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
            operator VkSwapchainKHR() { return m_SwapChain; } 

            VulkanSurface& surface_ptr;
        private:
            VkSwapchainKHR m_SwapChain;
        };
    }
}