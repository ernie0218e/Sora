#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif
#include "bullet.h"
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI  3.141592654

void newenemy(enemy **head, enemy **tail, int x, int y, double speed, double angle, int life, void **img, double r, int w, int h, int type){	
	if(*head == NULL){		//if there are no enemy, create an new list
        *head = (enemy *)malloc(sizeof(enemy));
        (*tail) = *head;
        (*tail) -> next = NULL;
        (*tail) -> previous = NULL;
    }else{		//add to queue
        (*tail) -> next = (enemy *)malloc(sizeof(enemy));
        (*tail) -> next -> previous = (*tail);
        (*tail)  = (*tail) -> next;
        (*tail) -> next = NULL;
    }
    (*tail) -> x = x;
    (*tail) -> y = y;
    (*tail) -> speed = speed;
    (*tail) -> angle = angle;
    (*tail) -> img = img;
    (*tail) -> r = r;
    (*tail) -> life = life;
    (*tail) -> w = w;
    (*tail) -> h = h;
    (*tail) -> type = type;
}

void deleteenemy(enemy *thisenemy, enemy **first, enemy **tail){
	if(thisenemy -> previous == NULL && thisenemy -> next == NULL){	//only one element inside the list
		*first = NULL;			//let the pointer point to NULL so as to generate a new list
		*tail = NULL;
		free(thisenemy);
	}
	else if(thisenemy -> previous == NULL){		//the begin of the list
  		thisenemy -> next -> previous = NULL;
  		*first = thisenemy -> next;
		free(thisenemy);
	}else if(thisenemy -> next == NULL){		//the end of the list
		*tail = thisenemy -> previous;
		thisenemy -> previous -> next = NULL;
		free(thisenemy);
	}else{
		thisenemy -> previous -> next = thisenemy -> next;
  		thisenemy -> next -> previous = thisenemy -> previous; 
		free(thisenemy);
	}
}

void updateenemy(enemy **first, enemy **tail){
    enemy *ptr = *first, *denemy;
    int w,h;
    int maxx,maxy;
    maxx = getmaxx();
    maxy = getmaxy();
    while(ptr != NULL){
    	ptr -> x += (int) ((ptr -> speed)*cos(ptr -> angle));	//update position
    	ptr -> y += (int) ((ptr ->	speed)*sin(ptr -> angle));
    	if((ptr -> x + ptr -> r) > 0 && (ptr -> x - ptr -> r) < maxx &&	//detect whether the enemy is inside the window
    		(ptr -> y + ptr -> r) > 0 && (ptr -> y - ptr -> r) < maxy){
			w = ptr -> w;
			h = ptr -> h;
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[0], 2);
			ptr = ptr -> next;
		}else{
			denemy = ptr;
			ptr = ptr -> next;
			deleteenemy(denemy, first, tail);
		}
    }
}

void deleteall(enemy **first, enemy **tail){
    enemy *ptr = *first, *buffer;
    while(ptr != NULL){
    	buffer = ptr;
    	ptr = ptr -> next;
    	free(buffer);
    }
    *first = NULL;	//let the pointer point to NULL so as to generate a new list
    *tail = NULL;
}

void chenemy(enemy *thisenemy, double speed, double angle){ //change the value of one enemy
	thisenemy -> speed = speed;
	thisenemy -> angle = angle;
}

void chaenemy(enemy *first, double speed, double angle){	//change the value of all enemy
	enemy *ptr = first;
	while(ptr != NULL){
		ptr -> speed = speed;
		ptr -> angle = angle;
	}
}

int checkenemy(enemy *first){
	if(first == NULL)
		return 0;
	return 1;
}

void e_nfire(enemy *plane, bullet **head, bullet **tail, void **img, int bw, int bh){
	int x, y, w, h, val = 3;
	double speed = 5, angle = 0.5*PI, r = (bw + bh) / 4.0;
	w = plane -> w;
	h = plane -> h;
	x = plane -> x;
	y = plane -> y + h/2;
	newbullet(head, tail, x, y, speed, angle, img, r, val, bw, bh);
}

void e_sfire_a(enemy *plane, bullet **head, bullet **tail, void **img, int bw, int bh){
	int x, y, w, h, val = 3;
	double speed = 5, angle = PI, r = (bw + bh) / 4.0, i;
	w = plane -> w;
	h = plane -> h;
	x = plane -> x;
	y = plane -> y + h/2;
	for(i = 2.5;i <= 7.5; i+=0.5) 
		newbullet(head, tail, x, y, speed, angle*i/10.0, img, r, val, bw, bh);
}

void e_sfire_b(enemy *plane, bullet **head, bullet **tail, void **img, double bangle, int bw, int bh){
	int val = 4;
	double speed = 8, angle = bangle, r = (bw + bh) / 4.0;
	newbullet(head, tail, plane -> x, plane -> y + plane -> h/2, speed, angle, img, r, val, bw, bh);
}
