#pragma once
#include "Shader.h"
#include "Spheres.h"
#include "CollideSpheres.h"
#include "Particle.h"
#include <vector>
#include <glm/glm.hpp>

class Box {
public:
    Box(const glm::vec3& position, const glm::vec3& size);

    void addSphere(const Spheres& sphere); 
    void makeParticles(int count, const glm::vec3& origin);

    void update(float deltaTime);
    void render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

    glm::vec3 getPosition() const { return mPosition; }
    glm::vec3 getSize() const { return mSize; }

private:
    glm::vec3 mPosition; // Position of the box
    glm::vec3 mSize;     // Dimensions of the box (width, height, depth)
    
    CollideSpheres mCollideSpheres;
    Particle mParticle;

    unsigned int mVAO, mVBO, mEBO; 
    void makingBox();  
    
};
