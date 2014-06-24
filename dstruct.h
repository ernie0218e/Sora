#include <time.h>

struct bullet{
    int x;			//current pos(center of the image)
    int y;
    double speed;	
    double angle;	
    int val;		//value of power
    void **img;		//lots of image
    double r;		//collision range
    int w;			//width & height of the image
    int h;
    struct bullet *previous;	//double linked list
    struct bullet *next;
};

struct enemy{
	int type;		//enemy type
	int x;			//current pos(center of the image)
	int y;
	double speed;
	double angle;
	int life;		//value of life
	void **img;		//lots of image
	double r;		//collision range
	int w;			//width & height of the image
    int h;
    int fire;
    int fcount;
	struct enemy *previous;		//double linked list
	struct enemy *next;
};

struct plane{
	int x;		//current pos(center of the image)
	int y;
	int life;	//value of life
	void **img;	//lots of image
	double r;	//collision range
	int w;		//width & height of the image
	int h;
};

struct boss{
	int x;		//curren pos(center of the image)
	int y;	
	int life;	//value of life
	void **img;	//image
	double r;	//collision range
	double speed;
	double angle;
	int w;		//width & height of the image
    int h;
    int active;
};

struct cloud{
	int x;		//curren pos(center of the image)
	int y;
	double speed;	//scroll speed
	int w;			//width & height of the image
	int h;
	void **img;	 //image
	int active;		//active or not
	int alt;		//altitude
};

struct explosion{
	int x;		//curren pos(center of the image)
	int y;
	clock_t time;	//previous time
	void **img;	 //image
	int w;			//width & height of the image
	int h;
	int frame;		//current frame
	int tframe;		//total frame
	struct explosion *previous;	//double linked list
    struct explosion *next;
};

struct lifeplus
{
	int x;		//curren pos(center of the image)
	int y;	
	void **img;	 //image
	int w;			//width & height of the image
	int h;
	double r;
	double angle;
	double speed;
	struct lifeplus *previous;	//double linked list
    struct lifeplus *next; 
};

struct spbulletplus
{
	int x;		//curren pos(center of the image)
	int y;	
	void **img;	 //image
	int w;			//width & height of the image
	int h;
	double r;
	double angle;
	double speed;
	struct spbulletplus *previous;	//double linked list
    struct spbulletplus *next; 
};

struct boss_sp_bullet{
	int x;		//curren pos(center of the image)
	int y;
	clock_t time;	//previous time
	void **img;	 //image
	int w;			//width & height of the image
	int h;
	double r;
	double angle;
	double speed;
	int frame;		//current frame
	int tframe;		//total frame
	struct boss_sp_bullet *previous;	//double linked list
    struct boss_sp_bullet *next;
};
