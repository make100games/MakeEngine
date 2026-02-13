//
//  SpriteRenderer.cpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#define GL_SILENCE_DEPRECATION
#include "SpriteRenderer.hpp"
#include <OpenGL/gl3.h>
#include <iostream>
#include "OpenGLUtils.hpp"

// TODO Shader should be pulled out of this class and into a separate class
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

SpriteRenderer::~SpriteRenderer() {
    
}

void SpriteRenderer::initShaders() {
    // Compile the vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertextShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    // Check vertex shader compilation
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex Shader Compilation failed: \n" << infoLog << std::endl;
    }
    
    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    // Check fragment shader compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment Shader Compilation Failed:\n" << infoLog << std::endl;
    }
    
    // Link shaders into a program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // Check linking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Failed:\n" << infoLog << std::endl;
    }
    
    // Delete shaders as they are now linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
    
    // Tell OpenGL how the vertex array should be interpreted. ie: How to read out the position data nd how
    // to read out the UV data. Location 0 is position data.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    // Location 1 is UV data.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    glBindVertexArray(0);
}

void SpriteRenderer::initialize(Bounds canvasBounds) {
    glUseProgram(shaderProgram);
    GLint projectionLocation = glGetUniformLocation(shaderProgram, "uProjection");
    
    glm::mat4 projection = glm::ortho(canvasBounds.left, canvasBounds.right, canvasBounds.bottom, canvasBounds.top);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void SpriteRenderer::render(const std::vector<std::pair<Renderable*, Transform>>& sprites) {
    glUseProgram(shaderProgram);
    GLint modelLocation = glGetUniformLocation(shaderProgram, "uModel");
    GLint colorLocation = glGetUniformLocation(shaderProgram, "uColor");
    GLint textureLocation = glGetUniformLocation(shaderProgram, "uTexture");
    
    glBindVertexArray(quadVAO);
    
    for(const std::pair<Renderable*, Transform> &sprite : sprites) {
        if(!sprite.first || !sprite.first -> texture) continue;
        
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(sprite.second.position.x, sprite.second.position.y, 0.0f));
        model = glm::rotate(model, sprite.second.rotation.z, glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(sprite.second.scale.x, sprite.second.scale.y, 1.0));
        
        // Pass values to shader
        glUniformMatrix4fv(
            modelLocation,
            1,              // number of matrices
            GL_FALSE,       // transpose?
            glm::value_ptr(model)
        );
        glUniform4f(colorLocation, sprite.first -> color().r, sprite.first -> color().g, sprite.first -> color().b, sprite.first -> color().a);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite.first -> texture -> id());
        glUniform1i(textureLocation, 0);    // We sample from texture in texture slot 0 (since we activated GL_TEXTURE0 above)
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);
}
