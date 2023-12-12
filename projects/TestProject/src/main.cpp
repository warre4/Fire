
#include "Fire.h"

#include <fstream>

CREATE_APPLICATION_CLASS(TestProject, "TestProject",
	_F Window* m_pExtraWindow = nullptr;
	);
SET_MAIN_APPLICATION(TestProject)

void TestProject::Initialize()
{

	//LOGI(GetName() + " initializing, hello! :D");

	GetWindow()->SetTitle("This is a custom title :D");

	bool shouldTestLogging = false;
	bool shouldPrintTextFile = false;

	if (shouldTestLogging)
	{
		// testing logging macros
		LOG_EMPTY_LINE();

		LOGT("---------------------");
		LOGT("-- Testing logging --");
		LOGT("---------------------");

		LOG_SET_COLOR(LOG_COLOR_MAGENTA);
		LOGRAW("Example raw message, this is text without pre or post fix, it will not automatically go to the next line either");
		LOG_EMPTY_LINE(); // manual enter

		LOGT("Example trace message");
		LOGD("Example debug message");
		LOGI("Example info message");
		LOGWARN("Example info message");
		LOGERROR("Example error message");
		LOGCRITICAL("Example critical error message");

		LOGT("---------------------");

		LOG_EMPTY_LINE();
	}
	if (shouldPrintTextFile)
	{
		// read and print delete_me.txt
		LOG_EMPTY_LINE();

		std::ifstream ifstream;

		ifstream.open(FENGINE_RESOURCES_PATH "delete_me.txt");

		if (!ifstream.is_open())
		{
			LOGWARN("ERROR: could not open file!");
		}

		LOGT("------------------------------");
		LOGT("-- printing `delete_me.txt` --");
		LOGT("------------------------------");
		LOG_EMPTY_LINE();

		char temp;
		while (ifstream.get(temp))
		{
			LOGRAW(temp);
		}
		temp = '\n';
		LOGRAW(temp);

		LOG_EMPTY_LINE();
		LOGT("------------------------------");

		ifstream.close();

		LOG_EMPTY_LINE();
	}

	m_pExtraWindow = new _F Window(_F WindowProps(400, 200), "another window :D");
}

void TestProject::Cleanup()
{
	SAFE_DELETE(m_pExtraWindow);

	_F_UTILS ShowMessageBoxInfo(GetName(), "Bye bye :D");
}