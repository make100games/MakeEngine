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
#include "Constants.hpp"
#include "Hud.hpp"

Level1::Level1() {
    myKudosManager = std::make_unique<KudosManager>();
}

Level1::~Level1() {
    
}

void Level1::onCanvasBoundsChanged(Bounds bounds) {
    myCanvasBounds = bounds;
    hudTop = myCanvasBounds.bottom - Constants::HudHeight;
}

void Level1::onStart() {
    myKudosManager -> setListener(this);
    
    // Add HUD
    myGameObjects.push_back(std::make_unique<Hud>());
    // Add paddle and ball
    myGameObjects.push_back(std::make_unique<Paddle>());
    myGameObjects.push_back(std::make_unique<Ball>(myKudosManager.get()));
    
    // By starting the game, the first level is loaded which causes the first Kudos to be added.
    // Make sure we add the Kudos last so that we can also reasily remove them by just removing the last item
    myKudosManager -> startGame();
}

void Level1::update() {
    
}

std::vector<std::unique_ptr<GameObject>>& Level1::gameObjects() {
    return myGameObjects;
}

void Level1::addSceneListener(SceneListener *listener) {
    this -> sceneListener = listener;
}

void Level1::onStartedNewLevel(Vec3 color, int maxKudosInLevel) {
    std::cout << "Started new level";
    currentKudosColor = color;
    kudosTop = hudTop + (Constants::HudHeight / 2) - (Kudos::Size / 2);
    spaceBetweenKudos = calculateSpaceBetween(maxKudosInLevel);
    std::unique_ptr<Kudos> kudos = std::make_unique<Kudos>(spaceBetweenKudos, kudosTop, currentKudosColor);
    myGameObjects.push_back(std::move(kudos));
}

float Level1::calculateSpaceBetween(int numberOfItems) {
    float canvasWidth = myCanvasBounds.right - myCanvasBounds.left;
    float leftOverSpace = canvasWidth - (numberOfItems * Kudos::Size);
    float numberOfSpaces = numberOfItems + 1;
    float spaceBetweenKudos = leftOverSpace / numberOfSpaces;
    return spaceBetweenKudos;
}

void Level1::onKudosEarned() {
    std::cout << "Kudos earned!\n";
    
    // We can assume the Kudos are always the last objects in the scene. A bit fragile but fine for now.
    auto& lastKudos = myGameObjects[myGameObjects.size() - 1];
    float endOfLastKudos = lastKudos -> transform().x + Kudos::Size;
    float newKudosX = endOfLastKudos + spaceBetweenKudos;
    std::unique_ptr<Kudos> kudos = std::make_unique<Kudos>(newKudosX, kudosTop, currentKudosColor);
    myGameObjects.push_back(std::move(kudos));
    this -> sceneListener -> onGameObjectsInSceneHaveChanged();
}

void Level1::onKudosLost() {
    std::cout << "Kudos lost!\n";
}
