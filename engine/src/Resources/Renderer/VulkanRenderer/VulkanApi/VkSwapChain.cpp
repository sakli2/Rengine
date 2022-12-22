#include "pch.h"
#include "VkSwapChain.h"
#include "VkLogicalDevice.h"
#include "VkSurface.h"
namespace RENGINE
{
    namespace VulkanAPI
    {
        VulkanSwapChain::VulkanSwapChain(VkSwapchainKHR swapChain, VulkanSurface& surface)
            :m_SwapChain(swapChain), surface_ptr(surface)
        {
            
        }

        VulkanSwapChain::~VulkanSwapChain()
        {
            //vkDestroySwapchainKHR(surface_ptr.logicalDevice_ptr, m_SwapChain, nullptr);
        }
    }
}