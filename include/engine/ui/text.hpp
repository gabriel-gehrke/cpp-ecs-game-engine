#pragma once

#include "engine/component.hpp"
#include "engine/resources.hpp"
#include "engine/rendering/graphics.hpp"
#include <string>
#include <SDL2/SDL.h>

enum UITextAlignment
{
    CENTER = 0,

    LEFT   = 0b0010,
    RIGHT  = 0b0001,
    TOP    = 0b1000,
    BOTTOM = 0b0100
};

class UIText : public Component
{
    private:
        int font_size = 20;
        Color color = Color::white();
        std::string text = "Text";
        const Resource* font_resource = &Resource::load(std::string("pixel.ttf"));

        // the component stores a cached version of the rendered font, which only gets rerendered if the size, font, color or text changes.
        int2 texture_size;
        SDL_Texture* cached_texture = NULL;
        TTF_Font* cached_font = NULL;

        void rerender();
    
    public:
        UIText(Entity& e) : Component(e) {rerender();}

        void update();

        void set_text(const std::string& text);
        const std::string& get_text() {return text;}

        void set_font_resource(const Resource& font);
        void set_font_size(int size);
        void set_color(const Color& color);
        
        int2 screen_position;
        int alignment = LEFT | TOP;
};