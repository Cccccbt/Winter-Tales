#include "magic_bear_state_nodes.h"
#include <iostream>
MagicBearIdle::MagicBearIdle()
{
	timer_idle.set_wait_time(2.0f);
	timer_idle.set_one_shot(true);
	timer_idle.set_callback([]()
	{
		// Callback logic can be implemented here if needed
		CharacterManager::instance()->get_magic_bear()->switch_state("walk");
	});
}

MagicBearIdle::~MagicBearIdle()
{
}

void MagicBearIdle::on_enter()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	bear->set_animation("idle");
	bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
	timer_idle.restart();
	std::cout << "MagicBear entered Idle state." << std::endl;
}



void MagicBearIdle::on_update(float delta)
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();

        timer_idle.on_update(delta);

        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }

        if (bear->consume_pending_sneer())
        {
                bear->switch_state("sneer");
                return;
        }

        if (bear->is_global_attack_cooling())
        {
                if (!bear->is_player_in_close_range())
                {
                        bear->switch_state("walk");
                }
                return;
        }

        if (!bear->is_player_in_close_range())
        {
                bear->switch_state("walk");
                return;
        }

        if (bear->is_player_in_close_range() && bear->can_attack_run())
        {
                bear->switch_state("attack2");
        }
        else if (bear->is_player_in_close_range() && bear->can_attack_bite())
        {
                bear->switch_state("attack1");
        }
        else if (bear->get_phase_index() >= 2 && (bear->is_player_in_mid_range() || bear->is_player_in_far_range()) && bear->can_attack_ball())
        {
                bear->switch_state("attack3");
        }
        else if ((bear->is_player_in_mid_range() || bear->is_player_in_far_range()) && bear->can_attack_ray())
        {
                bear->switch_state("attack4");
        }

}
void MagicBearIdle::on_exit()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	std::cout << "MagicBear exited Idle state." << std::endl;
}


MagicBearWalk::MagicBearWalk()
{
	timer_walk.set_wait_time(3.0f);
	timer_walk.set_one_shot(true);
	timer_walk.set_callback([]()
	{
		// Callback logic can be implemented here if needed
		CharacterManager::instance()->get_magic_bear()->switch_state("idle");
	});
}

MagicBearWalk::~MagicBearWalk()
{
}

void MagicBearWalk::on_enter()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	bear->set_animation("walk");
	bear->get_hit_box()->set_enabled(false);
	timer_walk.restart();
	std::cout << "MagicBear entered Walk state." << std::endl;
}


void MagicBearWalk::on_update(float delta)
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_velocity(Vector2(bear->get_is_facing_left() ? -bear->get_phase_walk_speed() : bear->get_phase_walk_speed(), bear->get_velocity().y));

        timer_walk.on_update(delta);

        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }

        if (bear->consume_pending_sneer())
        {
                bear->switch_state("sneer");
                return;
        }

        if (bear->is_player_in_close_range() && bear->can_attack_run())
        {
                bear->switch_state("attack2");
        }
        else if (bear->is_player_in_close_range() && bear->can_attack_bite())
        {
                bear->switch_state("attack1");
        }
        else if (bear->get_phase_index() >= 2 && (bear->is_player_in_mid_range() || bear->is_player_in_far_range()) && bear->can_attack_ball())
        {
                bear->switch_state("attack3");
        }
        else if ((bear->is_player_in_mid_range() || bear->is_player_in_far_range()) && bear->can_attack_ray())
        {
                bear->switch_state("attack4");
        }
}
void MagicBearWalk::on_exit()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
	std::cout << "MagicBear exited Walk state." << std::endl;
}

MagicBearAttack1::MagicBearAttack1()
{
	timer_attack.set_wait_time(1.0f);
	timer_attack.set_one_shot(true);
	timer_attack.set_callback([]()
	{
		CharacterManager::instance()->get_magic_bear()->switch_state("idle");
	});
}

MagicBearAttack1::~MagicBearAttack1()
{
}

void MagicBearAttack1::on_enter()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
	bear->get_hit_box()->set_size(Vector2(40.0f, 40.0f));
	bear->get_hit_box()->set_enabled(true);
	bear->set_animation("attack1");
	enter_facing_left = bear->get_is_facing_left();
	bear->on_bite();
	timer_attack.restart();
	std::cout << "MagicBear entered Attack1 state." << std::endl;
}

void MagicBearAttack1::on_update(float delta)
{
	timer_attack.on_update(delta);

	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	bear->set_is_facing_left(enter_facing_left);
	update_collision_box();
	if (bear->get_hp() <= 0)
	{
		bear->switch_state("dead");
		return;
	}

	Player* player = CharacterManager::instance()->get_player();
}


void MagicBearAttack1::on_exit()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->get_hit_box()->set_enabled(false);
        bear->start_attack1_cooldown();
        bear->start_global_attack_cooldown();
        std::cout << "MagicBear exited Attack1 state." << std::endl;
}

void MagicBearAttack1::update_collision_box()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	Vector2 center = bear->get_logical_center();
	if (bear->get_is_facing_left())
	{
		bear->get_hit_box()->set_position(Vector2(center.x - 50.0f, center.y - 36.0f));
	}
	else
	{
		bear->get_hit_box()->set_position(Vector2(center.x + 50.0f, center.y - 36.0f));
	}
}


MagicBearAttack2::MagicBearAttack2()
{
        timer_attack.set_wait_time(1.0f);
        timer_attack.set_one_shot(true);
        timer_attack.set_callback([]()
        {
                CharacterManager::instance()->get_magic_bear()->switch_state("idle");
        });
}

MagicBearAttack2::~MagicBearAttack2()
{
}

void MagicBearAttack2::on_enter()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_animation("attack2");
        bear->on_run();
        bear->get_hit_box()->set_enabled(false);
		enter_facing_left = bear->get_is_facing_left();
        timer_attack.restart();
        std::cout << "MagicBear entered Attack2 state." << std::endl;
}

void MagicBearAttack2::on_update(float delta)
{
        timer_attack.on_update(delta);
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
		bear->set_is_facing_left(enter_facing_left);
        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }
}

void MagicBearAttack2::on_exit()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
        bear->start_attack2_cooldown();
        bear->start_global_attack_cooldown();
        std::cout << "MagicBear exited Attack2 state." << std::endl;
}

MagicBearAttack3::MagicBearAttack3()
{
        timer_attack.set_wait_time(3.0f);
        timer_attack.set_one_shot(true);
        timer_attack.set_callback([]()
        {
                CharacterManager::instance()->get_magic_bear()->switch_state("idle");
        });

		timer_ray.set_wait_time(0.9f);
		timer_ray.set_one_shot(true);
        timer_ray.set_callback([this]()
        {
            CharacterManager::instance()->get_magic_bear()->on_ray(enter_facing_left);
			});
}

MagicBearAttack3::~MagicBearAttack3()
{
}

void MagicBearAttack3::on_enter()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
        bear->set_animation("attack3");
        //bear->on_ray();
        bear->get_hit_box()->set_enabled(false);
		enter_facing_left = bear->get_is_facing_left();
        timer_attack.restart();
		timer_ray.restart();
        std::cout << "MagicBear entered Attack3 state." << std::endl;
}

void MagicBearAttack3::on_update(float delta)
{
        timer_attack.on_update(delta);
		timer_ray.on_update(delta);
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
		bear->set_is_facing_left(enter_facing_left);
        update_collision_box();
        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }
}

void MagicBearAttack3::on_exit()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->get_hit_box()->set_enabled(false);
        bear->start_attack3_cooldown();
        bear->start_global_attack_cooldown();
        std::cout << "MagicBear exited Attack3 state." << std::endl;
}

void MagicBearAttack3::update_collision_box()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        Vector2 center = bear->get_logical_center();
        if (bear->get_is_facing_left())
        {
                bear->get_hit_box()->set_position(Vector2(center.x - 50.0f, center.y));
        }
        else
        {
                bear->get_hit_box()->set_position(Vector2(center.x + 50.0f, center.y));
        }
}

MagicBearAttack4::MagicBearAttack4()
{
        timer_attack.set_wait_time(2.5f);
        timer_attack.set_one_shot(true);
        timer_attack.set_callback([]()
        {
                CharacterManager::instance()->get_magic_bear()->switch_state("idle");
        });
}

MagicBearAttack4::~MagicBearAttack4()
{
}

void MagicBearAttack4::on_enter()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
        bear->set_animation("attack4");
        //bear->on_ball();
        bear->get_hit_box()->set_enabled(false);
		enter_facing_left = bear->get_is_facing_left();
        timer_attack.restart();
        std::cout << "MagicBear entered Attack4 state." << std::endl;
}

void MagicBearAttack4::on_update(float delta)
{
        timer_attack.on_update(delta);
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
		bear->set_is_facing_left(enter_facing_left);
        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }
}

void MagicBearAttack4::on_exit()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->start_attack4_cooldown();
        bear->start_global_attack_cooldown();
        std::cout << "MagicBear exited Attack4 state." << std::endl;
}

void MagicBearAttack4::update_collision_box()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        Vector2 center = bear->get_logical_center();
        if (bear->get_is_facing_left())
        {
                bear->get_hit_box()->set_position(Vector2(center.x - 70.0f, center.y));
        }
        else
        {
                bear->get_hit_box()->set_position(Vector2(center.x + 70.0f, center.y));
        }
}

MagicBearSneer::MagicBearSneer()
{
        sneer_timer.set_wait_time(1.2f);
        sneer_timer.set_one_shot(true);
        sneer_timer.set_callback([]()
        {
                CharacterManager::instance()->get_magic_bear()->switch_state("idle");
        });
}

MagicBearSneer::~MagicBearSneer()
{
}

void MagicBearSneer::on_enter()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_animation("sneer");
        bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
        bear->get_hit_box()->set_enabled(false);
        sneer_timer.restart();
        std::cout << "MagicBear entered Sneer state." << std::endl;
}

void MagicBearSneer::on_update(float delta)
{
        sneer_timer.on_update(delta);
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }
}

void MagicBearSneer::on_exit()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->start_global_attack_cooldown();
        std::cout << "MagicBear exited Sneer state." << std::endl;
}

MagicBearHurt::MagicBearHurt()
{
        hurt_timer.set_wait_time(0.6f);
        hurt_timer.set_one_shot(true);
        hurt_timer.set_callback([]()
        {
                CharacterManager::instance()->get_magic_bear()->switch_state("idle");
        });
}

MagicBearHurt::~MagicBearHurt()
{
}

void MagicBearHurt::on_enter()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_animation("hurt");
        bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
        bear->get_hit_box()->set_enabled(false);
        enter_facing_left = bear->get_is_facing_left();
        bear->enter_hurt_invulnerability();
        hurt_timer.restart();
        std::cout << "MagicBear entered Hurt state." << std::endl;
}

void MagicBearHurt::on_update(float delta)
{
        hurt_timer.on_update(delta);
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->set_is_facing_left(enter_facing_left);
        if (bear->get_hp() <= 0)
        {
                bear->switch_state("dead");
                return;
        }
}

void MagicBearHurt::on_exit()
{
        MagicBear* bear = CharacterManager::instance()->get_magic_bear();
        bear->get_hit_box()->set_enabled(false);
        bear->clear_hurt_invulnerability();
        std::cout << "MagicBear exited Hurt state." << std::endl;
}

MagicBearDead::MagicBearDead()
{
}

MagicBearDead::~MagicBearDead()
{
}

void MagicBearDead::on_enter()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	bear->set_animation("dead");
	bear->set_velocity(Vector2(0.0f, bear->get_velocity().y));
	bear->get_hit_box()->set_enabled(false);
	std::cout << "MagicBear entered Dead state." << std::endl;
}

void MagicBearDead::on_update(float delta)
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
}

void MagicBearDead::on_exit()
{
	MagicBear* bear = CharacterManager::instance()->get_magic_bear();
	std::cout << "MagicBear exited Dead state." << std::endl;
}





