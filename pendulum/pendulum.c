/*
The period of a pendulum (with small angle) is given in 
https://www.acs.psu.edu/drussell/Demos/Pendulum/Pendulum.html
Given pendulum length and g, write a function to calculate the period of oscillation.
*/

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

float pendulum_period(float len)
{
    float const g = 9.81; // m/s2
    float T;

    // 0.01 to covert len from cm to m
    T = 2 * M_PI * sqrt(len*0.01/g);
   
    return T;
}

int main()
{
    float len;

    printf("Enter length of the pendulum (cm): ");
    scanf("%f", &len);

    printf("Time period of the pendulum of length %.2f cm is %.2f s",
            len, pendulum_period(len));
}