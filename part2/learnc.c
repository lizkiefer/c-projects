/*
*learnc.c / Practice Assigment/ Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 24, 2024
*
*/

#include <stdio.h>
#include "mpg2km.h"

int main()
{
    printf("%.2lf mpg = %.2lf km per liter\n", 1.0, mpg2kml(1.0));
    printf("%.2lf mpg = %.2lf km per liter\n", 100.0, mpg2kml(100.0));
    
    printf("%.2lf mpg = %.2lf liters per 100 km\n", 1.0, mpg2lphm(1.0));
    printf("%.2lf mpg = %.2lf liters per 100 km\n", 100.0, mpg2lphm(100.0));
    
    printf("%.2lf liters per 100 km = %.2lf mpg\n", 1.0, lph2mpg(1.0));
    printf("%.2lf liters per 100 km = %.2lf mpg\n", 100.0, lph2mpg(100.0));
    return 0;
}
