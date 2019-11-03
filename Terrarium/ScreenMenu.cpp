#include "ScreenMenu.hpp"

terr::ScreenMenu::ScreenMenu(sf::String name): Screen(name)
{
}

terr::ScreenMenu::~ScreenMenu()
{
	for (std::vector<UIElement*>::size_type i = 0; i < m_elements.size(); ++i)
	{
		delete m_elements[i];
	}
}

void terr::ScreenMenu::setup(Game* game)
{
	m_middle = game->getWindowPtr()->getSize().x / 2;
}

void terr::ScreenMenu::draw(sf::RenderWindow& window)
{
	const unsigned int middle_x = window.getSize().x / 2;

	for (std::vector<UIElement*>::size_type i = 0; i < m_elements.size(); ++i)
	{
		window.draw(*m_elements[i]);
	}
}

terr::UIElement* terr::ScreenMenu::AddElement(UIElement* elem)
{
	//TODO: Œrednio podoba mi siê taki zapis liczenia y, warto kiedyœ poprawiæ
	//pozycjonuj po œrodku
	const int H = 40; //wysokoœæ + margines pozycji w menu
	auto s = elem->getSize();
	int y = m_first_button_offset + m_elements.size() * H;
	elem->setPosition(m_middle - s.x / 2, y);
	m_elements.push_back(elem);

	return elem;
}
