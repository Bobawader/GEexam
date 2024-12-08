#pragma once
#include "Box.h"
#include "Shader.h"
#include <glm/glm.hpp>

class World {
public:
    World();
    void update(float deltaTime);
    void render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);
    void addSphereToBox(const Spheres& sphere);
    

private:
    Box mBox; 
    
};
