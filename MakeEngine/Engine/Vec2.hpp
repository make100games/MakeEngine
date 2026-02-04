//
//  Vec2.hpp
//  MakeEngine
//
//  Created by Make100Games on 04.02.26.
//

#ifndef Vec2_hpp
#define Vec2_hpp

#include <stdio.h>

struct Vec2 {
    float x;
    float y;
    
    // Addition
    Vec2 operator+(const Vec2& other) const {
        return { x + other.x, y + other.y };
    }

    // Subtraction
    Vec2 operator-(const Vec2& other) const {
        return { x - other.x, y - other.y };
    }

    // Compound addition
    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Compound subtraction
    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    // Multiply vector by a scalar
    Vec2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    // Multiply scalar by vector (friend function)
    friend Vec2 operator*(float scalar, const Vec2& v) {
        return { v.x * scalar, v.y * scalar };
    }
    
    Vec2 operator*(const Vec2& other) const {
        return { x * other.x, y * other.y };
    }
};

#endif /* Vec2_hpp */
