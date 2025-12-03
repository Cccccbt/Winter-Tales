#pragma once

// Base class for nodes that participate in a StateMachine lifecycle.
class StateNode
{
public:
        StateNode() = default;
        virtual ~StateNode() = default;

        virtual void on_enter() {};
        virtual void on_update(float delta) {};
        virtual void on_exit() {};
};
