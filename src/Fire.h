#pragma once
// ===============================================================
// When a project is created:
// ---------------------------------------------------------------
// 1) #include "Fire.h"
// 2) call CREATE_APPLICATION_CLASS(), then SET_MAIN_APPLICATION()
// 
// note: You can create multiple application classes and you can run as many applications as you want,
//       but there has to be a root application that is automatically created and ran by the engine.
//       The root application is defined by calling SET_MAIN_APPLICATION.
// 
//       running an application looks like this:
//       
//       Fire::Application* pApp = Fire::CreateApplication<ApplicationClass>();
//       pApp->Run();
//       Fire::DestroyApplication(pApp);
// 
// note: This code will be removed once there is a test project that calls this code
// 
// ===============================================================

#include "Fire/entrypoint.h"
#include "Fire/application.h"
#include "Fire/general.h"


// Overriding `Initialize()` and `Cleanup()` is required
#define CREATE_APPLICATION_CLASS(appName, appNameStr)          \
class appName final : public Fire::Application                 \
{                                                              \
	public:                                                    \
		appName() : Fire::Application(appNameStr) {}           \
                                                               \
		virtual ~appName() = default;                          \
		appName(const appName& other) = delete;                \
		appName(appName&& other) noexcept = delete;            \
		appName& operator=(const appName& other) = delete;     \
		appName& operator=(appName&& other) noexcept = delete; \
	private:                                                   \
		void Initialize() override;                            \
		void Cleanup() override;                               \
};

// An instance of `ApplicationClass` will be created and run automatically
#define SET_MAIN_APPLICATION(ApplicationClass)                 \
Fire::Application* Fire::CreateMainApplication()               \
{                                                              \
	return Fire::CreateApplication<ApplicationClass>();        \
}