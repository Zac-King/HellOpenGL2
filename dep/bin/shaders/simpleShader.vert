#version 330

layout(location = 0)in vec4 position;
layout(location = 1)in vec4 colour;
layout(location = 2)in vec2 vertexUV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec4 vertColour;
out vec2 UV;

void main()
{
	vertColour = colour;
    UV = vertexUV;

	gl_Position = Projection * View * Model * position;
}