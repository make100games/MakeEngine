//
//  Hud.hpp
//  MakeEngine
//
//  Created by Make100Games on 07.02.26.
//

#ifndef Hud_hpp
#define Hud_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Renderable.hpp"
#include <memory>
#include "Transform.hpp"
#include "Bounds.hpp"
#include "Collider.hpp"
#include "KeyInput.hpp"
#include "RigidBody.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include <vector>

class Hud : public GameObject {
public:
    Hud();
    ~Hud();
    
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

#endif /* Hud_hpp */
