//
//  Ball.cpp
//  MakeEngine
//
//  Created by Make100Games on 02.02.26.
//

#include "Ball.hpp"
#include "Rectangle.hpp"
#include <iostream>

static const std::string tag = "Ball";
static const float ballMinSpeed = 150.0f;
static const float ballMaxSpeed = 1000.0f;
static const float ballVelocity = 150.0f;

// Amount by which to gradually increase speed of ball
static const float increaseInSpeed = 5.0f;

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
    yVelocity = ballVelocity;
    myRigidBody = RigidBody { xVelocity, yVelocity };
}

void Ball::update(float deltaTime) {
    // Check collision with top or bottom of screen
    if(myTransform.y < myCanvasBounds.top) {
        myTransform = myTransform.copyWithY(myCanvasBounds.top);
        yVelocity *= -1;
    } else if((myTransform.y + size) > myCanvasBounds.bottom) {
        myTransform = myTransform.copyWithY(myCanvasBounds.bottom - size);
        yVelocity *= -1;
    }
    
    // Check collision with left or right edge of screen
    if(myTransform.x < myCanvasBounds.left) {
        myTransform = myTransform.copyWithX(myCanvasBounds.left);
        xVelocity *= -1;
    } else if((myTransform.x + size) > myCanvasBounds.right) {
        myTransform = myTransform.copyWithX(myCanvasBounds.right - size);
        xVelocity *= -1;
    }
    
    myTransform.x += xVelocity * deltaTime;
    myTransform.y += yVelocity * deltaTime;
    myCollider = myCollider.copyWithX(myTransform.x).copyWithY(myTransform.y);
    
    increaseSpeedOverTime(deltaTime);
    
    myRigidBody = RigidBody { xVelocity, yVelocity };
}

void Ball::increaseSpeedOverTime(float deltaTime) {
    auto magnitude = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity));
    auto xNormalized = xVelocity / magnitude;
    auto yNormalized = yVelocity / magnitude;
    
    // Increase speed
    magnitude += increaseInSpeed * deltaTime;
    
    xVelocity = xNormalized * magnitude;
    yVelocity = yNormalized * magnitude;
}

const std::unique_ptr<Renderable>& Ball::renderable() const {
    return myRenderable;
}

Transform Ball::transform() {
    return myTransform;
}

RigidBody Ball::rigidBody() {
    return myRigidBody;
}

void Ball::onCanvasBoundsChanged(Bounds bounds) {
    myCanvasBounds = bounds;
}

Collider Ball::collider() {
    return myCollider;
}

void Ball::onCollision(Collider other) {
    // Do a simple overlap resolution to see whether the ball hit the sides of an object or the top/bottom of it. If it hit the sides, invert the x velocity. If it hit the top/bottom, invert the y velocity. Courtesy of Chat GPT :)
    Collider thisCollider = myCollider; // Get the ball's current collider bounds

    // Compute the centers
    float thisCenterX = thisCollider.x + thisCollider.width / 2.0f;
    float thisCenterY = thisCollider.y + thisCollider.height / 2.0f;
    float otherCenterX = other.x + other.width / 2.0f;
    float otherCenterY = other.y + other.height / 2.0f;

    // Compute the current overlap (assuming axis-aligned rectangles)
    float deltaX = thisCenterX - otherCenterX;
    float deltaY = thisCenterY - otherCenterY;

    float combinedHalfWidths = (thisCollider.width + other.width) / 2.0f;
    float combinedHalfHeights = (thisCollider.height + other.height) / 2.0f;

    float overlapX = combinedHalfWidths - std::abs(deltaX);
    float overlapY = combinedHalfHeights - std::abs(deltaY);

    // Determine direction of collision
    if (overlapX < overlapY) {
        // Horizontal collision → invert X velocity
        xVelocity *= -1;
        if(deltaX > 0) {
            // Collided with right side
            // Position ball at the edge of collision to avoid spurious double collisions? Not sure if this will do anything but it's an effort to fix some bugs where the ball sometimes just plows through multiple rows of bricks
            myTransform.x = other.x + other.width;
        } else if(deltaX < 0) {
            myTransform.x = other.x;
        }
    } else {
        if (other.tag == "Paddle") {
            performAngleBasedBounce(other);
        }
    }
}

void Ball::performAngleBasedBounce(Collider other) {
    // The following is also courtesy of Chat GPT. Gettin' a little too comfortable having it do all of the algorithmic heavy lifting for me. But I do understand what is happening here :)
    // This should only be called if we collide with the paddle so we can assume that the other collider is the collider of the paddle
    float ballCenterX = myCollider.x + (myCollider.width / 2);
    float paddleCenterX = other.x + (other.width / 2);
    float paddleHalfWidth = other.width / 2.0f;

    // Calculate the hit position relative to paddle center
    float distanceFromCenter = ballCenterX - paddleCenterX;

    // Normalize to [-1.0, 1.0] range
    float normalized = distanceFromCenter / paddleHalfWidth;
    normalized = std::clamp(normalized, -1.0f, 1.0f); // safety check

    // Add x velocity based on hit location
    float maxBounceAngle = 75.0f * (M_PI / 180.0f); // in radians
    float speed = std::sqrt(xVelocity * xVelocity + yVelocity * yVelocity);
    xVelocity = speed * std::sin(normalized * maxBounceAngle);
    if(myCollider.y < other.y) {
        // Hitting top of paddle
        bounceOffBallDependingOnPaddleSpeed(other, Vec2 { 0, 1 });
        myTransform.y = other.y - size;
    } else if(myCollider.y > other.y) {
        // Hitting bottom of paddle
        bounceOffBallDependingOnPaddleSpeed(other, Vec2 { 0, -1 });
        myTransform.y = other.y + other.height;
    }
}

void Ball::bounceOffBallDependingOnPaddleSpeed(Collider other, Vec2 paddleNormal) {
    // Calculate reflected velocity
    auto ballVelocity = Vec2 { xVelocity, yVelocity };
    Vec2 reflected = ballVelocity - 2.0f * dot(ballVelocity, paddleNormal) * paddleNormal;
    
    // Calculate paddle velocity along collision normal
    auto otherXVelocity = other.gameObject->rigidBody().xVelocity;
    auto otherYVelocity = other.gameObject->rigidBody().yVelocity;
    auto paddleVelocity = Vec2 { otherXVelocity, otherYVelocity };
    float paddleSpeedAlongNormal = dot(paddleVelocity, paddleNormal);
    
    // Add influence of paddle speed to reflected ball speed
    reflected += paddleNormal * paddleSpeedAlongNormal;
    
    // Clamp speed
    float speed = length(reflected);
    speed = clamp(speed, ballMinSpeed, ballMaxSpeed);
    reflected = normalize(reflected) * speed;
    
    // Apply velocity
    ballVelocity = reflected;
    xVelocity = ballVelocity.x;
    yVelocity = ballVelocity.y;
}

void Ball::onKeyInput(KeyInput input) {
    // No-op
}
