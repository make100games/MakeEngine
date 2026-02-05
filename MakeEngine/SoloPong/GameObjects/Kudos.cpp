//
//  Kudos.cpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#include "Kudos.hpp"
#include "Rectangle.hpp"

static const std::string tag = "Kudos";
static const float size = 10.0f;

Kudos::Kudos(float positionX, float positionY, int key): myTransform({0.0f, 0.0f, tag}) {
    this->positionX = positionX;
    this->positionY = positionY;
    this->key = key;
    auto color = Vec3 { 0.0f, 1.0f, 0.0f };
    auto top = 0.0f;
    auto left = 0.0f;
    std::vector<float> vertices = std::vector<float> {
        // Triangle 1
        left, top,
        left, top + size,
        left + size, top + size,
        // Triangle 2
        left, top,
        left + size, top,
        left + size, top + size
    };
    myRenderable = std::make_unique<Rectangle>(vertices, color, tag);
}

Kudos::~Kudos() {
    
}

void Kudos::initialize() {
    myTransform.copyWithX(positionX).copyWithY(positionY);
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

int Kudos::getKey() {
    return key;
}
