#pragma once

#include <stack>

#include "Screen.hpp"

namespace terr {
	class Navigator
	{
	public:
		Navigator();
		~Navigator() {};

		void goBack();
		void setScreen(Screen &screen, bool replace);		
		Screen &getScreen();
		
	private:
		std::stack<Screen> screens;
	};

}