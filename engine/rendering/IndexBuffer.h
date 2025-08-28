#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void Bind() const;
    static void Unbind();
    void SetData(int size, const void* data) const;

private:
    unsigned int m_IBO{};
};