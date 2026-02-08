//
//  GameManager.hpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include "GameManagerListener.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();
    
    void startGame();
    bool gameStarted();
    
    void loseGame();
    void winGame();
    
    void setListener(GameManagerListener* listener);
    
private:
    bool myGameStarted;
    GameManagerListener* myListener;
};

#endif /* GameManager_hpp */
