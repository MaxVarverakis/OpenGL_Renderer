#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aOriginLoc;

uniform mat4 u_MVP;

out vec4 v_Color;

void main()
{
    gl_Position = u_MVP * vec4(aPos + aOriginLoc, 0.0, 1.0);
    v_Color = aColor;
}
