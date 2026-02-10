//
//  AsteroidBlasterLevel1.cpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#include "AsteroidBlasterLevel1.hpp"
#include "Rocket.hpp"

AsteroidBlasterLevel1::AsteroidBlasterLevel1() {
    
}

AsteroidBlasterLevel1::~AsteroidBlasterLevel1() {
    
}

void AsteroidBlasterLevel1::onCanvasBoundsChanged() {
    
}

void AsteroidBlasterLevel1::onStart() {
    requestAdd(std::make_unique<Rocket>());
}

void AsteroidBlasterLevel1::addSceneListener(SceneListener* listener) {
    this -> sceneListener = listener;
}
