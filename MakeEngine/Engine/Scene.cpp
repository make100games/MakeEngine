//
//  Scene.cpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#include <stdio.h>
#include "Scene.hpp"
#include <iostream>

void Scene::initialize() {
    onStart();
    processPendingAdditions();
}

void Scene::changeCanvasBounds(Bounds bounds) {
    myCanvasBounds = bounds;
    onCanvasBoundsChanged();
}

Bounds Scene::getCanvasBounds() {
    return myCanvasBounds;
}

std::vector<std::unique_ptr<GameObject>>& Scene::gameObjects() {
    return myGameObjects;
}

void Scene::update(float deltaTime) {
    for(auto& gameObject : myGameObjects) {
        gameObject -> update(deltaTime);
    }
}

void Scene::requestAdd(std::unique_ptr<GameObject> gameObject) {
    pendingAdd.push_back(std::move(gameObject));
}

void Scene::requestRemove(GameObject * gameObject) {
    pendingRemoval.push_back(gameObject);
}

void Scene::requestRemoveMostRecent() {
    pendingRemoval.push_back(gameObjects()[gameObjects().size() - 1].get());
}

// FIXME: We have the steps of calling onCanvasBoundsChanged and initialize on the GameObject in 2 places: Here and in the Engine class as well. That is ugly and
// very brittle. Need to unify and clean up this whole lifecycle handling. It's a mess right now.
void Scene::processPendingAdditions() {
    for(auto& gameObject : pendingAdd) {
        gameObject -> onCanvasBoundsChanged(myCanvasBounds);
        gameObject -> initialize();
        myGameObjects.push_back(std::move(gameObject));
    }
    pendingAdd.clear();
}

void Scene::processPendingRemovals() {
    for(GameObject* obj : pendingRemoval) {
        auto it = std::remove_if(
                                 gameObjects().begin(),
                                 gameObjects().end(),
                                 [obj](const std::unique_ptr<GameObject>& ptr) {
                                     return ptr.get() == obj;
                                 });
        myGameObjects.erase(it, gameObjects().end());
    }
    pendingRemoval.clear();
}
