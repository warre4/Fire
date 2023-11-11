#include "application.h"

#include "core.h"
#include "general.h"
#include "window.h"


Fire::Application::Application(std::string name)
	: m_Name(std::move(name))
{
	InitializeCore();
}

void Fire::Application::InitializeCore()
{
	static Fire::Core instance{}; // Create and initialize core if it is not created yet
}

void Fire::Application::InitializeBase()
{
	m_pMainWindow = new Fire::Window{ Fire::WindowProps(STR("Fire Engine! :D [") + m_Name + STR("]"), 1920, 1080, true)};
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