#include "camera.h"
#include "util.h"

Camera* Camera::camera = nullptr;


Camera* Camera::instance()
{
	if (!camera)
	{
		camera = new Camera();
	}

	return camera;
}

Camera::Camera()
	: position(0.0f, 0.0f), original_position(Vector2(0.0f, 0.0f))
{
	// Set callback to stop shaking when timer expires
	timer_shake.set_callback([this]()
	{
		is_shaking = false;
		reset_position();
	});
}

void Camera::on_update(float delta_time)
{
	if (is_shaking)
	{
		position.x += range_random(-shake_strength, shake_strength);
		//position.y += range_random(-shake_strength, shake_strength);
	}

	timer_shake.on_update(delta_time);
}

