//
//  VictoryScreen.hpp
//  MakeEngine
//
//  Created by Make100Games on 09.02.26.
//

#ifndef GameOverScreen_hpp
#define GameOverScreen_hpp

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
#include "GameManager.hpp"

class GameOverScreen : public GameObject {
public:
    GameOverScreen(Vec3 color, GameManager* gameManager);
    ~GameOverScreen();
    
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
    Vec3 myColor;
    std::unique_ptr<Renderable> myRenderable;
    Transform myTransform;
    RigidBody myRigidBody;
    Bounds myBounds;
    Collider myCollider;
    GameManager* myGameManager;
};

#endif /* VictoryScreen_hpp */
