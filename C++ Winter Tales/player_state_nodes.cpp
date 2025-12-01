void PlayerIdle::on_update(float delta)
{
    Player* player = CharacterManager::instance()->get_player();

    if (player->get_hp() <= 0)
    {
        player->switch_state("dead");
    }
    else if (player->can_attack())
    {
        // USE combo to pick correct attack state instead of always attack_1
        switch (player->get_attack_combo())
        {
        case 0: player->switch_state("attack_1"); break;
        case 1: player->switch_state("attack_2"); break;
        case 2: player->switch_state("attack_3"); break;
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
        case 0: player->switch_state("attack_1"); break;
        case 1: player->switch_state("attack_2"); break;
        case 2: player->switch_state("attack_3"); break;
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
        switch (player->get_attack_combo())
        {
        case 0: player->switch_state("attack_1"); break;
        case 1: player->switch_state("attack_2"); break;
        case 2: player->switch_state("attack_3"); break;
        }
        std::cout << "Exit Jump to Attack\n";
        return;
    }

    if (!player->is_on_floor())
        has_left_ground = true;

    if (has_left_ground && player->is_on_floor())
    {
        player->on_land();
        if (player->get_move_axis() == 0)
        {
            player->switch_state("idle");
            std::cout << "Exit Jump to Idle\n";
        }
        else
        {
            player->switch_state("run");
            std::cout << "Exit Jump to Run\n";
        }
    }
}