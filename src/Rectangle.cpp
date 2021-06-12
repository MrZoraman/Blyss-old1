#include "Rectangle.hpp"

#include <cassert>
#include <cstdint>

namespace blyss
{
    Rectangle::Rectangle(std::int32_t width, std::int32_t height)
        : width_{width}
        , height_{height}
    {
        assert(width > 0);
        assert(height > 0);
    }

    std::int32_t Rectangle::Area() const
    {
        return width_ * height_;
    }
}
