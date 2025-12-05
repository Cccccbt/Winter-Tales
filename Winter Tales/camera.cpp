#include "camera.h"

#include <algorithm>

Camera* Camera::instance()
{
        static Camera camera;
        return &camera;
}

void Camera::set_viewport_size(float width, float height)
{
        viewport_size = Vector2(width, height);
}

void Camera::set_world_size(float width, float height)
{
        world_size = Vector2(width, height);
}

void Camera::set_target(const Vector2* target_position)
{
        target = target_position;
}

void Camera::update()
{
        if (!target)
        {
                return;
        }

        position.x = target->x - viewport_size.x / 2.0f;
        position.y = target->y - viewport_size.y / 2.0f;

        const float max_x = std::max(0.0f, world_size.x - viewport_size.x);
        const float max_y = std::max(0.0f, world_size.y - viewport_size.y);

        position.x = std::clamp(position.x, 0.0f, max_x);
        position.y = std::clamp(position.y, 0.0f, max_y);
}

Vector2 Camera::world_to_screen(const Vector2& world_position) const
{
        return world_position - position;
}
