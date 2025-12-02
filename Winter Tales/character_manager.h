#pragma once
#include "character.h"
#include "player.h"
#include "magic_bear.h"
#include <vector>
#include <unordered_map>
class CharacterManager
{
public:
	static CharacterManager* instance();

	Character* create_character(const std::string&);
	void destroy_character(const std::string&);

	Player* get_player();
	void on_update(float delta);
	void on_render();
	void on_input(const ExMessage& msg);

	MagicBear* get_magic_bear();

private:
	static CharacterManager* character_manager;
	std::unordered_map<std::string, Character*> character_list;
	Player* player;
	MagicBear* magic_bear;

	CharacterManager();
	~CharacterManager();
};