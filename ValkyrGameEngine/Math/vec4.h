#pragma once

#include <GL/glew.h>

namespace Valkyr { namespace Graphics {

	struct vec4
	{
		float x, y, z, w;

		vec4();
		vec4(float x, float y, float z, float w);

		vec4& add(const vec4& right);
		vec4& subtract(const vec4& right);
		vec4& multiply(const vec4& right);
		vec4& divide(const vec4& right);

		friend vec4& operator+(vec4 left, const vec4& right);
		friend vec4& operator-(vec4 left, const vec4& right);
		friend vec4& operator*(vec4 left, const vec4& right);
		friend vec4& operator/(vec4 left, const vec4& right);
		vec4& operator+=(const vec4& right);
		vec4& operator-=(const vec4& right);
		vec4& operator*=(const vec4& right);
		vec4& operator/=(const vec4& right);
		bool operator==(const vec4& right);
		bool operator!=(const vec4& right);
	};

} }