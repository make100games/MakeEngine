//
//  Ball.cpp
//  MakeEngine
//
//  Created by Make100Games on 02.02.26.
//

#include "Ball.hpp"
#include "Rectangle.hpp"

static const std::string tag = "Ball";

Ball::Ball():myTransform(Transform {0.0f, 0.0f, tag}) {
    // Note: Place top left vertex at 0,0. Otherwise you bake in an offset
    float left = 0.0f;
    float top = 0.0f;
    
    std::vector<float> vertices = {
        // Triangle 1
        left, top,
        left, top + size,
        left + size, top + size,
        // Triangle 2
        left, top,
        left + size, top,
        left + size, top + size
    };
    Vec3 color = { 1.0f, 1.0f, 1.0f };
    myRenderable = std::make_unique<Rectangle>(vertices, color, tag);
}

Ball::~Ball() {
    
}

void Ball::initialize() {
    float x = (myCanvasBounds.right / 2) - (size / 2);
    float y = myCanvasBounds.top + 50;
    myTransform = myTransform.copyWithX(x);
    myTransform = myTransform.copyWithY(y);
    myCollider = Collider { myTransform.x, myTransform.y, size, size, tag };
}

void Ball::update(float deltaTime) {
    
}

const std::unique_ptr<Renderable>& Ball::renderable() const {
    return myRenderable;
}

Transform Ball::transform() {
    return myTransform;
}

void Ball::onCanvasBoundsChanged(Bounds bounds) {
    myCanvasBounds = bounds;
}

Collider Ball::collider() {
    return myCollider;
}

void Ball::onCollision(Collider other) {
    
}

void Ball::onKeyInput(KeyInput input) {
    
}
