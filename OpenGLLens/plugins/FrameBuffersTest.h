#pragma once

#include "BaseLensPlugins.h"
#include "Shader.h"
#include "FrameBufferObject.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace OpenGLLens
{
	class FrameBuffersTest : public OpenGLLens::BaseLensPlugins
	{
	public:
		FrameBuffersTest();
		~FrameBuffersTest();

		void onUpdate(float delaTime) override;
		void onRender(const DrawContext* drawContext) override;
		void onImGuiRender() override;

	private:

		unsigned int loadTexture(const char* path);

		// 默认值 都应该为0 
		//unsigned int cubeVAO, cubeVBO;
		//unsigned int planeVAO, planeVBO;
		//unsigned int quadVAO, quadVBO;
		//unsigned int framebuffer;
		//unsigned int textureColorbuffer;
		//unsigned int rbo;
		unsigned int cubeTexture;
		unsigned int floorTexture;

		std::shared_ptr<Shader> cubeShader;
		std::shared_ptr<Shader> screenShader;
		std::shared_ptr<FrameBufferObject> m_frameBufferObject;

		std::shared_ptr<VertexArray> m_cubeVAO;
		std::shared_ptr<VertexArray> m_planeVAO;
		std::shared_ptr<VertexArray> m_quadVAO;

		std::shared_ptr<VertexBuffer> m_cubeVBO;
		std::shared_ptr<VertexBuffer> m_planeVBO;
		std::shared_ptr<VertexBuffer> m_quadVBO;

		bool m_initialized = false;
		unsigned int m_screenWidth;
		unsigned int m_screenHeight;

	};
}