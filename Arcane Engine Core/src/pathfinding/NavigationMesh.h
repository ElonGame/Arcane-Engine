#pragma once

#include "terrain/Terrain.h"

namespace arcane
{
	struct Triangle
	{
		union
		{
			std::array<glm::vec3*, 3> v;
			glm::vec3* a;
			glm::vec3* b;
			glm::vec3* c;
		};
	};

	struct Quad
	{
		union
		{
			std::array<glm::vec3*, 4> v;
			glm::vec3* a;
			glm::vec3* b;
			glm::vec3* c;
			glm::vec3* d;
		};
	};

	class NavigationMesh
	{
	public:
		Terrain* terrain; // Reference terrain that we want to build the navigation mesh on 
		float slope; // A parameter that will hold the slope that we will accept for the navigation mesh

		NavigationMesh(Terrain* terrain, int slope);
		~NavigationMesh();

		static bool IsPointOnTriangle(const glm::vec3& point, const Triangle& triangle);
		static bool IsPointOnPlane(const glm::vec3& point, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
		static bool SameSideTriangle(const glm::vec3& point, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);

		// Set the terrain that this navMesh will use (Might want to regenerate mesh for new Terrain)
		inline void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
		// Generate the navigation mesh from the current terrain
		void GenerateNavigationMesh();
		// Checks if there is an obstacle at this location
		bool ObstacleOnPoint(const glm::vec3& point);
		// Checks if this point is navigable
		bool ExistsPathToPoint(const glm::vec3& point);
		// Triangulate the generated polygon
		std::vector<Triangle> TriangulatePoly(std::vector<glm::vec3*> polygon);
		// Draw the navigation mesh
		void Draw(const std::vector<Triangle>& trinagles);
	};
}
