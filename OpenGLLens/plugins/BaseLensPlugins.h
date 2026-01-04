#pragma once

namespace OpenGLLens
{
	class BaseLensPlugins
	{
	public:
		BaseLensPlugins() {}
		virtual ~BaseLensPlugins() {}

		virtual void onUpdate(float delaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};
}