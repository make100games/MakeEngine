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

class KudosManager {
public:
    KudosManager();
    ~KudosManager();
    
    void setListener(KudosManagerListener* listener);
    
    void earnKudos();
    
    void loseKudos();
    
private:
    KudosManagerListener* myListener;
};

#endif /* KudosManager_hpp */
