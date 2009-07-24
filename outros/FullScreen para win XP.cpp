#include<stdio.h>
#include<stdlib.h>
#include"conio.c"
#include<time.h>
#include<windows.h>


void wait ( float seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}


main()
{
      keybd_event(VK_MENU,0x36,0,0);
      keybd_event(VK_RETURN,0x1c,0,0);
      keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
      keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
      //logo da Uel e nome
      system("color F0");
      printf("\n\n\n\n\n\n\n");
      for(int i=1;i<=11;i++)
      {
              printf("\n\t\t");
              for(int j=1;j<=15;j++)
              {
                      if(i==1)
                      {
                              if(j==5||j==11)
                              {
                                             textcolor(0);
                                             printf("\xDB");
                                             }
                              if(j==7||j==8||j==9)
                              {
                                             textcolor(10);
                                             printf("\xDB");
                                             }
                              if((j>0&&j<5)||(j==6)||(j==10)||(j>11&&j<16))
                              {
                                             textbackground(15);                                      
                                             printf(" ");
                                             }
                              if(j==15)
                              {
                                       textcolor(0);
                                       printf("\t\tUNIVERSIDADE ESTADUAL DE LONDRINA");
                                       }
                      }
                      if(i==2)
                      {
                              if(j==5||j==11)
                              {
                                             textcolor(0);
                                             printf("\xDB");
                                             }
                              if(j>6&&j<10)
                              {
                                             textcolor(10);
                                             printf("\xDB");
                                             }
                              if((j>0&&j<5)||(j==6)||(j==10)||(j>11&&j<16))
                              {
                                             textbackground(15);                              
                                             printf(" ");
                                             }
                      }
                      if(i==3)
                      {
                              if(j==3||j==5||j==11||j==13)
                              {
                                             textcolor(0);
                                             printf("\xDB");
                                             }
                              if(j==8)
                              {
                                      textcolor(10);
                                      printf("\xDB");
                                      }
                              if(j==1||j==2||j==4||j==6||j==7||j==9||j==10||j==12||j==14||j==15)
                              {
                                      textbackground(15);
                                      printf(" ");
                                      }
                      }
                      if(i==4||i==5||i==6)
                      {
                              if(j==1||j==3||j==5||j==11||j==13||j==15)
                              {
                                       textcolor(0);
                                       printf("\xDB");
                                       }
                              if(j==8)
                              {
                                      textcolor(10);
                                      printf("\xDB");
                                      }
                              if(j==2||j==4||j==6||j==7||j==9||j==10||j==12||j==14)
                              {
                                       textbackground(15);
                                       printf(" ");
                                       }
                              if(i==4&&j==15)
                              {
                                             textcolor(0);
                                             printf("\t\tERNESTO YUITI SAITO");
                                             }
                              if(i==6&&j==15)
                               {
                                             textcolor(0);
                                              printf("\t\tHAYATO FUJII");
                                              }
                      }
                      if(i==7)
                      {
                              if((j>1&&j<7)||(j>9&&j<15))
                              {
                                       textcolor(0);
                                       printf("\xDB");
                                       }
                              if(j==8)
                              {
                                      textcolor(10);
                                      printf("\xDB");
                                      }
                              if(j==1||j==7||j==9||j==15)
                              {
                                       textbackground(15);
                                       printf(" ");
                                       }
                      }
                      if(i==8||i==10)
                      {
                               if(j==8)
                               {
                                       textcolor(10);
                                       printf("\xDB");
                                       }
                               if((j>0&&j<8)||(j>8&&j<16))
                               {
                                       textbackground(15);
                                       printf(" ");
                                       }
                               if(i==8&&j==15)
                               {
                                               textcolor(0);
                                               printf("\t\tMARCOS OKAMURA RODRIGUES");
                                               }
                      }
                      if(i==9)
                      {
                              if(j==8)
                              {
                                      textcolor(10);
                                      printf("\xDB");
                                      }
                               if((j>2&&j<7)||(j>9&&j<14))
                               {
                                       textcolor(0);
                                       printf("\xDB");
                                       }
                               if(j==1||j==2||j==7||j==9||j==14||j==15)
                               {
                                       textbackground(15);
                                       printf(" ");
                                       }
                      }
                      if(i==11) 
                      {
                                if(j==8)
                              {
                                      textcolor(10);
                                      printf("\xDB");
                                      }
                               if((j>3&&j<7)||(j>9&&j<13))
                               {
                                       textcolor(0);
                                       printf("\xDB");
                                       }
                               if(j==1||j==2||j==3||j==7||j==9||j==13||j==14||j==15)
                               {
                                       textbackground(15);
                                       printf(" ");
                                       }
                               if(j==15)
                               {
                                               textcolor(0);
                                               printf("\t\tCIENCIA DA COMPUTACAO - 2009");
                                               }
                      }                                                             
                                             
                                       
              }
      }
      wait(7);
      system("cls");
      
      //abertura - impressao do BOMBERBALL e o bomberMAN
      textcolor(15);
      system("color 0F");
      printf("\n\n\n");
      for(int i=1;i<=5;i++)
      {
              wait(0.6);
              printf("\n\t\t");
              //logo BOMBERBALL
              for(int j=1;j<=40;j++)
              {
                      if(i==1)
                      {
                              if(j==1||j==2||j==6||j==9||j==13||j==15||j==16||j==19||j==20||j==22||j==23||j==24||j==28||j==29||j==33||j==36||j==39)
                              {
                                   printf("\xDB");
                                   }
                              else
                              {
                                   printf(" ");
                                  }
                      }
                      if(i==2)
                      {
                              if(j==1||j==3||j==5||j==7||j==9||j==10||j==12||j==13||j==15||j==17||j==19||j==22||j==25||j==28||j==30||j==32||j==34||j==36||j==39)
                              {
                                   printf("\xDB");
                                   }
                              else
                              {
                                   printf(" ");
                                   }
                      }
                      if(i==3)
                      {
                              if(j==1||j==2||j==5||j==7||j==9||j==11||j==13||j==15||j==16||j==19||j==20||j==22||j==23||j==24||j==28||j==29||j==32||j==33||j==34||j==36||j==39)
                              {
                                   printf("\xDB");
                                   }
                              else
                              {
                                  printf(" ");
                                  }
                      }
                      if(i==4)
                      {
                              if(j==1||j==3||j==5||j==7||j==9||j==13||j==15||j==17||j==19||j==22||j==24||j==28||j==30||j==32||j==34||j==36||j==39)
                              {
                                   printf("\xDB");
                                   }
                              else
                              {
                                   printf(" ");
                                   }
                      }
                      if(i==5)
                      {
                              if(j==1||j==2||j==6||j==9||j==13||j==15||j==16||j==19||j==20||j==22||j==25||j==28||j==29||j==32||j==34||j==36||j==37||j==39||j==40)
                              {
                                   printf("\xDB");
                                   }
                              else
                              {
                                  printf(" ");
                                  }
                      }
                                   
              
              }
      }
      wait(1);
      system("color 8E");
      printf("\n");
      //bomberMAN
      for(int i=1;i<=20;i++)
      {
              printf("\n\t\t\t");
              for(int j=1;j<=24;j++)
              {
                      if(i==1||i==2)
                      {
                              if(j==5||j==6||j==7||j==8)
                              {
                                   textcolor(13);                     
                                   printf("\xDB");
                                   }
                              else
                              {
                                  textbackground(8);
                                  printf(" ");
                                  }
                      }
                      if(i==3)
                      {
                              if(j==6||j==7)
                              {
                                   textcolor(0);
                                   printf("\xDB");
                                   }
                              else
                              {
                                   textbackground(8);
                                   printf(" ");
                                   }
                      }
                      if(i==4)
                      {
                              if(j==4||j==5||j==6||j==7||j==8||j==9)
                              {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                              else
                              {
                                   textbackground(8);
                                   printf(" ");
                                   }
                      }
                      if(i==5||i==11)
                      {
                              if(j==3||j==4||j==5||j==6||j==7||j==8||j==9||j==10)
                              {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                              if(i==11&&j==23)
                              {
                                    textcolor(4);
                                    printf("\xDB");
                                    }
                              if((i==5)&&((j==1)||(j==2)||(j>10&&j<25)))
                              {
                                   textbackground(8);
                                   printf(" ");
                                   }
                              if((i==11)&&((j==1)||(j==2)||(j>10&&j<23)||(j==24)))
                              {
                                   textbackground(8);
                                   printf(" ");
                                   }
                      }
                      if(i==6||i==10)
                      {
                              if(j==2||j==3||j==10||j==11)
                              {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                              if(j>3 && j<10)
                              {
                                   textcolor(13);
                                   printf("\xDB");
                                   }
                              if((i==6)&&(j==1||(j>11&&j<25)))
                              {
                                   textbackground(8);          
                                   printf(" ");
                                   }
                              if((i==10)&&((j==1)||(j>11&&j<22)||(j==23)))
                              {
                                   textbackground(8);
                                   printf(" ");
                                   }
                              if((i==10)&&(j==22||j==24))
                              {
                                   textcolor(12);
                                   printf("\xDB");
                                   }                                  
                      }
                      if(i==7||i==8||i==9)
                      {
                              if(j==1||j==2||j==11||j==12)
                              {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                              if(j==5||j==8)
                              {
                                   textcolor(0);
                                   printf("\xDB");
                                   }
                              if(j==3||j==4||j==6||j==7||j==9||j==10)
                              {
                                   textcolor(13);
                                   printf("\xDB");
                                   }
                              if(j>12&&j<26)
                              {
                                            textbackground(8);
                                            printf(" ");
                                            }
                                  
                      }
                      if(i==12)
                      {
                               if(j==5||j==6||j==7||j==8)
                               {
                                   textcolor(9);
                                   printf("\xDB");
                                   }
                               if(j==22)
                               {
                                        textcolor(7);
                                        printf("\xDB");
                                        }
                               if(j==24)
                               {
                                        textcolor(12);
                                        printf("\xDB");
                                        }    
                               if((j>0&&j<5)||(j>8&&j<22)||(j==23))
                               {
                                   textbackground(8);
                                   printf(" ");
                                   }
                      }
                      if(i==13)
                      {
                               if(j==5||j==6||j==7||j==8)
                               {
                                   textcolor(9);
                                   printf("\xDB");
                                   }
                               if(j==4||j==9)
                               {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                               if(j==22)
                               {
                                        textcolor(7);
                                        printf("\xDB");
                                        }
                               if((j>0&&j<4)||(j>9&&j<21)||(j>21&&j<25))
                               {
                                   textbackground(8);                       
                                   printf(" ");
                                   }
                      }
                      if(i==14)
                      {
                               if(j==5||j==6||j==7||j==8)
                               {
                                   textcolor(9);
                                   printf("\xDB");
                                   }
                               if(j==3||j==10)
                               {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                               if(j>18&&j<24)
                               {
                                   textcolor(0);
                                   printf("\xDB");
                                   } 
                               if(j==1||j==2||j==4||j==9||(j>10&&j<19)||j==24)
                               {
                                   textbackground(8);                                    
                                   printf(" ");
                                   }
                      }
                      if(i==15)
                      {
                               if(j==1||j==2||j==11||j==12)
                               {
                                   textcolor(13);
                                   printf("\xDB");
                                   }
                               if(j==5||j==9)
                               {
                                   textcolor(0);
                                   printf("\xDB");
                                   }
                               if(j==6||j==7)
                               {
                                   textcolor(14);
                                   printf("\xDB");
                                   }
                               if(j>17&&j<25)
                               {
                                   textcolor(0);
                                   printf("\xDB");
                                   }
                               if(j==3||j==4||j==9||j==10||(j>12&&j<18))
                               {
                                   textbackground(8);                       
                                   printf(" ");
                                   }
                      }
                      if(i==16)
                      {
                               if(j==1||j==2||j==11||j==12)
                               {
                                   textcolor(13);
                                   printf("\xDB");
                                   }
                               if(j>4&&j<9)
                               {
                                   textcolor(9);
                                   printf("\xDB");
                                   }
                               if(j>17&&j<25)
                               {
                                   textcolor(0);
                                   printf("\xDB");
                                   }
                               if(j==3||j==4||j==9||j==10||(j>12&&j<18))
                               {
                                   textbackground(8);                       
                                   printf(" ");
                                   }
                      }
                      if(i==17||i==18)
                      {
                               if(j==5 || j==8)
                               {
                                   textcolor(15);
                                   printf("\xDB");
                                   }
                               if((i==17||i==18)&&(j>0&&j<5)||(j>5&&j<8)||(j>8&&j<18))
                               {
                                   textbackground(8);                                   
                                   printf(" ");
                                   }
                               if((i==17||i==18)&&(j>17&&j<25))
                               {
                                   textcolor(0);
                                   printf("\xDB");
                                   }
                      }
                      if(i==19)
                      {
                               if(j==5 || j==8)
                               {
                                       textcolor(15);
                                       printf("\xDB");
                                       }
                               if((j>0&&j<5)||(j>5&&j<8)||(j>8&&j<19)||(j==24))
                               {
                                   textbackground(8);
                                   printf(" ");
                                   }
                               if(j>18&&j<24)
                               {
                                   textcolor(0);
                                   printf("\xDB");
                                   }         
                      }
                      if(i==20)
                      {
                               if(j>3&&j<10)
                               {
                                   textcolor(13);
                                   printf("\xDB");
                                   }
                               if((j>0&&j<4)||(j>9&&j<13))
                               {
                                   textbackground(8);                       
                                   printf(" ");
                                   }
                      }                                                                                                                                                                                                                                       
                                                                                                             
                      
              }
      }
      textcolor(14);
      wait(1);        
      printf("\n\n\n\t\t\t***APERTE ENTER***\n\n\n");
                                                                                                                                                
      printf("\n\n\n\n\n\n\n\n\n\n");                                                              
      system("pause");
}
