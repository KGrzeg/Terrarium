#include "UIGrid.hpp"
#include "Button.hpp"


namespace terr {

	void UIGrid::update(sf::Time time)
	{
		clicked_btn = UNSET_KEY;
		for (auto &element : elements)
		{
			if (auto btn = dynamic_cast<Button*>(element.second.get()))
			{
				if (btn->is_clicked())
					clicked_btn = element.first;
			}
			element.second->update(time);
		}
	}

	void UIGrid::add_element(std::string key, UIElementReference element)
	{
		if (elements.find(key) == elements.end())
			elements[key] = std::move(element);
	}

	UIElementReference& UIGrid::get_element(std::string key)
	{
		return elements[key];
	}


	void UIGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto &element : elements)
		{
			target.draw(*element.second);
		}
	}
	void UIGrid::handle_event(sf::Event& event)
	{
		for (auto &element : elements)
		{
			element.second->handle_event(event);
		}
	}


}
