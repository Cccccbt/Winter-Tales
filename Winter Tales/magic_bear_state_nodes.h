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
	bool enter_facing_left;
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
	bool enter_facing_left;
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
	Timer timer_ray;
	void update_collision_box();
	bool enter_facing_left;
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
        Timer timer_ball;
        void update_collision_box();
        bool enter_facing_left;
        int ball_cast_count = 0;
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
	bool enter_facing_left;
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
	bool enter_facing_left;
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
	bool enter_facing_left;
};