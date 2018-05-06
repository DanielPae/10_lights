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
  //printf("%d %d %d\n", a.red, a.blue, a.green);
  limit_color(&a);
  return a;
}

color calculate_diffuse(double light[2][3], double *dreflect, double *normal ) {
  color d;
  normalize(normal);
  double dot = dot_product(light[LOCATION], normal);
  d.red = (int)(light[COLOR][RED] * dreflect[RED] * dot);
  d.blue = (int)(light[COLOR][BLUE] * dreflect[BLUE] * dot);
  d.green = (int)(light[COLOR][GREEN] * dreflect[GREEN] * dot);
  //printf("%d %d %d\n", d.red, d.blue, d.green);
  limit_color(&d);
  return d;
}

color calculate_specular(double light[2][3], double *sreflect, double *view, double *normal ) {
  color s;
  normalize(normal);
  normalize(light[LOCATION]);
  normalize(view);
  double dotnl = dot_product(light[LOCATION], normal);
  normal[0] = normal[0] * dotnl;
  normal[1] = normal[1] * dotnl;
  normal[2] = normal[2] * dotnl;
  //printf("1 : %lf %lf %lf\n", normal[0], normal[1], normal[2]);
  normal[0] = normal[0] * 2;
  normal[1] = normal[1] * 2;
  normal[2] = normal[2] * 2;
  //printf("2 : %lf %lf %lf\n", normal[0], normal[1], normal[2]);
  normal[0] = normal[0] - light[LOCATION][0];
  normal[1] = normal[1] - light[LOCATION][1];
  normal[2] = normal[2] - light[LOCATION][2];
  //printf("3 : %lf %lf %lf\n", normal[0], normal[1], normal[2]);
  double dotnv = dot_product(view, normal);
  s.red = (int)(light[COLOR][RED] * sreflect[RED] * dotnv);
  s.blue = (int)(light[COLOR][BLUE] * sreflect[BLUE] * dotnv);
  s.green = (int)(light[COLOR][GREEN] * sreflect[GREEN] * dotnv);
  //printf("4 : %lf %lf\n", dotnl, dotnv);
  limit_color(&s);
  //printf("%d %d %d\n\n", s.red, s.blue, s.green);
  return s;
}


//limit each component of c to a max of 255
void limit_color( color * c ) {
  if(c->red > 255) c->red = 255;
  if(c->blue > 255) c->blue = 255;
  if(c->green > 255) c->green = 255;
  if(c->red < 0) c->red = 0;
  if(c->blue < 0) c->blue = 0;
  if(c->green < 0) c->green = 0;
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
