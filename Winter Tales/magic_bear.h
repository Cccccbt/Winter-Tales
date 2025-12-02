#pragma once
#include "resource_manager.h"
#include "character_manager.h"
#include "magic_bear_ball.h"
#include "magic_bear_ray.h"
#include "magic_bear_state_nodes.h"

class MagicBear : public Character
{
public:
	MagicBear();
	~MagicBear();

	bool is_attacking() const
	{
		return is_balling || is_raying || is_biting;
	};

	bool can_attack() const
	{
		return can_attack_ball() || can_attack_ray() || can_attack_bite();
	};

	bool can_attack_ball() const
	{
		return !is_global_attack_on_cd && !is_ball_on_cd;
	};

	bool can_attack_ray() const
	{
		return !is_global_attack_on_cd && !is_ray_on_cd;
	};

	Vector2 get_logical_center() const
	{
		return Vector2(position.x, position.y - logic_height / 2);
	}

	bool can_attack_bite() const
	{
		return !is_global_attack_on_cd && !is_bite_on_cd;
	};

	bool can_attack_run() const
	{
		return !is_global_attack_on_cd && !is_run_on_cd;
	};

	float get_walk_speed() const
	{
		return WALK_SPEED;
	};

	float get_run_speed() const
	{
		return RUN_SPEED;
	};

	CollisionBox* get_body_hit_box() const
	{
		return body_hit_box;
	};

	bool is_player_in_close_range() const;
	bool is_player_in_mid_range() const;
	bool is_player_in_far_range() const;

	virtual void on_hurt() override;
	virtual void on_input(const ExMessage& msg) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;

	void on_ball();
	void on_ray();
	void on_bite();
	void on_run();
private:
	const float GLOBAL_ATTACK_CD = 1.0f;
	const float BALL_ATTACK_CD = 3.0f;
	const float RAY_ATTACK_CD = 5.0f;
	const float BITE_ATTACK_CD = 2.0f;
	const float RUN_ATTACK_CD = 2.0f;
	const float WALK_SPEED = 150.0f;
	const float RUN_SPEED = 250.0f;
	const float CLOSE_RANGE = 100.0f;
	const float FAR_RANGE = 300.0f;
	const float MID_RANGE = 200.0f;

	bool is_global_attack_on_cd = false;
	bool is_ball_on_cd = false;
	bool is_ray_on_cd = false;
	bool is_bite_on_cd = false;
	bool is_run_on_cd = false;

	bool is_balling = false;
	bool is_raying = false;
	bool is_biting = false;

	CollisionBox* body_hit_box = nullptr;

	std::vector<MagicBearBall*> bear_ball_list;
	std::vector<MagicBearRay*> bear_ray_list;
};