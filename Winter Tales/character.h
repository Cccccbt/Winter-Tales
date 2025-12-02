#pragma once
#include "state_machine.h"
#include "vector2.h"
#include "collision_box.h"
#include "animation.h"
#include <unordered_map>
#include <string>

class Character
{
public:
	Character();
	~Character();

	void decrease_hp(int h);

	int get_hp() const
	{
		return hp;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	const Vector2& get_position() const
	{
		return position;
	}

	void set_velocity(const Vector2& velocity)
	{
		this->velocity = velocity;
	}

	const Vector2& get_velocity() const
	{
		return velocity;
	}

	const Vector2 get_logical_center() const
	{
		return Vector2(position.x, position.y - logic_height / 2);
	}

	void set_enable_gravity(bool flag)
	{
		enable_gravity = flag;
	}

	CollisionBox* get_hit_box()
	{
		return hit_box;
	}

	CollisionBox* get_hurt_box()
	{
		return hurt_box;
	}

	void make_invulnerable()
	{
		is_invulnerable = true;
		is_invulnerable_status.restart();
	}

	bool get_is_facing_left() const
	{
		return is_facing_left;
	}

	bool is_on_floor() const
	{
		return position.y >= FLOOR_Y;
	}

	virtual void on_hurt();

	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();

	void switch_state(const std::string& id);
	void set_animation(const std::string& id);

protected:
	const float GRAVITY = 980 * 2;
	const float FLOOR_Y =300;

	int hp = 10;
	Vector2 position;
	Vector2 velocity;
	float logic_height;
	bool is_facing_left = true;
	bool enable_gravity = true;
	bool is_invulnerable = false;
	Timer is_invulnerable_status;
	Timer is_invulnerable_blink;
	bool is_blink_invisiable = true;
	CollisionBox* hit_box = nullptr;
	CollisionBox* hurt_box = nullptr;
	AnimationGroup* current_animation = nullptr;
	StateMachine state_machine;
	std::unordered_map<std::string, AnimationGroup> animation_pool;
};