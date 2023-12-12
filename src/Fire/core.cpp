#include "core.h"

#include <string>

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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
	LOG_EMPTY_LINE();
}

// Destroy Core
Fire::Core::~Core()
{
	// Cleanup glfw
	glfwTerminate();


	// done
	LOG_EMPTY_LINE();
	LOGI("Core destroyed (press enter to exit ...)");
	std::cin.get();
}


// Callbacks

void Fire::Core::GlfwErrorCallback(int error, const char* description)
{
	EXCEPTION("GLFW Error " + std::to_string(error) + ": " + description);
}