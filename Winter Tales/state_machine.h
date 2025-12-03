#pragma once

#include <string>
#include <unordered_map>
#include "state_node.h"

// Generic state machine that dispatches lifecycle callbacks to registered nodes.
class StateMachine
{
public:
        // Update the active state each frame.
        void on_update(float delta);

        // Identify the first state to enter when the machine updates.
        void set_entry(const std::string& id);

        // Transition to another registered state immediately.
        void switch_to(const std::string& id);

        // Register a state node that can be switched to by ID.
        void register_state(const std::string& id, StateNode* state_node);

private:
        StateNode* current_state_node = nullptr;
        bool need_init = true;
        std::unordered_map<std::string, StateNode*> state_node_pool;
};
