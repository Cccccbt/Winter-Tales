#pragma once

#include <graphics.h>

// Base interface for game scenes. Override the lifecycle hooks to react to
// initialization, input, updates, and rendering.
class Scene
{
public:
        virtual ~Scene() = default;

        virtual void on_enter() {}
        virtual void on_exit() {}
        virtual void on_input(const ExMessage& msg) {}
        virtual void on_update(float delta) {}
        virtual void on_render() {}
};
