#include <glm/gtx/string_cast.hpp>
#include "entity.h"
#include "log.h"
#include "physics.h"
#include "input.h"
#include "graphics.h"
#include "instrumentor.h"

/* Entity handles rotation in degrees. When radians are used
(mainly in graphics and physics components) they are converted expliticly.
I.e. Entity takes rotation in degrees and passes it to needed components as radians.
*/

Entity::Entity(InputComponent* inputComponent, PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution) :
	input(inputComponent),
	graphics(graphicsComponent),
	physics(physicsComponent),
	Position(position),
	Size(size),
	Rotation(rotation),
	Color(color),
	BodyType(bodytype),
	Density(density),
	Friction(friction),
	Restitution(restitution)
{
	LOGGER_TRACE("Entity constructor called");
	physics->CreateFromEntity(*this);
}
Entity::~Entity()
{
	LOGGER_TRACE("Entity destructor called");
}

glm::vec2 Entity::GetSize() { return Size * 2.0f; }
glm::vec2 Entity::GetPosition() { return Position; }
float Entity::GetRotationDegrees() { return Rotation; }
float Entity::GetRotationRadians() { return glm::radians(Rotation); }
PhysicsComponent* Entity::GetPhysicsComponent() { return physics; }
GraphicsComponent* Entity::GetGraphicsComponent() { return graphics; }


void Entity::SetAttributes(glm::vec2 position, glm::vec2 size, float rotation)
{
	Position = position;
	Size = size;
	Rotation = rotation;
	physics->CreateFromEntity(*this);
}

void Entity::SetAttributes(glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution)
{
	Position = position;
	Size = size;
	Rotation = rotation;
	BodyType = bodytype;
	Density = density;
	Friction = friction;
	Restitution = restitution;

	physics->CreateFromEntity(*this);
}

void Entity::ProcessInput()
{
	PROFILE_FUNCTION();
	LOGGER_INFO("Processing input!");
	input->Update(*this);
}

void Entity::Advance()
{
	PROFILE_FUNCTION();
	LOGGER_INFO("Advancing entity!");
	physics->Update(*this);
}

void Entity::Draw()
{
	PROFILE_FUNCTION();
	LOGGER_INFO("Drawing entity!");
	graphics->Draw(*this);
}