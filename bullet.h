#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

//generate bullet list
//need two pointer to indicate head and tail of the linked-list
void newbullet(bullet **, bullet **, int, int, double, double, void **, double, int, int, int);

/*delete current bullet
Caution!! will change the start of the linked-list*/
void deletebullet(bullet *, bullet **, bullet **);	

/*update the postion of the bullet (include boundary detection)
Caution!! will change the start of the linked-list*/
void updatebullet(bullet **, bullet **);

//delete all bullet
void deleteall(bullet **, bullet **);

//change the value of one bullet
void chbullet(bullet *, double, double);

//change the value of all bullet
void chabullet(bullet *, double, double);
