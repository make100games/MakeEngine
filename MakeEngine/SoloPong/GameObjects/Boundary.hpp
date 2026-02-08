//
//  Boundary.hpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#ifndef Boundary_hpp
#define Boundary_hpp

#include <stdio.h>
#include "Paddle.hpp"
#include "GameObject.hpp"
#include "Renderable.hpp"
#include <memory>
#include "Transform.hpp"
#include "Bounds.hpp"
#include "Collider.hpp"
#include "KeyInput.hpp"
#include "RigidBody.hpp"

class Boundary : public GameObject {
public:
    Boundary();
    ~Boundary();
    
    void initialize() override;
    
    void update(float deltaTime) override;
    
    const std::unique_ptr<Renderable>& renderable() const override;
    
    Transform transform() override;
    
    RigidBody rigidBody() override;
    
    void onCanvasBoundsChanged(Bounds bounds) override;
    
    Collider collider() override;
    
    void onCollision(Collider other) override;
    
    void onKeyInput(KeyInput input) override;
    
private:
    std::unique_ptr<Renderable> myRenderable;
    Transform myTransform;
    RigidBody myRigidBody;
    Bounds myBounds;
    Collider myCollider;
};

#endif /* Boundary_hpp */
