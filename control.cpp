#include<windows.h>
#define UP_ARROW 0x26
#define LEFT_ARROW 0x25
#define DOWN_ARROW 0x28
#define RIGHT_ARROW 0x27
#define SPACEBAR 0x20 
#define ESC 0x1B
#define CTRL 0x11

int way(int *p)   // p is up down left right
{
   int k=0;
   for(int i=0;i<4;i++)
     if(p[i]!=0)
       k++;
   
   if(k==0) return 0;
   else if(k==1)
   {
      if(p[0]==1)      // up
	    return 1;
      else if(p[1]==1) // down
	    return 2;
      else if(p[2]==1) // left
	    return 3;
      else             // right
	    return 4;
   }
   else if(k==2)
   {
      if(p[0]==1 && p[3]==1)      //up & right
	    return 5;
      else if(p[0]==1 && p[1]==1) //up & left
	    return 6;
      else if(p[1]==1 && p[2]==1) //down & left
	    return 7;
      else if(p[2]==1 && p[3]==1) //down & right
	    return 8;
   }
   else
     return 0;
}
void control(int *x)//x為一陣列 
 
{
	int c[4]={0};    // c is up down left right

		if(GetAsyncKeyState(UP_ARROW)==0) c[0]=0;
        if(GetAsyncKeyState(LEFT_ARROW)==0) c[1]=0;
        if(GetAsyncKeyState(DOWN_ARROW)==0) c[2]=0;
        if(GetAsyncKeyState(RIGHT_ARROW)==0) c[3]=0;
        if(GetAsyncKeyState(SPACEBAR)==0) x[1]=0;//空白鍵控制一般攻擊
        if(GetAsyncKeyState(CTRL)==0) x[2]=0;//CTRL鍵放絕招  
        if(GetAsyncKeyState(ESC)==0) x[3]=0;//ESC結束遊戲 
        
        
        if(GetAsyncKeyState(UP_ARROW)!=0) c[0]=1;
        if(GetAsyncKeyState(LEFT_ARROW)!=0) c[1]=1;
        if(GetAsyncKeyState(DOWN_ARROW)!=0) c[2]=1;
        if(GetAsyncKeyState(RIGHT_ARROW)!=0) c[3]=1;
        if(GetAsyncKeyState(SPACEBAR)!=0) x[1]=1; 
        if(GetAsyncKeyState(CTRL)!=0) x[2]=1;
        if(GetAsyncKeyState(ESC)!=0) x[3]=1;
        
        
        x[0]=way(c);

}
