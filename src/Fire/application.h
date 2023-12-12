#pragma once
#include "api.h"

#include "stl_containers.h"
#include "window.h"

#include <string_view>


namespace Fire
{
	class Window;
	class Core;
}

// DO NOT INCLUDE core.h IN THIS FILE

namespace Fire
{
	class FAPI Application
	{
	public:
		Application(const char* const name);

		virtual ~Application() = default;
		Application(const Application& other) = delete;
		Application(Application&& other) noexcept = delete;
		Application& operator=(const Application& other) = delete;
		Application& operator=(Application&& other) noexcept = delete;

		void Run();


		// Getters & Setters

		[[nodiscard]] inline const char* GetName() const noexcept { return m_Name; }
		[[nodiscard]] inline Window* GetWindow() const noexcept { return m_pMainWindow; }

		inline void SetWindowTitle(const char* title) const { m_pMainWindow->SetTitle(title); }
		inline void SetWindowWidthHeight(int width, int height) const { m_pMainWindow->SetWindowWidthHeight(width, height); };
		inline void SetWindowWidth(int width) const { m_pMainWindow->SetWindowWidth(width); };
		inline void SetWindowHeight(int height) const { m_pMainWindow->SetWindowHeight(height); };


		// Helpers
		


	protected:
		virtual void Initialize() = 0;
		virtual void Cleanup() = 0;

	private:
		friend Fire::Core; // access to `InitializeCore()`

		void InitializeBase();
		void CleanupBase();
		void InitializeCore(); // Makes sure that the core is alive (creates it if it is not)

		const char* const m_Name; // Cannot change after initialization
		Fire::Window* m_pMainWindow;
	};
}