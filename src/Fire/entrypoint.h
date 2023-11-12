
#include "general.h"
#include "application.h"

#include <SDL3/SDL_messagebox.h>


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

	[[nodiscard]] extern inline _F Application* CreateMainApplication();
}

int main(int /*argc*/, char** /*argv*/)
{
#ifdef _DEBUG
	try
	{
#endif
		_F Application* pApp = _F CreateMainApplication();

		pApp->Run();

		_F DestroyApplication(pApp);

		// end of program
		LOG_EMPTY_LINE();
		LOGI("program terminated");
		

#ifdef _DEBUG
	}
	catch (std::exception& e)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Exception", e.what(), NULL);
		return EXIT_FAILURE;
	}
	catch (...)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Exception", "Exception of an undetermined type", NULL);
		return EXIT_FAILURE;
	}
#endif

	return EXIT_SUCCESS;
}