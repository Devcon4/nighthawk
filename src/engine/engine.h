#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

// #include "../../lib/json.hpp"

// #define TINYGLTF_IMPLEMENTATION
// #include "../../lib/tiny_gltf.h"

#define VMA_VULKAN_VERSION 1002000
#include "../../lib/vk_mem_alloc.h"

namespace Nighthawk {
std::vector<char> LoadShader(const std::string &path);

class NighthawkEngine {
 public:
  void run();

  static void framebufferResizeCallback(GLFWwindow *window, int width,
                                        int height);

 private:
  GLFWwindow *window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;
  VkSurfaceKHR surface;
  VkQueue presentQueue;
  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  std::vector<VkImageView> swapChainImageViews;
  VkRenderPass renderPass;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkCommandPool commandPool;
  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;

  VkBuffer vertexBuffer;
  VmaAllocation vertexBufferAlloc;
  VkBuffer indexBuffer;
  VmaAllocation indexBufferAlloc;

  VkImage textureImage;
  VmaAllocation textureImageAlloc;
  VkImageView textureImageView;
  VkSampler textureSampler;

  VkImage depthImage;
  VmaAllocation depthImageAlloc;
  VkImageView depthImageView;

  VmaAllocator allocator;

  std::vector<VkBuffer> uniformBuffers;
  std::vector<VmaAllocation> uniformBuffersAlloc;
  std::vector<void *> uniformBuffersMapped;

  std::vector<VkCommandBuffer> commandBuffers;
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  bool framebufferResized = false;
  double elapsedTime;
  uint32_t currentFrame = 0;

  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  const std::vector<const char *> validationLayers = {
      "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

  void initWindow();
  void initVulkan();
  void createSyncObjects();
  void cleanupSwapChain();
  void recreateSwapChain();
  void createGraphicsPipeline();
  void createFramebuffers();
  void createRenderPass();
  void createSurface();
  void createSwapChain();
  void createImageViews();
  void createCommandPool();
  void createCommandBuffers();
  void createInstance();
  void createVulkanMemoryAllocator();
  void mainLoop();
  void drawFrame();
  void updateUniformBuffer(uint32_t currentImage);
  void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                    VmaAllocationCreateFlags flags, VkBuffer &buffer,
                    VmaAllocation &alloc);
  void createDescriptorSetLayout();
  void transitionImageLayout(VkImage image, VkFormat format,
                             VkImageLayout oldLayout, VkImageLayout newLayout);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width,
                         uint32_t height);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer distBuffer, VkDeviceSize size);
  void createUniformBuffers();
  void createIndexBuffer();
  void createVertexBuffer();
  void createTextureImage();
  VkImageView createImageView(VkImage image, VkFormat format,
                              VkImageAspectFlags aspectFlags);
  void createTextureSampler();
  void createTextureImageView();
  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void createImage(uint32_t width, uint32_t height, VkFormat format,
                   VkImageTiling tiling, VkImageUsageFlags usage,
                   VmaAllocationCreateFlags flags, VkImage &image,
                   VmaAllocation &alloc);
  void createDescriptorPool();
  void createDescriptorSets();
  VkFormat findSupportedFormat(const std::vector<VkFormat> &canidates,
                               VkImageTiling tiling,
                               VkFormatFeatureFlags features);
  VkFormat findDepthFormat();
  bool hasStencilComponent(VkFormat format);
  void createDepthResources();
  void cleanup();

  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
  uint32_t findMemoryType(uint32_t typeFilter,
                          VkMemoryPropertyFlags properties);
  bool checkValidationLayerSupport();
  std::vector<const char *> getRequiredExtensions();
  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo);
  void setupDebugMessenger();
  void pickPhysicalDevice();
  void createLogicalDevice();
};
}  // namespace Nighthawk