add_library(Engine engine.cpp)
set (CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Engine PUBLIC glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Engine PUBLIC glm::glm)

include_directories("C:/VulkanSDK/1.3.211.0/Include")

target_link_libraries(Engine PUBLIC Vulkan::Vulkan)
target_include_directories(Engine PRIVATE stbImage)
target_include_directories(Engine PRIVATE tinygltf)
target_include_directories(Engine PRIVATE json)
