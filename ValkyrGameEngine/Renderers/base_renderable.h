#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Valkyr { namespace Graphics { 

	class BaseRenderable
	{
	public:
		BaseRenderable(glm::vec3 position, glm::vec3 size, glm::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color)
		{}

		inline const glm::vec3 getPosition() const { return m_Position; }
		inline const glm::vec3 getSize() const { return m_Size; }
		inline const glm::vec4 getColor() const { return m_Color; }

	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Size;
		glm::vec4 m_Color;

	};

} }