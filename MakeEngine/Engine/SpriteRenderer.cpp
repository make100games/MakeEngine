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
static const char* vertextShaderSource = R"(
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 uProjection;
uniform mat4 uModel;

out vec2 vUV;

void main()
{
    vUV = aUV;
    gl_Position = uProjection * uModel * vec4(aPos, 0.0, 1.0);
}
)";

static const char* fragmentShaderSource = R"(
#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
    FragColor = texture(uTexture, vUV) * uColor;
}
)";

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

void SpriteRenderer::render(const std::vector<Sprite *> &sprites, const glm::mat4& projection) {
    // TODO use the shaders. See OpenGLRenderer on how to do that
    
    glBindVertexArray(quadVAO);
    
    for(const Sprite* sprite : sprites) {
        if(!sprite || !sprite -> texture) continue;
        
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(sprite -> position.x, sprite -> position.y, 0.0f));
        
        model = glm::rotate(model, sprite -> rotation, glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(sprite -> scale.x, sprite -> scale.y, 1.0));
        
        // TODO pass values to shader
        // spriteShader.setMat4("uModel", model);
        // spriteShader.setVec4("uColor", sprite -> color);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite -> texture -> id());
        // spriteShader.setInt("uTexture", 0);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);
}
