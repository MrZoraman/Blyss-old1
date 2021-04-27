#include "Rectangle.h"

void Rectangle_init(struct Rectangle *self, int width, int height)
{
    self->width = width;
    self->height = height;
}

int Rectangle_area(struct Rectangle *self)
{
    return self-> width * self->height;
}