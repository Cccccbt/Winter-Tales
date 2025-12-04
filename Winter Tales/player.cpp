#include "player.h"
#include "resource_manager.h"
#include <cmath>
#include "player_state_nodes.h"
#include "animation.h"
#include "bullet_time_manager.h"

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

	timer_bullet_time.set_wait_time(3.0f);
	timer_bullet_time.set_one_shot(true);
	timer_bullet_time.set_callback([this]()
		{
			is_in_bullet_time = false;
			BulletTimeManager::instance()->set_status(BulletTimeManager::Status::Exiting);
		});

	// Pre-allocate to avoid rehashing during construction
	animation_pool.reserve(10);

	// Attack 1 Animation
	animation_pool["attack_1"].left.set_interval(0.05f);
	animation_pool["attack_1"].left.set_is_loop(false);
	animation_pool["attack_1"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_1"].left.add_frame(ResourceManager::instance()->find_image("player_attack_1_left"), 9);
	animation_pool["attack_1"].right.set_interval(0.05f);
	animation_pool["attack_1"].right.set_is_loop(false);
	animation_pool["attack_1"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_1"].right.add_frame(ResourceManager::instance()->find_image("player_attack_1_right"), 9);

	// Attack 2 Animation
	animation_pool["attack_2"].left.set_interval(0.05f);
	animation_pool["attack_2"].left.set_is_loop(false);
	animation_pool["attack_2"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_2"].left.add_frame(ResourceManager::instance()->find_image("player_attack_2_left"), 14);
	animation_pool["attack_2"].right.set_interval(0.05f);
	animation_pool["attack_2"].right.set_is_loop(false);
	animation_pool["attack_2"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_2"].right.add_frame(ResourceManager::instance()->find_image("player_attack_2_right"), 14);

	// Idle Animation
	animation_pool["idle"].left.set_interval(0.1f);
	animation_pool["idle"].left.set_is_loop(true);
	animation_pool["idle"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle"].left.add_frame(ResourceManager::instance()->find_image("player_idle_left"), 6);
	animation_pool["idle"].right.set_interval(0.1f);
	animation_pool["idle"].right.set_is_loop(true);
	animation_pool["idle"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle"].right.add_frame(ResourceManager::instance()->find_image("player_idle_right"), 6);

	// Idle 2 Animation
	animation_pool["idle_2"].left.set_interval(0.1f);
	animation_pool["idle_2"].left.set_is_loop(true);
	animation_pool["idle_2"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle_2"].left.add_frame(ResourceManager::instance()->find_image("player_idle_2_left"), 18);
	animation_pool["idle_2"].right.set_interval(0.1f);
	animation_pool["idle_2"].right.set_is_loop(true);
	animation_pool["idle_2"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle_2"].right.add_frame(ResourceManager::instance()->find_image("player_idle_2_right"), 18);

	// Run Animation
	animation_pool["run"].left.set_interval(0.08f);
	animation_pool["run"].left.set_is_loop(true);
	animation_pool["run"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["run"].left.add_frame(ResourceManager::instance()->find_image("player_run_left"), 10);
	animation_pool["run"].right.set_interval(0.08f);
	animation_pool["run"].right.set_is_loop(true);
	animation_pool["run"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["run"].right.add_frame(ResourceManager::instance()->find_image("player_run_right"), 10);

	// Hurt Animation
	animation_pool["hurt"].left.set_interval(0.1f);
	animation_pool["hurt"].left.set_is_loop(false);
	animation_pool["hurt"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["hurt"].left.add_frame(ResourceManager::instance()->find_image("player_hurt_left"), 4);
	animation_pool["hurt"].right.set_interval(0.1f);
	animation_pool["hurt"].right.set_is_loop(false);
	animation_pool["hurt"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["hurt"].right.add_frame(ResourceManager::instance()->find_image("player_hurt_right"), 4);

	// Dead Animation
	animation_pool["dead"].left.set_interval(0.1f);
	animation_pool["dead"].left.set_is_loop(false);
	animation_pool["dead"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["dead"].left.add_frame(ResourceManager::instance()->find_image("player_dead_left"), 6);
	animation_pool["dead"].right.set_interval(0.1f);
	animation_pool["dead"].right.set_is_loop(false);
	animation_pool["dead"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["dead"].right.add_frame(ResourceManager::instance()->find_image("player_dead_right"), 6);

	// Jump Animation
	animation_pool["jump"].left.set_interval(0.1f);
	animation_pool["jump"].left.set_is_loop(false);
	animation_pool["jump"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["jump"].left.add_frame(ResourceManager::instance()->find_image("player_jump_left"), 12);
	animation_pool["jump"].right.set_interval(0.1f);
	animation_pool["jump"].right.set_is_loop(false);
	animation_pool["jump"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["jump"].right.add_frame(ResourceManager::instance()->find_image("player_jump_right"), 12);
	animation_pool["jump"].right.set_on_finished(
		[this]()
		{
			std::cout << "Jump animation finished." << std::endl;
		});

	// Roll Animation
	animation_pool["roll"].left.set_interval(0.1f);
	animation_pool["roll"].left.set_is_loop(false);
	animation_pool["roll"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["roll"].left.add_frame(ResourceManager::instance()->find_image("player_roll_left"), 16);
	animation_pool["roll"].right.set_interval(0.1f);
	animation_pool["roll"].right.set_is_loop(false);
	animation_pool["roll"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["roll"].right.add_frame(ResourceManager::instance()->find_image("player_roll_right"), 16);

	// Charge Animation
	animation_pool["charge"].left.set_interval(0.08f);
	animation_pool["charge"].left.set_is_loop(true);
	animation_pool["charge"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["charge"].left.add_frame(ResourceManager::instance()->find_image("player_charge_left"), 6);
	animation_pool["charge"].right.set_interval(0.08f);
	animation_pool["charge"].right.set_is_loop(true);
	animation_pool["charge"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["charge"].right.add_frame(ResourceManager::instance()->find_image("player_charge_right"), 6);

	// Set initial animation
	current_animation = &animation_pool["idle"];

	//Initialize StateMachine
	state_machine.register_state("idle", new PlayerIdle());
	state_machine.register_state("run", new PlayerRun());
	state_machine.register_state("jump", new PlayerJump());
	state_machine.register_state("roll", new PlayerRoll());
	state_machine.register_state("attack_1", new PlayerAttack1());
	state_machine.register_state("attack_2", new PlayerAttack2());
	state_machine.register_state("hurt", new PlayerHurt());
	state_machine.register_state("dead", new PlayerDead());
	state_machine.register_state("bullet_time", new PlayerBulletTime());

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
			case 0x41: // A key
			case VK_LEFT:
				is_left_key_down = true;
				break;
			case 0x44: // D key
			case VK_RIGHT:
				is_right_key_down = true;
				break;
			case 0x57: // W key
			case VK_UP:
				is_jump_key_down = true;
				break;
			case 0x53: // S key
			case VK_DOWN:
				is_roll_key_down = true;
				break;

			case 0x4A: // J key
				is_attack_key_down = true;
				break;

			case VK_SPACE: // Space key
				is_bullet_time_key_down = true;
				break;
		}
		break;

	case WM_KEYUP:
		switch (msg.vkcode)
		{
			case 0x41: // A key
			case VK_LEFT:
				is_left_key_down = false;
				break;
			case 0x44: // D key
			case VK_RIGHT:
				is_right_key_down = false;
				break;
			case 0x57: // W key
			case VK_UP:
				is_jump_key_down = false;
				break;
			case 0x53: // S key
			case VK_DOWN:
				is_roll_key_down = false;
				break;

			case 0x4A: // J key
				is_attack_key_down = false;
				break;

			case VK_SPACE: // Space key
				is_bullet_time_key_down = false;
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

	if (get_move_axis() != 0)
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
	// Don't take damage if bullet time is active
	if (BulletTimeManager::instance()->is_active())
	{
		std::cout << "Damage blocked by bullet time!" << std::endl;
		return;
	}

	decrease_hp(1);
	std::cout << "Player took damage! HP: " << hp << std::endl;
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
	velocity.y = 0;
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
	Bullet* bullet = new Bullet(is_facing_left, get_logical_center() + Vector2(0, -20));
	bullet_pool.push_back(bullet);
}

void Player::enter_bullet_time()
{
	// Don't consume MP on entry - only consume when exiting
	state_machine.switch_to("bullet_time");
	BulletTimeManager::instance()->set_status(BulletTimeManager::Status::Entering);
	is_in_bullet_time = true;
	std::cout << "Entering bullet time! MP: " << current_mp << std::endl;
}

