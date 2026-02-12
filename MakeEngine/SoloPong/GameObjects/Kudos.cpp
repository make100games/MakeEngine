//
//  Kudos.cpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#include "Kudos.hpp"
#include "Rectangle.hpp"

static const std::string tag = "Kudos";

Kudos::Kudos(float positionX, float positionY, Vec3 color): myTransform({.renderTag = tag}) {
    this -> positionX = positionX;
    this -> positionY = positionY;
    auto top = positionY;
    auto left = positionX;
    std::vector<float> vertices = std::vector<float> {
        // Triangle 1
        left, top,
        left, top + Size,
        left + Size, top + Size,
        // Triangle 2
        left, top,
        left + Size, top,
        left + Size, top + Size
    };
    myRenderable = std::make_unique<Rectangle>(vertices, color, tag);
}

Kudos::~Kudos() {
    
}

float Kudos::getPositionX() {
    return positionX;
}

float Kudos::getPositionY() {
    return positionY;
}

void Kudos::initialize() {
    myCollider = Collider { myTransform.position.x, myTransform.position.y, Size, Size, tag };
}

void Kudos::update(float deltaTime) {
    
}

const std::unique_ptr<Renderable>& Kudos::renderable() const {
    return myRenderable;
}

Transform Kudos::transform() {
    return myTransform;
}

RigidBody Kudos::rigidBody() {
    return myRigidBody;
}

void Kudos::onCanvasBoundsChanged(Bounds bounds) {
    myBounds = bounds;
}

Collider Kudos::collider() {
    return myCollider;
}

void Kudos::onCollision(Collider other) {
    
}

void Kudos::onKeyInput(KeyInput input) {
    
}
