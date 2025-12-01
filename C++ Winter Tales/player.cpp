void Player::on_attack()
{
    timer_attack_cd.restart();
    is_attack_cd = true;
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
}