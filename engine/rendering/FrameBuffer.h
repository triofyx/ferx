#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include "Texture.h"

class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void RescaleFrameBuffer(int width, int height) const;
    void AttachTexture(int width, int height);
    void Bind() const;
    static void Unbind();

    Texture* GetFrameTexture() const;

private:
    unsigned int m_FBO{}, m_RBO{};
    std::unique_ptr<Texture> m_Texture;
};