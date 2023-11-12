#pragma once
#include "api.h"

namespace Fire
{
	class FAPI UseImgui
	{
	public:
		UseImgui() = default;
		virtual ~UseImgui() {}

		UseImgui(const UseImgui& other) = delete;
		UseImgui(UseImgui&& other) noexcept = delete;
		UseImgui& operator=(const UseImgui& other) = delete;
		UseImgui& operator=(UseImgui&& other) noexcept = delete;

		void Init();
		void ShutDown();

		void Update();
		void Render() const;

	private:
		bool InitVulkan();
	};
}