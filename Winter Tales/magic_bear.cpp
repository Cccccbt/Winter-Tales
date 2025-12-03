#include "magic_bear.h"
#include <algorithm>

MagicBear::MagicBear()
{
        // Constructor implementation (if any)
        hp_max = static_cast<float>(hp);
        is_facing_left = true;
	position = Vector2(400.0f, 300.0f);
	logic_height = 32.0f;

	hit_box = CollisionManager::instance()->create_collision_box();
	body_hit_box = CollisionManager::instance()->create_collision_box();
	hurt_box = CollisionManager::instance()->create_collision_box();

	hit_box->set_size(Vector2(56, 32));
	body_hit_box->set_size(Vector2(84, 56));
	hurt_box->set_size(Vector2(84, 56));

	hit_box->set_layer_src(CollisionLayer::None);
	body_hit_box->set_layer_src(CollisionLayer::None);
        hurt_box->set_layer_src(CollisionLayer::Enemy);

        hit_box->set_layer_dst(CollisionLayer::Player);
        body_hit_box->set_layer_dst(CollisionLayer::Player);
        hurt_box->set_layer_dst(CollisionLayer::None);

        hurt_box->set_on_collide(
                [this]()
                {
                        if (is_invulnerable)
                        {
                                return;
                        }

                        if (hp > 0)
                        {
                                --hp;
                        }

                        on_hurt();
                });

	AnimationGroup& idle_animation = animation_pool["idle"];
	Animation& idle_left = idle_animation.left;
	idle_left.set_interval(0.2f);
	idle_left.set_is_loop(true);
	idle_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	idle_left.add_frame(ResourceManager::instance()->find_image("magic_bear_idle_left"), 4);
	Animation& idle_right = idle_animation.right;
	idle_right.set_interval(0.2f);
	idle_right.set_is_loop(true);
	idle_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	idle_right.add_frame(ResourceManager::instance()->find_image("magic_bear_idle_right"), 4);

	AnimationGroup& walk_animation = animation_pool["walk"];
	Animation& walk_left = walk_animation.left;
	walk_left.set_interval(0.15f);
	walk_left.set_is_loop(true);
	walk_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	walk_left.add_frame(ResourceManager::instance()->find_image("magic_bear_walk_left"), 6);
	Animation& walk_right = walk_animation.right;
	walk_right.set_interval(0.15f);
	walk_right.set_is_loop(true);
	walk_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	walk_right.add_frame(ResourceManager::instance()->find_image("magic_bear_walk_right"), 6);

	AnimationGroup& sneer_animation = animation_pool["sneer"];
	Animation& sneer_left = sneer_animation.left;
	sneer_left.set_interval(0.2f);
	sneer_left.set_is_loop(true);
	sneer_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	sneer_left.add_frame(ResourceManager::instance()->find_image("magic_bear_sneer_left"), 4);
	Animation& sneer_right = sneer_animation.right;
	sneer_right.set_interval(0.2f);
	sneer_right.set_is_loop(true);
	sneer_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	sneer_right.add_frame(ResourceManager::instance()->find_image("magic_bear_sneer_right"), 4);

	AnimationGroup& hurt_animation = animation_pool["hurt"];
	Animation& hurt_left = hurt_animation.left;
	hurt_left.set_interval(0.2f);
	hurt_left.set_is_loop(false);
	hurt_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	hurt_left.add_frame(ResourceManager::instance()->find_image("magic_bear_hurt_left"), 2);
	Animation& hurt_right = hurt_animation.right;
	hurt_right.set_interval(0.2f);
	hurt_right.set_is_loop(false);
	hurt_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	hurt_right.add_frame(ResourceManager::instance()->find_image("magic_bear_hurt_right"), 2);

	AnimationGroup& dead_animation = animation_pool["dead"];
	Animation& dead_left = dead_animation.left;
	dead_left.set_interval(0.2f);
	dead_left.set_is_loop(false);
	dead_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	dead_left.add_frame(ResourceManager::instance()->find_image("magic_bear_dead_left"), 4);
	Animation& dead_right = dead_animation.right;
	dead_right.set_interval(0.2f);
	dead_right.set_is_loop(false);
	dead_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	dead_right.add_frame(ResourceManager::instance()->find_image("magic_bear_dead_right"), 4);

	AnimationGroup& attack1_animation = animation_pool["attack1"];
	Animation& attack1_left = attack1_animation.left;
	attack1_left.set_interval(0.15f);
	attack1_left.set_is_loop(false);
	attack1_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack1_left.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_1_left"), 6);
	Animation& attack1_right = attack1_animation.right;
	attack1_right.set_interval(0.15f);
	attack1_right.set_is_loop(false);
	attack1_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack1_right.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_1_right"), 6);

	AnimationGroup& attack2_animation = animation_pool["attack2"];
	Animation& attack2_left = attack2_animation.left;
	attack2_left.set_interval(0.15f);
	attack2_left.set_is_loop(false);
	attack2_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack2_left.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_2_left"), 6);
	Animation& attack2_right = attack2_animation.right;
	attack2_right.set_interval(0.15f);
	attack2_right.set_is_loop(false);
	attack2_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack2_right.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_2_right"), 6);

	AnimationGroup& attack3_animation = animation_pool["attack3"];
	Animation& attack3_left = attack3_animation.left;
	attack3_left.set_interval(0.15f);
	attack3_left.set_is_loop(false);
	attack3_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack3_left.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_3_left"), 6);
	
	Animation& attack3_right = attack3_animation.right;
	attack3_right.set_interval(0.15f);
	attack3_right.set_is_loop(false);
	attack3_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack3_right.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_3_right"), 6);
	

	AnimationGroup& attack4_animation = animation_pool["attack4"];
        Animation& attack4_left = attack4_animation.left;
        attack4_left.set_interval(0.2f);
        attack4_left.set_is_loop(false);
        attack4_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
        attack4_left.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_4_left"), 4);
        Animation& attack4_right = attack4_animation.right;
        attack4_right.set_interval(0.2f);
        attack4_right.set_is_loop(false);
        attack4_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
        attack4_right.add_frame(ResourceManager::instance()->find_image("magic_bear_attack_4_right"), 4);
	
	state_machine.register_state("idle", new MagicBearIdle());
	state_machine.register_state("walk", new MagicBearWalk());
	state_machine.register_state("attack1", new MagicBearAttack1());
	state_machine.register_state("attack2", new MagicBearAttack2());
        state_machine.register_state("attack3", new MagicBearAttack3());
        state_machine.register_state("attack4", new MagicBearAttack4());
        state_machine.register_state("sneer", new MagicBearSneer());
        state_machine.register_state("hurt", new MagicBearHurt());
        state_machine.register_state("dead", new MagicBearDead());
        state_machine.set_entry("idle");

	setup_cooldown_timers();

}

MagicBear::~MagicBear()
{
	// Destructor implementation (if any)
}

void MagicBear::on_hurt()
{
        std::cout << "MagicBear hurt! HP: " << hp << std::endl;
        enter_hurt_invulnerability();

        switch_state(hp <= 0 ? "dead" : "hurt");
}

void MagicBear::enter_hurt_invulnerability()
{
        is_invulnerable_status.pause();
        is_invulnerable_blink.pause();
        is_blink_invisiable = false;
        is_invulnerable = true;
}

void MagicBear::clear_hurt_invulnerability()
{
        is_invulnerable = false;
        is_invulnerable_status.pause();
        is_invulnerable_blink.pause();
        is_blink_invisiable = false;
}

void MagicBear::on_input(const ExMessage& msg)
{
	// Implementation of on_input
}

void MagicBear::on_update(float delta)
{
	// Implementation of on_update
	Player* player = CharacterManager::instance()->get_player();

	update_phase();
	update_attack_cooldowns(delta);

	// Update facing direction to always face the player
	Vector2 direction_to_player = player->get_position() - get_position();
	if (direction_to_player.x != 0)
	{
		is_facing_left = (direction_to_player.x < 0);
	}

	Character::on_update(delta);

	hurt_box->set_position(get_logical_center() + (is_facing_left ? Vector2(16, -24) : Vector2(-16, -24)));

	body_hit_box->set_position(get_logical_center() + (is_facing_left ? Vector2(16, -24) : Vector2(-16, -24)));

	for (auto& ball : bear_ball_list)
	{
		ball->on_update(delta);
	}

	for (auto& ray : bear_ray_list)
	{
		ray->on_update(delta);
	}

	bear_ball_list.erase(
		std::remove_if(
			bear_ball_list.begin(),
			bear_ball_list.end(),
			[](MagicBearBall* ball) 
			{ 
				if (!ball->get_enabled()) 
				{
					delete ball; 
					return true; 
				} 
				return false; 
			}),
		bear_ball_list.end());
	bear_ray_list.erase(
		std::remove_if(
			bear_ray_list.begin(),
			bear_ray_list.end(),
			[](MagicBearRay* ray)
			{
				if (!ray->get_enabled())
				{
					delete ray;
					return true;
				}
				return false;
			}),
		bear_ray_list.end());


	//std::cout << "MagicBear Phase: " << phase << ", HP: " << hp << "/" << hp_max << std::endl;
}

void MagicBear::on_render()
{
	// Implementation of on_render
	for (auto& ball : bear_ball_list)
	{
		ball->on_render();
	}
	for (auto& ray : bear_ray_list)
	{
		ray->on_render();
	}
	Character::on_render();
}

bool MagicBear::on_ball()
{
        // Implementation of on_ball
        int active_ball_count = 0;
        for (auto* ball : bear_ball_list)
        {
                if (ball && ball->get_enabled())
                {
                        ++active_ball_count;
                }
        }

        if (active_ball_count >= 3)
        {
                return false;
        }

        MagicBearBall* new_ball = new MagicBearBall(is_facing_left, get_logical_center());
        bear_ball_list.push_back(new_ball);
        return true;
}

void MagicBear::on_ray(bool flag)
{
	// Implementation of on_ray
	MagicBearRay* new_ray = new MagicBearRay(flag, Vector2(get_logical_center().x, get_logical_center().y - 28.0f));
	bear_ray_list.push_back(new_ray);
}

void MagicBear::on_bite()
{
	// Implementation of on_bite

}

void MagicBear::on_run()
{
	// Implementation of on_run
	// Run attack: Bear rushes toward the player with increased speed
	set_velocity(Vector2(is_facing_left ? -get_phase_run_speed() : get_phase_run_speed(), get_velocity().y));
}

bool MagicBear::is_player_in_close_range() const
{
	Character* player = CharacterManager::instance()->get_player();
	float distance = (player->get_logical_center() - get_logical_center()).length();
	return distance <= CLOSE_RANGE;
}

bool MagicBear::is_player_in_mid_range() const
{
	Character* player = CharacterManager::instance()->get_player();
	float distance = (player->get_logical_center() - get_logical_center()).length();
	return distance > CLOSE_RANGE && distance <= MID_RANGE;
}

bool MagicBear::is_player_in_far_range() const
{
Character* player = CharacterManager::instance()->get_player();
float distance = (player->get_logical_center() - get_logical_center()).length();
return distance > MID_RANGE && distance <= FAR_RANGE;
}

float MagicBear::get_phase_walk_speed() const
{
	switch (phase)
	{
	case 1:
		return WALK_SPEED;
	case 2:
		return WALK_SPEED * 1.2f;
	default:
		return WALK_SPEED * 1.4f;
	}
}

float MagicBear::get_phase_run_speed() const
{
	switch (phase)
	{
	case 1:
		return RUN_SPEED;
	case 2:
		return RUN_SPEED * 1.15f;
	default:
		return RUN_SPEED * 1.35f;
	}
}

float MagicBear::get_phase_based_global_cd() const
{
	switch (phase)
	{
	case 1:
		return GLOBAL_ATTACK_CD;
	case 2:
		return GLOBAL_ATTACK_CD * 0.8f;
	default:
		return GLOBAL_ATTACK_CD * 0.6f;
	}
}

float MagicBear::get_attack1_cd() const
{
	if (phase == 1)
	{
		return BITE_ATTACK_CD;
	}
	if (phase == 2)
	{
		return BITE_ATTACK_CD * 0.8f;
	}
	return BITE_ATTACK_CD * 0.5f;
}

float MagicBear::get_attack2_cd() const
{
	if (phase == 1)
	{
		return RUN_ATTACK_CD;
	}
	if (phase == 2)
	{
		return RUN_ATTACK_CD * 0.8f;
	}
	return RUN_ATTACK_CD * 0.55f;
}

float MagicBear::get_attack3_cd() const
{
	if (phase == 1)
	{
		return RAY_ATTACK_CD;
	}
	if (phase == 2)
	{
		return RAY_ATTACK_CD * 0.85f;
	}
	return RAY_ATTACK_CD * 0.75f;
}

float MagicBear::get_attack4_cd() const
{
	if (phase == 1)
	{
		return BALL_ATTACK_CD;
	}
	if (phase == 2)
	{
		return BALL_ATTACK_CD * 0.85f;
	}
	return BALL_ATTACK_CD * 0.75f;
}

void MagicBear::setup_cooldown_timers()
{
	global_cd_timer.set_one_shot(true);
	ball_cd_timer.set_one_shot(true);
	ray_cd_timer.set_one_shot(true);
	bite_cd_timer.set_one_shot(true);
	run_cd_timer.set_one_shot(true);

	global_cd_timer.set_callback([this]()
	                           { is_global_attack_on_cd = false; });
	ball_cd_timer.set_callback([this]()
	                         { is_ball_on_cd = false; });
	ray_cd_timer.set_callback([this]()
	                        { is_ray_on_cd = false; });
	bite_cd_timer.set_callback([this]()
	                         { is_bite_on_cd = false; });
	run_cd_timer.set_callback([this]()
	                        { is_run_on_cd = false; });
}

void MagicBear::update_attack_cooldowns(float delta)
{
	global_cd_timer.on_update(delta);
	ball_cd_timer.on_update(delta);
	ray_cd_timer.on_update(delta);
	bite_cd_timer.on_update(delta);
	run_cd_timer.on_update(delta);
}

void MagicBear::start_global_attack_cooldown()
{
	is_global_attack_on_cd = true;
	global_cd_timer.set_wait_time(get_phase_based_global_cd());
	global_cd_timer.restart();
}

void MagicBear::start_attack1_cooldown()
{
	is_bite_on_cd = true;
	bite_cd_timer.set_wait_time(get_attack1_cd());
	bite_cd_timer.restart();
}

void MagicBear::start_attack2_cooldown()
{
	is_run_on_cd = true;
	run_cd_timer.set_wait_time(get_attack2_cd());
	run_cd_timer.restart();
}

void MagicBear::start_attack3_cooldown()
{
	is_ray_on_cd = true;
	ray_cd_timer.set_wait_time(get_attack3_cd());
	ray_cd_timer.restart();
}

void MagicBear::start_attack4_cooldown()
{
	is_ball_on_cd = true;
	ball_cd_timer.set_wait_time(get_attack4_cd());
	ball_cd_timer.restart();
}

void MagicBear::update_phase()
{
	float ratio = hp_max > 0.0f ? static_cast<float>(hp) / hp_max : 0.0f;
	int previous_phase = phase;

	if (ratio > 0.6f)
	{
		phase = 1;
	}
	else if (ratio > 0.25f)
	{
		phase = 2;
	}
	else
	{
		phase = 3;
	}

	if (phase != previous_phase && phase >= 2 && hp > 0)
	{
		pending_phase_sneer = true;
	}
}

bool MagicBear::consume_pending_sneer()
{
	if (pending_phase_sneer)
	{
		pending_phase_sneer = false;
		return true;
	}
	return false;
}



