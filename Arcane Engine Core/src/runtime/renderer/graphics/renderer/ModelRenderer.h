#pragma once

#include "GLCache.h"

#include <runtime/renderer/scene/RenderableModel.h>
#include <runtime/renderer/graphics/camera/FPSCamera.h>
#include <runtime/renderer/graphics/mesh/Model.h>
#include <runtime/renderer/graphics/mesh/common/Quad.h>
#include <runtime/renderer/graphics/mesh/common/Cube.h>
#include <runtime/renderer/graphics/renderer/renderpass/RenderPassType.h>

namespace arcane {

	class ModelRenderer {
	public:
		ModelRenderer(FPSCamera *camera);

		void submitOpaque(RenderableModel *renderable);
		void submitTransparent(RenderableModel *renderable);
		
		void setupOpaqueRenderState();
		void setupTransparentRenderState();

		void flushOpaque(Shader *shader, RenderPassType pass);
		void flushTransparent(Shader *shader, RenderPassType pass);
	public:
		Quad NDC_Plane;
		Cube NDC_Cube;
	private:
		void ModelRenderer::setupModelMatrix(RenderableModel *renderable, Shader *shader, RenderPassType pass);

		std::deque<RenderableModel*> m_OpaqueRenderQueue;
		std::deque<RenderableModel*> m_TransparentRenderQueue;

		FPSCamera *m_Camera;
		GLCache *m_GLCache;
	};

}
