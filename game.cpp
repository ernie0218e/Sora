#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "bullet.h"
#include "enemy.h"
#include "plane.h"
#include "control.h"
#include "initial.h"
#include "ai.h"
#include "boss.h"
#include "collision.h"
#include "menu.h"
#include "utilize.h"
#define PI  3.141592654

long sc;
extern explosion *exhead,*extail;
extern void **eximg;


void easy(){
	//initial of object
	bullet *bhead[3] = {NULL}, *btail[3] = {NULL},*bosshead=NULL,*bosstail=NULL;
	enemy *ehead[3] = {NULL}, *etail[3] = {NULL};
	lifeplus *hphead=NULL,*hptail=NULL;
	spbulletplus *spbphead=NULL,*spbptail=NULL;
	boss_sp_bullet *bspbhead=NULL,*bspbtail=NULL;
	boss eboss;
	plane  myplane;
	cloud cl[10];
	cloudinit(cl,10);
	
	int i, offset, *w, *h, r , key[52], cur_page=1, cenemy = 0, enemy_aitype,bulletcount = 50,graphcount,scroll;
	void **img, **eimg1, **eimg2, **bimg, **mybimg, **back, **bbimg,**hpimg,**spbpimg,**bspbimg;
	clock_t cur, end, start, del = 0, del2 = 0;
	static clock_t hp=clock(),spbp=clock();
	const clock_t normaltime = 60000;
    srand(time(NULL));
	char mfname[64] = ".\\music\\boss3.mp3";
	
	//graph initial
	graphcount = graphinit("einit.txt", &img, &w, &h);
	eimg1 = new void*[2];
	eimg2 = new void*[2];
	bimg = new void*[2];
	mybimg = new void*[2];
	back = new void*[2];
	bbimg = new void *[2];
	eximg = new void*[28];
	hpimg = new void *[2];
	spbpimg = new void *[2];
	bspbimg = new void *[14];
	back[0] = img[46];
	back[1] = img[46];
	for(i = 18;i < 46;i++)
		eximg[i-18] = img[i];
	for(i=53;i<67;i++)
	    bspbimg[i-53] = img[i];
	for(i = 0;i < 10;i++){
    	cl[i].img = new void *[2];
    	cl[i].img[0] = img[47];
    	cl[i].img[1] = img[48];
    	cl[i].w = w[47];
    	cl[i].h = h[47];
	}
	    
	//*****initial myplane******//
    myplane.img = new void* [6];
    for(i = 0;i < 6;i++)
    	myplane.img[i] = img[i];
	myplane.x = getmaxx()/2;
    myplane.y = getmaxy() - h[0] / 2;
    myplane.life = 150;
    myplane.r = (w[0]+h[0])/4.0 - 10;
    //*************************//
    
    //*****initial boss******//
    eboss.img = new void * [2];
    eboss.img[0] = img[12];
    eboss.img[1] = img[13];
    eboss.w = w[12];
    eboss.h = h[12];
    eboss.y=-eboss.h;
    eboss.life = 500;
    eboss.angle=0.5*PI;
    eboss.speed=0;
    eboss.r=(w[12]+h[12])/4.0-20;
    eboss.x=getmaxx()/2;
    eboss.active = 0;
	//**********************//
    
    play_bgm(mfname);
    sc = 0;
    start = clock();
    scroll = 1;
    while(1){
    	cur = clock();
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
    	cleardevice();
    	
    	background(back[0],back[1],960,scroll);		//scroll the background
    	newcloud(cl,10);						//generate cloud
    	belowcloud(cl,10);						//update lower cloud
    	
    	if(myplane.life >= 0){
    		
	    	control(key);
    		
    		//*******myplane related******//
			p_move(&myplane,key[0]);
    		updateplane(&myplane, w, h, key[0]);
    		mybimg[0] = img[14];
    		mybimg[1] = img[15];
    		p_nfire(&myplane, &bhead[0], &btail[0], mybimg, w[14], h[14], key[1]);
			if(bulletcount)
				p_sfire_a(&myplane, &bhead[0], &btail[0], mybimg, w[14], h[14], key[2], &bulletcount);	//there are limits on number of special bullet
			//*******myplane related******//
			
			if(clock()-hp>=60000)//每分鐘產生 
			{
				hpimg[0] = img[49];
				hpimg[1] = img[50];
				newhp(hpimg,w[50],h[50],&hphead,&hptail,getmaxx()/2,50);
				hp=clock();
			}
			updatehp(&hphead,&hptail,&myplane);
			
			if(clock()-spbp>=30000)//每半分鐘產生 
			{
				spbpimg[0] = img[51];
				spbpimg[1] = img[52];
				newspbp(spbpimg,w[51],h[51],&spbphead,&spbptail,getmaxx()/2,50);
				spbp=clock();
			}
			if(updatespbp(&spbphead,&spbptail,&myplane))
			    bulletcount=50;
			
			if(cur - start < normaltime){		//determine whose show time~
				bimg[0] = img[16];				//pass the image
				bimg[1] = img[17];
				eimg1[0] = img[6];
				eimg1[1] = img[7];
				if(cur - start > 5000)
					easy(&ehead[0],&etail[0],eimg1,w[6],h[6],&bhead[1],&btail[1],bimg,w[16],h[16]);
				if(!(rand()%2000) || checkenemy(ehead[1])){
					eimg2[0] = img[8];
					eimg2[1] = img[9];
					medium(&myplane, &ehead[1], &etail[1], eimg2, w[8], h[8]);
				}
			}else{
				scroll = 2;
				if(eboss.life <= 0){
					change_bgm(mfname,".\\music\\sanka.mp3");
					//calculate score
					if(del < 500){
						putimage(getmaxx()/2 - 256,getmaxy()/2 - 192, img[68],3);
						putimage(getmaxx()/2 - 256,getmaxy()/2 - 192, img[67],2);
						del++;
					}else{
						name_enter(sc, 1);
						close_bgm(".\\music\\sanka.mp3");
						break;
					}
				}else{
					bbimg[0] = img[16];
					bbimg[1] = img[17];
					bossstage_easy(&bosshead,&bosstail,&myplane,&eboss,w[17],h[17],bbimg,&bspbhead,&bspbtail,bspbimg);
					updatebullet(&bosshead,&bosstail);
					d_battack(&bhead[0], &btail[0],&eboss);
					d_beattack(&bosshead,&bosstail, &myplane);
					d_bcrash(&eboss,&myplane);
					mbullet_ebullet_collision(&bosshead,&bosstail,&bhead[0],&btail[0]);
					updatebspb(&bspbhead,&bspbtail);
					updateboss(&eboss);
					d_beattack_bspb(&bspbhead,&bspbtail, &myplane);
				}
				
			}
			
			//****update the info of all linked-list****//
			for(i = 0;i < 3;i++){
				d_attack(&bhead[0], &btail[0], &ehead[i], &etail[i]);
				d_crash(&ehead[i],&etail[i],&myplane);
				updateenemy(&ehead[i], &etail[i]);
			}
			
			for(i = 1;i < 3;i++){
				d_beattack(&bhead[i], &btail[i], &myplane);
				mbullet_ebullet_collision(&bhead[i], &btail[i],&bhead[0],&btail[0]);
				updatebullet(&bhead[i], &btail[i]);
			}
			updatebullet(&bhead[0], &btail[0]);
			
			updateexplosion();		//update the explosion
			
			upcloud(cl,10);				//draw upper cloud
			life(myplane.life,150);		//life bar
			if(eboss.active)
				boss_life(eboss.life,500);
			score(sc);					//score bar
			spbullet(sc,&bulletcount,20,0);  //get some special bullet

			
		}else{
			change_bgm(mfname,".\\music\\Anixety.mp3");
			//Failed
			if(del2 < 500){
				putimage(getmaxx()/2 - w[74]/2,getmaxy()/2 - h[74]/2, img[70],3);
				putimage(getmaxx()/2 - w[74]/2,getmaxy()/2 - h[74]/2, img[69],2);
				del2++;
			}
			else{
				close_bgm(".\\music\\Anixety.mp3");
				break;
			}
		}
		end = clock();
		
		offset = 1000*double(end-cur)/CLOCKS_PER_SEC;		//offset of delay
		offset = abs(10-offset);

		delay(offset);
    	if(key[3]){
			r = esc_menu();
    		if(!r)
    			break;
    		else if(r == 2){			//reset
    			for(i = 0;i < 3;i++){
    				deleteall(&bhead[i],&btail[i]);
    				deleteall(&ehead[i],&etail[i]);
    			}
    			deleteall();
    			deleteall(&spbphead,&spbptail);
    			deleteall(&hphead,&hptail);
    			deleteall(&bspbhead,&bspbtail);
    			cloudinit(cl,10);
    			restart_bgm(mfname);
    			//reset score
    			eboss.y=-eboss.h;
    			eboss.life = 500;
    			eboss.x=getmaxx()/2;
    			eboss.active = 0;
    			sc = 0;
    			scroll = 1;
    			spbullet(sc,&bulletcount,20,1);
    			bulletcount = 50;
    			myplane.x = getmaxx()/2;
    			myplane.y = getmaxy() - h[0] / 2;
    			myplane.life = 150;
    			restart_bgm(mfname);
    			start = clock();
    		}
    	}
    }
    close_bgm(mfname);
    //deallocate memory!!
    
    for(i = 0;i < 3;i++){
    	deleteall(&bhead[i],&btail[i]);
    	deleteall(&ehead[i],&etail[i]);
   	}
    
   	for(i = 0;i < graphcount;i++)
    	free(img[i]);
    for(i = 0;i < 10;i++){
    	delete []cl[i].img;
	}
    delete []eimg1;
    delete []eimg2;
    delete []bimg;
    delete []mybimg;
    delete []myplane.img;
    delete []eximg;
    delete []bbimg;
    delete []hpimg;
    delete []eboss.img;
    delete []spbpimg;
    delete []bspbimg;
    free(img);
}

void medium(){
	bullet *bhead[3] = {NULL}, *btail[3] = {NULL},*bosshead=NULL,*bosstail=NULL;
	enemy *ehead[3] = {NULL}, *etail[3] = {NULL};
	lifeplus *hphead=NULL,*hptail=NULL,*ptr;
	spbulletplus *spbphead=NULL,*spbptail=NULL;
	boss_sp_bullet *bspbhead=NULL,*bspbtail=NULL;
	plane  myplane;
	boss eboss;
	cloud cl[10];
	cloudinit(cl,10);
	
	int i, offset, *w, *h, r , key[52], cur_page=1, cenemy = 0, enemy_aitype,bulletcount = 10,graphcount,scroll = 1;
	void **img, **eimg1, **eimg2, **bimg, **mybimg, **back, **eimg3,**bbimg,**hpimg,**spbpimg,**bspbimg;
	clock_t cur, end, start, del = 0, del2 = 0;
	static clock_t hp=clock(),spbp=clock();
	const clock_t normaltime = 60000;
    srand(time(NULL));
	char mfname[64] = ".\\music\\boss2.wma";
	
	//graph initial
	graphcount = graphinit("minit.txt", &img, &w, &h);
	eimg1 = new void*[2];
	eimg2 = new void*[2];
	eimg3 = new void*[2];
	bimg = new void*[2];
	bbimg = new void *[2];
	hpimg = new void *[2];
	spbpimg = new void *[2];
	mybimg = new void*[2];
	back = new void*[2];
	eximg = new void*[28];
	bspbimg = new void*[16];
	//need change
	back[0] = img[46];
	back[1] = img[46];
	for(i = 18;i < 46;i++)
		eximg[i-18] = img[i];
	for(i = 55;i<71;i++)
	    bspbimg[i-55]=img[i];
	for(i = 0;i < 10;i++){
    	cl[i].img = new void *[2];
    	cl[i].img[0] = img[47];
    	cl[i].img[1] = img[48];
    	cl[i].w = w[47];
    	cl[i].h = h[47];
	}
	    
	//*****initial myplane******//
    myplane.img = new void* [6];
    for(i = 0;i < 6;i++)
    	myplane.img[i] = img[i];
	myplane.x = getmaxx()/2;
    myplane.y = getmaxy() - h[0] / 2;
    myplane.life = 150;
    myplane.r = (w[0]+h[0])/4.0 - 10;
    //*************************//
    
    //*****initial boss******//
    eboss.img = new void * [2];
    eboss.img[0] = img[12];
    eboss.img[1] = img[13];
    eboss.w = w[12];
    eboss.h = h[13];
    eboss.x=getmaxx()/2;
    eboss.y=-eboss.h;
    eboss.life = 750;
    eboss.angle=0.5*3.14;
    eboss.speed=0;
    eboss.r=(w[12]+h[12])/4.0-20;
    eboss.active = 0;
	//**********************//
    
    play_bgm(mfname);
    sc = 0;
    start = clock();
    while(1){
    	cur = clock();
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
    	cleardevice();
    	
    	background(back[0],back[1],960,1);
    	newcloud(cl,10);
    	belowcloud(cl,10);
    	
    	if(myplane.life >= 0){
    		
	    	control(key);
    		
    		p_move(&myplane,key[0]);
    		updateplane(&myplane, w, h, key[0]);
    		mybimg[0] = img[14];
    		mybimg[1] = img[15];
    		p_nfire(&myplane, &bhead[0], &btail[0], mybimg, w[14], h[14], key[1]);
			if(bulletcount)
				p_sfire_a(&myplane, &bhead[0], &btail[0], mybimg, w[14], h[14], key[2], &bulletcount);	//there are limits on number of special bullet
			
			if(clock()-hp>=60000)//每分鐘產生 
			{
				hpimg[0] = img[49];
				hpimg[1] = img[50];
				newhp(hpimg,w[50],h[50],&hphead,&hptail,getmaxx()/2,50);
				hp=clock();
			}
			updatehp(&hphead,&hptail,&myplane);
			
			if(clock()-spbp>=30000)//每半分鐘產生 
			{
				spbpimg[0] = img[51];
				spbpimg[1] = img[52];
				newspbp(spbpimg,w[51],h[51],&spbphead,&spbptail,getmaxx()/2,50);
				spbp=clock();
			}
			if(updatespbp(&spbphead,&spbptail,&myplane))
			    bulletcount=50;
			
			if(cur - start < normaltime){		//determine whose show time~ by random
				if(cur - start > 5000){
					if(!(rand()%1200) || checkenemy(ehead[0])){	//three kind of enemy
						bimg[0] = img[16];
						bimg[1] = img[17];
						eimg1[0] = img[6];
						eimg1[1] = img[7];
						easy(&ehead[0],&etail[0],eimg1,w[6],h[6],&bhead[1],&btail[1],bimg,w[16],h[16]);
					}
					if(!(rand()&1000) || checkenemy(ehead[2])){
						eimg3[0] = img[10];
						eimg3[1] = img[11];
						bimg[0] = img[16];
						bimg[1] = img[17];
						medium_ai(&myplane,&ehead[2],&etail[2],eimg3,w[10],h[10],&bhead[2],&btail[2],bimg,w[16],h[16]);	
					}
					if(!(rand()%1200) || checkenemy(ehead[1])){
						eimg2[0] = img[8];
						eimg2[1] = img[9];
						medium(&myplane, &ehead[1], &etail[1], eimg2, w[8], h[8]);
					}
				}
			}else{ 
				scroll = 2;
				if(eboss.life <= 0){
					change_bgm(mfname,".\\music\\sanka.mp3");
					//calculate score
					if(del < 500){
						putimage(getmaxx()/2 - 256,getmaxy()/2 - 192, img[72],3);
						putimage(getmaxx()/2 - 256,getmaxy()/2 - 192, img[71],2);
						del++;
					}else{
						name_enter(sc, 2);
						close_bgm(".\\music\\sanka.mp3");
						break;
					}
				}else{
				
					bbimg[0] = img[16];
					bbimg[1] = img[17];
					bossstage_medium(&bosshead,&bosstail,&myplane,&eboss,w[16],h[16],bbimg,&bspbhead,&bspbtail,bspbimg);
					updatebullet(&bosshead,&bosstail);
					d_battack(&bhead[0], &btail[0],&eboss);
					d_beattack(&bosshead,&bosstail, &myplane);
					d_beattack_bspb(&bspbhead,&bspbtail, &myplane);
					d_bcrash(&eboss,&myplane);
					mbullet_ebullet_collision(&bosshead,&bosstail,&bhead[0],&btail[0]);
					updateboss(&eboss);
					updatebspb(&bspbhead,&bspbtail);
				}
			}
			
			for(i = 0;i < 3;i++){
				d_attack(&bhead[0], &btail[0], &ehead[i], &etail[i]);
				d_crash(&ehead[i],&etail[i],&myplane);
				updateenemy(&ehead[i], &etail[i]);
			}
			for(i = 1;i < 3;i++){
				d_beattack(&bhead[i], &btail[i], &myplane);
				mbullet_ebullet_collision(&bhead[i], &btail[i],&bhead[0],&btail[0]);
				updatebullet(&bhead[i], &btail[i]);
			}
			updatebullet(&bhead[0], &btail[0]);
			updateexplosion();
			
			upcloud(cl,10);
			life(myplane.life,150);
			if(eboss.active)
				boss_life(eboss.life,750);
			score(sc);
			spbullet(sc,&bulletcount,10,0);
			
		}else{
			change_bgm(mfname,".\\music\\Anixety.mp3");
			if(del2 < 500){
				putimage(getmaxx()/2 - w[74]/2,getmaxy()/2 - h[74]/2, img[74],3);
				putimage(getmaxx()/2 - w[74]/2,getmaxy()/2 - h[74]/2, img[73],2);
				del2++;
			}
			else{
				close_bgm(".\\music\\Anixety.mp3");
				break;
			}
			
		}
		end = clock();
		
		offset = 1000*double(end-cur)/CLOCKS_PER_SEC;
		offset = abs(10-offset);

		delay(offset);
    	if(key[3]){
			r = esc_menu();
    		if(!r)
    			break;
    		else if(r == 2){
    			
    			for(i = 0;i < 3;i++){
    				deleteall(&bhead[i],&btail[i]);
    				deleteall(&ehead[i],&etail[i]);
    			}
    			deleteall();
    			deleteall(&spbphead,&spbptail);
    			deleteall(&hphead,&hptail);
    			deleteall(&bspbhead,&bspbtail);
    			cloudinit(cl,10);
    			restart_bgm(mfname);
    			//reset score
    			eboss.x=getmaxx()/2;
    			eboss.y=-eboss.h;
    			eboss.life = 750;
    			eboss.active = 0;
    			scroll = 1;
    			sc = 0;
    			spbullet(sc,&bulletcount,40,1);
    			bulletcount = 50;
    			myplane.x = getmaxx()/2;
    			myplane.y = getmaxy() - h[0] / 2;
    			myplane.life = 150;
    			restart_bgm(mfname);
    			start = clock();
    		}
    	}
    }
    
    close_bgm(mfname);
    //deallocate memory!!
    
    for(i = 0;i < 3;i++){
    	deleteall(&bhead[i],&btail[i]);
    	deleteall(&ehead[i],&etail[i]);
   	}
    
   	for(i = 0;i < graphcount;i++)
    	free(img[i]);
    for(i = 0;i < 10;i++){
    	delete []cl[i].img;
	}
    delete []eimg1;
    delete []eimg2;
    delete []eimg3;
    delete []bimg;
    delete []mybimg;
    delete []myplane.img;
    delete []eximg;
    delete []bbimg;
    delete []hpimg;
    delete []eboss.img;
    delete []spbpimg;
    delete []bspbimg;
    free(img);
}

void hard(){
	bullet *bhead[4] = {NULL}, *btail[4] = {NULL}, *bosshead = NULL, *bosstail = NULL,*p;
	enemy *ehead[4] = {NULL}, *etail[4] = {NULL};
	lifeplus *hphead=NULL,*hptail=NULL,*ptr;
	spbulletplus *spbphead=NULL,*spbptail=NULL;
	boss_sp_bullet *bspbhead=NULL,*bspbtail=NULL;
	plane  myplane;
	boss eboss;
	cloud cl[10];
	cloudinit(cl,10);
	
	int i, offset, *w, *h, r , key[52], cur_page=1, cenemy = 0, enemy_aitype,bulletcount = 10,graphcount,scroll = 1;
	void **img, **eimg1, **eimg2, **bimg1, **bimg2, **bimg3, **mybimg, **back, **eimg3, **eimg4, **mybimg2, **bbimg,**hpimg,**spbpimg,**bspbimg;
	clock_t cur, end, start, del = 0, del2 = 0;
	static clock_t hp=clock(),spbp=clock();
	const clock_t normaltime = 60000;
	char mfname[64] = ".\\music\\boss1.wma";
    srand(time(NULL));
    double bangle,dir;
	
	//graph initial
	graphcount = graphinit("hinit.txt", &img, &w, &h);
	hpimg = new void*[2];
	eimg1 = new void*[2];
	eimg2 = new void*[2];
	eimg3 = new void*[2];
	eimg4 = new void*[2];
	bimg1 = new void*[2];
	bimg2 = new void*[2];
	bimg3 = new void*[2];
	bbimg = new void*[2];
	spbpimg = new void*[2];
	mybimg = new void*[2];
	mybimg2 = new void*[2];
	back = new void*[2];
	eximg = new void*[28];
	bspbimg = new void*[30];
	//need change
	back[0] = img[52];
	back[1] = img[52];
	for(i = 24;i < 52;i++)
		eximg[i-24] = img[i];
	for(i=59;i<89;i++)
		bspbimg[i-59] = img[i];
	for(i = 0;i < 10;i++){
    	cl[i].img = new void *[2];
    	cl[i].img[0] = img[53];
    	cl[i].img[1] = img[54];
    	cl[i].w = w[53];
    	cl[i].h = h[53];
	}
	    
	//*****initial myplane******//
    myplane.img = new void* [6];
    for(i = 0;i < 6;i++)
    	myplane.img[i] = img[i];
	myplane.x = getmaxx()/2;
    myplane.y = getmaxy() - h[0] / 2;
    myplane.life = 150;
    myplane.r = (w[0]+h[0])/4.0 - 10;
    //*************************//
    
    //*****initial boss******//
    eboss.img = new void * [2];
    eboss.img[0] = img[14];
    eboss.img[1] = img[15];
    eboss.w = w[14];
    eboss.h = h[14];
    eboss.x=getmaxx()/2;
    eboss.y=-eboss.h;
    eboss.life = 1000;
    eboss.angle=0.5*3.14;
    eboss.speed=0;
    eboss.r=(w[14]+h[14])/4.0-20;
    eboss.active = 0;
	//**********************//
	
	
	
    play_bgm(mfname);
    sc = 0;
    start = clock();
    while(1){
    	cur = clock();
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
    	cleardevice();
    	
    	background(back[0],back[1],960,scroll);
    	newcloud(cl,10);
    	belowcloud(cl,10);
    	if(myplane.life >= 0){
    		
	    	control(key);
    		
    		p_move(&myplane,key[0]);
    		updateplane(&myplane, w, h, key[0]);
    		mybimg[0] = img[22];
    		mybimg[1] = img[23];
    		mybimg2[0] = img[16];
    		mybimg2[1] = img[17];
    		p_nfire(&myplane, &bhead[0], &btail[0], mybimg, w[22], h[22], key[1]);
			if(bulletcount)
				p_sfire_a(&myplane, &bhead[0], &btail[0], mybimg2, w[16], h[16], key[2], &bulletcount);	//there are limits on number of special bullet
			
			if(clock()-hp>=60000)//每分鐘產生 
			{
				hpimg[0] = img[55];
				hpimg[1] = img[56];
				newhp(hpimg,w[55],h[55],&hphead,&hptail,getmaxx()/2,50);
				hp=clock();
			}
			updatehp(&hphead,&hptail,&myplane);
			
			if(clock()-spbp>=30000)//每半分鐘產生 
			{
				spbpimg[0] = img[57];
				spbpimg[1] = img[58];
				newspbp(spbpimg,w[57],h[57],&spbphead,&spbptail,getmaxx()/2,50);
				spbp=clock();
			}
			if(updatespbp(&spbphead,&spbptail,&myplane))
			    bulletcount=50;
			
			if(cur - start < normaltime){		//determine whose show time~ by random
				if(cur - start > 5000){
					if(!(rand()%600) || checkenemy(ehead[0])){	//four kind of enemy
						bimg1[0] = img[18];
						bimg1[1] = img[19];
						eimg1[0] = img[6];
						eimg1[1] = img[7];
						trace(&ehead[0],&etail[0],&bhead[1],&btail[1],bimg1,w[18],h[18],eimg1,w[6],h[6],&myplane);
					}
					if(!(rand()%1000) || checkenemy(ehead[3])){
						bimg2[0] = img[20];
						bimg2[1] = img[21];
						eimg4[0] = img[10];
						eimg4[1] = img[11];
						high_ai(&myplane,bhead[0],&ehead[3],&etail[3],eimg4,w[10],h[10],&bhead[3],&btail[3],bimg2,w[20],h[20]);
					}
					if(!(rand()&1200) || checkenemy(ehead[2])){
						eimg3[0] = img[12];
						eimg3[1] = img[13];
						bimg3[0] = img[18];
						bimg3[1] = img[19];
						medium_ai(&myplane,&ehead[2],&etail[2],eimg3,w[12],h[12],&bhead[2],&btail[2],bimg3,w[18],h[18]);	
					}
					if(!(rand()%1200) || checkenemy(ehead[1])){
						eimg2[0] = img[8];
						eimg2[1] = img[9];
						medium(&myplane, &ehead[1], &etail[1], eimg2, w[8], h[8]);
					}
					trace_bullet(bhead[1],&myplane);
				}
			}else{  
				scroll = 2;
				//boss
				if(eboss.life <= 0){
					change_bgm(mfname,".\\music\\sanka.mp3");
					//calculate score
					if(del < 500){
						putimage(getmaxx()/2 - 256,getmaxy()/2 - 192, img[90],3);
						putimage(getmaxx()/2 - 256,getmaxy()/2 - 192, img[89],2);
						del++;
					}else{
						name_enter(sc, 3);
						close_bgm(".\\music\\sanka.mp3");
						break;
					}
				}else{
					bbimg[0] = img[20];
					bbimg[1] = img[21];
					bossstage_hard(&bosshead,&bosstail,&myplane,&eboss,w[20],h[20],bbimg,&bspbhead,&bspbtail,bspbimg);
					updatebullet(&bosshead,&bosstail);
					d_battack(&bhead[0], &btail[0],&eboss);
					d_beattack(&bosshead,&bosstail, &myplane);
					d_beattack_bspb(&bspbhead,&bspbtail, &myplane);
					d_bcrash(&eboss,&myplane);
					mbullet_ebullet_collision(&bosshead,&bosstail,&bhead[0],&btail[0]);
					updatebspb(&bspbhead,&bspbtail);
					updateboss(&eboss);
				}
				
		    }
			for(i = 0;i < 4;i++){
				d_attack(&bhead[0], &btail[0], &ehead[i], &etail[i]);
				d_crash(&ehead[i],&etail[i],&myplane);
				updateenemy(&ehead[i], &etail[i]);
			}
			for(i = 1;i < 4;i++){
				d_beattack(&bhead[i], &btail[i], &myplane);
				mbullet_ebullet_collision(&bhead[i], &btail[i],&bhead[0],&btail[0]);
				updatebullet(&bhead[i], &btail[i]);
			}
			bullet_collision(&bhead[1],&btail[1]);		//bullet will cancel out it self
			updatebullet(&bhead[0], &btail[0]);
			updateexplosion();
			
			upcloud(cl,10);
			life(myplane.life,150);
			if(eboss.active)
				boss_life(eboss.life,1000);
			score(sc);
			spbullet(sc,&bulletcount,10,0);
			
		}else{
			change_bgm(mfname,".\\music\\Anixety.mp3");
			//Failed
			if(del2 < 500){
				putimage(getmaxx()/2 - w[92]/2,getmaxy()/2 - h[92]/2, img[92],3);
				putimage(getmaxx()/2 - w[92]/2,getmaxy()/2 - h[92]/2, img[91],2);
				del2++;
			}
			else{
				close_bgm(".\\music\\Anixety.mp3");
				break;
			}
		}
		end = clock();
		
		offset = 1000*double(end-cur)/CLOCKS_PER_SEC;
		offset = abs(10-offset);
		delay(offset);
    	if(key[3]){
			r = esc_menu();
    		if(!r)
    			break;
    		else if(r == 2){
    			
    			for(i = 0;i < 4;i++){
    				deleteall(&bhead[i],&btail[i]);
    				deleteall(&ehead[i],&etail[i]);
    			}
    			deleteall();
    			deleteall(&bspbhead,&bspbtail);
    			deleteall(&spbphead,&spbptail);
    			deleteall(&hphead,&hptail);
    			cloudinit(cl,10);
    			//reset score
    			eboss.x=getmaxx()/2;
    			eboss.y=-eboss.h;
    			eboss.life = 1000;
    			eboss.active = 0;
    			sc = 0;
    			scroll = 1;
    			spbullet(sc,&bulletcount,40,1);
    			bulletcount = 50;
    			myplane.x = getmaxx()/2;
    			myplane.y = getmaxy() - h[0] / 2;
    			myplane.life = 150;
    			restart_bgm(mfname);
    			start = clock();
    		}
    	}
    }
    
    close_bgm(mfname);
    //deallocate memory!!
    
    for(i = 0;i < 4;i++){
    	deleteall(&bhead[i],&btail[i]);
    	deleteall(&ehead[i],&etail[i]);
    }
    
   	for(i = 0;i < graphcount;i++)
    	free(img[i]);
    for(i = 0;i < 10;i++){
    	delete []cl[i].img;
	}
    delete []eimg1;
    delete []eimg2;
    delete []eimg3;
    delete []eimg4;
    delete []bimg1;
    delete []bimg2;
    delete []bimg3;
    delete []mybimg;
    delete []mybimg2;
    delete []myplane.img;
    delete []eboss.img;
    delete []eximg;
    delete []bbimg;
    delete []hpimg;
    delete []spbpimg;
    delete []bspbimg;
    free(img);
}
