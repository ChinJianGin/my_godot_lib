#include "character_controller.hpp"
#include<GodotGlobal.hpp>
#include<Node.hpp>
void CharacterController::_register_methods(){
    godot::register_method("_init", &CharacterController::_init);
    //godot::register_method("_ready", &CharacterController::_ready);

    godot::register_property("Max jump height", &CharacterController::set_max_jump_height, &CharacterController::get_max_jump_height, (int32_t)150);
    godot::register_property("Min jump height", &CharacterController::set_min_jump_height, &CharacterController::get_min_jump_height, (int32_t)40);
    godot::register_property("Double jump height", &CharacterController::set_double_jump_height, &CharacterController::get_double_jump_height, (int32_t)100);
    godot::register_property("Jump duration", &CharacterController::set_jump_duration, &CharacterController::get_jump_duration, (real_t)0.3);
    godot::register_property("Falling gravity multiplier", &CharacterController::set_falling_gravity_multiplier, &CharacterController::get_falling_gravity_multiplier, (real_t)1.5);
    godot::register_property("Max jump amount", &CharacterController::set_max_jump_amount, &CharacterController::get_max_jump_amount, (uint8_t)1);
    godot::register_property("Max acceleration", &CharacterController::set_max_acceleration, &CharacterController::get_max_acceleration, (int32_t)4000);
    godot::register_property("Friction", &CharacterController::set_friction, &CharacterController::get_friction, (int32_t)8);
    godot::register_property("Coyote time", &CharacterController::set_coyote_time, &CharacterController::get_coyote_time, (real_t)0.1);
    godot::register_property("Jump buffer", &CharacterController::set_jump_buffer, &CharacterController::get_jump_buffer, (real_t)0.1);
    godot::register_property("Can hold jump", &CharacterController::set_can_hold_jump, &CharacterController::get_can_hold_jump, false);
}

void CharacterController::_init(){
    _max_jump_height = 150;
    _min_jump_height = 40;
    _double_jump_height = 100;
    _jump_duration = (real_t)0.3;
    _falling_gravity_multiplier = 1.5;
    _max_jump_amount = 1;
    _max_acceleration = 4000;
    _friction = 8;
    _can_hold_jump = false;
    _coyote_time = (real_t)0.1;
    _jump_buffer = (real_t)0.1;

    _max_speed = 100;
    _acceleration_time = 10;

    _vel = godot::Vector2::ZERO;
    _acc = godot::Vector2::ZERO;

    _coyote_timer = godot::Timer::_new();
    _jump_buffer_timer = godot::Timer::_new();

    _default_gravity = _calculate_gravity(_max_jump_height, _jump_duration);
    godot::Godot::print(godot::String::num_real(_default_gravity));
    _jump_velocity = _calculate_jump_velocity(_max_jump_height, _jump_duration);
    _double_jump_velocity = _calculate_jump_velocity_2(_double_jump_height, _default_gravity);
    _release_gravity_multiplier = _calculate_release_gravity_multiplier(_jump_velocity, _min_jump_height, _default_gravity);
}

void CharacterController::_ready() {
    godot::Godot::print("Resource ready");
    _coyote_timer->set_wait_time(_coyote_time);
    _coyote_timer->set_one_shot(true);

    _jump_buffer_timer->set_wait_time(_jump_buffer);
    _jump_buffer_timer->set_one_shot(true);
}

real_t CharacterController::_calculate_gravity(int32_t max_jump_height, real_t jump_duration){
    return (real_t)(-2 * max_jump_height) / pow(jump_duration, 2);
}

real_t CharacterController::_calculate_jump_velocity(int32_t max_jump_height, real_t jump_duration){
    return (2 * max_jump_height) / jump_duration;
}

real_t CharacterController::_calculate_jump_velocity_2(int32_t max_jump_height, real_t gravity){
    return sqrt(-2 * gravity * max_jump_height);
}

real_t CharacterController::_calculate_release_gravity_multiplier(real_t jump_velocity, int32_t min_jump_height, real_t gravity){
    real_t release_gravity = (real_t)(0 - pow(jump_velocity, 2) / (2 * min_jump_height));
    return release_gravity / gravity;
}

real_t CharacterController::_calculate_friction(real_t time_to_max){
    return (real_t)(1 - (2.30259 / time_to_max));
}

real_t CharacterController::_calculate_speed(real_t max_speed, real_t friction){
    return (max_speed / friction) - max_speed;
}

void CharacterController::_jump(){
    if(_jumps_left == _max_jump_amount && _coyote_timer->is_stopped()){
        _jumps_left -= 1;
    }
    if(_jumps_left > 0){
        if(_jumps_left < _max_jump_amount){
            _vel.y = -_double_jump_velocity;
        }else{
            _vel.y = -_jump_velocity;
        }
        _jumps_left -= 1;
    }
    _coyote_timer->stop();
}

void CharacterController::set_max_jump_height(const int32_t height){
    _max_jump_height = height;

    _default_gravity = _calculate_gravity(_max_jump_height, _jump_duration);
    _jump_velocity = _calculate_jump_velocity(_max_jump_height, _jump_duration);
    _double_jump_velocity = _calculate_jump_velocity_2(_double_jump_height, _default_gravity);
    _release_gravity_multiplier = _calculate_release_gravity_multiplier(_jump_velocity, _min_jump_height, _default_gravity);
}
void CharacterController::set_min_jump_height(const int32_t height){
    _min_jump_height = height;

    _release_gravity_multiplier = _calculate_release_gravity_multiplier(_jump_velocity, _min_jump_height, _default_gravity);
}

void CharacterController::set_double_jump_height(const int32_t height){
    _double_jump_height = height;

    _double_jump_velocity = _calculate_jump_velocity_2(_double_jump_height, _default_gravity);
}

void CharacterController::set_jump_duration(const real_t duration){
    _jump_duration = duration;

    _default_gravity = _calculate_gravity(_max_jump_height, _jump_duration);
    _jump_velocity = _calculate_jump_velocity(_max_jump_height, _jump_duration);
    _double_jump_velocity = _calculate_jump_velocity_2(_double_jump_height, _default_gravity);
    _release_gravity_multiplier = _calculate_release_gravity_multiplier(_jump_velocity, _min_jump_height, _default_gravity);
}

void CharacterController::set_falling_gravity_multiplier(const real_t multiplier){
    _falling_gravity_multiplier = multiplier;
}

void CharacterController::set_max_jump_amount(const uint8_t amount){
    _max_jump_amount = amount;
}

void CharacterController::set_max_acceleration(const int32_t acceleration){
    _max_acceleration = acceleration;
}

void CharacterController::set_friction(const int32_t friction){
    _friction = friction;
}

void CharacterController::set_coyote_time(const real_t time){
    _coyote_time = time;
}

void CharacterController::set_jump_buffer(const real_t buffer){
    _jump_buffer = buffer;
}

void CharacterController::set_can_hold_jump(const bool flag){
    _can_hold_jump = flag;
}

void CharacterController::set_jump_left(const uint8_t amount){
    _jumps_left = amount;
}

void CharacterController::set_holding_jump(const bool holding){
    _holding_jump = holding;
}

int32_t CharacterController::get_max_jump_height() const{
    return _max_jump_height;
}

int32_t CharacterController::get_min_jump_height() const{
    return _min_jump_height;
}

int32_t CharacterController::get_double_jump_height() const{
    return _double_jump_height;
}

real_t CharacterController::get_jump_duration() const{
    return _jump_duration;
}

real_t CharacterController::get_coyote_time() const{
    return _coyote_time;
}

real_t CharacterController::get_jump_buffer() const{
    return _jump_buffer;
}

bool CharacterController::get_can_hold_jump() const{
    return _can_hold_jump;
}

real_t CharacterController::get_falling_gravity_multiplier() const{
    return _falling_gravity_multiplier;
}

uint8_t CharacterController::get_max_jump_amount() const{
    return _max_jump_amount;
}

int32_t CharacterController::get_max_acceleration() const{
    return _max_acceleration;
}

int32_t CharacterController::get_friction() const{
    return _friction;
}

godot::Vector2& CharacterController::get_vel_ref(){
    return _vel;
}

godot::Vector2& CharacterController::get_acc_ref(){
    return _acc;
}

godot::Timer& CharacterController::get_coyote_timer(){
    return *_coyote_timer;
}

godot::Timer& CharacterController::get_jump_buffer_timer(){
    return *_jump_buffer_timer;
}

bool CharacterController::get_holding_jump() const{
    return _holding_jump;
}

real_t CharacterController::get_default_gravity() const{
    return _default_gravity;
}

uint8_t CharacterController::get_jump_left() const{
    return _jumps_left;
}

real_t CharacterController::get_release_gravity_multiplier() const{
    return _release_gravity_multiplier;
}