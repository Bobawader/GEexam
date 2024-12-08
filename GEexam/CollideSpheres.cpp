#include "CollideSpheres.h"


CollideSpheres::CollideSpheres(const glm::vec3& boxPosition, const glm::vec3& boxSize)
    : mBoxPosition(boxPosition), mBoxSize(boxSize) {
    mWorldBounds.min = mBoxPosition - mBoxSize / 2.0f;
    mWorldBounds.max = mBoxPosition + mBoxSize / 2.0f;
}


uint32_t CollideSpheres::addSphere(const glm::vec3& position, const glm::vec3& velocity, float radius, const glm::vec3& color) {
    // Create entity
    uint32_t entity = mEntityManager.createEntity();

    // Ensure component storage can handle this entity
    if (entity >= mComponents.transforms.size()) {
        mComponents.resize(entity + 1);
    }

    // Assign components
    mComponents.transforms[entity] = { position, {}, glm::vec3(1.0f) };
    mComponents.physics[entity] = { velocity, 1.0f, radius };

    // Example: Initialize VAO for sphere rendering
    uint32_t vao = 0; // Replace with actual VAO initialization logic
    mComponents.renders[entity] = { vao, 0, 0, color };

    // Track entity locally
    mSphereEntities.push_back(entity);
    return entity;
}


void CollideSpheres::update(float deltaTime) {
    // Update physics for all entities in this box
    PhysicsSystem::update(mComponents, deltaTime);

    // Handle world bounds collisions
    CollisionSystem::updateWorldBoundCollisions(mComponents, mWorldBounds);

    // Handle inter-entity collisions
    CollisionSystem::updateInterEntityCollisions(mComponents);
}

void CollideSpheres::render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    // Render all entities in this box
    RenderSystem::render(mComponents, shader, view, projection);
}

void CollideSpheres::removeEntity(uint32_t entity) {
    mEntityManager.destroyEntity(entity);
    auto it = std::find(mSphereEntities.begin(), mSphereEntities.end(), entity);
    if (it != mSphereEntities.end()) {
        mSphereEntities.erase(it);
    }
    // Optionally clear component data (depends on how you're handling deleted entities)
}


//#include "CollideSpheres.h"
//
//CollideSpheres::CollideSpheres(const glm::vec3& boxPosition, const glm::vec3& boxSize)
//    : mBoxPosition(boxPosition), mBoxSize(boxSize) {
//}
//
//void CollideSpheres::addSphere(const Spheres& sphere) {
//    mSpheres.push_back(sphere);
//}
//
//
//void CollideSpheres::update(float deltaTime) {
//   
//    glm::vec3 boxMin = mBoxPosition - mBoxSize / 2.0f;
//    glm::vec3 boxMax = mBoxPosition + mBoxSize / 2.0f;
//
//
//
//    for (auto& sphere : mSpheres) {
//        sphere.update(deltaTime); // Update sphere position
//        checkWallCollision(sphere, boxMin, boxMax); // Check for wall collisions
//
//        const glm::vec3& pos = sphere.getPosition();
//    }
//    checkBallCollision();
//}
//
//void CollideSpheres::render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
//    // Render each sphere
//    for (auto& sphere : mSpheres) {
//        sphere.renderSphere(shader, view, projection);
//    }
//}
//
//void CollideSpheres::checkBallCollision() {
//    for (size_t i = 0; i < mSpheres.size(); ++i) {
//        for (size_t j = i + 1; j < mSpheres.size(); ++j) {
//            float collisionTime = detectCollision(mSpheres[i], mSpheres[j], 1.0f);
//            if (collisionTime < 1.0f) {
//                // Update positions to collision point
//                mSpheres[i].mPosition += mSpheres[i].mVelocity * collisionTime;
//                mSpheres[j].mPosition += mSpheres[j].mVelocity * collisionTime;
//
//                // Resolve collision
//                resolveCollision(mSpheres[i], mSpheres[j]);
//
//                // Use post-collision velocities for the remaining time
//                float remainingTime = 1.0f - collisionTime;
//                mSpheres[i].mPosition += mSpheres[i].mVelocity * remainingTime;
//                mSpheres[j].mPosition += mSpheres[j].mVelocity * remainingTime;
//            }
//        }
//    }
//}
//
//float CollideSpheres::detectCollision(const Spheres& s1, const Spheres& s2, float deltaTime) {
//    glm::vec3 A = s1.mPosition - s2.mPosition;
//    glm::vec3 B = s1.mVelocity - s2.mVelocity;
//    float A2 = glm::dot(A, A);
//    float B2 = glm::dot(B, B);
//    float AB = glm::dot(A, B);
//    float d = s1.mRadius + s2.mRadius;
//    float discriminant = AB * AB - B2 * (A2 - d * d);
//
//    if (discriminant < 0.0f) return 1.0f; // No collision
//    float t1 = (-AB - sqrt(discriminant)) / B2;
//    float t2 = (-AB + sqrt(discriminant)) / B2;
//
//    float t = (t1 >= 0.0f && t1 <= deltaTime) ? t1 : t2;
//    return (t >= 0.0f && t <= deltaTime) ? t : 1.0f; // Return collision time or 1.0f for no collision
//}
//
//void CollideSpheres::resolveCollision(Spheres& s1, Spheres& s2) {
//    glm::vec3 normal = glm::normalize(s1.mPosition - s2.mPosition);
//    float m1 = s1.mass, m2 = s2.mass;
//    glm::vec3 v1 = s1.mVelocity, v2 = s2.mVelocity;
//
//    float v1n = glm::dot(v1, normal);
//    float v2n = glm::dot(v2, normal);
//
//    float v1nPrime = (m1 - m2) / (m1 + m2) * v1n + (2 * m2) / (m1 + m2) * v2n;
//    float v2nPrime = (m2 - m1) / (m1 + m2) * v2n + (2 * m1) / (m1 + m2) * v1n;
//
//    glm::vec3 v1Prime = v1 + (v1nPrime - v1n) * normal;
//    glm::vec3 v2Prime = v2 + (v2nPrime - v2n) * normal;
//
//    s1.mVelocity = v1Prime;
//    s2.mVelocity = v2Prime;
//}
//
//void CollideSpheres::checkWallCollision(Spheres& sphere, const glm::vec3& boxMin, const glm::vec3& boxMax) {
//    glm::vec3 position = sphere.getPosition();
//    glm::vec3 velocity = sphere.getVelocity();
//    float radius = sphere.getRadius();
//
//    for (int i = 0; i < 3; ++i) { // Iterate over X, Y, Z axes
//        if (position[i] - radius < boxMin[i]) {
//            position[i] = boxMin[i] + radius; // Adjust position
//            velocity[i] = std::abs(velocity[i]); // Ensure velocity points inward
//        }
//        else if (position[i] + radius > boxMax[i]) {
//            position[i] = boxMax[i] - radius; // Adjust position
//            velocity[i] = -std::abs(velocity[i]); // Ensure velocity points inward
//        }
//    }
//
//    sphere.setVelocity(velocity); // Update sphere velocity
//}
//
//
