#include "Rectangle.h"

void rectangle_init(struct rectangle *self_s, int32_t width, int32_t height)
{
    self_s->width = width;
    self_s->height = height;
}

int32_t rectangle_area(struct rectangle *self_s)
{
    return self_s-> width * self_s->height;
}