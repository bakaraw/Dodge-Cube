//
// Created by bacal on 7/6/2024.
//

#include "Shader.h"

enum ShaderType {
    FRAGMENT_SHADER,
    VERTEX_SHADER,
    SHADER_PROGRAM
};

void getCompileError(const GLuint shader, const ShaderType type);

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStr, fShaderStr;
        vShaderStr << vShaderFile.rdbuf();
        fShaderStr << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStr.str();
        fragmentCode = fShaderStr.str();

    } catch (std::ifstream::failure e) {
        std::cout << "Shaders::loading_unsuccessful" << std::endl;
        return;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    getCompileError(vertexShader, VERTEX_SHADER);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    getCompileError(fragmentShader, FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    getCompileError(ID, SHADER_PROGRAM);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setModel(const std::string &name, glm::mat4 model) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::setProjection(const std::string &name, glm::mat4 projection) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::setView(const std::string &name, glm::mat4 view) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(view));
}

void getCompileError(const GLuint shader, const ShaderType type) {
    int success;
    char infoLog[512];

    if (type == VERTEX_SHADER || type == FRAGMENT_SHADER) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR IN LOADING SHADERS:: " << infoLog << std::endl;
        }
    } else if (type == SHADER_PROGRAM) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR IN LINKING SHADERS:: " << infoLog << std::endl;
        }
    } else {
        std::cout << "THERE IS NO SUCH THING AS " << type << " TYPE" << std::endl;
    }
}
