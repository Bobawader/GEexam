#include "Box.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>



Box::Box(const glm::vec3& position, const glm::vec3& size)
    : mPosition(position), mSize(size), mCollideSpheres(position, size) {
    makingBox();
}

void Box::addSphere(const Spheres& sphere) {
    mCollideSpheres.addSphere(sphere);
}

void Box::makeParticles(int count, const glm::vec3& origin)
{
}


void Box::update(float deltaTime)
{
    mCollideSpheres.update(deltaTime);
}

void Box::makingBox() {
    float halfWidth = mSize.x / 2.0f;
    float halfHeight = mSize.y / 2.0f;
    float halfDepth = mSize.z / 2.0f;

    // Define vertices for the floor and walls
    float vertices[] = {
        // Floor (y = 0)
        -halfWidth, 0.0f, -halfDepth,  0.0f, 1.0f, 0.0f, // Bottom-left
         halfWidth, 0.0f, -halfDepth,  0.0f, 1.0f, 0.0f, // Bottom-right
         halfWidth, 0.0f,  halfDepth,  0.0f, 1.0f, 0.0f, // Top-right
        -halfWidth, 0.0f,  halfDepth,  0.0f, 1.0f, 0.0f, // Top-left

        // Back wall (z = -halfDepth)
        -halfWidth, 0.0f, -halfDepth,  0.0f, 0.0f, -1.0f, // Bottom-left
         halfWidth, 0.0f, -halfDepth,  0.0f, 0.0f, -1.0f, // Bottom-right
         halfWidth, mSize.y, -halfDepth,  0.0f, 0.0f, -1.0f, // Top-right
        -halfWidth, mSize.y, -halfDepth,  0.0f, 0.0f, -1.0f, // Top-left

        // Front wall (z = +halfDepth)
        -halfWidth, 0.0f,  halfDepth,  0.0f, 0.0f, 1.0f, // Bottom-left
         halfWidth, 0.0f,  halfDepth,  0.0f, 0.0f, 1.0f, // Bottom-right
         halfWidth, mSize.y,  halfDepth,  0.0f, 0.0f, 1.0f, // Top-right
        -halfWidth, mSize.y,  halfDepth,  0.0f, 0.0f, 1.0f, // Top-left

        // Left wall (x = -halfWidth)
        -halfWidth, 0.0f, -halfDepth,  -1.0f, 0.0f, 0.0f, // Bottom-front
        -halfWidth, 0.0f,  halfDepth,  -1.0f, 0.0f, 0.0f, // Bottom-back
        -halfWidth, mSize.y,  halfDepth,  -1.0f, 0.0f, 0.0f, // Top-back
        -halfWidth, mSize.y, -halfDepth,  -1.0f, 0.0f, 0.0f, // Top-front

        // Right wall (x = +halfWidth)
         halfWidth, 0.0f, -halfDepth,  1.0f, 0.0f, 0.0f, // Bottom-front
         halfWidth, 0.0f,  halfDepth,  1.0f, 0.0f, 0.0f, // Bottom-back
         halfWidth, mSize.y,  halfDepth,  1.0f, 0.0f, 0.0f, // Top-back
         halfWidth, mSize.y, -halfDepth,  1.0f, 0.0f, 0.0f, // Top-front
        };

    unsigned int indices[] = {
        // Floor
        0, 1, 2, 2, 3, 0,
        // Back wall
        4, 5, 6, 6, 7, 4,
        // Front wall
        8, 9, 10, 10, 11, 8,
        // Left wall
        12, 13, 14, 14, 15, 12,
        // Right wall
        16, 17, 18, 18, 19, 16,
    };


    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::cout << "Box Size: (" << mSize.x << ", " << mSize.y << ", " << mSize.z << ")" << std::endl;
    std::cout << "Half Width: " << halfWidth << ", Half Height: " << halfHeight << ", Half Depth: " << halfDepth << std::endl;

}

void Box::render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, mPosition);
    model = glm::scale(model, glm::vec3(1.0f));

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // Pass lighting and material properties
    shader.setVec3("lightPos", glm::vec3(0.0f, 20.0f, 0.0f)); // Example light position
    shader.setVec3("viewPos", glm::vec3(0.0f, 5.0f, 10.0f)); // Example camera position
    shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f)); // White light
    shader.setVec3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f)); // Red color
    shader.setBool("useFlatColor", false); // Use Phong shading

    // Render the box
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 6 * 5, GL_UNSIGNED_INT, 0); // 5 sides (floor + 4 walls)
    glBindVertexArray(0);

    // Render all spheres inside the box
    mCollideSpheres.render(shader, view, projection);
}
