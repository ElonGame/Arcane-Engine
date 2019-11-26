#pragma once

#include <runtime/renderer/graphics/camera/CubemapCamera.h>
#include <runtime/renderer/graphics/renderer/renderpass/RenderPass.h>
#include <runtime/renderer/graphics/renderer/renderpass/ShadowmapPass.h>
#include <runtime/renderer/graphics/Shader.h>
#include <runtime/renderer/scene/Scene3D.h>

namespace arcane {

	class ForwardProbePass : public RenderPass {
	public:
		ForwardProbePass(Scene3D *scene);
		virtual ~ForwardProbePass() override;

		void pregenerateIBL();
		void pregenerateProbes();

		void generateLightProbe(glm::vec3& probePosition);
		void generateReflectionProbe(glm::vec3& probePosition);
	private:
		void generateBRDFLUT();
		void generateFallbackProbes();
	private:
		Framebuffer m_SceneCaptureShadowFramebuffer, m_SceneCaptureLightingFramebuffer, m_LightProbeConvolutionFramebuffer, m_ReflectionProbeSamplingFramebuffer;
		CubemapCamera m_CubemapCamera;
		CubemapSettings m_SceneCaptureSettings;
		Cubemap m_SceneCaptureCubemap;

		Shader *m_ConvolutionShader, *m_ImportanceSamplingShader;
	};

}
