#pragma once

#include <algorithm>
#include <cmath>
#include <ostream>
#include <type_traits>

// Visual Studio does not support <cmath> M_PI
constexpr double PI = 3.14159265358979323846;

namespace common {
template <class T>
struct Vector2D {
    T x;
    T y;

    constexpr static int PRECISION = 1000000;

    Vector2D(T x1, T y1)
        : x{ x1 }
        , y{ y1 }
    {
        static_assert(std::is_arithmetic<T>(), "Vector2D can only be created with arithmetic types");
    }

    Vector2D()
        : x{ 0 }
        , y{ 0 }
    {
    }

    // basic arithmetic functions
    Vector2D<T>& operator+=(const Vector2D<T>& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D<T>& operator+=(T addition)
    {
        x += addition;
        y += addition;
        return *this;
    }

    friend Vector2D<T> operator+(Vector2D<T> left, const Vector2D<T>& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    friend Vector2D<T> operator+(Vector2D<T> left, T increment)
    {
        left.x += increment;
        left.y += increment;
        return left;
    }

    friend Vector2D<T> operator-(Vector2D<T> left, const Vector2D<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }

    friend Vector2D<T> operator-(Vector2D<T> left, T decrement)
    {
        left.x -= decrement;
        left.y -= decrement;
        return left;
    }

    Vector2D<T>& operator*=(double factor)
    {
        x *= factor;
        y *= factor;
        return *this;
    }

    Vector2D<T>& operator*=(const Vector2D<T>& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    friend Vector2D<T> operator*(Vector2D<T> left, double factor)
    {
        left.x *= factor;
        left.y *= factor;
        return left;
    }

    friend Vector2D<T> operator*(Vector2D<T> left, const Vector2D<T>& right)
    {
        left.x *= right.x;
        left.y *= right.y;
        return left;
    }

    Vector2D<T>& operator/=(int factor)
    {
        x /= factor;
        y /= factor;
        return *this;
    }

    Vector2D<T>& operator/=(double factor)
    {
        x /= factor;
        y /= factor;
        return *this;
    }

    Vector2D<T>& operator/=(const Vector2D<T>& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2D<T>& operator-=(const Vector2D<T>& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    friend Vector2D<T> operator/(Vector2D<T> left, int factor)
    {
        left.x /= factor;
        left.y /= factor;
        return left;
    }

    friend Vector2D<T> operator/(Vector2D<T> left, double factor)
    {
        left.x /= factor;
        left.y /= factor;
        return left;
    }

    friend Vector2D<T> operator/(Vector2D<T> left, const Vector2D<T>& right)
    {
        left.x /= right.x;
        left.y /= right.y;
        return left;
    }

    friend bool operator==(const Vector2D& left, const Vector2D& right)
    {
        auto returnValue = (left.x == right.x && left.y == right.y);
        return returnValue;
    }
    friend bool operator!=(const Vector2D& left, const Vector2D& right)
    {
        auto returnValue = left.x != right.x || left.y != right.y;
        return returnValue;
    }

    // mathematical properties
    static Vector2D<T> max(Vector2D<T> left, const Vector2D<T>& right)
    {
        static_assert(std::is_arithmetic<T>(), "Vector2D can only use arithmetic types");
        left.x = std::max(left.x, right.x);
        left.y = std::max(left.y, right.y);
        return left;
    }

    static Vector2D<T> min(Vector2D<T> left, const Vector2D<T>& right)
    {
        left.x = std::min(left.x, right.x);
        left.y = std::min(left.y, right.y);
        return left;
    }

    T magnitude() const
    {
        return sqrt(
            pow(this->x, 2) + pow(this->y, 2));
    }

    // Vector mathematics
    Vector2D<T> rotateCounterClockwise(double degrees) const
    {
        double angle = degrees * (PI / 180);
        auto newX = round((this->x * cos(angle) - this->y * sin(angle)) * PRECISION) / PRECISION;
        auto newY = round((this->x * sin(angle) + this->y * cos(angle)) * PRECISION) / PRECISION;
        Vector2D<T> returnVector(newX, newY);
        return returnVector;
    }

    T dotProduct(const Vector2D<T>& other)
    {
        return this->x * other.x + this->y * other.y;
    }

    T findAngle(const Vector2D<T>& other)
    {
        T dot = this->dotProduct(other);
        auto cosAngle = dot / (this->magnitude() * other.magnitude());
        return acos(cosAngle);
    }

    double distance(const Vector2D<T>& other) const
    {
        T deltaXSquared = pow(other.x - x, 2);
        T deltaYSquared = pow(other.y - y, 2);
        double distance = sqrt(deltaXSquared + deltaYSquared);
        return distance;
    }

    friend std::ostream& operator<<(std::ostream& str, const Vector2D<T>& vector)
    {
        // print something from v to str, e.g: Str << v.getX();
        str << "{" << vector.x << ", " << vector.y << "}";
        return str;
    }

    Vector2D<double> normalize()
    {

        double length = sqrt(pow(x, 2) + pow(y, 2));
        auto newX = x / length;
        auto newY = y / length;
        Vector2D<double> result{ newX, newY };
        return result;
    }

    template <typename X>
    Vector2D<X> castTo() const
    {
        return { static_cast<X>(this->x), static_cast<X>(this->y) };
    }

    bool approximatelyEquals(Vector2D<double> v, double threshold) const
    {
        return v.x + threshold >= x && v.x - threshold <= x && v.y + threshold >= y && v.y - threshold <= y;
    }
};

template <typename X, typename Y>
Vector2D<Y> operator/(Vector2D<X> left,
    const Vector2D<Y>& right)
{
    left.x /= right.x;
    left.y /= right.y;
    Y newX = left.x / right.x;
    Y newY = left.y / right.y;
    return { newX, newY };
}
}