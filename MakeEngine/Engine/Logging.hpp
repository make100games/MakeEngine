//
//  Logging.hpp
//  MakeEngine
//
//  Created by Make100Games on 02.02.26.
//

#ifndef Logging_hpp
#define Logging_hpp

#include <stdio.h>
#include <ostream>
#include "KeyInput.hpp"

std::ostream& operator<<(std::ostream& os, KeyInteraction interaction);

std::ostream& operator<<(std::ostream& os, KeyCode keyCode);

std::ostream& operator<<(std::ostream& os, const KeyInput& input);

#endif /* Logging_hpp */
