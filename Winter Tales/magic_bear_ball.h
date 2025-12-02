#pragma once
#include "collision_manager.h"
#include "vector2.h"
#include "animation.h"
#include <cstdlib>
#include <ctime>


class MagicBearBall
{
public:
	MagicBearBall(bool is_facing_left = false, const Vector2& position = Vector2());
	~MagicBearBall();
	void on_update(float delta);
	void on_render();
	void set_position(const Vector2& position)
	{
		this->position = position;
		this->base_position = position;
	}
	const Vector2& get_position() const
	{
		return position;
	}

	const Vector2& get_velocity() const
	{
		return velocity;
	}

	CollisionBox* get_hit_box()
	{
		return hit_box;
	}
	void set_facing_left(bool flag)
	{
		is_facing_left = flag;
	}
	void set_enabled(bool flag)
	{
		is_enabled = flag;
	}
	bool get_enabled() const
	{
		return is_enabled;
	}
	bool get_facing_left() const
	{
		return is_facing_left;
	}
	void on_destroy();
private:
	enum Stage
	{
		Aiming,
		Dashing,
		Breaking	
	};
	Vector2 position;
	Vector2 velocity;
	Vector2 base_position;
	const float SPEED = 450.0f;
	const float SHAKE_INTENSITY = 3.0f;
	CollisionBox* hit_box;
	bool is_facing_left = false;
	bool is_enabled = true;
	IMAGE* ball_image;
	Timer timer_aim;
	Stage stage;
};