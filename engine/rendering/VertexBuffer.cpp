#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_VBO);
}

VertexBuffer::~VertexBuffer()
{
    Shutdown();
}

VertexBuffer VertexBuffer::Create()
{
    return VertexBuffer{};
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}
void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const int size, const void* data) const
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Shutdown() const
{
    glDeleteBuffers(1, &m_VBO);
}
