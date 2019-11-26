#pragma once

#include <runtime/renderer/graphics/renderer/renderpass/RenderPass.h>
#include <runtime/renderer/graphics/Shader.h>
#include <runtime/renderer/scene/Scene3D.h>
#include <runtime/renderer/graphics/camera/ICamera.h>

namespace arcane {

	enum DeferredStencilValue : int {
		ModelStencilValue = 0x01,
		TerrainStencilValue = 0x02
	};

	class DeferredGeometryPass : public RenderPass {
	public:
		DeferredGeometryPass(Scene3D *scene);
		DeferredGeometryPass(Scene3D *scene, GBuffer *customGBuffer);
		virtual ~DeferredGeometryPass() override;

		GeometryPassOutput executeGeometryPass(ICamera *camera, bool renderOnlyStatic);
	private:
		bool m_AllocatedGBuffer;
		GBuffer *m_GBuffer;
		Shader *m_ModelShader, *m_TerrainShader;
	};

}
