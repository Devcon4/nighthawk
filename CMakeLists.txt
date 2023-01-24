# CMakeList.txt : CMake project for Nighthawk, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Nighthawk")

# Add source to this project's executable.
add_executable (Nighthawk "src/main.cpp" "src/engine/engine.cpp" "src/engine/engine.h")

include_directories("C:/VulkanSDK/1.3.211.0/Include")

find_package(glfw REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)
find_package(Vulkan COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

add_subdirectory(src/engine)
add_subdirectory(lib)
set_target_properties(stbImage PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(tinygltf PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(vkMemAlloc PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Nighthawk PRIVATE glfw3)
target_link_libraries(Nighthawk PRIVATE Engine)
target_link_libraries(Nighthawk PRIVATE stbImage)
target_link_libraries(Nighthawk PRIVATE Vulkan::Vulkan)
target_link_libraries(Nighthawk PRIVATE glm::glm)
target_link_libraries(Nighthawk PRIVATE tinygltf)
target_link_libraries(Nighthawk PRIVATE json)

target_include_directories(Nighthawk PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/lib/engine")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/resources)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_BINARY_DIR}/bin )

# TODO: Add tests and install targets if needed.

function(add_shader TARGET SHADER)
    find_program(GLSLC glslc)

    set(current-shader-path ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/${SHADER})
    string(REPLACE . _ shader-name ${SHADER})
    set(current-output-path ${CMAKE_BINARY_DIR}/bin/shaders/${shader-name}.spv)

    # Add a custom command to compile GLSL to SPIR-V.
    get_filename_component(current-output-dir ${current-output-path} DIRECTORY)
    file(MAKE_DIRECTORY ${current-output-dir})

    add_custom_command(
           OUTPUT ${current-output-path}
           COMMAND ${GLSLC} -o ${current-output-path} ${current-shader-path}
           DEPENDS ${current-shader-path}
           IMPLICIT_DEPENDS CXX ${current-shader-path}
           VERBATIM)

    # Make sure our build depends on this output.
    set_source_files_properties(${current-output-path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${current-output-path})
endfunction(add_shader)

file(GLOB_RECURSE GLSL_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
    "*.frag"
    "*.vert"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  ADD_SHADER(Nighthawk ${GLSL})
endforeach(GLSL)
