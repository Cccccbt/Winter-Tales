#include "character_manager.h"
#include "player.h"
#include "magic_bear.h"
#include "bullet_time_manager.h"
#include <algorithm>
#include <cmath>
#include <graphics.h>

namespace
{
        float clamp01(float value)
        {
                return std::clamp(value, 0.0f, 1.0f);
        }

        void draw_bar(int x, int y, int width, int height, float ratio, COLORREF fill_color, COLORREF background_color, COLORREF border_color)
        {
                ratio = clamp01(ratio);

                setfillcolor(background_color);
                fillrectangle(x, y, x + width, y + height);

                int filled_width = static_cast<int>(width * ratio);
                setfillcolor(fill_color);
                fillrectangle(x, y, x + filled_width, y + height);

                setlinecolor(border_color);
                rectangle(x, y, x + width, y + height);
        }

        void draw_mp_clock(int center_x, int center_y, int radius, const Player* player)
        {
                if (!player)
                {
                        return;
                }

                constexpr double PI = 3.14159265358979323846;
                const int max_mp = std::max(player->get_max_mp(), 1);
                const float ratio = clamp01(static_cast<float>(player->get_current_mp()) / max_mp);

                setfillcolor(RGB(20, 24, 36));
                solidcircle(center_x, center_y, radius);

                setfillcolor(RGB(32, 38, 54));
                solidcircle(center_x, center_y, radius - 4);

                setlinecolor(RGB(70, 80, 105));
                circle(center_x, center_y, radius);

                setlinestyle(PS_SOLID, 3);
                setlinecolor(RGB(45, 52, 70));
                const int ring_segments = 64;
                for (int i = 0; i < ring_segments; ++i)
                {
                        double t = static_cast<double>(i) / ring_segments;
                        double angle = -PI / 2 + t * 2 * PI;
                        int inner = radius - 2;
                        int outer = radius;
                        int x1 = center_x + static_cast<int>(std::cos(angle) * inner);
                        int y1 = center_y + static_cast<int>(std::sin(angle) * inner);
                        int x2 = center_x + static_cast<int>(std::cos(angle) * outer);
                        int y2 = center_y + static_cast<int>(std::sin(angle) * outer);
                        line(x1, y1, x2, y2);
                }

                setlinecolor(RGB(108, 190, 255));
                int lit_segments = static_cast<int>(ring_segments * ratio);
                for (int i = 0; i <= lit_segments; ++i)
                {
                        double t = static_cast<double>(i) / ring_segments;
                        double angle = -PI / 2 + t * 2 * PI;
                        int inner = radius - 2;
                        int outer = radius;
                        int x1 = center_x + static_cast<int>(std::cos(angle) * inner);
                        int y1 = center_y + static_cast<int>(std::sin(angle) * inner);
                        int x2 = center_x + static_cast<int>(std::cos(angle) * outer);
                        int y2 = center_y + static_cast<int>(std::sin(angle) * outer);
                        line(x1, y1, x2, y2);
                }

                setlinecolor(RGB(200, 210, 225));
                for (int i = 0; i < max_mp; ++i)
                {
                        double t = static_cast<double>(i) / max_mp;
                        double angle = -PI / 2 + t * 2 * PI;
                        int inner = radius - 8;
                        int outer = radius - 2;
                        int x1 = center_x + static_cast<int>(std::cos(angle) * inner);
                        int y1 = center_y + static_cast<int>(std::sin(angle) * inner);
                        int x2 = center_x + static_cast<int>(std::cos(angle) * outer);
                        int y2 = center_y + static_cast<int>(std::sin(angle) * outer);
                        line(x1, y1, x2, y2);
                }

                double hand_angle = -PI / 2 + ratio * 2 * PI;
                int hand_length = radius - 7;
                int hand_x = center_x + static_cast<int>(std::cos(hand_angle) * hand_length);
                int hand_y = center_y + static_cast<int>(std::sin(hand_angle) * hand_length);
                setlinecolor(RGB(108, 190, 255));
                setlinestyle(PS_SOLID, 2);
                line(center_x, center_y, hand_x, hand_y);

                setfillcolor(RGB(15, 18, 28));
                solidcircle(center_x, center_y, 3);

                setlinestyle(PS_SOLID, 1);
        }
}

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
	
	magic_bear->on_update(delta);
	player->on_update(delta);
}

void CharacterManager::on_render()
{
        for (auto i = character_list.begin(); i != character_list.end(); i++)
        {
                i->second->on_render();
        }

        magic_bear->on_render();

        BulletTimeManager::instance()->post_process();

        player->on_render();

        render_ui();
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

void CharacterManager::render_ui()
{
        const int padding = 14;
        const int player_bar_width = 180;
        const int player_bar_height = 12;

        float player_hp_ratio = 0.0f;
        if (player && player->get_max_hp() > 0)
        {
                player_hp_ratio = clamp01(static_cast<float>(player->get_hp()) / player->get_max_hp());
        }

        draw_bar(padding, padding, player_bar_width, player_bar_height, player_hp_ratio,
                 RGB(220, 82, 94), RGB(60, 24, 32), RGB(255, 160, 170));

        const int clock_radius = 18;
        const int clock_x = padding + clock_radius;
        const int clock_y = padding + player_bar_height + clock_radius + 6;
        draw_mp_clock(clock_x, clock_y, clock_radius, player);

        const int bear_bar_width = 240;
        const int bear_bar_height = 12;
        const int bear_bar_x = (getwidth() - bear_bar_width) / 2;
        const int bear_bar_y = getheight() - bear_bar_height - padding;

        float bear_hp_ratio = 0.0f;
        if (magic_bear && magic_bear->get_max_hp() > 0)
        {
                bear_hp_ratio = clamp01(static_cast<float>(magic_bear->get_hp()) / magic_bear->get_max_hp());
        }

        draw_bar(bear_bar_x, bear_bar_y, bear_bar_width, bear_bar_height, bear_hp_ratio,
                 RGB(255, 196, 102), RGB(70, 46, 20), RGB(255, 220, 160));
}