#include <glew/glew.h>
#include "buffer.h"
#include "log.h"

VertexBuffer::VertexBuffer()
{
	LOGGER_INFO("VB constructor called!");
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	LOGGER_INFO("VB constructor!");
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	LOGGER_INFO("VB destructor!");
	glDeleteBuffers(1, &m_RendererId);
}

void VertexBuffer::Set(const void* data, unsigned int size)
{
	LOGGER_INFO("VB set called!");
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer() : m_Count(0)
{
	LOGGER_INFO("IB constructor called!");
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	LOGGER_INFO("IB constructor");
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	LOGGER_INFO("IB destructor!");
	glDeleteBuffers(1, &m_RendererId);
}

void IndexBuffer::Set(const unsigned int* data, unsigned int count)
{
	LOGGER_INFO("IB set called!");
	m_Count = count;
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}