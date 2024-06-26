#pragma once

#include "logical_device.hpp"
#include "shader.hpp"
#include "swapchain.hpp"

#include <memory>
#include <array>

using ShaderStageInfos = std::array<VkPipelineShaderStageCreateInfo, 2u>;

namespace VE {

struct PipelineConfigInfo {
    const VkPipelineDynamicStateCreateInfo dynamicState{};
    const VkPipelineViewportStateCreateInfo viewport{};
    const VkPipelineVertexInputStateCreateInfo vertexInput{};
    const VkPipelineInputAssemblyStateCreateInfo inputAsembly{};
    const VkPipelineRasterizationStateCreateInfo rasterizer{};
    const VkPipelineMultisampleStateCreateInfo multisampling{};
    const VkPipelineColorBlendStateCreateInfo colorBlends{};
};

class Pipeline {
public:
    Pipeline(std::shared_ptr<LogicalDevice> logicalDevice, std::shared_ptr<Swapchain> swapchain);

    ~Pipeline();

    VkPipeline getHandle() const;

    VkViewport getViewport() const;

    VkRect2D getScissor() const;

private:
    Shader m_vertexShader;
    Shader m_fragmentShader;
    std::shared_ptr<LogicalDevice> m_logicalDevice;
    std::shared_ptr<Swapchain> m_swapchain;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;
    VkViewport m_viewport;
    VkRect2D m_scissor;

    void createPipelineLayout();
    void createPipeline();

    VkPipelineShaderStageCreateInfo pupulateShaderStageInfo(enum VkShaderStageFlagBits shaderType, const Shader& shader) const;
    ShaderStageInfos createShaderStagesInfo() const;
    VkPipelineDynamicStateCreateInfo createDynamicStatesInfo() const;
    void createViewport();
    void createScissor();
    VkPipelineViewportStateCreateInfo createViewportStateInfo() const;
    VkPipelineVertexInputStateCreateInfo createVertexInputInfo() const;
    VkPipelineInputAssemblyStateCreateInfo createInputAsemblyInfo() const;
    VkPipelineRasterizationStateCreateInfo createRasterizerInfo() const;
    VkPipelineMultisampleStateCreateInfo createMultisamplingInfo() const;
    VkPipelineColorBlendAttachmentState createColorBlendAttachmentState() const;
    VkPipelineColorBlendStateCreateInfo createColorBlendAttachmentInfo(VkPipelineColorBlendAttachmentState state) const;
};

};