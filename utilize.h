#include <time.h>
#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

void play_bgm(char *);

void restart_bgm(char *);

void change_bgm(char *, char *);

void close_bgm(char *);

void score(long);

void life(long, long);

void boss_life(long, long);

void background(void *, void *, int, int);

void spbullet(long, int *, int, int);

void newexplosion(int, int, clock_t, void **, int, int, int);

void deleteexplosion(explosion *);

void updateexplosion(void);

void deleteall(void);

void updateexplosion(void);

void cloudinit(cloud *, int);

void newcloud(cloud *, int);

void upcloud(cloud *, int);

void belowcloud(cloud *, int);

void name_enter(long, int);

void save_record(char *, long, int);

void cal_record();

void load_record(char ***, int &, int **);

void newhp(void **, int, int, lifeplus **, lifeplus **, int, int);

void deletehp(lifeplus *, lifeplus **, lifeplus **);

void changehp(lifeplus *, double, double);

void updatehp(lifeplus **,lifeplus **,plane *);

void deleteall(lifeplus **head,lifeplus **tail);

void newspbp(void **, int, int, spbulletplus **, spbulletplus **, int, int);

void deletespbp(spbulletplus *, spbulletplus **, spbulletplus **);

void changespbp(spbulletplus *, double, double);

int updatespbp(spbulletplus **, spbulletplus **, plane *);

void deleteall(spbulletplus **,spbulletplus **);

void newbspb(boss_sp_bullet **,boss_sp_bullet **,int , int , clock_t , void **, int , int , int , double , double ,double );

void deletebspb(boss_sp_bullet *,boss_sp_bullet **,boss_sp_bullet **);

void updatebspb(boss_sp_bullet **,boss_sp_bullet **);

void deleteall(boss_sp_bullet **,boss_sp_bullet **);
