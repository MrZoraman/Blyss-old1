#pragma once

#include <stdint.h>

struct rectangle
{
    int width;
    int height;
};

void rectangle_init(struct rectangle *self, int32_t width, int32_t height);
int32_t rectangle_area(struct rectangle *self);
