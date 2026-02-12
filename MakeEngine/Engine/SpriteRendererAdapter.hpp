//
//  SpriteRendererAdapter.hpp
//  MakeEngine
//
//  Created by Make100Games on 12.02.26.
//

#ifndef SpriteRendererAdapter_hpp
#define SpriteRendererAdapter_hpp

#include <stdio.h>
#include "Renderable.hpp"
#include <memory>
#include <vector>
#include "Transform.hpp"
#include "Bounds.hpp"
#include <utility>
#include "Sprite.hpp"
#include "Renderer.hpp"
#include "SpriteRenderer.hpp"

/**
 Adapts the Renderer interface to the SpriteRenderer.
 */
class SpriteRendererAdapter : public Renderer {
public:
    SpriteRendererAdapter();
    ~SpriteRendererAdapter();
    
    void initialize(Bounds canvasBounds) override;
    void addToScene(const std::unordered_map<std::string, std::vector<Renderable*>> renderBuckets) override;
    void renderFrame(const std::unordered_map<std::string, std::pair<Transform, std::vector<Renderable*>>> renderObjects) override;
    void render(const std::vector<std::pair<Sprite*, Transform>>& sprites) override;
private:
    std::unique_ptr<SpriteRenderer> spriteRenderer;
};

#endif /* SpriteRendererAdapter_hpp */
