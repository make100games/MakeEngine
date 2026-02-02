//
//  Level1.cpp
//  MakeEngine
//
//  Created by Make100Games on 01.02.26.
//

#include "Level1.hpp"
#include <stdio.h>
#include <memory>
#include <vector>
#include "GameObject.hpp"
#include "Paddle.hpp"

Level1::Level1() {
    
}

Level1::~Level1() {
    
}

void Level1::onCanvasBoundsChanged(Bounds bounds) {
    myCanvasBounds = bounds;
}

void Level1::onStart() {
    // Add paddle and ball
    myGameObjects.push_back(std::make_unique<Paddle>());
}

void Level1::update() {
    
}

std::vector<std::unique_ptr<GameObject>>& Level1::gameObjects() {
    return myGameObjects;
}

void Level1::addSceneListener(SceneListener *listener) {
    this -> sceneListener = listener;
}
