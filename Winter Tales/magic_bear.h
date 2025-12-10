#pragma once

#include "character_manager.h"
#include "magic_bear_ball.h"
#include "magic_bear_ray.h"
#include "magic_bear_state_nodes.h"
#include "resource_manager.h"

// Boss enemy that coordinates several attack types and cooldowns.
class MagicBear : public Character
{
public:
        MagicBear();
        ~MagicBear();

        bool is_attacking() const
        {
                return is_balling || is_raying || is_biting;
        };

        bool can_attack() const
        {
                return can_attack_ball() || can_attack_ray() || can_attack_bite();
        };

        bool can_attack_ball() const
        {
                return !is_global_attack_on_cd && !is_ball_on_cd;
        };

        bool can_attack_ray() const
        {
                return !attack3_used && phase == 3 && !is_global_attack_on_cd && !is_ray_on_cd;
        };

        Vector2 get_logical_center() const
        {
                return Vector2(position.x, position.y - logic_height / 2);
        }

        bool can_attack_bite() const
        {
                return !is_global_attack_on_cd && !is_bite_on_cd;
        };

        bool can_attack_run() const
        {
                return !is_global_attack_on_cd && !is_run_on_cd;
        };

        bool is_global_attack_cooling() const
        {
                return is_global_attack_on_cd;
        }

        float get_walk_speed() const
        {
                return WALK_SPEED;
        };

        float get_run_speed() const
        {
                return RUN_SPEED;
        };

        float get_max_hp() const
        {
                return hp_max;
        }

        CollisionBox* get_body_hit_box() const
        {
                return body_hit_box;
        };

        bool is_player_in_close_range() const;
        bool is_player_in_mid_range() const;
        bool is_player_in_far_range() const;

        void on_hurt() override;
        void on_input(const ExMessage& msg) override;
        void on_update(float delta) override;
        void on_render() override;

        bool on_ball();
        void on_ray(bool);
        void on_bite();
        void on_run();

        void enter_hurt_invulnerability();
        void clear_hurt_invulnerability();
        void start_post_hurt_invulnerability();

        float get_phase_walk_speed() const;
        float get_phase_run_speed() const;
        int get_phase_index() const
        {
                return phase;
        }

        bool consume_pending_sneer();

        void mark_attack3_used();
        bool has_used_attack3() const
        {
                return attack3_used;
        }

        void start_global_attack_cooldown();
        void start_attack1_cooldown();
        void start_attack2_cooldown();
        void start_attack3_cooldown();
        void start_attack4_cooldown();
        void update_attack_cooldowns(float delta);
        void start_post_attack_idle();
        void update_post_attack_idle(float delta);
        bool is_forced_idle() const
        {
                return is_forced_idle_locked;
        }

private:
        const float GLOBAL_ATTACK_CD = 3.0f;
        const float BALL_ATTACK_CD = 5.0f;
        const float RAY_ATTACK_CD = 5.0f;
        const float BITE_ATTACK_CD = 2.0f;
        const float RUN_ATTACK_CD = 2.0f;
        const float WALK_SPEED = 150.0f;
        const float RUN_SPEED = 250.0f;
        const float CLOSE_RANGE = 50.0f;
        const float FAR_RANGE = 400.0f;
        const float MID_RANGE = 100.0f;
        const float POST_HURT_INVULNERABILITY_TIME = 1.0f;

        float hp_max = 10.0f;
        int phase = 1;
        bool pending_phase_sneer = false;
        bool attack3_used = false;

        bool is_global_attack_on_cd = false;
        bool is_ball_on_cd = false;
        bool is_ray_on_cd = false;
        bool is_bite_on_cd = false;
        bool is_run_on_cd = false;

        Timer global_cd_timer;
        Timer ball_cd_timer;
        Timer ray_cd_timer;
        Timer bite_cd_timer;
        Timer run_cd_timer;
        Timer post_attack_idle_timer;
        bool is_forced_idle_locked = false;

        void setup_cooldown_timers();
        float get_phase_based_global_cd() const;
        float get_attack1_cd() const;
        float get_attack2_cd() const;
        float get_attack3_cd() const;
        float get_attack4_cd() const;
        void update_phase();

        bool is_balling = false;
        bool is_raying = false;
        bool is_biting = false;

        CollisionBox* body_hit_box = nullptr;

        std::vector<MagicBearBall*> bear_ball_list;
        std::vector<MagicBearRay*> bear_ray_list;
};
