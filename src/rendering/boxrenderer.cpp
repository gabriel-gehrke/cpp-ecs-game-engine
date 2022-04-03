#include "rendering/boxrenderer.hpp"
#include "engine.hpp"

Bounds BoxRenderer::bounds() const
{
    return Bounds::from_pos_and_size(this->entity.position, this->size);
}

void BoxRenderer::draw()
{
    int x = (int) this->entity.position.x;
    int y = (int) this->entity.position.y;
    int w = (int) this->size.x;
    int h = (int) this->size.y;
    Graphics::draw_rectangle(x, y, w, h, Color::white());
}