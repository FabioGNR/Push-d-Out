#pragma once
#include <algorithm>
#include <cmath>

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

    // basic arithmetic functions
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

    Vector2D& operator/=(double factor)
    {
        x /= factor;
        y /= factor;
        return *this;
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

    friend Vector2D operator/(Vector2D left,
        double factor)
    {
        left.x /= factor;
        left.y /= factor;
        return left;
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

    friend bool operator==(const Vector2D left, const Vector2D& right) {
        return left.x == right.x && left.y == right.y;
    }
    friend bool operator!=(const Vector2D left, const Vector2D right) {
        return left.x != right.x || left.y != right.y;
    }

    // mathematical properties
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

    double magnitude() const {
        return sqrt(
                pow(this->x, 2) +
                pow(this->y, 2));
    }

    // Vector mathematics
    Vector2D rotate(double angle) {
        double newX = this->x*cos(angle) - this->y*sin(angle);
        double newY = this->x*sin(angle) - this->y*cos(angle);

        return Vector2D(newX, newY);
    }

    double dotProduct(const Vector2D& other) {
        return
            this->x * other.x +
            this->y * other.y;
    }

    double findAngle(const Vector2D& other) {
        double dot = this->dotProduct(other);
        double cosAngle = dot/(this->magnitude() * other.magnitude());
        return acos(cosAngle);
    }
};
}
