#pragma once

#include <GL/glew.h>

namespace Valkyr { namespace Graphics {

	struct vec3
	{
		float x, y, z;

		vec3();
		vec3(float x, float y, float z);

		vec3& add(const vec3& right);
		vec3& subtract(const vec3& right);
		vec3& multiply(const vec3& right);
		vec3& divide(const vec3& right);

		friend vec3& operator+(vec3 left, const vec3& right);
		friend vec3& operator-(vec3 left, const vec3& right);
		friend vec3& operator*(vec3 left, const vec3& right);
		friend vec3& operator/(vec3 left, const vec3& right);
		vec3& operator+=(const vec3& right);
		vec3& operator-=(const vec3& right);
		vec3& operator*=(const vec3& right);
		vec3& operator/=(const vec3& right);
		bool operator==(const vec3& right);
		bool operator!=(const vec3& right);
	};

} }