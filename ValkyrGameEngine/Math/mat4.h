#pragma once

#define _USE_MATH_DEFINES
#include "math.h"

namespace Valkyr { namespace Graphics {
	
	struct mat4
		{
			union
			{
				float elements[4 * 4];
				vec4 columns[4];
			};

			mat4();
			mat4(float diagonal);

			vec4 getColumn(int index)
			{
				index *= 4;
				return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
			}

			static mat4 identity();
			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);
			static mat4 translation(const vec3& translation);
			static mat4 rotation(float angle, const vec3& axis);
			static mat4 scale(const vec3& scale);

			mat4& multiply(const mat4& right);
			vec3 multiply(const vec3& right) const;
			vec4 multiply(const vec4& right) const;

			friend mat4 operator*(mat4 left, const mat4& right);
			friend vec3 operator*(const mat4& left, const vec3& right);
			friend vec4 operator*(const mat4& left, const vec4& right);
			mat4& operator*=(const mat4& right);
		};

} }