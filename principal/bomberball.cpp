#include<stdlib.h>
#include<stdio.h>
#include "conio.c"
#include<conio.h>

#define S1 1//smile1
#define S2 2//smile2
#define HT 3//heart
#define LG 4//losangle
#define TR 5//tree
#define SW 6//sword
#define B1 11//bomb1
#define B2 15//bomb2
#define B3 149//bomb3
#define B4 155//bomb4
#define B5 157//bomb5
#define B6 162//bomb6
#define B7 207//bomb7
#define B8 224//bomb8
#define B9 227//bomb9
#define SP 175//speed
#define R1 176//rock1
#define R2 177//rock2
#define R3 178//rock3
#define NR 219//normal retangle
#define DR 220//down retangle
#define UR 223//up retangle
#define SQ 254//square
#define RT 16 //right triangle
#define LT 17//left triangle
#define UT 30//up triangle
#define DT 31//down triangle
#define VL 186//vertical line
#define HL 205//horizontal line
#define ULB 201 //up left board
#define DLB 200 //down left board
#define URB 187 //up right board
#define DRB 188 //down right board
#define UL 238//up line
#define DL 95//down line
#define LB 92//left bar
#define RB 47//right bar
#define CC 79//circle
#define E1 226//eye 1
#define TC(a) textcolor(a)

typedef struct block
{
        int a;//ascii
        int c;//color
        int e;//effect
};

//***Funções ordem 1***
void BLOCK(block A[13][13],block B[39][65],int i,int j)
{
   B[i*3][j*5]=B[i*3][j*5+1]=B[i*3][j*5+2]=B[i*3][j*5+3]=B[i*3][j*5+4]=A[i][j];
   B[i*3+1][j*5]=B[i*3+1][j*5+1]=B[i*3+1][j*5+2]=B[i*3+1][j*5+3]=B[i*3+1][j*5+4]=A[i][j];
   B[i*3+2][j*5]=B[i*3+2][j*5+1]=B[i*3+2][j*5+2]=B[i*3+2][j*5+3]=B[i*3+2][j*5+4]=A[i][j];
}

void BOMB(block A[13][13],block B[39][65],int i,int j)
{
   if(A[i][j].a==UT)
   {
   B[i*3][j*5].a= B[i*3][j*5+4].a=0;
   B[i*3][j*5+1].a=B[i*3][j*5+3].a=DR;
   B[i*3][j*5+2].a=B[i*3+1][j*5].a=B[i*3+1][j*5+1].a=B[i*3+1][j*5+2].a=B[i*3+1][j*5+3].a=B[i*3+1][j*5+4].a=NR;
   B[i*3+2][j*5].a=B[i*3+2][j*5+1].a= B[i*3+2][j*5+2].a=B[i*3+2][j*5+3].a=B[i*3+2][j*5+4].a=NR;
   }
   else if(A[i][j].a==DT)
   {
   B[i*3][j*5].a=B[i*3][j*5+1].a=B[i*3][j*5+2].a=B[i*3][j*5+3].a=B[i*3][j*5+4].a=NR;
   B[i*3+1][j*5].a=B[i*3+1][j*5+1].a=B[i*3+1][j*5+2].a=B[i*3+1][j*5+3].a=B[i*3+1][j*5+4].a=NR;
   B[i*3+2][j*5].a=B[i*3+2][j*5+4].a=0; 
   B[i*3+2][j*5+1].a=B[i*3+2][j*5+3].a=UR;
   B[i*3+2][j*5+2].a=NR;
   }
   else if(A[i][j].a==RT)
   {
   B[i*3][j*5].a=B[i*3][j*5+1].a= B[i*3+2][j*5+3].a=UR;
   B[i*3][j*5+3].a=B[i*3+2][j*5].a=B[i*3+2][j*5+1].a=DR;
   B[i*3][j*5+4].a=B[i*3+2][j*5+4].a=0;
   B[i*3][j*5+2].a=B[i*3+1][j*5].a=B[i*3+1][j*5+1].a=B[i*3+1][j*5+2].a=B[i*3+1][j*5+3].a=B[i*3+1][j*5+4].a=B[i*3+2][j*5+2].a=NR;
   }
   else
   {
   B[i*3][j*5].a=B[i*3+2][j*5].a=0;
   B[i*3][j*5+1].a=B[i*3+2][j*5+3].a=B[i*3+2][j*5+4].a=DR;   
   B[i*3][j*5+3].a=B[i*3][j*5+4].a=B[i*3+2][j*5+1].a=UR;
   B[i*3][j*5+2].a=B[i*3+1][j*5].a=B[i*3+1][j*5+1].a=B[i*3+1][j*5+2].a=B[i*3+1][j*5+3].a=B[i*3+1][j*5+4].a=B[i*3+2][j*5+2].a=NR;
  }
}

void HLINE(block B[39][65],int i,int j,int a,int c,int l)
{
   B[i*3+l-1][j*5].a=B[i*3+l-1][j*5+1].a=B[i*3+l-1][j*5+2].a=B[i*3+l-1][j*5+3].a=B[i*3+l-1][j*5+4].a=a;
   B[i*3+l-1][j*5].c=B[i*3+l-1][j*5+1].c=B[i*3+l-1][j*5+2].c=B[i*3+l-1][j*5+3].c=B[i*3+l-1][j*5+4].c=c;
}

void VLINE(block B[39][65],int i,int j,int a,int c,int l)
{
   B[i*3][j*5+l-1].a=B[i*3+1][j*5+l-1].a=B[i*3+2][j*5+l-1].a=a;
   B[i*3][j*5+l-1].c=B[i*3+1][j*5+l-1].c=B[i*3+2][j*5+l-1].c=c;
}

void DOT(block B[39][65],int i,int j,int a,int c,int dot)
{
     switch(dot)
     {
     case 1:
     B[i*3][j*5].a=a;
     B[i*3][j*5].c=c;break;
     case 2:     
     B[i*3][j*5+1].a=a;
     B[i*3][j*5+1].c=c;break;
     case 3:
     B[i*3][j*5+2].a=a;
     B[i*3][j*5+2].c=c;break;
     case 4:
     B[i*3][j*5+3].a=a;
     B[i*3][j*5+3].c=c;break;     
     case 5:  
     B[i*3][j*5+4].a=a;
     B[i*3][j*5+4].c=c;break;       
     case 6:
     B[i*3+1][j*5].a=a;
     B[i*3+1][j*5].c=c;break;
     case 7:
     B[i*3+1][j*5+1].a=a;
     B[i*3+1][j*5+1].c=c;break;
     case 8:
     B[i*3+1][j*5+2].a=a;
     B[i*3+1][j*5+2].c=c;break;     
     case 9:
     B[i*3+1][j*5+3].a=a;
     B[i*3+1][j*5+3].c=c;break;
     case 10:
     B[i*3+1][j*5+4].a=a;
     B[i*3+1][j*5+4].c=c;break;
     case 11:
     B[i*3+2][j*5].a=a; 
     B[i*3+2][j*5].c=c;break;     
     case 12:
     B[i*3+2][j*5+1].a=a; 
     B[i*3+2][j*5+1].c=c;break;     
     case 13:
     B[i*3+2][j*5+2].a=a;
     B[i*3+2][j*5+2].c=c;break;
     case 14:
     B[i*3+2][j*5+3].a=a;
     B[i*3+2][j*5+3].c=c;break;
     default:
     B[i*3+2][j*5+4].a=a;
     B[i*3+2][j*5+4].c=c;
     }
}

void CIRCLE(block A[13][13],block B[39][65],int i,int j)
{
   B[i*3][j*5].a=B[i*3][j*5+4].a=DR;
   B[i*3][j*5+1].a=B[i*3][j*5+2].a=B[i*3][j*5+3].a=B[i*3+1][j*5].a=NR;
   B[i*3+1][j*5+1].a=B[i*3+1][j*5+2].a=B[i*3+1][j*5+3].a=B[i*3+1][j*5+4].a=NR;
   B[i*3+2][j*5].a= B[i*3+2][j*5+4].a=UR;
   B[i*3+2][j*5+1].a=B[i*3+2][j*5+2].a=B[i*3+2][j*5+3].a=NR;
  
}

int MOVE(block B[39][65],int i,int j,char key)
{
     block C[39][65];
     int a,b;
     if(key=='a')
     {
            if(j>6)
            {
            for(a=i-1;a<i+2;a++)
                              for(b=j-2;b<j+3;b++)
                                                  C[a][b]=B[a][b+1];
            for(a=i-1;a<i+2;a++)
                              for(b=j-2;b<j+3;b++)
                                                  B[a][b]=C[a][b];
            for(b=j+3,a=i-1;a<i+2;a++)
                              B[a][b].a=0,B[a][b].c=0;
            for(a=i-1;a<i+2;a++)
                              for(b=j-2;b<j+4;b++)                
                              {
                              gotoxy(b+8,a+4);
                              TC(B[a][b].c);
                              printf("%c",B[a][b].a);
                              }
            return (j-1);
            }
            else
              return j;  
     }
     else if(key=='d')
     {
            if(j<56)
            {
            for(a=i-1;a<i+2;a++)
                              for(b=j;b<j+5;b++)
                                                  C[a][b]=B[a][b-1];
            for(a=i-1;a<i+2;a++)
                              for(b=j;b<j+5;b++)
                                                  B[a][b]=C[a][b];
            for(b=j-1,a=i-1;a<i+2;a++)
                              B[a][b].a=0,B[a][b].c=0;
            for(a=i-1;a<i+2;a++)
                              for(b=j-1;b<j+5;b++)        
                              {
                              gotoxy(b+8,a+4);
                              TC(B[a][b].c);
                              printf("%c",B[a][b].a);
                              }
            return (j+1);
            }
            else
              return j;  
     }
     else if(key=='s')
     {
          if(i<34)
          {
          for(a=i;a<i+3;a++)
                            for(b=j-1;b<j+4;b++)
                                                C[a][b]=B[a-1][b];
          for(a=i;a<i+3;a++)
                            for(b=j-1;b<j+4;b++)
                                                B[a][b]=C[a][b];
          for(a=i-1,b=j-1;b<j+4;b++)
                                    B[a][b].a=0,B[a][b].c=0;
          for(a=i-1;a<i+3;a++)
                            for(b=j-1;b<j+4;b++)
                            {
                              gotoxy(b+8,a+4);
                              TC(B[a][b].c);
                              printf("%c",B[a][b].a);
                            }
          return (i+1);
          }
          else
              return i;  
     }
     else
     {
          if(i>4)
          {
          for(a=i-2;a<i+1;a++)
                            for(b=j-1;b<j+4;b++)
                                                C[a][b]=B[a+1][b];
          for(a=i-2;a<i+1;a++)
                            for(b=j-1;b<j+4;b++)
                                                B[a][b]=C[a][b];
          for(a=i+1,b=j-1;b<j+4;b++)
                                    B[a][b].a=0,B[a][b].c=0;
          for(a=i-2;a<i+2;a++)
                            for(b=j-1;b<j+4;b++)
                            {
                              gotoxy(b+8,a+4);
                              TC(B[a][b].c);
                              printf("%c",B[a][b].a);
                            }
          return (i-1);
          }
          else
              return i; 
     }
}

//***Funções ordem 2***

void BOARDS(block A[13][13],block B[39][65],int i,int j,int color)
{
     A[i][j].a=R1;
     A[i][j].c=color-8;
     BLOCK(A,B,i,j);
}

void BOMBERBALL(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=S1;
     A[i][j].c=14;   
     BLOCK(A,B,i,j);
     CIRCLE(A,B,i,j);
     DOT(B,i,j,DT,236,13);
     DOT(B,i,j,E1,233,7); 
     DOT(B,i,j,E1,233,9);
}

void GATE(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=SQ;
     A[i][j].c=9;   
     BLOCK(A,B,i,j);
     CIRCLE(A,B,i,j);
     DOT(B,i,j,LT,155,7);
     DOT(B,i,j,RT,155,9);
     DOT(B,i,j,NR,155,8);
}

void BOMB1(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=B1;
     A[i][j].c=12*16+8;
     BLOCK(A,B,i,j);
     CIRCLE(A,B,i,j);
     DOT(B,i,j,'*',8*16+0,3);
}

void BOMB2(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=B2;
     A[i][j].c=12*16+8;
     HLINE(B,i,j,NR,12,1);
     HLINE(B,i,j,NR,8,2);
     HLINE(B,i,j,NR,8,3);
     DOT(B,i,j,'*',8*16+0,8);
     DOT(B,i,j,DR,12*16+8,6);
     DOT(B,i,j,DR,12*16+8,10);
     DOT(B,i,j,UR,12*16+8,11);
     DOT(B,i,j,UR,12*16+8,15);
}

void FIREUP(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=UT;
     A[i][j].c=12;
     BLOCK(A,B,i,j);
     BOMB(A,B,i,j);
     DOT(B,i,j,NR,14,8);
     DOT(B,i,j,NR,14,12);
     DOT(B,i,j,NR,14,13);
     DOT(B,i,j,NR,14,14);
} 

void FIREVLINE(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=NR;
     A[i][j].c=12;
     BLOCK(A,B,i,j);
     VLINE(B,i,j,NR,14,2);
     VLINE(B,i,j,NR,14,4);
     VLINE(B,i,j,NR,15,3);
}

void FIREHLINE(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=NR;
     A[i][j].c=236;
     BLOCK(A,B,i,j);
     HLINE(B,i,j,UR,236,1);
     HLINE(B,i,j,DR,236,3);
     HLINE(B,i,j,NR,15,2);
}

void FIREDOWN(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=DT;
     A[i][j].c=12;
     BLOCK(A,B,i,j);
     BOMB(A,B,i,j);
     DOT(B,i,j,NR,14,8);
     DOT(B,i,j,NR,14,2);
     DOT(B,i,j,NR,14,3);
     DOT(B,i,j,NR,14,4);
}

void FIRELEFT(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=LT,
     A[i][j].c=12;
     BLOCK(A,B,i,j);
     BOMB(A,B,i,j);
     DOT(B,i,j,NR,14,8);
     DOT(B,i,j,NR,14,9);
     DOT(B,i,j,NR,14,10);
     DOT(B,i,j,UR,236,4);
     DOT(B,i,j,UR,236,5);
     DOT(B,i,j,DR,236,14);
     DOT(B,i,j,DR,236,15);
     DOT(B,i,j,NR,239,10);
}

void FIRERIGHT(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=RT;
     A[i][j].c=12;
     BLOCK(A,B,i,j);
     BOMB(A,B,i,j);
     DOT(B,i,j,NR,14,6);
     DOT(B,i,j,NR,14,7);
     DOT(B,i,j,NR,14,8);
     DOT(B,i,j,UR,236,1);
     DOT(B,i,j,UR,236,2);
     DOT(B,i,j,DR,236,11);
     DOT(B,i,j,DR,236,12);
     DOT(B,i,j,NR,239,6);
}

void FIRECENTER(block A[13][13],block B[39][65],int i,int j)
{
     A[i][j].a=NR;
     A[i][j].c=236;
     BLOCK(A,B,i,j);
     DOT(B,i,j,UR,236,1);
     DOT(B,i,j,UR,236,5);
     DOT(B,i,j,DR,236,11);
     DOT(B,i,j,DR,236,15);
     VLINE(B,i,j,NR,14,2);
     VLINE(B,i,j,NR,14,4);
     VLINE(B,i,j,NR,15,3);
     HLINE(B,i,j,NR,15,2);
}

void NUMBER(block C[1][13],block D[3][65],int i,int j,int n)
{
     switch (n)
     {
            case 0:
            {
                 VLINE(D,i,j,NR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,NR,15,4);
                 DOT(D,i,j,UR,15,12);
                 DOT(D,i,j,UR,15,14);
                 DOT(D,i,j,0,15,8);
                 break;
            }     
            case 1:
            {     
                  VLINE(D,i,j,NR,15,3);
                  DOT(D,i,j,UR,15,13);
                   DOT(D,i,j,UR,15,2);
                  break;
            }
            case 2:
            {
                 VLINE(D,i,j,UR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,UR,15,4);
                 DOT(D,i,j,NR,15,4);
                 DOT(D,i,j,NR,15,7);
                 break;
            }
            case 3:
            {
                 VLINE(D,i,j,UR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,UR,15,4);
                 DOT(D,i,j,NR,15,4);
                 DOT(D,i,j,NR,15,9);
                 break;
            }
            case 4:
            {
                 VLINE(D,i,j,NR,15,4);
                 DOT(D,i,j,NR,15,2);
                 DOT(D,i,j,UR,15,7);
                 DOT(D,i,j,UR,15,8);
                 DOT(D,i,j,UR,15,14);
                 break;
            }     
            case 5:
            {
                 VLINE(D,i,j,UR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,UR,15,4);
                 DOT(D,i,j,NR,15,2);
                 DOT(D,i,j,NR,15,9);
                 break;
            }     
            case 6:
            {
                 VLINE(D,i,j,NR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,UR,15,4);
                 DOT(D,i,j,UR,15,12);
                 DOT(D,i,j,NR,15,9);
                 break;
            }
            case 7:
            {
                 VLINE(D,i,j,NR,15,4);
                 DOT(D,i,j,NR,15,2);
                 DOT(D,i,j,UR,15,3);
                 DOT(D,i,j,UR,15,14);
                 break;
            }
                
            case 8:
            {
                 VLINE(D,i,j,NR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,NR,15,4);
                 DOT(D,i,j,UR,15,12);
                 DOT(D,i,j,UR,15,14); 
                 break;
            }
                 
            case 9:
            {
                 VLINE(D,i,j,UR,15,2);
                 VLINE(D,i,j,UR,15,3);
                 VLINE(D,i,j,NR,15,4);
                 DOT(D,i,j,NR,15,2);
                 DOT(D,i,j,UR,15,14); 
                 break;
            }                 
     }   
     
}
   
main()
{
      block A[13][13],B[39][65],C[1][13],D[3][65];
      int a,b,i,j,color;
      char key;
      
    color=11;//cor do estágio
    for(i=0;i<13;i++)
                       for(j=0;j<13;j++)
                                        {
                                                          if(i==0||j==0||i==12||j==12)
                                                                   BOARDS(A,B,i,j,color);
                                                          else if(i==1&&j==1)
                                                                   BOMBERBALL(A,B,i,j);
                                                          else if(i==1&&j==4)
                                                                   BOMB2(A,B,i,j);
                                                          else if(i==11&&j==11)
                                                                   GATE(A,B,i,j); 
                                                          else if(i==1&&j==3)//Bomb
                                                                   FIREUP(A,B,i,j);
                                                          else if((i==2||i==4)&&j==3)
                                                                   FIREVLINE(A,B,i,j);
                                                          else if(i==3&&(j==2||j==4))
                                                                   FIREHLINE(A,B,i,j);
                                                          else if(i==5&&j==3)
                                                                   FIREDOWN(A,B,i,j);
                                                          else if(i==3&&j==1)
                                                                   FIRELEFT(A,B,i,j);
                                                          else if(i==3&&j==5)
                                                                   FIRERIGHT(A,B,i,j);
                                                          else if(i==3&&j==3)
                                                                   FIRECENTER(A,B,i,j);
                                                          else if(i%2==0&&j%2==0)//Blocks
                                                          {
                                                                 A[i][j].a=NR;
                                                                 A[i][j].c=color;
                                                                 BLOCK(A,B,i,j);
                                                          }
                                                          else if(i%2==1&&j%2==1)
                                                          {
                                                               A[i][j].a=SQ;
                                                               A[i][j].c=color;
                                                               BLOCK(A,B,i,j);
                                                          }
                                                          else//Space(Nothing)
                                                          {
                                                              A[i][j].a=0;
                                                              A[i][j].c=0;
                                                              BLOCK(A,B,i,j);
                                                          }
                                       }
                                       
//***Impressão do tabuleiro
      for(i=j=0;j<13;j++)
      {
                         if(j==0)
                                 BOMBERBALL(C,D,i,j);
                         else if(j<10)
                                       NUMBER(C,D,i,j,j);
                         else if(j==11)
                                       BOMB1(C,D,i,j);                         
                         else
                                       NUMBER(C,D,i,j,0);
      }
      for(i=0;i<3;i++)
      {
                       for(j=0;j<65;j++)
                       {
                                        if(j==0)
                                                printf("       ");
                                        TC(D[i][j].c);
                                        printf("%c",D[i][j].a);
                       }
                       printf("\n");
      }
      
      for(i=0;i<39;i++)
      {
                       for(j=0;j<65;j++)
                       {
                                        if(j==0)
                                                printf("       ");
                                        TC(B[i][j].c);
                                        printf("%c",B[i][j].a);
                       }
                       printf("\n");
      }
      
      printf("\n");
      for(i=0;i<13;i++)
      {
                       for(j=0;j<13;j++)
                       {
                                        TC(A[i][j].c);
                                        printf("%c",A[i][j].a);
                       }
                       printf("\n");
      }
      TC(15);
      printf("\nPressione w a s d para mover space para bomba ou outra tecla para sair");
      i=4;
      j=6;
      do
      {
      gotoxy(j+7,i+5);
      key=getch();
      if(key==' ')//Bomba
      {
           int a,b,x,x2,y,y2;
           x2=i%3;
           x=(i-x2)/3;
           y2=j%5;
           y=(j-y2)/5;
           BOMB1(A,B,x,y);
           for(a=i;a<i+3;a++)
                   for(b=j;b<j+5;b++)
                   {
                           gotoxy(b+7,a+3);
                           TC(B[a-1][b-1].c);
                           printf("%c",B[a-1][b-1].a);
                   }
           BOMBERBALL(A,B,x,y);
      }
      else if(key=='d'||key=='a')// Movimento
           j=MOVE(B,i,j,key);
      else if(key=='s'||key=='w')
           i=MOVE(B,i,j,key);
      }while(key=='a'||key=='s'||key=='w'||key=='d'||key==' ');
      
}
