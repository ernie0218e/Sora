#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif


void bossstage_hard(bullet **,bullet **,plane *,boss *, int, int,void **,boss_sp_bullet **,boss_sp_bullet **,void **);

void updateboss(boss *);

void chboss(boss *, double , double );

void bossstage_medium(bullet **,bullet **,plane *,boss *, int , int ,void **,boss_sp_bullet **,boss_sp_bullet **,void **);

void bossstage_easy(bullet **,bullet **,plane *,boss *, int, int,void **,boss_sp_bullet **,boss_sp_bullet **,void **);

void bossbullet_trace(bullet **,bullet **,plane *,boss *, int , int ,void **);
