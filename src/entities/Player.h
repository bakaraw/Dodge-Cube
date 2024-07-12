//
// Created by bacal on 7/8/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/Shader.h"
#include "Collision/Box.h"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Player {
public:
    glm::vec3 Position;
    Box boundingBox;
    int playerDirection;
    float playerSpeed = 2.5f;
    float deltaTime = 0.0f;

    Player(glm::vec3 initialPosition)
    : Position(initialPosition), boundingBox(initialPosition, initialPosition + glm::vec3(1.0f)){}

    void processInput(Direction direction, float deltaTime);
    void update(Shader &shader);

};



#endif //PLAYER_H
