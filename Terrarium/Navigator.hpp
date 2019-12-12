#pragma once

#include <stack>

#include "Screen.hpp"

namespace terr {
	class Navigator
	{
	public:
		Navigator() {};

		void goBack();
		void setScreen(ScreenReference screen, bool replace);		
		ScreenReference &getScreen();
		
	private:
		std::stack<ScreenReference> screens;
	};

}