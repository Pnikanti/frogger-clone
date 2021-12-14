#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& path, int flipTexture = 1);
	~Texture();
	
	void Bind(unsigned int slot = 0) const; // optional parameter
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererId, m_InternalFormat, m_DataFormat;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Channels;
};