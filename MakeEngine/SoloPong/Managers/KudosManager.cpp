//
//  KudosManager.cpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#include "KudosManager.hpp"

KudosManager::KudosManager() {
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
        myListener -> onStartedNewLevel(currentKudosColor, 3);
    }
}

void KudosManager::earnKudos() {
    numberOfKudos++;
    if(numberOfKudos >= MaxKudosPerLevel) {
        numberOfKudos = 1;
        currentLevel++;
        if(currentLevel >= levelColors.size()) {
            // Player wins!
            // TODO notify GameManager!
        } else {
            currentKudosColor = levelColors[currentLevel];
            // TODO notify KudosManagerListener that we reached new level and pass new color
            if(myListener != nullptr) {
                myListener -> onStartedNewLevel(currentKudosColor, 10);
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
    if(numberOfKudos <= 0) {
        // Player lost!
        // TODO notify GameManager!
    } else {
        if(myListener != nullptr) {
            myListener -> onKudosLost();
        }
    }
}
