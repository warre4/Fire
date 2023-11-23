
#include "utils.h"

#include "general.h"

#include <SDL3/SDL_messagebox.h>

void Fire::Utils::ShowMessageBoxError(const char* title, const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
}
void Fire::Utils::ShowMessageBoxInfo(const char* title, const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, NULL);
}