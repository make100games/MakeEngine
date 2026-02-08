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
    requestAdd(std::make_unique<Hud>());
    // Add paddle and ball
    requestAdd(std::make_unique<Paddle>());
    requestAdd(std::make_unique<Ball>(myKudosManager.get()));
    
    // By starting the game, the first level is loaded which causes the first Kudos to be added.
    // Make sure we add the Kudos last so that we can also reasily remove them by just removing the last item
    myKudosManager -> startGame();
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
    myKudos.push_back(kudos.get());
    requestAdd(std::move(kudos));
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
    auto& lastKudos = myKudos[myKudos.size() - 1];
    float endOfLastKudos = lastKudos -> getPositionX() + Kudos::Size;
    float newKudosX = endOfLastKudos + spaceBetweenKudos;
    std::unique_ptr<Kudos> kudos = std::make_unique<Kudos>(newKudosX, kudosTop, currentKudosColor);
    kudos -> initialize();
    myKudos.push_back(kudos.get());
    requestAdd(std::move(kudos));
    this -> sceneListener -> onGameObjectsInSceneHaveChanged();
    
    std::cout << "Added new kudos at position x: " << newKudosX << ", y: " << kudosTop << "\n";
}

void Level1::onKudosLost() {
    std::cout << "Kudos lost!\n";
    // make sure to remove the raw pointer (observer) first!
    myKudos.pop_back();
    
    // remove owner second!
    requestRemoveMostRecent();
    
    this -> sceneListener -> onGameObjectsInSceneHaveChanged();
}
