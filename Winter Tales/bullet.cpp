#include "bullet.h"
#include "collision_manager.h"
#include "resource_manager.h"
Bullet::Bullet(bool is_facing_left)
{
	hit_box = CollisionManager::instance()->create_collision_box();
	hit_box->set_size(Vector2(16, 8));
	hit_box->set_layer_src(CollisionLayer::Player);
	hit_box->set_layer_dst(CollisionLayer::Enemy);
	hit_box->set_enabled(true);
	this->is_facing_left = is_facing_left;

	AnimationGroup& animation = animation_pool["moving"];

	Animation& bullet_animation_right = animation.right;
	bullet_animation_right.set_interval(0.1f);
	bullet_animation_right.set_is_loop(false);
	bullet_animation_right.add_frame(ResourceManager::instance()->find_image("player_bullet_right"), 3);
	bullet_animation_right.set_AnchorMode(Animation::AnchorMode::Centered);

	Animation& bullet_animation_left = animation.left;
	bullet_animation_left.set_interval(0.1f);
	bullet_animation_left.set_is_loop(false);
	bullet_animation_left.add_frame(ResourceManager::instance()->find_image("player_bullet_left"), 3);
	bullet_animation_left.set_AnchorMode(Animation::AnchorMode::Centered);

	AnimationGroup& animation_destroyed = animation_pool["destroyed"];
	Animation& bullet_destroyed_right = animation_destroyed.right;
	bullet_destroyed_right.set_interval(0.1f);
	bullet_destroyed_right.set_is_loop(false);
	bullet_destroyed_right.set_AnchorMode(Animation::AnchorMode::Centered);
	bullet_destroyed_right.add_frame(ResourceManager::instance()->find_image("player_bullet_destroyed_right"), 3);

	Animation& bullet_destroyed_left = animation_destroyed.left;
	bullet_destroyed_left.set_interval(0.1f);
	bullet_destroyed_left.set_is_loop(false);
	bullet_destroyed_left.set_AnchorMode(Animation::AnchorMode::Centered);
	bullet_destroyed_left.add_frame(ResourceManager::instance()->find_image("player_bullet_destroyed_left"), 3);
}

Bullet::~Bullet()
{
	CollisionManager::instance()->destroy_collision_box(hit_box);
}

void Bullet::on_update(float delta)
{
	
	position += SPEED * delta;
	hit_box->set_position(position);

}