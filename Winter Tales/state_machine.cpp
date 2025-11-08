#include "state_machine.h"

void StateMachine::on_update(float delta)
{
	if (!current_state_node)
		return;

	if (need_init)
	{
		current_state_node->on_enter();
		need_init = false;
	}

	current_state_node->on_update(delta);
}

void StateMachine::set_entry(const std::string& id)
{
	current_state_node = state_node_pool[id];
}

void StateMachine::switch_to(const std::string& id)
{
	if (current_state_node)
	{
		current_state_node->on_exit();
	}

	current_state_node = state_node_pool[id];

	if (current_state_node)
	{
		current_state_node->on_enter();
	}
}

void StateMachine::register_state(const std::string& id, StateNode* state_node)
{
	state_node_pool[id] = state_node;
}