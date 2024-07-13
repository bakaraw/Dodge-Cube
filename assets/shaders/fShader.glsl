#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool isTextureLoaded = false;
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 cubeColor = vec3(210.0/255.0, 222.0/255.0, 50.0/255.0);
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {

    float ambientStrenth = 0.1;
    float specularStrength = 0.9;

    vec3 ambient = ambientStrenth * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    if (isTextureLoaded) {

//        FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.0);

    } else {
        FragColor = vec4(cubeColor * (ambient + diffuse + specular), 1.0);
    }

}