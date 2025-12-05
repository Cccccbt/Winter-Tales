#pragma once

#include "vector2.h"

// Simple camera that converts world coordinates into screen space and follows
// a target while clamping to the configured world bounds.
class Camera
{
public:
        static Camera* instance();

        void set_viewport_size(float width, float height);
        void set_world_size(float width, float height);
        void set_target(const Vector2* target_position);

        void update();
        Vector2 world_to_screen(const Vector2& world_position) const;

        const Vector2& get_position() const
        {
                return position;
        }

        const Vector2& get_viewport_size() const
        {
                return viewport_size;
        }

        const Vector2& get_world_size() const
        {
                return world_size;
        }

private:
        Camera() = default;

        Vector2 position;
        Vector2 viewport_size;
        Vector2 world_size;
        const Vector2* target = nullptr;
};
