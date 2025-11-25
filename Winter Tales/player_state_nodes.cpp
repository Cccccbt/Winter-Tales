#include "player_state_nodes.h"

PlayerAttack_AState::PlayerAttack_AState()
{
	Player* player = CharacterManager::instance()->get_player();

	player->set_animation("attack_A");
	
}