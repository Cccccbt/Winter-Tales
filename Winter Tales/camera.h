#pragma once
#include "vector2.h"
#include "util.h"
#include "timer.h"

class Camera
{
public:
	static Camera* instance();

	const Vector2& get_position() const
	{
		return position;
	};
	void set_position(const Vector2& pos)
	{
		position = pos;
	};
	void shake(float magnitude, float duration)
	{
		is_shaking = true;
		shake_strength = magnitude;
		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	};
	void on_update(float delta_time);

private:
	static Camera* camera;
	Vector2 position;
	Timer timer_shake;
	float shake_strength = 0.0f;
	bool is_shaking = false;

	Camera();
	~Camera() = default;
};