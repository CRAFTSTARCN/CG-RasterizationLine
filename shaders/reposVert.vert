#version 330 core

layout (location = 0) in vec3 aPos;
out vec4 col;
out vec4 gl_Position;

uniform mat4 translate;

void main()
{
   vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   pos = translate * pos;
   col = vec4(pos.x * 0.5 + 0.5, pos.y * 0.5 + 0.5, pos.z * 0.5 + 0.5, 1.0);
   gl_Position = pos;
} 