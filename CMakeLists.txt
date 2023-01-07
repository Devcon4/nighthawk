cmake_minimum_required(VERSION 3.0.0)
project(Nighthawk VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src/engine)
add_subdirectory(lib)

add_executable(Nighthawk)

find_package(glfw3 REQUIRED)

set_target_properties(stbImage PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Nighthawk PRIVATE src/main.cpp)
target_link_libraries(Nighthawk PRIVATE Engine stbImage Vulkan::Vulkan glfw3)
target_include_directories(Nighthawk PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/lib/engine")
