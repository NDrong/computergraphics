#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertColor;
in vec2 textureCoord;
in float lIntensityDiff;
in vec3 lSpecColor;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example
uniform sampler2D textureSampler;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vec4 textureColor = texture(textureSampler, textureCoord);
    fColor = vec4(lIntensityDiff * textureColor.xyz + lSpecColor, textureColor.w);
}
