#include "vec4.h"

namespace Valkyr { namespace Graphics {

		vec4::vec4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		vec4::vec4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4& vec4::add(const vec4& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			w += right.w;

			return *this;
		}

		vec4& vec4::subtract(const vec4& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			w -= right.w;

			return *this;
		}

		vec4& vec4::multiply(const vec4& right)
		{
			x *= right.x;
			y *= right.y;
			z *= right.z;
			w *= right.w;

			return *this;
		}

		vec4& vec4::divide(const vec4& right)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;
			w /= right.w;

			return *this;
		}

		vec4& operator+(vec4 left, const vec4& right)
		{
			return left.add(right);
		}

		vec4& operator-(vec4 left, const vec4& right)
		{
			return left.subtract(right);
		}

		vec4& operator*(vec4 left, const vec4& right)
		{
			return left.multiply(right);
		}

		vec4& operator/(vec4 left, const vec4& right)
		{
			return left.divide(right);
		}

		vec4& vec4::operator+=(const vec4& right)
		{
			return add(right);
		}

		vec4& vec4::operator-=(const vec4& right)
		{
			return subtract(right);
		}

		vec4& vec4::operator*=(const vec4& right)
		{
			return multiply(right);
		}

		vec4& vec4::operator/=(const vec4& right)
		{
			return divide(right);
		}

		bool vec4::operator==(const vec4& right)
		{
			return ((x == right.x) && (y == right.y) && (z == right.z) && (w == right.w));
		}

		bool vec4::operator!=(const vec4& right)
		{
			return !(*this == right);
		}

} }