
#pragma once

namespace dotth
{
	template<typename ty>
	struct vector2d {
		union {
			struct { ty f[2]; };
			struct { ty x, y; };
		};

		vector2d(void)
			: x(0), y(0)
		{
		}

		vector2d(ty f)
			: x(f), y(f)
		{
		}

		vector2d(ty* f)
			: x(f[0]), y(f[1])
		{
		}

		vector2d(ty _x, ty _y)
			: x(_x), y(_y)
		{
		}

		static void add(const vector2d& left, const vector2d& right, vector2d& result)
		{
			result.x = left.x + right.x;
			result.y = left.y + right.y;
		}

		static void subtract(const vector2d& left, const vector2d& right, vector2d& result)
		{
			result.x = left.x - right.x;
			result.y = left.y - right.y;
		}

		static void multiply(const vector2d& left, const vector2d& right, vector2d& result)
		{
			result.x = left.x * right.x;
			result.y = left.y * right.y;
		}

		static void multiply(const vector2d& left, ty right, vector2d& result)
		{
			result.x = left.x * right;
			result.y = left.y * right;
		}

		static void devide(const vector2d& left, ty right, vector2d& result)
		{
			result.x = left.x / right;
			result.y = left.y / right;
		}

		static bool equal(const vector2d& left, const vector2d& right, ty tolerance = std::numeric_limits<ty>::epsilon())
		{
			return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance;
		}

		ty& operator[](int index)
		{
			return f[index];
		}

		ty operator[](int index) const
		{
			return f[index];
		}

		template <typename castTy>
		vector2d<castTy> cast(void) const
		{
			vector2d<castTy> v;
			v.x = static_cast<castTy>(this->x);
			v.y = static_cast<castTy>(this->y);
			return v;
		}
	};

	using vector2 = vector2d<float>;
	using vector2i = vector2d<int>;
};