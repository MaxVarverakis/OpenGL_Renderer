#pragma once

#include "../Renderer/Renderer.hpp"

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_filepath;
    unsigned char* m_local_buffer;
    int m_width, m_height, m_BPP;

public:
    Texture(const std::string& path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
};
