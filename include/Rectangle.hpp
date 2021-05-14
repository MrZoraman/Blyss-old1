#pragma once

#include <stdint.h>

struct rectangle
{
    int _width;
    int _height;
};

void rectangle_init(struct rectangle *self_s, int32_t width, int32_t height);
int32_t rectangle_area(struct rectangle *self_s);
