#pragma once
#include <cmath>


//Used in calculation

class Vector2
{
public:
	float x, y;

	Vector2() = default;

	Vector2(float a, float b)
		:x(a), y(b) {
	};

	~Vector2() = default;
	
	Vector2 operator+(const Vector2& v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(const Vector2& v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(const Vector2& v)
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 operator/(const Vector2& v)
	{
		return Vector2(x / v.x, y / v.y);
	}

	Vector2 operator+(const float& num)
	{
		return Vector2(x + num, y + num);
	}

	Vector2 operator-(const float& num)
	{
		return Vector2(x - num, y - num);
	}

	Vector2 operator*(float& num)
	{
		return Vector2(x * num, y * num);
	}

	Vector2 operator/(float& num)
	{
		return Vector2(x / num, y / num);
	}

	void operator+=(Vector2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator-=(Vector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	void operator*=(Vector2& v)
	{
		x *= v.x;
		y *= v.y;
	}

	void operator/=(Vector2& v)
	{
		x /= v.x;
		y /= v.y;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}

	void normalize()
	{
		if (this->length() == 0)
			return;
		x = x / this->length();
		y = y / this->length();
	}
};