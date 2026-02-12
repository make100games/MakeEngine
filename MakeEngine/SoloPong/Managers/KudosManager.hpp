//
//  KudosManager.hpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#ifndef KudosManager_hpp
#define KudosManager_hpp

#include <stdio.h>
#include "KudosManagerListener.hpp"
#include <vector>
#include "Vec4.hpp"
#include <iostream>
#include "GameManager.hpp"

class KudosManager {
public:
    KudosManager(GameManager* gameManager);
    ~KudosManager();
    
    void setListener(KudosManagerListener* listener);
    
    // Must be called after setting a KudosManagerListener!
    void startGame();
    
    void earnKudos();
    
    void loseKudos();
    
private:
    static const int MaxKudosPerLevel = 10;
    KudosManagerListener* myListener;
    int numberOfKudos = 0;
    int currentLevel = 0;
    std::vector<Vec4> levelColors;
    Vec4 currentKudosColor;
    GameManager* myGameManager;
    
    void resetGame();
};

#endif /* KudosManager_hpp */
