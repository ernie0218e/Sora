#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

void d_attack(bullet **, bullet **, enemy **, enemy **);

void d_beattack(bullet **, bullet **, plane *);

void d_crash(enemy **, enemy **, plane *);

void bullet_collision(bullet **,bullet **);

void mbullet_ebullet_collision(bullet **,bullet **,bullet **,bullet **);

void d_battack(bullet **, bullet **,boss *);

void d_bcrash(boss *, plane *);

void d_beattack_bspb(boss_sp_bullet **,boss_sp_bullet **, plane *);
