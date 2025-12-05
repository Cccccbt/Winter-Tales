#pragma once
#include "vector2.h"
#include "util.h"
#include "timer.h"

class Camera
{
public:
	Camera()
	{
		timer_shake.set_wait_time(0.5f);
		timer_shake.set_one_shot(true);
		timer_shake.set_callback([this]()
		{
			is_shaking = false;
		});
	};
	~Camera();
	void set_position(const Vector2& pos)
	{
		position = pos;
	};
	const Vector2& get_position() const
	{
		return position;
	};
	void shake(float intensity, float duration = 0.5f)
	{
		is_shaking = true;
		shake_intensity = intensity;
		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	};
	void on_update(float delta)
	{
		if (is_shaking)
		{
			position.x += range_random(-shake_intensity, shake_intensity);
			position.y += range_random(-shake_intensity, shake_intensity);
		}
		timer_shake.on_update(delta);
	};

private:
	Vector2 position;
	Timer timer_shake;
	float shake_intensity = 5.0f;
	bool is_shaking = false;
};