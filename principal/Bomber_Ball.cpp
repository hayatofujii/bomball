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
        void BLOCK(int ascii,int color,int effect);//***funcoes ordem1
        void HLINE(int ascii,int color,int line);
        void VLINE(int ascii,int color,int line);
        void DOT(int ascii,int color,int dot);
        void PRINT(int i,int j);
        void PRINTLINE(int i);
        void ZERO();//***funcoes ordem2
        void CIRCLE(int color);
        void BOARDS(int color);
        void FIREUP();
        void FIREDOWN();
        void FIRELEFT();
        void FIRERIGHT();
        void FIREHLINE();
        void FIREVLINE();
        void FIRECENTER();
        void NUMBER(int x, int color);
        void LETTER(int x, int color);//***
        void BOMBERBALL();//***funcoes ordem3
        void GATE();
        void BOMB1();
        void BOMB2();
        void MONSTER();
        void FIREIT();
        void BOMBIT();
};

typedef struct stage
{
        int BN; //bomb number
        int SN; //stage number
        int E; //hyper effect
        int F; //fire power
        int C; //stage color
        char K; //key
        block B[15][15];//board
        block M; //memory
        void BEGIN();
        void PRINT();
        int MOVE(int i,int j);
};

main()
{
        int i,j;
        stage S;
        S.BEGIN();
        S.SN=1;
        if(S.SN==1)
            S.C=11;
        for(i=1;i<14;i++)
                       for(j=1;j<14;j++)//***Tabuleiro
                                        {
                                                          if(i==1||j==1||i==13||j==13)
                                                                  S.B[i][j].BOARDS(S.C-8);
                                                          else if((i==3||i==5)&&j==4)
                                                                   S.B[i][j].FIREVLINE();
                                                          else if(i==4&&(j==3||j==5))
                                                                   S.B[i][j].FIREHLINE();
                                                          else if(i%2==1&&j%2==1)//Blocks
                                                                   S.B[i][j].BLOCK(NR,S.C,0);
                                                          else if(i%2==0&&j%2==0)
                                                                   S.B[i][j].BLOCK(SQ,S.C,0);
                                        }
        S.B[0][0].BOMBERBALL();//***Titulo
        S.B[0][1].DOT('x',15,21);
        S.B[0][1].NUMBER(0,15);
        S.B[0][2].FIREIT();
        S.B[0][3].DOT('x',15,21);
        S.B[0][3].NUMBER(1,15);
        S.B[0][4].BOMBIT();
        S.B[0][5].DOT('x',15,21);
        S.B[0][5].NUMBER(2,15);
        S.B[0][6].NUMBER(3,S.C);
        S.B[0][7].DOT(':',S.C,21);
        S.B[0][7].NUMBER(4,S.C);
        S.B[0][8].NUMBER(5,S.C);
        S.B[0][9].NUMBER(6,15);
        S.B[0][10].NUMBER(7,15);
        S.B[0][11].NUMBER(8,15);
        S.B[0][12].NUMBER(9,15);
        S.B[0][13].NUMBER(0,15);
        S.B[0][14].NUMBER(0,15);

        S.B[7][0].NUMBER(S.SN,S.C);//***Fase

        S.B[2][2].BOMBERBALL();//***Tabuleiro
        S.B[2][3].FIREIT();
        S.B[2][5].BOMB2();
        S.B[2][9].MONSTER();
        S.B[12][12].GATE();
        S.B[2][4].FIREUP();//bomb
        S.B[6][4].FIREDOWN();
        S.B[4][2].FIRELEFT();
        S.B[4][6].FIRERIGHT();
        S.B[4][4].FIRECENTER();

        S.PRINT();

        gotoxy(1,50);
        TC(15);
        printf("\nPressione w a s d para mover space para bomba ou outra tecla para sair");
        i=j=2;
        do
        {
            gotoxy(j*5+3,i*3+3);
            S.K=getch();
            if(S.K==' ')//Bomba
            {
                S.B[i][j].BOMB1();
                S.B[i][j].PRINT(i,j);
                S.M=S.B[i][j];
            }
            else if(S.K=='d'||S.K=='a')// Movimento
                j=S.MOVE(i,j);
            else if(S.K=='s'||S.K=='w')
                i=S.MOVE(i,j);
      }while(S.K=='a'||S.K=='s'||S.K=='w'||S.K=='d'||S.K==' ');
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
     gotoxy(j*5+3,i*3+1);
     TC(c11);printf("%c",a11);
     TC(c12);printf("%c",a12);
     TC(c13);printf("%c",a13);
     TC(c14);printf("%c",a14);
     TC(c15);printf("%c",a15);
     gotoxy(j*5+3,i*3+2);
     TC(c21);printf("%c",a21);
     TC(c22);printf("%c",a22);
     TC(c23);printf("%c",a23);
     TC(c24);printf("%c",a24);
     TC(c25);printf("%c",a25);
     gotoxy(j*5+3,i*3+3);
     TC(c31);printf("%c",a31);
     TC(c32);printf("%c",a32);
     TC(c33);printf("%c",a33);
     TC(c34);printf("%c",a34);
     TC(c35);printf("%c",a35);
     gotoxy(j*5+3,i*3+4);
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
     DOT(UR,14*16+12,22);
     DOT(UR,14*16+12,24);
     DOT(NR,14,23);
     DOT(NR,14,32);
     DOT(NR,15,33);
     DOT(NR,14,34);
}

void block::FIREDOWN()
{
     BLOCK(NR,12,1);
     DOT(NR,14,12);
     DOT(NR,15,13);
     DOT(NR,14,14);
     DOT(DR,14*16+12,22);
     DOT(NR,14,23);
     DOT(DR,14*16+12,24);
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

void block::NUMBER(int x,int color)
{
   switch(x)
   {
       case 0:
       {
                VLINE(NR,color,2);
                VLINE(UR,color,3);
                VLINE(NR,color,4);
                DOT(UR,color,32);
                DOT(UR,color,34);
                DOT(0,color,23);
                break;
        }
        case 1:
        {
                  VLINE(NR,color,3);
                  DOT(UR,color,33);
                  DOT(UR,color,12);
                  break;
        }
        case 2:
        {
                 VLINE(UR,color,2);
                 VLINE(UR,color,3);
                 VLINE(UR,color,4);
                 DOT(NR,color,14);
                 DOT(NR,color,22);
                 break;
        }
        case 3:
        {
                 VLINE(UR,color,2);
                 VLINE(UR,color,3);
                 VLINE(UR,color,4);
                 DOT(NR,color,14);
                 DOT(NR,color,24);
                 break;
        }
        case 4:
        {
                 VLINE(NR,color,4);
                 DOT(NR,color,12);
                 DOT(UR,color,22);
                 DOT(UR,color,23);
                 DOT(UR,color,34);
                 break;
        }
        case 5:
        {
                 VLINE(UR,color,2);
                 VLINE(UR,color,3);
                 VLINE(UR,color,4);
                 DOT(NR,color,12);
                 DOT(NR,color,24);
                 break;
        }
        case 6:
        {
                 VLINE(NR,color,2);
                 VLINE(UR,color,3);
                 VLINE(UR,color,4);
                 DOT(UR,color,32);
                 DOT(NR,color,24);
                 break;
        }
        case 7:
        {
                 VLINE(NR,color,4);
                 DOT(NR,color,12);
                 DOT(UR,color,13);
                 DOT(UR,color,34);
                 break;
        }
        case 8:
        {
                 VLINE(NR,color,2);
                 VLINE(UR,color,3);
                 VLINE(NR,color,4);
                 DOT(UR,color,32);
                 DOT(UR,color,34);
                 break;
        }
        case 9:
        {
                 VLINE(UR,color,2);
                 VLINE(UR,color,3);
                 VLINE(NR,color,4);
                 DOT(NR,color,12);
                 DOT(UR,color,34);
                 break;
        }
   }
}

void block::LETTER(int x, int color)
{
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
     M.ZERO();
     for(i=0;i<15;i++)
                      for(j=0;j<15;j++)
                                       B[i][j].ZERO();
}

void stage::PRINT()
{
     int i,j,x;
     for(i=0;i<15;i++)
                      for(x=1;x<4;x++)
                      {
                                      printf("  ");
                                      for(j=0;j<15;j++)
                                                       B[i][j].PRINTLINE(x);
                                      printf("\n");
                      }
}

int stage::MOVE(int i,int j)
{
    if(K=='w')
    {
        if(i<=2)
            return i;
        else
        {
        B[i][j]=M;
        B[i][j].PRINT(i,j);
        M=B[i-1][j];
        B[i-1][j].BOMBERBALL();
        B[i-1][j].PRINT(i-1,j);
        return i-1;
        }
    }
    else if(K=='s')
    {
        if(i>=12)
            return i;
        else
        {
        B[i][j]=M;
        B[i][j].PRINT(i,j);
        M=B[i+1][j];
        B[i+1][j].BOMBERBALL();
        B[i+1][j].PRINT(i+1,j);
        return i+1;
        }
    }
    else if(K=='a')
    {
        if(j<=2)
            return j;
        else
        {
        B[i][j]=M;
        B[i][j].PRINT(i,j);
        M=B[i][j-1];
        B[i][j-1].BOMBERBALL();
        B[i][j-1].PRINT(i,j-1);
        return j-1;
        }
    }
    else
    {
        if(j>=12)
            return j;
        else
        {
        B[i][j]=M;
        B[i][j].PRINT(i,j);
        M=B[i][j+1];
        B[i][j+1].BOMBERBALL();
        B[i][j+1].PRINT(i,j+1);
        return j+1;
        }
    }
}
