#pragma once
#include "typedefs.h"

namespace Fire
{
	struct Image
	{
		Byte* pData = nullptr;
		int width = 0;
		int height = 0;
	};

	struct MemoryChunk
	{
		Byte* pData = nullptr;
		uint16_t size = 0;
	};
}