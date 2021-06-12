#ifndef BLYSS_RECTANGLE_H
#define BLYSS_RECTANGLE_H

#include <cstdint>

namespace blyss
{
    class Rectangle
    {
    public:
        Rectangle(std::int32_t width, std::int32_t height);

        [[nodiscard]] std::int32_t Area() const;

    private:
        std::int32_t width_;
        std::int32_t height_;

    };
}

#endif