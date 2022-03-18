#pragma once
#include "Test.h"

namespace test {

	class TestClearColor
		:Test
	{
	private:
		float m_ClearColor[4];
	public:
		TestClearColor();
		~TestClearColor();
		void OnImGuiRender() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
	};

}