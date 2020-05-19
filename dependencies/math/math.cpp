#include "../utilities/csgo.hpp"

//aimtux
void math::correct_movement(vec3_t old_angles, c_usercmd* cmd, float old_forwardmove, float old_sidemove) {
	float delta_view = 0.f;
	float f1 = old_angles.y;
	float f2 = cmd->viewangles.y;

	if (old_angles.y < 0.f)
		f1 += 360.f;

	if (cmd->viewangles.y < 0.0f)
		f2 += 360.f;

	if (f2 < f1)
		delta_view = std::abs(f2 - f1);
	else
		delta_view = 360.f - std::abs(f1 - f2);

	delta_view = 360.f - delta_view;

	cmd->forwardmove = std::cos(DEG2RAD(delta_view)) * old_forwardmove + cos(DEG2RAD(delta_view + 90.f)) * old_sidemove;
	cmd->sidemove = std::sin(DEG2RAD(delta_view)) * old_forwardmove + sin(DEG2RAD(delta_view + 90.f)) * old_sidemove;
}

vec3_t math::calculate_angle(vec3_t& a, vec3_t& b) {
	vec3_t angles;
	vec3_t delta;
	delta.x = (a.x - b.x);
	delta.y = (a.y - b.y);
	delta.z = (a.z - b.z);

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	angles.x = (float)(atanf(delta.z / hyp) * 57.295779513082f);
	angles.y = (float)(atanf(delta.y / delta.x) * 57.295779513082f);

	angles.z = 0.0f;
	if (delta.x >= 0.0) { angles.y += 180.0f; }
	return angles;
}

void math::sin_cos(float r, float* s, float* c) {
	*s = std::sin(r);
	*c = std::cos(r);
}

vec3_t math::angle_vector(vec3_t angle) {
	auto sy = std::sin(angle.y / 180.f * static_cast<float>(M_PI));
	auto cy = std::cos(angle.y / 180.f * static_cast<float>(M_PI));

	auto sp = std::sin(angle.x / 180.f * static_cast<float>(M_PI));
	auto cp = std::cos(angle.x / 180.f * static_cast<float>(M_PI));

	return { cp * cy, cp * sy, -sp };
}

void math::transform_vector(vec3_t & a, matrix_t & b, vec3_t & out) {
	out.x = a.dot(b[0]) + b[0][3];
	out.y = a.dot(b[1]) + b[1][3];
	out.z = a.dot(b[2]) + b[2][3];
}

void math::vector_angles(vec3_t & forward, vec3_t & angles) {
	if (forward.y == 0.0f && forward.x == 0.0f) {
		angles.x = (forward.z > 0.0f) ? 270.0f : 90.0f;
		angles.y = 0.0f;
	}
	else {
		angles.x = atan2(-forward.z, vec2_t(forward).length()) * -180 / static_cast<float>(M_PI);
		angles.y = atan2(forward.y, forward.x) * 180 / static_cast<float>(M_PI);

		if (angles.y > 90)
			angles.y -= 180;
		else if (angles.y < 90)
			angles.y += 180;
		else if (angles.y == 90)
			angles.y = 0;
	}

	angles.z = 0.0f;
}

void math::angle_vectors(vec3_t & angles, vec3_t * forward, vec3_t * right, vec3_t * up) {
	float sp, sy, sr, cp, cy, cr;

	sin_cos(DEG2RAD(angles.x), &sp, &cp);
	sin_cos(DEG2RAD(angles.y), &sy, &cy);
	sin_cos(DEG2RAD(angles.z), &sr, &cr);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if (up) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

bool math::screen_transform(const vec3_t & point, vec3_t & screen) {
	static auto& w2sMatrix = interfaces::engine->world_to_screen_matrix();

	screen.x = w2sMatrix.m[0][0] * point.x + w2sMatrix.m[0][1] * point.y + w2sMatrix.m[0][2] * point.z + w2sMatrix.m[0][3];
	screen.y = w2sMatrix.m[1][0] * point.x + w2sMatrix.m[1][1] * point.y + w2sMatrix.m[1][2] * point.z + w2sMatrix.m[1][3];
	screen.z = 0.0f;
	float w = w2sMatrix.m[3][0] * point.x + w2sMatrix.m[3][1] * point.y + w2sMatrix.m[3][2] * point.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		screen.x *= 100000;
		screen.y *= 100000;
		return false;
	}

	screen.x /= w;
	screen.y /= w;

	return true;
}

bool math::world_to_screen(const vec3_t & origin, vec3_t & screen) {
	if (math::screen_transform(origin, screen)) {
		int w, h;
		interfaces::engine->get_screen_size(w, h);

		screen.x = (w / 2.0f) + (screen.x * w) / 2.0f;
		screen.y = (h / 2.0f) - (screen.y * h) / 2.0f;

		return true;
	}
	return false;
}
