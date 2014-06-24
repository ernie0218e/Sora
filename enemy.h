#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

void newenemy(enemy **, enemy **, int, int, double, double, int, void **, double, int, int, int);

void deleteenemy(enemy *, enemy **, enemy **);

void updateenemy(enemy **, enemy **);

void deleteall(enemy **, enemy **);

void chenemy(enemy *, double, double);

void chaenemy(enemy *, double, double);

int checkenemy(enemy *);

void e_nfire(enemy *, bullet **, bullet **, void **, int, int);

void e_sfire_a(enemy *, bullet **, bullet **, void **, int, int);

void e_sfire_b(enemy *, bullet **, bullet **, void **, double, int, int);
