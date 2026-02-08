//
//  GameManager.cpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#include "GameManager.hpp"

GameManager::GameManager() {
    
}

GameManager::~GameManager() {
    
}

void GameManager::setListener(GameManagerListener *listener) {
    myListener = listener;
}

void GameManager::startGame() {
    myGameStarted = true;
}

bool GameManager::gameStarted() {
    return myGameStarted;
}

void GameManager::loseGame() {
    myGameStarted = false;
    if(myListener != nullptr) {
        myListener -> onGameLost();
    }
}

void GameManager::winGame() {
    myGameStarted = false;
    if(myListener != nullptr) {
        myListener -> onGameWon();
    }
}
