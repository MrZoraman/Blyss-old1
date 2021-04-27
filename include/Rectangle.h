#pragma once

#include <stdint.h>

struct Rectangle
{
    int width;
    int height;
};

void Rectangle_init(struct Rectangle *self, int32_t width, int32_t height);
int32_t Rectangle_area(struct Rectangle *self);
