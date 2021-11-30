
#pragma once

#include <math.h>

float clamp(float min, float max, float value) {
	return min >= value ? min : max <= value ? max : value;
}

namespace easing {
	namespace sin {
		constexpr float pi = 3.141592f;
		float in(float k) {
			return 1.f - cosf(pi * k * 0.5f);
		}
		float out(float k) {
			return sinf(pi * k * 0.5f);
		}
		float in_out(float k) {
			return -(cosf(pi * k) - 1.f) * 0.5f;
		}
	}
	namespace quad {
		float in(float k) {
			return k * k;
		}
		float out(float k) {
			return 1.f - (1.f - k) * (1.f - k);
		}
		float in_out(float k) {
			return k < 0.5f ? 2.f * k * k : 1.f - pow((-2.f * k) + 2.f, 2.f) * 0.5f;
		}
	}
	namespace cubic {
		float in(float k) {
			return k * k * k;
		}
		float out(float k) {
			return 1.f - pow(1.f - k, 3.f);
		}
		float in_out(float k) {
			return k < 0.5f ? 4.f * k * k * k : 1.f - pow((-2.f * k) + 2.f, 3.f) * 0.5f;
		}
	}
	namespace quart {
		float in(float k) {
			return k * k * k * k;
		}
		float out(float k) {
			return 1.f - pow(1.f - k, 4.f);
		}
		float in_out(float k) {
			return k < 0.5f ? 8.f * k * k * k * k : 1.f - pow((-2.f * k) + 2.f, 4.f) * 0.5f;
		}
	}
	namespace quint {
		float in(float k) {
			return k * k * k * k * k;
		}
		float out(float k) {
			return 1.f - pow(1.f - k, 5.f);
		}
		float in_out(float k) {
			return k < 0.5f ? 16.f * k * k * k * k * k : 1.f - pow((-2.f * k) + 2.f, 5.f) * 0.5f;
		}
	}
	namespace expo {
		float in(float k) {
			return pow(2.f, 10.f * k - 10.f);
		}
		float out(float k) {
			return 1.f - pow(2.f, -10.f * k);
		}
		float in_out(float k) {
			return k < 0.5f ? pow(2.f, 20.f * k - 10.f) * 0.5f : (2.f - pow(2.f, -20.f * k + 10.f)) * 0.5f;
		}
	}
	namespace back {
		float in(float k, float c = 1.70158f) {
			float c1 = c + 1.f;
			return c1 * k * k * k - c * k * k;
		}
		float out(float k, float c = 1.70158f) {
			float c1 = c + 1.f;
			return 1.f + c1 * pow(k - 1.f, 3.f) + c * pow(k - 1.f, 2.f);
		}
		float in_out(float k, float c = 1.70158f) {
			float c1 = c * 1.525f;
			return k < 0.5f
				? (pow(2.f * k, 2.f) * ((c1 + 1.f) * 2.f * k - c1)) * 0.5f
				: (pow(2.f * k - 2.f, 2.f) * ((c1 + 1.f) * (k * 2.f - 2.f) + c1) + 2.f) * 0.5f;
		}
	}
	namespace elastic {
		constexpr float pi = 3.141592f;
		float in(float k) {
			float c = (2.f * pi) / 3.f;
			return -pow(2.f, 10.f * k - 10.f) * sinf((k * 10.f - 10.75f) * c);
		}
		float out(float k) {
			float c = (2.f * pi) / 3.f;
			return pow(2.f, -10.f * k)* sinf((k * 10.f - 0.75f) * c) + 1.f;
		}
		float in_out(float k) {
			float c = (2.f * pi) / 4.5f;
			return k < 0.5f
				? -(pow(2.f, 20.f * k - 10.f) * sinf((20.f * k - 11.125f) * c)) / 2.f
				: (pow(2.f, -20.f * k + 10.f) * sinf((20.f * k - 11.125f) * c)) / 2.f + 1.f;
		}
	}
	namespace bounce {
		float out(float k) {
			float n = 7.5625f;
			float d = 2.75f;
			if (k < 1.f / d)
				return n * k * k;
			else if (k < 2.f / d)
				return n * (k -= 1.5f / d) * k + 0.75f;
			else if (k < 2.5f / d)
				return n * (k -= 2.25f / d) * k + 0.9375f;
			return n * (k -= 2.625f / d) * k + 0.984375f;
		}
		float in(float k) {
			return 1.f - out(1.f - k);
		}
		float in_out(float k) {
			return k < 0.5f
				? (1.f - out(1.f - 2.f * k)) * 0.5f
				: (1.f + out(2.f * k - 1.f)) * 0.5f;
		}
	}
}