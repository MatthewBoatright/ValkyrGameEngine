#pragma once
#include <math.h>
#include <cstring>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace Valkyr { namespace Graphics {

	inline float toRadians(float degrees)
	{
		return degrees * M_PI / 180.0f;
	}

} }