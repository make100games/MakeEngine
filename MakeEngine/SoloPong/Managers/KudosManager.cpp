//
//  KudosManager.cpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#include "KudosManager.hpp"

KudosManager::KudosManager() {
    
}

KudosManager::~KudosManager() {
    
}

void KudosManager::setListener(KudosManagerListener *listener) {
    myListener = listener;
}

void KudosManager::earnKudos() {
    if(myListener != nullptr) {
        myListener -> onKudosEarned();
    }
}

void KudosManager::loseKudos() {
    if(myListener != nullptr) {
        myListener -> onKudosLost();
    }
}
