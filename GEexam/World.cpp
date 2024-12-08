#include "World.h"

World::World() : mBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 10.0f, 50.0f)) // Box at position (0, 0, 0) with size (10, 10, 10)
{
}

void World::update(float deltaTime) {
    mBox.update(deltaTime); 
}

void World::render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    mBox.render(shader, view, projection); 
}

void World::addSphereToBox(const Spheres& sphere) {
    mBox.addSphere(sphere); 
}