#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aNormal;

out vec3 color;
out vec3 Normal;
out vec3 crntPos;


uniform mat4 cam;
uniform mat4 model;



void main()
{
   gl_Position = cam * vec4(aPos, 1.0);
   color = aColor;
   Normal = aNormal;
   currentPos = vec3(model*vec4(aPos, 1.0f));
}