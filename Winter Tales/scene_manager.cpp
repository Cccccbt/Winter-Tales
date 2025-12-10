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

void SceneManager::register_scene(const std::string& id, StateNode* scene)
{
	state_machine.register_state(id, scene);
}

void SceneManager::on_update(float delta_time)
{
	state_machine.on_update(delta_time);
}

void SceneManager::on_render()
{
	
}

void SceneManager::on_input(const ExMessage& msg)
{
}

void SceneManager::switch_to(const std::string& id)
{
	state_machine.switch_to(id);
}