#ifndef Intersect
#define Intersect

struct pt { double x, y; };

bool intersect(pt a, pt b, pt c, pt d, pt & left, pt & right);

#endif 