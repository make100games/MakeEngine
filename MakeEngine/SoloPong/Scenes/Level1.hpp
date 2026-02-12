//
//  Level1.hpp
//  MakeEngine
//
//  Created by Make100Games on 01.02.26.
//

#ifndef Level1_hpp
#define Level1_hpp

#include <stdio.h>
#include "Scene.hpp"
#include <vector>
#include <memory>
#include "Bounds.hpp"
#include "KudosManagerListener.hpp"
#include "Kudos.hpp"
#include "KudosManager.hpp"
#include "Vec3.hpp"
#include "GameManager.hpp"
#include "GameManagerListener.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "GameOverScreen.hpp"
#include "Vec4.hpp"

class Level1 : public Scene, KudosManagerListener, GameManagerListener {
public:
    Level1();
    ~Level1();
    
    void onCanvasBoundsChanged() override;
    
    void onStart() override;
    
    void addSceneListener(SceneListener* listener) override;
    
    // Methods from KudosManagerListener
    void onStartedNewLevel(Vec4 color, int maxKudosInLevel) override;
    
    void onKudosEarned() override;
    
    void onKudosLost() override;
    
    // Methods from GameManagerListener
    virtual void onGameLost() override;
    
    virtual void onGameWon() override;
    
    virtual void onGameStarted() override;
    
private:
    std::unique_ptr<GameManager> myGameManager;
    std::unique_ptr<KudosManager> myKudosManager;
    SceneListener* sceneListener;
    GameOverScreen* myGameOverScreen;
    
    // This setup is a bit ugly and fragile. We have a list of GameObjects (managed by the Scene abstract class). This is the list that owns the GameObjects
    // But we also have a list of Kudos that are just raw pointers to Kudos objects. It is therefore important in
    // which order we add and remove items from these lists and that they remain in sync. Gross but fine for this game... lol
    std::vector<Kudos*> myKudos;
    float hudTop;
    float kudosTop;
    float spaceBetweenKudos = 0;
    Vec4 currentKudosColor;
    
    Ball* myBall;
    Paddle* myPaddle;
    
    float calculateSpaceBetween(int numberOfItems);
    void removeKudos();
};

#endif /* Level1_hpp */
