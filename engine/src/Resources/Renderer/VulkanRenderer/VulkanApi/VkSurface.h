#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"


namespace RENGINE
{
    namespace VulkanAPI
    {
        struct VulkanSwapChainConfig
        {
            VulkanSwapChainConfig() { swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;}
        //todo CREATE SEPERATE OBJECT
            VkSwapchainCreateInfoKHR swapChainInfo;
        };

        class VulkanSurface
        {
        public:
            VulkanSurface(VkSurfaceKHR surface, VulkanLogicalDevice& logicalDevice);
            ~VulkanSurface();
            VulkanSurface(const VulkanSurface& device) = delete;
            VulkanSurface(VulkanSurface& device) = delete;
            VulkanSurface& operator=(const VulkanSurface&) = delete;
            operator VkSurfaceKHR() { return m_Surface; } 

            VkSurfaceCapabilitiesKHR getSurfaceCapabilities();
            std::vector<VkSurfaceFormatKHR> getSurfaceFormats();
            std::vector<VkPresentModeKHR> getSurfacePresentModes();


            VulkanSwapChain createSwapChain(VulkanSwapChainConfig config);
            VulkanLogicalDevice& logicalDevice_ptr;
        private:
            VkSurfaceKHR m_Surface;
        };
    }
}