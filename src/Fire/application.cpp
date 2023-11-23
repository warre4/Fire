#include "application.h"

#include "core.h"
#include "general.h"
#include "window.h"

#ifdef _DEBUG
#define ADD_CONFIGURATION_STR + STR(", Debug mode")
#else
#define ADD_CONFIGURATION_STR + STR(", Release mode")
#endif


Fire::Application::Application(const char* name)
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
	m_pMainWindow = new Fire::Window{ Fire::WindowProps(STR(m_Name + STR(" [Fire Engine") ADD_CONFIGURATION_STR + STR("]")).c_str(), 1920, 1080, true)};
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