#pragma once

namespace arcane::editor {

	class Pane {
	public:
		Pane(std::string& paneName, glm::vec2& paneSize);
		~Pane() = default;

		void render();
	protected:
		virtual void setupPaneObjects() = 0;

		std::string m_PaneName;
		glm::vec2 m_PaneSize;
	};

}
