
cmake_minimum_required (VERSION 3.26)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(Fire VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(Fire
            ${SRC_FILES}
            ${INCLUDE_FILES}
            )
            
if(MSVC)
    target_compile_options(Fire PRIVATE /Wall /sdl /std:c++20 /external:anglebrackets /fsanitize=address)
else()
    target_compile_options(Fire PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_definitions(Fire PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # define RESOURCES_PATH macro

# -- libs --
set(VK_BOOTSTRAP_VULKAN_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/Vulkan-Headers/include" CACHE STRING "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(extern/vulkan)
add_subdirectory(extern/vkb)
add_subdirectory(extern/glfw)
add_subdirectory(extern/sdl)
# ----------
# -- ImGui --
set(IMGUI_PATH "${CMAKE_CURRENT_LIST_DIR}/extern/imgui")
add_library(imgui)

target_sources(imgui PRIVATE
            "${IMGUI_PATH}/imgui.h"
            "${IMGUI_PATH}/imgui.cpp"
            
            "${IMGUI_PATH}/imgui_demo.cpp"
            "${IMGUI_PATH}/imgui_draw.cpp"
            "${IMGUI_PATH}/imgui_widgets.cpp"
            
            "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp"
            "${IMGUI_PATH}/backends/imgui_impl_vulkan.cpp"
            "${IMGUI_PATH}/backends/imgui_impl_sdl3.cpp"
            )
target_include_directories(imgui PUBLIC
            ${IMGUI_PATH}/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/Vulkan-Headers/include/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/include/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/sdl/include/
            )
# -----------

target_include_directories(Fire PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
            ${IMGUI_PATH}/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/Vulkan-Headers/include/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/vkb/src/ # vulkan bootstrap
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/vulkan/ # vulkan-hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/include/
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/sdl/include/
            )

target_link_directories(Fire PUBLIC ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(Fire PUBLIC
            vulkan-1
            vk-bootstrap::vk-bootstrap
            glfw
            SDL3::SDL3
            imgui
            )