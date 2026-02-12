//
//  SpriteRenderer.hpp
//  MakeEngine
//
//  Created by Make100Games on 10.02.26.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp
#include <stdio.h>
#include <vector>
#include "Sprite.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Bounds.hpp"
#include "Transform.hpp"
#include <memory>
#include <utility>
#include "Renderable.hpp"

class SpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    void initialize(Bounds canvasBounds);
    void render(const std::vector<std::pair<Renderable*, Transform>>& sprites);
    
private:
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned int quadEBO = 0;
    unsigned int shaderProgram;
    
    void initShaders();
    void initQuad();
    void setProjection();
};

#endif /* SpriteRenderer_hpp */
