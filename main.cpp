#include <cstdlib>
#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include "menu.h"
using namespace std;

int music_flag;

int main(int argc, char *argv[])
{
	FILE *fp = fopen("option.txt","r");
	if(fp != NULL)
		fscanf(fp,"%d",&music_flag);
	else
		music_flag = 1;
		
	fclose(fp);
	
	initwindow(768,960, "蒼穹之翼");
    
    main_menu();
    
    
    closegraph();
    return 0;
}
