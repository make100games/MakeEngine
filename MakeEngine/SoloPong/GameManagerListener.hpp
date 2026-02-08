//
//  GameManagerListener.hpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#ifndef GameManagerListener_hpp
#define GameManagerListener_hpp

#include <stdio.h>

class GameManagerListener {
public:
    virtual void onGameLost() = 0;
    
    virtual void onGameWon() = 0;
};

#endif /* GameManagerListener_hpp */
