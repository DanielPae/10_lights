#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmath.h"
#include "matrix.h"
#include "ml6.h"

//lighting functions
color get_lighting( double *normal, double *view, color alight, double light[2][3], double *areflect, double *dreflect, double *sreflect) {
  color i;
  return i;
}

color calculate_ambient(color alight, double *areflect ) {
  color a;
  a.red = alight.red * areflect[0];
  a.blue = alight.blue * areflect[0];
  a.green = alight.green * areflect[0];
  return a;
}

color calculate_diffuse(double light[2][3], double *dreflect, double *normal ) {
  color d;
  double dot = dot_product(light[LOCATION], normal);
  d.red = p[COLOR][RED] * dreflect[RED] * dot;
  d.red = p[COLOR][BLUE] * dreflect[BLUE] * dot;
  d.red = p[COLOR][GREEN] * dreflect[GREEN] * dot;
  return d;
}

color calculate_specular(double light[2][3], double *sreflect, double *view, double *normal ) {
  color s;
  
  return s;
}


//limit each component of c to a max of 255
void limit_color( color * c ) {
  if(c.red > 255) c.red == 255;
  if(c.blue > 255) c.blue == 255;
  if(c.green > 255) c.green == 255;
}

//vector functions
//normalize vetor, should modify the parameter
void normalize( double *vector ) {
  double mag = sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));
  vector[0] = vector[0] / mag;
  vector[1] = vector[1] / mag;
  vector[2] = vector[2] / mag;
}

//Return the dot porduct of a . b
double dot_product( double *a, double *b ) {
  double tot;
  tot = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
  return tot;
}

double *calculate_normal(struct matrix *polygons, int i) {

  double A[3];
  double B[3];
  double *N = (double *)malloc(3 * sizeof(double));

  A[0] = polygons->m[0][i+1] - polygons->m[0][i];
  A[1] = polygons->m[1][i+1] - polygons->m[1][i];
  A[2] = polygons->m[2][i+1] - polygons->m[2][i];

  B[0] = polygons->m[0][i+2] - polygons->m[0][i];
  B[1] = polygons->m[1][i+2] - polygons->m[1][i];
  B[2] = polygons->m[2][i+2] - polygons->m[2][i];

  N[0] = A[1] * B[2] - A[2] * B[1];
  N[1] = A[2] * B[0] - A[0] * B[2];
  N[2] = A[0] * B[1] - A[1] * B[0];

  return N;
}
