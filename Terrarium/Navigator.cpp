#include "Navigator.hpp"

namespace terr {
	void Navigator::goBack()
	{
		next_action = GoBack;
	}
	void Navigator::pushScreen(ScreenReference screen)
	{
		next_action = Push;
		next_screen = std::move(screen);
	}

	void Navigator::setScreen(ScreenReference screen)
	{
		next_action = Set;
		next_screen = std::move(screen);
	}

	ScreenReference& Navigator::getScreen()
	{
		return screens.top();
	}

	void Navigator::update()
	{
		switch (next_action)
		{
		case None:
		{
			return;
			break;
		}
		case GoBack:
		{
			if (!screens.empty()) {
				getScreen()->pause();
				screens.pop();
			}
			getScreen()->resume();
			next_action = None;
			break;
		}
		case Push:
		{
			if (!screens.empty())
				getScreen()->pause();

			screens.push(std::move(next_screen));
			next_action = None;
			break;
		}
		case Set:
		{
			if (!screens.empty()) {
				getScreen()->pause();
				screens.pop();
			}
			screens.push(std::move(next_screen));
			break;
		}
		}
	}


}