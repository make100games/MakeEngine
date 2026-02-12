//
//  Hud.cpp
//  MakeEngine
//
//  Created by Make100Games on 07.02.26.
//

#include "Hud.hpp"
#include "Rectangle.hpp"
#include "Constants.hpp"

static const std::string tag = "HUD";

Hud::Hud() {
    
}

Hud::~Hud() {
    
}

void Hud::initialize() {
    
}

void Hud::update(float deltaTime) {
    
}

const std::unique_ptr<Renderable>& Hud::renderable() const {
    return myRenderable;
}

Transform Hud::transform() {
    return myTransform;
}

RigidBody Hud::rigidBody() {
    return myRigidBody;
}

void Hud::onCanvasBoundsChanged(Bounds bounds) {
    myBounds = bounds;
    float left = 0.0f;
    float top = bounds.bottom - Constants::HudHeight;
    Vec4 color = Vec4 { 0.3f, 0.3f, 0.3f, 1.0f };
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
    myCollider = Collider { left, top, myBounds.right, Constants::HudHeight, tag };
}

Collider Hud::collider() {
    return myCollider;
}

void Hud::onCollision(Collider other) {
    
}

void Hud::onKeyInput(KeyInput input) {
    
}
