//
//  Vec3.hpp
//  Breakout
//
//  Created by Chris Braunschweiler on 09.05.25.
//

#ifndef Vec3_hpp
#define Vec3_hpp

#include <stdio.h>

struct Vec3 {
    float x;
    float y;
    float z;
    
    // Multiply vector by a scalar
    Vec3 operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    }

    // Multiply scalar by vector (friend function)
    friend Vec3 operator*(float scalar, const Vec3& v) {
        return { v.x * scalar, v.y * scalar, v.z * scalar };
    }
    
    Vec3 operator*(const Vec3& other) const {
        return { x * other.x, y * other.y, z * other.z };
    }
    
    // Addition
    Vec3 operator+(const Vec3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    // Subtraction
    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    // Compound addition
    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Compound subtraction
    Vec3& operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
};

#endif /* Vec3_hpp */
