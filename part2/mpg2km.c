/*
*mpg2km.c / Practice Assigment/ Program in C
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Sep 24, 2024
*
*/

// Converts mpg to kilometers per liter
// Returns: (double) kilometers per liter
double mpg2kml(double mpg)
{
    return mpg * 1.609 / 3.785;
}

// Converts mpg to liters per 100 kilometers
// Returns: (double) liters per 100 kilometers
double mpg2lphm(double mpg)
{
    return 235.215 / mpg;
}

// Converts liters per 100 kilometers to mpg
// Returns: (double) mpg
double lph2mpg(double lph)
{
    return 235.215 / lph;
}
