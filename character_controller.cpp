#include "character_controller.hpp"
#include<GodotGlobal.hpp>
void CharacterController::_register_methods(){
    godot::register_method("_init", &CharacterController::_init);
    godot::register_method("_ready", &CharacterController::_ready);

    godot::register_property("Max jump height", &CharacterController::set_max_jump_height, &CharacterController::get_max_jump_height, (uint32_t)150);
    godot::register_property("Min jump height", &CharacterController::set_min_jump_height, &CharacterController::get_min_jump_height, (uint32_t)40);
    godot::register_property("Double jump height", &CharacterController::set_double_jump_height, &CharacterController::get_double_jump_height, (uint32_t)100);
    godot::register_property("Jump duration", &CharacterController::set_jump_duration, &CharacterController::get_jump_duration, (real_t)0.3);
}

void CharacterController::_init(){
    _max_jump_height = 150;
    _min_jump_height = 40;
    _double_jump_height = 100;
    _jump_duration = 0.3;
    _falling_gravity_multiplier = 1.5;
    _max_jump_amount = 1;
    _max_acceleration = 4000;
    _friction = 8;
    _can_hold_jump = false;
    _coyote_time = 0.1;
    _jump_buffer = 0.1;

    _max_speed = 100;
    _acceleration_time = 10;

    _vel = godot::Vector2::ZERO;
    _acc = godot::Vector2::ZERO;

    _coyote_timer = godot::Timer::_new();
    _jump_buffer_timer = godot::Timer::_new();
}

void CharacterController::_ready() {

}

real_t CharacterController::_calculate_gravity(real_t max_jump_height, real_t jump_duration){
    return (-2 * max_jump_height) / pow(jump_duration, 2);
}

real_t CharacterController::_calculate_jump_velocity(real_t max_jump_height, real_t jump_duration){
    return (2 * max_jump_height) / jump_duration;
}

real_t CharacterController::_calculate_jump_velocity_2(real_t max_jump_height, real_t gravity){
    return sqrt(-2 * gravity * max_jump_height);
}

real_t CharacterController::_calculate_release_gravity_multiplier(real_t jump_velocity, real_t min_jump_height, real_t gravity){
    real_t release_gravity = 0 - pow(jump_velocity, 2) / (2 * min_jump_height);
    return release_gravity / gravity;
}

real_t CharacterController::_calculate_friction(real_t time_to_max){
    return 1 - (2.30259 / time_to_max);
}

real_t CharacterController::_calculate_speed(real_t max_speed, real_t friction){
    return (max_speed / friction) - max_speed;
}

void CharacterController::set_max_jump_height(const uint32_t height){
    _max_jump_height = height;
}
void CharacterController::set_min_jump_height(const uint32_t height){
    _min_jump_height = height;
}

void CharacterController::set_double_jump_height(const uint32_t height){
    _double_jump_height = height;
}

void CharacterController::set_jump_duration(const real_t duration){
    _jump_duration = duration;
}

uint32_t CharacterController::get_max_jump_height() const{
    return _max_jump_height;
}

uint32_t CharacterController::get_min_jump_height() const{
    return _min_jump_height;
}

uint32_t CharacterController::get_double_jump_height() const{
    return _double_jump_height;
}

real_t CharacterController::get_jump_duration() const{
    return _jump_duration;
}