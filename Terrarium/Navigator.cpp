#include "Navigator.hpp"

namespace terr {
	void Navigator::goBack()
	{
		screens.pop();
	}
	void Navigator::setScreen(ScreenReference screen, bool replace)
	{
		if (replace)
		{
			screens.pop();
		}
		screens.push(std::move(screen));
	}

	ScreenReference& Navigator::getScreen()
	{
		return screens.top();
	}

}