
#include "window.h"
#include "general.h"

#include <iostream>


Fire::Window::Window(const WindowProps& props)
	: m_Props{ props }
{
	// Create window
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, props.IsResizable);

	m_pWindow = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
}

Fire::Window::~Window()
{
	// Destroy window
	glfwDestroyWindow(m_pWindow);
}

void Fire::Window::Update()
{
	glfwPollEvents();
}


// Vulkan

VkResult Fire::Window::CreateSurface(VkInstance instance, VkSurfaceKHR* pSurface, const VkAllocationCallbacks* pCallback)
{
	return glfwCreateWindowSurface(instance, m_pWindow, pCallback, pSurface);
}

void Fire::Window::GetFramebufferSize(int* width, int* height)
{
	glfwGetFramebufferSize(m_pWindow, width, height);
}