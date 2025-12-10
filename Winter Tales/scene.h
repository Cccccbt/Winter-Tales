#pragma once
#include "state_node.h"
#include <graphics.h>

class MenuScene : public StateNode
{
public:
    void on_enter() override;
    void on_exit() override;
    void on_update(float delta_time) override;
    void on_render();
    void on_input(const ExMessage& msg);
};

class GameScene : public StateNode
{
    
public:
    void on_enter() override;
    void on_exit() override;
    void on_update(float delta_time) override;
    void on_render();
    void on_input(const ExMessage& msg);
};

class TutorialScene : public StateNode
{
public:
    void on_enter() override;
    void on_exit() override;
    void on_update(float delta_time) override;
    void on_render();
	void on_input(const ExMessage& msg);
};