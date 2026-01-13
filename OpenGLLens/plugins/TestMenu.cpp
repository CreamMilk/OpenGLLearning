#include "TestMenu.h"
#include <imgui.h>
#include <glad/glad.h>

namespace OpenGLLens
{
	TestMenu::TestMenu(BaseLensPlugins*& currentTestPointer)
		:m_currentTestPointer(currentTestPointer)
	{

	}

	void TestMenu::onRender(const DrawContext* drawContext)
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestMenu::onImGuiRender()
	{
		for(auto & test : m_tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				//std::cout << "Switching to test: " << test.first << std::endl;
				m_currentTestPointer = test.second();
			}
		}
	}
}
