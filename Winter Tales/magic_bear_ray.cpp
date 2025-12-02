#include "magic_bear_ray.h"
#include "resource_manager.h"
#include <graphics.h>

MagicBearRay::MagicBearRay(bool is_facing_left, const Vector2& position)
	: is_facing_left(is_facing_left), position(position)
{
	timer_color_change.set_wait_time(0.4f);
	timer_color_change.set_one_shot(false);
	timer_color_change.set_callback([this]()
	{
		// Color change logic can be implemented here
		current_color = static_cast<Color>((static_cast<int>(current_color) + 1) % 3);
	});
	timer_life.set_wait_time(2.0f);
	timer_life.set_one_shot(true);
	timer_life.set_callback([this]()
		{
			is_enabled = false;
		});
	timer_life.restart();
	timer_color_change.restart();
	hit_box = CollisionManager::instance()->create_collision_box();
	hit_box->set_size(size);
	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Player);
	hit_box->set_enabled(true);
	hit_box->set_position(position);
}

MagicBearRay::~MagicBearRay()
{
	CollisionManager::instance()->destroy_collision_box(hit_box);
	hit_box = nullptr;
}

void MagicBearRay::on_update(float delta)
{
	if (!is_enabled) return;
	timer_life.on_update(delta);
	timer_color_change.on_update(delta);
}

void MagicBearRay::on_render()
{
	if (!is_enabled) return;

	int x = (int)position.x;
	int y = (int)position.y;
	int width = (int)size.x;
	int height = (int)size.y;

	COLORREF color;
	switch (current_color)
	{
	case LightBlue:
		color = RGB(0x9b, 0xf0, 0xfd);
		break;
	case DarkBlue:
		color = RGB(0x62, 0xab, 0xd4);
		break;
	case White:
		color = RGB(0xff, 0xff, 0xff);
		break;
	default:
		color = RGB(0x9b, 0xf0, 0xfd);
		break;
	}

	setfillcolor(color);
	fillrectangle(x, y, x + width, y + height);
}