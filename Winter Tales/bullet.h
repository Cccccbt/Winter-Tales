#pragma once
#include "state_node.h"
#include "timer.h"
#include "vector2.h"
#include "collision_box.h"
#include "animation.h"
#include "state_machine.h"
#include <unordered_map>

class Bullet
{
public:
	Bullet(bool is_facing_left = false, const Vector2& position = Vector2());
	~Bullet();
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
	Vector2 position;
	const Vector2 SPEED = Vector2(300.0f, 0.0f);
	bool is_facing_left = false;
	bool is_enabled = true;
	CollisionBox* hit_box;
	AnimationGroup* current_animation;
	std::unordered_map<std::string, AnimationGroup> animation_pool;
};