#include "UIGrid.hpp"
#include "Button.hpp"


namespace terr {

	void UIGrid::update(sf::Time time)
	{
		for (auto &element : elements)
		{
			element.second->update(time);

			clicked_btn = "none";
			if (auto btn = dynamic_cast<Button*>(element.second.get()))
			{
				if (btn->is_clicked())
					clicked_btn = element.first;
			}
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

}
