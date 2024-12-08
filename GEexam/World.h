#pragma once
#include "Box.h"
#include "Shader.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include <glm/glm.hpp>


class World {
public:
    World();

    // Add a new sphere entity to the world
    uint32_t createSphereEntity(const glm::vec3& position, const glm::vec3& velocity, float radius, glm::vec3 color);

    // Add a box to the world
    void addBox(const glm::vec3& position, const glm::vec3& size);

    // Update and render the world
    void update(float deltaTime);
    void render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

private:
    std::vector<Box> mBox;               // Boxes in the world
    EntityManager mEntityManager;        // Manages entities
    ComponentArrays mComponents;        // Stores components for all entities
    WorldBoundsComponent mWorldBounds;  // Global world bounds
};


//class World {
//public:
//    World();
//    void init();
//    void update(float deltaTime);
//    void render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);
//    void addSphereToBox(const Spheres& sphere);
//    uint32_t createEntity();
//    void destroyEntity(uint32_t entityID);
//
//private:
//    Box mBox; 
//
//    //ECS
//    EntityManager mEntityManager;
//    ComponentArrays mComponents;
//    WorldBoundsComponent mWorldBounds;
//    
//};
