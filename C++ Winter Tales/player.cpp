void Player::on_attack()
{
    timer_attack_cd.restart();
    is_attack_cd = true;
    // attack_combo_up();  // REMOVE from here
}