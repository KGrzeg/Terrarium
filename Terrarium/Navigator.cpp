#include "Navigator.hpp"

namespace terr {
	Navigator::Navigator()
	{
	}

	void Navigator::goBack()
	{
		screens.pop();
	}
	void Navigator::setScreen(Screen &screen, bool replace)
	{
		if (replace)
		{
			screens.pop();
		}
		screens.push(screen);
	}

	Screen& Navigator::getScreen()
	{
		return screens.top();
	}

}