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
uniform float waveAmplitudes[2];
uniform float waveFrequencies[2];
uniform float wavePhases[2];
uniform float time;
uniform vec3 lightPosition;

// Specify the output of the vertex stage
out vec3 vertNormal;
out vec2 uvCoord;
out vec3 lightPos;
out vec3 vertPos;
out vec3 color;

const float pi = 3.141593;

float waveHeight(int waveIdx, float uValue)
{
    // amplitude * sin(frequency + phase)
    return waveAmplitudes[waveIdx] * sin(uValue * waveFrequencies[waveIdx] + wavePhases[waveIdx] + time);
}

float waveDU(int waveIdx, float uValue)
{
    // amplitude * freqeuncy * cos(frequency + phase)
    return waveAmplitudes[waveIdx] * waveFrequencies[waveIdx] * cos(uValue * waveFrequencies[waveIdx] + wavePhases[waveIdx] + time);
}

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    vec3 vertCoordinates = vertCoordinates_in;
    uvCoord = uvCoord_in;
    // Generate a wave-like effect using a sum of sin function.
    float waveHeightSum = 0.0;
    float waveDUSum = 0.0;
    for (int idx = 0; idx < 2; idx++) {
        waveHeightSum += waveHeight(idx, uvCoord[0]);
        waveDUSum += waveDU(idx, uvCoord[0]);
    }

    vertCoordinates[2] = waveHeightSum;
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vertCoordinates, 1.0);
    vertNormal = normalize(vec3(-waveDUSum, 0, 1.0));

    lightPos = vec3(modelTransform * vec4(lightPosition, 1.0));
    vertPos = vec3(modelTransform * vec4(vertCoordinates, 1.0));

    color = mix(vec3(66.0/255.0, 134.0/255.0, 244.0/255.0), vec3(22.0/255.0, 68.0/255.0, 142.0/255.0), smoothstep(-waveAmplitudes[0] - waveAmplitudes[1], waveAmplitudes[0] + waveAmplitudes[1], waveHeightSum));
}
