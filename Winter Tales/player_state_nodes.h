#pragma once
#include "state_node.h"
#include "timer.h"
#include "character_manager.h"

class PlayerIdleState : public StateNode
{
public:
	PlayerIdleState() = default;
	~PlayerIdleState() = default;

	void on_enter() {};
	void on_update(float delta) {};
	void on_exit() {};
};

class PlayerAttack_AState : public StateNode
{
public:
	PlayerAttack_AState() = default;
	~PlayerAttack_AState() = default;

	void on_enter() {};
	void on_update(float delta) {};
	void on_exit() {};

private:
	Timer timer;
};

class PlayerAttack_BState : public StateNode
{
public:
	PlayerAttack_BState() = default;
	~PlayerAttack_BState() = default;

	void on_enter() {};
	void on_update(float delta) {};
	void on_exit() {};

private:
	Timer timer;
};

class PlayerRollState : public StateNode
{
public:
	PlayerRollState() = default;
	~PlayerRollState() = default;

	void on_enter() {};
	void on_update(float delta) {};
	void on_exit() {};

private:
	Timer timer;
};