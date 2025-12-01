void PlayerIdle::on_update(float delta)
{
    Player* player = CharacterManager::instance()->get_player();
<<<<<<< HEAD

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
=======
    player->clear_attack_animation_offset();
    player->set_animation("attack_1");
    player->set_attacking(true);
    player->on_attack();
    player->attack_combo_up(); // Move combo advance here (0->1)
    ...
>>>>>>> e8c519d30314a470f9a0a38704c20abcd76aef1e
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
<<<<<<< HEAD
        switch (player->get_attack_combo())
        {
        case 0: player->switch_state("attack_1"); break;
        case 1: player->switch_state("attack_2"); break;
        case 2: player->switch_state("attack_3"); break;
        }
        std::cout << "Exit Jump to Attack\n";
=======
        if (player->get_move_axis() == 0) player->switch_state("idle");
        else player->switch_state("run");
    }
}

void PlayerAttack2::on_enter()
{
    Player* player = CharacterManager::instance()->get_player();
    player->set_attack_animation_offset_x(-34);
    player->set_animation("attack_2");
    player->set_attacking(true);
    player->on_attack();
    player->attack_combo_up(); // 1->2
    ...
}

void PlayerAttack2::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();
    Player* player = CharacterManager::instance()->get_player();

    if (player->get_hp() <= 0) { player->switch_state("dead"); return; }

    if (player->can_chain_attack() && player->get_attack_combo() == 2)
    {
        player->switch_state("attack_3");
>>>>>>> e8c519d30314a470f9a0a38704c20abcd76aef1e
        return;
    }

    if (!player->is_on_floor())
        has_left_ground = true;

    if (has_left_ground && player->is_on_floor())
    {
<<<<<<< HEAD
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
=======
        player->clear_attack_animation_offset();
        if (player->get_move_axis() == 0) player->switch_state("idle");
        else player->switch_state("run");
    }
}

void PlayerAttack3::on_enter()
{
    Player* player = CharacterManager::instance()->get_player();
    player->clear_attack_animation_offset();
    player->set_animation("attack_3");
    player->set_attacking(true);
    player->on_attack();
    player->attack_combo_up(); // 2->0 reset
    ...
}

void PlayerAttack3::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();
    Player* player = CharacterManager::instance()->get_player();

    if (player->get_hp() <= 0) { player->switch_state("dead"); return; }

    // No further chaining; finish then return
    if (!player->get_attacking())
    {
        if (player->get_move_axis() == 0) player->switch_state("idle");
        else player->switch_state("run");
>>>>>>> e8c519d30314a470f9a0a38704c20abcd76aef1e
    }
}