#pragma once
#include <vector>

class GuiContext;

class GuiManager {
public:
	GuiManager(const GuiManager&) = delete;

	inline static GuiManager& Get() {
		static GuiManager Instance;
		return Instance;
	}
	inline std::vector<GuiContext*>& GetContexts() { return GuiContexts; }

	void Init(size_t size);
	void Destroy();
	void Draw();
	void Begin();
	void End();

protected:
	GuiManager::GuiManager() = default;
private:
	ImGuiContext* Context;
	std::vector<GuiContext*> GuiContexts;
	bool FirstDraw;
};
