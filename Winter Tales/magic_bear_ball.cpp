#include "magic_bear_ball.h"
#include "resource_manager.h"
#include "character_manager.h"
#include "camera.h"
#include <cstdlib>
#include <iostream>

MagicBearBall::MagicBearBall(bool is_facing_left, const Vector2& position)
	: is_facing_left(is_facing_left), position(position), base_position(position), stage(Aiming)
{

	ball_image = ResourceManager::instance()->find_image("magic_bear_ball");
	hit_box = CollisionManager::instance()->create_collision_box();
	hit_box->set_size(Vector2(18, 12));
	hit_box->set_layer_src(CollisionLayer::Enemy);
	hit_box->set_layer_dst(CollisionLayer::Player);
	hit_box->set_enabled(true);
	hit_box->set_position(position);
	hit_box->set_on_collide([this]() 
		{
			on_destroy();
		});
	timer_aim.set_wait_time(3.0f);
	timer_aim.set_one_shot(true);
	timer_aim.set_callback([this]() 
		{
			if (stage == Aiming) 
			{
				stage = Dashing;
				const Vector2& pos_player = CharacterManager::instance()->get_player()->get_position() + Vector2(0, -32);
				Vector2 direction = pos_player - this->position;
				float length = direction.length();
				if (length != 0)
				{
					direction = direction * (1.0f / length);
				}
				velocity = direction * SPEED;
			}
		});
	timer_aim.restart();
}

MagicBearBall::~MagicBearBall()
{

	if (hit_box)
	{
		CollisionManager::instance()->destroy_collision_box(hit_box);
		hit_box = nullptr;
	}
}

void MagicBearBall::on_update(float delta)
{
	if (!is_enabled) return;

	timer_aim.on_update(delta);

	// Update position
	if (stage == Dashing)
	{
		position = base_position + velocity * delta;
		base_position = position;
	}
	else if (stage == Aiming)
	{
		// Add shaking effect during aiming phase
		float shake_x = static_cast<float>((rand() % static_cast<int>(SHAKE_INTENSITY * 2 + 1)) - SHAKE_INTENSITY);
		float shake_y = static_cast<float>((rand() % static_cast<int>(SHAKE_INTENSITY * 2 + 1)) - SHAKE_INTENSITY);
		position = base_position + Vector2(shake_x, shake_y);
	}

	// Update collision box position
	if (hit_box) 
	{
		hit_box->set_position(position);
	}
	
	// Bounds checking
	if (position.x < -100 || position.x > 1400 || position.y < -100 || position.y > 900) 
	{
		on_destroy();
	}
}
void MagicBearBall::on_render()
{
	if (!is_enabled) return;
        if (ball_image)
        {
                Vector2 screen_pos = Camera::instance()->world_to_screen(position);
                int draw_x = (int)(screen_pos.x - ball_image->getwidth() / 2);
                int draw_y = (int)(screen_pos.y - ball_image->getheight() / 2);
                putimage_alpha(draw_x, draw_y, ball_image);
        }
}

void MagicBearBall::on_destroy()
{
	is_enabled = false;
	stage = Breaking;
	hit_box->set_enabled(false);
}