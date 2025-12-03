#pragma once

#include "magic_bear.h"
#include "state_node.h"

// States that drive the MagicBear boss behaviour and attacks.
class MagicBearIdle : public StateNode
{
public:
        MagicBearIdle();
        ~MagicBearIdle();

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

private:
        Timer timer_idle;
};

class MagicBearWalk : public StateNode
{
public:
        MagicBearWalk();
        ~MagicBearWalk();

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

private:
        Timer timer_walk;
};

class MagicBearAttack1 : public StateNode
{
public:
        MagicBearAttack1();
        ~MagicBearAttack1();

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

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

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

private:
        Timer timer_attack;
        bool enter_facing_left;
};

class MagicBearAttack3 : public StateNode
{
public:
        MagicBearAttack3();
        ~MagicBearAttack3();

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

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

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

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

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

private:
        Timer sneer_timer;
        bool enter_facing_left;
};

class MagicBearHurt : public StateNode
{
public:
        MagicBearHurt();
        ~MagicBearHurt();

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

private:
        Timer hurt_timer;
        bool enter_facing_left;
};

class MagicBearDead : public StateNode
{
public:
        MagicBearDead();
        ~MagicBearDead();

        void on_enter() override;
        void on_update(float delta) override;
        void on_exit() override;

private:
        Timer dead_timer;
        bool enter_facing_left;
};
