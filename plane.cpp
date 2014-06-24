#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#include "graph.h"
#include "bullet.h"
#define PI  3.141592654
#include <stdio.h>

#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif



void p_move(plane *myplane, int key){
	int w, h, x, y;
	const int yspeed = 5, xspeed = 5;
	w = myplane -> w;
	h = myplane -> h;
	x = myplane -> x;
	y = myplane -> y;
	switch(key){
		case 1:
			y -= yspeed;
			if(y - h/2 < 0)
				y = h/2;
			break;
		case 2:
			x -= xspeed;
			if(x - w/2 < 0)
				x = w/2;
			break;
		case 3:
			y += yspeed;
			if(y + h/2 > getmaxy())
				y = getmaxy() - h/2;
			break;
			
		case 4:
			x += xspeed;
			if(x + w/2 > getmaxx())
				x = getmaxx() - w/2;
			break;
		case 5:
			x += xspeed;
			if(x + w/2 > getmaxx())
				x = getmaxx() - w/2;
			y -= yspeed;
			if(y - h/2 < 0)
				y = h/2;
			break;
		case 6:
			x -= xspeed;
			if(x - w/2 < 0)
				x = w/2;
			y -= yspeed;
			if(y - h/2 < 0)
				y = h/2;
			break;
		case 7:
			x -= xspeed;
			if(x - w/2 < 0)
				x = w/2;
			y += yspeed;
			if(y + h/2 > getmaxy())
				y = getmaxy() - h/2;
			break;
		case 8:
			x += xspeed;
			if(x + w/2 > getmaxx())
				x = getmaxx() - w/2;
			y += yspeed;
			if(y + h/2 > getmaxy())
				y = getmaxy() - h/2;
			break;
	}
	myplane -> x = x;
	myplane -> y = y;
}

void updateplane(plane *myplane, int *w, int *h, int key){
	switch(key){
		case 2:
			myplane->w = w[1];
    		myplane->h = h[1];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[3],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[2],2);
			break;
		case 4:
			myplane->w = w[2];
    		myplane->h = h[2];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[5],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[4],2);
			break;
		case 5:
			myplane->w = w[2];
    		myplane->h = h[2];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[5],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[4],2);
			break;
		case 6:
			myplane->w = w[1];
    		myplane->h = h[1];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[3],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[2],2);
			break;
		case 7:
			myplane->w = w[1];
    		myplane->h = h[1];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[3],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[2],2);
			break;
		case 8:
			myplane->w = w[2];
    		myplane->h = h[2];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[5],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[4],2);
			break;
		default:
			myplane->w = w[0];
    		myplane->h = h[0];
			putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[1],3);
    		putimage(myplane->x - myplane->w/2, myplane->y - myplane->h/2, myplane->img[0],2);
    	break;
	}
	myplane->r = (myplane->w+myplane->h)/4.0 - 10;
}

void p_nfire(plane *myplane, bullet **head, bullet **tail, void **img, int bw, int bh, int key){
	int x, y, w, h, val = 4, delay = 250;
	double speed = 8, angle = 1.5*PI, r = (bw + bh) / 4.0;
	static clock_t cur = 0;
	w = myplane -> w;
	h = myplane -> h;
	x = myplane -> x;
	y = myplane -> y - h/2;
	if(key && clock() - cur > delay){
		newbullet(head, tail, x, y, speed, angle, img, r, val, bw, bh);
		cur = clock();
	}
}

void p_sfire_a(plane *myplane, bullet **head, bullet **tail, void **img, int bw, int bh, int key, int *bcount){
	int x, y, w, h, val = 3, delay = 250, i;
	double speed = 8, angle = PI, r = (bw + bh) / 4;
	static clock_t cur = 0;
	static int flag = 0;
	w = myplane -> w;
	h = myplane -> h;
	x = myplane -> x;
	y = myplane -> y - h/2;
	if(key && clock() - cur > delay){
		for(i = 12;i < 19; i++) {
			newbullet(head, tail, x, y, speed, angle*i/10.0, img, r, val, bw, bh);
		}
		--(*bcount);
		cur = clock();
	}
}
