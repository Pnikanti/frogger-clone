#pragma once
#include <vector>
#include <box2d/b2_body.h>

class GuiContext;
class GraphicsComponent;
class Entity;
class OrthographicCamera;
class PhysicsWorld;
class PhysicsComponent;
class GameInputComponent;
class ContactListener;
class InputComponent;

enum class GameState
{
	Play = 0, MainMenu, Start, Pause, GameOver
};

class Game {
public:
	Game(const char* appName, int width, int height);
	~Game();

	void Start();
	void End();
	void Exit();
	void Loop();

	void ProcessInput();
	void UpdateAllEntities();
	void CreateGameGui();

	void CreateEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution);

public:
	static float TimeStep;
	static GameState State;

private:
	PhysicsWorld* m_PhysicsWorld;
	ContactListener* m_PhysicsListener;
	GameInputComponent* m_Input;
};