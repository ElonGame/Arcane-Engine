#pragma once

#include <runtime/renderer/graphics/mesh/Mesh.h>

namespace arcane {

	class Sphere : public Mesh {
	public:
		Sphere(int xSegments = 30, int ySegments = 30);
	};

}
