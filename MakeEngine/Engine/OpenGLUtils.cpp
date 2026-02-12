//
//  OpenGLUtils.cpp
//  MakeEngine
//
//  Created by Make100Games on 12.02.26.
//

#include "OpenGLUtils.hpp"

void checkGLError(const char* operation) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after " << operation << ": " << err << std::endl;
    }
}
