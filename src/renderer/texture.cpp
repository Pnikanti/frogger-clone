#include <glew/glew.h>
#include <stb_image/stb_image.h>
#include "texture.h"
#include "log.h"

//Texture::Texture(const std::string& path)
//	: m_RendererId(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_Channels(0)
//{
//	// OpenGL expects texture pixels to start from bottom left.
//	// File formats typically start from top left.
//	// This is why flipping vertically is necessary.
//	stbi_set_flip_vertically_on_load(1);
//	glGenTextures(1, &m_RendererId);
//	glBindTexture(GL_TEXTURE_2D, m_RendererId);
//
//	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);
//	if (m_LocalBuffer)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		stbi_image_free(m_LocalBuffer);
//	}
//	else
//		LOGGER_ERROR("Failed to load texture: \"{0}\"", m_FilePath);
//
//	glBindTexture(GL_TEXTURE_2D, 0); // unbind texture
//}

Texture::Texture(const std::string& path, int flipTexture /* = 1*/) :
	m_RendererId(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_Channels(0), m_InternalFormat(0), m_DataFormat(0)
{
	// OpenGL expects textures to start from bottom left.
	// File formats typically start from top left.
	// This is why flipping vertically is *usually* necessary.

	stbi_set_flip_vertically_on_load(flipTexture);
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	if (!m_LocalBuffer)
		LOGGER_ERROR("Failed to load texture: \"{0}\"", m_FilePath);

	if (m_Channels == 4)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
	}
	else if (m_Channels == 3)
	{
		m_InternalFormat = GL_RGB8;
		m_DataFormat = GL_RGB;
	}

	glGenTextures(1, &m_RendererId);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);

	glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);

	stbi_image_free(m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererId);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}