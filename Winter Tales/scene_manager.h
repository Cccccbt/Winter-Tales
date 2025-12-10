#pragma once
#include <graphics.h>
#include "state_machine.h"
#include "state_node.h"

class SceneManager
{
public:
	static SceneManager* instance();

	void register_scene(const std::string& id, StateNode* scene);
	void on_update(float delta_time);
	void on_render();
	void on_input(const ExMessage& msg);
	void switch_to(const std::string& id);

private:
	static SceneManager* scene_manager;
	StateMachine state_machine;

	SceneManager() = default;
	~SceneManager() = default;
};