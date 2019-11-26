#include "pch.h"
#include "Pane.h"

namespace arcane {
	namespace editor {

		Pane::Pane(std::string& paneName, glm::vec2& paneSize) : m_PaneName(paneName), m_PaneSize(paneSize) {
		}

		void Pane::render() {
			ImGui::Begin(m_PaneName.c_str(), nullptr);
			setupPaneObjects();
			ImGui::End();
		}
	}
}
