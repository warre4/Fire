
#include "window.h"
#include "use_imgui.h"
#include "Fire.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <SDL_messagebox.h>




CREATE_APPLICATION(Sandbox, "Sandbox");

void Sandbox::Initialize()
{
	LOGI(GetName() + " initializing");
}

void Sandbox::Cleanup()
{
	LOGI(GetName() + " cleaning up");
}



CREATE_APPLICATION(MyOtherApp, "MyOtherApp");

void MyOtherApp::Initialize()
{
	LOGI(GetName() + " initializing");
}

void MyOtherApp::Cleanup()
{
	LOGI(GetName() + " cleaning up");
}




int main(int /*argc*/, char** /*argv*/)
{
#ifdef _DEBUG
	try
	{
#endif

		// Test Application
		_F Application* pApp = _F CreateApplication<Sandbox>();
		_F Application* pApp2 = _F CreateApplication<MyOtherApp>();

		pApp->Run();
		pApp2->Run();

		_F DestroyApplication(pApp);
		_F DestroyApplication(pApp2);


		/*
		// read and print delete_me.txt
		std::ifstream ifstream;

		ifstream.open(RESOURCES_PATH "delete_me.txt");

		if (!ifstream.is_open())
		{
			LOGWARN("ERROR: could not open file!");
		}

		LOGT("Contents of `delete_me.txt`:");
		LOGT("----------------------------");
		LOG_EMPTY_LINE();

		char temp;
		while (ifstream.get(temp))
		{
			LOG_RAW(temp);
		}
		temp = '\n';
		LOG_RAW(temp);

		LOG_EMPTY_LINE();
		LOGT("----------------------------");

		ifstream.close();

		LOG_EMPTY_LINE();
		
		
		// end of program
		LOGI("program terminated");
		*/

#if _DEBUG
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