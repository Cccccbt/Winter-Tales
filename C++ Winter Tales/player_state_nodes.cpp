void PlayerAttack1::on_enter()
{
    Player* player = CharacterManager::instance()->get_player();
    player->set_animation("attack_1");
    player->set_attacking(true);
    player->on_attack();
    player->attack_combo_up(); // Move combo advance here (0->1)
    ...
}

void PlayerAttack1::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();
    Player* player = CharacterManager::instance()->get_player();

    if (player->get_hp() <= 0) { player->switch_state("dead"); return; }

    // Buffer next attack while still attacking
    if (player->can_chain_attack() && player->get_attack_combo() == 1)
    {
        player->switch_state("attack_2");
        return;
    }

    if (!player->get_attacking())
    {
        if (player->get_move_axis() == 0) player->switch_state("idle");
        else player->switch_state("run");
    }
}

void PlayerAttack2::on_enter()
{
    Player* player = CharacterManager::instance()->get_player();
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
        return;
    }

    if (!player->get_attacking())
    {
        if (player->get_move_axis() == 0) player->switch_state("idle");
        else player->switch_state("run");
    }
}

void PlayerAttack3::on_enter()
{
    Player* player = CharacterManager::instance()->get_player();
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
    }
}