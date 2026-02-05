//
//  Kudos.hpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#ifndef Kudos_hpp
#define Kudos_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "GameObject.hpp"
#include "Renderable.hpp"
#include <memory>
#include "Transform.hpp"
#include "Bounds.hpp"
#include "Collider.hpp"
#include "KeyInput.hpp"
#include "RigidBody.hpp"
#include "Vec2.hpp"

/**
 You receive Kudos each time you successfully knock the ball back to the other side. Each time the ball hits the top or bottom of the window, you lose kudos.
 You lose the game when you run out of kudos.
 */
class Kudos : public GameObject {
public:
    Kudos(float positionX, float positionY, int key);
    ~Kudos();
    
    void initialize() override;
    
    void update(float deltaTime) override;
    
    const std::unique_ptr<Renderable>& renderable() const override;
    
    Transform transform() override;
    
    RigidBody rigidBody() override;
    
    void onCanvasBoundsChanged(Bounds bounds) override;
    
    Collider collider() override;
    
    void onCollision(Collider other) override;
    
    void onKeyInput(KeyInput input) override;
    
    int getKey();
    
private:
    float positionX;
    float positionY;
    int key;
    std::unique_ptr<Renderable> myRenderable;
    Transform myTransform;
    RigidBody myRigidBody;
    Bounds myBounds;
    Collider myCollider;
};

#endif /* Kudos_hpp */
