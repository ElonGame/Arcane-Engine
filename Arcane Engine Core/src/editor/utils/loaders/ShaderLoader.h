#pragma once

#include <runtime/renderer/graphics/Shader.h>

namespace arcane {
	namespace editor {

		class ShaderLoader {
		public:
			static Shader* loadShader(const char* vertPath, const char* fragPath);
			static Shader* loadShader(const char* vertPath, const char* fragPath, const char* geoPath);
		private:
			static std::unordered_map<std::size_t, Shader*> s_ShaderCache;
			static std::hash<std::string> s_Hasher;
		};
	}
}
