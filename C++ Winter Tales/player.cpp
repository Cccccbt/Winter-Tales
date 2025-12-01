void Player::on_attack()
{
    timer_attack_cd.restart();
    is_attack_cd = true;
<<<<<<< HEAD
    attack_combo_up();

    // Restart inactivity combo reset window
    timer_combo_reset.restart();
=======
    // attack_combo_up();  // REMOVE from here
}

// Track a temporary visual offset for attack-specific animations
int attack_animation_offset_x = 0;

void Player::set_attack_animation_offset_x(int offset)
{
    attack_animation_offset_x = offset;
}

int Player::get_attack_animation_offset_x() const
{
    return attack_animation_offset_x;
}

void Player::clear_attack_animation_offset()
{
    attack_animation_offset_x = 0;
>>>>>>> e8c519d30314a470f9a0a38704c20abcd76aef1e
}