#include <windows.h>
#include <string.h>
#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>
#ifndef dstruct
#define dstruct "dstruct.h"
#include dstruct
#endif
#define BACKSPACE 0x08
#define A_key 0x41
#define B_key 0x42
#define C_key 0x43
#define D_key 0x44
#define E_key 0x45
#define F_key 0x46
#define G_key 0x47
#define H_key 0x48
#define I_key 0x49
#define J_key 0x4A
#define K_key 0x4B
#define L_key 0x4C
#define M_key 0x4D
#define N_key 0x4E
#define O_key 0x4F
#define P_key 0x50
#define Q_key 0x51
#define R_key 0x52
#define S_key 0x53
#define T_key 0x54
#define U_key 0x55
#define V_key 0x56
#define W_key 0x57
#define X_key 0x58
#define Y_key 0x59
#define Z_key 0x5A
#define zero_lkey 0x30
#define one_lkey 0x31
#define two_lkey 0x32
#define three_lkey 0x33
#define four_lkey 0x34
#define five_lkey 0x35
#define six_lkey 0x36
#define seven_lkey 0x37
#define eight_lkey 0x38
#define nine_lkey 0x39
#define zero_rkey 0x60
#define one_rkey 0x61
#define two_rkey 0x62
#define three_rkey 0x63
#define four_rkey 0x64
#define five_rkey 0x65
#define six_rkey 0x66
#define seven_rkey 0x67
#define eight_rkey 0x68
#define nine_rkey 0x69
#define enter_key 0x0D
#define SPACEBAR 0x20
#define PI  3.141592654

extern int music_flag;

explosion *exhead = NULL, *extail = NULL;
void **eximg;

inline float sq(int n){
	return n*n;
}

void close_bgm(char *fname){
	char s1[100] = "close ";
	strcat(s1, fname);
	mciSendString(s1, NULL, 0, NULL);
}

void play_bgm(char *fname){
	char s1[100] = "open ";
	char s2[100] = "play ";
	char s3[100] = " repeat";
	if(music_flag){
		strcat(s1,fname);
		mciSendString(s1, NULL, 0, NULL);
		strcat(s2,fname);
		strcat(s2,s3);
		mciSendString(s2, NULL, 0, NULL);
	}else
		close_bgm(fname);
	//add something
	//return NULL;
}

void restart_bgm(char *fname){
	close_bgm(fname);
	if(music_flag)
		play_bgm(fname);
}

void change_bgm(char *fname, char *fname2){
	char s1[100] = "close ";
	strcat(s1, fname);
	mciSendString(s1, NULL, 0, NULL);
	if(music_flag)
		play_bgm(fname2);
}


void score(long sc){
	char buf[8];
	int x,y,i;
	static int flag = 1;
	if(flag){
		settextstyle(0, HORIZ_DIR, 4);
		flag = 0;
	}
	
	sprintf(buf,"%7d",sc);
	for(i = 0;i < 7;i++){
		if(buf[i] == 32)
			buf[i] = '0';
	}
	x = textwidth(buf);
	y = textheight(buf);
	outtextxy(getmaxx() - x ,y/2,buf);
	setbkcolor(BLACK);
}

void life(long l, long init){
	int p[12] = {10,10,getmaxx()/2,10,getmaxx()/2+5,17,getmaxx()/2+5,33,getmaxx()/2,40,10,40};
	double dv;
	setfillstyle(1,15);
	fillpoly(6,p);
	setfillstyle(1,1);
	bar(15,15,getmaxx()/2-10,35);
	dv = (getmaxx()/2-25)/(double)init;
	if(l > init/3.0)
		setfillstyle(1,11);
	else
		setfillstyle(1,12);
	bar(15,15,l*dv+15,35);
}

void boss_life(long l, long init){
	int p[12] = {10,50,getmaxx()*0.75,50,getmaxx()*0.75+5,57,getmaxx()*0.75+5,73,getmaxx()*0.75,80,10,80};
	double dv;
	setfillstyle(1,8);
	fillpoly(6,p);
	setfillstyle(1,1);
	bar(15,55,getmaxx()*0.75,75);
	dv = (getmaxx()*0.75-25)/(double)init;
	if(l > init/2.0)
		setfillstyle(1,12);
	else
		setfillstyle(1,4);
	bar(15,55,l*dv+25,75);
}

void background(void *img1, void *img2, int h, int scroll_speed){
	static int y1 = 0, y2 = 0;
	static int flag = 1;
	static clock_t cur = clock();
	const clock_t delay = 15;
	if(flag){
		y2 = -h;
		flag = 0;
	}
	if(y2 < 0){
		putimage(0,y2,img2,0);
		putimage(0,y1,img1,0);
	}else{
		putimage(0,y1,img1,0);
		putimage(0,y2,img2,0);
	}

	if(clock() - cur > delay){
	
		if(y1 >= getmaxy())
			y1 = -h;
		else
			y1 += scroll_speed;
		if(y2 >= getmaxy())
			y2 = -h;
		else
			y2 += scroll_speed;
		cur = clock();
	}	
	
}

void spbullet(long sc, int *bulletcount, int add, int res){
	static long psc = 0;
	if(res)
		psc = 0;
	if(sc - psc > 5000){
		(*bulletcount) += add;
		psc = sc;
	}
}

void newexplosion(int x, int y, clock_t time, void **img, int w, int h, int tframe){	
	
	if(exhead == NULL){		//if there are no explosion, create an new list
        exhead = (explosion *)malloc(sizeof(explosion));
        extail = exhead;
        extail -> next = NULL;
        extail -> previous = NULL;
    }else{		//add to queue
        extail -> next = (explosion *)malloc(sizeof(explosion));
        extail -> next -> previous = extail;
        extail  = extail -> next;
        extail -> next = NULL;
    }
    extail -> x = x;
    extail -> y = y;
    extail -> time = time;
    extail -> img = img;
    extail -> w = w;
    extail -> h = h;
    extail -> tframe = tframe;
    extail -> frame = 0;
}

void deleteexplosion(explosion *thispos){
	if(thispos -> previous == NULL && thispos -> next == NULL){	//only one element inside the list
		exhead = NULL;			//let the pointer point to NULL so as to generate a new list
		extail = NULL;
		free(thispos);
	}
	else if(thispos -> previous == NULL){		//the begin of the list
  		thispos -> next -> previous = NULL;
  		exhead = thispos -> next;
		free(thispos);
	}else if(thispos -> next == NULL){		//the end of the list
		extail = thispos -> previous;
		thispos -> previous -> next = NULL;
		free(thispos);
	}else{
		thispos -> previous -> next = thispos -> next;
  		thispos -> next -> previous = thispos -> previous; 
		free(thispos);
	}
}

void updateexplosion(void){
    explosion *ptr = exhead, *dexplosion;
    int w,h;
    const clock_t delay = 40;
    while(ptr != NULL){
    	if(clock() - ptr -> time < delay && ptr -> frame < ptr -> tframe){
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame) + 1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame)], 2);
			ptr -> frame += 1;
			ptr -> time = clock();
			ptr = ptr -> next;
		}else if(ptr -> frame >= ptr -> tframe){
			dexplosion = ptr;
			ptr = ptr -> next;
			deleteexplosion(dexplosion);
		}else{
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame) + 1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame)], 2);
			ptr = ptr -> next;
		}
    }
}

void deleteall(void){
    explosion *ptr = exhead, *buffer;
    while(ptr != NULL){
    	buffer = ptr;
    	ptr = ptr -> next;
    	free(buffer);
    }
    exhead = NULL;	//let the pointer point to NULL so as to generate a new list
    extail = NULL;
}

void cloudinit(cloud *cl, int len){
	int i;
	for(i = 0;i < len;i++){
		cl[i].x = 0;
		cl[i].y = 0;
		cl[i].active = 0;
		cl[i].speed = rand()%2+1;
	}
}

void newcloud(cloud *cl, int len){
	static clock_t t = 0;
	const clock_t  newdelay = 2000;
	int i, j,*x, pos;
	const int num = 3;
	
	x = new int [getmaxx() / 10];
	for(i = 0;i < getmaxx() / 10;i++)
		x[i] = 0;
	
	if(clock() - t > newdelay){
			for(i = 0;i < num;i++){
				pos = rand()%(getmaxx() / 10);
				while(x[pos] != 0)
					pos = rand()%(getmaxx() / 10);
				x[pos] = 1;
				j = 0;
				while(cl[j].active&&j < len)
					j++;
				if(j < len){
					cl[j].x = pos*10 + cl[j].w;
					cl[j].active = 1;
					cl[j].alt = rand()%2;
				}
			}
		t = clock();
		delete []x;
	}
	
	
	
	for(i = 0;i < len;i++){
		if(cl[i].active){
			cl[i].y += cl[i].speed;
			if(cl[i].y - cl[i].h > getmaxy()){
				cl[i].y = 0;
				cl[i].x = 0;
				cl[i].active = 0;
			}
		}
	}

}

void upcloud(cloud *cl, int len){
	int i;
	for(i = 0;i < len;i++){
		if(cl[i].alt && cl[i].active){
			putimage(cl[i].x - cl[i].w/2,cl[i].y-cl[i].h/2,cl[i].img[1],3);
			putimage(cl[i].x - cl[i].w/2,cl[i].y-cl[i].h/2,cl[i].img[0],2);
		}
	}
}

void belowcloud(cloud *cl, int len){
	int i;
	for(i = 0;i < len;i++){
		if((!cl[i].alt) && cl[i].active){
			putimage(cl[i].x - cl[i].w/2,cl[i].y-cl[i].h/2,cl[i].img[1],3);
			putimage(cl[i].x - cl[i].w/2,cl[i].y-cl[i].h/2,cl[i].img[0],2);
		}
	}
}

int button()
{
	    if(GetAsyncKeyState(A_key)!=0) return 0;
        if(GetAsyncKeyState(B_key)!=0) return 1;
        if(GetAsyncKeyState(C_key)!=0) return 2;
        if(GetAsyncKeyState(D_key)!=0) return 3;
        if(GetAsyncKeyState(E_key)!=0) return 4;
        if(GetAsyncKeyState(F_key)!=0) return 5;
        if(GetAsyncKeyState(G_key)!=0) return 6;
        if(GetAsyncKeyState(H_key)!=0) return 7;
        if(GetAsyncKeyState(I_key)!=0) return 8;
        if(GetAsyncKeyState(J_key)!=0) return 9;
        if(GetAsyncKeyState(K_key)!=0) return 10;
        if(GetAsyncKeyState(L_key)!=0) return 11;
        if(GetAsyncKeyState(M_key)!=0) return 12;
        if(GetAsyncKeyState(N_key)!=0) return 13;
        if(GetAsyncKeyState(O_key)!=0) return 14;
        if(GetAsyncKeyState(P_key)!=0) return 15;
        if(GetAsyncKeyState(Q_key)!=0) return 16;
        if(GetAsyncKeyState(R_key)!=0) return 17;
        if(GetAsyncKeyState(S_key)!=0) return 18;
        if(GetAsyncKeyState(T_key)!=0) return 19;
        if(GetAsyncKeyState(U_key)!=0) return 20;
        if(GetAsyncKeyState(V_key)!=0) return 21;
        if(GetAsyncKeyState(W_key)!=0) return 22;
        if(GetAsyncKeyState(X_key)!=0) return 23;
        if(GetAsyncKeyState(Y_key)!=0) return 24;
        if(GetAsyncKeyState(Z_key)!=0) return 25;
        if(GetAsyncKeyState(zero_lkey)!=0) return 26;
        if(GetAsyncKeyState(one_lkey)!=0) return 27;
        if(GetAsyncKeyState(two_lkey)!=0) return 28;
        if(GetAsyncKeyState(three_lkey)!=0) return 29;
        if(GetAsyncKeyState(four_lkey)!=0) return 30;
        if(GetAsyncKeyState(five_lkey)!=0) return 31;
        if(GetAsyncKeyState(six_lkey)!=0) return 32;
        if(GetAsyncKeyState(seven_lkey)!=0) return 33;
        if(GetAsyncKeyState(eight_lkey)!=0) return 34;
        if(GetAsyncKeyState(nine_lkey)!=0) return 35;
        if(GetAsyncKeyState(zero_rkey)!=0) return 36;
        if(GetAsyncKeyState(one_rkey)!=0) return 37;
        if(GetAsyncKeyState(two_rkey)!=0) return 38;
        if(GetAsyncKeyState(three_rkey)!=0) return 39;
        if(GetAsyncKeyState(four_rkey)!=0) return 40;
        if(GetAsyncKeyState(five_rkey)!=0) return 41;
        if(GetAsyncKeyState(six_rkey)!=0) return 42;
        if(GetAsyncKeyState(seven_rkey)!=0) return 43;
        if(GetAsyncKeyState(eight_rkey)!=0) return 44;
        if(GetAsyncKeyState(nine_rkey)!=0) return 45;
        if(GetAsyncKeyState(BACKSPACE)!=0) return 46;
        if(GetAsyncKeyState(enter_key)!=0) return 47;
        return 49;
}

void save_record(char *s, long sc, int level){
	FILE *fp = fopen("record.txt","a");
	if(!strcmp(s,""))
		fprintf(fp,"%d %ld %s ",level,sc,"Unknown");
	else
		fprintf(fp,"%d %ld %s ",level,sc,s);
	fclose(fp);
}

void cal_record(){
	FILE *fp = fopen("record.txt","r");
	int num = 0,l,*level,i,j,ltemp,numt;
	long sc = 0, *score,sctemp;
	char n[11] = "", **name, ntemp[11] = "";
	while(fscanf(fp,"%d %ld %s",&l,&sc,&n) != EOF)
		num++;
	level = new int[num];
	score = new long[num];
	name = new char * [num];
	for(i = 0;i < num;i++){
		name[i] = new char [11];
        strcpy(name[i],"");
	}
	num = 0;
	rewind(fp);
	while(fscanf(fp,"%d %ld %s",&level[num],&score[num],name[num]) != EOF)
		num++;
	for(i = 0;i < num - 1;i++)
		for(j = i+1;j < num;j++){
			if(score[i] < score[j]){
				sctemp = score[i];
				ltemp = level[i];
				strcpy(ntemp,name[i]);
				score[i] = score[j];
				level[i] = level[j];
				strcpy(name[i],name[j]);
				score[j] = sctemp;
				level[j] = ltemp;
				strcpy(name[j],ntemp);
			}
		}
	fclose(fp);
	fp = fopen("record.txt", "w");
	numt = num;
	if(num > 30)
		num = 30;
	for(i = 0;i < num;i++)
		fprintf(fp,"%d %ld %s ",level[i],score[i],name[i]);
	fclose(fp);
	delete []level;
	delete []score;
	for(i = 0;i < numt;i++)
		delete []name[i];
	delete []name;
}

void name_enter(long sc,int level)
{
	void load_record();
	char str[11] = "";
	int i,cur_page=0,count=0,lastindex;
	clock_t cur = clock();
	char *s[46]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9","0","1","2","3","4","5","6","7","8","9"};
	setfillstyle(0,WHITE);
	settextstyle(8,0,5);
	while(1)
    {
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
	    cleardevice();
	    readimagefile(".\\img\\background3.jpg",0,0,getmaxx(),getmaxy());
		readimagefile(".\\img\\name.gif",getmaxx()/2-50,getmaxy()/2-50,getmaxx()/2+50,getmaxy()/2);
		outtextxy(getmaxx()/7,getmaxy()/2, "ENTER:");
	    i=button();
	    if(i<46)
	    {	
	    	if(strlen(str) < 10)
	   			strcat(str,s[i]);
	    }
	    else if(i==46)
	    {
	    	lastindex = strlen(str);
	    	if(lastindex >= 1)
	    		str[lastindex - 1] = '\0';
	    }
	    else if(i==47)
	    {
	    	save_record(str,sc,level);
	    	cal_record();
	    	break;
	    }
	    cur = clock();
	    outtextxy(getmaxx()/3,getmaxy()/2,str);
	    delay(80);
    }

}

void load_record(char ***buf,int &number, int **level){
	FILE *fp = fopen("record.txt","r");
	int num = 0,l,i,j,ltemp;
	long sc = 0, *score,sctemp;
	char n[11] = "", **name, ntemp[11] = "";
	while(fscanf(fp,"%d %ld %s",&l,&sc,&n) != EOF)
		num++;
	(*level) = new int[num];
	score = new long[num];
	name = new char * [num];
	(*buf) = new char * [num];
	for(i = 0;i < num;i++){
		name[i] = new char [11];
		(*buf)[i] = new char [32];
	}
	num = 0;
	rewind(fp);
	while(fscanf(fp,"%d %ld %s",&((*level)[num]),&score[num],name[num]) != EOF)
		num++;
	for(i = 0;i < num;i++)
		sprintf((*buf)[i],"%-11s%-7ld",name[i],score[i]);
	number = num;
	
	delete []score;
}

void newhp(void **img,int w,int h,lifeplus **head,lifeplus **tail,int x,int y)
{
	if(*head==NULL)
	{
		*head = (lifeplus *)malloc(sizeof(lifeplus));
        (*tail) = *head;
        (*tail) -> next = NULL;
        (*tail) -> previous = NULL;
	}
	else
	{
		(*tail) -> next = (lifeplus *)malloc(sizeof(lifeplus));
        (*tail) -> next -> previous = (*tail);
        (*tail)  = (*tail) -> next;
        (*tail) -> next = NULL;
	}
	(*tail) -> x = x;
    (*tail) -> y = y;
    (*tail) -> speed = 3;
    (*tail) -> angle = 0.75*PI;
    (*tail) -> img = img;
    (*tail) -> r = (w+h)/2;
    (*tail) -> w = w;
    (*tail) -> h = h;
}

void deletehp(lifeplus *thishp,lifeplus **first,lifeplus **tail)
{
	if(thishp -> previous == NULL && thishp -> next == NULL){	//only one element inside the list
		*first = NULL;			//let the pointer point to NULL so as to generate a new list
		*tail = NULL;
		free(thishp);
	}
	else if(thishp -> previous == NULL){		//the begin of the list
  		thishp -> next -> previous = NULL;
  		*first = thishp -> next;
		free(thishp);
	}else if(thishp -> next == NULL){		//the end of the list
		*tail = thishp -> previous;
		thishp -> previous -> next = NULL;
		free(thishp);
	}else{
		thishp -> previous -> next = thishp -> next;
  		thishp -> next -> previous = thishp -> previous; 
		free(thishp);
	}
}

void changehp(lifeplus *thishp, double speed, double angle){ //change the value of one lifeplus
	thishp -> speed = speed;
	thishp -> angle = angle;
}

void updatehp(lifeplus **first,lifeplus **tail,plane *myplane)
{
	lifeplus *ptr = *first, *dhp;
    int w,h;
    int maxx,maxy;
    double dir;
    maxx = getmaxx();
    maxy = getmaxy();
    while(ptr != NULL){
    	ptr -> x += (int) ((ptr -> speed)*cos(ptr -> angle));	//update position
    	ptr -> y += (int) ((ptr ->	speed)*sin(ptr -> angle));
    	if(sq(ptr->x - myplane->x)+sq(ptr->y - myplane->y) < sq(ptr->r))
    	{
    		deletehp(ptr,first,tail);
    		myplane->life=150;
    	}
    	else if(ptr -> y + ptr->r > getmaxy()){
					ptr -> y = getmaxy() - ptr->r;
					dir = 2.0 * PI - ptr -> angle;
					changehp(ptr, 3, dir);
				}else if(ptr -> y - ptr->r < 0){
					ptr -> y = ptr->r;
					dir = 2.0 * PI - ptr -> angle;
					changehp(ptr, 3, dir);
				}else if(ptr -> x + ptr->r > getmaxx()){
					ptr -> x = getmaxx() - ptr->r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					changehp(ptr, 3, dir);
				}else if(ptr -> x - ptr->r < 0){
					ptr -> x = ptr->r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					changehp(ptr, 3, dir);
				}
    	if(ptr!=NULL){
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[0], 2);
			ptr = ptr -> next;
		}	
    }
}

void deleteall(lifeplus **head,lifeplus **tail){
    lifeplus *ptr = *head, *buffer;
    while(ptr != NULL){
    	buffer = ptr;
    	ptr = ptr -> next;
    	free(buffer);
    }
    *head = NULL;	//let the pointer point to NULL so as to generate a new list
    *tail = NULL;
}

void newspbp(void **img,int w,int h,spbulletplus **head,spbulletplus **tail,int x,int y)
{
	if(*head==NULL)
	{
		*head = (spbulletplus *)malloc(sizeof(spbulletplus));
        (*tail) = *head;
        (*tail) -> next = NULL;
        (*tail) -> previous = NULL;
	}
	else
	{
		(*tail) -> next = (spbulletplus *)malloc(sizeof(spbulletplus));
        (*tail) -> next -> previous = (*tail);
        (*tail)  = (*tail) -> next;
        (*tail) -> next = NULL;
	}
	(*tail) -> x = x;
    (*tail) -> y = y;
    (*tail) -> speed = 3;
    (*tail) -> angle = 0.25*PI;
    (*tail) -> img = img;
    (*tail) -> r = (w+h)/2;
    (*tail) -> w = w;
    (*tail) -> h = h;
}

void deletespbp(spbulletplus *thishp,spbulletplus **first,spbulletplus **tail)
{
	if(thishp -> previous == NULL && thishp -> next == NULL){	//only one element inside the list
		*first = NULL;			//let the pointer point to NULL so as to generate a new list
		*tail = NULL;
		free(thishp);
	}
	else if(thishp -> previous == NULL){		//the begin of the list
  		thishp -> next -> previous = NULL;
  		*first = thishp -> next;
		free(thishp);
	}else if(thishp -> next == NULL){		//the end of the list
		*tail = thishp -> previous;
		thishp -> previous -> next = NULL;
		free(thishp);
	}else{
		thishp -> previous -> next = thishp -> next;
  		thishp -> next -> previous = thishp -> previous; 
		free(thishp);
	}
}

void changespbp(spbulletplus *thishp, double speed, double angle){ //change the value of one lifeplus
	thishp -> speed = speed;
	thishp -> angle = angle;
}

int updatespbp(spbulletplus **first,spbulletplus **tail,plane *myplane)
{
	spbulletplus *ptr = *first, *dhp;
    int w,h;
    int maxx,maxy;
    double dir;
    maxx = getmaxx();
    maxy = getmaxy();
    while(ptr != NULL){
    	ptr -> x += (int) ((ptr -> speed)*cos(ptr -> angle));	//update position
    	ptr -> y += (int) ((ptr ->	speed)*sin(ptr -> angle));
    	if(sq(ptr->x - myplane->x)+sq(ptr->y - myplane->y) < sq(ptr->r))
    	{
    		deletespbp(ptr,first,tail);
    		return 1;
    	}
    	else if(ptr -> y + ptr->r > getmaxy()){
					ptr -> y = getmaxy() - ptr->r;
					dir = 2.0 * PI - ptr -> angle;
					changespbp(ptr, 3, dir);
				}else if(ptr -> y - ptr->r < 0){
					ptr -> y = ptr->r;
					dir = 2.0 * PI - ptr -> angle;
					changespbp(ptr, 3, dir);
				}else if(ptr -> x + ptr->r > getmaxx()){
					ptr -> x = getmaxx() - ptr->r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					changespbp(ptr, 3, dir);
				}else if(ptr -> x - ptr->r < 0){
					ptr -> x = ptr->r;
					if(ptr -> angle > PI)
						dir = 3.0*PI - ptr -> angle;
					else
						dir = PI - ptr -> angle;
					changespbp(ptr, 3, dir);
				}
    	if(ptr!=NULL){
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[0], 2);
			ptr = ptr -> next;
		}	
    }
    return 0;
}

void deleteall(spbulletplus **head,spbulletplus **tail){
    spbulletplus *ptr = *head, *buffer;
    while(ptr != NULL){
    	buffer = ptr;
    	ptr = ptr -> next;
    	free(buffer);
    }
    *head = NULL;	//let the pointer point to NULL so as to generate a new list
    *tail = NULL;
}

void newbspb(boss_sp_bullet **head,boss_sp_bullet **tail,int x, int y, clock_t time, void **img, int w, int h, int tframe, double speed, double angle,double r){	
	
	if(*head == NULL){		//if there are no explosion, create an new list
        (*head) = (boss_sp_bullet *)malloc(sizeof(boss_sp_bullet));
        (*tail) = (*head);
        (*tail) -> next = NULL;
        (*tail) -> previous = NULL;
    }else{		//add to queue
        (*tail) -> next = (boss_sp_bullet *)malloc(sizeof(boss_sp_bullet));
        (*tail) -> next -> previous = (*tail);
        (*tail)  = (*tail) -> next;
        (*tail) -> next = NULL;
    }
    (*tail) -> x = x;
    (*tail) -> y = y;
    (*tail) -> time = time;
    (*tail) -> img = img;
    (*tail) -> w = w;
    (*tail) -> h = h;
    (*tail) -> tframe = tframe;
    (*tail) -> frame = 0;
    (*tail) -> angle=angle;
    (*tail) -> speed = speed;
    (*tail) -> r = r;
}

void deletebspb(boss_sp_bullet *thispos,boss_sp_bullet **head,boss_sp_bullet **tail){
	if(thispos -> previous == NULL && thispos -> next == NULL){	//only one element inside the list
		*head = NULL;			//let the pointer point to NULL so as to generate a new list
		*tail = NULL;
		free(thispos);
	}
	else if(thispos -> previous == NULL){		//the begin of the list
  		thispos -> next -> previous = NULL;
  		*head = thispos -> next;
		free(thispos);
	}else if(thispos -> next == NULL){		//the end of the list
		*tail = thispos -> previous;
		thispos -> previous -> next = NULL;
		free(thispos);
	}else{
		thispos -> previous -> next = thispos -> next;
  		thispos -> next -> previous = thispos -> previous; 
		free(thispos);
	}
}

void updatebspb(boss_sp_bullet **head,boss_sp_bullet **tail){
    boss_sp_bullet *ptr = *head, *dexplosion;
    int w,h;
    const clock_t delay = 40;
    while(ptr != NULL){
    	ptr -> x += (int) ((ptr -> speed)*cos(ptr -> angle));	//update position
    	ptr -> y += (int) ((ptr ->	speed)*sin(ptr -> angle));
    	if((ptr -> x + ptr -> r) > 0 && (ptr -> x - ptr -> r) < getmaxx() &&	//detect whether the bullet inside the window
    		(ptr -> y + ptr -> r) > 0 && (ptr -> y - ptr -> r) < getmaxy())
    	{
    		if(clock() - ptr -> time < delay && ptr -> frame < ptr -> tframe)
			{
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame) + 1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame)], 2);
			ptr -> frame ++;
			ptr -> time = clock();
			ptr = ptr -> next;
		    }
			else if(ptr -> frame >= ptr -> tframe)
			{
			ptr->frame=0;
			ptr = ptr -> next;
		    }
			else
			{
			w = ptr -> w;
			h = ptr -> h;	
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame) + 1], 3);
			putimage(ptr -> x - w/2, ptr -> y - h/2, ptr -> img[2*(ptr -> frame)], 2);
			ptr = ptr -> next;
		    }
    	}
    	else
    	{
    		dexplosion = ptr;
    		ptr = ptr -> next;
    		deletebspb(dexplosion,head,tail);
    	}
    }
}

void deleteall(boss_sp_bullet **head,boss_sp_bullet **tail){
    boss_sp_bullet *ptr = *head, *buffer;
    while(ptr != NULL){
    	buffer = ptr;
    	ptr = ptr -> next;
    	free(buffer);
    }
    *head = NULL;	//let the pointer point to NULL so as to generate a new list
    *tail = NULL;
}
