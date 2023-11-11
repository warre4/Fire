#pragma once

// For use by Confused applications
#include "general.h"
#include "application.h"

// Override `Initialize()` and `Cleanup()` after calling this macro to implement your own application
#define CREATE_APPLICATION(appName, appNameStr)					\
class appName final : public _F Application						\
{																\
	public:														\
		appName() : _F Application(appNameStr) {}				\
																\
		virtual ~appName() = default;							\
		appName(const appName& other) = delete;					\
		appName(appName&& other) noexcept = delete;				\
		appName& operator=(const appName& other) = delete;		\
		appName& operator=(appName&& other) noexcept = delete;	\
	private:													\
		void Initialize() override;								\
		void Cleanup() override;								\
};

// functions for app creation and destruction
namespace Fire
{
	template <typename T>
	concept DerivedFromApplication = std::is_base_of<_F Application, T>::value;

	// You should call DestroyApplication() as well
	template <DerivedFromApplication T>
	[[nodiscard]] _F Application* CreateApplication()
	{
		_F Application* pApp = new T();
		LOGD(pApp->GetName() + STR(" allocated in memory"));
		return pApp;
	}
	void DestroyApplication(_F Application*& pApp)
	{
		std::string internalApplicationName = pApp->GetName();
		SAFE_DELETE(pApp);
		LOGD(internalApplicationName + STR(" released from memory"));
	}
}