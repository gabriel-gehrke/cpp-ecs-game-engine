#include "engine/engine.hpp"
#include "engine/ui/text.hpp"
#include "engine/input.hpp"
#include "engine/ui/text.hpp"
#include "game/charactercontroller.hpp"
#include <cstdlib>
#include <iostream>

static Engine engine = Engine();

class GameController : public Component
{
    public:
        Entity* player;

        GameController(Entity& e) : Component(e)
        {

        }

        void awake()
        {
            player = &engine.scene.new_entity();
            player->add_component<CharacterController>();
        }

        void update()
        {
            
        }
};

int main()
{
    engine.camera = Camera(5.0f);
    engine.scene.new_entity().add_component<GameController>();

    auto& text = engine.scene.new_entity().add_component<UIText>();
    text.set_text("Ja Moinsen");
    text.set_font_size(100);

    // hand over control to engine
    engine.loop();

    return 0;
}