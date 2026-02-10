//
//  Sprite.hpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include "Vec2.hpp"
#include "Vec4.hpp"
#include "Texture.hpp"

class Sprite {
public:
    Sprite(Texture* texture) : texture(texture) {}
    
    Texture* texture = nullptr;
    
    Vec2 position { 0.0f, 0.0f };
    float rotation = 0.0f;  // In radians
    Vec2 scale { 1.0f, 1.0f };
    
    Vec4 color { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // TODO add sprite sheet/atlas support later for animating sprites
};

#endif /* Sprite_hpp */
