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
#include "GameOverScreen.hpp"

Level1::Level1() {
    myGameManager = std::make_unique<GameManager>();
    myGameManager -> setListener(this);
    myKudosManager = std::make_unique<KudosManager>(myGameManager.get());
}

Level1::~Level1() {
    
}

void Level1::onCanvasBoundsChanged() {
    hudTop = getCanvasBounds().bottom - Constants::HudHeight;
}

void Level1::onStart() {
    myKudosManager -> setListener(this);
    // Add HUD
    requestAdd(std::make_unique<Hud>());
    // Add paddle and ball
    std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(myGameManager.get());
    myPaddle = paddle.get();
    requestAdd(std::move(paddle));
    std::unique_ptr<Ball> ball = std::make_unique<Ball>(myKudosManager.get(), myGameManager.get());
    myBall = ball.get();
    requestAdd(std::move(ball));
    
    // By starting the game, the first level is loaded which causes the first Kudos to be added.
    // Make sure we add the Kudos last so that we can also reasily remove them by just removing the last item
    myKudosManager -> startGame();
}

void Level1::addSceneListener(SceneListener *listener) {
    this -> sceneListener = listener;
}

void Level1::onStartedNewLevel(Vec3 color, int maxKudosInLevel) {
    std::cout << "Started new level\n";
    currentKudosColor = color;
    kudosTop = hudTop + (Constants::HudHeight / 2) - (Kudos::Size / 2);
    spaceBetweenKudos = calculateSpaceBetween(maxKudosInLevel);
    
    // Remove all kudos that are currently there
    for(auto kudos : myKudos) {
        requestRemove(kudos);
    }
    myKudos.clear();
    this -> sceneListener -> onGameObjectsInSceneHaveChanged();
}

float Level1::calculateSpaceBetween(int numberOfItems) {
    float canvasWidth = getCanvasBounds().right - getCanvasBounds().left;
    float leftOverSpace = canvasWidth - (numberOfItems * Kudos::Size);
    float numberOfSpaces = numberOfItems + 1;
    float spaceBetweenKudos = leftOverSpace / numberOfSpaces;
    return spaceBetweenKudos;
}

void Level1::onKudosEarned() {
    // We can assume the Kudos are always the last objects in the scene. A bit fragile but fine for now.
    if(myKudos.empty()) {
        std::unique_ptr<Kudos> kudos = std::make_unique<Kudos>(spaceBetweenKudos, kudosTop, currentKudosColor);
        myKudos.push_back(kudos.get());
        requestAdd(std::move(kudos));
    } else {
        auto& lastKudos = myKudos[myKudos.size() - 1];
        float endOfLastKudos = lastKudos -> getPositionX() + Kudos::Size;
        float newKudosX = endOfLastKudos + spaceBetweenKudos;
        std::unique_ptr<Kudos> kudos = std::make_unique<Kudos>(newKudosX, kudosTop, currentKudosColor);
        kudos -> initialize();
        myKudos.push_back(kudos.get());
        requestAdd(std::move(kudos));
    }
    this -> sceneListener -> onGameObjectsInSceneHaveChanged();
}

void Level1::onKudosLost() {
    // make sure to remove the raw pointer (observer) first!
    myKudos.pop_back();
    
    // remove owner second!
    requestRemoveMostRecent();
    
    this -> sceneListener -> onGameObjectsInSceneHaveChanged();
}

void Level1::onGameWon() {
    std::cout << "You beat the game!\n";
    std::unique_ptr<GameOverScreen> gameOverScreen = std::make_unique<GameOverScreen>(Vec3 {0.0f, 1.0f, 0.0}, myGameManager.get());
    myGameOverScreen = gameOverScreen.get();
    requestAdd(std::move(gameOverScreen));
    if(myBall != nullptr) {
        myBall -> endGame();
    }
    if(myPaddle != nullptr) {
        myPaddle -> endGame();
    }
    removeKudos();
}

void Level1::onGameLost() {
    // TODO: Show some red screen for a second or until player hits space bar or something
    if(myBall != nullptr) {
        myBall -> endGame();
    }
    if(myPaddle != nullptr) {
        myPaddle -> endGame();
    }
    removeKudos();
}

void Level1::onGameStarted() {
    if(myGameOverScreen != nullptr){
        requestRemove(myGameOverScreen);
        myGameOverScreen = nullptr;
    }
}

void Level1::removeKudos() {
    for(auto& kudos : myKudos) {
        requestRemove(kudos);
    }
    myKudos.clear();
}
