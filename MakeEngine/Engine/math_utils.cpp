//
//  math_utils.cpp
//  Breakout
//
//  Created by Chris Braunschweiler on 02.05.25.
//

#include "math_utils.hpp"

// TODO: write unit test to test this function thoroughly
/**
 Calculates values of an orthographic projection matrix and populates the passed matrix with those values. The resulting matrix is
 then usable for passing to, e.g. OpenGL as a projection.
 */
void ortho(float left, float right, float bottom, float top, float near, float far, float* matrix) {
    matrix[0]  = 2.0f / (right - left);
    matrix[1]  = 0.0f;
    matrix[2]  = 0.0f;
    matrix[3]  = 0.0f;

    matrix[4]  = 0.0f;
    matrix[5]  = 2.0f / (top - bottom);
    matrix[6]  = 0.0f;
    matrix[7]  = 0.0f;

    matrix[8]  = 0.0f;
    matrix[9]  = 0.0f;
    matrix[10] = -2.0f / (far - near);
    matrix[11] = 0.0f;

    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(far + near) / (far - near);
    matrix[15] = 1.0f;
}

float dot(const Vec2& a, const Vec2& b) {
    return a.x * b.x + a.y * b.y;
}

float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(const Vec2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float length(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec2 normalize(const Vec2& v) {
    float len = length(v);
    if (len == 0.0f) return {0.0f, 0.0f}; // avoid division by zero
    return { v.x / len, v.y / len };
}

Vec3 normalize(const Vec3& v) {
    float len = length(v);
    if (len == 0.0f) return {0.0f, 0.0f, 0.0f};
    return { v.x / len, v.y / len, v.z / len };
}

float clamp(float value, float minVal, float maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}
