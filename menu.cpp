#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include "game.h"
#include "utilize.h"

extern int music_flag;

void options_menu();
void record_menu();
void start_menu();

void main_menu()
{
    int i,j,cur_page=1,exit=1;
    char mfname[64] = ".\\music\\ground.mp3";
    play_bgm(mfname);
    while(exit)
    {
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
    	setbkcolor(BLACK);
	    cleardevice();//清畫面 
    	
    	readimagefile(".\\img\\background2.jpg",0,0,getmaxx(),getmaxy());
    	readimagefile(".\\img\\start_button2.gif",getmaxx()/2-100,getmaxy()/2-75,getmaxx()/2+100,getmaxy()/2-25);
    	readimagefile(".\\img\\options_button2.gif",getmaxx()/2-100,getmaxy()/2,getmaxx()/2+100,getmaxy()/2+50);
    	readimagefile(".\\img\\record_button2.gif",getmaxx()/2-100,getmaxy()/2+75,getmaxx()/2+100,getmaxy()/2+125);
    	readimagefile(".\\img\\exit_button2.gif",getmaxx()/2-100,getmaxy()/2+150,getmaxx()/2+100,getmaxy()/2+200);
    	
    	for(i=-1;i<=2;i++)
        if(mousex()>getmaxx()/2-100&&mousex()<getmaxx()/2+100&&mousey()>getmaxy()/2+75*i&&mousey()<getmaxy()/2+75*i+50)//判斷滑鼠位置來產生不同視覺效果 
        {
        	if(i==-1)
        	{    
				readimagefile(".\\img\\start_button1.gif",getmaxx()/2-100,getmaxy()/2+75*i,getmaxx()/2+100,getmaxy()/2+75*i+50);
				if(ismouseclick(WM_LBUTTONDOWN))
				{
					clearmouseclick(WM_LBUTTONDOWN);
					//infinity();
					start_menu();
				} 
        	} 
			if(i==0)
        	{    
				readimagefile(".\\img\\options_button1.gif",getmaxx()/2-100,getmaxy()/2+75*i,getmaxx()/2+100,getmaxy()/2+75*i+50);
        	    if(ismouseclick(WM_LBUTTONDOWN))
        	    {
        	    	clearmouseclick(WM_LBUTTONDOWN);
        	    	options_menu();
        	    }
			} 
			if(i==1)
        	{    
				readimagefile(".\\img\\record_button1.gif",getmaxx()/2-100,getmaxy()/2+75*i,getmaxx()/2+100,getmaxy()/2+75*i+50);
				if(ismouseclick(WM_LBUTTONDOWN))
				{
					clearmouseclick(WM_LBUTTONDOWN);
					record_menu();
				}
        	} 
			if(i==2)
        	{    
				readimagefile(".\\img\\exit_button1.gif",getmaxx()/2-100,getmaxy()/2+75*i,getmaxx()/2+100,getmaxy()/2+75*i+50);
				if(ismouseclick(WM_LBUTTONDOWN))
				{
					clearmouseclick(WM_LBUTTONDOWN);
					exit=0;
					close_bgm(mfname);
				}
            } 
        }
        clearmouseclick(WM_LBUTTONDOWN);
	}
}
void start_menu()
{
	int i,j,cur_page=1,back=1;
	char mfname[64] = ".\\music\\ground.mp3";
	while(back)
	{
		setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page); 
    	setbkcolor(BLACK);
	    cleardevice();//清畫面
	    
	    readimagefile(".\\img\\background2.jpg",0,0,getmaxx(),getmaxy());
	    readimagefile(".\\img\\easy1.bmp",getmaxx()/2-100,getmaxy()/5,getmaxx()/2+100,getmaxy()/5+50);
        readimagefile(".\\img\\medium1.bmp",getmaxx()/2-100,getmaxy()/5*2,getmaxx()/2+100,getmaxy()/5*2+50);
        readimagefile(".\\img\\hard1.bmp",getmaxx()/2-100,getmaxy()/5*3,getmaxx()/2+100,getmaxy()/5*3+50);
        readimagefile(".\\img\\home_button_files_2.gif",getmaxx()/2-25,getmaxy()/5*4,getmaxx()/2+25,getmaxy()/5*4+50);
        
        for(i=1;i<4;i++)
        if(mousex()>getmaxx()/2-100&&mousex()<getmaxx()/2+100&&mousey()>getmaxy()/5*i&&mousey()<getmaxy()/5*i+50)//判斷滑鼠位置來產生不同視覺效果 
        {
    	   	if(i==1)
        	{    
				readimagefile(".\\img\\easy2.bmp",getmaxx()/2-100,getmaxy()/5*i,getmaxx()/2+100,getmaxy()/5*i+50);
				if(ismouseclick(WM_LBUTTONDOWN))
				{
					clearmouseclick(WM_LBUTTONDOWN);
					close_bgm(mfname);
					easy();
					play_bgm(mfname);
				} 
        	} 
        	if(i==2)
        	{ 
        	    readimagefile(".\\img\\medium2.bmp",getmaxx()/2-100,getmaxy()/5*i,getmaxx()/2+100,getmaxy()/5*i+50);
        	    if(ismouseclick(WM_LBUTTONDOWN))
        	    {
				    clearmouseclick(WM_LBUTTONDOWN);
				    close_bgm(mfname);
				    medium();
				    play_bgm(mfname);
        	    }
        	} 
			if(i==3)
        	{    
				readimagefile(".\\img\\hard2.bmp",getmaxx()/2-100,getmaxy()/5*i,getmaxx()/2+100,getmaxy()/5*i+50);
        	    if(ismouseclick(WM_LBUTTONDOWN))
        	    {
        	    	clearmouseclick(WM_LBUTTONDOWN);
        	    	close_bgm(mfname);
        	    	hard();
        	    	play_bgm(mfname);
        	    }
			} 
        }
        if((mousex()-getmaxx()/2)*(mousex()-getmaxx()/2)+(mousey()-getmaxy()/5*4-25)*(mousey()-getmaxy()/5*4-25)<=625)
        {
        		readimagefile(".\\img\\home_button_files_1.gif",getmaxx()/2-25,getmaxy()/5*4,getmaxx()/2+25,getmaxy()/5*4+50);
        		if(ismouseclick(WM_LBUTTONDOWN))
        	    {
        	    	clearmouseclick(WM_LBUTTONDOWN);
        	    	back=0;
        	    }
        }
        clearmouseclick(WM_LBUTTONDOWN);
	}
}

void options_menu()
{
    int i,j,cur_page=1,back=1;
    static int c = music_flag;
    FILE *fp = fopen("option.txt","w");
    
    while(back)
    {
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
		setbkcolor(BLACK);
	    cleardevice();//清畫面
    	
    	readimagefile(".\\img\\background2.jpg",0,0,getmaxx(),getmaxy());
    	readimagefile(".\\img\\MUSIC.gif",50,getmaxy()/5,300,getmaxy()/5+50);
    	if(c==1)
    	readimagefile(".\\img\\on_button2.gif",getmaxx()/3*2,getmaxy()/5,getmaxx()/3*2+100,getmaxy()/5+50);
    	if(c==0)
    	readimagefile(".\\img\\off_button2.gif",getmaxx()/3*2,getmaxy()/5,getmaxx()/3*2+100,getmaxy()/5+50);
    	readimagefile(".\\img\\home_button_options_2.gif",getmaxx()/2-25,getmaxy()/5*4,getmaxx()/2+25,getmaxy()/5*4+50);
    	
    	
        if(mousex()>getmaxx()/3*2&&mousex()<getmaxx()/3*2+100&&mousey()>getmaxy()/5&&mousey()<getmaxy()/5+50)//判斷滑鼠位置來產生不同視覺效果 
        {
        	if(c==1)
        	readimagefile(".\\img\\on_button1.gif",getmaxx()/3*2,getmaxy()/5,getmaxx()/3*2+100,getmaxy()/5+50);
        	if(c==0)
    	    readimagefile(".\\img\\off_button1.gif",getmaxx()/3*2,getmaxy()/5,getmaxx()/3*2+100,getmaxy()/5+50);
            if(ismouseclick(WM_LBUTTONDOWN))  //WM_LBUTTONDOWN
            {
                clearmouseclick(WM_LBUTTONDOWN);
                rewind(fp);
                music_flag = -music_flag + 1;
                fprintf(fp,"%d",music_flag);
                c=-c+1;
            }
        }
        if((mousex()-getmaxx()/2)*(mousex()-getmaxx()/2)+(mousey()-getmaxy()/5*4-25)*(mousey()-getmaxy()/5*4-25)<=625)
        {
        		readimagefile(".\\img\\home_button_options_1.gif",getmaxx()/2-25,getmaxy()/5*4,getmaxx()/2+25,getmaxy()/5*4+50);
        		if(ismouseclick(WM_LBUTTONDOWN))
        	    {
        	    	clearmouseclick(WM_LBUTTONDOWN);
        	    	back=0;
        	    }
        }
        clearmouseclick(WM_LBUTTONDOWN);
	}
	fclose(fp);
}
void record_menu()
{
	char *s[10]={"1","2","3","4","5","6","7","8","9","10"};
	int i,j,cur_page=1,back=1,number,flag = 0,*level,count = 0;
	char **buf;
	settextstyle(8,0,5);
    load_record(&buf,number,&level);
    while(back)
    {
    	setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
		setbkcolor(BLACK);
	    cleardevice();//清畫面
	    
	    readimagefile(".\\img\\background2.jpg",0,0,getmaxx(),getmaxy());
	    readimagefile(".\\img\\home_button_record_2.gif",getmaxx()/2-25,getmaxy()/5*4,getmaxx()/2+25,getmaxy()/5*4+50);
	    readimagefile(".\\img\\record_easy.bmp",getmaxx()/3*0,getmaxy()/5*3,getmaxx()/3*1,getmaxy()/5*3+50);
	    readimagefile(".\\img\\record_medium.bmp",getmaxx()/3*1,getmaxy()/5*3,getmaxx()/3*2,getmaxy()/5*3+50);
	    readimagefile(".\\img\\record_hard.bmp",getmaxx()/3*2,getmaxy()/5*3,getmaxx(),getmaxy()/5*3+50);
	    
	    
    	for(i=0;i<10;i++)
    	{
    		setcolor(WHITE);
    		outtextxy(getmaxx()/5,0,"name       score");
			outtextxy(50,100+textheight(s[i])*i,s[i]);
    	}
    	if((mousex()-getmaxx()/2)*(mousex()-getmaxx()/2)+(mousey()-getmaxy()/5*4-25)*(mousey()-getmaxy()/5*4-25)<=625)
        {
        		readimagefile(".\\img\\home_button_record_1.gif",getmaxx()/2-25,getmaxy()/5*4,getmaxx()/2+25,getmaxy()/5*4+50);
        		if(ismouseclick(WM_LBUTTONDOWN))
        	    {
        	    	clearmouseclick(WM_LBUTTONDOWN);
        	    	back=0;
        	    }
        }
        for(i=0;i<=2;i++)
        {
        	if(mousex()>getmaxx()/3*i && mousex()<getmaxx()/3*(i+1) && mousey()>getmaxy()/5*3 && mousey()<getmaxy()/5*3+50)
        	{
        		if(i==0)
        		{
        			readimagefile(".\\img\\record_easy2.bmp",getmaxx()/3*i,getmaxy()/5*3,getmaxx()/3*(i+1),getmaxy()/5*3+50);
        		    if(ismouseclick(WM_LBUTTONDOWN))
        	        {
        	    	    clearmouseclick(WM_LBUTTONDOWN);
        	    	    flag = 1;
        	        }
        		}
        		if(i==1)
        		{
        			readimagefile(".\\img\\record_medium2.bmp",getmaxx()/3*i,getmaxy()/5*3,getmaxx()/3*(i+1),getmaxy()/5*3+50);
        		    if(ismouseclick(WM_LBUTTONDOWN))
        	        {
        	    	    clearmouseclick(WM_LBUTTONDOWN);
        	    	    flag = 2;
        	        }
        		}
        		if(i==2)
        		{
        			readimagefile(".\\img\\record_hard2.bmp",getmaxx()/3*i,getmaxy()/5*3,getmaxx()/3*(i+1),getmaxy()/5*3+50);
        		    if(ismouseclick(WM_LBUTTONDOWN))
        	        {
        	    	    clearmouseclick(WM_LBUTTONDOWN);
        	    	    flag = 3;
        	        }
        		}
        	}
        }
        clearmouseclick(WM_LBUTTONDOWN);
        switch(flag){
        	case 1:
        		count = 0;
        		for(i = 0;i < number;i++){
        			if(level[i] == 1){
        				outtextxy(getmaxx()/5,100+textheight(buf[i])*count,buf[i]);
        				count++;
        			}
        			if(count >= 10)
        				break;
				}
				break;
			case 2:
				count = 0;
        		for(i = 0;i < number;i++){
        			if(level[i] == 2){
        				outtextxy(getmaxx()/5,100+textheight(buf[i])*count,buf[i]);
        				count++;
        			}
        			if(count >= 10)
        				break;
				}
				break;
			case 3:
				count = 0;
        		for(i = 0;i < number;i++){
        			if(level[i] == 3){
        				outtextxy(getmaxx()/5,100+textheight(buf[i])*count,buf[i]);
        				count++;
        			}
        			if(count >= 10)
        				break;
				}
				break;
			default:
        		for(i = 0;i < 10;i++)
        			outtextxy(getmaxx()/5,100+textheight(buf[i])*i,buf[i]);
				break;
        }
    }
    for(i = 0;i < number;i++)
    	delete []buf[i];
    delete []buf;
    delete []level;
}

int esc_menu()
{
	int i,j,cur_page=1,back=1,flag = 1;
	while(back)
	{
		setvisualpage(cur_page);
    	cur_page=-cur_page+1;
    	setactivepage(cur_page);
		setbkcolor(BLACK);
	    cleardevice();//清畫面
	    
	    readimagefile(".\\img\\background.jpg",0,0,getmaxx(),getmaxy());
	    readimagefile(".\\img\\esc_button_retry1.bmp",getmaxx()/2-100,getmaxy()/6*2,getmaxx()/2+100,getmaxy()/6*2+50);
	    readimagefile(".\\img\\options_button2.gif",getmaxx()/2-100,getmaxy()/6*3,getmaxx()/2+100,getmaxy()/6*3+50);
	    readimagefile(".\\img\\resume1.bmp",getmaxx()/2-100,getmaxy()/6*4,getmaxx()/2+100,getmaxy()/6*4+50);
	    readimagefile(".\\img\\exit_button2.gif",getmaxx()/2-100,getmaxy()/6*5,getmaxx()/2+100,getmaxy()/6*5+50);
	    
	    for(i=2;i<=5;i++)
	    {
	    	if(mousex()>getmaxx()/2-100&&mousex()<getmaxx()/2+100&&mousey()>getmaxy()/6*i&&mousey()<getmaxy()/6*i+50)
	    	{
	    		if(i==2)
	    		{
	    		    readimagefile(".\\img\\esc_button_retry2.bmp",getmaxx()/2-100,getmaxy()/6*i,getmaxx()/2+100,getmaxy()/6*i+50);
	    		        if(ismouseclick(WM_LBUTTONDOWN))
				    {
					    clearmouseclick(WM_LBUTTONDOWN);
					    flag = 2;
					    back = 0;
				    }
	    		}
	    		if(i==3)
	    		{
	    			readimagefile(".\\img\\options_button1.gif",getmaxx()/2-100,getmaxy()/6*i,getmaxx()/2+100,getmaxy()/6*i+50);
	    			if(ismouseclick(WM_LBUTTONDOWN))
				    {
						clearmouseclick(WM_LBUTTONDOWN);
						options_menu();
				    }
	    		}
	    		if(i==5)
	    		{
	    			readimagefile(".\\img\\exit_button1.gif",getmaxx()/2-100,getmaxy()/6*i,getmaxx()/2+100,getmaxy()/6*i+50);
	    			if(ismouseclick(WM_LBUTTONDOWN))
				    {
					    clearmouseclick(WM_LBUTTONDOWN);
					    flag = 0;
					    back = 0;
				    }
	    		}
	    		if(i==4)
	    		{
	    			readimagefile(".\\img\\resume2.bmp",getmaxx()/2-100,getmaxy()/6*i,getmaxx()/2+100,getmaxy()/6*i+50);
	    			if(ismouseclick(WM_LBUTTONDOWN))
				    {
					    clearmouseclick(WM_LBUTTONDOWN);
				        back=0;
					}
	    		}
	    	}
	    	
	    }
	}
	return flag;
}
