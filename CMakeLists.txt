
cmake_minimum_required (VERSION 3.26)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

project(Fire VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

file(GLOB_RECURSE     SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_library(Fire SHARED
    ${SRC_FILES}
    ${INCLUDE_FILES}
)
            
if(MSVC)
    # disable warnings (informational warnings):
    # /wd4820 -> c4820 -> 'bytes' bytes padding added after construct 'member_name'
    # /wd4514 -> c4514 -> 'function' : unreferenced inline function has been removed
    # /wd4710 -> c4710 -> 'function' : function not inlined
    # /wd4711 -> c4711 -> function 'function' selected for inline expansion
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(Fire PRIVATE /Wall /wd4820 /wd4514 /wd4710 /wd4711 /sdl /std:c++20 /MDd /external:anglebrackets /external:I ${CMAKE_CURRENT_SOURCE_DIR}/extern/; /external:W0 /fsanitize=address)
        message(STATUS "compiler using debug options")
    else()
        target_compile_options(Fire PRIVATE /Wall /wd4820 /wd4514 /wd4710 /wd4711 /sdl /std:c++20 /MD /external:anglebrackets /external:I ${CMAKE_CURRENT_SOURCE_DIR}/extern/; /external:W0)
        message(STATUS "compiler using release options")
    endif()
else()
    target_compile_options(Fire PRIVATE -Wall -Wextra -Wpedantic)
endif()

# define macros
target_compile_definitions(Fire
    PRIVATE
        FIRE_ENGINE_COMPILING
        FENGINE_RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
)

# -- libs --
set(VK_BOOTSTRAP_VULKAN_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/Vulkan-Headers/include" CACHE STRING "" FORCE)
set(VK_BOOTSTRAP_TEST OFF CACHE BOOL "" FORCE)

set(GLFW_LIBRARY_TYPE STATIC)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
set(SDL_STATIC_PIC OFF CACHE BOOL "" FORCE) # PIC = position independent code

add_subdirectory(extern/vulkan)
add_subdirectory(extern/vkb)
add_subdirectory(extern/glfw)
add_subdirectory(extern/sdl)
# ----------
# -- ImGui --
set(IMGUI_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui")
add_library(imgui)

target_sources(imgui PRIVATE
    "${IMGUI_PATH}/imgui.h"
    "${IMGUI_PATH}/imgui.cpp"
    
    "${IMGUI_PATH}/imgui_demo.cpp"
    "${IMGUI_PATH}/imgui_draw.cpp"
    "${IMGUI_PATH}/imgui_widgets.cpp"
    "${IMGUI_PATH}/imgui_tables.cpp"
    
    "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_vulkan.cpp"
)
target_include_directories(imgui PUBLIC
    ${IMGUI_PATH}/
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/Vulkan-Headers/include/ # vulkan
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/include/ # glfw3
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/sdl/include/ # sdl3
)
# -----------

# define include directories
target_include_directories(Fire PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${IMGUI_PATH}/ # dear imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/Vulkan-Headers/include/ # vulkan
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/vkb/src/ # vulkan bootstrap
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan/vulkan/ # vulkan-hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/include/ # glfw3
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/sdl/include/ # sdl3
)

# link libraries
target_link_directories(Fire PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

target_link_libraries(Fire PRIVATE
    vulkan-1
    vk-bootstrap::vk-bootstrap
    glfw
    SDL3::SDL3-static
    imgui
)

# copy pre-built libs
if(WIN32)
    add_custom_command(TARGET Fire PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan-1.lib"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
else()
    add_custom_command(TARGET Fire PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/extern/vulkan-1.a"
            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif()