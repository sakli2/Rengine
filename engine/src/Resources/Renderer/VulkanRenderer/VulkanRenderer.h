#pragma once
#include <pch.h>
#include <Rengine/Resources/Resources.h>
#include "VulkanRendererSettings.h"





namespace RENGINE
{                                
    CREATE_RESOURCE(VulkanRenderer, Renderer)
    {
    public:
        VulkanRenderer();
        virtual ~VulkanRenderer() override;

        void setup();

    private:
        VulkanRendererSettings m_RendererSettings;

        std::unique_ptr<VulkanAPI::VulkanManager> m_Manager;
        std::unique_ptr<VulkanAPI::VulkanLogicalDevice> m_ActiveDevice;

        //std::unique_ptr<VulkanAPI::
    };
}

