#pragma once
#include "collision_manager.h"
#include "character.h"
#include "vector2.h"
#include "animation.h"
#include <cstdlib>

class MagicBearRay
{
public:
	MagicBearRay(bool is_facing_left = false, const Vector2& position = Vector2());
	~MagicBearRay();

	void on_update(float delta);
	void on_render();
	void set_position(const Vector2& position)
	{
		this->position = position;
	}
	const Vector2& get_position() const
	{
		return position;
	}

	bool get_enabled() const
	{
		return is_enabled;
	}

private:
	enum Color
	{
		LightBlue,
		DarkBlue,
		White
	};

	Timer timer_color_change;
	Timer timer_life;
	Vector2 position;
	const Vector2 size = Vector2(276.0f, 14.0f);
	bool is_facing_left = false;
	bool is_enabled = true;
	CollisionBox* hit_box = nullptr;
	Color current_color = LightBlue;
};