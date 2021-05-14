#ifndef BLYSS_RECTANGLE_H_
#define BLYSS_RECTANGLE_H_

#include <cstdint>

namespace Blyss
{
    class Rectangle
    {
    public:
        Rectangle(std::int32_t width, std::int32_t height);

        [[nodiscard]] std::int32_t area() const;

    private:
        std::int32_t width_;
        std::int32_t height_;

    };
}

#endif