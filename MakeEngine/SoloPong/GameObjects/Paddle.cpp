//
//  Paddle.cpp
//  MakeEngine
//
//  Created by Make100Games on 01.02.26.
//

#include "Paddle.hpp"
#include "Rectangle.hpp"
#include <iostream>
#include "Logging.hpp"

static const std::string tag = "Paddle";
static const float paddleVelocity = 500.0f;

Paddle::Paddle():myTransform(Transform { 0.0f, 0.0f, tag }) {
    // Note: Place top left vertex at 0,0. Otherwise you bake in an offset
    float left = 0.0f;
    float top = 0.0f;
    std::vector<float> vertices = {
        // Triangle 1
        left, top,
        left, top + height,
        left + width, top + height,
        // Triangle 2
        left, top,
        left + width, top,
        left + width, top + height
    };
    Vec3 color = Vec3 { 1.0f, 1.0f, 0.0f };
    myRenderable = std::make_unique<Rectangle>(vertices, color, tag);
}

Paddle::~Paddle() {
    
}

void Paddle::initialize() {
    auto xPos = (myCanvasBounds.right / 2) - (width / 2);
    auto yPos = (myCanvasBounds.bottom / 2) - (height / 2);
    myTransform = myTransform.copyWithX(xPos);
    myTransform = myTransform.copyWithY(yPos);
    myCollider = Collider { myTransform.x, myTransform.y, width, height, tag };
}

void Paddle::update(float deltaTime) {
    // Horizontal movement
    if(myTransform.x < myCanvasBounds.left) {
        xVelocity = 0.0f;
        myTransform = myTransform.copyWithX(myCanvasBounds.left);
    } else if((myTransform.x + width) > myCanvasBounds.right) {
        xVelocity = 0.0f;
        myTransform = myTransform.copyWithX(myCanvasBounds.right - width);
    } else {
        myTransform.x += xVelocity * deltaTime;
    }
    
    // Vertical movement
    if(myTransform.y < myCanvasBounds.top) {
        yVelocity = 0.0f;
        myTransform = myTransform.copyWithY(myCanvasBounds.top);
    } else if((myTransform.y + height) > myCanvasBounds.bottom) {
        yVelocity = 0.0f;
        myTransform = myTransform.copyWithY(myCanvasBounds.bottom - height);
    } else {
        myTransform.y += yVelocity * deltaTime;
    }
    
    myCollider = myCollider.copyWithX(myTransform.x).copyWithY(myTransform.y);
}

const std::unique_ptr<Renderable>& Paddle::renderable() const {
    return myRenderable;
}

Transform Paddle::transform() {
    return myTransform;
}

void Paddle::onCanvasBoundsChanged(Bounds bounds) {
    myCanvasBounds = bounds;
}

Collider Paddle::collider() {
    return myCollider;
}

void Paddle::onCollision(Collider other) {
    
}

// TODO: Improve movement here. Currently the following is not working yet:
//  1. Hold left arrow key -> Move left -> This is ok
//  2. Press and hold right arrow key -> Move right -> This is ok
//  3. Release right arrow key -> Should move back to left as left still pressed -> Not working. Paddle stands still
//  I need to keep track of currently pressed keys so that I can restore the movement properly when keys are released

void Paddle::onKeyInput(KeyInput keyInput) {
    //std::cout << "Key Input: " << keyInput << std::endl;
    if(keyInput.interaction == KeyInteraction::KeyDown) {
        switch(keyInput.keyCode) {
            case KeyCode::LeftArrow:
                xVelocity = -paddleVelocity;
                break;
            case KeyCode::RightArrow:
                xVelocity = paddleVelocity;
                break;
            case KeyCode::UpArrow:
                yVelocity = -paddleVelocity;
                break;
            case KeyCode::DownArrow:
                yVelocity = paddleVelocity;
                break;
            default:
                break;
        }
    } else if(keyInput.interaction == KeyInteraction::KeyUp) {
        switch(keyInput.keyCode) {
            case KeyCode::LeftArrow:
                if(xVelocity < 0) xVelocity = 0.0f;
                break;
            case KeyCode::RightArrow:
                if(xVelocity > 0) xVelocity = 0.0f;
                break;
            case KeyCode::UpArrow:
                if(yVelocity < 0) yVelocity = 0.0f;
                break;
            case KeyCode::DownArrow:
                if(yVelocity > 0) yVelocity = 0.0f;
                break;
            default:
                break;
        }
    }
}




