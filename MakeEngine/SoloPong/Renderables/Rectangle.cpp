//
//  Rectangle.cpp
//  MakeEngine
//
//  Created by Make100Games on 01.02.26.
//

#include "Rectangle.hpp"

Rectangle::Rectangle(std::vector<float> vertices, Vec3 color, std::string renderTag): myVertices(std::move(vertices)), myColor(std::move(color)), myRenderTag(std::move(renderTag)) {
}

Rectangle::~Rectangle() {
    
}

const std::vector<float>& Rectangle::vertices() {
    return myVertices;
}

const Vec3& Rectangle::color() const {
    return myColor;
}

std::string Rectangle::renderTag() {
    return myRenderTag;
}
