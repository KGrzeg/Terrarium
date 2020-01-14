#include <string>
#include "ScreenNewGame.hpp"
#include "ScreenPlay.hpp"
#include "Label.hpp"

namespace terr
{
	ScreenNewGame::ScreenNewGame(GlobalReference global) :
		global(global)
	{
		const float margin_lbl_ctr = 10.f;
		const auto window_size = global->window.getSize();

		auto title = new Label(global, "Nowa gra");
		auto world_name_lbl = new Label(global, "Nazwa swiata");
		auto resources_lbl = new Label(global, "Poziom trudnosci:");
		auto dimension_lbl = new Label(global, "Rozmiar swiata:");

		lbl_name = new Label(global, "Polanka");
		lbl_difficulty = new Label(global, "Normalny");
		lbl_dimension = new Label(global, "320x120");

		auto btn_start = new Button(global, "Start");
		auto btn_back = new Button(global, "Wstecz");

		title->get_text().setCharacterSize(90);
		title->get_text().setPosition((window_size.x - title->get_text().getLocalBounds().width) / 2, 50);
		world_name_lbl->get_text().setPosition(60, 200);
		resources_lbl->get_text().setPosition(60, 260);
		dimension_lbl->get_text().setPosition(60, 320);

		lbl_name->get_text().setPosition(370, 200);
		lbl_difficulty->get_text().setPosition(370, 260);
		lbl_dimension->get_text().setPosition(370, 320);

		m_background_rectangle.setSize(sf::Vector2f(window_size.x, window_size.y));
		m_background_rectangle.setTexture(&global->assets.getTexture("menu/background"));

		btn_start->get_text().setPosition((window_size.x - btn_start->get_text().getLocalBounds().width) / 2, window_size.y - 120);
		btn_back->setPosition((window_size.x - btn_back->get_text().getLocalBounds().width) / 2, window_size.y - 60);

		grid.add_element("title", UIElementReference(title));
		grid.add_element("worldname", UIElementReference(world_name_lbl));
		grid.add_element("resources", UIElementReference(resources_lbl));
		grid.add_element("dimension", UIElementReference(dimension_lbl));

		grid.add_element("name_val", UIElementReference(lbl_name));
		grid.add_element("difficulty_val", UIElementReference(lbl_difficulty));
		grid.add_element("dimension_val", UIElementReference(lbl_dimension));

		grid.add_element("start", UIElementReference(btn_start));
		grid.add_element("back", UIElementReference(btn_back));

		setup_maps();
		select_map(0);

		for (size_t i = 0; i < DEFINED_MAPS; i++)
		{
			auto btn = new Button(global, map_definitions[i].name);
			btn->setPosition(900, 200 + i * 60);
			grid.add_element(std::to_string(i), UIElementReference(btn));
		}
	}

	ScreenNewGame::~ScreenNewGame()
	{
		delete lbl_name, lbl_difficulty, lbl_dimension;
	}

	void ScreenNewGame::draw(sf::Time time)
	{
		auto& window = global->window;

		window.clear();

		window.draw(m_background_rectangle);
		window.draw(grid);

		window.display();

	}
	void ScreenNewGame::update(sf::Time time)
	{
		grid.update(time);

		auto clck_btn = grid.clicked_button();
		if (clck_btn == "start")
		{
			global->navigator.pushScreen(
				ScreenReference(
					new ScreenPlay(global, map_definitions[selected_map])
				)
			);
		}
		if (clck_btn == "back")
		{
			global->navigator.goBack();
		}
		if (clck_btn.length() == 1) {
			int id = std::stoi(clck_btn);
			select_map(id);
		}
	}

	void ScreenNewGame::handle_input()
	{
		sf::Event event;
		while (global->window.pollEvent(event))
		{
			grid.handle_event(event);
		}
	}

	void ScreenNewGame::setup_maps()
	{
		int q = 0, w;
		map_definitions[q].name = "Kopalnia";
		map_definitions[q].difficulty = "Latwy";
		map_definitions[q].default_power = 2;

		map_definitions[q].gravity = 385;
		map_definitions[q].width = 150;
		map_definitions[q].height = 150;

		map_definitions[q].background_texture_name = "game/skyBlue";

		map_definitions[q].player_x = 60;
		map_definitions[q].player_y = 10;
		map_definitions[q].initial_time = 300;

		w = 0;
		map_definitions[q].layers[w] = { 45, 3, TILE_STONE, 24.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 50, 2, TILE_STONE, 24.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 60, 10, TILE_COAL, 4.f, 0.25f, true };
		map_definitions[q].layers[++w] = { 70, 20, TILE_IRON, 12.f, 0.55f, true };
		map_definitions[q].layers[++w] = { 90, 20, TILE_GOLD, 5.f, 0.55f, true };
		map_definitions[q].layers[++w] = { 130, 20, TILE_EMERALD, 4.f, 0.8f, true };
		map_definitions[q].layers[++w] = { 140, 5, TILE_EMERALD, 0.3f, 0.5f, true };
		map_definitions[q].layers[++w] = { 120, 25, TILE_AIR, 15.f, 0.5f, true };
		map_definitions[q].layers[++w] = { 147, 2, TILE_DIAMOND, -0.1f, 0.995f, true };
		++q; w = 0;


		map_definitions[q].name = "Pustynia";
		map_definitions[q].difficulty = "Latwy";

		map_definitions[q].gravity = 385;
		map_definitions[q].width = 150;
		map_definitions[q].height = 150;

		map_definitions[q].background_texture_name = "game/skyYellow";

		map_definitions[q].player_x = 60;
		map_definitions[q].player_y = 10;
		map_definitions[q].initial_time = 300;

		map_definitions[q].layers[w] = { 45, 9, TILE_SAND, 14.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 55, 9, TILE_STONE, 24.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 60, 10, TILE_COAL, 4.f, 0.25f, true };
		map_definitions[q].layers[++w] = { 70, 20, TILE_IRON, 12.f, 0.55f, true };
		map_definitions[q].layers[++w] = { 90, 20, TILE_GOLD, 5.f, 0.55f, true };
		map_definitions[q].layers[++w] = { 130, 20, TILE_EMERALD, 4.f, 0.8f, true };
		map_definitions[q].layers[++w] = { 140, 5, TILE_EMERALD, 0.3f, 0.5f, true };
		map_definitions[q].layers[++w] = { 120, 25, TILE_AIR, 15.f, 0.5f, true };
		map_definitions[q].layers[++w] = { 147, 2, TILE_DIAMOND, -0.1f, 0.995f, true };
		++q; w = 0;


		map_definitions[q].name = "Ksiezyc";
		map_definitions[q].difficulty = "Sredni";

		map_definitions[q].gravity = 90;
		map_definitions[q].width = 250;
		map_definitions[q].height = 250;

		map_definitions[q].background_texture_name = "game/skySpace";

		map_definitions[q].player_x = 150;
		map_definitions[q].player_y = 10;
		map_definitions[q].initial_time = 300;

		map_definitions[q].layers[w] = { 45, 10, TILE_MOON_TORF, 0.05f, 0.1f, true };
		map_definitions[q].layers[++w] = { 46, 9, TILE_MOON_ROCK, 14.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 60, 10, TILE_MOON_COAL, 2.f, 0.55f, true };
		map_definitions[q].layers[++w] = { 90, 20, TILE_MOON_IRON, 12.f, 0.75f, true };
		map_definitions[q].layers[++w] = { 120, 20, TILE_MOON_GOLD, 3.f, 0.85f, true };
		map_definitions[q].layers[++w] = { 170, 20, TILE_MOON_EMERALD, 5.f, 0.9f, true };
		map_definitions[q].layers[++w] = { 190, 5, TILE_MOON_EMERALD, 0.3f, 0.95f, true };
		map_definitions[q].layers[++w] = { 200, 50, TILE_OBSIDIAN, 0.1f, 0.95f, true };
		map_definitions[q].layers[++w] = { 197, 2, TILE_DIAMOND, -0.1f, 0.995f, true };
		++q; w = 0;


		map_definitions[q].name = "Polana";
		map_definitions[q].difficulty = "Trudny";

		map_definitions[q].gravity = 385;
		map_definitions[q].width = 700;
		map_definitions[q].height = 300;

		map_definitions[q].background_texture_name = "game/skyBlue";

		map_definitions[q].player_x = 350;
		map_definitions[q].player_y = 10;
		map_definitions[q].initial_time = 60;

		map_definitions[q].layers[w] = { 45, 9, TILE_GRASS, 14.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 65, 8, TILE_DIRT, 14.1f, -2.f, true };
		map_definitions[q].layers[++w] = { 90, 16, TILE_STONE, 11.2f, -2.f, true };
		map_definitions[q].layers[++w] = { 80, 8, TILE_STONE, 4.f, 0.45f, true };
		map_definitions[q].layers[++w] = { 80, 8, TILE_COAL, 4.f, 0.75f, true };
		map_definitions[q].layers[++w] = { 125, 20, TILE_STONE, 12.f, 0.65f, true };
		map_definitions[q].layers[++w] = { 125, 20, TILE_IRON, 12.f, 0.75f, true };
		map_definitions[q].layers[++w] = { 190, 8, TILE_STONE, 4.f, 0.55f, true };
		map_definitions[q].layers[++w] = { 190, 8, TILE_GOLD, 4.f, 0.80f, true };
		map_definitions[q].layers[++w] = { 260, 40, TILE_EMERALD, 4.f, 0.9f, true };
		map_definitions[q].layers[++w] = { 230, 40, TILE_EMERALD, 1.f, 0.9f, true };
		map_definitions[q].layers[++w] = { 200, 95, TILE_AIR, 15.f, 0.3f, true };
		map_definitions[q].layers[++w] = { 147, 2, TILE_DIAMOND, -0.1f, 0.995f, true };
	}
	void ScreenNewGame::select_map(int id)
	{
		selected_map = id;
		lbl_name->get_text().setString(map_definitions[id].name);
		lbl_difficulty->get_text().setString(map_definitions[id].difficulty);
		lbl_dimension->get_text().setString(
			std::to_string(map_definitions[id].width) +
			"x" +
			std::to_string(map_definitions[id].height));
	}

}
