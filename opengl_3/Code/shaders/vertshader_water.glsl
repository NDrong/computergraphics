#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec3 vertNormal_in;
layout (location = 3) in vec2 uvCoord_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat3 normalTransform;

// Specify the output of the vertex stage
out vec3 vertNormal;
out vec2 uvCoord;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    vec3 vertCoordinates = vertCoordinates_in;
    uvCoord = uvCoord_in;
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vertCoordinates, 1.0);
    vertNormal = (normalTransform * vertNormal_in + 1) / 2;
}
