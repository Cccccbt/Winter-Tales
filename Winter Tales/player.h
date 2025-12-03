#pragma once
#include "bullet.h"
#include "character.h"
#include "bullet_time_manager.h"

class Player : public Character
{
public:
	Player();
	~Player();
	virtual void on_hurt() override;
	virtual void on_input(const ExMessage& msg) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;

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

    bool can_attack() const
    {
            return !is_attack_cd && is_attack_key_down;
    };

	bool can_jump() const
	{
		return is_jump_key_down && is_on_floor();
	};

        bool can_bullet_time() const
        {
                return current_mp >= mp_max && is_bullet_time_key_down && !is_in_bullet_time;
        };

	void decrease_mp(int m)
	{
		current_mp -= m;
		if (current_mp < 0)
			current_mp = 0;
	}

	int get_move_axis() const
	{
		return is_right_key_down - is_left_key_down;
	}

    int get_attack_combo() const
    {
            return attack_combo;
    }

    bool is_attack3_available() const
    {
            return !attack3_used;
    }

    void attack_combo_up()
    {
            attack_combo = (attack_combo + 1) % max_attack_combo;
    }

    void disable_attack3()
    {
            attack3_used = true;
            max_attack_combo = 2;

            if (attack_combo >= max_attack_combo)
            {
                    attack_combo = 0;
            }
    }

	void set_attack_combo(int num)
	{
		attack_combo = (attack_combo + num) % max_attack_combo;
	}

	void throw_bullet();

	void enter_bullet_time();

private:
	const float CD_ROLL = 0.75f;
	const float CD_ATTACK = 0.5f;
	const float CD_COMBO_RESET = 2.0f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_ROLL = 600.0f;
	const float SPEED_JUMP = 780.0f;  // Perfect for 1.2s animation duration

    Timer timer_combo_reset;
    int attack_combo = 0;
    int max_attack_combo = 3;  // CHANGE FROM 2 TO 3!
    bool attack3_used = false;

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

	bool is_in_bullet_time = false;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
    bool is_attack_key_down = false;
	bool is_bullet_time_key_down = false;

	Animation* charge_effect_animation;
	std::vector<Bullet*> bullet_pool;

	/// temp solution for player invulnerability
	/// replace with proper state machine code later
	Timer is_invulnerable_status;
	Timer is_invulnerable_blink;
	bool is_invulnerable = false;
	bool is_blink_invisiable = false;
};