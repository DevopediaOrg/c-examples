/*
This code converts RGB color from hex form to decimal form.
Hex form starts with '#' character, which is common on webpages.
Example: #66CCDE in decimal is (102, 204, 222)
*/

#include <stdio.h>

typedef struct {
    unsigned int r;
    unsigned int g;
    unsigned int b;
} Color;


void main() {
    char bg_color[7] = "#66CCDE";

    Color c;
    sscanf(bg_color, "#%2x%2x%2x", &c.r, &c.g, &c.b);
    printf("%d %d %d\n", c.r, c.g, c.b);

    // Illustrating pointer syntax to struct member variables
    Color *p = &c;
    printf("%d %d %d\n", p->r, p->g, p->b);
}
