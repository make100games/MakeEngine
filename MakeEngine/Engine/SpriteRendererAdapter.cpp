//
//  SpriteRendererAdapter.cpp
//  MakeEngine
//
//  Created by Make100Games on 12.02.26.
//

#include "SpriteRendererAdapter.hpp"

SpriteRendererAdapter::SpriteRendererAdapter() {
    spriteRenderer = std::make_unique<SpriteRenderer>();
}

SpriteRendererAdapter::~SpriteRendererAdapter() {
    
}

void SpriteRendererAdapter::initialize(Bounds canvasBounds) {
    spriteRenderer -> initialize(canvasBounds);
}

void SpriteRendererAdapter::addToScene(const std::unordered_map<std::string, std::vector<Renderable *>> renderBuckets) {
    // No op. Not relevant for sprite renderer
}

void SpriteRendererAdapter::renderFrame(const std::unordered_map<std::string, std::pair<Transform, std::vector<Renderable *>>> renderObjects) {
    // No op. Not relevant for sprite renderer
}

void SpriteRendererAdapter::render(const std::vector<std::pair<Renderable *, Transform>> &sprites) {
    spriteRenderer -> render(sprites);
}
