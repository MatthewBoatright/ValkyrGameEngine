#pragma once

#include <GL/glew.h>

namespace Valkyr { namespace Graphics { 

	struct vec2
	{
		float x, y;

		vec2();
		vec2(float x, float y);

		vec2& add(const vec2& right);
		vec2& subtract(const vec2& right);
		vec2& multiply(const vec2& right);
		vec2& divide(const vec2& right);

		friend vec2& operator+(vec2 left, const vec2& right);
		friend vec2& operator-(vec2 left, const vec2& right);
		friend vec2& operator*(vec2 left, const vec2& right);
		friend vec2& operator/(vec2 left, const vec2& right);
		vec2& operator+=(const vec2& right);
		vec2& operator-=(const vec2& right);
		vec2& operator*=(const vec2& right);
		vec2& operator/=(const vec2& right);
		bool operator==(const vec2& right);
		bool operator!=(const vec2& right);
	};

} }