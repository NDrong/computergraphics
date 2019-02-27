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
uniform mat4 projectionTransform;
uniform mat3 normalTransform;
uniform vec3 lightPosition;
uniform vec3 material;

// Specify the output of the vertex stage
out vec3 vertColor;
out vec2 textureCoord;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation

    gl_Position = projectionTransform * modelTransform * vec4(vertCoordinates_in, 1.0);
    vertColor = vertColor_in;
    textureCoord = textureCoord_in;
}
