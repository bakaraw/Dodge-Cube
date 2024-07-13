//
// Created by bacal on 7/9/2024.
//

#ifndef BOX_H
#define BOX_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Box {
public:
    glm::vec3 min;
    glm::vec3 max;

    Box(glm::vec3 min, glm::vec3 max): min(min), max(max){}

    bool collidesWith(const Box &otherBox) const {
        return
        min.x <= otherBox.max.x && max.x >= otherBox.min.x &&
            min.y <= otherBox.max.y && max.y >= otherBox.min.y &&
                min.z <= otherBox.max.z && max.z >= otherBox.min.z;
    }
};



#endif //BOX_H
