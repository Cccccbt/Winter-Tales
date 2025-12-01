bool can_chain_attack() const
{
    // Allow input buffering during current attack
    return is_attack_key_down && !is_attack_cd;
}