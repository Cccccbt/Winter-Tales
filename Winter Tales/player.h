#pragma once

#include "bullet.h"
#include "character.h"
#include "bullet_time_manager.h"

// Player-specific behaviour including combo attacks, rolling, and bullet throws.
class Player : public Character
{
public:
        Player();
        ~Player();

        void on_hurt() override;
        void on_input(const ExMessage& msg) override;
        void on_update(float delta) override;
        void on_render() override;

        void on_jump();
        void on_roll();
        void on_attack();
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

	bool get_in_bullet_time() const
	{
		return is_in_bullet_time;
	}

	void set_in_bullet_time(bool flag)
	{
		is_in_bullet_time = flag;
	}

        bool can_attack1() const
        {
                return !is_attack_cd && is_attack1_key_down;
        };

        bool can_attack2() const
        {
                return !is_attack_cd && is_attack2_key_down;
        };

        bool can_jump() const
        {
                return is_jump_key_down && is_on_floor();
        };

	bool can_bullet_time() const
	{
		// Can only enter if: have enough MP, space is pressed, not already in bullet time, and bullet time effect is not active
		return current_mp >= 1 && is_bullet_time_key_down && !is_in_bullet_time && !BulletTimeManager::instance()->is_active();
	};

	void decrease_mp(int m)
	{
		current_mp -= m;
		if (current_mp < 0)
			current_mp = 0;
	}

	void increase_mp(int m)
	{
		current_mp += m;
		if (current_mp > mp_max)
			current_mp = mp_max;
	}

	int get_current_mp() const
	{
		return current_mp;
	}

	int get_max_mp() const
	{
		return mp_max;
	}

	int get_move_axis() const
	{
		return is_right_key_down - is_left_key_down;
	}

	int get_attack_combo() const
	{
		return attack_combo;
	}

	void set_attack_combo(int combo)
	{
		attack_combo = combo;
	}

	void throw_bullet();

	void enter_bullet_time();

	void make_bullet_time_invulnerable()
	{
		// Make invulnerable without blinking during bullet time
		is_invulnerable = true;
		is_blink_invisiable = false;  // Don't blink
		is_invulnerable_status.restart();
	}

private:
	const float CD_ROLL = 0.75f;
	const float CD_ATTACK = 0.5f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_ROLL = 600.0f;
	const float SPEED_JUMP = 780.0f;

	Timer timer_roll_cd;
	bool is_rolling = false;
	bool is_roll_cd = false;

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd = false;

	Timer timer_bullet_time;

	int hp_max = 5;
	int mp_max = 3;
	int current_hp = 5;
	int current_mp = 3;

	int attack_combo = 0;

	bool is_in_bullet_time = false;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack1_key_down = false;
	bool is_attack2_key_down = false;
	bool is_bullet_time_key_down = false;

	Animation* charge_effect_animation;
	std::vector<Bullet*> bullet_pool;

	Timer is_invulnerable_status;
	Timer is_invulnerable_blink;
	bool is_invulnerable = false;
	bool is_blink_invisiable = false;
};