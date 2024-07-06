#version 330 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool isTextureLoaded;
void main() {

        if (isTextureLoaded) {
                FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.0);

        } else {
                FragColor = vec4(210.0/255.0, 222.0/255.0, 50.0/255.0, 1.0);
        }

}