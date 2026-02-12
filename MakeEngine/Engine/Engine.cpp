//
//  Engine.cpp
//  Breakout
//
//  Created by Chris Braunschweiler on 02.05.25.
//

#include "Engine.hpp"
#include <memory>
#include "Level1.hpp"
#include "OpenGlRenderer.hpp"
#include <iostream>
#include <utility>
#include <unordered_map>
#include "AsteroidBlasterLevel1.hpp"
#include "SpriteRendererAdapter.hpp"

Engine::Engine() : myCanvasBounds(Bounds { 0, 1000, 0, 700 }) {
    objectsInSceneHaveChanged = false;
    lastTime = std::chrono::high_resolution_clock::now();
    renderer = std::make_unique<SpriteRendererAdapter>();
    scenes = std::vector<std::unique_ptr<Scene>>();
}

Engine::~Engine() {
    scenes.clear();
}

void Engine::start() {
    renderer->initialize(myCanvasBounds);
    addScenes();
    
    if(!scenes.empty()) {
        currentScene = std::move(scenes[0]);
        std::cout << "Current scene obtained\n";
    } else {
        std::cout << "No scenes available\n";
    }
    if(currentScene) {
        currentScene -> addSceneListener(this);
        currentScene -> changeCanvasBounds(myCanvasBounds);
        currentScene -> initialize();
        std::unordered_map<std::string, std::vector<Renderable*>> renderBuckets;
        auto& gameObjects = currentScene -> gameObjects();
        for (auto& go : gameObjects) {
            go -> onCanvasBoundsChanged(myCanvasBounds);
            auto& renderable = go -> renderable();
            auto renderables = renderBuckets[renderable -> renderTag()];
            renderables.push_back(renderable.get());
            renderBuckets[renderable -> renderTag()] = renderables;
            go -> initialize();
            std::cout << "GameObject initialized\n";
        }
        renderer -> addToScene(renderBuckets);
        std::cout << "Current scene loaded\n";
    } else {
        std::cout << "No scene available!\n";
    }
}

void Engine::update() {
    float deltaTime = measureTimeSinceLastUpdate();
    
    if(currentScene) {
        currentScene -> update(deltaTime);
        auto& gameObjects = currentScene -> gameObjects();
        
        // TODO: We should refactor this so that the engine can just call something like renderer -> render(renderables) and all is taken care of polymporphically somehow. But something for another day...
        // Render all of the shape renderables
        std::unordered_map<std::string, std::pair<Transform, std::vector<Renderable*>>> renderObjects;
        for (auto& go : gameObjects) {
            auto transform = go -> transform();
            auto& renderable = go -> renderable();
            auto& renderObject = renderObjects[renderable -> renderTag()];
            renderObject.first = transform;
            renderObject.second.push_back(renderable.get());
            renderObjects[renderable -> renderTag()] = renderObject;
        }
        // There is probably a much more efficient way to do all this but I wanted to make sure that I had as few draw calls as possible in the renderer and to do that I batched Renderables that share the same tag into one draw call. Bridging this with the GameObject API (and avoiding having to expose too many of the implementation details of the Renderer to the GameObjects) I have to bring all this together here.
        renderer -> renderFrame(renderObjects);
        
        // Render all the sprites
        std::vector<std::pair<Renderable*, Transform>> sprites;
        for (auto& go : gameObjects) {
            auto transform = go -> transform();
            auto& renderable = go -> renderable();
            sprites.push_back(std::make_pair(renderable.get(), transform));
        }
        renderer -> render(sprites);
        
        checkForCollisions(gameObjects);
        currentScene -> processPendingRemovals();
        currentScene -> processPendingAdditions();
    }
    if(objectsInSceneHaveChanged) {
        reDrawObjectsInScene();
        objectsInSceneHaveChanged = false;
    }
}

float Engine::measureTimeSinceLastUpdate() {
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - lastTime;
    lastTime = now;
    return duration.count();
}

// FIXME: Optimize this to use broad phase and narrow phase collision detection. Right now we just have a nasty O(n squared) nested for-loop situation here
void Engine::checkForCollisions(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    // Do a to-pass collision detection and notification approach.
    // Pass 1: Collect objects that are colliding along with objects they are colliding with
    // Pass 2: Notify all colliding objects of their collision
    std::vector<std::pair<GameObject*, GameObject*>> collidingGos = std::vector<std::pair<GameObject*, GameObject*>>();
    for (auto& go : gameObjects) {
        bool alreadyCollided = false;
        for (auto& otherGo : gameObjects) {
            // We don't want to check collision with ourselves
            if (go != otherGo) {
                bool collisionOccurred = isColliding(go -> collider(), otherGo -> collider());
                if(collisionOccurred && !alreadyCollided) {
                    collidingGos.push_back(std::make_pair(go.get(), otherGo.get()));
                    alreadyCollided = true;
                }
            }
        }
    }
    
    for (auto go : collidingGos) {
        go.first -> onCollision(go.second -> collider());
    }
}

// Simple AABB (Axis-Algined Bounding Box) collision detection
bool Engine::isColliding(const Collider& a, const Collider& b) {
    return (
        a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y
    );
}

Bounds Engine::canvasBounds() {
    return myCanvasBounds;
}

void Engine::addScenes() {
    //scenes.push_back(std::make_unique<Level1>());
    scenes.push_back(std::make_unique<AsteroidBlasterLevel1>());
}

void Engine::onKeyInput(KeyInput input) {
    if(input.interaction == KeyInteraction::KeyUp) {
        delegateKeyInputToGameObjects(input);
    } else if(input.interaction == KeyInteraction::KeyDown) {
        delegateKeyInputToGameObjects(input);
    }
}

void Engine::delegateKeyInputToGameObjects(const KeyInput& input) {
    if(currentScene) {
        auto& gameObjects = currentScene -> gameObjects();
        for(auto& go : gameObjects) {
            go -> onKeyInput(input);
        }
    }
}

void Engine::onGameObjectsInSceneHaveChanged() {
    objectsInSceneHaveChanged = true;
}

void Engine::reDrawObjectsInScene() {
    // Here we basically fetch the GameObjects again (since they probably changed, otherwise why would the caller have called this method), and add them anew to the Renderer. This replaces what's already in the Renderer's scene
    // Note: This is a bit of copy/pasta from a snippet above. I could probably find a way to share this somehow but my hope is this won't change frequently. Famous last words, I know...
    std::unordered_map<std::string, std::vector<Renderable*>> renderBuckets;
    auto& gameObjects = currentScene -> gameObjects();
    for (auto& go : gameObjects) {
        auto& renderable = go -> renderable();
        auto renderables = renderBuckets[renderable -> renderTag()];
        renderables.push_back(renderable.get());
        renderBuckets[renderable -> renderTag()] = renderables;
    }
    renderer -> addToScene(renderBuckets);
}
