#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"

namespace visuals {
	namespace chams {
		void render(IMatRenderContext* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix);
	};
	namespace esp {
		void draw();
	};
	namespace other_visuals {
		void draw();
	};
}

namespace misc {
	
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
	};
}