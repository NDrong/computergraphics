#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec3 vertNormal_in;
layout (location = 3) in vec2 textureCoord_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat3 normalTransform;
uniform vec3 lightPosition;
uniform vec3 material;

// Specify the output of the vertex stage
out vec3 vertColor;
out vec2 textureCoord;
out float lIntensityDiff;
out vec3 lSpecColor;

void main()
{
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vertCoordinates_in, 1.0);

    vec3 lightPos = vec3(modelTransform * vec4(lightPosition, 1.0));

    vec3 vertPos = vec3(modelTransform * vec4(vertCoordinates_in, 1.0));
    vec3 viewPos = normalize(-vertPos); // eye is at 0,0,0
    vec3 norm = normalize(normalTransform * vertNormal_in);
    vec3 lightDir = normalize(lightPos - vertPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float Id = max(0, dot(norm, lightDir));
    float Is = pow(max(dot(viewPos, reflectDir), 0), 32);
    float Ia = 0.5;
    float I = material[0] * Ia + material[1] * Id + material[2] * Is;

    textureCoord = textureCoord_in;
    lIntensityDiff = material[0] * Ia + material[1] * Id;
    lSpecColor = material[2] * Is * vec3(1, 1, 1);
    vertColor = vec3(I, I, I);
}
