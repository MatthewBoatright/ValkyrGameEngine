#include "vec2.h"

namespace Valkyr {	namespace Graphics {

	vec2::vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	vec2::vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	vec2& vec2::add(const vec2& right)
	{
		x += right.x;
		y += right.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& right)
	{
		x -= right.x;
		y -= right.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& right)
	{
		x *= right.x;
		y *= right.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& right)
	{
		x /= right.x;
		y /= right.y;

		return *this;
	}

	vec2& operator+(vec2 left, const vec2& right)
	{
		return left.add(right);
	}

	vec2& operator-(vec2 left, const vec2& right)
	{
		return left.subtract(right);
	}

	vec2& operator*(vec2 left, const vec2& right)
	{
		return left.multiply(right);
	}

	vec2& operator/(vec2 left, const vec2& right)
	{
		return left.divide(right);
	}

	vec2& vec2::operator+=(const vec2& right)
	{
		return add(right);
	}

	vec2& vec2::operator-=(const vec2& right)
	{
		return subtract(right);
	}

	vec2& vec2::operator*=(const vec2& right)
	{
		return multiply(right);
	}

	vec2& vec2::operator/=(const vec2& right)
	{
		return divide(right);
	}

	bool vec2::operator==(const vec2& right)
	{
		return ((x == right.x) && (y == right.y));
	}

	bool vec2::operator!=(const vec2& right)
	{
		return !(*this == right);
	}

} }