//
//  Ball.hpp
//  MakeEngine
//
//  Created by Make100Games on 02.02.26.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Renderable.hpp"
#include <memory>
#include "Transform.hpp"
#include "Bounds.hpp"
#include "Collider.hpp"
#include "KeyInput.hpp"

class Ball : public GameObject {
public:
    Ball();
    ~Ball();
    
    void initialize() override;
    
    void update(float deltaTime) override;
    
    const std::unique_ptr<Renderable>& renderable() const override;
    
    Transform transform() override;
    
    void onCanvasBoundsChanged(Bounds bounds) override;
    
    Collider collider() override;
    
    void onCollision(Collider other) override;
    
    void onKeyInput(KeyInput input) override;
    
private:
    std::unique_ptr<Renderable> myRenderable;
    Transform myTransform;
    Bounds myCanvasBounds;
    Collider myCollider;
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float size = 20.0f;
    
    void performAngleBasedBounce(Collider other);
};

#endif /* Ball_hpp */
