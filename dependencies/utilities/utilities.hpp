#pragma once

#include <cstdint>
#include <string>

struct color;

namespace utilities {
	std::uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept;
	void set_clantag(std::string clantag);
	std::string get_time_as_string();
	color color_from_hsv(int H, float S, float V);
}