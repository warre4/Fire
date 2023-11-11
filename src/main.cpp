
#include "Fire.h"

#include <SDL3/SDL.h>

#include <fstream>




CREATE_APPLICATION_CLASS(Sandbox, "Sandbox");

void Sandbox::Initialize()
{
	LOGI(GetName() + " initializing");
}

void Sandbox::Cleanup()
{
	LOGI(GetName() + " cleaning up");
}



//CREATE_APPLICATION_CLASS(MyOtherApp, "MyOtherApp");
//
//void MyOtherApp::Initialize()
//{
//	LOGI(GetName() + " initializing");
//}
//
//void MyOtherApp::Cleanup()
//{
//	LOGI(GetName() + " cleaning up");
//}




int main(int /*argc*/, char** /*argv*/)
{
#ifdef _DEBUG
	try
	{
#endif

		// testing logging macros
		LOG_SET_COLOR(LOG_COLOR_MAGENTA);
		LOGRAW("Text without pre or post fix, will not automatically go to the next line");
		LOG_EMPTY_LINE(); // manual enter

		LOGT("Example trace message");
		LOGD("Example debug message");
		LOGI("Example info message");
		LOGWARN("Example info message");
		LOGERROR("Example error message");
		LOGCRITICAL("Example critical error message");

		LOG_EMPTY_LINE();


		// Test Application
		_F Application* pApp = _F CreateApplication<Sandbox>();
		//_F Application* pApp2 = _F CreateApplication<MyOtherApp>();

		pApp->Run();
		//pApp2->Run();

		_F DestroyApplication(pApp);
		//_F DestroyApplication(pApp2);


		
		/*
		// read and print delete_me.txt
		LOG_EMPTY_LINE();
		LOG_EMPTY_LINE();

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
			LOGRAW(temp);
		}
		temp = '\n';
		LOGRAW(temp);

		LOG_EMPTY_LINE();
		LOGT("----------------------------");

		ifstream.close();

		LOG_EMPTY_LINE();
		LOG_EMPTY_LINE();
		*/
		
		// end of program
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