//
//  AsteroidBlasterLevel1.hpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#ifndef AsteroidBlasterLevel1_hpp
#define AsteroidBlasterLevel1_hpp

#include <stdio.h>
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

class AsteroidBlasterLevel1 : public Scene {
public:
    AsteroidBlasterLevel1();
    ~AsteroidBlasterLevel1();
    
    void onCanvasBoundsChanged() override;
    
    void onStart() override;
    
    void addSceneListener(SceneListener* listener) override;
    
private:
    SceneListener* sceneListener;
};

#endif /* AsteroidBlasterLevel1_hpp */
