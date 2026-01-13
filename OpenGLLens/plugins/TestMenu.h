#pragma once

#include "BaseLensPlugins.h"

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <iostream>

namespace OpenGLLens
{
	class TestMenu : public BaseLensPlugins
	{
	public:
		TestMenu(BaseLensPlugins* & currentTestPointer);

		void onImGuiRender() override;

		void onRender(const DrawContext* drawContext) override;

		template<typename T>
		void registerTest(const std::string& name)
		{
			//std::cout << "Registering test: " << name << std::endl;	
			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		BaseLensPlugins*& m_currentTestPointer;
		std::vector<std::pair<std::string, std::function<BaseLensPlugins* ()>>> m_tests;
	};
}


