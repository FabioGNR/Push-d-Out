#pragma once

namespace engine {
struct Color {
    explicit Color(int r, int g, int b, int a)
        : r{ r }
        , g{ g }
        , b{ b }
        , a{ a }
    {
    }
    explicit Color()
        : r{ 0 }
        , g{ 0 }
        , b{ 0 }
        , a{ 255 }
    {
    }
    int r;
    int g;
    int b;
    int a;

    bool operator==(const Color& rhs) const
    {
        return r == rhs.r
            && g == rhs.g
            && b == rhs.b
            && a == rhs.a;
    }

    bool operator!=(const Color& rhs) const
    {
        return !(rhs == *this);
    }
};
}
