#pragma once

#include <unordered_map>
#include <vector>
#include "character.h"
#include "player.h"

// Forward declaration to avoid circular dependency.
class MagicBear;

// Central registry for all characters with helpers for update, render, and input.
class CharacterManager
{
public:
        static CharacterManager* instance();

        Character* create_character(const std::string& id);
        void destroy_character(const std::string& id);

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
