#include "Rectangle.h"

void Rectangle_init(struct Rectangle *self, int32_t width, int32_t height)
{
    self->width = width;
    self->height = height;
}

int32_t Rectangle_area(struct Rectangle *self)
{
    return self-> width * self->height;
}