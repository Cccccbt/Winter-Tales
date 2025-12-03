#include "bullet.h"
#include "collision_manager.h"
#include "resource_manager.h"

Bullet::Bullet(bool is_facing_left, const Vector2& position)
{
	this->is_facing_left = is_facing_left;
	this->position = position;

	// Create collision box
	hit_box = CollisionManager::instance()->create_collision_box();
	if (hit_box) {
		hit_box->set_size(Vector2(16, 8));
		hit_box->set_layer_src(CollisionLayer::None);
		hit_box->set_layer_dst(CollisionLayer::Enemy);
		hit_box->set_enabled(true);
		hit_box->set_position(position);

		// CRITICAL FIX: Use [this] instead of [&] to avoid dangling reference
		hit_box->set_on_collide([this]() {
			on_destroy();
		});
	}

	// Setup animations
	AnimationGroup& animation = animation_pool["moving"];

	Animation& bullet_animation_right = animation.right;
	bullet_animation_right.set_interval(0.1f);
	bullet_animation_right.set_is_loop(true);
	IMAGE* right_img = ResourceManager::instance()->find_image("player_bullet_moving_right");
	if (right_img) {
		bullet_animation_right.add_frame(right_img, 3);
	}
	bullet_animation_right.set_AnchorMode(Animation::AnchorMode::Centered);

	Animation& bullet_animation_left = animation.left;
	bullet_animation_left.set_interval(0.1f);
	bullet_animation_left.set_is_loop(true);
	IMAGE* left_img = ResourceManager::instance()->find_image("player_bullet_moving_left");
	if (left_img) {
		bullet_animation_left.add_frame(left_img, 3);
	}
	bullet_animation_left.set_AnchorMode(Animation::AnchorMode::Centered);

	AnimationGroup& animation_destroyed = animation_pool["destroyed"];
	
	Animation& bullet_destroyed_right = animation_destroyed.right;
	bullet_destroyed_right.set_interval(0.1f);
	bullet_destroyed_right.set_is_loop(false);
	bullet_destroyed_right.set_AnchorMode(Animation::AnchorMode::Centered);
	IMAGE* destroyed_right_img = ResourceManager::instance()->find_image("player_bullet_destroyed_right");
	if (destroyed_right_img) {
		bullet_destroyed_right.add_frame(destroyed_right_img, 3);
	}
	// CRITICAL FIX: Use [this] instead of [&]
	bullet_destroyed_right.set_on_finished([this]() {
		is_enabled = false;
	});

	Animation& bullet_destroyed_left = animation_destroyed.left;
	bullet_destroyed_left.set_interval(0.1f);
	bullet_destroyed_left.set_is_loop(false);
	bullet_destroyed_left.set_AnchorMode(Animation::AnchorMode::Centered);
	IMAGE* destroyed_left_img = ResourceManager::instance()->find_image("player_bullet_destroyed_left");
	if (destroyed_left_img) {
		bullet_destroyed_left.add_frame(destroyed_left_img, 3);
	}
	// CRITICAL FIX: Use [this] instead of [&]
	bullet_destroyed_left.set_on_finished([this]() {
		is_enabled = false;
	});

	// Set current animation
	current_animation = &animation_pool["moving"];
}

Bullet::~Bullet()
{
	if (hit_box) {
		CollisionManager::instance()->destroy_collision_box(hit_box);
		hit_box = nullptr;
	}
}

void Bullet::on_update(float delta)
{
	if (!is_enabled) return;

	// Update position based on direction
	Vector2 velocity = SPEED;
	if (is_facing_left) {
		velocity.x = -velocity.x;
	}
	position += velocity * delta;
	
	// Update collision box position
	if (hit_box) {
		hit_box->set_position(position);
	}

	// Update current animation
	if (current_animation) {
		Animation& current_anim = is_facing_left ? current_animation->left : current_animation->right;
		current_anim.set_position(position);
		current_anim.on_update(delta);
	}

	// Bounds checking
	if (position.x < -100 || position.x > 1400 || position.y < -100 || position.y > 900) {
		on_destroy();
	}
}

void Bullet::on_render()
{
	if (!is_enabled) return;

	if (current_animation) {
		Animation& current_anim = is_facing_left ? current_animation->left : current_animation->right;
		current_anim.on_render();
	}
}

void Bullet::on_destroy()
{
	if (!is_enabled) return;
	current_animation = &animation_pool["destroyed"];
	
	// Reset and start destroyed animation
	if (current_animation) {
		Animation& current_anim = is_facing_left ? current_animation->left : current_animation->right;
		current_anim.reset();
	}
	
	// Disable collision
	if (hit_box) {
		hit_box->set_enabled(false);
	}
}