# CMakeList.txt : CMake project for Nighthawk, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Nighthawk")

# Add source to this project's executable.
add_executable (Nighthawk "src/main.cpp" "src/engine/engine.cpp" "src/engine/engine.h")

include_directories("/mnt/c/VulkanSDK/1.3.211.0/Include")

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)
find_package(Vulkan COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

add_subdirectory(src/engine)
add_subdirectory(lib)
set_target_properties(stbImage PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(tinygltf PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Nighthawk PRIVATE Engine stbImage Vulkan::Vulkan glfw glm::glm tinygltf json)

target_include_directories(Nighthawk PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/lib/engine" "${PROJECT_BINARY_DIR}/bin")

file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

# TODO: Add tests and install targets if needed.

if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else()
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin32/glslangValidator.exe")
endif()
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "shaders/*.frag"
    "shaders/*.vert"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )

add_dependencies(Nighthawk Shaders)

add_custom_command(TARGET Nighthawk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Nighthawk>/shaders/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:Nighthawk>/shaders"
        )