//
//  Boundary.cpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#include "Boundary.hpp"
#include "Rectangle.hpp"
#include "Constants.hpp"

static const std::string tag = "Boundary";
static const float Height = 50.0f;

Boundary::Boundary() {
    
}

Boundary::~Boundary() {
    
}

void Boundary::initialize() {
    myCollider = Collider { 0, -Height, myBounds.right, 0, tag };
}

void Boundary::update(float deltaTime) {
    
}

const std::unique_ptr<Renderable>& Boundary::renderable() const {
    return myRenderable;
}

Transform Boundary::transform() {
    return myTransform;
}

RigidBody Boundary::rigidBody() {
    return myRigidBody;
}

void Boundary::onCanvasBoundsChanged(Bounds bounds) {
    float left = 0.0f;
    float top = bounds.bottom - Constants::HudHeight;
    Vec3 color = Vec3 { 0.3f, 0.3f, 0.3f };
    std::vector<float> vertices = std::vector<float> {
        // Triangle 1
        left, top,
        left, bounds.bottom,
        bounds.right, bounds.bottom,
        // Triangle 2
        left, top,
        bounds.right, top,
        bounds.right, bounds.bottom
    };
    myRenderable = std::make_unique<Rectangle>(vertices, color, tag);
}

Collider Boundary::collider() {
    return myCollider;
}

void Boundary::onCollision(Collider other) {
    
}

void Boundary::onKeyInput(KeyInput input) {
    
}
