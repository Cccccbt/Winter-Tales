#pragma once

#include "camera.h"
#include "character_manager.h"
#include "collision_manager.h"
#include "resource_manager.h"
#include "scene.h"

// Primary gameplay scene responsible for driving simulation and rendering.
class GameScene : public Scene
{
public:
        void on_input(const ExMessage& msg) override;
        void on_update(float delta) override;
        void on_render() override;
};
