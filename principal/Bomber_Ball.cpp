/* block.e/stage.Effects
    e[0]=morte/invencivel       fire/monster
    e[1]=bloco inquebravel      block NR
    e[2]=bloco quebravel        block SQ/bomb
    e[3]=item                   fireit/bombit/wallit
    e[4]=fire up item           fireit
    e[5]=bomb up item           bombit
    e[6]=wall cross item        wallit
    e[7]=bomb                   bomb
    e[8]=monster                monster
    e[9]=portal                 gate
    e[10]=life up item          lifeit
    e[11]=fire                  fireup/down/left/right/center
    */

#include<stdlib.h>
#include<stdio.h>
#include "conio.c"
#include<conio.h>
#include<time.h>

#define HT 3//heart '♥'
#define LG 4//losangle '♦'
#define TR 5//tree '♣'
#define SW 6//sword '♠'
#define B1 11//bomb1 '♂'
#define B2 15//bomb2 '☼'
#define B3 155//bomb4 'ø'
#define B4 157//bomb5 'Ø'
#define B5 207//bomb7 '¤'
#define E1 226//eye 1 'Ô'
#define E2 149//eye2 'ò'
#define E3 162//eye3 'ó'
#define E4 227//eye5 'Ò'
#define E5 224//eye 4 'Ó'
#define R1 176//rock1 '░'
#define R2 177//rock2 '▒'
#define R3 178//rock3 '▓'
#define NR 219//normal retangle '█'
#define DR 220//down retangle '▄'
#define UR 223//up retangle '▀'
#define SQ 254//square '■'
#define RT 16 //right triangle '►'
#define LT 17//left triangle '◄'
#define UT 30//up triangle '▲'
#define DT 31//down triangle '▼'
#define VL 179//vertical line '│'
#define HL 196//horizontal line '─'
#define UL 238//up line '¯'
#define DL 95//down line '_'
#define LB 92//left bar '\'
#define RB 47//right bar '/'
#define CC 79//circle O
#define TC(a) textcolor(a)

typedef struct block
{
        bool e[20]; //effect
        int a11,a12,a13,a14,a15,a21,a22,a23,a24,a25,a31,a32,a33,a34,a35; //ascii
        int c11,c12,c13,c14,c15,c21,c22,c23,c24,c25,c31,c32,c33,c34,c35; //color
        void BLOCK(int ascii,int color);//***funcoes ordem1
        void EFFECT(int i,bool effect);
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
        void LETTER(char x, int color);
        void BOMBERBALL();//***funcoes ordem3
        void BOMBERBALL2();
        void BOMBERDIE();
        void GATE();
        void BOMB1();
        void BOMB2();
        void MONSTER();
        void FIREIT();
        void BOMBIT();
        void WALLIT();
        void LIFEIT();
};

typedef struct stage
{
        int Bomb; //bomb number
        int Stage; //stage number
        bool Effect[20]; //hyper effect
        int Fire; //fire power
        int Color;
        int Life;
        int Score[6];
        int Time[3];
        char Pass[13];//password
        char Key;
        block B[15][15];//board
        block Memory;
        void BEGIN();
        void PRINT();
        void CONTROL(int i,int j);
        int MOVE(int i,int j);
        void ITEM(int i,int j);
        void PASSWORD();//under constuction
        void TITLE();
        void EXPLOSION(int i,int j);//under construction
        void DIE(int i,int j);
};


void sleep (long milli )
{
  clock_t end, current = clock();
  for (end = current + milli; current < end; current = clock());
}

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

main()
{
        int i,j,k;
        stage S;
        S.BEGIN();
        for(i=2;i<13;i++)
                       for(j=2;j<13;j++)//***Tabuleiro
                                        {
                                                          if(i%2==0&&j%2==0)
                                                          {
                                                                   S.B[i][j].BLOCK(SQ,S.Color);
                                                                   S.B[i][j].e[2]=1;//e[2]=bloco quebravel
                                                          }
                                        }

        S.B[2][2].BOMBERBALL();//***Tabuleiro
        S.B[2][3].FIREIT();
        S.B[2][9].MONSTER();
        S.B[3][2].BOMBIT();
        S.B[5][2].LIFEIT();
        S.B[12][12].GATE();

        S.B[2][14].WALLIT();//***Efeitos

        S.B[14][0].LETTER('!',15);//***Passwords
        S.B[14][1].LETTER('B',15);
        S.B[14][2].LETTER('O',15);
        S.B[14][3].LETTER('M',15);
        S.B[14][4].LETTER('B',15);
        S.B[14][5].LETTER('E',15);
        S.B[14][6].LETTER('R',15);
        S.B[14][7].LETTER('B',15);
        S.B[14][8].LETTER('A',15);
        S.B[14][9].LETTER('L',15);
        S.B[14][10].LETTER('L',15);

        S.PRINT();

        S.Effect[6]=1;//wall cross

        gotoxy(1,50);
        TC(15);
        printf("\nPressione w a s d para mover space para bomba ou outra tecla para sair");
        i=j=2;

        /*int l,n;//relogio do ernesto aguarde 1 para jogar...
        l=1;
        do{
                          l--;
                          for (n=60; n>=0; n--)
                          {
                              if(n==60)
                              {
                                S.B[0][6].NUMBER(l,S.Color);
                                S.B[0][7].NUMBER(0,S.Color);
                                S.B[0][8].NUMBER(0,S.Color);
                              }
                              else
                              {
                                S.B[0][6].NUMBER(l,S.Color);
                                S.B[0][7].NUMBER(n/10,S.Color);
                                S.B[0][8].NUMBER(n%10,S.Color);
                              }
                              S.B[0][6].PRINT(0,6);
                              S.B[0][7].PRINT(0,7);
                              S.B[0][8].PRINT(0,8);
                              wait (1);
                              if(n==0)
                              l--;
                          }
            }while(l>=0);*/

        S.CONTROL(i,j);
}

void block::BLOCK(int ascii,int color)
{
     a11=a12=a13=a14=a15=a21=a22=a23=a24=a25=a31=a32=a33=a34=a35=ascii;
     c11=c12=c13=c14=c15=c21=c22=c23=c24=c25=c31=c32=c33=c34=c35=color;
}

void block::EFFECT(int i,bool effect)
{
    e[i]=effect;
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
     int i;
     BLOCK(0,0);
     for(i=0;i<20;i++)
        e[i]=0;
}

void block::CIRCLE(int color)
{
     BLOCK(NR,color);
     DOT(DR,color,11);
     DOT(DR,color,15);
     DOT(UR,color,31);
     DOT(UR,color,35);
}

void block::BOARDS(int color)
{
     BLOCK(R1,color);
}

void block::FIREUP()
{
     BLOCK(NR,12);
     e[0]=1; //e[0]=morte
     e[11]=1;
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
     BLOCK(NR,12);
     e[0]=1;
     e[11]=1;
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
     BLOCK(NR,12);
     e[0]=1;
     e[11]=1;
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
     BLOCK(NR,12);
     e[0]=1;
     e[11]=1;
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
     BLOCK(NR,15);
     e[0]=1;
     e[11]=1;
     HLINE(DR,12*16+14,1);
     HLINE(UR,12*16+14,3);
}

void block::FIREVLINE()
{
     BLOCK(NR,12);
     e[0]=1;
     e[11]=1;
     VLINE(NR,14,2);
     VLINE(NR,15,3);
     VLINE(NR,14,4);
}

void block::FIRECENTER()
{
     BLOCK(NR,15);
     e[0]=1;
     e[11]=1;
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
   VLINE(0,0,2);
   VLINE(0,0,3);
   VLINE(0,0,4);
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

void block::LETTER(char x, int color)
{
    ZERO();
    if(x=='a'||x=='A')
        {
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            DOT(UR,color,12);
            DOT(UR,color,13);
            DOT(UR,color,22);
            DOT(UR,color,23);
            DOT(UR,color,31);
            DOT(UR,color,34);
        }
    else if(x=='b'||x=='B')
        {
            VLINE(NR,color,1);
            VLINE(UR,color,2);
            VLINE(UR,color,3);
            VLINE(DR,color,4);
            DOT(UR,color,31);
            DOT(0,color,34);
        }
    else if(x=='c'||x=='C')
        {
            BLOCK(UR,color);
            HLINE(0,color,2);
            VLINE(0,color,5);
            DOT(NR,color,11);
            DOT(NR,color,21);
        }
    else if(x=='d'||x=='D')
        {
            BLOCK(UR,color);
            DOT(NR,color,11);
            DOT(DR,color,14);
            HLINE(NR,color,2);
            DOT(0,color,22);
            DOT(0,color,23);
            DOT(0,color,34);
            VLINE(0,color,5);
        }
    else if(x=='e'||x=='E')
        {
            BLOCK(UR,color);
            VLINE(0,0,5);
            DOT(NR,color,11);
            DOT(NR,color,21);
        }
    else if(x=='f'||x=='F')
        {
            BLOCK(UR,color);
            DOT(NR,color,11);
            DOT(NR,color,21);
            HLINE(0,color,3);
            DOT(UR,color,31);
            VLINE(0,color,5);
        }
    else if(x=='g'||x=='G')
        {
            BLOCK(UR,color);
            VLINE(0,0,5);
            DOT(NR,color,11);
            DOT(NR,color,21);
            DOT(0,color,22);
            DOT(NR,color,24);
        }
    else if(x=='h'||x=='H')
        {
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            DOT(UR,color,22);
            DOT(UR,color,23);
            DOT(UR,color,31);
            DOT(UR,color,34);
        }
    else if(x=='i'||x=='I')
        {
            VLINE(NR,color,2);
            VLINE(NR,color,3);
            DOT(UR,color,32);
            DOT(UR,color,33);
        }
    else if(x=='j'||x=='J')
        {
            VLINE(NR,color,4);
            HLINE(UR,color,3);
            DOT(DR,color,21);
            DOT(0,color,35);
        }
    else if(x=='k'||x=='K')
        {
            VLINE(NR,color,1);
            VLINE(UR,color,4);
            DOT(DR,color,13);
            DOT(UR,color,22);
            DOT(DR,color,23);
            DOT(0,color,24);
            DOT(UR,color,31);
        }
    else if(x=='l'||x=='L')
        {
            VLINE(NR,color,1);
            HLINE(UR,color,3);
            DOT(0,color,35);
        }
    else if(x=='m'||x=='M')
        {
            BLOCK(NR,color);
            DOT(DR,color,12);
            DOT(DR,color,13);
            DOT(UT,color*16,22);
            DOT(UT,color*16,23);
            HLINE(UR,color,3);
            DOT(0,color,32);
            DOT(0,color,33);
            VLINE(0,color,5);
        }
    else if(x=='n'||x=='N')
        {
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            DOT(DR,color,12);
            DOT(UR,color,23);
            DOT(UR,color,31);
            DOT(UR,color,34);
        }
    else if(x=='o'||x=='O')
        {
            BLOCK(UR,color);
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            DOT(0,color,22);
            DOT(0,color,23);
            HLINE(UR,color,3);
            VLINE(0,color,5);
        }
    else if(x=='p'||x=='P')
        {
            BLOCK(UR,color);
            VLINE(NR,color,1);
            DOT(NR,color,14);
            HLINE(0,color,3);
            DOT(UR,color,31);
            VLINE(0,color,5);
        }
    else if(x=='q'||x=='Q')
        {
            BLOCK(UR,color);
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            DOT(0,color,22);
            DOT(DR,color,23);
            HLINE(UR,color,3);
            VLINE(0,color,5);
        }
    else if(x=='r'||x=='R')
        {
            BLOCK(UR,color);
            DOT(NR,color,11);
            DOT(DR,color,14);
            DOT(NR,color,21);
            DOT(NR,color,23);
            DOT(0,color,24);
            DOT(0,color,32);
            VLINE(0,color,5);
        }
    else if(x=='s'||x=='S')
        {
            BLOCK(UR,color);
            VLINE(0,0,5);
            DOT(NR,color,11);
            DOT(NR,color,24);
        }
    else if(x=='t'||x=='T')
        {
            HLINE(UR,color,1);
            VLINE(NR,color,2);
            VLINE(NR,color,3);
            DOT(0,color,15);
            DOT(UR,color,32);
            DOT(UR,color,33);
        }
    else if(x=='u'||x=='U')
        {
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            HLINE(UR,color,3);
            DOT(0,color,35);
        }
    else if(x=='v'||x=='V')
        {
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            HLINE(0,color,3);
            DOT(UR,color,32);
            DOT(UR,color,33);
        }
    else if(x=='w'||x=='W')
        {
            VLINE(NR,color,1);
            VLINE(NR,color,4);
            HLINE(UR,color,3);
            DOT(DT,color*16,22);
            DOT(DT,color*16,23);
            DOT(0,color,35);
        }
    else if(x=='x'||x=='X')
        {
            DOT(NR,color,11);
            DOT(NR,color,14);
            DOT(DR,color,21);
            DOT(UR,color,22);
            DOT(UR,color,23);
            DOT(DR,color,24);
            DOT(UR,color,31);
            DOT(UR,color,34);
        }
    else if(x=='y'||x=='Y')
        {
            DOT(NR,color,11);
            DOT(NR,color,14);
            DOT(UR,color,21);
            DOT(NR,color,22);
            DOT(NR,color,23);
            DOT(UR,color,24);
            DOT(UR,color,32);
            DOT(UR,color,33);
        }
    else if(x=='z'||x=='Z')
        {
            BLOCK(UR,color);
            VLINE(0,color,5);
            DOT(NR,color,14);
            DOT(0,color,24);
            DOT(DR,color,21);
        }
    else if(x=='!')
        {
            VLINE(UR,color,3);
            DOT(NR,color,13);
        }
}

void block::BOMBERBALL()
{
    CIRCLE(15);
    DOT(VL,6*16,22);
    DOT(NR,6,23);
    DOT(VL,6*16,24);
}

void block::BOMBERBALL2()
{
    CIRCLE(14);
    DOT(E1,14*16+1,22);
    DOT(E1,14*16+1,24);
    DOT(DT,14*16+12,33);
}

void block::BOMBERDIE()
{
    CIRCLE(12);
    DOT('x',15*16,22);
    DOT(NR,15,23);
    DOT('x',15*16,24);

}

void block::GATE()
{
     CIRCLE(9);
     e[9]=1; //e[9]= fim da fase
     DOT(LT,16*9+11,22);
     DOT(NR,11,23);
     DOT(RT,16*9+11,24);
}

void block::BOMB1()
{
     CIRCLE(12*16+1);
     e[2]=1;
     DOT(201,1*16+8,13);
     DOT(B2,1*16+8,14);
     DOT(UR,1*16+8,23);
}

void block::BOMB2()
{
     BLOCK(NR,12);
     e[2]=1; //e[2]= parede quebravel
     e[7]=1; //e[7]= bomba
     DOT(201,12*16+8,13);
     DOT(B2,12*16+8,14);
     HLINE(NR,1,2);
     HLINE(NR,1,3);
     DOT(DR,12*16+1,21);
     DOT(UR,1*16+8,23);
     DOT(DR,12*16+1,25);
     DOT(UR,12*16+1,31);
     DOT(UR,12*16+1,35);
}

void block::MONSTER()
{
     CIRCLE(12);
     e[0]=1; //e[0]= morte
     HLINE(UT,12,1);
     DOT(E2,12*16,22);
     DOT(E3,12*16,24);
     DOT(UT,12*16,33);
}

//***Itens
void block::FIREIT()
{
     e[3]=1;//e[3]= item
     e[4]=1;//e[4]= fire item
     BLOCK(NR,12);
     HLINE(DR,14*16+12,3);
     DOT(NR,10,11);
     DOT(DR,10*16+12,12);
     DOT(DR,10*16+12,14);
     DOT(NR,10,15);
     DOT(UR,14*16+12,22);
     DOT(UR,15*16+14,23);
     DOT(UR,14*16+12,24);
     DOT(UR,10*16+12,31);
     DOT(UR,10*16+12,35);
}

void block::BOMBIT()
{
     CIRCLE(10*16+1);
     e[3]=1;
     e[5]=1; //e[5]= bomb item
     DOT(201,1*16+8,13);
     DOT(B2,1*16+8,14);
     DOT(UR,1*16+8,23);
}

void block::WALLIT()
{
    BLOCK(SQ,15*16+12);
    e[3]=1;
    e[6]=1; //e[6]= wall item
    VLINE('=',15*16+12,1);
    VLINE('=',15*16+12,2);
}

void block::LIFEIT()
{
    CIRCLE(10*16+15);
    e[3]=1;
    e[10]=1;
    DOT(VL,6*16,22);
    DOT(NR,6,23);
    DOT(VL,6*16,24);
}

void stage::BEGIN()
{
     int i,j;
     Memory.ZERO();
     Life=3;
     Color=11;
     Bomb=Fire=Stage=1;
     Time[0]=Time[1]=0;
     Time[2]=5;
     for(i=0;i<6;i++)
        Score[i]=0;
     for(i=0;i<13;i++)
        Pass[i]='\0';
     for(i=0;i<20;i++)
        Effect[i]=0;
     Effect[0]=1;
     for(i=0;i<15;i++)
                      for(j=0;j<15;j++)
                                      B[i][j].ZERO();
    for(i=1;i<14;i++)
                      for(j=1;j<14;j++)
                      {
                                      if(i==1||j==1||i==13||j==13)//Boards
                                                                  B[i][j].BOARDS(Color-8);
                                      else if(i%2==1&&j%2==1)//Blocks
                                      {
                                                                   B[i][j].BLOCK(NR,Color);
                                                                   B[i][j].e[1]=1; //e[1]= bloco inquebravel
                                      }
                      }
        TITLE();
}

void stage::PRINT()
{
     int i,j,x;
     for(i=0;i<15;i++)
                      for(x=1;x<4;x++)
                      {
                                      TC(0);
                                      printf("  ");
                                      for(j=0;j<15;j++)
                                                       B[i][j].PRINTLINE(x);
                                      printf("\n");
                      }
}

void stage::CONTROL(int i,int j)
{
    int k;
    gotoxy(j*5+3,i*3+3);
    do
    {
    Key=getch();
    if(Key=='\r')
            PASSWORD();
    else if(Key==' '&&B[i][j].e[7]==0)//Bomba
            {
                for(k=0;k<5;k++)
                {
                B[i][j].BOMB1();
                B[i][j].PRINT(i,j);
                //MOVE(i,j);
                sleep(200);
                B[i][j].BOMB2();
                B[i][j].PRINT(i,j);
                //MOVE(i,j);
                sleep(200);
                }
                //MOVE(i,j);
                sleep(200);
                B[i][j].e[2]=0;
                B[i][j].e[7]=0;
                EXPLOSION(i,j);
                Memory=B[i][j];
            }
    else if(Key=='d'||Key=='a')// Movimento
                j=MOVE(i,j);
    else if(Key=='s'||Key=='w')
                i=MOVE(i,j);
    }while(Key=='a'||Key=='s'||Key=='d'||Key=='w'||Key==' '||Key=='\r');
}

int stage::MOVE(int i,int j)
{
    int down,right;
    down=right=0;
    if(Key=='w')
            down=-1;
    else if(Key=='s')
            down=1;
    else if(Key=='a')
            right=-1;
    else if(Key=='d')
            right=1;
    if(Effect[6]==0)
        {
            if(B[i+down][j+right].e[2]==1)
            {
                if(Key=='w'||Key=='s')
                    return i;
                else
                    return j;
            }
        }
    if((Key=='w'&&i<=2)||(Key=='s'&&i>=12)||(Key=='a'&&j<=2)||(Key=='d'&&j>=12)||(B[i+down][j+right].e[1]==1))
            {
                if(Key=='w'||Key=='s')
                    return i;
                else
                    return j;
            }
    else
            {
                B[i][j]=Memory;
                B[i][j].PRINT(i,j);
                {
                if(B[i+down][j+right].e[3]==1)
                {
                    Memory.ZERO();
                    ITEM(i+down,j+right);
                }
                else
                    Memory=B[i+down][j+right];
                }
                {
                if(B[i+down][j+right].e[0]==1&&Effect[0]==1)
                    DIE(i+down,j+right);
                else
                    B[i+down][j+right].BOMBERBALL();
                }
                B[i+down][j+right].PRINT(i+down,j+right);
                {
                if(Key=='w'||Key=='s')
                    return (i+down);
                else
                    return (j+right);
                }
            }
}

void stage::ITEM(int i,int j)
{
   if(B[i][j].e[4]==1)
   {
       if(Fire<9)
       {
           Fire++;
           B[0][3].NUMBER(Fire,15);
           B[0][3].PRINT(0,3);
       }
   }
   else if(B[i][j].e[5]==1)
   {
       if(Bomb<9)
       {
           Bomb++;
           B[0][5].NUMBER(Bomb,15);
           B[0][5].PRINT(0,5);
       }
   }
   else if(B[i][j].e[10]==1)
   {
       if(Life<9)
       {
           Life++;
           B[0][1].NUMBER(Life,15);
           B[0][1].PRINT(0,1);
       }
   }
}


void stage::PASSWORD()
{
    int j;
    B[14][0].LETTER('!',12);
    B[14][0].PRINT(14,0);
    for(j=0;j<13;j++)
    {
        Pass[j]=getch();
        if(Pass[j]!='\r')
            {
                B[14][j+1].LETTER(Pass[j],15);
                B[14][j+1].PRINT(14,j+1);
            }
        else
                break;
    }
    B[14][0].LETTER('!',14);
    B[14][0].PRINT(14,0);
}

void stage::TITLE()
{
        B[0][0].LIFEIT();//***Titulo
        B[0][1].NUMBER(Life,15);
        B[0][1].DOT('x',15,21);
        B[0][2].FIREIT();
        B[0][3].NUMBER(Fire,15);
        B[0][3].DOT('x',15,21);
        B[0][4].BOMBIT();
        B[0][5].NUMBER(Bomb,15);
        B[0][5].DOT('x',15,21);
        B[0][6].NUMBER(Time[2],Color);
        B[0][7].NUMBER(Time[1],Color);
        B[0][7].DOT(':',Color,21);
        B[0][8].NUMBER(Time[0],Color);
        B[0][9].NUMBER(Score[5],15);
        B[0][10].NUMBER(Score[4],15);
        B[0][11].NUMBER(Score[3],15);
        B[0][12].NUMBER(Score[2],15);
        B[0][13].NUMBER(Score[1],15);
        B[0][14].NUMBER(Score[0],15);

        B[2][0].LETTER('S',Color);//***Fase
        B[3][0].LETTER('T',Color);
        B[4][0].LETTER('A',Color);
        B[5][0].LETTER('G',Color);
        B[6][0].LETTER('E',Color);
        B[8][0].NUMBER(Stage,Color);
}

void stage::EXPLOSION(int i,int j)
{
    bool up,down,left,right;
    int f;
    up=down=left=right=0;
    B[i][j].FIRECENTER();
    B[i][j].PRINT(i,j);
    sleep(100);
    B[i][j].ZERO();
    B[i][j].PRINT(i,j);
    for(f=1;f<=Fire;f++)
    {

        if(down==0&&i+f-1<12)
        {
            if(B[i+f][j].e[2]==1||B[i+f][j].e[3]==1||B[i+f][j].e[8]==1) //bloco SQ, item, monster
            {
            B[i+f][j].ZERO();
            B[i+f][j].PRINT(i+f,j);
            down=1;
            }
            else if(B[i+f][j].e[1]==1) //bloco NR
                down=1;
            else if(B[i+f][j].e[11]==1);//fire
            else if(B[i+f][j].e[7]==1) //bomb
                EXPLOSION(i+f,j);
            else
            {
                {
                if(f==Fire)
                    B[i+f][j].FIREDOWN();
                else
                    B[i+f][j].FIREVLINE();
                }
                B[i+f][j].PRINT(i+f,j);
                sleep(100);
                B[i+f][j].ZERO();
                B[i+f][j].PRINT(i+f,j);
            }
        }
        //
        if(up==0&&i-f+1>2)
        {
            if(B[i-f][j].e[2]==1||B[i-f][j].e[3]==1||B[i-f][j].e[8]==1)
            {
            B[i-f][j].ZERO();
            B[i-f][j].PRINT(i-f,j);
            up=1;
            }
            else if(B[i-f][j].e[1]==1)
                up=1;
            else if(B[i-f][j].e[11]==1);
            else if(B[i-f][j].e[7]==1)
                EXPLOSION(i-f,j);
            else
            {
                {
                if(f==Fire)
                    B[i-f][j].FIREUP();
                else
                    B[i-f][j].FIREVLINE();
                }
                B[i-f][j].PRINT(i-f,j);
                sleep(100);
                B[i-f][j].ZERO();
                B[i-f][j].PRINT(i-f,j);
            }
        }
        //
        if(right==0&&j+f-1<12)
        {
            if(B[i][j+f].e[2]==1||B[i][j+f].e[3]==1||B[i][j+f].e[8]==1)
            {
            B[i][j+f].ZERO();
            B[i][j+f].PRINT(i,j+f);
            right=1;
            }
            else if(B[i][j+f].e[1]==1)
                right=1;
            else if(B[i][j+f].e[11]==1);
            else if(B[i][j+f].e[7]==1)
                EXPLOSION(i,j+f);
            else
            {
                {
                if(f==Fire)
                    B[i][j+f].FIRERIGHT();
                else
                    B[i][j+f].FIREHLINE();
                }
                B[i][j+f].PRINT(i,j+f);
                sleep(100);
                B[i][j+f].ZERO();
                B[i][j+f].PRINT(i,j+f);
            }
        }
        //
        if(left==0&&j-f+1>2)
        {
            if(B[i][j-f].e[2]==1||B[i][j-f].e[3]==1||B[i][j-f].e[8]==1)
            {
                B[i][j-f].ZERO();
                B[i][j-f].PRINT(i,j-f);
                left=1;
            }
            else if(B[i][j-f].e[1]==1)
                left=1;
            else if(B[i][j-f].e[11]==1);
            else if(B[i][j-f].e[7]==1)
                EXPLOSION(i,j-f);
            else
            {
                {
                if(f==Fire)
                    B[i][j-f].FIRELEFT();
                else
                    B[i][j-f].FIREHLINE();
                }
                B[i][j-f].PRINT(i,j-f);
                sleep(100);
                B[i][j-f].ZERO();
                B[i][j-f].PRINT(i,j-f);
            }
        }
    }
}

void stage::DIE(int i,int j)
{
    B[i][j].BOMBERDIE();
    if(Life>0)
    {
        Life--;
        B[0][1].NUMBER(Life,15);
        B[0][1].PRINT(0,1);
    }
}
