#include "player.h"
#include "resource_manager.h"
#include <cmath>
#include "player_state_nodes.h"
#include "animation.h"

Player::Player()
{
	is_facing_left = false;
	position = Vector2(250, 200);
	logic_height = 64;
	hp = 5;

	hit_box->set_size(Vector2(32, 64));
	hurt_box->set_size(Vector2(16, 64));

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Enemy);

	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);
	hurt_box->set_enabled(true);

	hurt_box->set_on_collide([this]() 
		{
			this->on_hurt();
		});

	timer_combo_reset.set_wait_time(CD_COMBO_RESET);
	timer_combo_reset.set_one_shot(true);
	timer_combo_reset.set_callback([this]()
		{
			attack_combo = 0;
		});

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_roll_cd.set_wait_time(CD_ROLL);

	timer_attack_cd.set_one_shot(true);
	timer_roll_cd.set_one_shot(true);

	timer_attack_cd.set_callback([this]()
		{
			is_attack_cd = false;
		});

	timer_roll_cd.set_callback([this]()
		{
			is_roll_cd = false;
		});

	// Attack 1 Animation
	AnimationGroup& animation_attack_1 = animation_pool["attack_1"];
	Animation& attack_1_left = animation_attack_1.left;
	attack_1_left.set_interval(0.05f);
	attack_1_left.set_is_loop(false);
	attack_1_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack_1_left.add_frame(ResourceManager::instance()->find_image("player_attack_1_left"), 9);
	Animation& attack_1_right = animation_attack_1.right;
	attack_1_right.set_interval(0.05f);
	attack_1_right.set_is_loop(false);
	attack_1_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack_1_right.add_frame(ResourceManager::instance()->find_image("player_attack_1_right"), 9);

	// Attack 2 Animation
	AnimationGroup& animation_attack_2 = animation_pool["attack_2"];
	Animation& attack_2_left = animation_attack_2.left;
	attack_2_left.set_interval(0.05f);
	attack_2_left.set_is_loop(false);
	attack_2_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack_2_left.add_frame(ResourceManager::instance()->find_image("player_attack_2_left"), 14);
	Animation& attack_2_right = animation_attack_2.right;
	attack_2_right.set_interval(0.05f);
	attack_2_right.set_is_loop(false);
	attack_2_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack_2_right.add_frame(ResourceManager::instance()->find_image("player_attack_2_right"), 14);

	// Attack 3 Animation
	AnimationGroup& animation_attack_3 = animation_pool["attack_3"];
	Animation& attack_3_left = animation_attack_3.left;
	attack_3_left.set_interval(0.05f);
	attack_3_left.set_is_loop(false);
	attack_3_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack_3_left.add_frame(ResourceManager::instance()->find_image("player_attack_3_left"), 6);
	Animation& attack_3_right = animation_attack_3.right;
	attack_3_right.set_interval(0.05f);
	attack_3_right.set_is_loop(false);
	attack_3_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	attack_3_right.add_frame(ResourceManager::instance()->find_image("player_attack_3_right"), 6);

	// Idle Animation
	AnimationGroup& animation_idle = animation_pool["idle"];
	Animation& idle_left = animation_idle.left;
	idle_left.set_interval(0.1f);
	idle_left.set_is_loop(true);
	idle_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	idle_left.add_frame(ResourceManager::instance()->find_image("player_idle_left"), 6);
	Animation& idle_right = animation_idle.right;
	idle_right.set_interval(0.1f);
	idle_right.set_is_loop(true);
	idle_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	idle_right.add_frame(ResourceManager::instance()->find_image("player_idle_right"), 6);

	// Idle 2 Animation
	AnimationGroup& animation_idle_2 = animation_pool["idle_2"];
	Animation& idle_2_left = animation_idle_2.left;
	idle_2_left.set_interval(0.1f);
	idle_2_left.set_is_loop(true);
	idle_2_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	idle_2_left.add_frame(ResourceManager::instance()->find_image("player_idle_2_left"), 18);
	Animation& idle_2_right = animation_idle_2.right;
	idle_2_right.set_interval(0.1f);
	idle_2_right.set_is_loop(true);
	idle_2_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	idle_2_right.add_frame(ResourceManager::instance()->find_image("player_idle_2_right"), 18);

	// Run Animation
	AnimationGroup& animation_run = animation_pool["run"];
	Animation& run_left = animation_run.left;
	run_left.set_interval(0.08f);
	run_left.set_is_loop(true);
	run_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	run_left.add_frame(ResourceManager::instance()->find_image("player_run_left"), 10);
	Animation& run_right = animation_run.right;
	run_right.set_interval(0.08f);
	run_right.set_is_loop(true);
	run_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	run_right.add_frame(ResourceManager::instance()->find_image("player_run_right"), 10);

	// Hurt Animation
	AnimationGroup& animation_hurt = animation_pool["hurt"];
	Animation& hurt_left = animation_hurt.left;
	hurt_left.set_interval(0.1f);
	hurt_left.set_is_loop(false);
	hurt_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	hurt_left.add_frame(ResourceManager::instance()->find_image("player_hurt_left"), 4);
	Animation& hurt_right = animation_hurt.right;
	hurt_right.set_interval(0.1f);
	hurt_right.set_is_loop(false);
	hurt_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	hurt_right.add_frame(ResourceManager::instance()->find_image("player_hurt_right"), 4);

	// Dead Animation
	AnimationGroup& animation_dead = animation_pool["dead"];
	Animation& dead_left = animation_dead.left;
	dead_left.set_interval(0.1f);
	dead_left.set_is_loop(false);
	dead_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	dead_left.add_frame(ResourceManager::instance()->find_image("player_dead_left"), 6);
	Animation& dead_right = animation_dead.right;
	dead_right.set_interval(0.1f);
	dead_right.set_is_loop(false);
	dead_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	dead_right.add_frame(ResourceManager::instance()->find_image("player_dead_right"), 6);

	// Jump Animation
	AnimationGroup& animation_jump = animation_pool["jump"];
	Animation& jump_left = animation_jump.left;
	jump_left.set_interval(0.1f);
	jump_left.set_is_loop(false);
	jump_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	jump_left.add_frame(ResourceManager::instance()->find_image("player_jump_left"), 12);
	Animation& jump_right = animation_jump.right;
	jump_right.set_interval(0.1f);
	jump_right.set_is_loop(false);
	jump_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	jump_right.add_frame(ResourceManager::instance()->find_image("player_jump_right"), 12);
	jump_right.set_on_finished(
		[this]()
		{
			std::cout << "Jump animation finished." << std::endl;
		});

	// Roll Animation
	AnimationGroup& animation_roll = animation_pool["roll"];
	Animation& roll_left = animation_roll.left;
	roll_left.set_interval(0.1f);
	roll_left.set_is_loop(false);
	roll_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	roll_left.add_frame(ResourceManager::instance()->find_image("player_roll_left"), 16);
	Animation& roll_right = animation_roll.right;
	roll_right.set_interval(0.1f);
	roll_right.set_is_loop(false);
	roll_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	roll_right.add_frame(ResourceManager::instance()->find_image("player_roll_right"), 16);


	// Charge Animation
	AnimationGroup& animation_charge = animation_pool["charge"];
	Animation& charge_left = animation_charge.left;
	charge_left.set_interval(0.08f);
	charge_left.set_is_loop(true);
	charge_left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	charge_left.add_frame(ResourceManager::instance()->find_image("player_charge_left"), 6);
	Animation& charge_right = animation_charge.right;
	charge_right.set_interval(0.08f);
	charge_right.set_is_loop(true);
	charge_right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	charge_right.add_frame(ResourceManager::instance()->find_image("player_charge_right"), 6);

	// Set initial animation
	current_animation = &animation_pool["idle"];

	//Initialize StateMachine
	state_machine.register_state("idle", new PlayerIdle());
	state_machine.register_state("run", new PlayerRun());
	state_machine.register_state("jump", new PlayerJump());
	state_machine.register_state("roll", new PlayerRoll());
	state_machine.register_state("attack_1", new PlayerAttack1());
	state_machine.register_state("attack_2", new PlayerAttack2());
	state_machine.register_state("attack_3", new PlayerAttack3());
	state_machine.register_state("hurt", new PlayerHurt());
	state_machine.register_state("dead", new PlayerDead());

	state_machine.set_entry("idle");
}

Player::~Player()
{
	// Clean up bullets
	for (auto bullet : bullet_pool) {
		delete bullet;
	}
	bullet_pool.clear();
}

void Player::on_input(const ExMessage& msg)
{
	if (hp < 0)
		return;

	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
			case 0x41: // A key - FIXED: Remove quotes
			case VK_LEFT:
				is_left_key_down = true;
				break;
			case 0x44: // D key - FIXED: Remove quotes
			case VK_RIGHT:
				is_right_key_down = true;
				break;
			case 0x57: // W key - FIXED: Remove quotes
			case VK_UP:
				is_jump_key_down = true;
				break;
			case 0x53: // S key - FIXED: Remove quotes
			case VK_DOWN:
				is_roll_key_down = true;
				break;

			case 0x4A: // J key - FIXED: Remove quotes
				is_attack_key_down = true;
				break;

			case VK_SPACE: // Space key
				//Super Skill
				break;
		}
		break; // FIXED: Add missing break

	case WM_KEYUP: // FIXED: Change from WM_IME_KEYUP to WM_KEYUP
		switch (msg.vkcode)
		{
			case 0x41: // A key - FIXED: Remove quotes
			case VK_LEFT:
				is_left_key_down = false;
				break;
			case 0x44: // D key - FIXED: Remove quotes
			case VK_RIGHT:
				is_right_key_down = false;
				break;
			case 0x57: // W key - FIXED: Remove quotes
			case VK_UP:
				is_jump_key_down = false;
				break;
			case 0x53: // S key - FIXED: Remove quotes
			case VK_DOWN:
				is_roll_key_down = false;
				break;

			case 0x4A: // J key - FIXED: Remove quotes
				is_attack_key_down = false;
				break;

			case VK_SPACE: // Space key
				//Super Skill
				break;
		}
		break;
	}
}

void Player::on_update(float delta)
{
	if (hp > 0 && !is_rolling)
	{
		velocity.x = get_move_axis() * SPEED_RUN;
	}

	// Only allow direction changes when NOT attacking
	if (get_move_axis() != 0 && !is_attacking)
	{
		is_facing_left = get_move_axis() < 0;
	}

	timer_roll_cd.on_update(delta);
	timer_attack_cd.on_update(delta);
	timer_combo_reset.on_update(delta);

	Character::on_update(delta);
	hurt_box->set_position(is_facing_left ? get_logical_center() + Vector2(8, 0) : get_logical_center() - Vector2(8, 0));
	
	// Update bullets and clean up disabled ones
	for (auto it = bullet_pool.begin(); it != bullet_pool.end();)
	{
		(*it)->on_update(delta);
		if (!(*it)->get_enabled())
		{
			delete *it;
			it = bullet_pool.erase(it);
		}
		else
		{
			++it;
		}
	}

	//std::cout << "Player Position: (" << position.x << ", " << position.y << ")\n";
}

void Player::on_render()
{
	Character::on_render();
	
	// Render bullets
	for (auto bullet : bullet_pool)
	{
		bullet->on_render();
	}
}

void Player::on_hurt()
{
    decrease_hp(1);  // Decrease player HP by 1 point
    std::cout << "Player took damage! HP: " << hp << std::endl;
    
    // Optional: Transition to hurt state for visual feedback
    // if (!is_invulnerable) {
    //     switch_state("hurt");
    // }
}

void Player::on_jump()
{
	velocity.y = -SPEED_JUMP;
}

void Player::on_land()
{
	// Placeholder for landing effects
}

void Player::on_roll()
{
	timer_roll_cd.restart();
	is_roll_cd = true;
	velocity.x = (is_facing_left ? -1 : 1) * SPEED_ROLL;
}

void Player::on_attack()
{
        timer_attack_cd.restart();
        is_attack_cd = true;
        timer_combo_reset.restart();
        attack_combo_up();
}

void Player::throw_bullet()
{
	// Create a new bullet with the current facing direction and position
	Bullet* bullet = new Bullet(is_facing_left, get_logical_center() + Vector2(0, -20));
	bullet_pool.push_back(bullet);
}
