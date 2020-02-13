#include "pch.h"

#include <editor/Window.h>
#include <runtime/renderer/graphics/renderer/MasterRenderer.h>
#include <runtime/renderer/scene/Scene3D.h>
#include <runtime/renderer/utils/Time.h>
#include <editor/ui/RuntimePane.h>
#include <editor/ui/DebugPane.h>
#include <editor/utils/loaders/TextureLoader.h>

int main() {
	// This should be at an entry point of the application
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

	// Prepare the engine
	arcane::editor::Window window("Arcane Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	arcane::editor::TextureLoader::initializeDefaultTextures();
	arcane::Scene3D scene(&window);
	arcane::MasterRenderer renderer(&scene);
	arcane::editor::InputManager manager;

	// Prepare the UI
	arcane::editor::RuntimePane runtimePane(glm::vec2(270.0f, 175.0f));
	arcane::editor::DebugPane debugPane(glm::vec2(270.0f, 400.0f));

	// Initialize the renderer
	renderer.init();

	arcane::Time deltaTime;
	while (!window.closed()) {
		deltaTime.update();

#if DEBUG_ENABLED
		if (debugPane.getWireframeMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		arcane::editor::Window::bind();
		arcane::editor::Window::clear();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		scene.onUpdate((float)deltaTime.getDeltaTime());
		renderer.render();

		// Display panes
		arcane::editor::Window::bind();
		runtimePane.render();
		debugPane.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Window and input updating
		window.update();
	}
	return 0;
}
