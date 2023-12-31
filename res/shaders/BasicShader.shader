#shader vertex 
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 transform;

void main()
{
	gl_Position = transform * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 colorTint;

void main()
{
   color = vec4(colorTint.x,colorTint.y,colorTint.z,colorTint.w);
};