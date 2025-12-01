bool can_chain_attack() const
{
    // Allow buffering next attack while current attack playing
    return !is_attack_cd && is_attack_key_down;
}