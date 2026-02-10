//
//  SpriteRenderer.cpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#define GL_SILENCE_DEPRECATION
#include "SpriteRenderer.hpp"
#include <OpenGL/gl3.h>

// TODO shader stuff. For starters I can just declare the here and compile them...
SpriteRenderer::SpriteRenderer() {
    initShaders();
    initQuad();
}

void SpriteRenderer::initShaders() {
    // TODO
}

void SpriteRenderer::initQuad() {
    float vertices [] = {
        // pos              uv
        -0.5f,  -0.5f,      0.0f,   0.0f,
        0.5f,   -0.5f,      1.0f,   0.0f,
        0.5f,   0.5f,       1.0f,   1.0f,
        -0.5f,  0.5f,       0.0f,   1.0f
    };
    
    // Tells OpenGL how to interpret the vertices array above (ie: to use just 4 pairs of vertices to draw a quad
    // instead of having to use 6. Remember, the quad is made up of 2 triangles.
    unsigned int indices [] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);
    
    glBindVertexArray(quadVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    glBindVertexArray(0);
}

// TODO rendering the sprites. See "OpenGL sprite rendering" in Chat GPT :)
