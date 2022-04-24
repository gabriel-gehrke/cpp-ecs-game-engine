#pragma once

#include "engine/component.hpp"
#include "engine/rendering/sprite.hpp"
#include "engine/components/spriterenderer.hpp"
#include "engine/entity.hpp"

class CharacterController : public Component
{
    public:
        float speed = 5.0f;

        CharacterController(Entity& e) : Component(e), renderer(this->entity.add_component<SpriteRenderer>())
        {
            allocated_sprite = new Sprite();
            *allocated_sprite = Sprite::load("guy.png");
            renderer.sprite = allocated_sprite;
            renderer.layer = 10;
        }

        void update();
    
    private:
        Sprite* allocated_sprite;
        SpriteRenderer& renderer;
};