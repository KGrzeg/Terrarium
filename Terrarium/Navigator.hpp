#pragma once

#include <stack>

#include "Screen.hpp"

namespace terr {
	enum Action
	{
		None,
		GoBack,
		Push,
		Set
	};
	
	class Navigator
	{
	public:
		Navigator() {};

		void update();
		void goBack();
		void setScreen(ScreenReference screen);
		void pushScreen(ScreenReference screen);
		ScreenReference &getScreen();
		
	private:
		std::stack<ScreenReference> screens;
		Action next_action = None;
		ScreenReference next_screen;
	};

}