#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
//layout(location = 2) in vec3 vNormal;

out vec2 texCoord;

uniform mat4 modelTransform = mat4(1.f);
uniform mat4 viewTransform = mat4(1.f);
uniform mat4 projectionTransform = mat4(1.f);

void main(void)
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPosition, 1.0) ;
	texCoord = vTexCoord;
}