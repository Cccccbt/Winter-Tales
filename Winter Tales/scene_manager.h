#pragma once

#include <graphics.h>
#include <memory>
#include <string>
#include <unordered_map>
#include "scene.h"

// Manages the active scene and coordinates transitions between registered scenes.
class SceneManager
{
public:
        static SceneManager* instance();

        void register_scene(const std::string& id, std::unique_ptr<Scene> scene);
        void switch_to(const std::string& id);

        void on_input(const ExMessage& msg);
        void on_update(float delta);
        void on_render();

private:
        static SceneManager* scene_manager;

        SceneManager() = default;
        ~SceneManager() = default;

        Scene* current_scene = nullptr;
        std::unordered_map<std::string, std::unique_ptr<Scene>> scene_pool;
};
