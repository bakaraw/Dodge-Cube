#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/Shader.h"
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entities/Enemy.h"
#include "entities/Player.h"
#include <vector>
#include <random>

void initializeGLFW();
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void addEnemy(const glm::vec3& position);
void movePlayer();
float generateRandomFloat(float min, float max);

glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, -5.0f);
glm::vec3 cameraFront = glm::normalize(-cameraPos);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = 0.0f;
float lastY = 0.0f;

float enemyZ = 20.0f;

Player player(glm::vec3(0.0f, 0.0f, -2.0f));
std::vector<Enemy> enemies;

    int main() {
        initializeGLFW();
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        int monitor_width = mode->width;
        int monitor_height = mode->height;

        GLFWwindow *window = glfwCreateWindow(monitor_width, monitor_height, "Snek", NULL, NULL);
        if(window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Shader shader("assets/shaders/vShader.glsl", "assets/shaders/fShader.glsl");
            float vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

        float lightVertices[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        };

       //  float vertices[] = {
       //      // positions          // texture coords
       //      0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
       //      0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
       //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
       //     -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
       // };
       //  unsigned int indices[] = {
       //      0, 1, 3, // first triangle
       //      1, 2, 3  // second triangle
       //  };
        GLuint VBO, VAO, EBO;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glEnable(GL_DEPTH_TEST);
        addEnemy(glm::vec3(generateRandomFloat(-3, 3), 0.0f, enemyZ));

        float startTime = glfwGetTime();
        float spawnInterval = 7.0f;
        while(!glfwWindowShouldClose(window)) {
            processInput(window);
            glClearColor(15.0f/255.0f, 15.0f/255.0f, 15.0f/255.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindVertexArray(VAO);

            glm::mat4 view;
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(60.0f), (float)monitor_width/(float)monitor_height, 0.1f, 100.0f);

            shader.use();
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
            shader.setVec4("cubeColor", glm::vec4(210.0f/255.0f, 222.0f/255.0f, 50.0f/255.0f, 0.0f));

            player.update(shader);

            // every spawnRate seconds, an enemy will spawn
            if(glfwGetTime() - startTime >= spawnInterval) {
                addEnemy(glm::vec3(generateRandomFloat(-3, 3), 0.0f, enemyZ));
                startTime = glfwGetTime();

            }

            for (Enemy& enemy : enemies) {
                enemy.update(shader, deltaTime);
                if (player.boundingBox.collidesWith(enemy.boundingBox)) {
                    glfwSetWindowShouldClose(window, GL_TRUE);
                }
            }

            glfwPollEvents();
            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
    }

void initializeGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
}

void processInput(GLFWwindow *window) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            player.processInput(LEFT, deltaTime);


        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            player.processInput(RIGHT, deltaTime);

        // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //     pDirection = BACKWARD;
        //
        // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //     pDirection = FORWARD;
    }

void addEnemy(const glm::vec3 &position) {
    enemies.push_back(Enemy(position));
}

float generateRandomFloat(float min, float max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }


// void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
//         if (firstMouse) {
//             lastX = xpos;
//             lastY = ypos;
//             firstMouse = false;
//         }
//
//         float xOffset = xpos - lastX;
//         float yOffset = lastY - ypos;
//         lastX = xpos;
//         lastY = ypos;
//
//         const float sensitivity = 0.03f;
//         xOffset *= sensitivity;
//         yOffset *= sensitivity;
//
//         yaw += xOffset;
//         pitch += yOffset;
//
//         if (pitch > 89.0f) {
//             pitch = 89.0f;
//         }
//
//         if (pitch < -89.0f) {
//             pitch = -89.0f;
//         }
//
//         glm::vec3 direction;
//         direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//         direction.y = sin(glm::radians(pitch));
//         direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//         cameraFront = glm::normalize(direction);
//
//         std::cout << "yaw: " << yaw << ", pitch: " << pitch << std::endl;
//     }
