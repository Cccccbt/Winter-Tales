#pragma once

#include <cmath>

// Simple 2D vector with basic arithmetic helpers used throughout gameplay
// code for positioning, velocity, and offset calculations.
class Vector2
{
public:
        float x = 0.0f;
        float y = 0.0f;

        Vector2() = default;
        Vector2(float a, float b) : x(a), y(b) {}
        ~Vector2() = default;

        // Basic arithmetic operators operating component-wise.
        Vector2 operator+(const Vector2& v) const
        {
                return Vector2(x + v.x, y + v.y);
        }

        Vector2 operator-(const Vector2& v) const
        {
                return Vector2(x - v.x, y - v.y);
        }

        Vector2 operator*(const Vector2& v) const
        {
                return Vector2(x * v.x, y * v.y);
        }

        Vector2 operator/(const Vector2& v) const
        {
                return Vector2(x / v.x, y / v.y);
        }

        // Scalar arithmetic for convenient scaling.
        Vector2 operator+(float num) const
        {
                return Vector2(x + num, y + num);
        }

        Vector2 operator-(float num) const
        {
                return Vector2(x - num, y - num);
        }

        Vector2 operator*(float num) const
        {
                return Vector2(x * num, y * num);
        }

        Vector2 operator/(float num) const
        {
                return Vector2(x / num, y / num);
        }

        // In-place arithmetic.
        void operator+=(const Vector2& v)
        {
                x += v.x;
                y += v.y;
        }

        void operator-=(const Vector2& v)
        {
                x -= v.x;
                y -= v.y;
        }

        void operator*=(const Vector2& v)
        {
                x *= v.x;
                y *= v.y;
        }

        void operator/=(const Vector2& v)
        {
                x /= v.x;
                y /= v.y;
        }

        float length() const
        {
                return std::sqrt(x * x + y * y);
        }

        // Normalize in place and return the normalized copy; returns zero vector
        // when the magnitude is 0 to avoid division by zero.
        Vector2 normalize()
        {
                if (length() == 0)
                        return Vector2();
                x = x / length();
                y = y / length();

                return Vector2(x, y);
        }
};
