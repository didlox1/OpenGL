#pragma once
#include <functional>

namespace test {
	
	class Test {
	public:
		Test() {};
		virtual ~Test() {};
		virtual void OnImGuiRender() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender() {};
	};
}