/*
Given two points in 3D Cartesian coordinates,
find the Euclidean distance between the points.
*/

#include <stdio.h>
#include <math.h>


// We use a struct to organize data belonging to a point
typedef struct {
    double x;
    double y;
    double z;
} Point3D;


double euclidean_dist(Point3D a, Point3D b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}


int main() {
    Point3D a = { 5.5, 8, 9 };
    Point3D b = { 3, 5, 4.3 };
    
    printf("Distance is %g", euclidean_dist(a, b));

    return 0;
}