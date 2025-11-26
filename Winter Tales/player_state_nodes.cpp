#include "player_state_nodes.h"

PlayerAttack_AState::PlayerAttack_AState()
{
	timer.set_wait_time(0.3f);	//Define Later
	timer.set_one_shot(true);
	timer.set_callback(
		[&]()
		{
			CharacterManager::instance()->get_player()->set_attacking(false);
			CharacterManager::instance()->get_player()->get_hit_box()->set_enabled(false);
		}
	);

	CharacterManager::instance()->get_player()->get_hit_box()->set_size(Vector2(56, 96));
}

void PlayerAttack_AState::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();

	player->set_animation("attack_A");
	player->get_hit_box()->set_enabled(true);
	player->set_attacking(true);
	update_hit_box_position();
	player->on_attack();
	timer.restart();
}

void PlayerAttack_AState::on_update(float delta)
{
	timer.on_update(delta);
	update_hit_box_position();

	Player* player = CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		//player->switch_state("dead");
	}

	else if (!player->get_attacking())
	{
		if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
		}

		else if (player->get_move_axis() != 0)
		{
			player->switch_state("run");
		}
	}
}

void PlayerAttack_AState::on_exit()
{
	Player* player = CharacterManager::instance()->get_player();

	player->get_hit_box()->set_enabled(false);
	player->set_attacking(false);
}

void PlayerAttack_AState::update_hit_box_position()
{
	Player* player = CharacterManager::instance()->get_player();
	CollisionBox* hit_box = player->get_hit_box();

	hit_box->set_position(Vector2(player->get_logical_center().x + 16, player->get_logical_center().y));
}

PlayerAttack_BState::PlayerAttack_BState()
{
	timer.set_wait_time(0.5f); //Define Later
	timer.set_one_shot(false);
	timer.set_callback(
		[&]()
		{
			CharacterManager::instance()->get_player()->set_attacking(false);
		}
	);

	CharacterManager::instance()->get_player()->get_hit_box()->set_size(Vector2(8*16, 6*16));
}

void PlayerAttack_BState::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();

	player->set_animation("attack_B");
	player->get_hit_box()->set_enabled(true);
	player->set_attacking(true);
	update_hit_box_position();
	player->on_attack();
	timer.restart();
}

void PlayerAttack_BState::on_update(float delta)
{

	timer.on_update(delta);
	update_hit_box_position();

	Player* player = CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		//player->switch_state("dead");
	}

	else if (!player->get_attacking())
	{
		if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
		}

		else if (player->get_move_axis() != 0)
		{
			player->switch_state("run");
		}
	}
}

void PlayerAttack_BState::on_exit()
{
	Player* player = CharacterManager::instance()->get_player();

	player->get_hit_box()->set_enabled(false);
	player->set_attacking(false);
}

void PlayerAttack_BState::update_hit_box_position()
{
	Player* player = CharacterManager::instance()->get_player();
	CollisionBox* hit_box = player->get_hit_box();

	hit_box->set_position(Vector2(player->get_logical_center().x, player->get_logical_center().y));

}