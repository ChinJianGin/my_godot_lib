#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<Godot.hpp>
#include<Resource.hpp>
#include<Timer.hpp>

class CharacterController : public godot::Resource {
    GODOT_CLASS(CharacterController, godot::Resource)

    private:

    uint32_t _max_jump_height;
    uint32_t _min_jump_height;
    uint32_t _double_jump_height;
    real_t _jump_duration;
    real_t _falling_gravity_multiplier;

    uint8_t _max_jump_amount;
    int32_t _max_acceleration;
    int32_t _friction;

    bool _can_hold_jump;

    real_t _coyote_time;
    real_t _jump_buffer;

    uint32_t _max_speed;
    real_t _acceleration_time;

    real_t _default_gravity;
    real_t _jump_velocity;
    real_t _double_jump_velocity;
    real_t _release_gravity_multiplier;

    uint8_t _jumps_left;
    bool _holding_jump;

    godot::Vector2 _vel;
    godot::Vector2 _acc;

    godot::Timer* _coyote_timer;
    godot::Timer* _jump_buffer_timer;
    public:

    void _init();
    void _ready();

    static void _register_methods();

    void set_max_jump_height(const uint32_t height);
    void set_min_jump_height(const uint32_t height);
    void set_double_jump_height(const uint32_t height);
    void set_jump_duration(const real_t duration);

    uint32_t get_max_jump_height() const;
    uint32_t get_min_jump_height() const;
    uint32_t get_double_jump_height() const;
    real_t get_jump_duration() const;

    protected:

    real_t _calculate_gravity(real_t max_jump_height, real_t jump_duration);
    real_t _calculate_jump_velocity(real_t max_jump_height, real_t jump_duration);
    real_t _calculate_jump_velocity_2(real_t max_jump_height, real_t gravity);
    real_t _calculate_release_gravity_multiplier(real_t jump_velocity, real_t min_jump_height, real_t gravity);
    real_t _calculate_friction(real_t time_to_max);
    real_t _calculate_speed(real_t max_speed, real_t friction);
};

#endif