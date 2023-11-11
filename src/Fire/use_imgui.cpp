
#include "use_imgui.h"
#include "general.h"

#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_vulkan.h>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#pragma warning(push)
//#pragma warning(disable : 26451) // Arithmetic overflow: Using operator 'operator' on a size-a byte value and then casting the result to a size-b byte value. Cast the value to the wider type before calling operator 'operator' to avoid overflow (io.2)
//    #include <vulkan/vulkan.hpp>
//#pragma warning(pop)
#include <VkBootstrap.h>

#include <iostream>


#ifdef _DEBUG
    #define IMGUI_VULKAN_DEBUG_REPORT
#endif


void Fire::UseImgui::Init()
{

}

void Fire::UseImgui::ShutDown()
{

}

void Fire::UseImgui::Update()
{

}

void Fire::UseImgui::Render() const
{

}

bool Fire::UseImgui::InitVulkan()
{

    return false;
}