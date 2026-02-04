//
//  RigidBody.hpp
//  MakeEngine
//
//  Created by Make100Games on 04.02.26.
//

#ifndef RigidBody_hpp
#define RigidBody_hpp

#include <stdio.h>

// TODO: Currently the RigidBody is just a container that contains velocity information. The GameObjects are still
//  required to update the velocity themselves. In the future, this velocity should be set by some sort of physics
//  engine (should I ever write one) and only be able to be set manually by GameObjects if the RigidBody's isKinematic
//  property is set accordingly. Basically like it is in Unity. For now this is just a useful container for velocity
//  because that is where I would expect to find it.
struct RigidBody {
    float xVelocity;
    float yVelocity;
};

#endif /* RigidBody_hpp */
