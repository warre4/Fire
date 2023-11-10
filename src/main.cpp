
#include "general.h"
#include "window.h"
#include "use_imgui.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <SDL_messagebox.h>


int main()
{
#ifdef _DEBUG
	try
	{
#endif

		// create window and update it until user closes it (TODO: WindowManager class)
		glfwInit();
#pragma warning(push)
#pragma warning(disable : 5039) // 'function': pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavior may occur if this function throws an exception.
		glfwSetErrorCallback(Fire::Window::GlfwErrorCallback);
#pragma warning(pop)

		Fire::Window* pWindow = new Fire::Window{ Fire::WindowProps("Fire Engine! :D", 1920, 1080, true)};

		while (!pWindow->GetShouldClose())
		{
			pWindow->Update();
		}

		SAFE_DELETE(pWindow);

		glfwTerminate();






		// read and print delete_me.txt
		std::ifstream ifstream;

		ifstream.open(RESOURCES_PATH "delete_me.txt");

		if (!ifstream.is_open())
		{
			std::cerr << "ERROR: could not open file!\n";
		}

		std::cout << "Contents of `delete_me.txt`:\n";
		std::cout << "----------------------------\n";

		char temp;
		while (ifstream.get(temp))
		{
			std::cout << temp;
		}
		std::cout << "\n";
		ifstream.close();

		std::cout << "----------------------------\n";
		// end of read and print delete_me.txt

		std::cout << "\n\nprogram terminated, press enter to quit\n";
		std::cin.get();

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