#include <iostream>
#include <math.h>
#include "VertexBuffer/VertexBuffer.hpp"
#include "IndexBuffer/IndexBuffer.hpp"
#include "VertexArray/VertexArray.hpp"
#include "Shader/Shader.hpp"
#include "VertexBufferLayout/VertexBufferLayout.hpp"
#include "Texture/Texture.hpp"
#include "Circle/Circle.hpp"

#include "Surface/Surface.hpp"

SDL_Window* window;
SDL_GLContext gl_context;

bool is_running;


float anglex { 0.0f };
float anglez { 0.0f };

int i_width { 960 };
int i_height { 540 };

float width { 960.0f };
float height { 540.0f };

void set_sdl_gl_attributes()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
}

// static float f(float x, float y)
// {
//     constexpr float epsilon { 0.0001f };
//     constexpr float k { 15.0 };
// 
//     if (abs(x) < epsilon && abs(y) < epsilon) { return 1.0f; }
//     else
//     {
//         float arg { static_cast<float>(sqrt(pow(x * k, 2) + pow(y * k, 2))) };
//         return sin(arg) / arg;
//     }
// }

void rotateWithArrowKeys(SDL_Event& event)
{
    constexpr float dtheta { 5.0f };

    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
        {
            anglez -= dtheta;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            anglez += dtheta;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
        {
            anglex -= dtheta;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
        {
            anglex += dtheta;
        }
    }
}

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout<<"SDL2 initialized successfully."<<std::endl;
        set_sdl_gl_attributes();
        
        // const GLubyte* version = glGetString(GL_VERSION);
        // std::cout << "OpenGL Version: " << version << std::endl;
        
        window = SDL_CreateWindow("Window!", 0.0f, 0.0f, i_width, i_height, SDL_WINDOW_OPENGL);
        gl_context = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1);

        if(glewInit() == GLEW_OK)
        {
            std::cout << "GLEW initialization successful" << std::endl;
        }
        else
        {
            std::cout << "GLEW initialization failed" << std::endl;
            return -1;
        }

        // Surface s(f, 60);

        // float vertices[]
        // {
        //     -0.5f, -0.5f, 1.0f, 0.2f, 0.2f, 1.0f, // 0.0f, 0.0f,
        //     0.5f, -0.5f, 1.0f, 0.2f, 0.2f, 1.0f, // 1.0f, 0.0f,
        //     0.5f, 0.5f, 1.0f, 0.2f, 0.2f, 1.0f, // 1.0f, 1.0f,
        //     -0.5f, 0.5f, 1.0f, 0.2f, 0.2f, 1.0f, // 0.0f, 1.0f,
        // };

        // unsigned int indices[]
        // {
        //     0, 1, 2,
        //     2, 3, 0,
        // };

        Circle circ1(glm::vec2(-100.0f, -100.0f), 100.0f, glm::vec4(1.0f, 0.1f, 0.3f, 1.0f), 0.1f);
        Circle circ2(glm::vec2(100.0f, 100.0f), 50.0f, glm::vec4(0.2f, 1.0f, 0.4f, 1.0f), 0.75f);
        Circle circ3(glm::vec2(-200.0f, 100.0f), 100.0f, glm::vec4(1.0f, 0.8f, 0.0f, 1.0f), 0.9f);
        Circle circ4(glm::vec2(-105.0f, 25.0f), 50.0f, glm::vec4(0.2f, 0.3f, 1.0f, 0.5f));

        Circles circles;
        circles.addVertices(circ1);
        circles.addVertices(circ2);
        circles.addVertices(circ3);
        circles.addVertices(circ4);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray VAO;

        // constructor automatically binds buffer
        // VertexBuffer VBO(vertices, 4 * 6 * sizeof(float));
        // VertexBuffer VBO(circ1.vertices().data(), static_cast<unsigned int>(circ1.vertices().size() * sizeof(float)));
        VertexBuffer VBO(circles.m_vertices.data(), static_cast<unsigned int>(circles.m_vertices.size() * sizeof(float)));
        
        VertexBufferLayout layout;
        for (unsigned int i = 0; i < 5; ++i)
        {
            layout.push<float>(Circle::layout_descriptor[i]);
        }
        // layout.push<float>(2); // xyz position
        // layout.push<float>(4); // RGBA color
        // layout.push<float>(2); // texture coordinates
        VAO.addBuffer(VBO, layout);

        // constructor automatically binds buffer
        // IndexBuffer IBO(indices, 6);
        // IndexBuffer IBO(Circle::indices, 3);
        IndexBuffer IBO(circles.m_indices.data(), static_cast<unsigned int>(circles.m_indices.size()));

        glm::mat4 proj { glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f) };
        glm::mat4 view { glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) };
        glm::mat4 model { glm::translate(glm::mat4(1.0f), glm::vec3(width/2, height/2, 0.0f)) };

        glm::mat4 MVP { proj * view * model };

        Shader shader("res/shaders", "circle_");
        shader.bind();
        shader.setUniformMatrix4fv("u_MVP", MVP);
        
        // Texture texture("res/textures/OpenGL_Logo.png");
        // texture.bind();
        // shader.setUniform1i("u_Texture", 0);

        VAO.unbind();
        VBO.unbind();
        IBO.unbind();
        shader.unbind();

        Renderer renderer;

        // Main loop
        SDL_Event event;
        is_running = true;

        while(is_running)
        {
            while(SDL_PollEvent(&event))
            {
                if( event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) )
                {
                    is_running = false;
                }
                
                // rotateWithArrowKeys(event);
            }

            // Render
            renderer.clear();
            
            // glm::mat4 modelMatrix(1.0f);

            // modelMatrix = glm::rotate(modelMatrix, glm::radians(anglex), glm::vec3(1.0f, 0.0f, 0.0f));
            // modelMatrix = glm::rotate(modelMatrix, glm::radians(anglez), glm::vec3(0.0f, 0.0f, 1.0f));

            // will be replaced with a material passed to the renderer
            shader.bind();
            // shader.setUniformMatrix4fv("modelMatrix", modelMatrix);

            // renderer.drawTriangles(VAO, IBO, shader);
            renderer.drawCircles(VAO, IBO, shader);

            SDL_GL_SwapWindow(window);
        }

        SDL_Quit();
    }
    else
    {
        std::cout<<"SDL2 initialization failed."<<std::endl;
        return -1;
    }

    return 0;
}
