#include "engine/components/spriterenderer.hpp"
#include "engine/rendering/graphics.hpp"
#include "engine/engine.hpp"
#include "engine/camera.hpp"
#include "engine/scene.hpp"

Bounds SpriteRenderer::bounds() const
{
    return Bounds(float2::zero(), float2::zero());
}

void SpriteRenderer::draw()
{
    if (this->sprite == NULL) return;

    const float& rot = this->entity.rotation;
    const float2& pos = this->entity.position;
    const auto& cam = this->entity.scene.engine.camera;

    // calculate upper left and lower right corner of sprite (based on entity position and scale)
    const float2 hscale = this->entity.scale * 0.5f;
    const int2 upleft = cam.world_to_screenpos(pos.x - hscale.x, pos.y + hscale.y);
    const int2 botright = cam.world_to_screenpos(pos.x + hscale.x, pos.y - hscale.y);

    Graphics::draw_sprite(this->sprite, upleft, botright, rot);
}