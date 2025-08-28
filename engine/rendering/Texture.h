#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <memory>
#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    void Init();
    void Bind() const;
    void GenerateFromImage(const std::string& path);

    unsigned int GetID() const;
    unsigned char** GetTexture() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetNrChannels() const;

    static void ToImage(int width, int height, unsigned char** data);
    static void GenerateMipmaps();

private:
    unsigned int m_Texture{};
    std::unique_ptr<unsigned char*> m_Data{};
    int m_Width{}, m_Height{}, m_NrChannels{};
};