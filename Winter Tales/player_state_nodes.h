#pragma once
#include "state_node.h"
#include "timer.h"

class PlayerAttack1 : public StateNode
{
public:
	PlayerAttack1();
	~PlayerAttack1() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
	void update_hit_box_position();
};

class PlayerAttack2 : public StateNode
{
public:
	PlayerAttack2();
	~PlayerAttack2() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
	void update_hit_box_position();
};

class PlayerAttack3 : public StateNode
{
public:
	PlayerAttack3();
	~PlayerAttack3() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
	void update_hit_box_position();
};

class PlayerRoll : public StateNode
{
public:
	PlayerRoll();
	~PlayerRoll() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class PlayerIdle : public StateNode
{
public:
	PlayerIdle();
	~PlayerIdle() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class PlayerIdle2 : public StateNode
{
public:
	PlayerIdle2();
	~PlayerIdle2() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class PlayerRun : public StateNode
{
public:
	PlayerRun();
	~PlayerRun() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class PlayerHurt : public StateNode
{
public:
	PlayerHurt();
	~PlayerHurt() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class PlayerDead : public StateNode
{
public:
	PlayerDead();
	~PlayerDead() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class PlayerJump : public StateNode
{
public:
	PlayerJump();
	~PlayerJump() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};