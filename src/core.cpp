#include "core.h"

#include "general.h"
#include "window.h"

// Initialize Core
Fire::Core::Core()
{
	// Init glfw
	glfwInit();
#pragma warning(push)
#pragma warning(disable : 5039) // 'function': pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavior may occur if this function throws an exception.
	glfwSetErrorCallback(Fire::Core::GlfwErrorCallback);
#pragma warning(pop)


	// done
	LOGI("Core initialized");
}

// Destroy Core
Fire::Core::~Core()
{
	// Cleanup glfw
	glfwTerminate();


	// done
	LOGI("Core destroyed (press enter to exit ...)");
	std::cin.get();
}


// Callbacks

void Fire::Core::GlfwErrorCallback(int error, const char* description)
{
	EXCEPTION(STR("GLFW Error ") + std::to_string(error) + STR(": ") + STR(description));
}