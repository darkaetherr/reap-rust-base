#pragma once

namespace crt::math {
	inline float modf( float x, float y ) {
		return x - math::trunc( x / y ) * y;
	}
}