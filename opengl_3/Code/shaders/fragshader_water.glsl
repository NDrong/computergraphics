#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertNormal;
in vec2 uvCoord;
in vec3 lightPos;
in vec3 vertPos;
in vec3 color;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example
uniform vec3 lightPosition;
uniform vec3 material;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vec3 vn = normalize(vertNormal);

    vec3 viewPos = normalize(-vertPos); // eye is at 0,0,0
    vec3 lightDir = normalize(lightPos - vertPos);
    vec3 reflectDir = reflect(-lightDir, vn);

    float Id = max(0, dot(vn, lightDir));
    float Is = pow(max(dot(viewPos, reflectDir), 0), 32);
    float Ia = 0.5;
    float diffuse = 0.2 * Ia + 0.5 * Id;
    vec3 spec = Is * vec3(1, 1, 1);

    vec4 textureColor = vec4(color, 1);

    fColor = vec4(diffuse * textureColor.xyz + spec, textureColor.w);

//    fColor = vec4(0.5 * normalize(vertNormal) + vec3(0.5, 0.5, 0.5), 1.0);
}
