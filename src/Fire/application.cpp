#include "application.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "core.h"
#include "general.h"
#include "window.h"


Fire::Application::Application(const char* const name)
	: m_Name(name)
{
	InitializeCore();
}

void Fire::Application::InitializeCore()
{
	static Fire::Core instance{}; // Create and initialize core if it is not created yet
}

void Fire::Application::InitializeBase()
{
	m_pMainWindow = new Fire::Window{ Fire::WindowProps(1920, 1080, true), (STR(m_Name) + " [Fire Engine, " + CONFIGURATION_STR + " mode]").c_str() };
	m_pMainWindow->SetIcon(FENGINE_RESOURCES_PATH "icons/FireIcon_32x32.png");
}

void Fire::Application::CleanupBase()
{
	SAFE_DELETE(m_pMainWindow);
}

void Fire::Application::Run()
{
	// Initialize
	InitializeBase();
	Initialize(); // override for implementation

	// Loop
	bool shouldContinue = true;

	while (shouldContinue)
	{
		glfwPollEvents(); // TODO: this should only be called on the main thread (frequency of calls should also be looked into), make it safe (no multithreading yet but could bring problems in the future)
		m_pMainWindow->Update();

		if (m_pMainWindow->GetShouldClose() == GLFW_TRUE)
		{
			shouldContinue = false;
		}
	}

	// Cleanup
	Cleanup(); // override for implementation
	CleanupBase();
}