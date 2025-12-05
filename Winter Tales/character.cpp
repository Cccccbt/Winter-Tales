#include "character.h"
#include "collision_manager.h"
#include "camera.h"

Character::Character()
	: position(0.0f, 0.0f),  // Initialize position
	  velocity(0.0f, 0.0f),  // Initialize velocity
	  logic_height(64.0f),   // Initialize logic_height
	  is_facing_left(false),
	  hp(100),
	  enable_gravity(false),
	  is_invulnerable(false),
	  is_blink_invisiable(false),
	  current_animation(nullptr)
{
	hit_box = CollisionManager::instance()->create_collision_box();
	hurt_box = CollisionManager::instance()->create_collision_box();
	
	is_invulnerable_status.set_wait_time(1.0f);
	is_invulnerable_status.set_one_shot(true);
	// FIXED: Use [this] instead of [&]
        is_invulnerable_status.set_callback
        (
                [this]()
                {
                        is_invulnerable = false;
                        is_blink_invisiable = false;
                        is_invulnerable_blink.pause();
                }
        );

	is_invulnerable_blink.set_wait_time(0.075f);
	is_invulnerable_blink.set_one_shot(false);
	// FIXED: Use [this] instead of [&]
	is_invulnerable_blink.set_callback
	(
		[this]()
		{
			is_blink_invisiable = !is_blink_invisiable;
		}
	);
}

Character::~Character()
{
	CollisionManager::instance()->destroy_collision_box(hit_box);
	CollisionManager::instance()->destroy_collision_box(hurt_box);
}

void Character::decrease_hp(int h)
{
	if (is_invulnerable) return;

	hp -= h;
	if (hp > 0)
	{
		make_invulnerable();
	}

}

void Character::on_input(const ExMessage& msg)
{

}

void Character::on_update(float delta)
{
	state_machine.on_update(delta);

	if (hp < 0)
	{
		velocity.x = 0;
	}

	if (enable_gravity)
	{
		velocity.y += GRAVITY * delta;
	}

	position.x += velocity.x * delta;
	position.y += velocity.y * delta;

        if (is_invulnerable)
        {
                is_invulnerable_blink.on_update(delta);
        }

        // Screen boundaries (X axis)
        const float world_width = Camera::instance()->get_world_size().x;
        const float boundary_width = world_width > 0 ? world_width : static_cast<float>(getwidth());
        if (position.x <= 0)
        {
                position.x = 0;
        }

        if (position.x >= boundary_width)
        {
                position.x = boundary_width;
        }

	// Ceiling
	if (position.y <= 0)
	{
		position.y = 0;
	}

	// FLOOR COLLISION
	if (position.y >= FLOOR_Y)
	{
		position.y = FLOOR_Y;
		velocity.y = 0;
	}

	hurt_box->set_position(get_logical_center());
	is_invulnerable_status.on_update(delta);

	if (!current_animation)
	{
		return;
	}
	Animation& animation = (is_facing_left ? current_animation->left : current_animation->right);
	animation.on_update(delta);
	animation.set_position(position);
}

void Character::on_render()
{
	if (!current_animation || (is_invulnerable && is_blink_invisiable))
	{
		return;
	}

	(is_facing_left ? current_animation->left : current_animation->right).on_render();
}

void Character::on_hurt()
{

}

void Character::switch_state(const std::string& id)
{
	state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id)
{
	current_animation = &animation_pool[id];

	current_animation->left.reset();
	current_animation->right.reset();
}