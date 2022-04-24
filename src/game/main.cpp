#include "engine/engine.hpp"
#include "engine/rendering/sprite.hpp"
#include "engine/collision/collider.hpp"
#include "engine/component.hpp"
#include "engine/components/rigidbody.hpp"
#include "engine/components/spriterenderer.hpp"
#include "engine/ui/text.hpp"
#include "engine/input.hpp"
#include <cstdlib>

//static Engine engine = Engine();

class GameController : public Component
{
    public:
        GameController(Entity& e) : Component(e)
        {

        }

        void start()
        {
            // create character

            // sprite
            /*
            Sprite* character_sprite = new Sprite();
            *character_sprite = Sprite::load("guy.png");
            {
                auto& e = engine.scene.new_entity();
                auto& r = e.add_component<SpriteRenderer>();
                r.sprite = character_sprite;
            }
            */
        }

        void update()
        {
            // main g
        }
};

int main()
{
    auto engine = Engine();
    //engine.camera = Camera(5.0f);

    // hand over control to engine
    engine.loop();

    return 0;
}