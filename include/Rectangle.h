#pragma once

struct Rectangle
{
    int width;
    int height;
};

void Rectangle_init(struct Rectangle *self, int width, int height);
int Rectangle_area(struct Rectangle *self);
