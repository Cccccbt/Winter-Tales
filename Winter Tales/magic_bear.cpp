#include "magic_bear.h"

MagicBear::MagicBear()
{
	// Constructor implementation (if any)
	is_facing_left = true;
	position = Vector2(400.0f, 300.0f);
	logic_height = 32.0f;

	hit_box = CollisionManager::instance()->create_collision_box();
	body_hit_box = CollisionManager::instance()->create_collision_box();
	hurt_box = CollisionManager::instance()->create_collision_box();

	hit_box->set_size(Vector2(56, 32));
	body_hit_box->set_size(Vector2(56, 32));
	hurt_box->set_size(Vector2(56, 32));

	hit_box->set_layer_src(CollisionLayer::None);
	body_hit_box->set_layer_src(CollisionLayer::None);
	hurt_box->set_layer_src(CollisionLayer::Enemy);

	hit_box->set_layer_dst(CollisionLayer::Player);
	body_hit_box->set_layer_dst(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hurt_box->set_on_collide(
		[this]() 
		{
			decrease_hp(1);
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
//	state_machine.register_state("hurt", new MagicBearHurt());
//	state_machine.register_state("dead", new MagicBearHurt()); // Reuse hurt state for dead for simplicity
//	state_machine.register_state("sneer", new MagicBearIdle()); // Reuse idle state for sneer for simplicity
	state_machine.set_entry("idle");

}

MagicBear::~MagicBear()
{
	// Destructor implementation (if any)
}

void MagicBear::on_hurt()
{
	// Implementation of on_hurt
}

void MagicBear::on_input(const ExMessage& msg)
{
	// Implementation of on_input
}

void MagicBear::on_update(float delta)
{
	// Implementation of on_update
	Player* player = CharacterManager::instance()->get_player();
	
	// Update facing direction to always face the player
	Vector2 direction_to_player = player->get_position() - get_position();
	if (direction_to_player.x != 0)
	{
		is_facing_left = (direction_to_player.x < 0);
	}
	
	Character::on_update(delta);

	hit_box->set_position(get_logical_center());
	body_hit_box->set_position(get_logical_center());

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

void MagicBear::on_ball()
{
	// Implementation of on_ball
	MagicBearBall* new_ball = new MagicBearBall(is_facing_left, get_logical_center());
	bear_ball_list.push_back(new_ball);
}

void MagicBear::on_ray()
{
	// Implementation of on_ray
	MagicBearRay* new_ray = new MagicBearRay(is_facing_left, Vector2(get_logical_center().x, get_logical_center().y - 20.0f));
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
	set_velocity(Vector2(is_facing_left ? -get_run_speed() : get_run_speed(), get_velocity().y));
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

