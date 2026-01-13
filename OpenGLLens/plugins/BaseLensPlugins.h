#pragma once

#include "DrawContext.h"

namespace OpenGLLens
{
	class BaseLensPlugins
	{
	public:
		BaseLensPlugins() {}
		virtual ~BaseLensPlugins() {}

		virtual void onUpdate(float delaTime) {}
		virtual void onRender(const DrawContext* drawContext) {}
		virtual void onImGuiRender() {}
	};
}