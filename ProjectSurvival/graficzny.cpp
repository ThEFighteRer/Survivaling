#include "grafika.h"








void graficzny::rysuj_crafting(ALLEGRO_BITMAP *target)
{
         //std::cout<<args->co_ma[2].substraty[1]<<std::endl;
         al_draw_bitmap_region(crafting_tlo, 0,0,X*22,Y*14, 0, 0,0);///tlo

         ALLEGRO_COLOR c= al_map_rgb(0,0,0);///linie schematowe tla
         al_draw_line(X, Y, X*21,Y,c,1);
         al_draw_line(X, Y*2, X*21,Y*2,c,1);
         al_draw_line(X, Y*13, X*22,Y*13,c,1);
         al_draw_line(X, Y*14, X*22,Y*14,c,1);
         al_draw_line(X, Y, X ,Y*14,c,1);
         al_draw_line(X*22, Y, X*22,Y*14,c,1);
         al_draw_line(X*23-2, Y, X*23-2,Y*14,c,1);

         al_draw_bitmap_region(crafting_el,X*args->da_sie_strone_w_lewo_w_craftingu,0,X,Y,15*X,13*Y,0);///strzalki
         al_draw_bitmap_region(crafting_el,2*X+X*args->da_sie_strone_w_prawo_w_craftingu,0,X,Y,20*X,13*Y,0);

         for(short h=0; h<1; ++h)///ktora kategoria i strona
                  al_draw_bitmap_region(crafting_el,X*h,Y,X,Y,(h+1)*X,13*Y,0);
         al_draw_bitmap_region(crafting_el,4*X,0,X,Y,(args->ktora_kategoria+1)*X,13*Y,0);
         narysuj_duze_cyfry(17.7*X, 13*Y, args->ktora_strona);

         rozmiary_tabeli rozmiary = args->rozmiary;
         short x = X, y;

         const Przepis*przepis = args->przepis;

         short *wsp_r = args->wsp_r;
         std::shared_ptr<co_ma_gracz> co_ma = args->co_ma;

         if(co_ma.get()==NULL || wsp_r==NULL || przepis==NULL) return;///sprawdzanie poprawnosci wskaznikow
         for(short i=0;1;++i)
                  if(przepis[i].ilosc_substratow==-1 || co_ma.get()[i].ilosc_substratow==-1)
                  {
                           //std::cout<<przepis[i].ilosc_substratow<<" "<<co_ma[i].ilosc_substratow<<std::endl;
                           if(przepis[i].ilosc_substratow!=-1 || co_ma.get()[i].ilosc_substratow!=-1) return;
                           break;
                  }

         y=0;
         while(wsp_r[y]!=-1)///przyciski craft
         {
                  ///std::cout<<wsp_r[y]+0.25*Y<<std::endl;
                  short pop = wsp_r[y+1]==-1 ? 12*Y : wsp_r[y+1];
                  pop = pop-wsp_r[y]; pop-=Y/2; pop/=2;
                  short yyy = wsp_r[y]+pop - 0.5*Y;
                  if(przepis[y].ilosc_substratow!=-1)
                  {
                           al_draw_bitmap_region(crafting_el,0,Y*2,X*2,Y,20*X,yyy,0);
                          al_draw_line(X,wsp_r[y]-0.25*Y,22*X,wsp_r[y]-0.25*Y,c,1);

                           graficzny *g = this;
                           yyy = yyy + (Y-g->wysokosc_cyfr_0r)/2;
                           short p = przepis[y].koszt;
                           if(p<10)
                           al_draw_bitmap_region(g->r_liczby, g->szerokosc_cyfr_0r*p,0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,19*X+X/3,yyy,0);
                           else if(p<100)
                           {al_draw_bitmap_region(g->r_liczby, g->szerokosc_cyfr_0r*(p/10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,19*X+X/6,yyy,0);
                           al_draw_bitmap_region(g->r_liczby, g->szerokosc_cyfr_0r*(p%10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,19*X+g->szerokosc_cyfr_0r+X/6,yyy,0);}
                           else if(p<1000)
                           {al_draw_bitmap_region(g->r_liczby, g->szerokosc_cyfr_0r*(p/100),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,19*X,yyy,0);
                           al_draw_bitmap_region(g->r_liczby, g->szerokosc_cyfr_0r*((p%100)/10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,19*X+g->szerokosc_cyfr_0r,yyy,0);
                           al_draw_bitmap_region(g->r_liczby, g->szerokosc_cyfr_0r*(p%10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,19*X+g->szerokosc_cyfr_0r*2,yyy,0);}
                  }
                  ++y;
         }

         for(y=0; przepis[y].ilosc_substratow!=-1; ++y)///rysowanie itemow
         {
                  ///rysuj_atrybut_tabeli_craftingu(0, jaki_wiersz, przepis[y], co_ma[y], rozmiary);
                  for(short  t=0;t<5;++t)
                    {
                            //std::cout<<t;
                            rysuj_atrybut_tabeli_craftingu(t, wsp_r[y], przepis[y], co_ma.get()+y, rozmiary);
                            //std::cout<<t; if(args->co_ma[2].substraty[1]==false) {throw "D";}
                    }
         }

         if(rozmiary.I>0)///napisy i linie pionowe
         {
                  y = x+ 1.5*X*rozmiary.I+X*0.5;

                  al_draw_bitmap_region(crafting_napisy,0,0,X*2,Y,x+(y-x-X*2)/2,1*Y,0);
                  x = y; al_draw_line(x, Y*2, x,Y*13,c,1);
         }
         if(rozmiary.II>0)
         {
                  y = x+1.5*X*rozmiary.II+0.5*X;
                  al_draw_bitmap_region(crafting_napisy,0,Y,X*2,Y,x+(y-x-X*2)/2,1*Y,0);
                   x=y; al_draw_line(x, Y*2, x,Y*13,c,1);
         }
         if(rozmiary.III>0)
         {
                  y = x+ 1.5*X*rozmiary.III+0.5*X;
                  al_draw_bitmap_region(crafting_napisy,0,Y*2,X*2,Y,x+(y-x-X*2)/2,1*Y,0);
                  x=y; al_draw_line(x, Y*2, x,Y*13,c,1);
         }
         if(rozmiary.IV)
         {
                   y = x + 1.5*X*rozmiary.IV + 0.5*X;
                  al_draw_bitmap_region(crafting_napisy,0,Y*3,X*2,Y,x+(y-x-X*2)/2,1*Y,0);
                   x=y; al_draw_line(x, Y*2, x,Y*13,c,1);
         }
         y = 19*X; al_draw_bitmap_region(crafting_napisy,0,Y*4,X*2,Y,x+(y-x-X*2)/2,1*Y,0);
         x=y; al_draw_line(x, Y*2, x,Y*13,c,1);

}

void graficzny::rysuj_atrybut_tabeli_craftingu(short ktora, short jaki_wiersz, Przepis przepis, co_ma_gracz *co_ma_g, rozmiary_tabeli rozmiary)///ktora od 0 do 4
{
         void (graficzny::*rysujaca)(int, int, int);
         short ilosc_sub = 0; short kraw = X; ///krawedz po lewej
         short rozm = 0; int *subs; bool *co_ma;
         short x1 = X, x2 = x1+(rozmiary.I==1 ? X*1.5 : X*1.5*rozmiary.I) + 0.5*X*(rozmiary.I>0),
         x3 = x2 + (rozmiary.II==1 ? X*1.5 : X*1.5*rozmiary.II) + 0.5*X*(rozmiary.II>0), x4 = x3 + (rozmiary.III==1 ? X*1.5 : X*1.5*rozmiary.III) +0.5*X*(rozmiary.III>0),
          x5 = x4 + (rozmiary.IV==1 ? X*1.5 : X*1.5*rozmiary.IV) + 0.5*X*(rozmiary.IV>0);
         switch(ktora)
         {
         case 0:
                  ilosc_sub = przepis.ilosc_substratow; kraw = x1; rozm = rozmiary.I; rysujaca = &narysuj_miniature_rzeczy; subs = przepis.substraty; co_ma = co_ma_g->substraty;
                  break;
         case 1:
                  ilosc_sub = przepis.ilosc_objektow_w_poblizu; kraw = x2; rozm = rozmiary.II; rysujaca = &narysuj_miniature_rzeczy/*narysuj_warsztat*/; subs = przepis.objekty_w_poblizu; co_ma = co_ma_g->objekty_w_poblizu;
                  break;
         case 2:
                  ilosc_sub = przepis.ilosc_katalizatorow; kraw =  x3; rozm = rozmiary.III; rysujaca = &narysuj_miniature_rzeczy; subs = przepis.katalizatory; co_ma = co_ma_g->katalizatory;
                  break;
         case 3:
                  ilosc_sub = przepis.ilosc_umiejetnosci; kraw = x4; rozm = rozmiary.IV; rysujaca = &narysuj_miniature_rzeczy/*narysuj_umiejetnosc*/; subs = przepis.skills; co_ma = co_ma_g->skills;
                  break;
         case 4:
                  ilosc_sub = przepis.ilosc_rezultatow; kraw = x5; rozm = rozmiary.V; rysujaca = &narysuj_miniature_rzeczy; subs = przepis.rezultaty;
                  break;
         }

         if(ilosc_sub>0)
         {
                  if(rozm<1) {return;}
                  short licznik = 0;

                  while(ilosc_sub-licznik>=rozm)
                  {
                           for(short f=0; f<rozm; ++f)
                           {
                                    int o_itemie = subs[licznik+f];
                                    short nr = ((short*)&o_itemie)[0];
                                    short ile = ((short*)&o_itemie)[1];

                                    short y_pop = (przepis.potrzebne_wiersze(rozmiary)-przepis.potrzebne_wiersze_na_atrybut(rozmiary, ktora))*Y/2;
                                    short wsp_x = (ktora==4)*X/4-2 + kraw+f*X*1.5 + 0.5* X + (ile>1)*0.5*X - 2*(f<rozm-1), wsp_y = jaki_wiersz+(licznik/rozm)*Y +2*(f>licznik>=rozm)+y_pop;

                                    if(ktora!=4)
                                    {bool gracz_go_ma = co_ma[licznik+f];
                                    al_draw_bitmap_region(crafting_el, 2*X+X*!gracz_go_ma, 2*Y,  X, Y, wsp_x, wsp_y, 0);}

                                    (this->*rysujaca)(nr, wsp_x, wsp_y);
                                    if(ile>1) narysuj_cyfry_takie_czarne_z_x(wsp_x - 0.5*X, wsp_y,ile);
                           }
                                    ///ukladanie rowno
                           licznik+=rozm;
                  }
                  if(licznik <= ilosc_sub-1)
                  {
                           short przes = ((rozm - (ilosc_sub - licznik))*X*1.5)/2;
                           for(short f=licznik; f<ilosc_sub; ++f)
                           {
                                    int o_itemie = subs[f];
                                    short nr = ((short*)&o_itemie)[0];
                                    short ile = ((short*)&o_itemie)[1];
                                    short y_pop = (przepis.potrzebne_wiersze(rozmiary)-przepis.potrzebne_wiersze_na_atrybut(rozmiary, ktora))*Y/2;
                                    short wsp_x = (ktora==4)*X/4 -2 + przes+kraw+(f%rozm)*X*1.5 + 0.5*X + (ile>1)*0.5*X- 2*(licznik<ilosc_sub-1), wsp_y = jaki_wiersz+(licznik/rozm)*Y +2+y_pop;

                                    if(ktora!=4)
                                    {bool gracz_go_ma = co_ma[f];
                                    al_draw_bitmap_region(crafting_el, 2*X+X*!gracz_go_ma, 2*Y,  X, Y, wsp_x, wsp_y, 0);}

                                    (this->*rysujaca)(nr,wsp_x , wsp_y);
                                    if(ile>1) narysuj_cyfry_takie_czarne_z_x(wsp_x-X/2, wsp_y, ile);
                           }
                  }
         }
}

void graficzny::narysuj_cyfry_takie_czarne_z_x(int x, int y, short p) ///wsp kratki
{
         graficzny*g=this;
         short yyy = y + (Y-wysokosc_cyfr_0r)/2;
         if(p<10)
         {al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*p,0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x+X/6,yyy,0);
                  al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*10,0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x+X/6+g->szerokosc_cyfr_0r,yyy,0);}
         else if(p<100)
         {al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*(p/10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x,yyy,0);
         al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*(p%10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x+g->szerokosc_cyfr_0r,yyy,0);
         al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*10,0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x+g->szerokosc_cyfr_0r*2,yyy,0);}
         else if(p<1000)
         {al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*(p/100),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x-X/6,yyy,0);
         al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*((p%100)/10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x-X/6+g->szerokosc_cyfr_0r,yyy,0);
         al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*(p%10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x-X/6+g->szerokosc_cyfr_0r*2,yyy,0);
         al_draw_bitmap_region(g->rr_liczby, g->szerokosc_cyfr_0r*10,0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,x-X/6+g->szerokosc_cyfr_0r*3,yyy,0);}
}

void graficzny::narysuj_warsztat(int nr, int x, int y)
{

}

void graficzny::narysuj_umiejetnosc(int nr, int x, int y)
{

}

void graficzny::narysuj_miniature_rzeczy(int nr, int x, int y)
{
         dane_rysownicze a = jak_narysowac(nr);
         al_draw_bitmap_region(a.a, a.x, a.y, X, Y, x, y, 0);
}

void graficzny::narysuj_ekw_po_prawej()
{
         unsigned char ggg = args->nat_osw_alt != 0 ? args->nat_osw_alt : args->nat_osw;
         unsigned char kkk = ggg>args->max_przyciemnienie_interfejsu-1 ? args->max_przyciemnienie_interfejsu : (ggg>0 ? ggg : 1);
         graficzny*g = this;
         ALLEGRO_BITMAP* co=NULL;
         int x_zrodl, y_zrodl, x_dom, y_dom, val;
         for(int i=0; i<10; ++i)
         {
                  switch(i)
                  {
                           case 0: val=g->args->p_ramie;break;
                           case 1: val=g->args->p_glowa;break;
                           case 2: val=g->args->p_plecak;break;
                           case 3: val=g->args->p_rece;break;
                           case 4: val=g->args->p_korpus;break;
                           case 5: val=g->args->p_rekawice;break;
                           case 6: val=g->args->p_kieszenl;break;
                           case 7: val=g->args->p_spodnie;break;
                           case 8: val=g->args->p_kieszenp;break;
                           case 9: val=g->args->p_buty;break;
                  }
                  if(val<0) continue;
                  else if(val==0)
                  {
                           co=g->equ; x_zrodl=(i%5)*g->args->X_kratka; y_zrodl=(i/5)*g->args->Y_kratka;
                  }
                  else
                  {
                           dane_rysownicze a=g->jak_narysowac(val);
                           x_zrodl=a.x;y_zrodl=a.y;co=a.a;
                  }
                  if(i==9)
                  {
                           x_dom=g->args->p_pozycja_x+g->args->p_poprawka+g->args->X_kratka;
                           y_dom=g->args->p_pozycja_y+3*g->args->Y_kratka+3*g->args->p_poprawka;
                  }
                  else
                  {
                           x_dom=g->args->p_pozycja_x+(g->args->p_poprawka+g->args->X_kratka)*(i%3);
                           y_dom=g->args->p_pozycja_y+(g->args->Y_kratka+3*g->args->p_poprawka)*(i/3);
                  }
                  al_draw_tinted_bitmap_region(co, al_map_rgba_f (kkk,kkk,kkk,1.0), x_zrodl, y_zrodl, g->args->X_kratka,  g->args->Y_kratka, x_dom, y_dom, 0);
         }
}

graficzny::graficzny(struct dla_grafiki *argumenty)
{
                  args = argumenty;
                  X=args->X_kratka,Y=args->Y_kratka;
                  graficzny *g = this;

                  display = al_create_display(args->rozdz_X, args->rozdz_Y);

                  int menu_x=150*args->rozdz_X/1920,menu_y=50*args->rozdz_Y/1080;
                  args->menu_x=menu_x; args->menu_y=menu_y;
                  ALLEGRO_BITMAP *pom;

                  pom = al_load_bitmap("img/interface/postac1.bmp"); mp=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/postacobrocsie.bmp"); mp1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/postacpostawa.bmp"); mp2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/postacodglos.bmp"); mp3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_plecak.bmp"); menu_p=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_skrzynka.bmp"); menu_s=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_ziemia.bmp"); menu_ziemia=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/menuplecak.bmp"); menu_plecak=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menuramie.bmp"); menu_ramie=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menugracz.bmp"); menu_ubranie=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menurece.bmp"); menu_rece=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menukieszen.bmp"); menu_kieszen=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menuplecak2.bmp"); menu_plecak_s=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/menu_walka1_1.bmp"); menu_walka1_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka1_2.bmp"); menu_walka1_2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka1_3.bmp"); menu_walka1_3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka1_4.bmp"); menu_walka1_4=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka1.bmp"); menu_walka1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka11.bmp"); menu_walka11=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka12.bmp"); menu_walka12=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka13.bmp"); menu_walka13=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka14.bmp"); menu_walka14=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/menu_walka2.bmp"); menu_walka2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka21.bmp"); menu_walka21=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka22.bmp"); menu_walka22=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka2_1.bmp"); menu_walka2_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka2_2.bmp"); menu_walka2_2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka3.bmp"); menu_walka3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka4.bmp"); menu_walka4=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/podnies.bmp"); menu_pust_plecak=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/schowek_menu.bmp"); menu_schowek=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_drzewo.bmp"); menu_drzewo=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_ognisko1.bmp"); menu_ognisko=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/strzelanie_menu1.bmp"); strzelanie_menu1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu1_1.bmp"); strzelanie_menu1_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu1_2.bmp"); strzelanie_menu1_2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu1_3.bmp"); strzelanie_menu1_3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu1_4.bmp"); strzelanie_menu1_4=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu2.bmp"); strzelanie_menu2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu2_1.bmp"); strzelanie_menu2_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu2_2.bmp"); strzelanie_menu2_2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu3.bmp"); strzelanie_menu3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu3_1.bmp"); strzelanie_menu3_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu11.bmp"); strzelanie_menu11=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/strzelanie_menu12.bmp"); strzelanie_menu12=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka_lezacy.bmp"); menu_walka_lezacy=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka_lezacy_1.bmp"); menu_walka_lezacy_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_walka_lezacy_2.bmp"); menu_walka_lezacy_2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_ataku_zwierzeta.bmp"); menu_ataku_zwiarzeta=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_strzelanie_zwierzeta.bmp"); menu_strzelanie_zwierzeta=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/menu_okno1.bmp"); menu_okno1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_okno2.bmp"); menu_okno2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_okno3.bmp"); menu_okno3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_okno4.bmp"); menu_okno4=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_okno5.bmp"); menu_okno5=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/zniszcz.bmp"); zniszcz=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/zniszcz_.bmp"); zniszcz_=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_drzwi1.bmp"); menu_drzwi1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_drzwi2.bmp"); menu_drzwi2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_drzwi3.bmp"); menu_drzwi3=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/submenu_przemiesc.bmp"); submenu_przemieszcz=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/uniwersalne_menu.bmp"); uniwersalne_menu=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/stol_sub_1.bmp"); stol_sub_1=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/stol_sub_2.bmp"); stol_sub_2=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/menu_strony.bmp"); menu_strony=wyskaluj_menu(pom,menu_x,menu_y);
                  pom = al_load_bitmap("img/interface/beczka_sub.bmp"); beczka_sub=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/menu_szalas.bmp"); menu_szalasu=wyskaluj_menu(pom,menu_x,menu_y);

                  pom = al_load_bitmap("img/interface/kursor_aim.bmp"); al_convert_mask_to_alpha( pom, al_map_rgb(255,0,255));
                  kursor_aim=al_create_bitmap(X/2, Y/2); al_set_target_bitmap(kursor_aim); al_draw_scaled_bitmap(pom, 0, 0, 35, 35, 0, 0, X/2, Y/2, 0);
                  al_destroy_bitmap(pom);

                  ///ALLEGRO_BITMAP *avatar[5], *drzewa[5], *el_stale[5];

                  pom = al_load_bitmap("img/mapa/zjawiska.bmp");
                  zjawiska=wyskaluj(pom,X,Y); al_convert_mask_to_alpha( zjawiska, al_map_rgb(255,0,255)); al_destroy_bitmap(pom);
                  avatar = new ALLEGRO_BITMAP*[5];
                  drzewa = new ALLEGRO_BITMAP*[5];
                  el_stale = new ALLEGRO_BITMAP*[5];

                  for(int i=0; i<5; i++)
                  {
                           ALLEGRO_BITMAP *avatar_ob, *drzewa_ob, *el_stale_ob;
                           switch(i)
                           {
                                    case 0:
                                             {
                                                      avatar_ob=al_load_bitmap("img/avatar/avatar1.bmp");
                                                      drzewa_ob=al_load_bitmap("img/mapa/naturalne/drzewa1.bmp");
                                                      el_stale_ob=al_load_bitmap("img/rzeczy/wolnostojace/el_stale1.bmp");
                                             break;}
                                    case 1:
                                             {
                                                      avatar_ob=al_load_bitmap("img/avatar/avatar2.bmp");
                                                      drzewa_ob=al_load_bitmap("img/mapa/naturalne/drzewa2.bmp");
                                                      el_stale_ob=al_load_bitmap("img/rzeczy/wolnostojace/el_stale2.bmp");
                                             break;}
                                    case 2:
                                              {
                                                       avatar_ob=al_load_bitmap("img/avatar/avatar3.bmp");
                                                       drzewa_ob=al_load_bitmap("img/mapa/naturalne/drzewa3.bmp");
                                                       el_stale_ob=al_load_bitmap("img/rzeczy/wolnostojace/el_stale3.bmp");
                                              break;}
                                    case 3:
                                              {
                                                       avatar_ob=al_load_bitmap("img/avatar/avatar4.bmp");
                                                       drzewa_ob=al_load_bitmap("img/mapa/naturalne/drzewa4.bmp");
                                                       el_stale_ob=al_load_bitmap("img/rzeczy/wolnostojace/el_stale4.bmp");
                                              break;}
                                    case 4:
                                             {
                                                      avatar_ob=al_load_bitmap("img/avatar/avatar5.bmp");
                                                      drzewa_ob=al_load_bitmap("img/mapa/naturalne/drzewa5.bmp");
                                                      el_stale_ob=al_load_bitmap("img/rzeczy/wolnostojace/el_stale5.bmp");
                                             break;}
                           }
                           avatar[i]=wyskaluj(avatar_ob,X,Y); al_convert_mask_to_alpha( avatar[i], al_map_rgb(255,0,255));al_destroy_bitmap(avatar_ob);
                           drzewa[i]=wyskaluj(drzewa_ob,X,Y); al_convert_mask_to_alpha( drzewa[i], al_map_rgb(255,0,255)); al_destroy_bitmap(drzewa_ob);
                           el_stale[i]=wyskaluj(el_stale_ob,X,Y); al_convert_mask_to_alpha( el_stale[i], al_map_rgb(255,0,255)); al_destroy_bitmap(el_stale_ob);
                  }
                  //int ilosc_tekstur=1;

                  pom= al_load_bitmap("img/wrogowie/zombie.bmp");
                  zombie = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(zombie, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/equ.bmp");
                  equ = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(equ, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/zwierzeta/zwierzeta.bmp");
                  zwierzeta = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(zwierzeta, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/crafting_el.bmp");
                  crafting_el = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(crafting_el, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/crafting_napisy.bmp");
                  crafting_napisy = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(crafting_napisy, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/mapa/elementy_krajobrazu.bmp");
                  krajobraz = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(krajobraz, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/wys.bmp");
                  wys = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(wys, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/crafting_tlo.bmp");
                  crafting_tlo = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(crafting_tlo, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/equip.bmp");equip = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(equip, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/equ_pasek.bmp");equ_pasek = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(equ_pasek, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/rzeczy/bron.bmp");equ_bron = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(equ_bron, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/interface/strony.bmp");way = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(way, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/interface/int_pogody.bmp");pogoda = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(pogoda, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/interface/spanie_menu.bmp");menu_spania = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(menu_spania, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/interface/kondycja_paski.bmp");kondycja_paski = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(kondycja_paski, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/interface/ubranie_info.bmp");ubranie_info = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(ubranie_info, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/interface/bron_info.bmp");bron_info = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(bron_info, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/equ_akcesoria.bmp");
                  equ_akcesoria = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(equ_akcesoria, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/rzeczy/rzeczy.bmp");rzeczy = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(rzeczy, al_map_rgb(255,0,255));
                  pom= al_load_bitmap("img/mapa/zamkniecia.bmp");klodki = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(klodki, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/HP.bmp");HP = wyskaluj(pom, X,Y);al_destroy_bitmap(pom);al_convert_mask_to_alpha(HP, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/wrogowie/block.bmp");
                  block = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(block, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/anatomia.bmp");
                  anatomia = wyskaluj(pom, X,Y);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(anatomia, al_map_rgb(255,0,255));

                  args->cyfry1_x=15*args->rozdz_X/1920; args->cyfry1_y=20*args->rozdz_Y/1080;
                  pom= al_load_bitmap("img/interface/cyfry1.bmp");
                  cyfry1 = al_create_bitmap(args->cyfry1_x*10,args->cyfry1_y);
                  al_set_target_bitmap(cyfry1); al_draw_scaled_bitmap(pom,0,0,150,20,0,0,args->cyfry1_x*10,args->cyfry1_y,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(cyfry1, al_map_rgb(255,0,255));

                  args->cyfry_duze_x=52*args->rozdz_X/1920; args->cyfry_duze_y=75*args->rozdz_Y/1080;
                  pom= al_load_bitmap("img/interface/cyfry_duze.bmp");
                  cyfry_duze = al_create_bitmap(args->cyfry_duze_x*11,args->cyfry_duze_y);
                  al_set_target_bitmap(cyfry_duze); al_draw_scaled_bitmap(pom,0,0,572,75,0,0,args->cyfry_duze_x*11,args->cyfry_duze_y,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(cyfry_duze, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/pasek_zycia.bmp");
                  pasek_anatomii = al_create_bitmap(args->X_kratka*2,args->Y_kratka*2/3);
                  al_set_target_bitmap(pasek_anatomii); al_draw_scaled_bitmap(pom,0,0,150,50,0,0,args->X_kratka*2,args->Y_kratka*2/3,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(pasek_anatomii, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/czczionka_paski.bmp");
                  czczionka_paski = al_create_bitmap(args->rozdz_X*220/1920,args->rozdz_Y*26/1080);
                  al_set_target_bitmap(czczionka_paski); al_draw_scaled_bitmap(pom,0,0,220,26,0,0,args->rozdz_X*220/1920,args->rozdz_Y*26/1080,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(czczionka_paski, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/pasekogolny.bmp");
                  pasek_ogolny = al_create_bitmap(args->rozdz_X*250/1920,args->rozdz_Y*30/1080);
                  al_set_target_bitmap(pasek_ogolny); al_draw_scaled_bitmap(pom,0,0,250,30,0,0,args->rozdz_X*250/1920,args->rozdz_Y*30/1080,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(pasek_ogolny, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/napisy.bmp");
                  napisy = al_create_bitmap(args->rozdz_X*125/1920,args->rozdz_Y*120/1080);
                  al_set_target_bitmap(napisy); al_draw_scaled_bitmap(pom,0,0,125,120,0,0,args->rozdz_X*125/1920,args->rozdz_Y*120/1080,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(napisy, al_map_rgb(255,0,255));

                  pom= al_load_bitmap("img/interface/pasek_uzytkowy.bmp");
                  pasek_uzytkowy = al_create_bitmap(args->rozdz_X*244/1920,args->rozdz_Y*30/1080);
                  al_set_target_bitmap(pasek_uzytkowy); al_draw_scaled_bitmap(pom,0,0,244,30,0,0,args->rozdz_X*244/1920,args->rozdz_Y*30/1080,0);
                  al_destroy_bitmap(pom);
                  al_convert_mask_to_alpha(pasek_uzytkowy, al_map_rgb(255,0,255));

                  g->szerokosc_cyfr_0=30*args->rozdz_X/1920, g->wysokosc_cyfr_0=60*args->rozdz_Y/1080
                  ,g->szerokosc_cyfr_0r=25*args->rozdz_X/1920, g->wysokosc_cyfr_0r=50*args->rozdz_Y/1080,
                  g->szerokosc_zegarka=260*args->rozdz_X/1920, g->wysokosc_zegarka=150*args->rozdz_Y/1080;
                  zegarek=al_create_bitmap(g->szerokosc_zegarka, g->wysokosc_zegarka);
                  zegarek_=al_create_bitmap(g->szerokosc_zegarka, g->wysokosc_zegarka);
                  r_liczby=al_create_bitmap(g->szerokosc_cyfr_0r*10, g->wysokosc_cyfr_0r);
                  rr_liczby=al_create_bitmap(g->szerokosc_cyfr_0r*11, g->wysokosc_cyfr_0r);
                  _liczby=al_create_bitmap(g->szerokosc_cyfr_0*10, g->wysokosc_cyfr_0);
                  pom=al_load_bitmap("img/interface/0.bmp"); al_set_target_bitmap(_liczby);
                  al_draw_scaled_bitmap(pom, 0,0,300,60,0,0,g->szerokosc_cyfr_0*10, g->wysokosc_cyfr_0,0);
                  al_destroy_bitmap(pom);al_convert_mask_to_alpha(_liczby, al_map_rgb(255,0,255));
                  pom=al_load_bitmap("img/interface/0r.bmp"); al_set_target_bitmap(r_liczby);
                  al_draw_scaled_bitmap(pom, 0,0,250,50,0,0,g->szerokosc_cyfr_0r*10, g->wysokosc_cyfr_0r,0);
                  al_destroy_bitmap(pom);al_convert_mask_to_alpha(r_liczby, al_map_rgb(255,0,255));
                   pom=al_load_bitmap("img/interface/0rr.bmp"); al_set_target_bitmap(rr_liczby);
                  al_draw_scaled_bitmap(pom, 0,0,275,50,0,0,g->szerokosc_cyfr_0r*11, g->wysokosc_cyfr_0r,0);
                  al_destroy_bitmap(pom);al_convert_mask_to_alpha(rr_liczby, al_map_rgb(255,0,255));
                  pom=al_load_bitmap("img/interface/zegarek.bmp"); al_set_target_bitmap(zegarek);
                  al_draw_scaled_bitmap(pom, 0,0,260,150,0,0,g->szerokosc_zegarka, g->wysokosc_zegarka,0);
                  al_destroy_bitmap(pom);al_convert_mask_to_alpha(zegarek, al_map_rgb(255,0,255));
                  pom=al_load_bitmap("img/interface/zegarek_.bmp"); al_set_target_bitmap(zegarek_);
                  al_draw_scaled_bitmap(pom, 0,0,260,150,0,0,g->szerokosc_zegarka, g->wysokosc_zegarka,0);
                  al_destroy_bitmap(pom);al_convert_mask_to_alpha(zegarek_, al_map_rgb(255,0,255));
                  g->h_1=(g->szerokosc_zegarka-4)/2-g->szerokosc_cyfr_0*2; g->h_2=g->h_1+g->szerokosc_cyfr_0;
                  g->h_3=g->h_2+g->szerokosc_cyfr_0+4;g->h_4=g->h_3+g->szerokosc_cyfr_0;
                  g->h_y=20*g->wysokosc_zegarka/150;
                  g->p_1=g->szerokosc_zegarka/2-1.5*g->szerokosc_cyfr_0r;g->p_y=90*g->wysokosc_zegarka/150;
                  g->pozycja_zegarka_x=(args->rozdz_X-22*args->X_kratka-g->szerokosc_zegarka)/2+22*args->X_kratka;
                  g->pozycja_zegarka_y=0;

                  tlo =new ALLEGRO_BITMAP*[2];
                  tlo[0] =al_load_bitmap("img/mapa/plansza_laka.bmp");
                  tlo[1] =al_load_bitmap("img/mapa/bruk.bmp");
                  for(int i=0; i<2; i++)
                  {
                           ALLEGRO_BITMAP * pom = al_create_bitmap(X*22, Y*14);
                           al_set_target_bitmap(pom);
                           al_draw_scaled_bitmap(tlo[i], 0, 0,  1650, 1050, 0, 0, X*22, Y*14, 0);
                           al_destroy_bitmap(tlo[i]);
                           tlo[i]=pom;
                  }

                  message = new ALLEGRO_BITMAP*[1];
                  message[0] = al_load_bitmap("img/messages/messageniedasie.bmp");

                  podklad=new ALLEGRO_BITMAP*[1];
                  podklad[0] =al_load_bitmap("img/tlo/czarne.bmp");
                  for(int i=0; i<1; i++)
                  {
                                    pom = al_create_bitmap(args->rozdz_X, args->rozdz_Y);
                                    al_set_target_bitmap(pom);
                                    al_draw_scaled_bitmap(podklad[i], 0, 0,  1920, 1080 , 0, 0, args->rozdz_X, args->rozdz_Y, 0);
                                    al_destroy_bitmap(podklad[i]);
                                    podklad[i]=pom;
                  }

                  plansza_1=args->plansza1; plansza_2=args->plansza2;
                  plansza1=al_create_bitmap(args->X_kratka*22,args->Y_kratka*14),plansza2=al_create_bitmap(args->X_kratka*22,args->Y_kratka*14);
                  bufor=al_create_bitmap(args->rozdz_X, args->rozdz_Y);


                  g->eq1 = al_create_bitmap(args->X_kratka*9,args->Y_kratka*11);
                  g->eq2 = al_create_bitmap(args->X_kratka*9,args->Y_kratka*11);

}

void graficzny::rysuj_ekwipunek()
{
         graficzny*g = this;
         al_draw_bitmap(g->equip, 0,0,0);

         al_set_target_bitmap(g->eq1);
         al_clear_to_color(al_map_rgb(255,255,255));

         std::pair<std::vector<std::pair<int, punkt>>, std::pair<int, int>> prawa = args->skrzynki.getPlecak();
         std::pair<std::vector<std::pair<int, punkt>>, std::pair<int, int>> lewa = args->skrzynki.getZiemia();

         for(int i=0; i<lewa.second.second-g->args->eq_przesuiniecie_z;++i)
         {
                  for(int j=0;j<lewa.second.first;++j)
                  {
                           al_draw_bitmap_region(g->equ_akcesoria, 0,0,g->args->X_kratka,g->args->Y_kratka, g->args->X_kratka*(j), g->args->Y_kratka*(i),0);
                  }
         }
         for(std::vector<std::pair<int, punkt>>::iterator it = lewa.first.begin(); it!=lewa.first.end(); ++it)
         {
                  g->namaluj_rzecz(g->eq1, ((*it).first), ((*it).second).x, ((*it).second).y, g->args->eq_przesuiniecie_z);
         }

         al_set_target_bitmap(g->eq2);
         al_clear_to_color(al_map_rgb(255,255,255));

         for(int i=0; i<prawa.second.second-g->args->eq_przesuiniecie_p;++i)
         {
                  for(int j=0;j<prawa.second.first;++j)
                  {
                           al_draw_bitmap_region(g->equ_akcesoria, 0,0,g->args->X_kratka,g->args->Y_kratka, g->args->X_kratka*(j), g->args->Y_kratka*(i),0);
                  }
         }
         for(std::vector<std::pair<int, punkt>>::iterator it = prawa.first.begin(); it!=prawa.first.end(); ++it)
         {
                  g->namaluj_rzecz(g->eq2, ((*it).first), ((*it).second).x, ((*it).second).y, g->args->eq_przesuiniecie_p);
         }

         al_set_target_bitmap(g->plansza1);
         al_draw_bitmap(g->eq1, g->args->X_kratka, g->args->Y_kratka,0);
         al_draw_bitmap(g->eq2, g->args->X_kratka*12, g->args->Y_kratka,0);

         int a=1;
         if(g->args->p_1) a+=2;
         al_draw_bitmap_region(g->equ_akcesoria, a*g->args->X_kratka, 0, g->args->X_kratka,g->args->Y_kratka,10*g->args->X_kratka, g->args->Y_kratka,0);
         a=1; if(g->args->p_2) a+=2;
         al_draw_bitmap_region(g->equ_akcesoria, a*g->args->X_kratka, 0, g->args->X_kratka,g->args->Y_kratka,21*g->args->X_kratka, g->args->Y_kratka,0);
         a=2;
         if(g->args->p_3) a+=2;
         al_draw_bitmap_region(g->equ_akcesoria, a*g->args->X_kratka, 0, g->args->X_kratka,g->args->Y_kratka,10*g->args->X_kratka, 11*g->args->Y_kratka,0);
         a=2; if(g->args->p_4) a+=2;
         al_draw_bitmap_region(g->equ_akcesoria, a*g->args->X_kratka, 0, g->args->X_kratka,g->args->Y_kratka,21*g->args->X_kratka, 11*g->args->Y_kratka,0);

         al_draw_bitmap_region(g->equ_pasek, 0,0, g->args->X_kratka, g->args->dlugosc_paska_s, 10*g->args->X_kratka, 2*g->args->Y_kratka+g->args->pozycja_paska_s,0);
         al_draw_bitmap_region(g->equ_pasek, 0,0, g->args->X_kratka, g->args->dlugosc_paska_p, 21*g->args->X_kratka, 2*g->args->Y_kratka+g->args->pozycja_paska_p,0);
}

void graficzny::rysuj_menu_anatomii()
{
         graficzny*g = this;
         al_draw_bitmap(g->anatomia, 0,0,0);
         g->namaluj_paskek_anatomii(g->args->brzuch_a, g->args->brzuch_max, 10*g->args->X_kratka, 5*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->klatka_a, g->args->klatka_max, 10*g->args->X_kratka, 3*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->l_ramie_a, g->args->l_ramie_max, 13*g->args->X_kratka, 4*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->p_ramie_a, g->args->p_ramie_max, 7*g->args->X_kratka, 4*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->l_dlon_a, g->args->l_dlon_max, 14*g->args->X_kratka, 6*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->p_dlon_a, g->args->p_dlon_max, 6*g->args->X_kratka, 6*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->l_udo_a, g->args->l_udo_max, 12*g->args->X_kratka, 8*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->p_udo_a, g->args->p_udo_max, 8*g->args->X_kratka, 8*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->l_golen_a, g->args->l_golen_max, 13*g->args->X_kratka, 10*g->args->Y_kratka);
         g->namaluj_paskek_anatomii(g->args->p_golen_a, g->args->p_golen_max, 7*g->args->X_kratka, 10*g->args->Y_kratka);
}

void graficzny::narysuj_zegarek()
{
         unsigned char ggg = args->nat_osw_alt != 0 ? args->nat_osw_alt : args->nat_osw;
         unsigned char kkk = ggg>args->max_przyciemnienie_interfejsu-1 ? args->max_przyciemnienie_interfejsu : (ggg>0 ? ggg : 1);
         unsigned char C1=kkk, C2=kkk, C3=kkk, C4=1.0;
         graficzny *g = this;
         int czas=g->args->czas,dzies_h, h, dzies_m, m;
         dzies_h=czas/600;
         h=czas/60-10*dzies_h;
         dzies_m=(czas-(dzies_h*10+h)*60)/10;
         m=czas-(dzies_h*10+h)*60-dzies_m*10;
         if(args->runda_swiata) al_draw_tinted_bitmap(g->zegarek_, al_map_rgba_f (C1,C2,C3,C4), g->pozycja_zegarka_x, g->pozycja_zegarka_y, 0);
         else al_draw_tinted_bitmap(g->zegarek, al_map_rgba_f (C1,C2,C3,C4), g->pozycja_zegarka_x, g->pozycja_zegarka_y, 0);
         al_draw_tinted_bitmap_region(g->_liczby, al_map_rgba_f (C1,C2,C3,C4),g->szerokosc_cyfr_0*(dzies_h),0,g->szerokosc_cyfr_0,g->wysokosc_cyfr_0, g->h_1+g->pozycja_zegarka_x,g->h_y,0);
         al_draw_tinted_bitmap_region(g->_liczby, al_map_rgba_f (C1,C2,C3,C4),g->szerokosc_cyfr_0*(h),0,g->szerokosc_cyfr_0,g->wysokosc_cyfr_0, g->h_2+g->pozycja_zegarka_x,g->h_y,0);
         al_draw_tinted_bitmap_region(g->_liczby, al_map_rgba_f (C1,C2,C3,C4),g->szerokosc_cyfr_0*(dzies_m),0,g->szerokosc_cyfr_0,g->wysokosc_cyfr_0, g->h_3+g->pozycja_zegarka_x,g->h_y,0);
         al_draw_tinted_bitmap_region(g->_liczby, al_map_rgba_f (C1,C2,C3,C4),g->szerokosc_cyfr_0*(m),0,g->szerokosc_cyfr_0,g->wysokosc_cyfr_0, g->h_4+g->pozycja_zegarka_x,g->h_y,0);
         int p=g->args->punkty_ruchu;
         if(g->args->punkty_ruchu<10)
         al_draw_tinted_bitmap_region(g->r_liczby, al_map_rgba_f (C1,C2,C3,C4), g->szerokosc_cyfr_0r*p,0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,g->p_1+g->szerokosc_cyfr_0r+g->pozycja_zegarka_x,g->p_y,0);
         else if(g->args->punkty_ruchu<100)
         {al_draw_tinted_bitmap_region(g->r_liczby, al_map_rgba_f (C1,C2,C3,C4), g->szerokosc_cyfr_0r*(p/10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,g->p_1+g->szerokosc_cyfr_0r*0.5+g->pozycja_zegarka_x,g->p_y,0);
         al_draw_tinted_bitmap_region(g->r_liczby, al_map_rgba_f (C1,C2,C3,C4), g->szerokosc_cyfr_0r*(p-p/10*10),0,g->szerokosc_cyfr_0r, g->wysokosc_cyfr_0r,g->p_1+g->szerokosc_cyfr_0r*1.5+g->pozycja_zegarka_x,g->p_y,0);}
}

void graficzny::narysuj_roznego_rodzaju_mena()
{
         graficzny*g = this;
         if(g->args->menu_spania)
         {
                  al_draw_bitmap_region(g->menu_spania, 0,0,g->X*7,g->Y*3, g->X*9, g->Y*5,0); int a=g->args->ile_spac;
                  if(a<10)
                  al_draw_bitmap_region(g->cyfry_duze, g->args->cyfry_duze_x*a,0,g->args->cyfry_duze_x, g->args->cyfry_duze_y,105*g->X/10, 6*g->Y,0);
                  else if(a<100)
                  {al_draw_bitmap_region(g->cyfry_duze, g->args->cyfry_duze_x*(a/10),0,g->args->cyfry_duze_x,g->args->cyfry_duze_y,10*g->X, 6*g->Y,0);
                  al_draw_bitmap_region(g->cyfry_duze,g->args->cyfry_duze_x*(a-a/10*10),0,g->args->cyfry_duze_x,g->args->cyfry_duze_y,10*g->X+g->args->cyfry_duze_x, 6*g->Y,0);}
         }
         if(g->args->ubranie_info)
         {
                  al_draw_bitmap(g->ubranie_info,9*g->X,3*g->Y,0);
                  g->narysuj_duze_cyfry(15*g->X,5*g->Y,g->args->wytrzymalosc);
                  g->narysuj_duze_cyfry(15*g->X,6*g->Y,g->args->ocieplenie);
                  g->narysuj_duze_cyfry(15*g->X,7*g->Y,g->args->kamuflarz);
                  g->narysuj_duze_cyfry(15*g->X,8*g->Y,g->args->ochrona);
         }
         if(g->args->bron_info)
         {
                  al_draw_bitmap(g->bron_info,9*g->X,3*g->Y,0);
                  g->narysuj_duze_cyfry(15*g->X,5*g->Y,g->args->wytrzymalosc);
                  g->narysuj_duze_cyfry(15*g->X,6*g->Y,g->args->obrazen);
                  g->narysuj_duze_cyfry(15*g->X,7*g->Y,g->args->szans);
                  g->narysuj_duze_cyfry(15*g->X,8*g->Y,g->args->blo);
                  g->narysuj_duze_cyfry(15*g->X,9*g->Y,g->args->kryty);
                  g->narysuj_duze_cyfry(15*g->X,10*g->Y,g->args->bonus_uni);
                  g->narysuj_duze_cyfry(15*g->X,11*g->Y,g->args->bonus_kop);
         }
}

graficzny::~graficzny()///destruktor niekompletny ale jako ze zawsze wywolany bedzie na koncu dzialania programu, a jego tresc trzeba byloby ciagle aktualizowac, to nie przywiazuje do niego wagi
{
         for(int i=0; i<5; i++)
         {
                  al_destroy_bitmap(avatar[i]);
                  al_destroy_bitmap(drzewa[i]);
         }

         //al_destroy_bitmap(tlo[0]);

         al_destroy_bitmap(podklad[0]);

         al_destroy_bitmap(mp);al_destroy_bitmap(mp1);al_destroy_bitmap(mp2);al_destroy_bitmap(mp3);

         al_destroy_bitmap(bufor);al_destroy_bitmap(plansza1); al_destroy_bitmap(plansza2);

         al_destroy_display(display);
}

ALLEGRO_BITMAP *graficzny::ktore_menu()
{

switch(args->ktore_menu)
{
         case 1: {return mp; break;}
case 2:
    {return menu_plecak; break;}
case 3:
    {return menu_s; break;}
case 4:
    {return menu_p; break;}
case 5:
    {return menu_ziemia; break;}
case 6:
    {return menu_ramie; break;}
case 7:
    {return menu_ubranie; break;}
case 8:
    {return menu_rece; break;}
case 9:
    {return menu_kieszen; break;}
case 10:
    {return menu_plecak_s; break;}
case 11:
    {return menu_walka1; break;}
case 12:
    {return menu_walka1_1; break;}
case 13:
    {return menu_walka1_2; break;}
case 14:
    {return menu_walka1_3; break;}
case 15:
    {return menu_walka1_4; break;}
case 20:
    {return menu_walka2; break;}
case 21:
    {return menu_walka2_1; break;}
case 22:
    {return menu_walka2_2; break;}
case 23:
    {return menu_walka3; break;}
case 24:
    {return menu_walka4; break;}
case 25:
    {return menu_pust_plecak; break;}
case 26:
    {return menu_schowek; break;}
case 27:
    {return menu_drzewo; break;}
case 28:
    {return menu_ognisko; break;}
case 29:
    {return strzelanie_menu1; break;}
case 30:
    {return strzelanie_menu1_1; break;}
case 31:
    {return strzelanie_menu1_2; break;}
case 32:
    {return strzelanie_menu1_3; break;}
case 33:
    {return strzelanie_menu1_4; break;}
case 34:
    {return strzelanie_menu2; break;}
case 35:
    {return strzelanie_menu2_1; break;}
case 36:
    {return strzelanie_menu2_2; break;}
case 37:
    {return strzelanie_menu3; break;}
case 38:
    {return strzelanie_menu3_1; break;}
case 39:
    {return menu_szalasu; break;}
case 40:
    {return menu_ataku_zwiarzeta; break;}
case 41:
    {return menu_strzelanie_zwierzeta; break;}
case 42:
    {return menu_okno1; break;}
case 43:
    {return menu_okno2; break;}
case 44:
    {return menu_okno3; break;}
case 45:
    {return menu_okno4; break;}
case 46:
    {return menu_okno5; break;}
case 47:
    {return zniszcz; break;}
case 48:
    {return zniszcz_; break;}
case 49:
    {return menu_drzwi1; break;}
case 50:
    {return menu_drzwi2; break;}
case 51:
    {return menu_drzwi3; break;}
case 52:{return menu_walka_lezacy;}
case 53:{return menu_walka_lezacy_1;}
case 54:{return menu_walka_lezacy_2;}
    ///statyczne numery musza byc <256


    ///montowanie menu:
    ///bity od lewego 8 bitu sa najwazniejsze, od 256
    ///w kolejnosci bity oznaczaja
    ///zniszcz 256
    ///przeszukaj 512
    ///przemiesc 1024
    ///wejdz 2048
    ///wyjdz 4096
    ///wez przescieradlo 8192
    ///umies przescieradlo 16384
    ///wez 32768
    ///przejdz nad/pod 65536
    ///spij 131072
    ///otworz 262144
    ///zamknij 524288

default:
    {
        ///skalujemy w locie bo jest to wzglednie rzadka i pojedyncza operacja
        if((int)args->ktore_menu<256)
        {
            std::cout<< "Grafika, wyswietlanie menu, niewlasciwe menu";
            throw 'n';
        }

        if(ktore_aktualnie_mamy_menu == args->ktore_menu)
        {
            return aktualne_dynamiczie_robione_menu;
            break;
        }
        else
        {
            if(aktualne_dynamiczie_robione_menu!=NULL)
                al_destroy_bitmap(aktualne_dynamiczie_robione_menu);
            aktualne_dynamiczie_robione_menu = NULL;

            short dl = 0;
            for(short kl=0; kl<30; ++kl)
                if((args->ktore_menu&(256<<kl))==(256<<kl))
                    ++dl;

            ALLEGRO_BITMAP* ff= al_create_bitmap(150, dl*50);
            al_set_target_bitmap(ff);
            dl = 0; ///dl jest teraz ostatnia wysokoscia wklejania menu

            for(short kl=0; kl<20; ++kl)
                if((args->ktore_menu&((256<<kl)))==(256<<kl))
                {
                    al_draw_bitmap_region(uniwersalne_menu,0,kl*50,150,50,0,dl++*50,0);
                }


            aktualne_dynamiczie_robione_menu = graficzny::wyskaluj_menu(ff, args->menu_x, args->menu_y);
            ///wyskaluj menu deletuje ff
            return aktualne_dynamiczie_robione_menu;


        }
        //std::cout<< "Grafika, wyswietlanie menu, niewlasciwe menu"; throw 'n';
    }
}
}

ALLEGRO_BITMAP *graficzny::ktore_submenu()
{
         switch(args->ktore_sub_menu)
         {
                  case 2: {return mp1; break;}
                  case 3: {return mp2; break;}
                  case 4: {return mp3; break;}
                  case 16: {return menu_walka11; break;}
                  case 17: {return menu_walka12; break;}
                  case 18: {return menu_walka13; break;}
                  case 19: {return menu_walka14; break;}
                  case 20: {return menu_walka21; break;}
                  case 21: {return menu_walka22; break;}
                  case 41: {return strzelanie_menu11; break;}
                  case 42: {return strzelanie_menu12; break;}
                  case 45: {return submenu_przemieszcz; break;}
                  case 46: {return stol_sub_1; break;}///przewroc
                  case 47: {return stol_sub_2; break;}///podnies
                  case 48: {return menu_strony; break;}
                  case 49: {return beczka_sub; break;}

                  default: std::cout<< "Grafika, wyswietlanie submenu, niewlasciwe menu"; throw 'n';
                  }
}

ALLEGRO_BITMAP * graficzny::wyskaluj (ALLEGRO_BITMAP* obrazek, int X, int Y)
{
         al_convert_mask_to_alpha( obrazek, al_map_rgb(255,0,255));
         ALLEGRO_BITMAP*zwracany=al_create_bitmap(al_get_bitmap_width(obrazek)/75*X, al_get_bitmap_height(obrazek)/75*Y);
         al_set_target_bitmap(zwracany);
         //al_draw_scaled_bitmap(obrazek, 0,0,al_get_bitmap_width(obrazek),al_get_bitmap_height(obrazek),0,0,al_get_bitmap_width(obrazek)/75*X,al_get_bitmap_height(obrazek)/75*Y,0);
         al_draw_tinted_scaled_bitmap(obrazek, al_map_rgba_f (1,1,1,1.0), 0,0,al_get_bitmap_width(obrazek),al_get_bitmap_height(obrazek),0,0,al_get_bitmap_width(obrazek)/75*X,al_get_bitmap_height(obrazek)/75*Y,0);
         return zwracany;
         //ALLEGRO_BITMAP* zwracany = al_create_bitmap(al_get_bitmap_width(obrazek)/75*X, al_get_bitmap_height(obrazek)/75*Y);
         //al_set_target_bitmap(zwracany);
         for(int m=0; m<al_get_bitmap_width(obrazek)/75; m++)///xxxx
         {
                  for(int d=0; d<al_get_bitmap_height(obrazek)/75; d++)
                  {
                           al_draw_tinted_scaled_rotated_bitmap_region(obrazek, 75*m, 75*d, X, Y, al_map_rgba_f (1.0,1.0,1.0,1.0),0,0,X*m,Y*d,1, 1,0,0);
                  }
         }
         return zwracany;
}

ALLEGRO_BITMAP * graficzny::wyskaluj_menu (ALLEGRO_BITMAP* obrazek, int menu_x, int menu_y)
{
         ALLEGRO_BITMAP* zwracany = al_create_bitmap(menu_x, al_get_bitmap_height(obrazek)/50*menu_y);
         al_set_target_bitmap(zwracany);
         /*for(int m=0; m<al_get_bitmap_height(obrazek)/50; m++)///xxxx
         {
                  al_draw_tinted_scaled_rotated_bitmap_region(obrazek, 0, 50*m, menu_x, menu_y, al_map_rgba_f (1.0,1.0,1.0,1.0),0,0,0,menu_y*m,1, 1,0,0);
         }*/
         al_draw_scaled_bitmap(obrazek,0,0,al_get_bitmap_width(obrazek),al_get_bitmap_height(obrazek),0,0,menu_x, al_get_bitmap_height(obrazek)/50*menu_y,0);
         al_destroy_bitmap(obrazek);
         return zwracany;
}

dane_rysownicze graficzny::jak_narysowac(int nr)
{
         graficzny*g=this;
         dane_rysownicze a; ALLEGRO_BITMAP*co;
          int x_zrodl=g->args->X_kratka, y_zrodl=g->args->Y_kratka;
         switch(nr)
         {
                  case 2001:{co=g->rzeczy;x_zrodl*=0;y_zrodl*=0;break;}
                  case 2006:{co=g->rzeczy;x_zrodl*=2;y_zrodl*=6;break;}
                  case 2007:{co=g->rzeczy;x_zrodl*=3;y_zrodl*=6;break;}
                  case 2008:{co=g->rzeczy;x_zrodl*=5;y_zrodl*=15;break;}
                  case 3001: {co=g->rzeczy;x_zrodl*=0;y_zrodl*=2;break;}
                  case 4251: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=3;break;}
                  case 4252: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=4;break;}
                  case 4003:  {co=g->rzeczy;x_zrodl*=12;y_zrodl*=8;break;}
                  case 4004: {co=g->rzeczy;x_zrodl*=14;y_zrodl*=8;break;}
                  case 4005: {co=g->rzeczy;x_zrodl*=16;y_zrodl*=6;break;}
                  case 4501: {co=g->rzeczy;x_zrodl*=0;y_zrodl*=1;break;}
                  case 5001: {co=g->rzeczy;x_zrodl*=0;y_zrodl*=3;break;}
                  case 2002: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=5;break;}
                  case 2003: {co=g->rzeczy;x_zrodl*=11;y_zrodl*=15;break;}
                  case 2004: {co=g->rzeczy;x_zrodl*=12;y_zrodl*=15;break;}
                  case 2005: {co=g->rzeczy;x_zrodl*=13;y_zrodl*=15;break;}
                  case 3002: {co=g->rzeczy;x_zrodl*=0;y_zrodl*=4;break;}
                  case 3003: {co=g->rzeczy;x_zrodl*=0;y_zrodl*=8;break;}
                  case 3004: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=8;break;}
                  case 3005: {co=g->rzeczy;x_zrodl*=0;y_zrodl*=9;break;}
                  case 3006: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=9;break;}
                  case 4006: {co=g->rzeczy;x_zrodl*=17;y_zrodl*=11;break;}
                  case 4009: {co=g->rzeczy;x_zrodl*=3;y_zrodl*=13;break;}
                  case 4253: {co=g->equ_bron;x_zrodl*=9;y_zrodl*=0;break;}
                  case 4254: {co=g->equ_bron;x_zrodl*=9;y_zrodl*=2;break;}
                  case 4255: {co=g->equ_bron;x_zrodl*=9;y_zrodl*=1;break;}
                  case 4256: {co=g->equ_bron;x_zrodl*=9;y_zrodl*=3;break;}
                  case 4260: {co=g->rzeczy;x_zrodl*=13;y_zrodl*=10;break;}
                  case 4751: {co=g->rzeczy;x_zrodl*=7;y_zrodl*=8;break;}
                  case 4752: {co=g->rzeczy;x_zrodl*=11;y_zrodl*=8;break;}
                  case 4753: {co=g->rzeczy;x_zrodl*=15;y_zrodl*=9;break;}
                  case 5002:  {co=g->rzeczy;x_zrodl*=4;y_zrodl*=6;break;}
                  case 5501: {co=g->rzeczy;x_zrodl*=6;y_zrodl*=8;break;}
                  case 5502: {co=g->rzeczy;x_zrodl*=6;y_zrodl*=7;break;}
                  case 5503: {co=g->rzeczy;x_zrodl*=7;y_zrodl*=9;break;}
                  case 6001: {co=g->rzeczy;x_zrodl*=10;y_zrodl*=6;break;}
                  case 6002: {co=g->rzeczy;x_zrodl*=9;y_zrodl*=7;break;}
                  case 6003: {co=g->rzeczy;x_zrodl*=11;y_zrodl*=12;break;}
                  case 6004: {co=g->rzeczy;x_zrodl*=2;y_zrodl*=9;break;}
                  case 6501: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=6;break;}
                  case 6502: {co=g->rzeczy;x_zrodl*=7;y_zrodl*=6;break;}
                  case 6503: {co=g->rzeczy;x_zrodl*=14;y_zrodl*=10;break;}
                  case 6504: {co=g->rzeczy;x_zrodl*=13;y_zrodl*=11;break;}
                  case 6505: {co=g->rzeczy;x_zrodl*=14;y_zrodl*=11;break;}
                  case 2101: {co=g->rzeczy;x_zrodl*=1;y_zrodl*=2;break;}
                  case 8001: {co=g->rzeczy;x_zrodl*=2;y_zrodl*=7;break;}
                  case 8002: {co=g->rzeczy;x_zrodl*=3;y_zrodl*=7;break;}
                  case 2102: {co=g->rzeczy;x_zrodl*=10;y_zrodl*=9;break;}
                  case 2103: {co=g->rzeczy;x_zrodl*=13;y_zrodl*=8;break;}
                  case 2104: {co=g->equ_bron;x_zrodl*=9;y_zrodl*=4;break;}
                  case 8017: {co=g->rzeczy;x_zrodl*=2;y_zrodl*=8;break;}
                  case 8003: {co=g->equ_bron;x_zrodl*=9;y_zrodl*=7;break;}
                  case 8004: {co=g->rzeczy;x_zrodl*=10;y_zrodl*=7;break;}
                  case 8005: {co=g->rzeczy;x_zrodl*=10;y_zrodl*=8;break;}
                  case 4007:{co=g->rzeczy;x_zrodl*=19;y_zrodl*=10;break;}
                  case 4008:{co=g->rzeczy;x_zrodl*=19;y_zrodl*=5;break;}
                  case 4502:{co=g->rzeczy;x_zrodl*=18;y_zrodl*=11;break;}
                  case 4503:{co=g->rzeczy;x_zrodl*=19;y_zrodl*=11;break;}
                  case 8006:{co=g->rzeczy;x_zrodl*=3;y_zrodl*=12;break;}
                  case 8007:{co=g->rzeczy;x_zrodl*=4;y_zrodl*=12;break;}
                  case 8008:{co=g->rzeczy;x_zrodl*=5;y_zrodl*=12;break;}
                  case 8009:{co=g->rzeczy;x_zrodl*=6;y_zrodl*=12;break;}
                  case 8010:{co=g->rzeczy;x_zrodl*=7;y_zrodl*=12;break;}
                  case 8011:{co=g->rzeczy;x_zrodl*=8;y_zrodl*=12;break;}
                  case 8012:{co=g->rzeczy;x_zrodl*=9;y_zrodl*=12;break;}
                  case 8013:{co=g->rzeczy;x_zrodl*=6;y_zrodl*=13;break;}
                  case 8014:{co=g->rzeczy;x_zrodl*=7;y_zrodl*=13;break;}
                  case 8015:{co=g->rzeczy;x_zrodl*=8;y_zrodl*=13;break;}
                  case 8016:{co=g->rzeczy;x_zrodl*=9;y_zrodl*=13;break;}
                  case 8018:{co=g->rzeczy;x_zrodl*=17;y_zrodl*=12;break;}
                  case 8019:{co=g->rzeczy;x_zrodl*=5;y_zrodl*=14;break;}
                  case 8020:{co=g->rzeczy;x_zrodl*=6;y_zrodl*=14;break;}
                  default: {std::cout<<"nie wiem jak narysowac ten przedmiot maly"<<" "<<nr;co=g->rzeczy;x_zrodl*=3;y_zrodl*=8;break; }
         }
         a.x=x_zrodl; a.y=y_zrodl; a.a=co;
         return a;
}

void graficzny::namaluj_rzecz(ALLEGRO_BITMAP*a, int nr, int x, int y, int wsp_x,bool brac_doslownie_wymiary) ///wsp_x to wspolrzedne x dla lewego gornego
{
         graficzny*g=this;
         int x_zrodl=g->args->X_kratka, y_zrodl=g->args->Y_kratka, x_rozm=g->args->X_kratka, y_rozm=g->args->Y_kratka; ALLEGRO_BITMAP*d;
         switch(nr)
         {
                  case 2001:{d=g->rzeczy;x_zrodl*=0;y_zrodl*=0;break;}
                   case 2002:{d=g->rzeczy;x_zrodl*=1;y_zrodl*=5;x_rozm*=1;y_rozm*=1;break;}
                  case 2003: {d=g->rzeczy;x_zrodl*=11;y_zrodl*=13;x_rozm*=1;y_rozm*=2;break;}
                  case 2004: {d=g->rzeczy;x_zrodl*=12;y_zrodl*=13;x_rozm*=1;y_rozm*=2;break;}
                  case 2005: {d=g->rzeczy;x_zrodl*=13;y_zrodl*=13;x_rozm*=1;y_rozm*=2;break;}
                  case 2006: {d=g->rzeczy;x_zrodl*=2;y_zrodl*=6;x_rozm*=1;y_rozm*=1;break;}
                  case 2007: {d=g->rzeczy;x_zrodl*=3;y_zrodl*=6;x_rozm*=1;y_rozm*=1;break;}
                  case 2008: {d=g->rzeczy;x_zrodl*=3;y_zrodl*=14;x_rozm*=1;y_rozm*=2;break;}
                  case 2101: {d=g->rzeczy;x_zrodl*=1;y_zrodl*=0;x_rozm*=1;y_rozm*=2;break;}
                  case 2104: {d=g->equ_bron;x_zrodl*=9;y_zrodl*=4;x_rozm*=1;y_rozm*=1;break;}
                  case 3001: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=2;break;}
                  case 3002: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=4;x_rozm*=1;y_rozm*=1;break;}
                  case 3003: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=8;x_rozm*=1;y_rozm*=1;break;}
                  case 3004: {d=g->rzeczy;x_zrodl*=1;y_zrodl*=8;x_rozm*=1;y_rozm*=1;break;}
                  case 3005: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=9;x_rozm*=1;y_rozm*=1;break;}
                  case 3006: {d=g->rzeczy;x_zrodl*=1;y_zrodl*=9;x_rozm*=1;y_rozm*=1;break;}
                  case 4006: {d=g->rzeczy;x_zrodl*=17;y_zrodl*=0;x_rozm*=2;y_rozm*=11;break;}
                  case 4009: {d=g->rzeczy;x_zrodl*=3;y_zrodl*=13;x_rozm*=1;y_rozm*=1;break;}
                  case 4251: {d=g->rzeczy;x_zrodl*=2;y_zrodl*=0;x_rozm*=9;y_rozm*=3;break;}
                  case 4252: {d=g->rzeczy;x_zrodl*=2;y_zrodl*=3;x_rozm*=9;y_rozm*=3;break;}
                  case 4260: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=10;x_rozm*=9;y_rozm*=2;break;}
                  case 4003: {d=g->rzeczy;x_zrodl*=11;y_zrodl*=0;x_rozm*=1;y_rozm*=8;break;}
                  case 4004: {d=g->rzeczy;x_zrodl*=12;y_zrodl*=0;x_rozm*=2;y_rozm*=8;break;}
                  case 4005: {d=g->rzeczy;x_zrodl*=15;y_zrodl*=0;x_rozm*=2;y_rozm*=6;break;}
                  case 4253: {d=g->equ_bron;x_zrodl*=0;y_zrodl*=0;x_rozm*=9;y_rozm*=3;break;}
                  case 4254: {d=g->equ_bron;x_zrodl*=0;y_zrodl*=6;x_rozm*=9;y_rozm*=2;break;}
                  case 4255: {d=g->equ_bron;x_zrodl*=0;y_zrodl*=3;x_rozm*=9;y_rozm*=3;break;}
                  case 4256: {d=g->equ_bron;x_zrodl*=0;y_zrodl*=8;x_rozm*=9;y_rozm*=2;break;}
                  case 4501: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=1;break;}
                  //case 4251: {d=g->rzeczy;x_zrodl*=8;y_zrodl*=8;x_rozm*=2;y_rozm*=2;break;}
                  //case 4252: {d=g->rzeczy;x_zrodl*=11;y_zrodl*=9;x_rozm*=2;y_rozm*=2;break;}
                  //case 4253: {d=g->rzeczy;x_zrodl*=13;y_zrodl*=9;x_rozm*=2;y_rozm*=1;break;}
                  case 4751: {d=g->rzeczy;x_zrodl*=8;y_zrodl*=8;x_rozm*=2;y_rozm*=2;break;}
                  case 4752: {d=g->rzeczy;x_zrodl*=11;y_zrodl*=9;x_rozm*=2;y_rozm*=2;break;}
                  case 4753: {d=g->rzeczy;x_zrodl*=13;y_zrodl*=9;x_rozm*=2;y_rozm*=1;break;}
                  case 5001: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=3;break;}
                  case 5002:  {d=g->rzeczy;x_zrodl*=4;y_zrodl*=6;x_rozm*=1;y_rozm*=1;break;}
                  case 5501: {d=g->rzeczy;x_zrodl*=4;y_zrodl*=8;x_rozm*=2;y_rozm*=1;break;}
                  case 5502: {d=g->rzeczy;x_zrodl*=4;y_zrodl*=7;x_rozm*=2;y_rozm*=1;break;}
                  case 5503: {d=g->rzeczy;x_zrodl*=5;y_zrodl*=9;x_rozm*=2;y_rozm*=1;break;}
                  case 6001: {d=g->rzeczy;x_zrodl*=8;y_zrodl*=6;x_rozm*=2;y_rozm*=1;break;}
                  case 6002: {d=g->rzeczy;x_zrodl*=7;y_zrodl*=7;x_rozm*=2;y_rozm*=1;break;}
                  case 6003: {d=g->rzeczy;x_zrodl*=12;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 6004: {d=g->rzeczy;x_zrodl*=3;y_zrodl*=9;x_rozm*=2;y_rozm*=1;break;}
                  case 6501: {d=g->rzeczy;x_zrodl*=0;y_zrodl*=7;x_rozm*=2;y_rozm*=1;break;}
                  case 6502: {d=g->rzeczy;x_zrodl*=5;y_zrodl*=6;x_rozm*=2;y_rozm*=1;break;}
                  case 6503: {d=g->rzeczy;x_zrodl*=15;y_zrodl*=10;x_rozm*=2;y_rozm*=1;break;}
                  case 6504: {d=g->rzeczy;x_zrodl*=11;y_zrodl*=11;x_rozm*=2;y_rozm*=1;break;}
                  case 6505: {d=g->rzeczy;x_zrodl*=15;y_zrodl*=11;x_rozm*=2;y_rozm*=2;break;}
                  case 8001: {d=g->rzeczy;x_zrodl*=2;y_zrodl*=7;x_rozm*=1;y_rozm*=1;break;}
                  case 8002: {d=g->rzeczy;x_zrodl*=9;y_zrodl*=10;x_rozm*=2;y_rozm*=2;break;}
                  case 2102: {d=g->rzeczy;x_zrodl*=10;y_zrodl*=9;x_rozm*=1;y_rozm*=1;break;}
                  case 2103: {d=g->rzeczy;x_zrodl*=13;y_zrodl*=8;x_rozm*=1;y_rozm*=1;break;}
                  case 8017: {d=g->rzeczy;x_zrodl*=2;y_zrodl*=8;x_rozm*=1;y_rozm*=1;break;}
                  case 8003: {d=g->equ_bron;x_zrodl*=9;y_zrodl*=5;x_rozm*=1;y_rozm*=2;break;}
                  case 8004: {d=g->equ_bron;x_zrodl*=10;y_zrodl*=7;x_rozm*=1;y_rozm*=1;break;}
                  case 8005: {d=g->equ_bron;x_zrodl*=10;y_zrodl*=8;x_rozm*=1;y_rozm*=1;break;}
                  case 4007:{d=g->rzeczy;x_zrodl*=19;y_zrodl*=6;x_rozm*=1;y_rozm*=4;break;}
                  case 4008:{d=g->rzeczy;x_zrodl*=19;y_zrodl*=0;x_rozm*=1;y_rozm*=5;break;}
                  case 4502:{d=g->rzeczy;x_zrodl*=18;y_zrodl*=11;x_rozm*=1;y_rozm*=1;break;}
                  case 4503:{d=g->rzeczy;x_zrodl*=19;y_zrodl*=11;x_rozm*=1;y_rozm*=1;break;}
                  case 8006:{d=g->rzeczy;x_zrodl*=0;y_zrodl*=12;x_rozm*=3;y_rozm*=2;break;}

                  case 8007:{d=g->rzeczy;x_zrodl*=4;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8008:{d=g->rzeczy;x_zrodl*=5;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8009:{d=g->rzeczy;x_zrodl*=6;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8010:{d=g->rzeczy;x_zrodl*=7;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8011:{d=g->rzeczy;x_zrodl*=8;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8012:{d=g->rzeczy;x_zrodl*=9;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8013:{d=g->rzeczy;x_zrodl*=6;y_zrodl*=13;x_rozm*=1;y_rozm*=1;break;}
                  case 8014:{d=g->rzeczy;x_zrodl*=7;y_zrodl*=13;x_rozm*=1;y_rozm*=1;break;}
                  case 8015:{d=g->rzeczy;x_zrodl*=8;y_zrodl*=13;x_rozm*=1;y_rozm*=1;break;}
                  case 8016:{d=g->rzeczy;x_zrodl*=9;y_zrodl*=13;x_rozm*=1;y_rozm*=1;break;}
                  case 8018:{d=g->rzeczy;x_zrodl*=17;y_zrodl*=12;x_rozm*=1;y_rozm*=1;break;}
                  case 8019:{d=g->rzeczy;x_zrodl*=4;y_zrodl*=14;x_rozm*=1;y_rozm*=2;break;}
                  case 8020:{d=g->rzeczy;x_zrodl*=6;y_zrodl*=14;x_rozm*=1;y_rozm*=1;break;}
                  default: {std::cout<<"nie wiem jak narysowac ten przedmiot duzy"<<" "<<nr; d=g->rzeczy;x_zrodl*=3;y_zrodl*=8;x_rozm*=1;y_rozm*=1;break;}
         }
         al_set_target_bitmap(a);
         if(!brac_doslownie_wymiary){al_draw_bitmap_region(d, x_zrodl, y_zrodl, x_rozm, y_rozm,(x)*g->args->X_kratka,(y-wsp_x)*g->args->Y_kratka,0);}
         else{al_draw_bitmap_region(d, x_zrodl, y_zrodl, x_rozm, y_rozm,x,y,0);}
}

int graficzny::najmniej_zero(int a)
{
         if(a>0) return a; else return 0;
}

void graficzny::namaluj_paskek_anatomii(int a, int maxx, int x, int y)
{
         graficzny*g=this;
         al_draw_bitmap_region(g->pasek_anatomii, 0,0,a*2*g->args->X_kratka/maxx, 2*g->args->Y_kratka/3,x, y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*10,0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-0.5*(20*g->args->rozdz_X/1920), y,0);
         if(a<10)
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*a,0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-1.5*(20*g->args->rozdz_X/1920), y,0);
         else if(a<100)
         {al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*(a/10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-2.5*(20*g->args->rozdz_X/1920), y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*(a-a/10*10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-1.5*(20*g->args->rozdz_X/1920), y,0);}
         else if(a<1000)
         {al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*g->najmniej_zero(a/100),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-3.5*(20*g->args->rozdz_X/1920), y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*g->najmniej_zero((a-a/100*100)/10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-2.5*(20*g->args->rozdz_X/1920), y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*g->najmniej_zero(a-a/10*10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka-1.5*(20*g->args->rozdz_X/1920), y,0);}
         if(maxx<10)
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*maxx,0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka+0.5*(20*g->args->rozdz_X/1920), y,0);
         else if(maxx<100)
         {al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*(maxx/10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka+0.5*(20*g->args->rozdz_X/1920), y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*(maxx-maxx/10*10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka+1.5*(20*g->args->rozdz_X/1920), y,0);}
         else if(maxx<1000)
         {al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*g->najmniej_zero(maxx/100),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka+0.5*(20*g->args->rozdz_X/1920), y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*g->najmniej_zero((maxx-maxx/100*100)/10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka+1.5*(20*g->args->rozdz_X/1920), y,0);
         al_draw_bitmap_region(g->czczionka_paski, (20*g->args->rozdz_X/1920)*g->najmniej_zero(maxx-maxx/10*10),0,20*g->args->rozdz_X/1920, 26*g->args->rozdz_Y/1080,x+g->args->X_kratka+2.5*(20*g->args->rozdz_X/1920), y,0);}
}

void graficzny::namaluj_paski()
{
         unsigned char ggg = args->nat_osw_alt != 0 ? args->nat_osw_alt : args->nat_osw;
         unsigned char kkk = ggg>args->max_przyciemnienie_interfejsu-1 ? args->max_przyciemnienie_interfejsu : (ggg>0 ? ggg : 1);
         unsigned char C1=kkk, C2=kkk, C3=kkk, C4=1.0;
         graficzny *g = this;
         for(int i=0;i<4;++i)
         {
                  al_draw_tinted_bitmap_region(g->napisy, al_map_rgba_f (C1,C2,C3,C4), 0,i*al_get_bitmap_height(g->napisy)/4, al_get_bitmap_width(g->napisy),al_get_bitmap_height(g->napisy)/4,i*415*g->args->rozdz_X/1920, 14*g->args->Y_kratka,0);
                  int a, maxx;switch(i){case 0:a=g->args->woda_a;maxx=g->args->woda_max;break;case 1:a=g->args->jedzenie_a;maxx=g->args->jedzenie_max;break;
                  case 2:a=g->args->cieplo_a;maxx=g->args->cieplo_max;break;case 3:a=g->args->energia_a;maxx=g->args->energia_max;break;}
                  al_draw_tinted_bitmap(g->pasek_ogolny, al_map_rgba_f (C1,C2,C3,C4),(125+20+i*415)*g->args->rozdz_X/1920, 14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->pasek_uzytkowy, al_map_rgba_f (C1,C2,C3,C4),0,0,al_get_bitmap_width(g->pasek_uzytkowy)*a/maxx,al_get_bitmap_height(g->pasek_uzytkowy),(125+23+i*415)*g->args->rozdz_X/1920, 14*g->args->Y_kratka,0);

                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*10,0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-0.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  if(a<10)al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*a,0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-1.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  else if(a<100)
                  {al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(a/10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-2.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(a-a/10*10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-1.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);}
                  else if(a<1000)
                  {al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(a/100),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-3.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*((a-a/100*100)/10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-2.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(a-a/10*10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2-1.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);}
                  if(maxx<10)al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*maxx,0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2+0.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  else if(maxx<100)
                  {al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(maxx/10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2+0.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(maxx-maxx/10*10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2+1.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);}
                  else if(maxx<1000)
                  {al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(maxx/100),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2+0.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*((maxx-maxx/100*100)/10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2+1.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);
                  al_draw_tinted_bitmap_region(g->czczionka_paski, al_map_rgba_f (C1,C2,C3,C4),(20*g->args->rozdz_X/1920)*(maxx-maxx/10*10),0,(20*g->args->rozdz_X/1920),26*g->args->rozdz_Y/1080,(145+i*415)*g->args->rozdz_X/1920+(al_get_bitmap_width(g->pasek_ogolny)/2+2.5*(20*g->args->rozdz_X/1920)),14*g->args->Y_kratka,0);}

         }


}

void graficzny::narysuj_duze_cyfry(int x, int y, int a)
{
         graficzny *g = this;
         if(a<0){
                           if(a>-10)al_draw_bitmap_region(g->cyfry_duze,g->args->cyfry_duze_x*10,0,g->args->cyfry_duze_x, g->args->cyfry_duze_y,x-g->args->cyfry_duze_x, y,0);
                           else if(a>-100)al_draw_bitmap_region(g->cyfry_duze,g->args->cyfry_duze_x*10,0,g->args->cyfry_duze_x, g->args->cyfry_duze_y,x-2*g->args->cyfry_duze_x, y,0);
                  a*=-1;
         }
         if(a<10)
         al_draw_bitmap_region(g->cyfry_duze,g->args->cyfry_duze_x*a,0,g->args->cyfry_duze_x, g->args->cyfry_duze_y,x, y,0);
         else if(a<100)
         {al_draw_bitmap_region(g->cyfry_duze, g->args->cyfry_duze_x*(a/10),0,g->args->cyfry_duze_x,g->args->cyfry_duze_y,x-0.5*g->args->cyfry_duze_x, y,0);
         al_draw_bitmap_region(g->cyfry_duze,g->args->cyfry_duze_x*(a-a/10*10),0,g->args->cyfry_duze_x,g->args->cyfry_duze_y,x+0.5*g->args->cyfry_duze_x, y,0);}
}
