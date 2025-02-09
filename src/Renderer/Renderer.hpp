#pragma once

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include "../VertexArray/VertexArray.hpp"
#include "../IndexBuffer/IndexBuffer.hpp"
#include "../Shader/Shader.hpp"

#define ASSERT(x) if (!(x)) SDL_TriggerBreakpoint();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

void printShaderInfoLog(unsigned int shader);

void printProgramInfoLog(unsigned int program);

class Renderer
{
public:
    void draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const;
    
    void clear() const;
};
