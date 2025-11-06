#pragma once
#include "vector2.h"
#include <functional>
#include "collision_layer.h"

class CollisionManager;

class CollisionBox
{
	friend class CollisionManager;

public:
	void set_enabled(bool flag)
	{
		enabled = flag;
	}

	void set_position(const Vector2& pos)
	{
		position = pos;
	}

	void set_size(const Vector2& size)
	{
		this->size = size;
	}

	void set_on_collide(std::function<void()> on_collide)
	{
		this->on_collide = on_collide;
	}

	void set_layer_src(CollisionLayer layer_src)
	{
		this->layer_src = layer_src;
	}

	void set_layer_dst(CollisionLayer layer_dst)
	{
		this->layer_dst = layer_dst;
	}

	const Vector2& get_position() const
	{
		return position;
	}

	const Vector2& get_size() const
	{
		return size;
	}



private:
	bool enabled = true;
	Vector2 position;
	Vector2 size;
	std::function<void()> on_collide;
	CollisionLayer layer_src = CollisionLayer::None;
	CollisionLayer layer_dst = CollisionLayer::None;

	CollisionBox() = default;
	~CollisionBox() = default;
};