
#include "window.h"
#include "general.h"
#include "utils.h"

#include <iostream>
#include <functional>
#include <optional>

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



std::unordered_map<const GLFWwindow*, Fire::Window*>* Fire::Window::m_pGLFWwindowToWindowMap = nullptr;


Fire::Window::Window(const WindowProps& props, const char* title)
	: m_Props{ props }
{
	// Create window
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, props.IsResizable);

	m_pWindow = glfwCreateWindow(props.Width, props.Height, title, nullptr, nullptr);

	if (props.IsResizable)
	{
		// set callbacks
#pragma warning(push)
#pragma warning(disable: 5039) //C5039: 'glfwSetWindowSizeCallback': pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc. Undefined behavior may occur if this function throws an exception.
		glfwSetWindowSizeCallback(m_pWindow, OnWindowResized);
#pragma warning(pop)
	}

	// title
	m_pTitle = new std::string(title);

	// add to umap
	if (m_pGLFWwindowToWindowMap == nullptr)
	{
		m_pGLFWwindowToWindowMap = new std::unordered_map<const GLFWwindow*, Fire::Window*>{};
		LOGD("m_pGLFWwindowToWindowMap was allocated in memory");
	}
	(*m_pGLFWwindowToWindowMap)[m_pWindow] = this; // storing `this` for later use, `this` object could be incomplete in the constructor but we are simply storing its address
}

Fire::Window::~Window()
{
	// remove from umap
	m_pGLFWwindowToWindowMap->erase(m_pWindow);

	if (m_pGLFWwindowToWindowMap->size() == 0)
	{
		SAFE_DELETE(m_pGLFWwindowToWindowMap); // also gets set to nullptr
		LOGD("m_pGLFWwindowToWindowMap was released from memory");
	}

	// title
	SAFE_DELETE(m_pTitle);

	// Destroy window
	glfwDestroyWindow(m_pWindow);
}

void Fire::Window::Update()
{

}

void Fire::Window::Render() const
{

}


// Callbacks

void Fire::Window::OnWindowResized(GLFWwindow* pGLFWwindow, int width, int height)
{
	// TODO: add something to delay the call of `pWindow->SetWindowWidthHeight(width, height);` if the user is still resizing the window

	// Find Window object that owns `pGLFWwindow`
	Fire::Window* pWindow = Fire::Window::GetWindowFromGLFWwindow(pGLFWwindow);
	
	pWindow->SetWindowWidthHeight(width, height);
}


// Helpers

//...


// Getters & Setters

bool Fire::Window::GetShouldClose() const
{
	return glfwWindowShouldClose(m_pWindow) == GLFW_TRUE;
}

void Fire::Window::SetTitle(const char* title)
{
	delete m_pTitle;
	m_pTitle = new std::string(title); // speed should not matter here

	glfwSetWindowTitle(m_pWindow, title);
}

void Fire::Window::SetWindowWidthHeight(int width, int height)
{
	m_Props.Width = width;
	m_Props.Height = height;
	glfwSetWindowSize(m_pWindow, width, height);

	LOGD("Window was resized (window title: " + *m_pTitle + ")");
}

void Fire::Window::SetIcon(const char* path)
{
	Image image = _F_UTILS CreateImage(path);
	SetIcon(image);
	_F_UTILS DestroyImage(image);
}

void Fire::Window::SetIcon(const Image& image)
{
	GLFWimage images[1];
	images[0].pixels = image.pData;
	images[0].width = image.width;
	images[0].height = image.height;
	
	glfwSetWindowIcon(m_pWindow, 1, images);
}