#version 330 core

layout (location = 0) in vec3 aPos;
out vec4 col; 
out vec4 gl_Position;

uniform mat4 MATRIX_MVP;

void main()
{
   gl_Position = MATRIX_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0) ;
   col = vec4(gl_Position.x * 0.5 + 0.5, gl_Position.y * 0.5 + 0.5, gl_Position.z * 0.5 + 0.5, 1.0);
} 