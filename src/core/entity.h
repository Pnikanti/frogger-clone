#pragma once
#include <string>
#include <glm/glm.hpp>
#include <box2d/b2_body.h>
#include "graphics.h"
#include "input.h"
#include "physics.h"

class Entity {
public:
	Entity(InputComponent* inputComponent, PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution);
	~Entity();

	void Advance();
	void Draw();
	void ProcessInput();

	PhysicsComponent* GetPhysicsComponent();
	GraphicsComponent* GetGraphicsComponent();
	glm::vec2 GetSize();
	glm::vec2 GetPosition();
	float GetRotationDegrees();
	float GetRotationRadians();

	void SetAttributes(glm::vec2 position, glm::vec2 size, float rotation);
	void SetAttributes(glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution);

public:
	glm::vec3 Color;
	glm::vec2 Size;
	glm::vec2 Position;
	b2BodyType BodyType;
	float Density;
	float Friction;
	float Restitution;
	float Rotation;
private:
	InputComponent* input;
	PhysicsComponent* physics;
	GraphicsComponent* graphics;
};