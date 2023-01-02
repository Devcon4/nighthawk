#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace Nighthawk {
std::vector<char> LoadShader(const std::string &path);

class NighthawkEngine {
 public:
  void run();

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
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
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
  void createGraphicsPipeline();
  void createFramebuffers();
  void createRenderPass();
  void createSurface();
  void createSwapChain();
  void createImageViews();
  void createCommandPool();
  void createCommandBuffers();
  void createInstance();
  void mainLoop();
  void drawFrame();
  void cleanup();

  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
  bool checkValidationLayerSupport();
  std::vector<const char *> getRequiredExtensions();
  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo);
  void setupDebugMessenger();
  void pickPhysicalDevice();
  void createLogicalDevice();
};
}  // namespace Nighthawk