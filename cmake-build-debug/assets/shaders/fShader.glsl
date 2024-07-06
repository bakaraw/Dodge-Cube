#version 330 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool isTextureLoaded;
void main() {
        FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.0);
//        FragColor = vec4(1.0, 0.0, 0.0, 1.0);

}