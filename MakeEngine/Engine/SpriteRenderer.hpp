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

class SpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    void render(const std::vector<Sprite*>& sprites, const glm::mat4& projection);
    
private:
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned int quadEBO = 0;
    
    void initShaders();
    void initQuad();
};

#endif /* SpriteRenderer_hpp */
