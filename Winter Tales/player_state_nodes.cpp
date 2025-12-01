#include "player_state_nodes.h"
#include "character_manager.h"

PlayerAttack1::PlayerAttack1()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shot(true);
	timer.set_callback([&]()
	{
		CharacterManager::instance()->get_player()->set_attacking(false);
	});
}

void PlayerAttack1::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->set_animation("attack_1");
	player->set_attacking(true);
	player->on_attack();

	CollisionBox* hit_box = player->get_hit_box();
	hit_box->set_enabled(true);
	update_hit_box_position();

	timer.restart();
	std::cout << "Enter PlayerAttack1, attack_combo " << player->get_attack_combo() << std::endl;
	//Play attack sound
}

void PlayerAttack1::on_update(float delta)
{
	timer.on_update(delta);
	
	update_hit_box_position();

	Player* player = CharacterManager::instance()->get_player();

	player->set_velocity(Vector2(0, player->get_velocity().y));

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
		return;
	}

        // Check for combo transitions while attacking
        if (player->can_attack() && !player->get_attacking())
        {
                if (player->get_attack_combo() == 1)
                {
                        player->switch_state("attack_2");
                        return;
                }
        }

	// Only transition out when attack is finished (timer callback sets is_attacking = false)
	if (!player->get_attacking())
	{
		if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
		}
		else
		{
			player->switch_state("run");
		}
	}
}

void PlayerAttack1::on_exit()
{
	CollisionBox* hit_box = CharacterManager::instance()->get_player()->get_hit_box();
	hit_box->set_enabled(false);
	CharacterManager::instance()->get_player()->set_attacking(false);
	std::cout << "Exit PlayerAttack1, attack_combo " << CharacterManager::instance()->get_player()->get_attack_combo() << std::endl;
}

void PlayerAttack1::update_hit_box_position()
{
	Player* player = CharacterManager::instance()->get_player();
	CollisionBox* hit_box = player->get_hit_box();
	Vector2 player_pos = player->get_position();
	Vector2 hit_box_size = hit_box->get_size();
	if (player->get_is_facing_left())
	{
		hit_box->set_position(Vector2(
			player_pos.x - hit_box_size.x,
			player_pos.y - hit_box_size.y));
	}
	else
	{
		hit_box->set_position(Vector2(
			player_pos.x,
			player_pos.y - hit_box_size.y));
	}
}

PlayerAttack2::PlayerAttack2()
{
	timer.set_wait_time(0.75f);
	timer.set_one_shot(true);
	timer.set_callback([&]()
	{
		CharacterManager::instance()->get_player()->set_attacking(false);
	});
}

void PlayerAttack2::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->set_animation("attack_2");
	player->set_attacking(true);
	player->on_attack();

	CollisionBox* hit_box = player->get_hit_box();
	hit_box->set_size(Vector2(64, 16));
	update_hit_box_position();
	hit_box->set_enabled(true);

	timer.restart();
	std::cout << "Enter PlayerAttack2, attack_combo " << player->get_attack_combo() << std::endl;
}

void PlayerAttack2::on_update(float delta)
{
        timer.on_update(delta);
        update_hit_box_position();


        Player* player = CharacterManager::instance()->get_player();
		player->set_velocity(Vector2(0, player->get_velocity().y));

        // Allow chaining to the third attack while the second animation is playing
        if (player->can_attack() && !player->get_attacking())
        {
                if (player->get_attack_combo() == 2)
                {
                        player->switch_state("attack_3");
                        return;
                }
        }

        if (player->get_hp() <= 0)
        {
                player->switch_state("dead");
        }
        else if (!player->get_attacking())
	{
		if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
		}
		else if (player->is_on_floor())
		{
			player->switch_state("run");
		}
	}
}

void PlayerAttack2::on_exit()
{
	CollisionBox* hit_box = CharacterManager::instance()->get_player()->get_hit_box();
	hit_box->set_enabled(false);
	CharacterManager::instance()->get_player()->set_attacking(false);
	std::cout << "Exit PlayerAttack2, attack_combo " << CharacterManager::instance()->get_player()->get_attack_combo() << std::endl;
}

void PlayerAttack2::update_hit_box_position()
{
	Player* player = CharacterManager::instance()->get_player();
	CollisionBox* hit_box = player->get_hit_box();
	Vector2 player_pos = player->get_position();
	Vector2 hit_box_size = hit_box->get_size();
	hit_box->set_position(player->get_logical_center() + (player->get_is_facing_left() ? Vector2(-56, -20) : Vector2(56, -20)));

}

PlayerAttack3::PlayerAttack3()
{
	timer.set_wait_time(0.35f);
	timer.set_one_shot(true);
	timer.set_callback([&]()
	{
		CharacterManager::instance()->get_player()->set_attacking(false);
	});
}

void PlayerAttack3::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->set_animation("attack_3");
	player->set_attacking(true);
	player->on_attack();

	CollisionBox* hit_box = player->get_hit_box();
	hit_box->set_enabled(true);
	update_hit_box_position();

	timer.restart();
	std::cout << "Enter PlayerAttack3, attack_combo " << player->get_attack_combo() << std::endl;
}

void PlayerAttack3::on_update(float delta)
{
	timer.on_update(delta);
	update_hit_box_position();

	Player* player = CharacterManager::instance()->get_player();
	player->set_velocity(Vector2(0, player->get_velocity().y));

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (!player->get_attacking())
	{
		if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
		}
		else if (player->is_on_floor())
		{
			player->switch_state("run");
		}
	}
}

void PlayerAttack3::on_exit()
{
	CollisionBox* hit_box = CharacterManager::instance()->get_player()->get_hit_box();
	hit_box->set_enabled(false);
	CharacterManager::instance()->get_player()->set_attacking(false);
	std::cout << "Exit PlayerAttack3, attack_combo " << CharacterManager::instance()->get_player()->get_attack_combo() << std::endl;
}

void PlayerAttack3::update_hit_box_position()
{
	Player* player = CharacterManager::instance()->get_player();
	CollisionBox* hit_box = player->get_hit_box();
	Vector2 player_pos = player->get_position();
	Vector2 hit_box_size = hit_box->get_size();
	if (player->get_is_facing_left())
	{
		hit_box->set_position(Vector2(
			player_pos.x - hit_box_size.x,
			player_pos.y - hit_box_size.y));
	}
	else
	{
		hit_box->set_position(Vector2(
			player_pos.x,
			player_pos.y - hit_box_size.y));
	}
}

PlayerDead::PlayerDead()
{
	timer.set_wait_time(2.0f);
	timer.set_one_shot(true);
	timer.set_callback([&]()
	{
		// Placeholder for respawn or game over logic
			MessageBox(GetHWnd(), _T("No......"), _T("You Dead"), MB_OK);
			exit(0);
	});
}

void PlayerDead::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->set_animation("dead");
	//Play death sound
}

void PlayerDead::on_update(float delta)
{
	timer.on_update(delta);
}

void PlayerDead::on_exit()
{
	// Dead state typically doesn't need exit logic
}

PlayerIdle::PlayerIdle()
{

}

void PlayerIdle::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("idle");
	std::cout << "Enter Idle" << std::endl;
}

void PlayerIdle::on_update(float delta)
{
	Player* player = CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}

	else if (player->can_attack())
	{
		switch (player->get_attack_combo())
		{
		case 0:
			player->switch_state("attack_1");
			break;
		case 1:
			player->switch_state("attack_2");
			break;
		case 2:
			player->switch_state("attack_3");
			break;
		}
	}

	else if (player->get_move_axis() != 0)
	{
		player->switch_state("run");
	}

	else if (player->can_jump())
	{
		player->switch_state("jump");
	}

	else if (player->can_roll())
	{
		player->switch_state("roll");
	}
}

void PlayerIdle::on_exit()
{
	// Idle state typically doesn't need exit logic
	std::cout << "Exit Idle" << std::endl;
}

PlayerJump::PlayerJump()
{
    has_left_ground = false;  // Add this member variable
}

void PlayerJump::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->set_animation("jump");
	player->on_jump();
	has_left_ground = false;  // Reset flag when entering jump state
	std::cout << "Enter Jump" << std::endl;
	//Play jump sound
}

void PlayerJump::on_update(float delta)
{
	Player* player = CharacterManager::instance()->get_player();
	
	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
		std::cout << "Exit Jump to Dead\n";
		return;
	}

	if (player->can_attack())
	{
		player->switch_state("attack_1");
		std::cout << "Exit Jump to Attack";
		return;
	}

	// Track when player leaves the ground
	if (!player->is_on_floor())
	{
		has_left_ground = true;
	}

	// Only transition when:
	// 1. Player has left the ground (prevents immediate exit)
	// 2. Player is falling downward (velocity.y > 0)
	// 3. Player touches the floor
	if (has_left_ground && player->is_on_floor())
	{
		player->on_land();
		if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
			std::cout<<"Exit Jump to Idle\n";
		}
		else
		{
			player->switch_state("run");
			std::cout << "Exit Jump to Run";
		}
	}
}

void PlayerJump::on_exit()
{
	// Jump state typically doesn't need exit logic
	std::cout << "Exit Jump\n";
}

PlayerRoll::PlayerRoll()
{
	timer.set_wait_time(0.35f);
	timer.set_one_shot(true);
	timer.set_callback([&]()
		{
			CharacterManager::instance()->get_player()->set_rolling(false);
		});
}

void PlayerRoll::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->get_hurt_box()->set_enabled(false);
	player->set_animation("roll");
	player->set_rolling(true);
	player->on_roll();
	timer.restart();
	//Play roll sound
	std::cout << "Enter Roll" << std::endl;
}

void PlayerRoll::on_update(float delta)
{
	timer.on_update(delta);

	Player* player = CharacterManager::instance()->get_player();
	if (!player->get_rolling())
	{
		if (player->get_move_axis() != 0)
		{
			player->switch_state("run");
		}
		else if (player->can_jump())
		{
			player->switch_state("jump");
		}

		else
		{
			player->switch_state("idle");
		}
	}
}

void PlayerRoll::on_exit()
{
	Player* player = CharacterManager::instance()->get_player();
	player->get_hurt_box()->set_enabled(true);
	std::cout << "Exit Roll" << std::endl;
}

PlayerRun::PlayerRun()
{

}

void PlayerRun::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("run");
	std::cout << "Enter Run" << std::endl;
	//Play run sound loop
}

void PlayerRun::on_update(float delta)
{
	Player* player = CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->can_attack())
	{
		switch (player->get_attack_combo())
		{
		case 0:
			player->switch_state("attack_1");
			break;
		case 1:
			player->switch_state("attack_2");
			break;
		case 2:
			player->switch_state("attack_3");
			break;
		}
	}
	else if (player->get_move_axis() == 0)
	{
		player->switch_state("idle");
	}
	else if (player->can_jump())
	{
		player->switch_state("jump");
	}
	else if (player->can_roll())
	{
		player->switch_state("roll");
	}
}

void PlayerRun::on_exit()
{
	// Run state typically doesn't need exit logic
	std::cout << "Exit Run" << std::endl;
}

PlayerHurt::PlayerHurt()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shot(true);
	timer.set_callback([&]()
	{
		// End hurt state
	});
}

void PlayerHurt::on_enter()
{
	Player* player = CharacterManager::instance()->get_player();
	player->set_animation("hurt");
	timer.restart();
}

void PlayerHurt::on_update(float delta)
{
	timer.on_update(delta);
	
	Player* player = CharacterManager::instance()->get_player();
	
	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	// Add logic to transition back to appropriate state after hurt animation
}

void PlayerHurt::on_exit()
{
	// Hurt state typically doesn't need exit logic
}