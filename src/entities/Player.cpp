//
// Created by bacal on 7/8/2024.
//

#include "Player.h"

void Player::processInput(Direction direction, float deltaTime) {
    float velocity = playerSpeed * deltaTime;

    if (direction == LEFT)
        Position.x += velocity;

    if (direction == RIGHT)
        Position.x -= velocity;

    if (Position.x > 3.0f)
        Position.x = 3.0f;

    if (Position.x <= -3.0f)
        Position.x = -3.0f;

    boundingBox.min = Position;
    boundingBox.max = Position + glm::vec3(1.0f);
}


void Player::update(Shader &shader) {
    shader.use();
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::translate(Model, Position);
    shader.setMat4("model", Model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


