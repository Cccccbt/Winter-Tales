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
	const float WALK_SPEED = 150.0f;
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
	Timer attack_timer;
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
	Timer attack_timer;
	float charge_progress = 0.0f;
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
	Timer attack_timer;
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
	Timer attack_timer;
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