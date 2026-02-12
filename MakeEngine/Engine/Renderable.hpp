//
//  Renderable.hpp
//  Breakout
//
//  Created by Chris Braunschweiler on 03.05.25.
//

#ifndef Renderable_hpp
#define Renderable_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Vec4.hpp"
#include "Texture.hpp"

// Note: Right now the Renderable interface is implemented by simple shape Renderables such as Rectangles that just provide vertices and a color and Sprite which provide a Texture and a color. This is clunky use of OOP and polymorphism. Instead, we should think about having the Renderable draw itself so the Renderer can just call renderable.draw and everything will render correctly. This would allow you to render sprites and shapes side by side. But that's something for the future. I don't want to refactor too much while building out the engine. Also not sure if the shape renderable will have much of a future yet...
class Renderable {
public:
    virtual ~Renderable() = default;
    
    /**
     A texture to be rendered. The texture is not owned by the Renderable but by the Renderer.
     */
    Texture* texture = nullptr;
    
    /**
     The vertices that make up the geometry that is to be rendered. Returning a reference because we don't want to copy potentially
     large numbers of vertices each time this method is called.
     */
    virtual const std::vector<float>* vertices() const { return nullptr; }
    
    /**
     The color of the renderable.
     */
    virtual const Vec4& color() const = 0;
    
    /**
     A tag that indicates in what context this renderable should be rendered. Renderables with the same tag will be rendered together, translated
     together etc. As a rule of thumb: each renderable that can move independently of others should have its own renderTag.
     
     Renderables with the same tag which are applied to different GameObject instances will share the same Transform. What this means is, say you have a Brick GameObject with a Renderable of tag "Brick". Say you create multiple instances of these Brick GameObjects. Each instance has the same tag "Brick". If
     you change the transform of one of these instances, it will be applied to all instances during rendering. If you therefore want to place multiple Bricks at
     different locations, do so not by providing a value to the transform but by baking the position straight into the vertices of the Renderable. The transform can
     be used to translate all of the Bricks at once (e.g. to create a moving wall, for example).
     */
    virtual std::string renderTag() { return ""; }
};

#endif /* Renderable_hpp */
