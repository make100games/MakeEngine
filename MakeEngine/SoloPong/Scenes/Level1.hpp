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

class Level1 : public Scene, KudosManagerListener {
public:
    Level1();
    ~Level1();
    
    std::vector<std::unique_ptr<GameObject>>& gameObjects() override;
    
    void onCanvasBoundsChanged(Bounds bounds) override;
    
    void onStart() override;
    
    void update() override;
    
    void addSceneListener(SceneListener* listener) override;
    
    // Methods from KudosManagerListener
    void onStartedNewLevel(Vec3 color, int maxKudosInLevel) override;
    
    void onKudosEarned() override;
    
    void onKudosLost() override;
    
private:
    std::unique_ptr<KudosManager> myKudosManager;
    SceneListener* sceneListener;
    Bounds myCanvasBounds;
    std::vector<std::unique_ptr<GameObject>> myGameObjects;
    float hudTop;
    float kudosTop;
    float spaceBetweenKudos = 0;
    Vec3 currentKudosColor;
    
    float calculateSpaceBetween(int numberOfItems);
};

#endif /* Level1_hpp */
