#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include "graph.h"


void initimg(char *fname, void **img){
	int w,h;
	graphinfo(fname,&w,&h);
	readimagefile(fname,0,0,w,h);
	*img = malloc(imagesize(0,0,w,h));
	getimage(0,0,w,h,*img);
}

int graphinit(const char *fname, void ***img, int **width, int **height){
	FILE *fp = fopen(fname, "r");
	
	char buf[128];
	int	count = 0;
	int w,h;
	
	if(fp != NULL){
	
		setactivepage(0);
		setvisualpage(1);
		while(fgets(buf, sizeof(buf), fp) != NULL)
			count++;

		*img = (void **)malloc(count * sizeof(void *));
		*width = (int *)malloc(count * sizeof(int));
		*height = (int *)malloc(count * sizeof(int));
		
		count = 0;
		rewind(fp);
	
		while(fscanf(fp, "%s", buf) != EOF){
			graphinfo(buf,&w,&h);
			(*width)[count] = w;
			(*height)[count] = h;
			readimagefile(buf,0,0,w,h);
			(*img)[count] = malloc(imagesize(0,0,w,h));
			getimage(0,0,w,h,(*img)[count]);
			count++;
		}
		cleardevice();
	}
	return count;
}
