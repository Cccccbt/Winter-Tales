#pragma once
#include "animation.h"
#include "timer.h"
#include "character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	void on_input(const ExMessage& msg) override;
	void on_update(float delta) override;
	void on_render() override;
	void on_hurt() override;

	void set_rolling(bool flag)
	{
		is_rolling = flag;
	}

	bool get_rolling() const
	{
		return is_rolling;
	}

	bool can_roll() const
	{
		return is_colling_cd_comp && !is_rolling && is_down_key_down;
	}

	void set_attacking(bool flag)
	{
		is_attacking = flag;
	}

	bool get_attacking() const
	{
		return is_attacking;
	}

	bool can_Attack() const
	{
		return is_attacking_cd_comp && !is_attacking && is_attack_key_down;
	}

	bool can_jump() const
	{
		return is_on_floor && is_up_key_down;
	}


	int get_move_axis() const
	{
		return is_right_key_down - is_left_key_down;
	}

private:
	const float CD_ROLL = 0.75f;
	const float CD_ATTACK = 0.5f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 780.0f;
	const float SPEED_ROLL = 800.0f;

	Timer timer_roll_cd;
	bool is_rolling = false;
	bool is_colling_cd_comp = true;

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attacking_cd_comp = true;

	bool is_on_floor = false;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_up_key_down = false;
	bool is_down_key_down = false;
	bool is_attack_key_down = false;

	Animation attack_fan;

	bool is_jump_vfx_visiable = false;
	Animation animation_jump_vfx;
	bool is_land_vfx_visiable = false;
	Animation animation_land_vfx;

	bool is_facing_left;
};