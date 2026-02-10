//
//  Texture.hpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>
#include <OpenGL/gl3.h>

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();
    
    // We delete the copy constructors as well as the copy aissignment operators so that we can't create copies of
    // the GPU resource. An OpenGL ID refers to a unique resource on the GPU.
    // If we had two copies of this ID and deleted them both, OpenGL would attempt to
    // delete the resource on the GPU that the ID refers to twice and that would lead to undefined behavior or
    // GPU crashes. We therefore get rid of the copy constructor here so that you can't make copies of the ID.
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    
    // We provide a move constructor and move assignmenet operator so that ownership of the texture can be
    // transferred between different owners.
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;
    
    unsigned int id() const { return textureID; }
    
    int width() const { return m_width; }
    int height() const { return m_height; }
    
private:
    unsigned int textureID = 0;
    int m_width = 0;
    int m_height = 0;
};

#endif /* Texture_hpp */
