#pragma once

#include "Shader.h"

#include <runtime/renderer/graphics/camera/FPSCamera.h>
#include <runtime/renderer/graphics/renderer/GLCache.h>
#include <runtime/renderer/graphics/mesh/common/Cube.h>
#include <runtime/renderer/platform/OpenGL/Buffer.h>
#include <runtime/renderer/platform/OpenGL/IndexBuffer.h>
#include <runtime/renderer/platform/OpenGL/VertexArray.h>
#include <editor/utils/loaders/TextureLoader.h>

namespace arcane {

	class Skybox {
	public:
		Skybox(const std::vector<std::string> &filePaths);

		void Draw(ICamera *camera);

		Cubemap* getSkyboxCubemap() { return m_SkyboxCubemap; }
	private:
		Shader *m_SkyboxShader;
		GLCache *m_GLCache;
		
		Cube cube;
		Cubemap *m_SkyboxCubemap;
	};

}
