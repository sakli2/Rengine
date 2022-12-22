#include "pch.h"
#include "VkSurface.h"
#include "VkManager.h"
#include "VkLogicalDevice.h"
#include "VkPhysicalDevice.h"
#include "VkSwapChain.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        VulkanSurface::VulkanSurface(VkSurfaceKHR surface,VulkanLogicalDevice& logicalDevice)
            :logicalDevice_ptr(logicalDevice),m_Surface(surface)
        {

        }

        VulkanSurface::~VulkanSurface()
        {
            //vkDestroySurfaceKHR(logicalDevice_ptr.physicalDevice_ptr.manager_ptr, m_Surface, nullptr);
        }

        VkSurfaceCapabilitiesKHR VulkanSurface::getSurfaceCapabilities()
        {
            VkSurfaceCapabilitiesKHR capabilities;
            //vkGetPhysicalDeviceSurfaceCapabilitiesKHR(logicalDevice_ptr.physicalDevice_ptr, m_Surface, &capabilities);
            return capabilities;
        }
        

        std::vector<VkSurfaceFormatKHR> VulkanSurface::getSurfaceFormats()
        {
            std::uint32_t formatCount;
            //vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDevice_ptr.physicalDevice_ptr, m_Surface, &formatCount, nullptr);

            std::vector<VkSurfaceFormatKHR> formats;
            //formats.resize(formatCount);
            //if (formatCount != 0)
            //    vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDevice_ptr.physicalDevice_ptr, m_Surface, &formatCount, formats.data());
            //else
            //    LOG::warning("Surface has no supported format");

            return formats;
        }
    
        std::vector<VkPresentModeKHR> VulkanSurface::getSurfacePresentModes()
        {
            //uint32_t presentModeCount;
            //vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDevice_ptr.physicalDevice_ptr, m_Surface, &presentModeCount, nullptr);
//
            std::vector<VkPresentModeKHR> presentModes;
            //presentModes.resize(presentModeCount);
            //if (presentModeCount != 0) 
            //    vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDevice_ptr.physicalDevice_ptr, m_Surface, &presentModeCount, presentModes.data());
            return presentModes;
        }


        VulkanSwapChain VulkanSurface::createSwapChain(VulkanSwapChainConfig config)
        {
            VkSwapchainKHR swapChain;
            //config.swapChainInfo.surface = m_Surface;
            //if (vkCreateSwapchainKHR(logicalDevice_ptr, &config.swapChainInfo, nullptr, &swapChain) != VK_SUCCESS)
            //{
            //    LOG::error("Failed to create swapchain for surface!");
            //}

            return VulkanSwapChain(swapChain, *this);
        }
        
    }
}
