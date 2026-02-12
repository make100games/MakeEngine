//
//  Rocket.hpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#ifndef Rocket_hpp
#define Rocket_hpp

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
#include "GameManager.hpp"
#include "Vec4.hpp"
#include "Texture.hpp"

class Rocket : public GameObject {
public:
    Rocket();
    ~Rocket();
  
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
    std::unique_ptr<Texture> spriteTexture;
    std::unique_ptr<Renderable> myRenderable;
    Transform myTransform;
    Bounds myCanvasBounds;
    Collider myCollider;
    RigidBody myRigidBody;
    
};

#endif /* Rocket_hpp */
