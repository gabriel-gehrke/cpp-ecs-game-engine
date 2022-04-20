#include "engine/rendering/renderer.hpp"

void Renderer::update()
{
    // TODO: add check for bounds
    //Bounds bounds = this->bounds();

    this->draw();
}