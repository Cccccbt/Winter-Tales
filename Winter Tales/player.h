#pragma once
#include "character.h"

class Player : public Character
{
public:
	Player();
	~Player();
	virtual void on_hurt() override;
	virtual void on_input(const ExMessage& msg) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;

	void on_hurt() override;
	void on_jump();
	void on_roll();
	void on_attack_A();
	void on_attack_B();
	void on_land();

	void set_rolling(bool flag)
	{
		is_rolling = flag;
	};

	bool get_rolling() const
	{
		return is_rolling;
	};

	bool can_roll() const
	{
		return !is_roll_cd && !is_rolling && is_roll_key_down;
	};

	void set_attacking(bool flag)
	{
		is_attacking = flag;
	};

	bool get_attacking() const
	{
		return is_attacking;
	};

	bool can_attack() const
	{
		return !is_attack_cd && !is_attacking && (is_attack_A_key_down || is_attack_B_key_down);
	};

	bool can_jump() const
	{
		return is_jump_key_down && is_on_floor();
	};

	int get_move_axis() const
	{
		return is_left_key_down - is_right_key_down;
	}

private:
	const float CD_ROLL = 0.75f;
	const float CD_ATTACK = 0.5f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_ROLL = 800.0f;
	const float SPEED_JUMP = 780.0f;

	Timer timer_roll_cd;
	bool is_rolling = false;
	bool is_roll_cd = false;

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd = false;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_A_key_down = false;
	bool is_attack_B_key_down = false;

	Animation* charge_effect_animation;
};