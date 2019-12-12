#include <string>
#include "ScreenNewGame.hpp"
#include "ScreenPlay.hpp"
#include "Label.hpp"

namespace terr
{

	ScreenNewGame::ScreenNewGame(GlobalReference global) :
		global(global)/*,
		title(global, L"Nowa gra"),
		world_name_lbl(global, L"Nazwa swiata"),
		resources_lbl(global, L"Poziom zasob�w:"),
		btn_start(global, L"Start"),
		btn_back(global, L"Wstecz")*/
	{

		const float margin_lbl_ctr = 10.f;
		const auto window_size = global->window.getSize();

		auto title = new Label(global, L"Nowa gra");
		auto world_name_lbl = new Label(global, L"Nazwa swiata");
		auto resources_lbl = new Label(global, L"Poziom zasob�w:");

		auto btn_start = new Button(global, L"Start");
		auto btn_back = new Button(global, L"Wstecz");

		title->get_text().setCharacterSize(90);
		title->get_text().setPosition((window_size.x - title->get_text().getLocalBounds().width) / 2, 50);
		world_name_lbl->get_text().setPosition(60, 300);
		resources_lbl->get_text().setPosition(60, 380);

		m_background_rectangle.setSize(sf::Vector2f(window_size.x, window_size.y));
		m_background_rectangle.setTexture(&global->assets.getTexture("menu/background"));

		btn_start->get_text().setPosition((window_size.x - btn_start->get_text().getLocalBounds().width) / 2, window_size.y - 120);
		btn_back->setPosition((window_size.x - btn_back->get_text().getLocalBounds().width) / 2, window_size.y - 60);


		grid.add_element("title_lbl", UIElementReference(title));
		grid.add_element("worldname_lbl", UIElementReference(world_name_lbl));
		grid.add_element("resources_lbl", UIElementReference(resources_lbl));

		grid.add_element("start", UIElementReference(btn_start));
		grid.add_element("back", UIElementReference(btn_back));
	}

	void ScreenNewGame::draw(sf::Time time)
	{
		auto &window = global->window;

		window.clear();

		window.draw(m_background_rectangle);

		window.draw(grid);

		/*
		window.draw(title);
		window.draw(world_name_lbl);
		window.draw(resources_lbl);

		window.draw(btn_start);
		window.draw(btn_back);*/

		window.display();

	}
	void ScreenNewGame::update(sf::Time time)
	{
		grid.update(time);

		auto clck_btn = grid.clicked_button();
		if (clck_btn == "start")
		{
			WorldSettings settings;
			settings.width = 50;
			settings.height = 40;

			global->navigator.pushScreen(ScreenReference(new ScreenPlay(global, settings)));
		}
		if (clck_btn == "back")
		{
			global->navigator.goBack();
		}

		/*if (btn_start.is_clicked())
		{
			WorldSettings settings;
			settings.width = 50;
			settings.height = 40;

			global->navigator.pushScreen(ScreenReference(new ScreenPlay(global, settings)));
		}
		if (btn_back.is_clicked())
		{
			global->navigator.goBack();
		}

		btn_start.update(time);
		btn_back.update(time);*/
	}

	void ScreenNewGame::handle_input()
	{
		sf::Event event;
		while (global->window.pollEvent(event))
		{
			grid.handle_event(event);
			/*btn_start.handle_event(event);
			btn_back.handle_event(event);*/
		}
	}



}

