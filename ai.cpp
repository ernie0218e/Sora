#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
#include "enemy.h"
#include "collision.h"
#include "bullet.h"
#define PI  3.141592654
#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

inline float fsqrt(float n){
	float x=n;
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	int ma = 0x5f375a86;
	i = ma - (i>>1); 
	x = *(float*)&i;
	x = x*(1.5f-xhalf*x*x);
	x = x*(1.5f-xhalf*x*x);
	x = x*(1.5f-xhalf*x*x); 
	return 1/x;
}

inline float sq(int n){
	return n*n;
}



void easy(enemy **head, enemy **tail, void **eimg, int ew, int eh, bullet **bhead, bullet **btail, void **bimg, int bw, int bh){
	int  i, j, life = 10, num = 4, *x, pos = 0;
	static int flag = 0, flg2 = 0;
	static clock_t cur = 0, t = 0, l = clock(), d = clock(),delay = 3000, init = 800 ,change = 1600, leave = 10000,
			bt = 0, bdelay = 800;
	double speed = 3, angle = 0.5*PI, r = (ew + eh)/4.0, dir;
	enemy *ptr = *head;
	
	x = new int [getmaxx() / ew];
	for(i = 0;i < getmaxx() / ew;i++)
		x[i] = 0;
	
	if(!checkenemy(*head) && clock() - cur > delay){
			for(i = 0;i < num;i++){
				pos = rand()%(getmaxx() / ew);
				while(x[pos] != 0)
					pos = rand()%(getmaxx() / ew);
				x[pos] = 1;
				newenemy(head, tail, pos*ew + ew/2, -eh/3, speed, angle, life, eimg, r, ew, eh, 1);
			}
		cur = clock();
		l = clock();
		d = clock();
		flag = 0;
		delete []x;
	}
	
	ptr = *head;
	
	if(clock() - l < leave && !flag){
		if(clock() - d > init){
			while(ptr != NULL){
				if(clock() - t > change){
					dir = 2.0 * (double)rand()/(double)(RAND_MAX-1) *PI;
					chenemy(ptr, speed, dir);
					flg2 = 1;
				}else
				if(ptr -> y + r > getmaxy()/2){
					ptr -> y = getmaxy()/2 - r;
					dir = 2.0 * PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}else if(ptr -> y - r < 0){
					ptr -> y = r;
					dir = 2.0 * PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}else if(ptr -> x + r > getmaxx()){
					ptr -> x = getmaxx() - r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}else if(ptr -> x - r < 0){
					ptr -> x = r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}
				ptr = ptr -> next;
			}
			if(flg2){
				t = clock();
				flg2 = 0;
			}
		}
		
	}else if(!flag){
		flag = 1;
		while(ptr != NULL){
			dir = 0.5 * (double)rand()/(double)(RAND_MAX-1) + 0.25;
			chenemy(ptr, speed+2, dir * PI);
			ptr = ptr -> next;
		}
	}
	
	ptr = *head;
	if(clock() - bt > bdelay){
		while(ptr != NULL){
			if(rand()%2)
				e_nfire(ptr, bhead, btail, bimg, bw, bh);
			else if(!(rand()%5))
				e_sfire_a(ptr, bhead, btail, bimg, bw, bh);
			ptr = ptr -> next;
		}
	 	bt = clock();
	}
}

void medium_ai(plane *myplane, enemy **head, enemy **tail, void **eimg, int ew, int eh, bullet **bhead, bullet **btail, void **bimg, int bw, int bh){
	int i, *x, pos = 0;
	const int life = 20, num = 4;
	static int flg = 0, bflg = 0;
	static clock_t cur = 0, d = 0, t = 0, bt = 0, bd = 0;
	const clock_t delay = 1500, init = 600, change = 1500, bdelay = 1500, bfdelay = 100;
	double angle = 0.5*PI, r = (ew + eh)/4.0, ispeed = 1, speed = 4, bangle;
	double dir = 0;
	enemy *ptr = *head;
	
	x = new int [getmaxx() / ew];
	for(i = 0;i < getmaxx() / ew;i++)
		x[i] = 0;
	
	if(!checkenemy(*head) && clock() - cur > delay){
			for(i = 0;i < num;i++){
				pos = rand()%(getmaxx() / ew);
				while(x[pos] != 0)
					pos = rand()%(getmaxx() / ew);
				x[pos] = 1;
				newenemy(head, tail, pos*ew/2 + ew/2, -eh/3, ++ispeed, angle, life, eimg, r, ew, eh, 3);
			}
		cur = clock();
		d = clock();
		flg = 0;
	}
	
	if(clock() - d > init){
		while(ptr != NULL){
			if(!flg){
				dir = -dir + 1;
				chenemy(ptr, speed, dir*PI);
			}
			if(ptr -> y + r > getmaxy()/2){
				ptr -> y = getmaxy()/2 - r;
				dir = 2.0 * PI - ptr -> angle;
				chenemy(ptr, speed, dir);
			}else if(ptr -> y - r < 0){
				ptr -> y = r;
				dir = 2.0 * PI - ptr -> angle;
				chenemy(ptr, speed, dir);
			}else if(ptr -> x + r > getmaxx()){
				ptr -> x = getmaxx() - r;
				if(ptr -> angle > PI)
					dir = 3.0*PI - ptr -> angle;
				else
					dir = PI - ptr -> angle;
				chenemy(ptr, speed, dir);
			}else if(ptr -> x - r < 0){
				ptr -> x = r;
				if(ptr -> angle > PI)
					dir = 3.0*PI - ptr -> angle;
				else
					dir = PI - ptr -> angle;
				chenemy(ptr, speed, dir);
			}
			ptr = ptr -> next;
		}
		flg = 1;
	}
	
	ptr = *head;
	if(clock() - bt > bdelay){
		while(ptr != NULL){
			if(!(rand()%5)){
				ptr -> fire = 1;
				ptr -> fcount = 0;
			}
			ptr = ptr -> next;
		}
	 	bt = clock();
	}
	if(clock() - bd > bfdelay){
		ptr = *head;
		while(ptr != NULL){
			if(ptr -> fire && ptr -> fcount < 5){
				bangle = acos((myplane -> x - ptr -> x)/fsqrt(sq(myplane -> x - ptr -> x)+sq(myplane -> y - ptr -> y)));
				if(myplane -> y - ptr -> y < 0)
					bangle = 2 * PI - bangle;
				e_sfire_b(ptr, bhead, btail, bimg, bangle, bw, bh);
				ptr -> fcount += 1;
			}else if(ptr -> fcount > 5)
				ptr -> fire = 0;
			ptr = ptr -> next;
		}
		bd = clock();
	}
}


void medium(plane *myplane, enemy **head, enemy **tail, void **eimg, int ew, int eh)
{
	int  i, j, life = 15;
	static clock_t cur = 0, t = 0, l = clock();
	const static clock_t delay = 5000;
	double speed = 3, angle = 0.5*PI, r = (ew + eh)/4.0, dir;
	enemy *ptr = *head;
	
	if(!checkenemy(*head))
	{
			i = rand()%getmaxx();
				while(i <= r || i >= getmaxx()-r)
					i = rand()%getmaxx();
		newenemy(head, tail, i, 50, speed, angle, life, eimg, r, ew, eh, 2);
		cur = clock();

	}
	else if(clock()-cur>delay)//每五秒出現一次 
	{
		i = rand()%getmaxx();
				while(i <= r || i >= getmaxx()-r)
					i = rand()%getmaxx();
		newenemy(head, tail, i, 50, speed, angle, life, eimg, r, ew, eh, 2);
		cur=clock();

	}
	while(ptr != NULL)
	{
				if(ptr -> y + r > getmaxy()){
					ptr -> y = getmaxy() - r;
					dir = 2.0 * PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}else if(ptr -> y - r < 0){
					ptr -> y = r;
					dir = 2.0 * PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}else if(ptr -> x + r > getmaxx()){
					ptr -> x = getmaxx() - r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}else if(ptr -> x - r < 0){
					ptr -> x = r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					chenemy(ptr, speed, dir);
				}
				else
				{
					dir=atan2(myplane->y - ptr->y,myplane->x - ptr->x);//追蹤我方 
					chenemy(ptr, speed, dir);
				}
				ptr = ptr -> next;

	}
}

void high_ai(plane *myplane, bullet *ebhead, enemy **head, enemy **tail, void **eimg, int ew, int eh, bullet **bhead, bullet **btail, void **bimg, int bw, int bh){
	int i, *x, pos = 0 , flg2 = 0;
	const int life = 30, num = 4;
	static int flg = 0, bflg = 0;
	static clock_t cur = 0, d = 0, t = 0, bt = 0, bd = 0;
	const clock_t delay = 1500, init = 200, change = 1500, bdelay = 2000, bfdelay = 200;
	double angle = 0.5*PI, r = (ew + eh)/4.0, ispeed = 1, speed = 4, bangle, bdr = r + 100;
	double dir = 0, ddir, dangle, dirp = 0;
	
	enemy *ptr = *head, *eptr = *head;
	bullet *ebptr = ebhead;
	
	x = new int [getmaxx() / ew];
	for(i = 0;i < getmaxx() / ew;i++)
		x[i] = 0;
	
	if(!checkenemy(*head) && clock() - cur > delay){
			for(i = 0;i < num;i++){
				pos = rand()%(getmaxx() / ew);
				while(x[pos] != 0)
					pos = rand()%(getmaxx() / ew);
				x[pos] = 1;
				newenemy(head, tail, pos*ew/2 + ew/2, -eh/3, speed, angle, life, eimg, r, ew, eh, 5);
			}
		cur = clock();
		d = clock();
		flg = 0;
		delete []x;
	}
	
	if(clock() - d > init){

		ptr = *head;
		while(ptr != NULL){
			if(ptr -> y + r > getmaxy()){
				ptr -> y = getmaxy() - r;
				dir = 2.0 * PI - ptr -> angle;
				chenemy(ptr, speed, dir);
			}else if(ptr -> y - r < 0){
				ptr -> y = r;
				dir = 2.0 * PI - ptr -> angle;
				chenemy(ptr, speed, dir);
			}else if(ptr -> x + r > getmaxx()){
				if(ptr -> angle > PI)
					dir = 3.0*PI - ptr -> angle;
				else
					dir = PI - ptr -> angle;
				ptr -> x = getmaxx() - r - speed;
				chenemy(ptr, speed, dir);
			}else if(ptr -> x - r < 0){
				if(ptr -> angle > PI)
					dir = 3.0*PI - ptr -> angle;
				else
					dir = PI - ptr -> angle;
				ptr -> x = r + speed;
				chenemy(ptr, speed, dir);
			}else{
				ebptr = ebhead;
				while(ebptr != NULL){
					if(sq(ptr -> x - ebptr -> x) + sq(ptr -> y - ebptr -> y) < sq(bdr)){
						if(ptr -> y - ebptr -> y < 0){
							ddir = fabs(((ebptr -> x - ptr -> x)*cos(ebptr -> angle) + (ebptr -> y - ptr -> y)*sin(ebptr -> angle))/fsqrt(sq(ptr -> x - ebptr -> x) + sq(ptr -> y - ebptr -> y)));
							dangle = fsqrt(sq(ptr -> x - ebptr -> x) + sq(ptr -> y - ebptr -> y) - sq(r+5) - sq(ebptr -> r))/fsqrt(sq(ptr -> x - ebptr -> x) + sq(ptr -> y - ebptr -> y));
							if(ddir >= dangle){
								if((ebptr -> x - ptr -> x) > 0)
									ddir = ebptr -> angle + acos(ddir);
								else
									ddir = ebptr -> angle - acos(ddir);
								if(ddir > 1.5*PI)
									dir = (ddir - 0.5*PI);
								else if(ddir > PI)
									dir = (ddir + 0.5*PI);
								if(!flg2)
									dirp = dir;
								else{
									dir = acos((cos(dirp) + cos(dir))/fsqrt(sq(cos(dirp) + cos(dir))+sq(sin(dirp) + sin(dir))));
									dirp = dir;
									flg2 = 1;
								}
								ispeed = 5;
								chenemy(ptr, ispeed, dir);
							}
						}
					}
						
					ebptr = ebptr -> next;
				}
			}
			flg2 = 0;
			ptr = ptr -> next;
		}
	}
	
	ptr = *head;
	if(clock() - bt > bdelay){
		while(ptr != NULL){
			if(!(rand()%5)){
				ptr -> fire = 1;
				ptr -> fcount = 0;
			}
			ptr = ptr -> next;
		}
	 	bt = clock();
	}
	
	if(clock() - bd > bfdelay){
		ptr = *head;
		while(ptr != NULL){
			if(ptr -> fire && ptr -> fcount < 5){
				bangle = acos((myplane -> x - ptr -> x)/fsqrt(sq(myplane -> x - ptr -> x)+sq(myplane -> y - ptr -> y)));
				if(myplane -> y - ptr -> y < 0)
					bangle = 2 * PI - bangle;
				e_sfire_b(ptr, bhead, btail, bimg, bangle, bw, bh);
				ptr -> fcount += 1;
			}else if(ptr -> fcount > 5)
				ptr -> fire = 0;
			ptr = ptr -> next;
		}
		bd = clock();
	}
	
}


void trace(enemy **head, enemy **tail, bullet **bhead, bullet **btail, void **bimg, int bw, int bh, void **eimg, int ew, int eh,plane *myplane)
{
	int i, *x, pos = 0;
	const int life = 20;
	static clock_t cur = 0;
	const clock_t delay = 1000;
	double angle = 0.5*PI, r = (ew + eh)/4.0, speed = 4, bangle=0.5*PI;
	double dir = 0;
	enemy *ptr = *head;
	
	if(!checkenemy(*head)||clock()-cur>delay)//每五秒出現一次 
	{
			i = rand()%getmaxx();
				while(i <= r || i >= getmaxx()-r)
					i = rand()%getmaxx();
		newenemy(head, tail, i, 40, speed, angle, life, eimg, r, ew, eh,4);
		cur = clock();
	}
	ptr=*head;
	while(ptr != NULL)
	{
		if(ptr -> y + r > getmaxy()/4)
		{
			dir = 2.0 * PI - ptr -> angle;
			e_sfire_b(ptr, bhead, btail, bimg, bangle, bw, bh);
			chenemy(ptr, speed, dir);
		}
		ptr = ptr -> next;
	}
}

void trace_bullet(bullet *bhead,plane *myplane)
{
	double bangle;
	bullet *p=bhead;
	while(p!=NULL)
	{
		bangle=atan2(myplane->y - p->y,myplane->x - p->x);
		chbullet(p,4,bangle);
		p=p->next;
	}
}
