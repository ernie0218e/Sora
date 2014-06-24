#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
#include "enemy.h"
#include "bullet.h"
#include "utilize.h"
#define PI  3.141592654
#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif
inline float sq(int n){
	return n*n;
}

void updateboss(boss *);
void boss_sfire_a(boss *, bullet **, bullet **, void **, double , int , int );
void chboss(boss *, double , double );

void bossbullet_trace(bullet **bhead,bullet **btail,plane *myplane,boss *bos, int bw, int bh,void **bimg)
{
    static clock_t cur=0;
    static double bangle=0;
	if(*bhead==NULL||clock()-cur>=2000)
	{
		newbullet(bhead,btail,bos->x,bos->y,6,PI*3/2.0,bimg,(bw+bh)/4,5,bw,bh);
		cur=clock();
	}
	bullet *p=*bhead;
	while(p!=NULL)
	{
		bangle=atan2(myplane->y - p->y,myplane->x - p->x);
		chbullet(p,4,bangle);
		p=p->next;
	}
}

void bossstage_easy(bullet **bhead,bullet **btail,plane *myplane,boss *bos, int bw, int bh,void **bimg,boss_sp_bullet **head,boss_sp_bullet **tail,void **bspbimg)
{
	int    life = 10, num = 8;
	static int flag = 0, flg2 = 0,flag1=0;
	static clock_t cur = 0, t = 0, l =0, d = clock(),delay = 3000 ,enter = clock(),delay1=clock(),delay2=clock(),
		form2=clock(),form1=clock(),form3=clock(),form4=clock();
	double speed = 3, angle = 0.5*PI, dir,bangle=0;
	static double f2=0,f1=0,f3=0,f4=0;
	if(!(bos->active))
		enter = clock();
	if(clock()-enter<5000)
	{
		dir=PI*0.5;
		chboss(bos,1,dir);
		flg2=0;
		bos->active = 1;
	}
	else
	{
		bos->speed=0;
		flg2=1;
	}
	if(flg2)
	{
		if(clock()-form4>=2000)
		{
			//attack_form4 圓形 
		    while(f4<72)
            {
    	        bangle=f4/36*PI;
    	        	newbullet(bhead,btail,bos->x,bos->y,5,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	f4++;
            }
            	form4=clock();
            	f4=0; 
		}
	    if(clock()-form2>=13000)
		{
			//attack_form2  順與逆時針 
            if(f2<18)
            {
    	        bangle=f2/18*PI;
    	        if(clock()-delay2>=100)
    	        {
    	        	newbullet(bhead,btail,bos->x+bos->w/4,bos->y+20,10,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	newbullet(bhead,btail,bos->x-bos->w/4,bos->y+20,10,PI-bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	f2++;
    	            delay2=clock();
    	        }
            }
            else
            {
            	form2=clock();
            	f2=0;
            }
		}
		if(clock()-form1>=7000)
		{
			//attack_form1 雙葉順時針 
		    if(f1<36)
            {
    	        bangle=f1/36*PI;
    	        if(clock()-delay1>=100)
    	        {
    	        	newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,PI+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	f1++;
    	            delay1=clock();
    	        }
            }
            else
            {
            	form1=clock();
            	f1=0;
            } 
		}
		if(clock()-form3>=5000)
		{//attack_form3 四葉草形 
			while(f3<36)
			{
				bangle=f3/18*PI;
				newbspb(head,tail,bos->x,bos->y,clock(),bspbimg,75,75,7,8*(cos(2*bangle)),bangle,32);
				//newbullet(bhead,btail,bos->x,bos->y,8*(cos(2*bangle)),bangle,bimg,(bw+bh)/4,5,bw,bh);
				f3++;
			}
			f3=0;
			form3=clock();
		}
	}
}

void bossstage_medium(bullet **bhead,bullet **btail,plane *myplane,boss *bos, int bw, int bh,void **bimg,boss_sp_bullet **head,boss_sp_bullet **tail,void **bspbimg)
{
	int   j, life = 10, num = 8;
	static int flag = 0, flg2 = 0,flag1=0;
	static clock_t cur = 0, t = 0, l =0, delay1 = clock(),delay2 = clock(),enter = clock(),delay4=clock(),
			form1 = clock(), form2=clock(),form3=clock(),form4=clock();
	double speed = 3, angle = 0.5*PI, dir,bangle=0;
	static double f1=72,f4=0,f2=0,f3=0;
	if(!(bos->active))
		enter = clock();
	if(clock()-enter<7000)
	{
		dir=PI*0.5;
		chboss(bos,1,dir);
		flg2=0;
		bos->active = 1;
	}
	else
	{
		bos->speed=0;
		flg2=1;
	}
	if(flg2)
	{
		if(clock()-form1>=7000)
		{
			//attack_form1 雙葉逆時針 
		    if(f1>0)
            {
    	        bangle=f1/36*PI;
    	        if(clock()-delay1>=50)
    	        {
    	        	newbullet(bhead,btail,bos->x,bos->y,20,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	newbullet(bhead,btail,bos->x,bos->y,20,PI+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	f1--;
    	            delay1=clock();
    	        }
            }
            else
            {
            	form1=clock();
            	f1=72;
            } 
        }
        if(clock()-form2>=1000)
		{
			//attack_form2 踏四角 
			bangle=PI/4.0;
			if(f2<3)
			{
				if(clock()-delay2>=100)
			    {
			        newbullet(bhead,btail,bos->x,bos->y,4,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	            newbullet(bhead,btail,bos->x,bos->y,4,PI/2.0+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	            newbullet(bhead,btail,bos->x,bos->y,4,PI+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	            newbullet(bhead,btail,bos->x,bos->y,4,PI/2.0*3+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	            delay2=clock();
    	            f2++;
			    }
			}
    	    else
			{
				f2=0;
			    form2=clock();	
			}  
            	
        }
        if(clock()-form4>=13000)
        {
            //attack_form4 三葉螺旋 
			if(f4<36)
            {
    	        bangle=f4/18*PI;
    	        if(clock()-delay4>=50)
    	        {
    	        	newbullet(bhead,btail,bos->x,bos->y,6,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	newbullet(bhead,btail,bos->x,bos->y,6,2*PI/3+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	newbullet(bhead,btail,bos->x,bos->y,6,4*PI/3+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	f4++;
    	            delay4=clock();
    	        }
            }
            else
            {
            	form4=clock();
            	f4=0;
            } 	
        }
        if(clock()-form3>=19000)
        {
            //attack_form3 四葉花型  
			while(f3<36)
            {
    	        bangle=f3/18*PI;
    	        	newbspb(head,tail,bos->x,bos->y,clock(),bspbimg,81,81,8,3*(sin(2*bangle)+2),bangle,32);
    	        	newbspb(head,tail,bos->x,bos->y,clock(),bspbimg,81,81,8,3*(sin(2*bangle)+2),0.5*PI+bangle,32);
    	        	f3++;
            }
            if(f3==36)
            {
            	form3=clock();
            	f3=0;
            } 	
        }
	}
}

void bossstage_hard(bullet **bhead,bullet **btail,plane *myplane,boss *bos, int bw, int bh,void **bimg,boss_sp_bullet **head,boss_sp_bullet **tail,void **bspbimg)
{
	int    life = 10, num = 8;
	static int flag = 0, flg2 = 0,flag1=0,x,k=1,f4=1;
	static clock_t cur = 0, t = 0, l =0, delay4 = clock(),delay2=clock(),delay3=clock(),enter = clock(),change1=clock(),d=clock(),trace=clock(),
			form4=clock(),form2=clock(),form1=clock(),form3=clock();
	double speed = 3, angle = 0.5*PI, dir,bangle=0;
	static double i=0,f2=0,f1=0,f3=36,j=0;
	if(!(bos->active))
		enter = clock();
	if(clock()-enter<4000)
	{
		dir=PI*0.5;
		chboss(bos,1,dir);
		flg2=0;
		bos->active = 1;
	}
	else
	{
		bos->speed=0;
		flg2=1;
	}
	if(bos->life<500&&bos->y+bos->h/2<getmaxy()/2)
	{
		chboss(bos,1,PI*0.5);
	}
	if(flg2)
	{
		if(k)
		{
			if(clock()-form4>=2000)
		    {
			    bangle=atan2(myplane->y - bos->y,myplane->x - bos->x);
			    if(f4<6)
			    {
				    if(clock()-delay4>=100)
			        {
			            newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	                newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,PI/3.0+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	                newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,PI/3.0*2+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	                newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,PI+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	                newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,PI/3.0*4+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	                newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,PI/3.0*5+bangle,bimg,(bw+bh)/4,5,bw,bh);
    	                delay4=clock();
    	                f4++;
			        }
			    }
    	        else
			    {
				    f4=0;
			        form4=clock();	
			    }
		    }
	        if(clock()-form2>=3000)
		    {
			//attack_form2  五葉螺旋 
                if(f2<18)
                {
    	            bangle=f2/18*PI;
    	            if(clock()-delay2>=50)
    	            {
    	        	    newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle,bimg,(bw+bh)/4,5,bw,bh);
    	        	    newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle-PI/5*2,bimg,(bw+bh)/4,5,bw,bh);
    	        	    newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle-PI/5*4,bimg,(bw+bh)/4,5,bw,bh);
    	        	    newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle-PI/5*6,bimg,(bw+bh)/4,5,bw,bh);
    	        	    newbullet(bhead,btail,bos->x,bos->y+bos->h/2,6,bangle-PI/5*8,bimg,(bw+bh)/4,5,bw,bh);
    	        	    f2++;
    	                delay2=clock();
    	            }
                }
                else
                {
            	    form2=clock();
            	    f2=0;
                }
		    }
		    if(clock()-form3>=31000)
		    {
			    //attack_form3 四葉逆時針 
                if(f3>0)
                {
    	            bangle=f3/36*PI;
    	            if(clock()-delay3>=50)
    	            {
    	            	newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,bangle,32);
    	            	newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,0.5*PI+bangle,32);
    	            	newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,PI+bangle,32);
    	            	newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,1.5*PI+bangle,32);
    	        	    f3--;
    	                delay3=clock();
    	            }
                }
                else
                {
            	    form3=clock();
            	    f3=36;
                }
		    }
		}
		if(clock()-trace>=15000)//十五秒玩一次敵機追蹤玩家 
		{
			k=0;
			if(clock()-form1>=1000)
		    {
			    bangle=atan2(myplane->y - bos->y,myplane->x - bos->x);
			            newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,bangle,32);
			            newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,bangle+PI*0.5,32);
			            newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,bangle+PI,32);
			            newbspb(head,tail,bos->x,bos->y+bos->h/2,clock(),bspbimg,60,64,15,10,bangle+1.5*PI,32);
			        form1=clock();	
		    }
		    if(clock()-change1>=1000)
		    {
			    if(myplane->x-myplane->r/2>bos->x)
			    {
				    chboss(bos,20,0);
				    i=0;
			    }
			    else if(myplane->x+myplane->r/2<bos->x)
			    {
				    chboss(bos,20,PI);
				    i=0;
			    }
			    else
			    {
			        i=1;
			        f4=0;
				    change1=clock();
			    }
		    }
		    if(i)
		    {
			    if(f4<4&&!j)
				{
					if(clock()-delay4>=50)
					{
						newbullet(bhead,btail,bos->x+bos->r/5.0*f4,bos->y,15,0.5*PI,bimg,(bw+bh)/4,15,bw,bh);
				        newbullet(bhead,btail,bos->x-bos->r/5.0*f4,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				        if(f4==4)
				        {
				            newbullet(bhead,btail,bos->x+bos->r/5.0*3,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*3,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
							newbullet(bhead,btail,bos->x+bos->r/5.0*2,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*2,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
							newbullet(bhead,btail,bos->x+bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
							newbullet(bhead,btail,bos->x,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);	
				        }
				        if(f4==2)
				        {
				        	newbullet(bhead,btail,bos->x+bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				        }
				        f4++;
				        delay4=clock();
					}
				}
				else
				{
					j=1;
				}
			    if(j&&f4>0)
			    {
					if(clock()-delay4>=50)
					{
						newbullet(bhead,btail,bos->x+bos->r/5.0*f4,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				        newbullet(bhead,btail,bos->x-bos->r/5.0*f4,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				        if(f4==4)
				        {
				            newbullet(bhead,btail,bos->x+bos->r/5.0*3,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*3,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
							newbullet(bhead,btail,bos->x+bos->r/5.0*2,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*2,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
							newbullet(bhead,btail,bos->x+bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
							newbullet(bhead,btail,bos->x,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);	
				        }
				        if(f4==2)
				        {
				        	newbullet(bhead,btail,bos->x+bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x-bos->r/5.0*1,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				            newbullet(bhead,btail,bos->x,bos->y,15,0.5*PI,bimg,(bw+bh)/4,5,bw,bh);
				        }
				        f4--;
				        delay4=clock();
					}
			    }
		 	    else
			    {
				    j=0;
			    }
		    }
			if(clock()-trace>=25000)
			{
				trace=clock();
				k=1;
			}	
		}
		
	}
}

void updateboss(boss *bos)
{
    int maxx,maxy;
    maxx = getmaxx();
    maxy = getmaxy();
    if(bos->life>0)
    {
    	bos->x+=(int) ((bos -> speed)*cos(bos -> angle));
        bos->y+=(int) ((bos -> speed)*sin(bos -> angle));
        putimage(bos -> x - bos->w/2, bos -> y - bos->h/2, bos -> img[1], 3);
	    putimage(bos -> x - bos->w/2, bos -> y - bos->h/2, bos -> img[0], 2);
    }
}

void boss_sfire_a(boss *plane, bullet **head, bullet **tail, void **img, double bangle, int bw, int bh){
	int val = 4;
	double speed = 40, angle = bangle, r = (bw + bh) / 4.0;
	newbullet(head, tail, plane-> x, plane -> y , speed, angle, img, r, val, bw, bh);
}

void chboss(boss *thisenemy, double speed, double angle){ //change the value of boss
	thisenemy -> speed = speed;
	thisenemy -> angle = angle;
}
