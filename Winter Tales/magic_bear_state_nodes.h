#pragma once
#include "state_node.h"
#include "magic_bear.h"

// Forward declarations
class MagicBear;

class MagicBearIdle : public StateNode
{
public:
	MagicBearIdle();
	~MagicBearIdle();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer timer_idle;
};

class MagicBearWalk : public StateNode
{
public:
	MagicBearWalk();
	~MagicBearWalk();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer timer_walk;
};

class MagicBearAttack1 : public StateNode
{
public:
	MagicBearAttack1();
	~MagicBearAttack1();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer timer_attack;
	void update_collision_box();
};

class MagicBearAttack2 : public StateNode
{
public:
	MagicBearAttack2();
	~MagicBearAttack2();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer timer_attack;
};

class MagicBearAttack3 : public StateNode
{
public:
	MagicBearAttack3();
	~MagicBearAttack3();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer timer_attack;
	void update_collision_box();
};

class MagicBearAttack4 : public StateNode
{
public:
	MagicBearAttack4();
	~MagicBearAttack4();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer timer_attack;
	void update_collision_box();
};

class MagicBearSneer : public StateNode
{
public:
	MagicBearSneer();
	~MagicBearSneer();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer sneer_timer;
};

class MagicBearHurt : public StateNode
{
public:
	MagicBearHurt();
	~MagicBearHurt();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer hurt_timer;
};

class MagicBearDead : public StateNode
{
public:
	MagicBearDead();
	~MagicBearDead();

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_exit() override;
private:
	Timer dead_timer;
};