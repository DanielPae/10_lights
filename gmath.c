#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmath.h"
#include "matrix.h"
#include "ml6.h"

//lighting functions
color get_lighting( double *normal, double *view, color alight, double light[2][3], double *areflect, double *dreflect, double *sreflect) {
  color i, a, d, s;
  a = calculate_ambient(alight, areflect);
  d = calculate_diffuse(light, dreflect, normal);
  s = calculate_specular(light, sreflect, view, normal);
  i.red = a.red + d.red + s.red;
  i.blue = a.blue + d.blue + s.blue;
  i.green = a.green + d.green + s.green;
  return i;
}

color calculate_ambient(color alight, double *areflect ) {
  color a;
  a.red = alight.red * areflect[RED];
  a.blue = alight.blue * areflect[BLUE];
  a.green = alight.green * areflect[GREEN];
  return a;
}

color calculate_diffuse(double light[2][3], double *dreflect, double *normal ) {
  color d;
  double dot = dot_product(light[LOCATION], normal);
  d.red = light[COLOR][RED] * dreflect[RED] * dot;
  d.red = light[COLOR][BLUE] * dreflect[BLUE] * dot;
  d.red = light[COLOR][GREEN] * dreflect[GREEN] * dot;
  return d;
}

color calculate_specular(double light[2][3], double *sreflect, double *view, double *normal ) {
  color s;
  double dotnl = dot_product(light[LOCATION], normal);
  normal[0] *= 2 * dotnl;
  normal[1] *= 2 * dotnl;
  normal[2] *= 2 * dotnl;
  normal[0] -= light[LOCATION][0];
  normal[1] -= light[LOCATION][1];
  normal[2] -= light[LOCATION][2];
  double dotnv = dot_product(view, normal);
  s.red = sreflect[RED] * dotnv;
  s.blue = sreflect[BLUE] * dotnv;
  s.green = sreflect[GREEN] * dotnv;
  printf("%lf %lf %lf\n", s.red, s.blue, s.green);
  return s;
}


//limit each component of c to a max of 255
void limit_color( color * c ) {
  if(c->red > 255) c->red = 255;
  if(c->blue > 255) c->blue = 255;
  if(c->green > 255) c->green = 255;
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
