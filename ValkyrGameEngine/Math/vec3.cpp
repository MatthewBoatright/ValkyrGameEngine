#include "vec3.h"

namespace Valkyr { namespace Graphics {

		vec3::vec3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		vec3::vec3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3& vec3::add(const vec3& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& right)
		{
			x *= right.x;
			y *= right.y;
			z *= right.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& right)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;

			return *this;
		}

		vec3& operator+(vec3 left, const vec3& right)
		{
			return left.add(right);
		}

		vec3& operator-(vec3 left, const vec3& right)
		{
			return left.subtract(right);
		}

		vec3& operator*(vec3 left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3& operator/(vec3 left, const vec3& right)
		{
			return left.divide(right);
		}

		vec3& vec3::operator+=(const vec3& right)
		{
			return add(right);
		}

		vec3& vec3::operator-=(const vec3& right)
		{
			return subtract(right);
		}

		vec3& vec3::operator*=(const vec3& right)
		{
			return multiply(right);
		}

		vec3& vec3::operator/=(const vec3& right)
		{
			return divide(right);
		}

		bool vec3::operator==(const vec3& right)
		{
			return ((x == right.x) && (y == right.y) && (z == right.z));
		}

		bool vec3::operator!=(const vec3& right)
		{
			return !(*this == right);
		}

} }