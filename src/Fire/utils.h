#pragma once
#include "api.h"

#include "general.h"
#include "structs.h"
#include "stl_containers.h"

namespace Fire
{
	namespace Utils
	{
		inline void FAPI ShowMessageBoxError(const char* title, const char* message);
		inline void FAPI ShowMessageBoxInfo(const char* title, const char* message);

		// Call `DestroyImage(Image& image)` before the image goes out of scope!
		[[nodiscard]] Image FAPI CreateImage(const char* path);
		void FAPI DestroyImage(Image& image);
	}
}