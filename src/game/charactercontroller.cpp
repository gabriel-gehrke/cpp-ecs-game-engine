#include "game/charactercontroller.hpp"

#include "engine/entity.hpp"
#include "engine/scene.hpp"
#include "engine/input.hpp"
#include "engine/engine.hpp"

void CharacterController::update()
{
    const auto& cam = this->entity.scene.engine.camera;

    // look at cursor
    float2 target = cam.screen_to_worldpos(Input::mouse_position());
    float2 dir = (target - this->entity.position).normalized();
    this->entity.set_up(dir);

    // movement
    float x = Input::is_key_down('a') * -speed + Input::is_key_down('d') * speed;
    float y = Input::is_key_down('s') * -speed + Input::is_key_down('w') * speed;
    if (std::abs(x) > EPSILON || std::abs(y) > EPSILON)
    {
        this->entity.position += float2(x, y).normalized() * dt();
    }
}