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
#include "Renderable.hpp"

class Sprite : public Renderable {
public:
    Sprite(Texture* tex): Renderable() {
        texture = tex;
    }
    
    Vec4 _color { 1.0f, 1.0f, 1.0f, 1.0f };
    
    const Vec4& color() const override {
        return _color;
    }
    
    // TODO: add sprite sheet/atlas support later for animating sprites
};

#endif /* Sprite_hpp */
