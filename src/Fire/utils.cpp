
#include "utils.h"

#include "general.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#pragma warning(push)
#pragma warning(disable : 26451 5045 6262 26819) // the `/external:W0` compilerflag is not working on this library
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#pragma warning(pop)
#include <SDL3/SDL_messagebox.h>

void Fire::Utils::ShowMessageBoxError(const char* title, const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
}
void Fire::Utils::ShowMessageBoxInfo(const char* title, const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, NULL);
}

Fire::Image Fire::Utils::CreateImage(const char* path)
{
	Fire::Image image;
	image.pData = stbi_load(path, &image.width, &image.height, NULL, 4); //rgba

	return image;
}

void Fire::Utils::DestroyImage(Image& image)
{
	stbi_image_free(image.pData);
}