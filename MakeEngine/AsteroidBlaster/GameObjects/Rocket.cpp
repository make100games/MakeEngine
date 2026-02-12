//
//  Rocket.cpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#include "Rocket.hpp"
#include "Rectangle.hpp"

Rocket::Rocket() {
    std::vector<float> vertices = {
        // Tri 1
        0.0f, 0.0f,
        100.0f, 0.0f,
        100.0f, 200.0f,
        // Tri 2
        0.0f, 0.0f,
        100.0f, 200.0f,
        0.0f, 200.0f
    };
    Vec4 color = Vec4 { 1.0f, 0.0f, 0.0f, 1.0f };
    myRenderable = std::make_unique<Rectangle>(vertices, color, "Rocket");
}

Rocket::~Rocket() {
    
}

void Rocket::initialize() {
    
}

void Rocket::update(float deltaTime) {
    
}

const std::unique_ptr<Renderable>& Rocket::renderable() const {
    return myRenderable;
}

Transform Rocket::transform() {
    return myTransform;
}

RigidBody Rocket::rigidBody() {
    return myRigidBody;
}

void Rocket::onCanvasBoundsChanged(Bounds bounds) {
}

Collider Rocket::collider() {
    return myCollider;
}

void Rocket::onCollision(Collider other) {
}

void Rocket::onKeyInput(KeyInput keyInput) {
}
