#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <box2d/b2_body.h>
#include "statistics.h"
#include "gui.h"
#include "entitymanager.h"
#include "entity.h"
#include "context.h"
#include "log.h"
#include "graphics.h"
#include "physics.h"
#include "game.h"
#include "instrumentor.h"

void GuiContext::Update() {}
void GuiContext::Update(Entity& entity) {}

DebugGuiContext::DebugGuiContext() : wFlags(0), visible(true)
{
	wFlags |= ImGuiWindowFlags_NoBackground;
	wFlags |= ImGuiWindowFlags_NoTitleBar;
	wFlags |= ImGuiWindowFlags_NoResize;
	wFlags |= ImGuiWindowFlags_NoMove;
	LOGGER_TRACE("WindowFlags: {0}", wFlags);
}

GameGuiContext::GameGuiContext() : wFlags(0), wBackgroundFlags(0), visible(true)
{
	wFlags |= ImGuiWindowFlags_NoBackground;
	wFlags |= ImGuiWindowFlags_NoTitleBar;
	wFlags |= ImGuiWindowFlags_NoResize;
	wFlags |= ImGuiWindowFlags_NoMove;
	wBackgroundFlags |= ImGuiWindowFlags_NoTitleBar;
	wBackgroundFlags |= ImGuiWindowFlags_NoResize;
	wBackgroundFlags |= ImGuiWindowFlags_NoMove;
	ImGui::GetIO().Fonts->AddFontDefault();

	LOGGER_TRACE("WindowFlags: {0}", wFlags);
	LOGGER_TRACE("WindowBackgroundFlags: {0}", wBackgroundFlags);

}

void DebugGuiContext::Update() {
	PROFILE_FUNCTION();
	ImGui::SetNextWindowPos(ImVec2(0, (int)Context::SCR_HEIGHT - 100));
	ImGui::SetNextWindowSize(ImVec2(350, 200));
	ImGui::Begin("Debug", &visible, wFlags);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Total Allocated (bytes): %u", Statistics::Get().AllocatedMemory);
	ImGui::Text("Freed (bytes): %u", Statistics::Get().FreedMemory);
	ImGui::Text("Current (bytes): %u", Statistics::Get().CurrentHeapUsage());
	ImGui::Text("Entity vector size: %u", EntityManager::Get().GetEntities().size());
	ImGui::End();
}

void GameGuiContext::Update()
{
	PROFILE_FUNCTION();
	switch (Game::State)
	{
		case GameState::Start:
		{
			break;
		}
		case GameState::MainMenu:
		{
			break;
		}
		case GameState::GameOver:
		{
			break;
		}
		case GameState::Pause:
		{
			break;
		}
	}
}
