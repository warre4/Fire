#pragma once
#include "api.h"

#include "stl_containers.h"
#include "structs.h"

#include <cstdint>

class GLFWwindow;

namespace Fire
{
	struct FAPI WindowProps
	{
		int Width;
		int Height;
		bool IsResizable; // IsResizable cannot be changed after window creation

		WindowProps(int width = 1600, int height = 900, bool isResizable = false)
			: Width{ width }
			, Height{ height }
			, IsResizable{ isResizable }
		{}
	};

	class FAPI Window
	{
	public:
		Window(const WindowProps& props, const char* title = "Placeholder Title");
		virtual ~Window();

		Window(const Window& other) = delete;
		Window(Window&& other) noexcept = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(Window&& other) noexcept = delete;

		void Update();
		void Render() const;


		// Calllbacks

		static void OnWindowResized(GLFWwindow* pGLFWwindow, int width, int height);
		

		// Getters & Setters

		[[nodiscard]] bool GetShouldClose() const;

		[[nodiscard]] inline const GLFWwindow* GetWindow() const noexcept { return m_pWindow; }
		[[nodiscard]] inline int GetWidth() const noexcept { return m_Props.Width; }
		[[nodiscard]] inline int GetHeight() const noexcept { return m_Props.Height; }
		[[nodiscard]] inline const char* GetTitle() const noexcept { return m_pTitle->c_str(); }
		[[nodiscard]] inline const WindowProps& GetProperties() const noexcept { return m_Props; }

		[[nodiscard]] static Window* GetWindowFromGLFWwindow(const GLFWwindow* pGLFWwindow) { return (*m_pGLFWwindowToWindowMap)[pGLFWwindow]; }

		void SetTitle(const char* title);
		void SetWindowWidthHeight(int width, int height);
		inline void SetWindowWidth(int width) { SetWindowWidthHeight(width, m_Props.Height); }
		inline void SetWindowHeight(int height) { SetWindowWidthHeight(m_Props.Width, height); }
		void SetIcon(const char* path);
		void SetIcon(const Image& image);

	private:

		WindowProps m_Props;
		std::string* m_pTitle;

		GLFWwindow* m_pWindow;

		static std::unordered_map<const GLFWwindow*, Window*>* m_pGLFWwindowToWindowMap;
	};
}