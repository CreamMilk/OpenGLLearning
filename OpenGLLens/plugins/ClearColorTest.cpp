#include "ClearColorTest.h"

#include "imgui.h"

#include <GL/glew.h>

#include <iostream>

namespace OpenGLLens
{
	ClearColorTest::ClearColorTest()
		:m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}

	ClearColorTest::~ClearColorTest()
	{

	}

	void ClearColorTest::onUpdate(float delaTime)
	{

	}

	void ClearColorTest::onRender()
	{ 

		glClearColor(m_ClearColor[0]
			, m_ClearColor[1]
			, m_ClearColor[2]
			, m_ClearColor[3]);

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ClearColorTest::onImGuiRender()
	{
		ImGui::Begin("ClearColorWindow");
		ImGui::ColorEdit4("clear color", (float*)&m_ClearColor);
		ImGui::End();
	}
}