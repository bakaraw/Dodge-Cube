//
// Created by bacal on 7/8/2024.
//

#include "Enemy.h"

void Enemy::update(Shader &shader, float deltaTime) {

    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    shader.setMat4("model", model);
    shader.setVec4("cubeColor", Color);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    Position.z -= enemySpeed * deltaTime;
    std::cout << "enemyz: " << Position.z << std::endl;
}
