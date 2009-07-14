#include<stdlib.h>
#include<stdio.h>
#include "conio.c"
#include<conio.h>

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
#define UL 238//up line
#define DL 95//down line
#define LB 92//left bar
#define RB 47//right bar
#define CC 79//circle
#define E1 226//eye 1
#define TC(a) textcolor(a)

typedef struct block
{
        int e; //effect
        int a11,a12,a13,a14,a15,a21,a22,a23,a24,a25,a31,a32,a33,a34,a35; //ascii
        int c11,c12,c13,c14,c15,c21,c22,c23,c24,c25,c31,c32,c33,c34,c35; //color
        void BLOCK(int ascii,int color,int effect);//funcoes ordem1
        void HLINE(int ascii,int color,int line);
        void VLINE(int ascii,int color,int line);
        void DOT(int ascii,int color,int dot);
        void PRINT(int i,int j);
        void PRINTLINE(int i);
        void ZERO();//funcoes ordem2
        void CIRCLE(int color);
        int MOVE(int i,int j,char key);//***
        void BOARDS(int color);
        void FIREUP();
        void FIREDOWN();
        void FIRELEFT();
        void FIRERIGHT();
        void FIREHLINE();
        void FIREVLINE();
        void FIRECENTER();
        void NUMBER();//***
        void BOMBERBALL();//funcoes ordem3
        void GATE();
        void BOMB1();
        void BOMB2();
        void MONSTER();
        void FIREIT();
        void BOMBIT();
};

typedef struct stage
{
        int E; //hyper effect
        int C; //stage color
        block B[13][13];
        void BEGIN();
        void PRINT();
};

main()
{
        int i,j;
        block C[1][13];
        stage S;
        char key;
        S.BEGIN();
        S.C=11;
        for(i=0;i<13;i++)
                       for(j=0;j<13;j++)
                                        {
                                                          if(i==0||j==0||i==12||j==12)
                                                                  S.B[i][j].BOARDS(S.C-8);
                                                          else if(i==1&&j==1)
                                                                   S.B[i][j].BOMBERBALL();
                                                          else if(i==1&&j==2)
                                                                   S.B[i][j].FIREIT();
                                                          else if(i==1&&j==4)
                                                                   S.B[i][j].BOMB2();
                                                          else if(i==1&&j==6)
                                                                   S.B[i][j].BOMBIT();
                                                          else if(i==1&&j==8)
                                                                   S.B[i][j].MONSTER();
                                                          else if(i==11&&j==11)
                                                                   S.B[i][j].GATE(); 
                                                          else if(i==1&&j==3)//Bomb
                                                                   S.B[i][j].FIREUP();
                                                          else if((i==2||i==4)&&j==3)
                                                                   S.B[i][j].FIREVLINE();
                                                          else if(i==3&&(j==2||j==4))
                                                                   S.B[i][j].FIREHLINE();
                                                          else if(i==5&&j==3)
                                                                   S.B[i][j].FIREDOWN();
                                                          else if(i==3&&j==1)
                                                                   S.B[i][j].FIRELEFT();
                                                          else if(i==3&&j==5)
                                                                   S.B[i][j].FIRERIGHT();
                                                          else if(i==3&&j==3)
                                                                   S.B[i][j].FIRECENTER();
                                                          else if(i%2==0&&j%2==0)//Blocks
                                                                   S.B[i][j].BLOCK(NR,S.C,0);
                                                          else if(i%2==1&&j%2==1)
                                                                   S.B[i][j].BLOCK(SQ,S.C,0);
                                        }
//***Impressão do tabuleiro
      for(i=j=0;j<13;j++)
      {
                         if(j==0)
                         {
                                 C[i][j].BOMBERBALL();
                                 //C[i][j].PRINT(i,j);
                         }
                         //else if(j==9)
                         //        FIRE(C,D,i,j);
                         //else if(j<10)
                         //              NUMBER(C,D,i,j,j);
                         else if(j==11)
                         {
                                       C[i][j].BOMBIT();
                                       //C[i][j].PRINT(i,j);  
                         }                       
                         //else
                         //              NUMBER(C,D,i,j,0);
      }
      S.PRINT();    
      system("pause"); 
}
        
void block::BLOCK(int ascii,int color,int effect)
{
     a11=a12=a13=a14=a15=a21=a22=a23=a24=a25=a31=a32=a33=a34=a35=ascii;
     c11=c12=c13=c14=c15=c21=c22=c23=c24=c25=c31=c32=c33=c34=c35=color;
     e=effect;
}        

void block::HLINE(int ascii,int color,int line)
{
     if(line==1)
     {
                 a11=a12=a13=a14=a15=ascii;
                 c11=c12=c13=c14=c15=color;
     }
     else if(line==2)
     {
                 a21=a22=a23=a24=a25=ascii;
                 c21=c22=c23=c24=c25=color;
     }
     else
     {
                 a31=a32=a33=a34=a35=ascii;
                 c31=c32=c33=c34=c35=color;
     }
}

void block::VLINE(int ascii,int color,int line)
{
     if(line==1)
     {
                a11=a21=a31=ascii;
                c11=c21=c31=color;
     }
     else if(line==2)
     {
                a12=a22=a32=ascii;
                c12=c22=c32=color;
     }
     else if(line==3)
     {
                a13=a23=a33=ascii;
                c13=c23=c33=color;
     }
     else if(line==4)
     {
                a14=a24=a34=ascii;
                c14=c24=c34=color;
     }
     else 
     {
                a15=a25=a35=ascii;
                c15=c25=c35=color;
     }
}        
                
void block::DOT(int ascii,int color,int dot)
{
     switch(dot)
     {
                case 11:
                {
                     a11=ascii;
                     c11=color;
                     break;
                }
                case 12:
                {
                     a12=ascii;
                     c12=color;
                     break;
                }     
                case 13:
                {
                     a13=ascii;
                     c13=color;
                     break;
                }
                case 14:
                {
                     a14=ascii;
                     c14=color;
                     break;
                }
                case 15:
                {
                     a15=ascii;
                     c15=color;
                     break;
                }
                case 21:
                {
                     a21=ascii;
                     c21=color;
                     break;
                }
                case 22:
                {
                     a22=ascii;
                     c22=color;
                     break;
                }
                case 23:
                {
                     a23=ascii;
                     c23=color;
                     break;
                }
                case 24:
                {
                     a24=ascii;
                     c24=color;
                     break;
                }
                case 25:
                {
                     a25=ascii;
                     c25=color;
                     break;
                }
                case 31:
                {
                     a31=ascii;
                     c31=color;
                     break;
                }
                case 32:
                {
                     a32=ascii;
                     c32=color;
                     break;
                }
                case 33:
                {
                     a33=ascii;
                     c33=color;
                     break;
                }
                case 34:
                {
                     a34=ascii;
                     c34=color;
                     break;
                }
                default:
                {
                     a35=ascii;
                     c35=color;
                }     
     }
}        

void block::PRINT(int i,int j)
{
     int x,y;
     for(y=i;y>0;y--)
                     printf("\n");
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c11);printf("%c",a11);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c12);printf("%c",a12);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c13);printf("%c",a13);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c14);printf("%c",a14);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c15);printf("%c",a15);
     printf("\n");
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c21);printf("%c",a21);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c22);printf("%c",a22);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c23);printf("%c",a23);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c24);printf("%c",a24);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c25);printf("%c",a25);
     printf("\n");
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c31);printf("%c",a31);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c32);printf("%c",a32);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c33);printf("%c",a33);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c34);printf("%c",a34);
     for(x=j;x>0;x--);
                      printf(" ");
     TC(c35);printf("%c",a35);
     printf("\n");
}        

void block::PRINTLINE(int i)
{
     if(i==1)
     {
     TC(c11);printf("%c",a11);
     TC(c12);printf("%c",a12);
     TC(c13);printf("%c",a13);
     TC(c14);printf("%c",a14);
     TC(c15);printf("%c",a15);
     }
     else if(i==2)
     {
     TC(c21);printf("%c",a21);
     TC(c22);printf("%c",a22);
     TC(c23);printf("%c",a23);
     TC(c24);printf("%c",a24);
     TC(c25);printf("%c",a25);
     }
     else
     {
     TC(c31);printf("%c",a31);
     TC(c32);printf("%c",a32);
     TC(c33);printf("%c",a33);
     TC(c34);printf("%c",a34);
     TC(c35);printf("%c",a35);
     }
}

void block::ZERO()
{
     BLOCK(0,0,0);
}        
        
void block::CIRCLE(int color)
{
     BLOCK(NR,color,0);
     DOT(DR,color,11);
     DOT(DR,color,15);
     DOT(UR,color,31);
     DOT(UR,color,35);
}

void block::BOARDS(int color)
{
     BLOCK(R1,color,0);
}

void block::FIREUP()
{
     BLOCK(NR,12,1);
     DOT(NR,0,11);
     DOT(DR,12,12);
     DOT(DR,12,14);
     DOT(NR,0,15);
     DOT(NR,14,23);
     DOT(NR,14,32);
     DOT(NR,14,33);
     DOT(NR,14,34);
}

void block::FIREDOWN()
{
     BLOCK(NR,12,1);
     DOT(NR,14,12);
     DOT(NR,14,13);
     DOT(NR,14,14);
     DOT(NR,14,23);
     DOT(NR,0,31);
     DOT(UR,12,32);
     DOT(UR,12,34);
     DOT(NR,0,35);
}

void block::FIRELEFT()
{
     BLOCK(NR,12,1);
     DOT(NR,0,11);
     DOT(DR,12,12);
     DOT(UR,14*16+12,14);
     DOT(UR,14*16+12,15);
     DOT(NR,14,23);
     DOT(NR,14,24);
     DOT(NR,15,25);
     DOT(NR,0,31);
     DOT(UR,12,32);
     DOT(DR,14*16+12,34);
     DOT(DR,14*16+12,35);
}

void block::FIRERIGHT()
{
     BLOCK(NR,12,1);
     DOT(UR,14*16+12,11);
     DOT(UR,14*16+12,12);
     DOT(DR,12,14);
     DOT(NR,0,15);
     DOT(NR,15,21);
     DOT(NR,14,22);
     DOT(NR,14,23);
     DOT(DR,14*16+12,31);
     DOT(DR,14*16+12,32);
     DOT(UR,12,34);
     DOT(NR,0,35);
}      

void block::FIREHLINE()
{
     BLOCK(NR,15,1);
     HLINE(DR,12*16+14,1);
     HLINE(UR,12*16+14,3);
}

void block::FIREVLINE()
{
     BLOCK(NR,12,1);
     VLINE(NR,14,2);
     VLINE(NR,15,3);
     VLINE(NR,14,4);
}

void block::FIRECENTER()
{
     BLOCK(NR,15,1);
     DOT(DR,12*16+14,11);
     DOT(NR,14,12);
     DOT(NR,14,14);
     DOT(DR,12*16+14,15);
     DOT(UR,12*16+14,31);
     DOT(NR,14,32);
     DOT(NR,14,34);
     DOT(UR,12*16+14,35);
}  

void block::BOMBERBALL()
{
    CIRCLE(14);
    DOT(E1,14*16+1,22);
    DOT(E1,14*16+1,24);
    DOT(DT,14*16+12,33);
}

void block::GATE()
{
     CIRCLE(9);
     DOT(LT,16*9+11,22);
     DOT(NR,11,23);
     DOT(RT,16*9+11,24);
}

void block::BOMB1()
{
     CIRCLE(12*16+1);
     DOT('*',15,13);
}

void block::BOMB2()
{
     CIRCLE(12*16+1);
     HLINE(NR,12,1);
     DOT(DR,12*16+1,21);
     DOT('*',15,23);
     DOT(DR,12*16+1,25);
}

void block::MONSTER()
{
     BLOCK(0,0,1);
     CIRCLE(12);
     HLINE(UT,12,1);
     DOT(B3,12*16,22);
     DOT(B6,12*16,24);
     DOT(UT,12*16,33);
}

void block::FIREIT()
{
     BLOCK(NR,15,2);
     DOT(UT,14*16+12,13);
     DOT(LT,14*16+12,21);
     DOT(LT,14*16+12,22);
     DOT(LG,14*16+12,23);
     DOT(RT,14*16+12,24);
     DOT(RT,14*16+12,25);
     DOT(DT,14*16+12,33);
}

void block::BOMBIT()
{
     CIRCLE(15*16+1);
     DOT('*',15,13);
}
     
void stage::BEGIN()
{
     int i,j;
     for(i=0;i<13;i++)
                      for(j=0;j<13;j++)
                                       B[i][j].ZERO();
}

void stage::PRINT()
{
     int i,j,x;
     for(i=0;i<13;i++)
                      for(x=1;x<4;x++)
                      {
                                      printf("       ");
                                      for(j=0;j<13;j++)
                                                       B[i][j].PRINTLINE(x);
                                      printf("\n");
                      }
}     
