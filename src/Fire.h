#pragma once

// For use by Confused applications
#include "general.h"
#include "application.h"

// Overriding `Initialize()` and `Cleanup()` is required
#define CREATE_APPLICATION_CLASS(appName, appNameStr)			\
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
	concept ConceptDerivedFromApplication = std::is_base_of<_F Application, T>::value;

	// You should call DestroyApplication() as well
	template <ConceptDerivedFromApplication T>
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