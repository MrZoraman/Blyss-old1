#include <stdio.h>
#include <stdlib.h>

#include "Rectangle.h"

int main()
{
    struct Rectangle r;
    Rectangle_init(&r, 5, 10);
    printf("Rectangle area: %d\n", Rectangle_area(&r));
    return EXIT_SUCCESS;
}