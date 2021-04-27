#include "Rectangle.h"

void rectangle_init(struct rectangle *self, int32_t width, int32_t height)
{
    self->width = width;
    self->height = height;
}

int32_t rectangle_area(struct rectangle *self)
{
    return self-> width * self->height;
}