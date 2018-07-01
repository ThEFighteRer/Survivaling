#include "grafika.h"
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

int g=0;

void*grafika(ALLEGRO_THREAD *thr,void *arg)
{
         struct dla_grafiki *args = (struct dla_grafiki*)arg;
         ALLEGRO_DISPLAY_MODE   disp_data;
         al_init_image_addon();
         al_init_primitives_addon();
         al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
         al_set_new_display_flags(ALLEGRO_FULLSCREEN);
         graficzny* g=new graficzny(args);

         int X=args->X_kratka,Y=args->Y_kratka;
         int menu_x=150*args->rozdz_X/1920,menu_y=50*args->rozdz_Y/1080;
         args->menu_x=menu_x; args->menu_y=menu_y;

         al_set_target_bitmap(al_get_backbuffer(g->display));

         al_set_target_bitmap(g->plansza1);

         char mysza_jest_jakas='n';///n nijaka, a aim, z zajeta
         ALLEGRO_MOUSE_CURSOR *aim = al_create_mouse_cursor(g->kursor_aim, 17, 17);


         ALLEGRO_TIMER* timer=al_create_timer(0.02);
         ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
         al_register_event_source(event_queue, al_get_timer_event_source(timer));
         al_start_timer(timer);
         int animacja = 1;ALLEGRO_EVENT ev;


         while(true)
         {
                  if(args->flaga_zakoncz==1) break;

                  if(g->args->myszka_zajeta)
                           {if(mysza_jest_jakas!='z')
                           {al_set_system_mouse_cursor(g->display,ALLEGRO_SYSTEM_MOUSE_CURSOR_BUSY);mysza_jest_jakas='z';}}
                  else if(g->args->myszka_aim)
                           {if(mysza_jest_jakas!='a')
                           {al_set_mouse_cursor(g->display, aim);mysza_jest_jakas='a';}}
                  else if(mysza_jest_jakas!='n')
                           {al_set_system_mouse_cursor(g->display,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);mysza_jest_jakas='n';}


                  al_wait_for_event(event_queue, &ev);
                  if(ev.type == ALLEGRO_EVENT_TIMER)
                  {
                  ++animacja; if(animacja==98) animacja=1;
                  g->animacja=animacja;

                  //std::cout<<"P";
                  g->rysuj();
                  //std::cout<<"K";
                  }
                  //al_rest(0.001);
         }

         al_destroy_timer(timer);

         delete g;

         args->zakonczylem=1;return NULL;
}


void graficzny::rysuj()
{
         float C1=1.0, C2=1.0, C3=1.0, C4=1.0;
         unsigned char b=210;///od 1 do 255
         //float b=1.0;
         C1=b;C2=b;C3=b;//C4=b;

         graficzny *g = this;
         if(g->args->flaga_zakoncz==1) return;
         ++g->animacja; if(g->animacja==98) g->animacja=1;

         al_set_target_bitmap(g->plansza1);

         if(g->args->otwarte_menu_anatomii)
         {
                  args->nat_osw_alt = 1;
                  g->rysuj_menu_anatomii();
         }
         else if(g->args->otwarte_menu_craftingu)
         {
                  args->nat_osw_alt = 1;
                  g->rysuj_crafting(g->plansza1);
         }
         else if(g->args->otwarty_ekwipunek)
         {
                  args->nat_osw_alt = 1;
                  g->rysuj_ekwipunek();
        }
        else if(g->args->wysokosci)
        {
                for(short h=0; h<21; ++h)
                {
                    for(short j=0; j<13; ++j)
                    {
                            al_draw_bitmap_region(g->wys, g->args->wys[j][h]*g->X, 0, g->X,g->Y,(h+1)*g->X+g->acc->przesuniecie[j+1][h+1].x-(g->args->X_kratka/2), (j+1)*g->Y+g->acc->przesuniecie[j+1][h+1].y-(g->args->Y_kratka/2),0);
                    }
                }
        }
         else
         {
                  args->nat_osw_alt = 0;
                  C1 = args->nat_osw;
                  C2 = args->nat_osw;
                  C3 = args->nat_osw;
                  C4 = 1.0;
                  int b;
                  for(int l=0; l<2; l++)
                  {
                           switch(l) {case 0:al_set_target_bitmap(g->plansza1);g->acc=g->plansza_1; break;case 1:al_set_target_bitmap(g->plansza2);g->acc=g->plansza_2;break;}
                           if(l==1 && !g->args->przesuwamy_plansze) break;


                           //al_draw_tinted_bitmap(g->tlo[0][0], al_map_rgba_f (C1,C2,C3,C4), 0,0,0);

                           z_planszy *pl = g->acc;


                           /*for(short v=0;v<23;++v)
                                    for(short w=0;w<15;++w)
                                    {
                                             C1 = pl->oswietlenie[w][v];
                                             al_draw_tinted_bitmap_region(g->tlo[0], al_map_rgba_f (C1,C1,C1,C4), v*g->X-g->X/2,w*g->Y-g->Y/2,g->X, g->Y, v*g->X-g->X/2,w*g->Y-g->Y/2, 0);
                                    }*/

                           for(short v=0;v<21;++v)
                                    for(short w=0;w<13;++w)
                                    {
                                             C1 = pl->oswietlenie[w+1][v+1];
                                             al_draw_tinted_bitmap_region(g->tlo[g->acc->b_akt], al_map_rgba_f (C1,C1,C1,C4), v*g->X,w*g->Y,g->X, g->Y, v*g->X+g->X/2,w*g->Y+g->Y/2, 0);
                                    }

                           for(short i=0; i<23; ++i)
                                    {
                                             C1 = pl->oswietlenie[0][i];
                                             al_draw_tinted_bitmap_region(g->tlo[g->acc->b_high], al_map_rgba_f (C1,C1,C1,C4), i*g->X-g->X/2,0,g->X, g->Y/2, i*g->X-g->X/2,0, 0);
                                             //std::cout<<pl->oswietlenie[22][i]<<std::endl;
                                             C1 = pl->oswietlenie[14][i];
                                             short ttt = 13.5 * float(g->Y);
                                             al_draw_tinted_bitmap_region(g->tlo[g->acc->b_down], al_map_rgba_f (C1,C1,C1,C4), i*g->X-g->X/2,ttt,g->X, std::ceil(float(g->Y)/2.0), i*g->X-g->X/2,ttt, 0);
                                    }

                           for(short i=0; i<15; ++i)
                                    {
                                             C1 = pl->oswietlenie[i][0];
                                             al_draw_tinted_bitmap_region(g->tlo[g->acc->b_left], al_map_rgba_f (C1,C1,C1,C4), 0, g->Y*i-g->Y/2,g->X/2, g->Y, 0, g->Y*i-g->Y/2, 0);
                                             //std::cout<<pl->oswietlenie[22][i]<<std::endl;
                                             C1 = pl->oswietlenie[i][22];
                                             short ttt = 21.5 * float(g->X);
                                             al_draw_tinted_bitmap_region(g->tlo[g->acc->b_right], al_map_rgba_f (C1,C1,C1,C4), ttt, g->Y*i-g->Y/2,std::ceil(float(g->X)/2.0), g->Y, ttt, g->Y*i-g->Y/2, 0);
                                    }

                           int i,j;


                           if(pl!=NULL && pl->podlogi!=NULL)
                                    for(i = 0; i<pl->podlogi->ilosc;++i)
                                    {
                                             short wiek = (short)pl->podlogi->obiekt[i]->a.y>=(short)pl->podlogi->obiekt[i]->b.y ? (short)pl->podlogi->obiekt[i]->a.y : (short)pl->podlogi->obiekt[i]->b.y
                                             , mniej = (short)pl->podlogi->obiekt[i]->a.y<(short)pl->podlogi->obiekt[i]->b.y ? (short)pl->podlogi->obiekt[i]->a.y : (short)pl->podlogi->obiekt[i]->b.y;

                                             for(short w = (short)pl->podlogi->obiekt[i]->a.x; w<=(short)pl->podlogi->obiekt[i]->b.x; ++w)
                                             {
                                                      for(short v = mniej; v<wiek; ++v)
                                                      {
                                                               C1 = pl->oswietlenie[v+1][w+1];
                                                               al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C1,C1,C4), g->X*((short)pl->podlogi->obiekt[i]->jaka), g->Y*9, g->X,g->Y, w*g->X+(g->args->X_kratka/2), v*g->Y+(g->args->Y_kratka/2),0);
                                                      }
                                             }
                                    }

                           for(int w=0; w<15; w++)
                           {
                                    for(int v=1; v<22; v++)
                                    {
                                             j=v; i=w;
                                             int a=0;

                                             if(g->acc->ziemia[w][v])
                                             {
                                                      C1 = pl->oswietlenie[w][v];
                                                      al_draw_tinted_bitmap_region(g->equ_akcesoria, al_map_rgba_f (C1,C1,C1,C4),g->X*5,0,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                             }

                                    }
                                    for(int v=0; v<23; v++)
                                    {
                                             C1 = C2 = C3 = pl->oswietlenie[w][v];
                                             j=v; i=w;
                                             int a=0;

                                             a = g->animacja/4; if(a==24) a=23;
                                             //std::cout<<a<<std::endl;
                                             if((g->acc->stany_srodowisk[i][j]&4)!=0)
                                                      al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1,C2,C3,C4),g->X,3*g->Y,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                             if((g->acc->stany_srodowisk[i][j]&2)!=0)
                                                      al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1,C2,C3,C4),0,3*g->Y,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                             if((g->acc->stany_srodowisk[i][j]&1)==1)
                                                      al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1,C2,C3,C4),(a%12)*g->X,(a/12+1)*g->Y,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);

                                             if(g->acc->srodowisko[w][v][0]>=291 && g->acc->srodowisko[w][v][0]<590)///zwloki
                                             {
                                                      a=g->acc->srodowisko[w][v][0];a-=291;
                                                      if(a==0)al_draw_tinted_bitmap_region(g->zwierzeta, al_map_rgba_f (C1,C2,C3,C4),g->X*8,g->Y,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                                      else if(a==1)al_draw_tinted_bitmap_region(g->zwierzeta, al_map_rgba_f (C1,C2,C3,C4),g->X*8,g->Y*2,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                                      else if(a<20)al_draw_tinted_bitmap_region(g->zombie, al_map_rgba_f (C1,C2,C3,C4),g->X*((a-2)%9),g->Y*((a-2)/9+12),g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                                      else {}
                                            }
                                            else if(g->acc->srodowisko[w][v][0]>=590 && g->acc->srodowisko[w][v][0]<594)///ognisko
                                             {
                                                      a=g->acc->srodowisko[w][v][0];a-=590;
                                                      al_draw_tinted_bitmap_region(g->el_stale, al_map_rgba_f (C1,C2,C3,C4),g->X*a,g->Y,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                            }
                                             else if(g->acc->srodowisko[w][v][0]>=769 && g->acc->srodowisko[w][v][0]<812)///okno
                                             {
                                                      a=g->acc->srodowisko[w][v][0];a-=769;//a/=g->args->X_kratka;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a%9),g->Y*2,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                            }
                                            else if(g->acc->srodowisko[w][v][0]>=812 && g->acc->srodowisko[w][v][0]<3000)///drzwi
                                             {
                                                      a=g->acc->srodowisko[w][v][0];a-=812;//a/=g->args->X_kratka;770
                                                      int ktore_drzwi=a/512; a%=512;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a/256) + ktore_drzwi*g->X*2,g->Y*4,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                      /*a/=256;
                                                      ktore_drzwi=(a/128)*2;a/=128;ktore_drzwi+=a/64; a/=64;
                                                      switch(ktore_drzwi)
                                                      {
                                                               case 1:{
                                                               ktore_drzwi=a/32*2;a/=32;ktore_drzwi+=a/16; --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*6,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                               }break;
                                                               case 2:{
                                                               ktore_drzwi=a/32*2;a/=32;ktore_drzwi+=a/16; a/=16; ktore_drzwi+=2;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*5,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                               ktore_drzwi=a/8*2;a/=8;ktore_drzwi+=a/4; ktore_drzwi+=2;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*6,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                               }break;
                                                               case 3:{
                                                               ktore_drzwi=a/32*2;a/=32;ktore_drzwi+=a/16; a/=16; --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*5,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                               ktore_drzwi=a/8*2;a/=8;ktore_drzwi+=a/4; a/=4; --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*6,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                               ktore_drzwi=a/2*2;a/=2;ktore_drzwi+=a;  --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*7,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                               }break;
                                                               case 0:default:break;
                                                      }*/
                                            }
                                            else if(g->acc->srodowisko[w][v][0]>=3000 && g->acc->srodowisko[w][v][0]<3100)///trawa
                                             {
                                                      a=g->acc->srodowisko[w][v][0];a-=3000;
                                                      if(a/3 == 1)
                                                      {
                                                               a=0; if(g->animacja>16 && g->animacja<=49)a+=1; else if(g->animacja>49 && g->animacja<84)a+=2;
                                                               al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,g->Y*10,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                                      }
                                                      else if(a/3==0)
                                                      {
                                                               if(g->animacja<12 || g->animacja>87 || (g->animacja>37 && g->animacja<62))a+=3;
                                                               al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,0,g->X,g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                                      }
                                             }
                                             else if(g->acc->srodowisko[w][v][0]>=4500 && g->acc->srodowisko[w][v][0]<4600)///galaz
                                             {
                                                      a=g->acc->srodowisko[w][v][0]; a-=4500;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a+3),g->Y*10,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->srodowisko[w][v][0]>=4600 && g->acc->srodowisko[w][v][0]<4700)///halogen
                                             {
                                                      a=g->acc->srodowisko[w][v][0]; a-=4600;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a),g->Y*16,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->srodowisko[w][v][0]>=4700 && g->acc->srodowisko[w][v][0]<4800)///reflektor
                                             {
                                                      a=g->acc->srodowisko[w][v][0]; a-=4700;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*((a>=8)*2+(a&1)),g->Y*17,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                                      if(a&4)
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(4+((a&2)==0)),g->Y*17,g->X,g->Y, j*g->X+g->acc->przesuniecie_srodowisk[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie_srodowisk[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                    }
                                    for(int v=1; v<23; v++)
                                    {
                                             j=v; i=w;
                                             int a=0;

                                             if(g->acc->upadli[w][v]>=590 && g->acc->upadli[w][v]<=765)
                                             {
                                                      C1 = C2 = C3 = pl->oswietlenie[w][v];
                                                      int ile=g->acc->upadli[w][v]-590;int x=ile%9, y=ile/9;
                                                      al_draw_tinted_bitmap_region(g->zombie, al_map_rgba_f (C1,C2,C3,C4),x*g->X,y*g->Y,g->X,g->Y,j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2), 0);
                                             }
                                    }

                           for(int v=0; v<23; v++)
                                    {
                                             i=w;j=v;
                                             int a=0;
                                             C1 = C2 = C3 = pl->oswietlenie[w][v];


                                             a = g->animacja/5;
                                             //std::cout<<a<<std::endl;
                                             if((g->acc->stany_obiektow[i][j]&1)==1)
                                                      al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1,C2,C3,C4),(a%11)*g->X,0,g->X,g->Y,j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2), 0);

                                             if(g->acc->otoczenie[w][v][0]==0);
                                             else if(g->acc->otoczenie[w][v][0]>=10 &&g->acc->otoczenie[w][v][0]<=50)
                                             {
                                                      int x,y,n=0;
                                                      switch(g->acc->otoczenie[w][v][0])
                                                      {
                                                               case 10:{x=0; y=1; break;}case 11:{x=1; y=1; break;}case 12:{x=2; y=1; break;}case 13:{x=3; y=1; break;}
                                                               case 16:{x=0; y=2; break;}case 17:{x=1; y=2; break;}case 18:{x=2; y=2; break;}case 19:{x=3; y=2; break;}
                                                               case 24:{x=0; y=0; break;}case 25:{x=1; y=0; break;}case 26:{x=2; y=0; break;}case 27:{x=3; y=0; break;}
                                                               case 30:{x=0; y=3; break;}case 31:{x=1; y=3; break;}case 32:{x=2; y=3; break;}
                                                      }


                                                      al_draw_tinted_bitmap_region(g->avatar, al_map_rgba_f (C1,C2,C3,C4),x*g->X,y*g->Y,g->X,g->Y,j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2), 0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]<=210) //drzewo
                                             {
                                                      a = g->acc->otoczenie[w][v][0];
                                                      a-=51; b = 0;
                                                      if(g->animacja<16) b=0; else if(g->animacja<49) b=1; else if(g->animacja<82) b=2;
                                                       al_draw_tinted_bitmap_region(g->drzewa, al_map_rgba_f (C1,C2,C3,C4),b*g->X,a*g->Y,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]<=245)//sarna
                                             {
                                                      int ile=g->acc->otoczenie[w][v][0]-210;///int x=ile%9, y=ile/9;
                                                      //a=(animacja%33); if(a>=3) a=2;//cout<<al_get_bitmap_height(drzewa[0])<<" "<<al_get_bitmap_width(drzewa[0]);
                                                      al_draw_tinted_bitmap_region(g->zwierzeta, al_map_rgba_f (C1,C2,C3,C4),g->X*(ile%8),g->Y,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      ile/=8;
                                                      if(ile>1)al_draw_tinted_bitmap_region(g->zwierzeta, al_map_rgba_f (C1,C2,C3,C4),g->X*(ile-2),0,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]==246)///woda
                                             {
                                                      //a=0; if(g->animacja>25) a=1; if(g->animacja>50) a=2; if(g->animacja>75) a=1;
                                                      //al_draw_bitmap_region(g->krajobraz,g->X*a,g->Y,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);

                                                      a=0; a=g->animacja/14; /// 14 to polowa animacji
                                                      al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1,C2,C3,C4),g->X*(a%12),(4+(a>=12))*g->Y,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                            }
                                             else if(g->acc->otoczenie[w][v][0]<253)///trawa
                                             {//if(animacja<12 || (animacja>=25 && animacja<36)|| (animacja>=50 && animacja<62)|| (animacja>=75 && animacja<87))a+=3;
                                                      a=g->acc->otoczenie[w][v][0];a-=247; if(g->animacja<12 || (g->animacja>50 && g->animacja<75)|| (g->animacja>50 && g->animacja<75))a+=3;///if(animacja/50==0) a+=3;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,0,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]<=290)///niedzwiedz
                                             {
                                                      int ile=g->acc->otoczenie[w][v][0]-253;///int x=ile%9, y=ile/9;
                                                      //a=(animacja%33); if(a>=3) a=2;//cout<<al_get_bitmap_height(drzewa[0])<<" "<<al_get_bitmap_width(drzewa[0]);
                                                      //al_draw_bitmap_region(g->zwierzeta,g->X*(ile%8),g->Y*2,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      al_draw_tinted_bitmap_region(g->zwierzeta, al_map_rgba_f (C1,C2,C3,C4),g->X*(ile%8),g->Y*2,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);


                                                      ile/=8;
                                                      if(ile>1)al_draw_tinted_bitmap_region(g->zwierzeta, al_map_rgba_f (C1,C2,C3,C4),g->X*(ile-2),0,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]<765)
                                             {
                                                      int ile=g->acc->otoczenie[i][j][0]-590;int x=ile%9, y=ile/9;
                                                      al_draw_tinted_bitmap_region(g->zombie, al_map_rgba_f (C1,C2,C3,C4),x*g->X,y*g->Y,g->X,g->Y,j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2), 0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]<767)
                                             {
                                                      a=0; if(g->acc->otoczenie[w][v][0]==766) a=1;
                                                      al_draw_tinted_bitmap_region(g->el_stale, al_map_rgba_f (C1,C2,C3,C4),a*g->X,0,g->X,g->Y,j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2), 0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]<768)
                                             {
                                                      al_draw_tinted_bitmap_region(g->el_stale, al_map_rgba_f (C1,C2,C3,C4),0,g->Y*2,g->X,g->Y,j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2), 0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=769 && g->acc->otoczenie[w][v][0]<812)///okno
                                             {
                                                      a=g->acc->otoczenie[w][v][0];a-=769;//a/=g->args->X_kratka;


                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a%9),g->Y*2,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a/9),g->Y*3,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                            }
                                            else if(g->acc->otoczenie[w][v][0]>=812 && g->acc->otoczenie[w][v][0]<3000)///drzwi
                                             {
                                                      a=g->acc->otoczenie[w][v][0];
                                                      a-=812;//a/=g->args->X_kratka;770
                                                      int ktore_drzwi=a/512; a%=512;
                                                      //std::cout<<a<<std::endl;
                                                      //std::cout<<ktore_drzwi<<std::endl;
                                                      //std::cout<<"XD"<<std::endl;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a/256)+ktore_drzwi*2*g->X,g->Y*4,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      //std::cout<<g->X*(a/256)+ktore_drzwi*2*g->X;
                                                      /*a%=256;
                                                      ktore_drzwi=(a/128)*2;a%=128;ktore_drzwi+=a/64; a%=64;
                                                      switch(ktore_drzwi)
                                                      {
                                                               case 1:{
                                                               ktore_drzwi=a/32*2;a%=32;ktore_drzwi+=a/16; --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*6,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                               }break;
                                                               case 2:{
                                                               ktore_drzwi=a/32*2;a%=32;ktore_drzwi+=a/16; a%=16; ktore_drzwi+=2;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*5,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                               ktore_drzwi=a/8*2;a%=8;ktore_drzwi+=a/4; ktore_drzwi+=2;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*6,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                               }break;
                                                               case 3:{
                                                               ktore_drzwi=a/32*2;a%=32;ktore_drzwi+=a/16; a%=16; --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*5,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                               ktore_drzwi=a/8*2;a%=8;ktore_drzwi+=a/4; a%=4; --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*6,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                               ktore_drzwi=a/2*2;a%=2;ktore_drzwi+=a;  --ktore_drzwi;
                                                               al_draw_bitmap_region(g->krajobraz,g->X*ktore_drzwi,g->Y*7,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                               }break;
                                                               case 0:default:break;
                                                      }*/
                                            }
                                           else if(g->acc->otoczenie[w][v][0]>=3001 && g->acc->otoczenie[w][v][0]<3500)///sciana
                                             {
                                                      a=g->acc->otoczenie[w][v][0];
                                                      a-=3001;//a/=g->args->X_kratka;770
                                                      //std::cout<<a<<std::endl;
                                                      //std::cout<<ktore_drzwi<<std::endl;
                                                      //std::cout<<"XD"<<std::endl;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,g->Y*8,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      //std::cout<<g->X*(a/256)+ktore_drzwi*2*g->X;
                                            }
                                             else if(g->acc->otoczenie[w][v][0]>=3501 && g->acc->otoczenie[w][v][0]<3600)///krzeslo
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=3501;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,g->Y*11,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=3700 && g->acc->otoczenie[w][v][0]<3800)///stol
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=3700;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,g->Y*12,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=3800 && g->acc->otoczenie[w][v][0]<4100)///szafa
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=3800;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a/9*2+((a%9)/4)==1),g->Y*13,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      a%=9; a%=4;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(4+a),g->Y*3,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=4100 && g->acc->otoczenie[w][v][0]<4400)///lozko
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=4100;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*((a/4)*3+((a%4)>=2 ? 2 : (a%2))),g->Y*14,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=4400 && g->acc->otoczenie[w][v][0]<4500)///ukrycie pod
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=4400;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a,g->Y*15,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=4700 && g->acc->otoczenie[w][v][0]<4800)///reflektor
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=4700;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*((a>=8)*2+(a&1)),g->Y*17,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                                      if(a&4)
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(4+((a&2)!=2)),g->Y*17,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=4800 && g->acc->otoczenie[w][v][0]<4900)///beczka
                                             {

                                                      a=g->acc->otoczenie[w][v][0]; a-=4800;

                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(a),g->Y*18,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=4900 && g->acc->otoczenie[w][v][0]<5000)///beczka
                                             {

                                                      a=g->acc->otoczenie[w][v][0]; a-=4900;

                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*a, g->Y*19,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }
                                             else if(g->acc->otoczenie[w][v][0]>=5000 && g->acc->otoczenie[w][v][0]<5100)///lampa
                                             {
                                                      a=g->acc->otoczenie[w][v][0]; a-=5000;
                                                      al_draw_tinted_bitmap_region(g->krajobraz, al_map_rgba_f (C1,C2,C3,C4),g->X*(4+a), g->Y*11,g->X,g->Y, j*g->X+g->acc->przesuniecie[w][v].x-(g->args->X_kratka/2), i*g->Y+g->acc->przesuniecie[w][v].y-(g->args->Y_kratka/2),0);
                                             }


                                    }
                                    for(int v=0; v<23; v++)
                                    {
                                             i=w;j=v;
                                             int a=0;
                                             if(g->acc->otoczenie[w][v][1]>-1) //drzewo
                                             {
                                                      al_draw_tinted_bitmap_region(g->HP, al_map_rgba_f (C1,C2,C3,C4),0,0,g->X*g->acc->otoczenie[w][v][1]/100, g->Y, j*g->X-(g->args->X_kratka/2), i*g->Y-(g->args->Y_kratka/2),0);
                                             }
                                    }
                           }

                           for(short i=0;i<21;++i) for(short j=0;j<13;++j)
                           {
                                    C1 = args->plansza1->oswietlenie[j][i];
                                    if(args->wybuch[j][i])
                                    {
                                             short a = args->wybuch[j][i];
                                             //std::cout<<C1<<std::endl;
                                             //al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1>0.2 ? 0.2:C1,C1>0.2 ? 0.2:C1,C1>0.2 ? 0.2:C1, 1.0), args->X_kratka*((a-1)%12), args->Y_kratka*(7+a/13), args->X_kratka, args->Y_kratka,g->args->X_kratka*(i+0.5), g->args->Y_kratka*(j+0.5), 0);
                                             al_draw_tinted_bitmap_region(g->zjawiska, al_map_rgba_f (C1,C1,C1, 1),g->X*((a-1)%12),g->Y*(7+a/13),g->X,g->Y, i*g->X+(g->args->X_kratka/2), j*g->Y+(g->args->Y_kratka/2),0);
                                    }
                                    if(acc->oszolomiony[j][i])
                                    al_draw_bitmap_region(g->block,g->args->X_kratka*3,0,g->args->X_kratka, g->args->Y_kratka,g->args->X_kratka*(i+0.5)+g->acc->przesuniecie[j+1][i+1].x, g->args->Y_kratka*(j+0.5)+g->acc->przesuniecie[j+1][i+1].y,0);

                           }

                           bool u=true, b=true, s=true;
                           for(int i=0; i<20; ++i)
                           {
                                    //if(g->args->bloki[i].x==-1 && g->args->uniki[i].x==-1 && g->args->skupienia[i].x==-1) break;
                                    if(b && g->args->bloki[i].x!=-1) al_draw_bitmap_region(g->block,0,0,g->args->X_kratka, g->args->Y_kratka,
                                                                                           g->args->X_kratka*(g->args->bloki[i].x+0.5)+g->acc->przesuniecie[g->args->bloki[i].y+1][g->args->bloki[i].x+1].x,
                                                                                           g->args->Y_kratka*(g->args->bloki[i].y+0.5)+g->acc->przesuniecie[g->args->bloki[i].y+1][g->args->bloki[i].x+1].y,0);
                                    else b=false;
                                    if(u && g->args->uniki[i].x!=-1) al_draw_bitmap_region(g->block,g->args->X_kratka,0,g->args->X_kratka, g->args->Y_kratka,
                                                                                           g->args->X_kratka*(g->args->uniki[i].x+0.5)+g->acc->przesuniecie[g->args->uniki[i].y+1][g->args->uniki[i].x+1].x,
                                                                                           g->args->Y_kratka*(g->args->uniki[i].y+0.5)+g->acc->przesuniecie[g->args->uniki[i].y+1][g->args->uniki[i].x+1].y,0);
                                    else u=false;
                                    if(s && g->args->skupienia[i].x!=-1) al_draw_bitmap_region(g->block,g->args->X_kratka*2, 0,g->args->X_kratka, g->args->Y_kratka
                                                                                          ,g->args->X_kratka*(g->args->skupienia[i].x+0.5)+g->acc->przesuniecie[g->args->skupienia[i].y+1][g->args->skupienia[i].x+1].x
                                                                                          , g->args->Y_kratka*(g->args->skupienia[i].y+0.5)+g->acc->przesuniecie[g->args->skupienia[i].y+1][g->args->skupienia[i].x+1].y,0);
                                    else s=false;

                           }

                           for(int d=0; d<g->args->ilosc_zadan; ++d)
                           {
                                    int x=g->args->gdzie_obrazenia[d].x, y=g->args->gdzie_obrazenia[d].y, obr=g->args->obrazenia[d];if(obr<0) obr=0;
                                    if(obr<10) {x+=g->args->X_kratka/2-g->args->cyfry1_x/2;}
                                    else if(obr<100) {x+=g->args->X_kratka/2-g->args->cyfry1_x;}
                                    else if(obr<1000) {x+=g->args->X_kratka/2-g->args->cyfry1_x*1.5;}
                                    else {std::cout<<"nie wyswietlimy obrazen 1000+"<<'\n';continue;}
                                    y-=g->args->ile_nad;
                                    ostringstream ss;
                                    ss << obr;
                                    string str = ss.str();
                                    for(int b=0; b<str.length(); b++)
                                    {
                                             //std::cout<<g->args->cyfry1_x*(int)(str[b]-48)<<" "<<0<<" "<<g->args->cyfry1_x<<" "<<g->args->cyfry1_y<<" "<<x<<" "<<y<<std::endl;
                                             al_draw_bitmap_region(g->cyfry1, g->args->cyfry1_x*(int)(str[b]-48),0,g->args->cyfry1_x,g->args->cyfry1_y,x+(g->args->X_kratka/2),y+(g->args->Y_kratka/2),0);
                                             x+=g->args->cyfry1_x;
                                    }
                           }
                           if(g->args->iskra>0)
                           {
                                    al_draw_bitmap_region(g->zjawiska,g->args->X_kratka*(g->args->iskra-1),g->args->Y_kratka*6,g->args->X_kratka,g->args->Y_kratka,args->x_iskry,args->y_iskry,0);
                           }
                           if(g->args->rzucana_bron_id>0)
                           {
                                    dane_rysownicze a=g->jak_narysowac(g->args->rzucana_bron_id);
                                    ALLEGRO_BITMAP * ppp = al_create_bitmap(g->args->X_kratka,g->args->X_kratka);
                                    al_set_target_bitmap(ppp);
                                    al_draw_tinted_bitmap_region(a.a, al_map_rgba_f (C1,C2,C3,C4),a.x,a.y,g->args->X_kratka,g->args->Y_kratka,0,0,0);
                                    switch(l) {case 0:al_set_target_bitmap(g->plansza1);break;case 1:al_set_target_bitmap(g->plansza2);break;}

                                    al_draw_rotated_bitmap(ppp,g->args->X_kratka/2,g->args->Y_kratka/2,g->args->rzucana_bron_x,g->args->rzucana_bron_y,g->args->rzucana_bron_kat,0);
                                    al_destroy_bitmap(ppp);
                           }
                           if(g->args->prosta)
                           {
                                    al_draw_line(g->args->x1,g->args->y1,g->args->x2,g->args->y2,al_map_rgb(0,0,0),g->args->szerokosc);
                           }

                  }
         }

                  al_set_target_bitmap(g->bufor);
                  al_clear_to_color(al_map_rgb(0,0 ,0));
                  //al_draw_bitmap(g->podklad[0],0,0,0);


                  if(!g->args->przesuwamy_plansze) al_draw_bitmap(g->plansza1,0,0,0);
                  else
                  {
                           if(g->args->strona=='p')
                                    {
                                             al_draw_bitmap_region(g->plansza1,g->args->przesuniecie,0,22*g->args->X_kratka-g->args->przesuniecie,14*g->args->Y_kratka,0,0,0);
                                             al_draw_bitmap_region(g->plansza2,0,0,g->args->przesuniecie,14*g->args->Y_kratka,22*g->args->X_kratka-g->args->przesuniecie,0,0);
                                    }
                           else if(g->args->strona=='l')
                                    {
                                             al_draw_bitmap_region(g->plansza1,0,0,22*g->args->X_kratka-g->args->przesuniecie,14*g->args->Y_kratka,g->args->przesuniecie,0,0);
                                             al_draw_bitmap_region(g->plansza2,22*g->args->X_kratka-g->args->przesuniecie,0,g->args->przesuniecie,14*g->args->Y_kratka,0,0,0);
                                    }
                           else if(g->args->strona=='g')
                                    {
                                             al_draw_bitmap_region(g->plansza1,0,0,22*g->args->X_kratka,14*g->args->Y_kratka-g->args->przesuniecie,0,g->args->przesuniecie,0);
                                             al_draw_bitmap_region(g->plansza2,0,14*g->args->Y_kratka-g->args->przesuniecie,22*g->args->X_kratka,g->args->przesuniecie,0,0,0);
                                    }
                           else if(g->args->strona=='d')
                                    {
                                             al_draw_bitmap_region(g->plansza1,0,g->args->przesuniecie,22*g->args->X_kratka,14*g->args->Y_kratka-g->args->przesuniecie,0,0,0);
                                             al_draw_bitmap_region(g->plansza2,0,0,22*g->args->X_kratka,g->args->przesuniecie,0,14*g->args->Y_kratka-g->args->przesuniecie,0);
                                    }
                  }


         g->narysuj_roznego_rodzaju_mena();


                  if(!g->args->przesuwamy_plansze && !g->args->otwarty_ekwipunek)
                  {
                                    bool a=g->args->kroki,b=g->args->lewy_krok,c=g->args->prawy_krok,d=g->args->gora_krok,e=g->args->dol_krok;
                                    if(a)
                                    {
                                             if(b){al_draw_bitmap_region(g->avatar, 3*g->X, 3*g->Y, g->X,g->Y ,g->args->x1*g->X+(g->args->X_kratka/2), g->args->y1*g->Y+(g->args->Y_kratka/2),0);}
                                             if(c){al_draw_bitmap_region(g->avatar, 3*g->X, 3*g->Y, g->X,g->Y ,g->args->x2*g->X+(g->args->X_kratka/2), g->args->y2*g->Y+(g->args->Y_kratka/2),0);}
                                             if(d){al_draw_bitmap_region(g->avatar, 3*g->X, 3*g->Y, g->X,g->Y ,g->args->x3*g->X+(g->args->X_kratka/2), g->args->y3*g->Y+(g->args->Y_kratka/2),0);}
                                             if(e){al_draw_bitmap_region(g->avatar, 3*g->X, 3*g->Y,g-> X,g->Y ,g->args->x4*g->X+(g->args->X_kratka/2),g-> args->y4*g->Y+(g->args->Y_kratka/2),0);}
                                    }
                  }

                  g->narysuj_ekw_po_prawej();


                           g->narysuj_zegarek();

                           g->namaluj_paski();

                           g->draw_cross();

                           unsigned char ggg = args->nat_osw_alt != 0 ? args->nat_osw_alt : args->nat_osw;
                           unsigned char kkk = ggg>args->max_przyciemnienie_interfejsu-1 ? args->max_przyciemnienie_interfejsu : (ggg>0 ? ggg : 1);
                           unsigned char M1=kkk, M2=kkk, M3=kkk, M4=1.0;

                           for(int i=0;i<4;++i)
                           {
                                    int xowa=g->args->p_pozycja_x,yowa=g->args->p_pozycja_y+(g->args->p_poprawka+g->Y)*4+g->args->p_poprawka;
                                    switch(i)
                                    {
                                             case 0:xowa+=(g->args->p_poprawka+g->X)*2; yowa+=g->args->p_poprawka+g->Y; break;
                                             case 1:xowa+=g->args->p_poprawka+g->X; yowa+=(g->args->p_poprawka+g->Y)*2;break;
                                             case 2: yowa+=g->args->p_poprawka+g->Y;break;
                                             case 3:xowa+=g->args->p_poprawka+g->X; break;
                                    }
                                    al_draw_tinted_bitmap_region(g->way, al_map_rgba_f (M1,M2,M3,M4),g->X*i,g->Y*g->args->way[i],g->X,g->Y,xowa,yowa,0);
                           }
                           al_draw_tinted_bitmap_region(g->pogoda, al_map_rgba_f (M1,M2,M3,M4),0,g->Y*g->args->pogoda,g->X*3,g->Y,g->args->p_pozycja_x+g->args->p_poprawka,g->args->p_pozycja_y-g->args->p_poprawka-g->Y,0);

                           {
                                    int k=g->args->kondycja;
                                    for(int i=0;i<3;++i)
                                    {
                                             for(int j=0;j<2;++j)
                                             {
                                                      int maxx=0; if(j==0)switch(i){case 0: maxx=3;break;case 1: maxx=6;break;case 2: maxx=9;break;}
                                                      else if(j==1) switch(i){case 0: maxx=12;break;case 1: maxx=15;break;case 2: maxx=18;break;}
                                                      int a;if(k>=maxx)a=0;else if(k<maxx-2) a=3;else a=maxx-k;
                                                      al_draw_tinted_bitmap_region(g->kondycja_paski, al_map_rgba_f (M1,M2,M3,M4),g->X*a,0,g->X,g->Y,g->args->p_pozycja_x+i*(g->args->p_poprawka+g->X),g->args->p_pozycja_y-3*(g->args->p_poprawka+g->Y)+j*(g->args->p_poprawka+g->Y)+3*g->args->p_poprawka,0);
                                             }
                                    }
                           }


                           if(g->args->menu)
                           {
                                    ALLEGRO_BITMAP * do_wyswietlenia=g->ktore_menu();

                                    if(do_wyswietlenia==NULL){std::cout<<(int)g->args->ktore_menu<< " Menu jest NULL"; throw "Grafika, wyswietlanie menu, niewlasciwe menu";}
                                    al_set_target_bitmap(g->bufor);
                                    al_draw_bitmap(do_wyswietlenia, g->args->wmx, g->args->wmy, 0);

                                    if(g->args->submenu)
                                    {

                                             do_wyswietlenia=g->ktore_submenu();

                                             if(do_wyswietlenia==NULL) {std::cout<<(int)g->args->ktore_sub_menu<< " SubMenu jest NULL";throw "G";}
                                             al_set_target_bitmap(g->bufor);
                                             al_draw_bitmap(do_wyswietlenia, g->args->wsmx, g->args->wsmy, 0);
                                    }
                           }


                           if(g->args->p_nr_przedmiotu!=0)
                           {
                                    g->namaluj_rzecz(g->bufor, g->args->p_nr_przedmiotu, g->args->p_x, g->args->p_y,0,true);
                           }

                    if(g->args->wiadomosc==1)
                            al_draw_bitmap_region(g->message[0], 0, 0, g->X*6, g->Y*4, g->X*9, g->Y*5, 0);



                  al_set_target_bitmap(al_get_backbuffer(g->display));

                          al_draw_bitmap(g->bufor,0,0,0);

                           if(g->args->screen)
                                    {
                                             g->args->screen=false;
                                             al_save_bitmap("ekran.bmp",g->bufor);
                                    }
                           al_flip_display();


         }









