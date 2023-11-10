#pragma once
#include <string>
#include <cstdint>

#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_vulkan.h>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Fire
{
#pragma pack()
	struct WindowProps
	{
		std::string Title;
		int Width;
		int Height;
		bool IsResizable;

		WindowProps(std::string title = "Placeholder Title", int width = 1600, int height = 900, bool isResizable = false)
			: Title{ std::move(title) }
			, Width{ width }
			, Height{ height }
			, IsResizable{ isResizable }
		{}
	};

	class Window
	{
	public:
		Window(const WindowProps& props);
		virtual ~Window();

		Window(const Window& other) = delete;
		Window(Window&& other) noexcept = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(Window&& other) noexcept = delete;

		void Update();
		

		// Vulkan

		[[nodiscard]] VkResult CreateSurface(VkInstance instance, VkSurfaceKHR* pSurface, const VkAllocationCallbacks* pCallback = nullptr);

		void GetFramebufferSize(int* width, int* height);


		// Getters & Setters

		[[nodiscard]] inline bool GetShouldClose() const { return glfwWindowShouldClose(m_pWindow) == GLFW_TRUE; }

		[[nodiscard]] inline const GLFWwindow* GetWindow() const noexcept { return m_pWindow; }
		[[nodiscard]] inline int GetWidth() const noexcept { return m_Props.Width; }
		[[nodiscard]] inline int GetHeight() const noexcept { return m_Props.Height; }
		[[nodiscard]] inline const std::string& GetTitle() const noexcept { return m_Props.Title; }
		[[nodiscard]] inline const WindowProps& GetProperties() const noexcept { return m_Props; }

		void SetTitle(const std::string& title)
		{
			m_Props.Title = title;
			glfwSetWindowTitle(m_pWindow, title.c_str());
		}


		// Callbacks

		static void GlfwErrorCallback(int error, const char* description);

	private:

		WindowProps m_Props;
		GLFWwindow* m_pWindow;
	};
}