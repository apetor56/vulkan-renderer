#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "logical_device.hpp"

namespace VE {

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Swapchain {
public:
    Swapchain(std::shared_ptr<PhysicalDevice> physicalDevice,
              std::shared_ptr<LogicalDevice> logicalDevice,
              std::shared_ptr<Window> window);

    ~Swapchain();

    Swapchain(const Swapchain& other) = delete;
    Swapchain(Swapchain&& other) = delete;

    Swapchain& operator=(const Swapchain& other) = delete;
    Swapchain& operator=(Swapchain&& other) = delete;

    static SwapchainSupportDetails querySwapChainSupport(const VkPhysicalDevice physicalDevice,
                                                         const VkSurfaceKHR surface);

    VkExtent2D getExtent() const noexcept;

    VkRenderPass getRenderpass() const noexcept;

    VkFramebuffer getFrambuffer(const uint32_t index) const;

    uint32_t getImagesCount() const noexcept;

    VkSwapchainKHR getHandle() const noexcept;

private:
    std::shared_ptr<PhysicalDevice> m_physicalDevice;
    std::shared_ptr<LogicalDevice> m_logicalDevice;
    std::shared_ptr<Window> m_window;

    VkSwapchainKHR m_swapchain;
    VkFormat m_format;
    VkExtent2D m_extent;
    VkRenderPass m_renderPass;
    std::vector<VkImage> m_swapchainImages;
    std::vector<VkImageView> m_swapChainImageViews;
    std::vector<VkFramebuffer> m_framebuffers;

    void createSwapchain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;
};

}