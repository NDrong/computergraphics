#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec3 vertNormal_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat3 normalTransform;
uniform vec3 lightPosition;
uniform vec3 material;

// Specify the output of the vertex stage
out vec3 vertColor;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    vec3 vertCoordTrans = vec3(modelTransform * vec4(vertCoordinates_in, 1.0));
    vec3 lightPosTrans = vec3(modelTransform * vec4(lightPosition, 1.0));
    vec3 normal = normalize(normalTransform * vertNormal_in);

    vec3 L = normalize(lightPosTrans - vertCoordTrans);
    vec3 R = normalize(reflect(L, normal));

    float Is = max(0, pow(dot(-R, normalize(-vertCoordTrans)), 50));
    float Id = max(0, dot(normal, L));

    gl_Position = projectionTransform * modelTransform * vec4(vertCoordinates_in, 1.0);
    vertColor = vec3(0.1, 0.1, 0.1) + material[1] * Id * vertColor_in + material[2] * Is * vec3(1,1,1);
    //vertColor = vertColor_in;
}
