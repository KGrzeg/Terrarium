#include <fstream>
#include "ScreenDeleteSaves.hpp"
#include "Definitions.hpp"

namespace terr {
	inline bool exists_test(const std::string& name) {
		std::ifstream f(name.c_str());
		return f.good();
	}

	ScreenDeleteSaves::ScreenDeleteSaves(GlobalReference global) :
		ScreenMenu(global)
	{
		for (size_t i = 0; i < DEFINED_MAPS; i++)
		{
			//std::filesystem
			std::string name = "Slot ";
			name += std::to_string(i + 1) + ' ';
			name += names[i];

			if (exists_test(names[i] + ".sav"))
				name += " / zajete";

			addPosition(name);
		}
		addPosition("Powrot");
	}

	void ScreenDeleteSaves::clicked_option(int id)
	{

		switch (id)
		{
		case DEFINED_MAPS:
		{
			global->navigator.goBack();
			return;
		}
		}

		if (id >= 0 && id < DEFINED_MAPS) {
			std::remove((names[id] + ".sav").c_str());
		}
	}

}