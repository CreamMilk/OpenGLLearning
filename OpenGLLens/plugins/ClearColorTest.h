#pragma once


#include "BaseLensPlugins.h"

namespace OpenGLLens
{
	class ClearColorTest : public BaseLensPlugins
	{
	public:
		ClearColorTest();
		~ClearColorTest();

		void onUpdate(float delaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:

		float m_ClearColor[4];
	};
}


