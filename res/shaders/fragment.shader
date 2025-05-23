#version 410 core

layout (location = 0) out vec4 FragColor;

// uniform vec4 u_Color;
uniform sampler2D u_Texture;

// in vec4 vColor;
in vec2 v_TexCoord;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
}
