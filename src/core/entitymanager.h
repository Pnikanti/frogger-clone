#pragma once

#include <glm/glm.hpp>
#include <box2d/b2_body.h>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "entity.h"
#include "game.h"

class PhysicsComponent;
namespace OpenGL { class GraphicsComponent; }

class EntityManager {
public:
	EntityManager(const EntityManager&) = delete; // copy-constructor

	inline static EntityManager& Get() {
		static EntityManager Instance;
		return Instance;
	}
	void Init(size_t size);
	void Draw();
	inline std::vector<Entity*>& GetEntities() { return Entities; }
	inline std::unordered_map<std::string, Entity*>& GetEntityMap() { return EntityMap; }
protected:
	EntityManager() = default; // constructor
private:
	std::vector<Entity*> Entities;
	std::unordered_map<std::string, Entity*> EntityMap;
};