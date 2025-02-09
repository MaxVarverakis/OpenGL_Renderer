#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 texCoord;

// out vec4 vColor;
out vec2 v_TexCoord;

// uniform mat4 modelMatrix;
uniform mat4 u_MVP;

void main()
{
    // gl_Position = modelMatrix * vec4(aPos, 1.0);
    gl_Position = u_MVP * vec4(aPos, 1.0);
    // vColor = aColor;
    v_TexCoord = texCoord;
}
