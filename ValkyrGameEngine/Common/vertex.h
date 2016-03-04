#pragma once

#include <glm/glm.hpp>

namespace Valkyr { namespace Graphics { 

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 UV;
		glm::vec3 Normal;

		Vertex() {}
		Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
			: Position(position), UV(uv), Normal(normal)
		{}
	};

} }