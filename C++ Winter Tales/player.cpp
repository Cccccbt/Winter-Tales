void Player::on_attack()
{
    timer_attack_cd.restart();
    is_attack_cd = true;
    attack_combo_up();

    // Restart inactivity combo reset window
    timer_combo_reset.restart();
}