//
//  Paddle.hpp
//  MakeEngine
//
//  Created by Make100Games on 01.02.26.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "Paddle.hpp"
#include "GameObject.hpp"
#include "Renderable.hpp"
#include <memory>
#include "Transform.hpp"
#include "Bounds.hpp"
#include "Collider.hpp"
#include "KeyInput.hpp"
#include "RigidBody.hpp"

class Paddle : public GameObject {
public:
    Paddle();
    ~Paddle();
    
    void initialize() override;
    
    void update(float deltaTime) override;
    
    const std::unique_ptr<Renderable>& renderable() const override;
    
    Transform transform() override;
    
    RigidBody rigidBody() override;
    
    void onCanvasBoundsChanged(Bounds bounds) override;
    
    Collider collider() override;
    
    void onCollision(Collider other) override;
    
    void onKeyInput(KeyInput keyInput) override;
    
private:
    std::unique_ptr<Renderable> myRenderable;
    Transform myTransform;
    Bounds myCanvasBounds;
    Collider myCollider;
    RigidBody myRigidBody;
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float width = 150.0f;
    float height = 20.0f;
};

#endif /* Paddle_hpp */
