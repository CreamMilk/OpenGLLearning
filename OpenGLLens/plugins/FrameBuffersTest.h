#pragma once

#include "BaseLensPlugins.h"
#include "Shader.h"


namespace OpenGLLens
{
	class FrameBuffersTest : public OpenGLLens::BaseLensPlugins
	{
	public:
		FrameBuffersTest();
		~FrameBuffersTest();

		void onUpdate(float delaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:

		unsigned int loadTexture(const char* path);

		// 默认值 都应该为0 
		unsigned int cubeVAO, cubeVBO;
		unsigned int planeVAO, planeVBO;
		unsigned int quadVAO, quadVBO;
		unsigned int framebuffer;
		unsigned int textureColorbuffer;
		unsigned int rbo;
		unsigned int cubeTexture;
		unsigned int floorTexture;

		std::shared_ptr<Shader> cubeShader;
		std::shared_ptr<Shader> screenShader;
	};
}