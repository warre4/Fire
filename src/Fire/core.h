#pragma once
#include "application.h"

namespace Fire
{
	class Core final
	{
	public:
		~Core();
		Core(const Core& other) = delete;
		Core(Core&& other) noexcept = delete;
		Core& operator=(const Core& other) = delete;
		Core& operator=(Core&& other) noexcept = delete;

	private:
		friend void Application::InitializeCore(); // Core can only be initialized in `Application::InitializeCore()`
		Core(); // private constructor

		static void GlfwErrorCallback(int error, const char* description);
	};
}