#pragma once

#include <string>
#include "shader.h"
#include "buffer.h"
#include "vertexarray.h"

class Entity;

struct Quad {
	float vertices[12] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};
};

struct TexturedQuad {
	float vertices[20] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};
};

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() = default;
	virtual void Draw(Entity& entity);
protected:
	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	VertexBufferLayout* layout;
	Shader* shader;
};

class QuadComponent : public GraphicsComponent
{
public:
	QuadComponent();
	~QuadComponent();
	void Draw(Entity& entity) override;
private:
	Quad quad;
};

//class TexturedQuadComponent : public GraphicsComponent
//{
//public:
//	TexturedQuadComponent(const char* textureFilePath);
//	~TexturedQuadComponent();
//	void Draw(Entity& entity) override;
//private:
//	TexturedQuad texturedQuad;
//	unsigned int vertexArray;
//	unsigned int vertexBuffer;
//	unsigned int elementBuffer;
//	unsigned int texture;
//};
