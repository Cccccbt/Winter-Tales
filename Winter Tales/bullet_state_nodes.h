#pragma once
#include "state_node.h"
#include "timer.h"

class Bullet_Moving : public StateNode
{
public:
	Bullet_Moving();
	~Bullet_Moving();

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class Bullet_Destroyed : public StateNode
{
public:
	Bullet_Destroyed();
	~Bullet_Destroyed();
    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;

private:

};