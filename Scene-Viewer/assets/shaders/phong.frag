#version 330 core
layout (std140) uniform Camera {
	uniform mat4 projection;
	uniform mat4 view;
	uniform vec3 cameraPos;
};

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

out vec4 outColor;

struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
};
uniform Material material;

vec3 lightDir = -normalize(vec3(0, -1, 0));
float lightAmbient = 0.3;
vec3 lightColor = vec3(1, 1, 1);
float specularStrength = 0.5;

void main() {
    vec3 diffuseColor = vec3(texture(material.diffuse0, texCoords));

    vec3 ambient = lightAmbient * diffuseColor;

    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = lightColor * diff * diffuseColor;
    
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    vec3 specular = specularStrength * spec * vec3(texture(material.specular0, texCoords));

    outColor = vec4(ambient + diffuse + specular, 1);
} 