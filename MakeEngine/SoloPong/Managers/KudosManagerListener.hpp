//
//  KudosManagerListener.hpp
//  MakeEngine
//
//  Created by Make100Games on 05.02.26.
//

#ifndef KudosManagerListener_hpp
#define KudosManagerListener_hpp

#include <stdio.h>
#include "Kudos.hpp"
#include <memory>

class KudosManagerListener {
public:
    virtual void onKudosEarned() = 0;
    
    virtual void onKudosLost() = 0;
};

#endif /* KudosManagerListener_hpp */
