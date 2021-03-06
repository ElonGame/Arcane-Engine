#pragma once

#include <graphics/Shader.h>

namespace arcane {

	class Light {
	public:
		Light(float lightIntensity, glm::vec3 &lightColour);

		virtual void setupUniforms(Shader *shader, int currentLightIndex) = 0;
	protected:
		float m_Intensity;
		glm::vec3 m_LightColour;

		bool m_IsStatic; // Should be true if the light will never have any of it's properties changed
	};

}
