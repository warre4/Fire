#pragma once

#include <imgui.h>

namespace Fire
{
	class UseImgui
	{
	public:
		UseImgui() = default;
		virtual ~UseImgui() {}

		void Init();
		void ShutDown();

		void Update();
		void Render() const;

	private:

	};
}