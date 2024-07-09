//
// Created by bacal on 7/8/2024.
//

#ifndef ENEMY_H
#define ENEMY_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/Shader.h"


class Enemy {
public:
    glm::vec3 Position;
    glm::vec4 Color = glm::vec4(255.0f/255.0f, 7.0f/255.0f, 57.0f/255.0f, 0.0f);
    float enemySpeed = 5.0f;
    float deltaTime = 0.0f;

    Enemy(glm::vec3 initialPosition): Position(initialPosition){}
    void update(Shader &shader, float deltaTime);
};



#endif //ENEMY_H
