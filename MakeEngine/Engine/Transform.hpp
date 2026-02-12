//
//  Transform.hpp
//  Breakout
//
//  Created by Chris Braunschweiler on 05.05.25.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include <string>
#include "Vec3.hpp"

struct Transform {
    Vec3 position { 0.0f, 0.0f, 0.0f };
    Vec3 rotation { 0.0f, 0.0f, 0.0f };
    Vec3 scale { 1.0f, 1.0f, 1.0f };
    std::string renderTag;
};

#endif /* Transform_hpp */
