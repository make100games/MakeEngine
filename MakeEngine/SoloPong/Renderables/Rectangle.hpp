//
//  Rectangle.hpp
//  MakeEngine
//
//  Created by Make100Games on 01.02.26.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include "Renderable.hpp"
#include <string>
#include <vector>
#include "Vec4.hpp"

class Rectangle : public Renderable {
public:
    Rectangle(std::vector<float> vertices, Vec4 color, std::string renderTag);
    ~Rectangle();
    
    const std::vector<float>* vertices() const override;
    
    const Vec4& color() const override;
    
    std::string renderTag() override;
    
private:
    std::vector<float> myVertices;
    Vec4 myColor;
    std::string myRenderTag;
};

#endif /* Rectangle_hpp */
