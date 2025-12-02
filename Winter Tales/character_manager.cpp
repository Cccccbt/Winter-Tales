#include "character_manager.h"
#include "player.h"

CharacterManager* CharacterManager::character_manager = nullptr;

CharacterManager* CharacterManager::instance()
{
	if (!character_manager)
	{
		character_manager = new CharacterManager();
	}

	return character_manager;
}

Character* CharacterManager::create_character(const std::string& id)
{
	Character* character = new Character();

	character_list[id] = character;

	return character;
}

void CharacterManager::destroy_character(const std::string& id)
{
	auto it = character_list.find(id);
	if (it != character_list.end())
	{
		delete it->second;
		character_list.erase(it);
	}
}

Player* CharacterManager::get_player()
{
	return player;
}

MagicBear* CharacterManager::get_magic_bear()
{
	return magic_bear;
}

void CharacterManager::on_input(const ExMessage& msg)
{
	for (auto i = character_list.begin(); i != character_list.end(); i++)
	{
		i->second->on_input(msg);
		
	}

	player->on_input(msg);
}

void CharacterManager::on_update(float delta)
{
	for (auto i = character_list.begin(); i != character_list.end(); i++)
	{
		i->second->on_update(delta);
		
	}
	
	player->on_update(delta);
	magic_bear->on_update(delta);
}

void CharacterManager::on_render()
{
	for (auto i = character_list.begin(); i != character_list.end(); i++)
	{
		i->second->on_render();
	}
	player->on_render();
	magic_bear->on_render();
}

CharacterManager::CharacterManager()
{
	Player* player = new Player();
	this->player = player;
	player->set_position(Vector2(40, 400));
	player->set_enable_gravity(true);

	MagicBear* magic_bear = new MagicBear();
	this->magic_bear = magic_bear;
	magic_bear->set_position(Vector2(400, 400));
	magic_bear->set_enable_gravity(true);
};

CharacterManager::~CharacterManager()
{
	for (auto i = character_list.begin(); i != character_list.end(); i++)
	{
		delete i->second;
	}
};