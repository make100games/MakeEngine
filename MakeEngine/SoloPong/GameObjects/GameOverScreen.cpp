//
//  VictoryScreen.cpp
//  MakeEngine
//
//  Created by Make100Games on 09.02.26.
//

#include "GameOverScreen.hpp"
#include "Rectangle.hpp"
#include "Constants.hpp"

static const std::string tag = "GameOverScreen";

GameOverScreen::GameOverScreen(Vec3 color, GameManager* gameManager):myColor(color), myGameManager(gameManager) {
}

GameOverScreen::~GameOverScreen() {
    
}

void GameOverScreen::initialize() {
    
}

void GameOverScreen::update(float deltaTime) {
    
}

const std::unique_ptr<Renderable>& GameOverScreen::renderable() const {
    return myRenderable;
}

Transform GameOverScreen::transform() {
    return myTransform;
}

RigidBody GameOverScreen::rigidBody() {
    return myRigidBody;
}

void GameOverScreen::onCanvasBoundsChanged(Bounds bounds) {
    myBounds = bounds;
    float left = 0.0f;
    float top =0.0f;
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
    myRenderable = std::make_unique<Rectangle>(vertices, myColor, tag);
    myCollider = Collider { left, top, myBounds.right, Constants::HudHeight, tag };
}

Collider GameOverScreen::collider() {
    return myCollider;
}

void GameOverScreen::onCollision(Collider other) {
    
}

void GameOverScreen::onKeyInput(KeyInput input) {
    if(input.interaction == KeyInteraction::KeyDown && input.keyCode == KeyCode::Space) {
        if(myGameManager != nullptr) {
            myGameManager -> startGame();
        }
    }
}
