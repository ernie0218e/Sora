#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

void p_move(plane *, int);

void p_nfire(plane *, bullet **, bullet **, void **, int, int, int);

void p_sfire_a(plane *, bullet **, bullet **, void **, int, int, int, int *);

void updateplane(plane *, int *, int *, int);
