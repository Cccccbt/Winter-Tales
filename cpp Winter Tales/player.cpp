Player::Player()
{
	is_facing_left = false;
	position = Vector2(250, 200);
	logic_height = 64;

	hit_box->set_size(Vector2(32, 64));
	hurt_box->set_size(Vector2(16, 64));

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Enemy);

	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);
	hurt_box->set_enabled(true);

	hurt_box->set_on_collide([this]() 
		{
			this->on_hurt();
		});

	timer_combo_reset.set_wait_time(CD_COMBO_RESET);
	timer_combo_reset.set_one_shot(true);
	timer_combo_reset.set_callback([this]()
		{
			attack_combo = 0;
		});

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_roll_cd.set_wait_time(CD_ROLL);

	timer_attack_cd.set_one_shot(true);
	timer_roll_cd.set_one_shot(true);

	timer_attack_cd.set_callback([this]()
		{
			is_attack_cd = false;
		});

	timer_roll_cd.set_callback([this]()
		{
			is_roll_cd = false;
		});

	// Pre-allocate and initialize animations safely
	animation_pool.emplace("attack_1", AnimationGroup());
	animation_pool["attack_1"].left.set_interval(0.05f);
	animation_pool["attack_1"].left.set_is_loop(false);
	animation_pool["attack_1"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_1"].left.add_frame(ResourceManager::instance()->find_image("player_attack_1_left"), 9);
	animation_pool["attack_1"].right.set_interval(0.05f);
	animation_pool["attack_1"].right.set_is_loop(false);
	animation_pool["attack_1"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_1"].right.add_frame(ResourceManager::instance()->find_image("player_attack_1_right"), 9);

	animation_pool.emplace("attack_2", AnimationGroup());
	animation_pool["attack_2"].left.set_interval(0.05f);
	animation_pool["attack_2"].left.set_is_loop(false);
	animation_pool["attack_2"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_2"].left.add_frame(ResourceManager::instance()->find_image("player_attack_2_left"), 14);
	animation_pool["attack_2"].right.set_interval(0.05f);
	animation_pool["attack_2"].right.set_is_loop(false);
	animation_pool["attack_2"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_2"].right.add_frame(ResourceManager::instance()->find_image("player_attack_2_right"), 14);

	animation_pool.emplace("attack_3", AnimationGroup());
	animation_pool["attack_3"].left.set_interval(0.05f);
	animation_pool["attack_3"].left.set_is_loop(false);
	animation_pool["attack_3"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_3"].left.add_frame(ResourceManager::instance()->find_image("player_attack_3_left"), 6);
	animation_pool["attack_3"].right.set_interval(0.05f);
	animation_pool["attack_3"].right.set_is_loop(false);
	animation_pool["attack_3"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["attack_3"].right.add_frame(ResourceManager::instance()->find_image("player_attack_3_right"), 6);

	animation_pool.emplace("idle", AnimationGroup());
	animation_pool["idle"].left.set_interval(0.1f);
	animation_pool["idle"].left.set_is_loop(true);
	animation_pool["idle"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle"].left.add_frame(ResourceManager::instance()->find_image("player_idle_left"), 6);
	animation_pool["idle"].right.set_interval(0.1f);
	animation_pool["idle"].right.set_is_loop(true);
	animation_pool["idle"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle"].right.add_frame(ResourceManager::instance()->find_image("player_idle_right"), 6);

	animation_pool.emplace("idle_2", AnimationGroup());
	animation_pool["idle_2"].left.set_interval(0.1f);
	animation_pool["idle_2"].left.set_is_loop(true);
	animation_pool["idle_2"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle_2"].left.add_frame(ResourceManager::instance()->find_image("player_idle_2_left"), 18);
	animation_pool["idle_2"].right.set_interval(0.1f);
	animation_pool["idle_2"].right.set_is_loop(true);
	animation_pool["idle_2"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["idle_2"].right.add_frame(ResourceManager::instance()->find_image("player_idle_2_right"), 18);

	animation_pool.emplace("run", AnimationGroup());
	animation_pool["run"].left.set_interval(0.08f);
	animation_pool["run"].left.set_is_loop(true);
	animation_pool["run"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["run"].left.add_frame(ResourceManager::instance()->find_image("player_run_left"), 10);
	animation_pool["run"].right.set_interval(0.08f);
	animation_pool["run"].right.set_is_loop(true);
	animation_pool["run"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["run"].right.add_frame(ResourceManager::instance()->find_image("player_run_right"), 10);

	animation_pool.emplace("hurt", AnimationGroup());
	animation_pool["hurt"].left.set_interval(0.1f);
	animation_pool["hurt"].left.set_is_loop(false);
	animation_pool["hurt"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["hurt"].left.add_frame(ResourceManager::instance()->find_image("player_hurt_left"), 4);
	animation_pool["hurt"].right.set_interval(0.1f);
	animation_pool["hurt"].right.set_is_loop(false);
	animation_pool["hurt"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["hurt"].right.add_frame(ResourceManager::instance()->find_image("player_hurt_right"), 4);

	animation_pool.emplace("dead", AnimationGroup());
	animation_pool["dead"].left.set_interval(0.1f);
	animation_pool["dead"].left.set_is_loop(false);
	animation_pool["dead"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["dead"].left.add_frame(ResourceManager::instance()->find_image("player_dead_left"), 6);
	animation_pool["dead"].right.set_interval(0.1f);
	animation_pool["dead"].right.set_is_loop(false);
	animation_pool["dead"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["dead"].right.add_frame(ResourceManager::instance()->find_image("player_dead_right"), 6);

	animation_pool.emplace("jump", AnimationGroup());
	animation_pool["jump"].left.set_interval(0.1f);
	animation_pool["jump"].left.set_is_loop(false);
	animation_pool["jump"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["jump"].left.add_frame(ResourceManager::instance()->find_image("player_jump_left"), 12);
	animation_pool["jump"].right.set_interval(0.1f);
	animation_pool["jump"].right.set_is_loop(false);
	animation_pool["jump"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["jump"].right.add_frame(ResourceManager::instance()->find_image("player_jump_right"), 12);
	animation_pool["jump"].right.set_on_finished(
		[this]()
		{
			std::cout << "Jump animation finished." << std::endl;
		});

	animation_pool.emplace("roll", AnimationGroup());
	animation_pool["roll"].left.set_interval(0.1f);
	animation_pool["roll"].left.set_is_loop(false);
	animation_pool["roll"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["roll"].left.add_frame(ResourceManager::instance()->find_image("player_roll_left"), 16);
	animation_pool["roll"].right.set_interval(0.1f);
	animation_pool["roll"].right.set_is_loop(false);
	animation_pool["roll"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["roll"].right.add_frame(ResourceManager::instance()->find_image("player_roll_right"), 16);

	animation_pool.emplace("charge", AnimationGroup());
	animation_pool["charge"].left.set_interval(0.08f);
	animation_pool["charge"].left.set_is_loop(true);
	animation_pool["charge"].left.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["charge"].left.add_frame(ResourceManager::instance()->find_image("player_charge_left"), 6);
	animation_pool["charge"].right.set_interval(0.08f);
	animation_pool["charge"].right.set_is_loop(true);
	animation_pool["charge"].right.set_AnchorMode(Animation::AnchorMode::BottomCentered);
	animation_pool["charge"].right.add_frame(ResourceManager::instance()->find_image("player_charge_right"), 6);

	// Set initial animation
	current_animation = &animation_pool["idle"];

	//Initialize StateMachine
	state_machine.register_state("idle", new PlayerIdle());
	state_machine.register_state("run", new PlayerRun());
	state_machine.register_state("jump", new PlayerJump());
	state_machine.register_state("roll", new PlayerRoll());
	state_machine.register_state("attack_1", new PlayerAttack1());
	state_machine.register_state("attack_2", new PlayerAttack2());
	state_machine.register_state("attack_3", new PlayerAttack3());
	state_machine.register_state("hurt", new PlayerHurt());
	state_machine.register_state("dead", new PlayerDead());

	state_machine.set_entry("idle");
}