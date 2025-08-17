#ifndef RESOURCE_H
#define RESOURCE_H
namespace Constant{
    namespace Resource
    {
        // Shader names
        constexpr const char* SPRITE_SHADER = "sprite";
        constexpr const char* PARTICLE_SHADER = "particle";
        
        // Texture names
        constexpr const char* BRICK_TEXTURE = "brick";
        constexpr const char* SOLID_BRICK_TEXTURE = "solid_brick";
        constexpr const char* BACKGROUND = "background";
        constexpr const char* PLAYER = "player";
        constexpr const char* BALL = "ball";
        constexpr const char* PARTICLE = "particle";




        // Shader uniform names
        constexpr const char* TEX_UNIFORM = "tex";
        constexpr const char* PROJECTION_UNIFORM = "projection";
        constexpr const char* MODEL_UNIFORM = "model";
        constexpr const char* SPRITE_COLOR_UNIFORM = "spriteColor";


    }
}
#endif
