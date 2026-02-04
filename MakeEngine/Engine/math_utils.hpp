//
//  math_utils.hpp
//  Breakout
//
//  Created by Chris Braunschweiler on 02.05.25.
//

#ifndef math_utils_hpp
#define math_utils_hpp

#include <stdio.h>
#include "Vec2.hpp"
#include "Vec3.hpp"
#include <iostream>

/**
 Generates an orghographic projection matrix. Didn't feel like including GLM or whatever for now... I know, cost of carry and such. Sue me.
 */
void ortho(float left, float right, float bottom, float top, float near, float far, float* matrix);

/**
 Computes the dot product of 2 Vec2 types.
 */
float dot(const Vec2& a, const Vec2& b);

/**
 Computes the dot product of 2 Vec3 types.
 */
float dot(const Vec3& a, const Vec3& b);

/**
 Computes the magnitude of a Vec2.
 */
float length(const Vec2& v);

/**
 Computes the magnitude of a Vec3.
 */
float length(const Vec3& v);

/**
 Computes unit vector in the same direction.
 */
Vec2 normalize(const Vec2& v);

/**
 Computes unit vector in the same direction.
 */
Vec3 normalize(const Vec3& v);

/**
 Restricst a value to a range.
 */
float clamp(float value, float minVal, float maxVal);

#endif /* math_utils_hpp */
