//
//  Scene.cpp
//  MakeEngine
//
//  Created by Make100Games on 08.02.26.
//

#include <stdio.h>
#include "Scene.hpp"

void Scene::initialize() {
    onStart();
    processPendingAdditions();
}

std::vector<std::unique_ptr<GameObject>>& Scene::gameObjects() {
    return myGameObjects;
}

void Scene::update(float deltaTime) {
    for(auto& gameObject : myGameObjects) {
        gameObject -> update(deltaTime);
    }
    processPendingRemovals();
    processPendingAdditions();
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

void Scene::processPendingAdditions() {
    for(auto& gameObject : pendingAdd) {
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
