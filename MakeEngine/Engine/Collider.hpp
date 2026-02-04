//
//  Collider.hpp
//  Breakout
//
//  Created by Chris Braunschweiler on 08.05.25.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include <string>

class GameObject;

struct Collider {
    float x;
    float y;
    float width;
    float height;
    std::string tag;
    GameObject* gameObject = nullptr;
    
    Collider copyWithX(float newX) const {
        Collider newCollider = *this;
        newCollider.x = newX;
        return newCollider;
    }
    
    Collider copyWithY(float newY) const {
        Collider newCollider = *this;
        newCollider.y = newY;
        return newCollider;
    }
};

#endif /* Collider_hpp */
