#version 330 core
//uniform float time;
uniform mat4 P, transformation3,keygrej;

layout (location =0) in vec3 Position;
layout (location =1) in vec3 Normal;
layout (location =2) in vec2 TexCoord;
out vec3 interpolatedNormal;
out vec2 st;
//out vec3 lightDirection;
out vec3 transformedNormal;
//mat4 Tn;

void main() {
    gl_Position = P*transformation3*vec4 (Position , 0.5) ; // Special , required output

    vec3 transformedNormal = Normal ;
    interpolatedNormal = normalize(transformedNormal);
    st = TexCoord ; // Will also be interpolated across the triangle
}
