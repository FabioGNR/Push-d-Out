#pragma once
#include <algorithm>

namespace common {
struct Vector2D {
    double x;
    double y;

    explicit Vector2D(double x1, double y1)
        : x{ x1 }
        , y{ y1 }
    {
    }

    int x_int()
    {
        return static_cast<int>(x);
    }

    int y_int()
    {
        return static_cast<int>(y);
    }

    Vector2D& operator+=(const Vector2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend Vector2D operator+(Vector2D left,
        const Vector2D& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    Vector2D& operator*=(double factor)
    {
        x *= factor;
        y *= factor;
        return *this;
    }

    Vector2D& operator*=(const Vector2D& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    friend Vector2D operator*(Vector2D left,
        double factor)
    {
        left.x *= factor;
        left.y *= factor;
        return left;
    }

    friend Vector2D operator*(Vector2D left,
        const Vector2D& right)
    {
        left.x *= right.x;
        left.y *= right.y;
        return left;
    }

    Vector2D& operator/=(const Vector2D& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    friend Vector2D operator/(Vector2D left,
        const Vector2D& right)
    {
        left.x /= right.x;
        left.y /= right.y;
        return left;
    }

    Vector2D& operator/=(double factor)
    {
        x /= factor;
        y /= factor;
        return *this;
    }

    friend Vector2D operator/(Vector2D left,
        double factor)
    {
        left.x /= factor;
        left.y /= factor;
        return left;
    }

    Vector2D max(Vector2D other)
    {
        other.x = std::max(x, other.x);
        other.y = std::max(y, other.y);
        return other;
    }

    Vector2D min(Vector2D other)
    {
        other.x = std::min(x, other.x);
        other.y = std::min(y, other.y);
        return other;
    }

    Vector2D& operator-=(const Vector2D& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    friend Vector2D operator-(Vector2D left,
        const Vector2D& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }
};
}
