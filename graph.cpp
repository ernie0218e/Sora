#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

int gifinfo(const char *fname, int *w, int *h){
	FILE *fp;
	char ch;
	short temp;
	
	fp = fopen(fname, "rb");
	rewind(fp);
	fread(&ch, sizeof(char), 1, fp);
	if(fp == NULL){
		showerrorbox("File can't open");
		return 0;
	}else if(ch == 'G'){
		fseek(fp, 6, SEEK_SET);
		fread(&temp, sizeof(temp), 1, fp);
		*w = temp;
		fseek(fp, 8, SEEK_SET);
		fread(&temp, sizeof(temp), 1, fp);
		*h = temp;
		return 1;
	}else
		return 0;
	
	fclose(fp);
}

int bmpinfo(const char *fname, int *w, int *h){
	FILE *fp = NULL;
	fp = fopen(fname, "rb");
    if(fp == NULL){
        showerrorbox("File can't open");
        return 0;
    }else{
    	fseek(fp, 18, SEEK_SET);    //Get width & height of image
    	fread(w, sizeof(int), 1, fp);
    	fread(h, sizeof(int), 1, fp);
    	return 1;
    }
    fclose(fp);
}

void graphinfo(const char *fname, int *w, int *h){
	if(!gifinfo(fname, w, h))
		bmpinfo(fname, w, h);
}

