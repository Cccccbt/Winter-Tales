#include "scene_manager.h"

SceneManager* SceneManager::scene_manager = nullptr;

SceneManager* SceneManager::instance()
{
        if (!scene_manager)
        {
                scene_manager = new SceneManager();
        }

        return scene_manager;
}

void SceneManager::register_scene(const std::string& id, std::unique_ptr<Scene> scene)
{
        scene_pool[id] = std::move(scene);
}

void SceneManager::switch_to(const std::string& id)
{
        auto it = scene_pool.find(id);
        if (it == scene_pool.end())
        {
                return;
        }

        if (current_scene)
        {
                current_scene->on_exit();
        }

        current_scene = it->second.get();
        current_scene->on_enter();
}

void SceneManager::on_input(const ExMessage& msg)
{
        if (current_scene)
        {
                current_scene->on_input(msg);
        }
}

void SceneManager::on_update(float delta)
{
        if (current_scene)
        {
                current_scene->on_update(delta);
        }
}

void SceneManager::on_render()
{
        if (current_scene)
        {
                current_scene->on_render();
        }
}
