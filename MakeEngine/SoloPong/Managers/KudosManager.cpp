//
//  KudosManager.cpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#include "KudosManager.hpp"

KudosManager::KudosManager(GameManager* gameManager) {
    myGameManager = gameManager;
    levelColors = std::vector<Vec3> {
        Vec3 {1.0f, 0.0f, 0.0f},
        Vec3 {0.0f, 1.0f, 0.0f},
        Vec3 {0.0f, 0.0f, 1.0f},
        Vec3 {1.0f, 1.0f, 0.0f},
        Vec3 {0.0f, 1.0f, 1.0f},
        Vec3 {1.0f, 0.0f, 1.0f},
        Vec3 {0.5f, 1.0f, 0.0f},
        Vec3 {0.0f, 1.0f, 0.5f},
        Vec3 {0.0f, 0.5f, 1.0f},
        Vec3 {1.0f, 0.5f, 0.0f}
    };
}

KudosManager::~KudosManager() {
    
}

void KudosManager::setListener(KudosManagerListener *listener) {
    myListener = listener;
}

void KudosManager::startGame() {
    currentLevel = 0;
    currentKudosColor = levelColors[currentLevel];
    if(myListener != nullptr) {
        myListener -> onStartedNewLevel(currentKudosColor, MaxKudosPerLevel);
    }
}

void KudosManager::earnKudos() {
    numberOfKudos++;
    std::cout << "Earned Kudos. Current number: " << numberOfKudos << "\n";
    if(numberOfKudos > MaxKudosPerLevel) {
        numberOfKudos = 1;
        currentLevel++;
        if(currentLevel >= levelColors.size()) {
            // Player wins!
            if(myGameManager != nullptr) {
                myGameManager -> winGame();
            }
        } else {
            currentKudosColor = levelColors[currentLevel];
            // Notify KudosManagerListener that we reached new level and pass new color
            if(myListener != nullptr) {
                myListener -> onStartedNewLevel(currentKudosColor, MaxKudosPerLevel);
            }
        }
    } else {
        if(myListener != nullptr) {
            myListener -> onKudosEarned();
        }
    }
}

void KudosManager::loseKudos() {
    numberOfKudos--;
    std::cout << "Lost Kudos. Current number: " << numberOfKudos << "\n";
    if(numberOfKudos <= 0) {
        // Player lost!
        if(myGameManager != nullptr) {
            myGameManager -> loseGame();
        }
    } else {
        if(myListener != nullptr) {
            myListener -> onKudosLost();
        }
    }
}
