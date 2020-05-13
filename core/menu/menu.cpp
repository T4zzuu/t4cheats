#include "menu.hpp"

//todo auto elements positioning

auto do_frame = [&](std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg, color header_text, color header_line, const std::string& name) {
		render::draw_filled_rect(x - 1, y - 1, w + 2, h + 2, color(255, 140, 0, 150));
		render::draw_filled_rect(x, y, w, h, bg);
		render::draw_filled_rect(x, y, w, 30, header_text);
		render::draw_filled_rect(x, y + 30, w, 2, header_line);
		render::draw_text_string(x + 10, y + 8, render::fonts::main, name, false, color::white());
};

std::string captions[] = {
	"we are back",
	"hL can't believe it",
	"maybe without crashes now?",
	"crashware 2.0",
	"funny yes",
	"lorem ipsum",
	"now in HD!",
	"dominating legits since 1000 BC"
};

void menu::render() {
	static bool init = false;
	static std::string caption = "";
	if (!init) {
		caption = captions[rand() % 8];
		init = true;
	}
	if (!variables::menu::opened)
		return;

	do_frame(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(36, 36, 36, 255), color(25, 25, 25, 255), color(36, 36, 36, 255), "t4cheats - " + caption);
	
	menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 35, 100, 260, render::fonts::main, "Tabs", false); {
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + 45, 100, 30, render::fonts::main, "Aimbot", menu::current_tab, 0, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + 80, 100, 30, render::fonts::main, "Visuals", menu::current_tab, 1, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + 115, 100, 30, render::fonts::main, "Misc", menu::current_tab, 2, false);
	}

	switch (current_tab) {
	case 0:
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::main, "Aimbot", false); {
			int pos[2] = { variables::menu::x + 120, variables::menu::y + 45 };
			menu_framework::slider(&pos[0], &pos[1], 125, render::fonts::main, "Test slider", variables::test_float, -101.f, 101.f);
		}
		break;
	case 1:
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::main, "Visuals", false); {
			int pos[2] = { variables::menu::x + 120, variables::menu::y + 45 };
			menu_framework::check_box(&pos[0], &pos[1], pos[0] + 200, render::fonts::main, "Esp enable", variables::visuals::esp_enable);
			menu_framework::check_box(&pos[0], &pos[1], pos[0] + 200, render::fonts::main, "Esp show name", variables::visuals::esp_show_name);
			menu_framework::check_box(&pos[0], &pos[1], pos[0] + 200, render::fonts::main, "Esp show box", variables::visuals::esp_show_box);
			menu_framework::check_box(&pos[0], &pos[1], pos[0] + 200, render::fonts::main, "Esp show weapon", variables::visuals::esp_show_weapon);
			menu_framework::check_box(&pos[0], &pos[1], pos[0] + 200, render::fonts::main, "Esp show healthbar", variables::visuals::esp_show_healthbar);
		}
		break;
	case 2:
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::main, "Misc", false); {
			int pos[2] = { variables::menu::x + 120, variables::menu::y + 45 };
			menu_framework::check_box(&pos[0], &pos[1], pos[0] + 200, render::fonts::main, "Bunnyhop", variables::bunnyhop);
		}
		break;
	}

	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}