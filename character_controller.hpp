/*
    I converted the GDScript in the PlatformerController2D which
    can find in the Godot's AssetLib into GDNative.
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H



#include<Godot.hpp>
#include<Resource.hpp>
#include<Timer.hpp>

class CharacterController : public godot::Resource {
    GODOT_CLASS(CharacterController, godot::Resource)

    private:

    int32_t _max_jump_height;
    int32_t _min_jump_height;
    int32_t _double_jump_height;
    real_t _jump_duration;
    real_t _falling_gravity_multiplier;
    
    uint8_t _max_jump_amount;
    int32_t _max_acceleration;
    int32_t _friction;

    bool _can_hold_jump;

    real_t _coyote_time;
    real_t _jump_buffer;

    int32_t _max_speed;
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

    void set_max_jump_height(const int32_t height);
    void set_min_jump_height(const int32_t height);
    void set_double_jump_height(const int32_t height);
    void set_jump_duration(const real_t duration);
    void set_falling_gravity_multiplier(const real_t multiplier);
    void set_max_jump_amount(const uint8_t amount);
    void set_max_acceleration(const int32_t acceleration);
    void set_friction(const int32_t friction);
    void set_can_hold_jump(const bool flag);
    void set_coyote_time(const real_t time);
    void set_jump_buffer(const real_t buffer);
    void set_vel(const godot::Vector2& vel);
    void set_jump_left(const uint8_t amount);
    void set_holding_jump(const bool holding);

    int32_t get_max_jump_height() const;
    int32_t get_min_jump_height() const;
    int32_t get_double_jump_height() const;
    real_t get_jump_duration() const;
    real_t get_falling_gravity_multiplier() const;
    uint8_t get_max_jump_amount() const;
    int32_t get_max_acceleration() const;
    int32_t get_friction() const;
    real_t get_coyote_time() const;
    real_t get_jump_buffer() const;
    real_t get_default_gravity() const;
    bool get_can_hold_jump() const;
    godot::Vector2& get_vel_ref();
    godot::Vector2& get_acc_ref();
    godot::Timer& get_coyote_timer();
    godot::Timer& get_jump_buffer_timer();
    bool get_holding_jump() const;
    uint8_t get_jump_left() const;
    real_t get_release_gravity_multiplier() const;

    void _jump();
    protected:

    real_t _calculate_gravity(int32_t max_jump_height, real_t jump_duration);
    real_t _calculate_jump_velocity(int32_t max_jump_height, real_t jump_duration);
    real_t _calculate_jump_velocity_2(int32_t max_jump_height, real_t gravity);
    real_t _calculate_release_gravity_multiplier(real_t jump_velocity, int32_t min_jump_height, real_t gravity);
    real_t _calculate_friction(real_t time_to_max);
    real_t _calculate_speed(real_t max_speed, real_t friction);

};

#endif
