extern int attack_animation_offset_x;

bool can_chain_attack() const
{
<<<<<<< HEAD
    // Allow buffering next attack while current attack playing
    return !is_attack_cd && is_attack_key_down;
=======
    // Allow input buffering during current attack even if the attack cooldown
    // timer is still running. The combo transitions are driven by animation
    // timing instead of the cooldown gate, so keep only the input check here
    // to avoid missing follow-up attacks.
    return is_attack_key_down;
}

// Attack animation offset helpers
void set_attack_animation_offset_x(int offset)
{
    attack_animation_offset_x = offset;
}

int get_attack_animation_offset_x() const
{
    return attack_animation_offset_x;
}

void clear_attack_animation_offset()
{
    attack_animation_offset_x = 0;
>>>>>>> e8c519d30314a470f9a0a38704c20abcd76aef1e
}