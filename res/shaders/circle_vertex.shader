#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aOriginLoc;
layout (location = 3) in float aRadius;
layout (location = 4) in float aInnerRadius;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_UV;
out float v_innerRadius2;

void main()
{
    gl_Position = u_MVP * vec4(aPos*aRadius + aOriginLoc, 0.0, 1.0);
    v_UV = aPos.xy;
    v_Color = aColor;
    v_innerRadius2 = aInnerRadius * aInnerRadius;
}
