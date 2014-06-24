#include "bullet.h"
#include "boss.h"
#include "enemy.h"
#include "plane.h"
#include "utilize.h"
#include <stdlib.h>
#include <graphics.h>
#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif

extern long sc;
extern explosion *exhead,*extail;
extern void **eximg;

inline float sq(int n){
	return n*n;
}

int type_reward(enemy *thisenemy){
	
	switch(thisenemy -> type){
		case 1:
			return 100;
		case 2:
			return 150;
		case 3:
			return 200;
		case 4:
			return 250;
		case 5:
			return 300;
	}
	
}

int type_hurt(enemy *thisenemy){
	
	switch(thisenemy -> type){
		case 1:
			return 10;
		case 2:
			return 15;
		case 3:
			return 20;
		case 4:
			return 25;
		case 5:
			return 30;
	}
}

void d_attack(bullet **bfirst, bullet **btail, enemy **efirst, enemy **etail){
	bullet *bptr = *bfirst, *bbuffer;
	enemy *eptr = *efirst, *ebuffer;
	int flag = 0, c = 1;
	while(bptr != NULL){
		eptr = *efirst;
		while(eptr != NULL && bptr != NULL){
			if(sq(eptr -> x - bptr -> x) + sq(eptr -> y - bptr -> y) < sq(eptr -> r + bptr -> r)){
				eptr -> life -= bptr -> val;

				if(eptr -> life <= 0){

					PlaySound(".\\music\\explosion1.wav",NULL, SND_FILENAME|SND_ASYNC);
					newexplosion(eptr -> x, eptr -> y,clock(),eximg,64,64,14);
					sc += type_reward(eptr);
					ebuffer = eptr;
					eptr = eptr -> next;
					deleteenemy(ebuffer, efirst, etail);
				}else{
					sc += type_hurt(eptr);
					eptr = eptr -> next;
				}
					
				bbuffer = bptr;
				bptr = bptr -> next;
				deletebullet(bbuffer, bfirst, btail);
				flag = 1;
			}else
				eptr = eptr -> next;
		}
		if(flag){
			flag = 0;
		}else
			bptr = bptr -> next;
	}
}

void d_beattack(bullet **first, bullet **tail, plane *myplane){
	bullet *ptr = *first, *buffer;
	while(ptr != NULL){
		if(sq(ptr -> x - myplane -> x) + sq(ptr -> y - myplane -> y) < sq(ptr -> r + myplane -> r)){
			myplane -> life -= ptr -> val;

			buffer = ptr;
			ptr = ptr -> next;
			deletebullet(buffer, first, tail);
		}else
			ptr = ptr -> next;
	}
}

void d_crash(enemy **first, enemy **tail, plane *myplane){
	enemy *ptr = *first, *buffer;
	const int val = 10;
	while(ptr != NULL){
		if(sq(ptr -> x - myplane -> x)+sq(ptr -> y - myplane -> y) < sq(ptr -> r + myplane -> r)){
			myplane -> life -= val;
			ptr -> life -= val;
			
			if(ptr -> life <= 0){

				newexplosion(ptr -> x, ptr -> y,clock(),eximg,64,64,14);
				sc += type_reward(ptr) - 50;
				buffer = ptr;
				ptr = ptr -> next;
				deleteenemy(buffer, first, tail);
			}else
				ptr = ptr -> next;
			
		}else
			ptr = ptr -> next;
	}
}

void bullet_collision(bullet **first,bullet **tail)
{
	int flag=1;
	bullet *ptr = *first,*p,*p1;
	p=ptr;
	while(ptr!=NULL)
	{
		p=*first;
		while(p!=NULL)
		{
			if(p!=ptr)
			{
				if(sq(ptr -> x - p -> x)+sq(ptr -> y - p -> y) < sq(ptr -> r + p -> r))
				{
					sc++;
					if(p==ptr->next)//如果p為ptr的下一個，新的ptr應為p的下一個 
					    p1=p->next;
					else//否則新的ptr為ptr的下一個 
					    p1=ptr->next;
					deletebullet(ptr, first, tail);
					deletebullet(p, first, tail);
					ptr=p1;
					if(ptr!=NULL)
					    p=ptr->next;
					else
					    p=NULL;
				}
				else
				p=p->next;
			}
			else
			p=p->next;
		}
		if(ptr!=NULL)
		ptr=ptr->next;
	}
}

void mbullet_ebullet_collision(bullet **eh,bullet **et,bullet **mh,bullet **mt)//(敵方子彈頭,敵方子彈尾,我方子彈頭,我方子彈尾)
{
	bullet *ptr = *mh,*p,*pe,*pm;
	p=*eh;
	while(ptr!=NULL)
	{
		p=*eh;
		while(p!=NULL)
		{
			if(sq(ptr -> x - p -> x)+sq(ptr -> y - p -> y) < sq(ptr -> r + p -> r))
			{
				sc++;
				pm=ptr->next;
				pe=p->next;	
				deletebullet(ptr, mh, mt);
				deletebullet(p, eh, et);
				ptr=pm;
				if(ptr!=NULL)
				p=pe;
				else
				p=NULL;
			}
			else
			p=p->next;
		}
		if(ptr!=NULL)
		ptr=ptr->next;
	}
}



void d_battack(bullet **first, bullet **tail,boss *mao){
	bullet *ptr = *first, *buffer;
	while(ptr != NULL){
			if(sq(ptr -> x - mao -> x) + sq(ptr -> y - mao -> y) < sq(ptr -> r + mao -> r)){
				mao -> life -= ptr -> val;
				
				buffer = ptr;
				ptr = ptr -> next;
				deletebullet(buffer, first, tail);
			}else
				ptr = ptr -> next;
	}
}

void d_bcrash(boss *mao, plane *myplane){
	const int val = 10;
	if(sq(mao -> x - myplane -> x)+sq(mao -> y - myplane -> y) < sq(mao -> r + myplane -> r)){
			myplane -> life -= val;

	}
}

void d_beattack_bspb(boss_sp_bullet **first,boss_sp_bullet **tail, plane *myplane){
	boss_sp_bullet *ptr = *first, *buffer;
	while(ptr != NULL){
		if(sq(ptr -> x - myplane -> x) + sq(ptr -> y - myplane -> y) < sq(ptr -> r + myplane -> r)){
			myplane -> life -= 5;

			buffer = ptr;
			ptr = ptr -> next;
			deletebspb(buffer, first, tail);
		}else
			ptr = ptr -> next;
	}
}
