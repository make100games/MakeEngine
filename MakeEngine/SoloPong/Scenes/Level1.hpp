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
    
    void onCanvasBoundsChanged(Bounds bounds) override;
    
    void onStart() override;
    
    void addSceneListener(SceneListener* listener) override;
    
    // Methods from KudosManagerListener
    void onStartedNewLevel(Vec3 color, int maxKudosInLevel) override;
    
    void onKudosEarned() override;
    
    void onKudosLost() override;
    
private:
    std::unique_ptr<KudosManager> myKudosManager;
    SceneListener* sceneListener;
    Bounds myCanvasBounds;
    
    // This setup is a bit ugly and fragile. We have a list of GameObjects (managed by the Scene abstract class). This is the list that owns the GameObjects
    // But we also have a list of Kudos that are just raw pointers to Kudos objects. It is therefore important in
    // which order we add and remove items from these lists and that they remain in sync. Gross but fine for this game... lol
    std::vector<Kudos*> myKudos;
    float hudTop;
    float kudosTop;
    float spaceBetweenKudos = 0;
    Vec3 currentKudosColor;
    
    float calculateSpaceBetween(int numberOfItems);
};

#endif /* Level1_hpp */
