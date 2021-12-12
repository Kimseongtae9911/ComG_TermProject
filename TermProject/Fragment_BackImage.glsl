#version 330 core

in vec2 texCoord;

out vec4 out_FragColor;

uniform sampler2D outTexture;

void main(void)
{
	out_FragColor = texture(outTexture, texCoord);
}