#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include "graph.h"

#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif


void newbullet(bullet **head, bullet **tail, int x, int y, double speed, double angle, void **img, double r, int val,int w, int h){	
	if(*head == NULL){		//if there are no bullet, create an new list
        *head = (bullet *)malloc(sizeof(bullet));
        (*tail) = *head;
        (*tail) -> next = NULL;
        (*tail) -> previous = NULL;
    }else{		//add to queue
        (*tail) -> next = (bullet *)malloc(sizeof(bullet));
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
    (*tail) -> val = val;
    (*tail) -> w = w;
    (*tail) -> h = h;
}

void deletebullet(bullet *thisbullet, bullet **first, bullet **tail){
	if(thisbullet -> previous == NULL && thisbullet -> next == NULL){	//only one element inside the list
		*first = NULL;			//let the pointer point to NULL so as to generate a new list
		*tail = NULL;
		free(thisbullet);
	}
	else if(thisbullet -> previous == NULL){		//the begin of the list
  		thisbullet -> next -> previous = NULL;
  		*first = thisbullet -> next;
		free(thisbullet);
	}else if(thisbullet -> next == NULL){		//the end of the list
		*tail = thisbullet -> previous;
		thisbullet -> previous -> next = NULL;
		free(thisbullet);
	}else{
		thisbullet -> previous -> next = thisbullet -> next;
  		thisbullet -> next -> previous = thisbullet -> previous; 
		free(thisbullet);
	}
}

void updatebullet(bullet **first, bullet **tail){
    bullet *ptr = *first, *dbullet;
    int w,h;
    int maxx,maxy;
    maxx = getmaxx();
    maxy = getmaxy();
    while(ptr != NULL){
    	ptr -> x += (int) ((ptr -> speed)*cos(ptr -> angle));	//update position
    	ptr -> y += (int) ((ptr ->	speed)*sin(ptr -> angle));
    	if((ptr -> x + ptr -> r) > 0 && (ptr -> x - ptr -> r) < maxx &&	//detect whether the bullet inside the window
    		(ptr -> y + ptr -> r) > 0 && (ptr -> y - ptr -> r) < maxy){
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[0], 2);
			ptr = ptr -> next;
		}else{
			dbullet = ptr;
			ptr = ptr -> next;
			deletebullet(dbullet, first, tail);
		}
    }
}


void deleteall(bullet **first, bullet **tail){
    bullet *ptr = *first, *buffer;
    while(ptr != NULL){
    	buffer = ptr;
    	ptr = ptr -> next;
    	free(buffer);
    }
    *first = NULL;	//let the pointer point to NULL so as to generate a new list
    *tail = NULL;
}

void chbullet(bullet *thisbullet, double speed, double angle){ //change the value of one bullet
	thisbullet -> speed = speed;
	thisbullet -> angle = angle;
}

void chabullet(bullet *first, double speed, double angle){	//change the value of all bullet
	bullet *ptr = first;
	while(ptr != NULL){
		ptr -> speed = speed;
		ptr -> angle = angle;
	}
}
