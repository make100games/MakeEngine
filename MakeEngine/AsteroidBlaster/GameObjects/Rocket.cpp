//
//  Rocket.cpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#include "Rocket.hpp"
#include "Rectangle.hpp"
#include "Sprite.hpp"

Rocket::Rocket() {
    spriteTexture = std::make_unique<Texture>("MakeEngine/AsteroidBlaster/Assets/Rocket.png");
    myRenderable = std::make_unique<Sprite>(spriteTexture.get());
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
