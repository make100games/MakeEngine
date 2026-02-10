//
//  Texture.cpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

// NB: ONLY CALL STB_IMAGE_IMPLEMENTATION HERE AND NOWHERE ELSE! OTHERWISE YOU WILL RUN INTO LINKING ISSUES!
#define STB_IMAGE_IMPLEMENTATION
#define GL_SILENCE_DEPRECATION
#include "Texture.hpp"
#include "stb_image.h"
#include <stdexcept>

Texture::Texture(const std::string& path) {
    stbi_set_flip_vertically_on_load(true);
    
    int channels;
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, STBI_rgb_alpha);
    
    if(!data) {
        throw std::runtime_error("Failed to load texture: " + path);
    }
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(
                 GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 m_width,
                 m_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 data
                 );
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
}

Texture::~Texture() {
    if(textureID) {
        glDeleteTextures(1, &textureID);
    }
}

Texture::Texture(Texture&& other) noexcept {
    textureID = other.textureID;
    m_width = other.m_width;
    m_height = other.m_height;
    
    other.textureID = 0;
}

Texture& Texture::operator=(Texture &&other) noexcept {
    if(this != &other) {
        glDeleteTextures(1, &textureID);
        
        textureID = other.textureID;
        m_width = other.m_width;
        m_height = other.m_height;
        
        other.textureID = 0;
    }
    return *this;
}
