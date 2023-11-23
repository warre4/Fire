#pragma once
#include "api.h"

#include "stl_containers.h"

namespace Fire
{
	namespace Utils
	{
		inline void FAPI ShowMessageBoxError(const char* title, const char* message);
		inline void FAPI ShowMessageBoxInfo(const char* title, const char* message);
	}
}