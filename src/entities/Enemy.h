//
// Created by bacal on 7/8/2024.
//

#ifndef ENEMY_H
#define ENEMY_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/Shader.h"
#include "Collision/Box.h"

class Enemy {
public:
    Box boundingBox;
    glm::vec3 Position;
    glm::vec3 Color = glm::vec3(1.0f, 7.0f/255.0f, 57.0f/255.0f);
    float enemySpeed = 5.0f;
    float deltaTime = 0.0f;
    float enemyZ;

    Enemy(glm::vec3 initialPosition): Position(initialPosition), boundingBox(initialPosition, initialPosition + glm::vec3(1.0f)), enemyZ(initialPosition.z){}
    void update(Shader &shader, float deltaTime);
};



#endif //ENEMY_H
