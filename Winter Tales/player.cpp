#include "player.h"
#include "resource_manager.h"

Player::Player()
	:Character()
{
	current_animation = &animation_pool["idle"];
	is_facing_left = false;
	logic_height = 64;

	hurt_box->set_size(Vector2(32, 64));
	hit_box->set_size(Vector2(64, 128)); //Edit Later

	hit_box->set_layer_dst(CollisionLayer::Enemy);
	hit_box->set_layer_src(CollisionLayer::None);
	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);
	hurt_box->set_on_collide(
		[&]()
		{
			decrease_hp(1);
		}
	);

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback(
		[&]()
		{
			is_attacking_cd_comp = true;
		}
	);

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback(
		[&]()
		{
			is_attacking_cd_comp = true;
		}
	);

	AnimationGroup& animation_attack_A = animation_pool["attack_A"];
	animation_attack_A.right.set_interval(0.05f);
	animation_attack_A.right.set_is_loop(false);
	animation_attack_A.right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_attack_A.right.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_A_right"), 4);

	animation_attack_A.left.set_interval(0.05f);
	animation_attack_A.left.set_is_loop(false);
	animation_attack_A.left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_attack_A.left.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_A_left"), 4);

	AnimationGroup& animation_attack_B = animation_pool["attack_B"];
	animation_attack_B.right.set_interval(0.05f);
	animation_attack_B.right.set_is_loop(false);
	animation_attack_B.right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_attack_B.right.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_B_right"), 4);

	animation_attack_B.left.set_interval(0.05f);
	animation_attack_B.left.set_is_loop(false);
	animation_attack_B.left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_attack_B.left.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_B_left"), 4);

	AnimationGroup& animation_idle = animation_pool["idle"];
	animation_idle.right.set_interval(0.05f);
	animation_idle.right.set_is_loop(false);
	animation_idle.right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_idle.right.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_A_right"), 4);

	animation_idle.left.set_interval(0.05f);
	animation_idle.left.set_is_loop(false);
	animation_idle.left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_idle.left.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_A_left"), 4);

	AnimationGroup& animation_attack = animation_pool["attack"];
	animation_attack.right.set_interval(0.05f);
	animation_attack.right.set_is_loop(false);
	animation_attack.right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_attack.right.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_A_right"), 4);

	animation_attack.left.set_interval(0.05f);
	animation_attack.left.set_is_loop(false);
	animation_attack.left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_attack.left.add_frame(ResourceManager::instance()->find_image("little_match_girl_attack_A_left"), 4);


}

Player::~Player() = default;

void Player::on_input(const ExMessage& msg)
{
	if (hp <= 0)
	{
		return;
	}

	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
		case 0x41:
			is_left_key_down = true;
			break;
		case 0x44:
			is_right_key_down = true;
			break;
		case 0x57:
			is_up_key_down = true;
			break;
		case 0x53:
			is_down_key_down = true;
			break;
		}
		break;

	case WM_KEYUP:
		switch (msg.vkcode)
		{
		case 0x41:
			is_left_key_down = false;
			break;
		case 0x44:
			is_right_key_down = false;
			break;
		case 0x57:
			is_up_key_down = false;
			break;
		case 0x53:
			is_down_key_down = false;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		is_attack_key_down = true;
		break;
	case WM_LBUTTONUP:
		is_attack_key_down = false;
		break;
	}
}

void Player::on_update(float delta)
{
	if (hp > 0 && !is_rolling)
	{
		velocity.x = get_move_axis() * SPEED_RUN;
	}

	if (is_rolling)
	{
		velocity.x = get_move_axis() * SPEED_ROLL;
	}

	timer_attack_cd.on_update(delta);
	timer_roll_cd.on_update(delta);

	Character::on_update(delta);
}

void Player::on_render()
{
	Character::on_render();
}

void Player::on_hurt()
{
	//PlaceHolder
}