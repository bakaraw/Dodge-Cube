//
// Created by bacal on 7/8/2024.
//

#include "Enemy.h"
#include <random>

float randomX(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

void Enemy::update(Shader &shader, float deltaTime) {
    Position.z -= enemySpeed * deltaTime;
    boundingBox.min = Position;
    boundingBox.max = Position + glm::vec3(1.0f);

    if (Position.z < -5.0f) {
        Position = glm::vec3(randomX(-3, 3), 0.0f, enemyZ);
    }

    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);

    shader.setMat4("model", model);
    shader.setVec4("cubeColor", Color);

    glDrawArrays(GL_TRIANGLES, 0, 36);



}
