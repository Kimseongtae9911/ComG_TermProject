#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;
layout(location = 3) in vec4 in_Color;

uniform mat4 modelTransform = mat4(1.f);
uniform mat4 viewTransform = mat4(1.f);
uniform mat4 projectionTransform = mat4(1.f);

out vec3 FragPos;
out vec3 Normal;
out vec4 out_Color;
out vec2 TexCoord;

void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);

	FragPos = vec3(modelTransform * vec4(vPos, 1.0));

	Normal = mat3(modelTransform) * vNormal;
	out_Color = in_Color;
	TexCoord = vTexCoord;
}