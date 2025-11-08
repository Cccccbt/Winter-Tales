#pragma once
#include <string>
#include "state_node.h"
#include <unordered_map>

class StateMachine
{
public:
	void on_update(float delta);

	void set_entry(const std::string& id);
	void switch_to(const std::string& id);
	void register_state(const std::string& id, StateNode* state_node);
private:
	StateNode* current_state_node = nullptr;
	bool need_init = true;
	std::unordered_map<std::string, StateNode*> state_node_pool;
};