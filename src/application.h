#pragma once
#include <string>

namespace Fire
{
	class Window;
	class Core;
}

// DO NOT INCLUDE core.h IN THIS FILE

namespace Fire
{
	class Application
	{
	public:
		Application(std::string name);

		virtual ~Application() = default;
		Application(const Application& other) = delete;
		Application(Application&& other) noexcept = delete;
		Application& operator=(const Application& other) = delete;
		Application& operator=(Application&& other) noexcept = delete;

		void Run();

		// Helpers
		[[nodiscard]] inline const std::string& GetName() const noexcept { return m_Name; }

	protected:
		virtual void Initialize() = 0;
		virtual void Cleanup() = 0;

	private:
		friend Fire::Core; // access to `InitializeCore()`

		void InitializeBase();
		void CleanupBase();
		void InitializeCore(); // Makes sure that the core is alive (creates it if it is not)

		std::string m_Name;
		Fire::Window* m_pMainWindow;
	};
}