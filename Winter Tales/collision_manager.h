#pragma once
#include "collision_box.h"
#include <vector>
class CollisionManager
{
public:
	static CollisionManager* instance();

	CollisionBox* create_collision_box();
	void destroy_collision_box(CollisionBox*);
	void process_collide();
	void on_debug_render();

private:
	static CollisionManager* collision_manager;
	std::vector<CollisionBox*> collision_box_list;

	CollisionManager();
	~CollisionManager();
};