#version 330 core

layout (location = 0) in vec3 aPos;
out vec4 col; 
out vec4 gl_Position;

void main()
{
   col = vec4(aPos.x * 0.5 + 0.5, aPos.y * 0.5 + 0.5, aPos.z * 0.5 + 0.5, 1.0);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
} 