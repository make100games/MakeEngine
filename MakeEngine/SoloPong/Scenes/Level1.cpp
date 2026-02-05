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
#include "Ball.hpp"

Level1::Level1() {
    myKudosManager = std::make_unique<KudosManager>();
}

Level1::~Level1() {
    
}

void Level1::onCanvasBoundsChanged(Bounds bounds) {
    myCanvasBounds = bounds;
}

void Level1::onStart() {
    myKudosManager -> setListener(this);
    
    // Add paddle and ball
    myGameObjects.push_back(std::make_unique<Paddle>());
    myGameObjects.push_back(std::make_unique<Ball>(myKudosManager.get()));
}

void Level1::update() {
    
}

std::vector<std::unique_ptr<GameObject>>& Level1::gameObjects() {
    return myGameObjects;
}

void Level1::addSceneListener(SceneListener *listener) {
    this -> sceneListener = listener;
}

void Level1::onKudosEarned() {
    std::cout << "Kudos earned!\n";
    //myGameObjects.push_back(std::move(kudos));
    //this -> sceneListener -> onGameObjectsInSceneHaveChanged();
}

void Level1::onKudosLost() {
    std::cout << "Kudos lost!\n";
}
