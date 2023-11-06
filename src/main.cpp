
#include <iostream>
#include <fstream>
#include <string>

#include <SDL3/SDL.h>

#include "use_imgui.h"


void PrintKeyInfo(SDL_KeyboardEvent* key)
{
	printf("Scancode: 0x%02X", key->keysym.scancode);
	printf(", Name: %s\n", SDL_GetKeyName(key->keysym.sym));
}

int main()
{
	Fire::UseImgui ui{};

	ui.Init();

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

	ui.ShutDown();

	std::cout << "\n\nprogram terminated, press enter to quit\n";
	std::cin.get();

	return 0;
}