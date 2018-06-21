#include "gra.h"
#include "allegro5/allegro.h"

bool Gra::jest_na_polu (dla_grafiki*args,ALLEGRO_MOUSE_STATE myszka, int x, int y)///pole standardowe, poz myszki, poz pola
{
         return (myszka.x>=(args->X_kratka*x)+(args->X_kratka/2) && myszka.x<(args->X_kratka*(x+1)+(args->X_kratka/2))&&(myszka.y>=args->Y_kratka*y+(args->Y_kratka/2))&&(myszka.y<args->Y_kratka*(y+1)+(args->Y_kratka/2)));
}

void Gra::poczekaj_na_puszczenie_klawisza(short k)
{
         ALLEGRO_KEYBOARD_STATE klawiatura;
         while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura); if(al_key_down(&klawiatura, k))break;}
}

void Gra::show_message(std::string a)
{

}



bool Gra::pobierz_punkty_ruchu(int ile)
{
         if(swiat->aktualny->p_ruchu<ile) return false;
         else {swiat->aktualny->p_ruchu-=ile; return true;}
}

bool Gra::pobierz_punkty_ruchu_i_kondycje(int ile_p_ruchu, int ile_kondycji)
{
         if(*args->godmode) return true;
         if(swiat->aktualny->kondycja-ile_kondycji>=0 && pobierz_punkty_ruchu(ile_p_ruchu))
         {
                  swiat->aktualny->kondycja-=ile_kondycji; return true;
         }
         return false;
}

void Gra::dodaj_jedzenia(int ile)
{
         int d=swiat->aktualny->jedzenie_a+ile; if(d>swiat->aktualny->jedzenie_max) d=swiat->aktualny->jedzenie_max;
         if(d<0) d=0;
         swiat->aktualny->jedzenie_a=d;
}

void Gra::dodaj_wody(int ile)
{
         int d=swiat->aktualny->woda_a+ile; if(d>swiat->aktualny->woda_max) d=swiat->aktualny->woda_max;
         if(d<0) d=0; swiat->aktualny->woda_a=d;
}

void Gra::przesun_mapy(char strona, dla_grafiki *args, Swiat*swiat)
{
         swiat->aktualna->ma_gracza=false;/////////////////////////////////////////////////////////////////////////////////////////////////////
         args->przesuniecie=0; args->strona=strona;
         int nx=swiat->aktualna->x,ny=swiat->aktualna->y;
         switch (strona) {case 'p':nx++;break;case 'l':nx--;break;case 'd':ny++;break;case 'g':ny--;break; }
         args->plansza_docelowa=(void*)swiat->zwroc_taka_plansze(nx, ny, swiat->aktualna->z);
         if(args->plansza_docelowa==NULL) {std::cout<<"przesun mapy dostala nullowa aree"; throw "F";}
         args->przesuwamy_plansze=true;
         if(strona=='p' || strona=='l') for(int i=0; i<22*args->X_kratka;++i) {++args->przesuniecie;if(i%2==0)Sleep(1000/(args->rozdz_X/2));}
                  else for(int i=0; i<14*args->Y_kratka;i++) {++args->przesuniecie;if(i%2==0)Sleep(660/(args->rozdz_Y/2));}
          //swiat->a_x=nx; swiat->a_y=ny;
          swiat->Ustaw_aktualna((Plansza*)args->plansza_docelowa);
         //swiat->aktualna=(Plansza*)swiat->area[swiat->a_x][swiat->a_y][swiat->aktualna->z];
         swiat->aktualna->ma_gracza=true;////////////////////////////////////////////////////////////////////////////////////////////////////////
         al_rest(0.2);args->przesuwamy_plansze=false;
}
Gra*Gra::gra;
Punkt *Objekt::c;
bool Objekt::wstrzymaj_animacje=false;
Punkt *Plansza::c;
Punkt *Objekt::z;
Punkt_wagowy *Objekt::d;
planszowa<short> Plansza::pomocnicza;
planszowa<bool> Plansza::pom[5];
planszowa<bool> Objekt::obstacles;
Gra :: Gra(struct dla_grafiki* arg)
{
         Objekt::c = new  Punkt[300];
         Objekt::z = new  Punkt[300];
         Objekt::d = new  Punkt_wagowy[300];
         Plansza::c = new Punkt[2500];

         swiat = new Swiat(&przerwa, arg->X_kratka, arg->Y_kratka,arg, godmode);
         arg->world=(void*)swiat;
         gra=this;args=arg;
}

struct punkt Gdzie_menu(int x, int y, bool submenowe, struct dla_grafiki*args, int il_opcji)
{
         struct punkt a;
         if(!submenowe)
         {
                  if(x+args->menu_x+5<args->rozdz_X)a.x=x;
                  else a.x=x-args->menu_x;
         }
         else
         {
                  ///tutaj x i y oznaczaja lewy gorny rog kliknietego menu
                  if(x+args->menu_x*2+5<args->rozdz_X) a.x=x+args->menu_x;
                  else a.x=x-args->menu_x;
         }
         for(int i=0; i<il_opcji*args->menu_y;i+=args->menu_y)
         {
                  if(y+il_opcji*args->menu_y-i+5<args->rozdz_Y)
                  {
                           a.y=y-i; break;
                  }
                  else if(!submenowe && i+args->menu_y>=il_opcji*args->menu_y)
                  {
                           a.y=y-il_opcji*args->menu_y;
                  }
         }
         return a;
}

int ktora_opcja(int x, int y, int ilosc_opcji, int mx, int my, struct dla_grafiki*args) ///0 to poza menu, mx to myszka
{
         if((mx<x)||(mx>x+args->menu_x)||(my<y)||(my>y+ilosc_opcji*args->menu_y)) return 0;
         return (my-y)/args->menu_y+1;
}

void Gra::poczekaj_na_myszke(int przycisk){ALLEGRO_MOUSE_STATE myszka; while(true){al_rest(0.01);al_get_mouse_state(&myszka);if(!(myszka.buttons & przycisk))break;}}
void Gra::koncz_z_menami(dla_grafiki*args) {args->menu=false; args->submenu=false;}

bool Gra::jest_nad_klatka(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>9*args->X_kratka&&myszka.x<13*args->X_kratka&&myszka.y>2*args->Y_kratka&&myszka.y<3*args->Y_kratka)||
(myszka.x>10*args->X_kratka&&myszka.x<12*args->X_kratka&&myszka.y>3*args->Y_kratka&&myszka.y<4*args->Y_kratka);}
bool Gra::jest_nad_brzuch(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>10*args->X_kratka&&myszka.x<12*args->X_kratka&&myszka.y>4*args->Y_kratka&&myszka.y<6*args->Y_kratka);}
bool Gra::jest_nad_l_ramie(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>13*args->X_kratka&&myszka.x<17*args->X_kratka&&myszka.y>3*args->Y_kratka&&myszka.y<4*args->Y_kratka)||
(myszka.x>13*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>4*args->Y_kratka&&myszka.y<5*args->Y_kratka);}
bool Gra::jest_nad_p_ramie(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>6*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>3*args->Y_kratka&&myszka.y<4*args->Y_kratka)||
(myszka.x>7*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>4*args->Y_kratka&&myszka.y<5*args->Y_kratka);}
bool Gra::jest_nad_l_dlon(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>13*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>5*args->Y_kratka&&myszka.y<6*args->Y_kratka)||
(myszka.x>14*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>6*args->Y_kratka&&myszka.y<7*args->Y_kratka);}
bool Gra::jest_nad_p_dlon(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>6*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>5*args->Y_kratka&&myszka.y<6*args->Y_kratka)||
(myszka.x>6*args->X_kratka&&myszka.x<8*args->X_kratka&&myszka.y>6*args->Y_kratka&&myszka.y<7*args->Y_kratka);}
bool Gra::jest_nad_l_udo(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>12*args->X_kratka&&myszka.x<15*args->X_kratka&&myszka.y>7*args->Y_kratka&&myszka.y<8*args->Y_kratka)||
(myszka.x>12*args->X_kratka&&myszka.x<14*args->X_kratka&&myszka.y>8*args->Y_kratka&&myszka.y<9*args->Y_kratka);}
bool Gra::jest_nad_p_udo(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>7*args->X_kratka&&myszka.x<10*args->X_kratka&&myszka.y>7*args->Y_kratka&&myszka.y<8*args->Y_kratka)||
(myszka.x>8*args->X_kratka&&myszka.x<10*args->X_kratka&&myszka.y>8*args->Y_kratka&&myszka.y<9*args->Y_kratka);}
bool Gra::jest_nad_p_golen(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>6*args->X_kratka&&myszka.x<10*args->X_kratka&&myszka.y>9*args->Y_kratka&&myszka.y<10*args->Y_kratka)||
(myszka.x>7*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>10*args->Y_kratka&&myszka.y<11*args->Y_kratka);}
bool Gra::jest_nad_l_golen(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>12*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>9*args->Y_kratka&&myszka.y<10*args->Y_kratka)||
(myszka.x>13*args->X_kratka&&myszka.x<15*args->X_kratka&&myszka.y>10*args->Y_kratka&&myszka.y<11*args->Y_kratka);}

bool Gra::jest_nad_strzalka_prawo(ALLEGRO_MOUSE_STATE myszka)
{
         return myszka.x>args->p_pozycja_x+(args->p_poprawka+args->X_kratka)*2&&myszka.x<args->p_pozycja_x+(args->p_poprawka+args->X_kratka)*2+args->X_kratka&&
         myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+args->p_poprawka+args->p_poprawka+args->Y_kratka&&
         myszka.y<args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+args->p_poprawka+args->p_poprawka+args->Y_kratka+args->Y_kratka;
}
bool Gra::jest_nad_strzalka_dol(ALLEGRO_MOUSE_STATE myszka)
{
         return myszka.x>args->p_pozycja_x+args->p_poprawka+args->X_kratka&&myszka.x<args->X_kratka+args->p_pozycja_x+args->p_poprawka+args->X_kratka
         &&myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+(args->p_poprawka+args->Y_kratka)*2&&
         myszka.y<args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+(args->p_poprawka+args->Y_kratka)*2+args->Y_kratka;
}
bool Gra::jest_nad_strzalka_lewo(ALLEGRO_MOUSE_STATE myszka)
{
         return myszka.x>args->p_pozycja_x&&myszka.x<args->X_kratka+args->p_pozycja_x
         &&myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+args->p_poprawka+args->p_poprawka+args->Y_kratka&&
         myszka.y<args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+args->p_poprawka+args->p_poprawka+args->Y_kratka+args->Y_kratka;
}
bool Gra::jest_nad_strzalka_gora(ALLEGRO_MOUSE_STATE myszka)
{
         return myszka.x>args->p_pozycja_x&&myszka.x<args->X_kratka+args->p_pozycja_x+args->X_kratka
         &&myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+args->p_poprawka&&myszka.y<args->Y_kratka+args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4+args->p_poprawka;
}

void Gra::message(struct dla_grafiki*args,short a)
{
       if(a==1)
       {
                args->wiadomosc = 1; ALLEGRO_MOUSE_STATE myszka;
                while(true)
                {
                        al_get_mouse_state(&myszka);
                        if(myszka.buttons&2 && myszka.x>args->X_kratka*7 && myszka.x<args->X_kratka*13 && myszka.y>args->Y_kratka*7 && myszka.y>args->Y_kratka*8)
                            poczekaj_na_myszke(2);
                        al_rest(0.01);
                }
                args->wiadomosc = 0;
       }
}

int Gra:: Menu(int x, int y, struct dla_grafiki*args, struct specyfikacja_menu* menu)
{
         ALLEGRO_KEYBOARD_STATE klawiatura; ALLEGRO_MOUSE_STATE myszka;

         struct punkt gdzie; gdzie=Gdzie_menu(x,y,false,args,menu->ilosc);
         args->ktore_menu=menu->ktore;
          args->wmx=gdzie.x; args->wmy=gdzie.y; args->menu=true;
         int wybor=0;

         while(true)
         {
                  al_get_keyboard_state(&klawiatura);
                  al_get_mouse_state(&myszka);
                  menu_glowne:
                  if(myszka.buttons & 1 || myszka.buttons & 2)
                  {
                           poczekaj_na_myszke(1); poczekaj_na_myszke(2);
                           wybor=ktora_opcja(gdzie.x, gdzie.y, menu->ilosc, myszka.x, myszka.y, args);
                           if(wybor==0) {koncz_z_menami(args);return 0;}
                           if((menu->item[wybor-1])->ilosc==0)
                           {
                                    koncz_z_menami(args);return (menu->item[wybor-1])->ktore;
                           }
                           else
                           {
                                    specyfikacja_menu * submenu_1 = *(menu->item+wybor-1);
                                    if(menu->ktore>=11 && menu->ktore<=15){menu->ktore=wybor+11;args->ktore_menu=menu->ktore;}
                                    else if(menu->ktore>=52 && menu->ktore<=54){menu->ktore=wybor+52;args->ktore_menu=menu->ktore;}
                                    else if(menu->ktore>=20 && menu->ktore<=22){menu->ktore=20;if(wybor==1)menu->ktore+=1;if(wybor==4)menu->ktore+=2;args->ktore_menu=menu->ktore;}
                                    else if(menu->ktore>=29 && menu->ktore<=33){menu->ktore=wybor+29;args->ktore_menu=menu->ktore;}
                                    else if(menu->ktore>=34 && menu->ktore<=36){menu->ktore=wybor+34;args->ktore_menu=menu->ktore;}
                                    else if(menu->ktore>=37 && menu->ktore<=38){menu->ktore=wybor+37;args->ktore_menu=menu->ktore;}

                                    //if(args->submenu && args->ktore_sub_menu==submenu_1 ->ktore) args->submenu=false;
                                    //else
                                    {
                                             punkt gdzie_s; gdzie_s=Gdzie_menu(gdzie.x,gdzie.y+args->menu_y*(wybor-1),true,args,submenu_1->ilosc);
                                             args->ktore_sub_menu=submenu_1->ktore; args->wsmx=gdzie_s.x; args->wsmy=gdzie_s.y; args->submenu=true;

                                             while(true)
                                             {
                                                      al_get_keyboard_state(&klawiatura);
                                                      al_get_mouse_state(&myszka);
                                                      if(myszka.buttons & 1 || myszka.buttons & 2)
                                                      {
                                                               poczekaj_na_myszke(1); poczekaj_na_myszke(2);
                                                               int wybor_s=ktora_opcja(gdzie_s.x, gdzie_s.y, submenu_1->ilosc, myszka.x, myszka.y, args);
                                                               if(wybor_s==0)
                                                               {
                                                                        goto menu_glowne;
                                                                        //koncz_z_menami(args);return 0;
                                                               }
                                                               if(submenu_1->item[wybor_s-1]->ilosc==0)
                                                               {
                                                                        koncz_z_menami(args);return submenu_1->item[wybor_s-1]->ktore;
                                                               }
                                                               else
                                                               {
                                                                        std::cout<<"nie zaiplementowano potrojnych i wiecej menu";
                                                                        throw "nie zaiplementowano potrojnych i wiecej menu";
                                                               }

                                                      }
                                                      else if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))
                                                      {
                                                               while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))break;}
                                                               koncz_z_menami(args); return 0;
                                                      }


                                                      al_rest(0.01);
                                             }
                                    }
                           }

                  }
                  else if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))
                  {
                           while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))break;}
                           koncz_z_menami(args); return 0;
                  }



                  al_rest(0.01);
         }
         ///wywieszamy flage uwazajac na rozdzielczosc i menu
}




int Gra::wersjal; int Gra::wersjap;

void* Obliczanie_grafiki(ALLEGRO_THREAD *thr,void * arg)
{
         struct dla_grafiki* args = (struct dla_grafiki*) arg;
         Swiat* swiat = (Swiat*)args->world;
         Gracz*ggg;
         short xxx,yyy ,zzz;

         struct z_planszy *plansza1=args->plansza1, *plansza2=args->plansza2,*acc;
         Plansza *p1,*accu,*lewo, *prawo, *gora, *dol;
         Objekt *ten;

         while(true)
         {
                  if(args->melduj_grafike) std::cout<<"1";
                  ggg=swiat->aktualny;
                  args->czas=swiat->czas;
                  args->nat_osw = swiat->getJasnosc();
                  Skrzynka *&lewa=Gra::gra->lewa, *&prawa=Gra::gra->prawa;
                  swiat->aktualny->otwarta = lewa;
                  if(ggg) args->punkty_ruchu=ggg->p_ruchu;else args->punkty_ruchu=0;
                  args->pogoda=swiat->pogoda;

                  if(args->koniec_sterowania) break;

                  if(!args->zostala_przesunieta && ggg)
                  {if(args->pp) args->way[0]=true; else args->way[0]=false;
                  if(args->dd) args->way[1]=true; else args->way[1]=false;
                  if(args->ll) args->way[2]=true; else args->way[2]=false;
                  if(args->gg) args->way[3]=true; else args->way[3]=false;}
                  if(args->melduj_grafike) std::cout<<"2";

                  int* aaaa = ggg->worn_items_graphics();//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                  args->p_buty=aaaa[0];
                  args->p_plecak=aaaa[1];
                  args->p_glowa=aaaa[2];
                  args->p_spodnie=aaaa[3];
                  args->p_ramie=aaaa[4];
                  args->p_rece=aaaa[5];
                  args->p_rekawice=aaaa[6];
                  args->p_korpus=aaaa[7];
                  args->p_kieszenl=aaaa[8];
                  args->p_kieszenp=aaaa[9];

                  if(ggg){Gracz*g=ggg;args->kondycja=g->kondycja;
                  args->woda_a=g->woda_a,args->jedzenie_max=g->jedzenie_max, args->jedzenie_a=g->jedzenie_a,args->cieplo_max=g->cieplo_max,
                  args->woda_max=g->woda_max,args->cieplo_a=g->cieplo_a,args->energia_max=g->energia_max, args->energia_a=g->energia_a;
                   args->klatka_max=g->klatka_max, args->klatka_a=g->klatka_a, args->brzuch_max=g->brzuch_max, args->brzuch_a=g->brzuch_a,
                   args->l_ramie_max=g->l_ramie_max,args->l_ramie_a=g->l_ramie_a, args->p_ramie_max=g->p_ramie_max, args->p_ramie_a=g->p_ramie_a,
                   args->l_dlon_max=g->l_dlon_max, args->l_dlon_a=g->l_dlon_a, args->p_dlon_max=g->p_dlon_max, args->p_dlon_a=g->p_dlon_a
                  , args->l_udo_max=g->l_udo_max, args->l_udo_a=g->l_udo_a, args->p_udo_max=g->p_udo_max, args->p_udo_a=g->p_udo_a, args->l_golen_max=g->l_golen_max, args->l_golen_a=g->l_golen_a,
                  args->p_golen_max=g->p_golen_max, args->p_golen_a=g->p_golen_a;}
                  if(args->melduj_grafike) std::cout<<"3";

                  if(args->otwarty_ekwipunek)
                  {
                           if(lewa && Gra::wersjal!=lewa->getWersja())
                           {
                                    Gra::wersjal=lewa->getWersja();
                                    args->skrzynki.aktualizuj_lewo(lewa->raport_obrazkowy());
                           }
                           if(prawa && Gra::wersjap!=prawa->getWersja())
                           {
                                    Gra::wersjap=prawa->getWersja();
                                    args->skrzynki.aktualizuj_prawo(prawa->raport_obrazkowy());
                           }///bezpiecznie bo po usunieciu skrzynki nie powinno byc woli jej narysowania
                 }
                  else
                  {
                           args->skrzynki.reset();

                           p1=swiat->aktualna;
                           for(int l=0;l<2;l++)
                           {
                                    switch(l){case 0:acc=plansza1;accu=p1;break;case 1:acc=plansza2;accu=(Plansza*)(args->plansza_docelowa);break;}
                                    if(l==1 && !args->przesuwamy_plansze) {break;}

                                    prawo=swiat->zwroc_taka_plansze(accu->x+1, accu->y, accu->z);
                                    lewo=swiat->zwroc_taka_plansze(accu->x-1, accu->y, accu->z);
                                    gora=swiat->zwroc_taka_plansze(accu->x, accu->y-1, accu->z);
                                    dol=swiat->zwroc_taka_plansze(accu->x, accu->y+1, accu->z);
                                    if(args->melduj_grafike) std::cout<<"4";

                                    xxx = accu->x,yyy = accu->y,zzz = accu->z;
                                    acc->b_akt =accu->getBiom();
                                    acc->b_right  = swiat->zwroc_taka_aree(xxx+1, yyy, zzz) ? swiat->zwroc_taka_aree(xxx+1, yyy, zzz)->getBiom() : acc->b_akt;
                                    acc->b_left  = swiat->zwroc_taka_aree(xxx-1, yyy, zzz) ? swiat->zwroc_taka_aree(xxx-1, yyy, zzz)->getBiom() : acc->b_akt;
                                    acc->b_high  = swiat->zwroc_taka_aree(xxx, yyy-1, zzz) ? swiat->zwroc_taka_aree(xxx, yyy-1, zzz)->getBiom() : acc->b_akt;
                                    acc->b_down  = swiat->zwroc_taka_aree(xxx, yyy+1, zzz) ? swiat->zwroc_taka_aree(xxx, yyy+1, zzz)->getBiom() : acc->b_akt;
                                    //std::cout<<acc->b_down<<std::endl;

                                   if(!prawo || args->przesuwamy_plansze) {for(int j=0; j<14; j++) {acc->stany_obiektow[j][22]=0;acc->stany_srodowisk[j][22]=0;acc->otoczenie[j][22][0]=0;acc->srodowisko[j][22][0]=0;acc->oswietlenie[j][22] = swiat->getJasnosc();}}
                                    else {for(int j=1; j<14; j++){
                                                      ten = prawo->otoczenie[j-1][0];
                                                      if(ten==NULL || !ten->exists()){acc->otoczenie[j][22][0]=0;acc->stany_obiektow[j][22]=0;}
                                                      else {acc->otoczenie[j][22][0]=ten->get_co_to();acc->stany_obiektow[j][22]=ten->stan;}
                                                      if(prawo->srodowisko[j-1][0]==NULL){acc->srodowisko[j][22][0]=0;acc->stany_srodowisk[j][22]=0;}
                                                      else {od_srodowiska a = prawo->srodowisko[j-1][0]->rysunek(); acc->srodowisko[j][22][0]=a.rys;acc->stany_srodowisk[j][22]=a.stan;}
                                                      acc->oswietlenie[j][22] = prawo->oswietlenie[j-1][0];
                                    }}
                                    if(!lewo || args->przesuwamy_plansze) {for(int j=0; j<14; j++) {acc->stany_srodowisk[j][0]=0;acc->stany_obiektow[j][0]=0;acc->otoczenie[j][0][0]=0;acc->srodowisko[j][0][0]=0;acc->oswietlenie[j][0] = swiat->getJasnosc();}}
                                   else {for(int j=1; j<14; j++) {
                                             ten = lewo->otoczenie[j-1][20];
                                             if(ten==NULL || !ten->exists()){acc->otoczenie[j][0][0]=0;acc->stany_obiektow[j][0]=0;}
                                             else {acc->otoczenie[j][0][0]=ten->get_co_to();acc->stany_obiektow[j][0]=ten->stan;}
                                             if(lewo->srodowisko[j-1][20]==NULL){acc->srodowisko[j][0][0]=0;acc->stany_srodowisk[j][0]=0;}
                                             else {od_srodowiska a =lewo->srodowisko[j-1][20]->rysunek(); acc->srodowisko[j][0][0]=a.rys;acc->stany_srodowisk[j][0]=a.stan;}
                                             acc->oswietlenie[j][0] = lewo->oswietlenie[j-1][20];
                                   }}
                                    if(!gora || args->przesuwamy_plansze) {for(int j=1; j<22; j++) {acc->stany_srodowisk[0][j]=0;acc->stany_obiektow[0][j]=0;acc->otoczenie[0][j][0]=0;acc->srodowisko[0][j][0]=0;acc->oswietlenie[0][j] = swiat->getJasnosc();}}
                                    else {for(int j=1; j<22; j++) {
                                             ten = gora->otoczenie[12][j-1];
                                             if(ten==NULL || !ten->exists()){acc->otoczenie[0][j][0]=0;acc->stany_obiektow[0][j]=0;}
                                             else {acc->otoczenie[0][j][0]=ten->get_co_to();acc->stany_obiektow[0][j]=ten->stan;}
                                             if(gora->srodowisko[12][j-1]==NULL){acc->srodowisko[0][j][0]=0;acc->stany_srodowisk[0][j]=0;}
                                             else {od_srodowiska a = gora->srodowisko[12][j-1]->rysunek();acc->srodowisko[0][j][0]=a.rys;acc->stany_srodowisk[0][j]=a.stan;}
                                             acc->oswietlenie[0][j] = gora->oswietlenie[12][j-1];
                                    }}
                                    if(!dol || args->przesuwamy_plansze) {for(int j=1; j<22; j++) {acc->stany_obiektow[14][j]=0;acc->stany_srodowisk[14][j]=0;acc->otoczenie[14][j][0]=0;acc->srodowisko[14][j][0]=0;acc->oswietlenie[14][j]=swiat->getJasnosc();}}
                                    else {for(int j=1; j<22; j++) {
                                             ten = dol->otoczenie[0][j-1];
                                             if(ten==NULL || !ten->exists()){acc->otoczenie[14][j][0]=0;acc->stany_obiektow[14][j]=0;}
                                             else {acc->otoczenie[14][j][0]=ten->get_co_to();acc->stany_obiektow[14][j]=ten->stan;}
                                             if(dol->srodowisko[0][j-1]==NULL){acc->srodowisko[14][j][0]=0;acc->stany_srodowisk[14][j]=0;}
                                             else {od_srodowiska a = dol->srodowisko[0][j-1]->rysunek(); acc->srodowisko[14][j][0]=a.rys;acc->stany_srodowisk[14][j]=a.stan;}
                                             acc->oswietlenie[14][j] = dol->oswietlenie[0][j-1];

                                    }}
                                    if(args->melduj_grafike) std::cout<<"5";
                                    acc->oswietlenie[0][0]=swiat->getJasnosc(); acc->oswietlenie[14][22]=swiat->getJasnosc(); acc->oswietlenie[0][22]=swiat->getJasnosc();acc->oswietlenie[14][0]=swiat->getJasnosc();

                                    acc->podlogi = accu->floors;

                                    for(int i=0;i<23;++i){for(int j=0;j<15;++j){acc->upadli[j][i]=0;}}

                                    std::vector<std::shared_ptr<Upadly>> upadl(accu->daj_wskazniki_do_upadlych());
                                    for(std::vector<std::shared_ptr<Upadly>>::iterator it = upadl.begin(); it!=upadl.end(); ++it)
                                    {
                                             acc->upadli[(**it).getY()+1][(**it).getX()+1]=(**it).getA()->get_co_to();
                                    }

                                    for(int i=1; i<14; i++)
                                    {
                                             for(int j=1; j<22; j++)
                                             {
                                                      ten = accu->otoczenie[i-1][j-1];
                                                      if(ten==NULL || !ten->exists()) {acc->otoczenie[i][j][0]=0;
                                                               acc->przesuniecie[i][j].x=0;
                                                               acc->przesuniecie[i][j].y=0;
                                                               acc->stany_obiektow[i][j]=0;
                                                               acc->oszolomiony[i-1][j-1]=false;}
                                                      else
                                                      {
                                                               acc->otoczenie[i][j][0]=ten->get_co_to();
                                                               acc->przesuniecie[i][j].x=ten->przesuniecie_x;
                                                               acc->przesuniecie[i][j].y=ten->przesuniecie_y;

                                                               acc->stany_obiektow[i][j]=ten->stan;
                                                               acc->oszolomiony[i-1][j-1] = ten->zywy ? ((Objekt_zywy*)ten)->oszolomiony() : false;
                                                       }
                                                      if(accu->srodowisko[i-1][j-1]==NULL) {acc->srodowisko[i][j][0]=0;acc->stany_srodowisk[i][j]=0;}
                                                      else
                                                      {
                                                      od_srodowiska a = accu->srodowisko[i-1][j-1]->rysunek();
                                                      acc->stany_srodowisk[i][j]=a.stan;
                                                      acc->przesuniecie_srodowisk[i][j].x=a.przesuniecie_x;
                                                      acc->przesuniecie_srodowisk[i][j].y=a.przesuniecie_y;
                                                      acc->srodowisko[i][j][0]=a.rys;
                                                      }

                                                      acc->ziemia[i][j]=accu->ziemia[i-1][j-1]!=NULL;
                                                      acc->oswietlenie[i][j] = accu->oswietlenie[i-1][j-1];

                                             }
                                    }
                                    if(args->melduj_grafike) std::cout<<"6";
                           }int i;
                           if(ggg)
                           {
                                    Gracz*g=ggg;

                                    std::vector<punkt> zablokowani = ggg->blokowani();
                                    short ile = zablokowani.size()<19 ? zablokowani.size() : 18;
                                    short i=0;
                                    args->bloki[ile].x = -1;
                                    for(std::vector<punkt>::iterator it = zablokowani.begin(); it!=zablokowani.end(); ++it)
                                    {
                                             if(i>=ile) break;
                                             args->bloki[i].y=(*it).y; args->bloki[i].x=(*it).x;
                                             ++i;
                                    }

                                    std::vector<punkt> unikani = ggg->unikani();
                                    ile = unikani.size()<19 ? unikani.size() : 18;
                                    i=0;
                                    args->uniki[ile].x = -1;
                                    for(std::vector<punkt>::iterator it = unikani.begin(); it!=unikani.end(); ++it)
                                    {
                                             if(i>=ile) break;
                                             args->uniki[i].y=(*it).y; args->uniki[i].x=(*it).x;
                                             ++i;
                                    }

                                    std::vector<punkt> skupiani = ggg->skupiani();
                                    ile = skupiani.size()<19 ? skupiani.size() : 18;
                                    i=0;
                                    args->skupienia[ile].x = -1;
                                    for(std::vector<punkt>::iterator it = skupiani.begin(); it!=skupiani.end(); ++it)
                                    {
                                             if(i>=ile) break;
                                             args->skupienia[i].y=(*it).y; args->skupienia[i].x=(*it).x;
                                             ++i;
                                    }
                           }
                           else
                           {
                                    args->skupienia[0].x=-1;
                                    args->uniki[0].x=-1;
                                    args->bloki[0].x=-1;
                           }
                  }

                  al_rest(0.02);
         }
         args->skonczylem_sterowac=true;
}



Item* Gra::uzyj(Item*a)
{
         ALLEGRO_MOUSE_STATE myszka; ALLEGRO_KEYBOARD_STATE klawiatura; Gracz*g=swiat->aktualny;
         switch(a->czym_jest)
         {
                  case 2003: {dodaj_wody(50);delete a; return Item::stworz_obiekt(2003);}break;
                  case 2004: {dodaj_wody(50); delete a; return Item::stworz_obiekt(2005);}break;
                  case 2009: {dodaj_wody(50); dodaj_jedzenia(-losuj(10, 80)); delete a; return Item::stworz_obiekt(2010);}break;
                  case 2010: {dodaj_wody(50); dodaj_jedzenia(-losuj(10, 80)); delete a; return Item::stworz_obiekt(2005);}break;

                  case 2001: {dodaj_jedzenia(50);return NULL;}break;
                  //case 2011: {dodaj_jedzenia();return NULL;}break;
                  case 2012: {dodaj_jedzenia(((Konsumpcjum*)a)->get_uzycia());return NULL;}break;
                  //case 2013: {dodaj_jedzenia();return NULL;}break;
                  case 2014: {dodaj_jedzenia(((Konsumpcjum*)a)->get_uzycia());return NULL;}break;
                  case 2006: {dodaj_wody(50);return NULL;}break;
                  case 2007:
                  {
                           poczekaj_na_myszke(1);
                           args->otwarte_menu_anatomii=true;
                           args->p_nr_przedmiotu=a->czym_jest;
                           int roznica_x=args->X_kratka/2,
                           roznica_y=args->Y_kratka/2;
                           while(true)
                           {
                                    args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if((myszka.buttons&1)) break;
                           }
                           args->p_nr_przedmiotu=0;
                           if(jest_nad_klatka(myszka) && g->klatka_a<g->klatka_max){g->klatka_a+=20; if(g->klatka_a>g->klatka_max)g->klatka_a=g->klatka_max;delete a;a=NULL;}
                           else if(jest_nad_brzuch(myszka) && g->brzuch_a<g->brzuch_max){g->brzuch_a+=20; if(g->brzuch_a>g->brzuch_max)g->brzuch_a=g->brzuch_max;delete a;a=NULL;}
                           else if( jest_nad_l_ramie(myszka) && g->l_ramie_a<g->l_ramie_max){g->l_ramie_a+=20; if(g->l_ramie_a>g->l_ramie_max)g->l_ramie_a=g->l_ramie_max;delete a;a=NULL;}
                           else if( jest_nad_p_ramie(myszka) && g->p_ramie_a<g->p_ramie_max){g->p_ramie_a+=20; if(g->p_ramie_a>g->p_ramie_max)g->p_ramie_a=g->p_ramie_max;delete a;a=NULL;}
                           else if( jest_nad_l_dlon(myszka) && g->l_dlon_a<g->l_dlon_max){g->l_dlon_a+=20; if(g->l_dlon_a>g->l_dlon_max)g->l_dlon_a=g->l_dlon_max;delete a;a=NULL;}
                           else if( jest_nad_p_dlon(myszka) && g->p_dlon_a<g->p_dlon_max){g->p_dlon_a+=20; if(g->p_dlon_a>g->p_dlon_max)g->p_dlon_a=g->p_dlon_max;delete a;a=NULL;}
                           else if( jest_nad_l_udo(myszka) && g->l_udo_a<g->l_udo_max){g->l_udo_a+=20; if(g->l_udo_a>g->l_udo_max)g->l_udo_a=g->l_udo_max;delete a;a=NULL;}
                           else if( jest_nad_p_udo(myszka) && g->p_udo_a<g->p_udo_max){g->p_udo_a+=20; if(g->p_udo_a>g->p_udo_max)g->p_udo_a=g->p_udo_max;delete a;a=NULL;}
                           else if( jest_nad_l_golen(myszka) && g->l_golen_a<g->l_golen_max){g->l_golen_a+=20; if(g->l_golen_a>g->l_golen_max)g->l_golen_a=g->l_golen_max;delete a;a=NULL;}
                           else if( jest_nad_p_golen(myszka) && g->p_golen_a<g->p_golen_max){g->p_golen_a+=20; if(g->p_golen_a>g->p_golen_max)g->p_golen_a=g->p_golen_max;delete a;a=NULL;}
                           Sleep(750);
                           args->otwarte_menu_anatomii=false;
                           return a;
                  }break;
                  case 2101: {return zaladuj_bron(4252,(Konsumpcjum*)a);}break;
                  case 4252: {return rozladuj_bron((Bron*)a,2101);}break;
                  case 2102: {return zaladuj_bron(4752,(Konsumpcjum*)a);}break;
                  case 4752: {return rozladuj_bron((Bron*)a,2102);}break;
                  case 2103: {return zaladuj_bron(4753,(Konsumpcjum*)a, 4260);}break;
                  case 4753: {return rozladuj_bron((Bron*)a,2103);}break;
                  case 4260: {return rozladuj_bron((Bron*)a,2103);}break;
                  case 2104:{return zaladuj_bron(4255,(Konsumpcjum*)a,4256);}break;
                  case 4255:
                           {if(((Bron*)a)->mag>0)return rozladuj_bron((Bron*)a,2104);
                           daj_aktualnemu_item(Item::stworz_obiekt(8003));Bron*b=new Bron(4256),*k=(Bron*)a; b->mag=k->mag; delete k; daj_aktualnemu_item(b); return NULL;
                           }break;
                  case 4256: {return rozladuj_bron((Bron*)a,2104);}break;
                  case 8003: {return zamien_jeden_na_drugi_za_pomoca_tego(4255,4256,a);}break;
                  case 8004:{
                  bool ekw=args->otwarty_ekwipunek;



                  args->otwarty_ekwipunek=ekw;
                  }break;
                  case 8017:
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           if(swiat->aktualna==swiat->zwroc_taka_aree(g->px, g->py, g->pz) && Strefa::w_planszy(aaa.x, aaa.y) && Objekt::zaraz_obok(g->x, g->y, aaa.x, aaa.y) && pobierz_punkty_ruchu(3))
                           {
                                    swiat->aktualna->iskra(aaa.x, aaa.y);
                                    if(((Konsumpcjum*)a)->wykorzystaj())
                                             {delete a;przywroc_ekw();return NULL;}
                                    else {przywroc_ekw();return a;}
                           }
                           przywroc_ekw();
                           return a;
                  }break;
                  case 8018:
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           if(swiat->aktualna==swiat->zwroc_taka_aree(g->px, g->py, g->pz) && Strefa::w_planszy(aaa.x, aaa.y) && g->mozna_rzucic(aaa.x, aaa.y) && pobierz_punkty_ruchu(3))
                           {
                                    g->animacja_rzutu_przedmiotu(args,aaa.x, aaa.y, a);
                                    swiat->aktualna->wybuch_o_mocy(3, aaa.x, aaa.y);
                                    delete a;
                                    przywroc_ekw();
                                    return NULL;
                           }
                           przywroc_ekw();
                           return a;
                  }break;
                  case 8019:
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           if(swiat->aktualna==swiat->zwroc_taka_aree(g->px, g->py, g->pz) && Strefa::w_planszy(aaa.x, aaa.y) && g->mozna_rzucic(aaa.x, aaa.y) && pobierz_punkty_ruchu(3))
                           {
                                    g->animacja_rzutu_przedmiotu(args,aaa.x, aaa.y, a);
                                    swiat->aktualna->podpalenie_o_mocy(3, aaa.x, aaa.y, 5);
                                    delete a;
                                    przywroc_ekw();
                                    return NULL;
                           }
                           przywroc_ekw();
                           return a;
                  }break;

                  default: return a;
         }
}

Item* Gra::zamien_jeden_na_drugi_za_pomoca_tego(int jaki,int z_jakiego,Item*a)
{
         poczekaj_na_myszke(1); ALLEGRO_MOUSE_STATE myszka; Gracz*g=swiat->aktualny;
         args->p_nr_przedmiotu=a->get_co_to();int roznica_x=args->X_kratka/2,roznica_y=args->Y_kratka/2;
         while(true){args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if((myszka.buttons&1)) {poczekaj_na_myszke(1);break;}}args->p_nr_przedmiotu=0;
         if(jest_nad_ramieniem(myszka) && g->p_ramie!=NULL && g->p_ramie->czym_jest==z_jakiego){Item*b=Item::stworz_obiekt(jaki),*k=g->p_ramie;
         //b->mag=k->mag;
         g->p_ramie=b;delete k;delete a; return NULL;}
         else if(jest_nad_rekami(myszka) && g->p_rece!=NULL && g->p_rece->czym_jest==z_jakiego){Item*b=Item::stworz_obiekt(jaki),*k=g->p_rece;
         //b->mag=k->mag;
         g->p_rece=b; delete k;delete a; return NULL;}
         else if(jest_nad_lewa(myszka) && lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)!=NULL &&
         lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)->item->czym_jest==z_jakiego)
         {
                  Przedmiot*k=lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z);
                  Item*b=Item::stworz_obiekt(jaki);
                  //b->mag=((Bron*)k->item)->mag;
                  lewa->wyjmij_przedmiot(k);delete k;delete a;Przedmiot*j=new Przedmiot(b); if(lewa->wloz_przedmiot(j)); else {delete j;daj_aktualnemu_item(b);}return NULL;
         }
         else if(jest_nad_prawa(myszka) && prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)!=NULL &&
         prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)->item->czym_jest==z_jakiego)
         {
                  Przedmiot*k=prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p);
                  Item*b=Item::stworz_obiekt(jaki);
                  //b->mag=((Bron*)k->item)->mag;
                  prawa->wyjmij_przedmiot(k);delete k;delete a;Przedmiot*j=new Przedmiot(b); if(prawa->wloz_przedmiot(j)); else {delete j;daj_aktualnemu_item(b);} return NULL;
         }
         else return a;
}

Item* Gra::rozladuj_bron(Bron*a, int nr_mag)
{
         if(a->mag<=0)return a;
         a->mag=0;
         daj_aktualnemu_item(a);
         return new Konsumpcjum(nr_mag,a->mag);
}

Item* Gra::zaladuj_bron(int jej_nr, Konsumpcjum*a,int zapas)
{
         Gracz*g=swiat->aktualny;
         poczekaj_na_myszke(1); ALLEGRO_MOUSE_STATE myszka;
         args->p_nr_przedmiotu=a->get_co_to();int roznica_x=args->X_kratka/2,roznica_y=args->Y_kratka/2;
         while(true)
         {
                  args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if((myszka.buttons&1)) {poczekaj_na_myszke(1);break;}
         }
         args->p_nr_przedmiotu=0;
         if(jest_nad_ramieniem(myszka) && g->p_ramie!=NULL && (g->p_ramie->czym_jest==jej_nr||g->p_ramie->czym_jest==zapas)&&((Bron*)g->p_ramie)->mag<=0){ ((Bron*)g->p_ramie)->mag=a->get_uzycia();delete a;return NULL;}
         else if(jest_nad_rekami(myszka) && g->p_rece!=NULL && (g->p_rece->czym_jest==jej_nr||g->p_rece->czym_jest==zapas)&&((Bron*)g->p_rece)->mag<=0){ ((Bron*)g->p_rece)->mag=a->get_uzycia();delete a;return NULL;}
         else if(jest_nad_lewa(myszka) && lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)!=NULL &&
         (lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)->item->czym_jest==jej_nr||
          lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)->item->czym_jest==zapas)
                 &&((Bron*)lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)->item)->mag<=0)
         {
                  ((Bron*)lewa->przedmiot((myszka.x-15*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_z)->item)->mag=a->get_uzycia();
                  delete a;  return NULL;
         }
         else if(jest_nad_prawa(myszka) && prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)!=NULL &&
         (prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)->item->czym_jest==jej_nr||
          prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)->item->czym_jest==zapas)&&
                 ((Bron*)prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)->item)->mag<=0)
         {
                  ((Bron*)prawa->przedmiot((myszka.x-125*args->X_kratka/10)/args->X_kratka, (myszka.y-15*args->Y_kratka/10)/args->Y_kratka+args->eq_przesuiniecie_p)->item)->mag=a->get_uzycia();
                  delete a; return NULL;
         }
         else
         {
                   return a;
         }
}

void Gra::daj_aktualnemu_item(Item*a)
{
         Gracz*g=swiat->aktualny;
         if(g->p_rece==NULL) g->p_rece=a;
         else if(g->p_plecak!=NULL && ((Plecak*)g->p_plecak)->s->wloz_przedmiot(new Przedmiot(a)));
         else if(args->otwarty_ekwipunek && lewa!=NULL && lewa->wloz_przedmiot(new Przedmiot(a)));
         else
         {
                  Plansza*p=swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);
                  if(p->ziemia[g->y][g->x]==NULL)p->ziemia[g->y][g->x]=new Kontener<Item>();
                  p->ziemia[g->y][g->x]->dodaj_obiekt(a);
         }
}

bool Gra::jest_nad_lewa(ALLEGRO_MOUSE_STATE myszka)
{
         return args->otwarty_ekwipunek && lewa!=NULL &&myszka.x>args->X_kratka && myszka.x<(lewa->x+1)*args->X_kratka &&
         myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka && myszka.y<(lewa->y+1-args->eq_przesuiniecie_z)*args->Y_kratka;
}

bool Gra::jest_nad_prawa(ALLEGRO_MOUSE_STATE myszka)
{
         return args->otwarty_ekwipunek && prawa!=NULL &&myszka.x>12*args->X_kratka && myszka.x<(prawa->x+12)*args->X_kratka &&
         myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka && myszka.y<(prawa->y+1-args->eq_przesuiniecie_p)*args->Y_kratka;
}

int Gra::ile_czasu_spac()
{
         ALLEGRO_MOUSE_STATE myszka;
         args->ile_spac=1; args->menu_spania=true; poczekaj_na_myszke(1);
         while(true)
         {
                  al_get_mouse_state(&myszka);
                  if(myszka.buttons&1)
                  {
                           poczekaj_na_myszke(1);
                           if(myszka.x>args->X_kratka*14 && myszka.x<args->X_kratka*15&&
                                    myszka.y>6*args->Y_kratka && myszka.y<7*args->Y_kratka){break;}
                           else if(myszka.x>args->X_kratka*13 && myszka.x<args->X_kratka*14&&
                                    myszka.y>6*args->Y_kratka && myszka.y<7*args->Y_kratka){if(args->ile_spac>0)--args->ile_spac;continue;}
                           else if(myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*13&&
                                    myszka.y>6*args->Y_kratka && myszka.y<7*args->Y_kratka){if(args->ile_spac<10)++args->ile_spac;continue;}
                           else if(myszka.x>args->X_kratka*9 && myszka.x<args->X_kratka*16&&
                                    myszka.y>5*args->Y_kratka && myszka.y<8*args->Y_kratka) continue;
                           else {args->ile_spac=0; break;}
                  }
                  al_rest(0.02);
         }
         args->menu_spania=false;
         return args->ile_spac;
}

void Gra::spij(int gdzie, Objekt_martwy *na_czym)///funkcja pozostawia gracza spiacego, wszystko inne dzieje sie w swiecie
{
         if(na_czym->czym_jest==25) ((Szalas*)na_czym)->przespij_sie_w(ile_czasu_spac()*60, swiat->aktualny);
         else if(na_czym->czym_jest==32) ((Lozko*)na_czym)->przespij_sie_w(ile_czasu_spac()*60, swiat->aktualny);
}

void Gra::opcje_zawsze_dostepne(struct dla_grafiki* arg)
{
         ALLEGRO_MOUSE_STATE myszka;
         ALLEGRO_KEYBOARD_STATE klawiatura;
          al_get_mouse_state(&myszka);
         al_get_keyboard_state(&klawiatura);
         if(al_key_down(&klawiatura, ALLEGRO_KEY_Z))
         {
                 arg->screen=true;
         }

}

bool Gra::jest_nad_ramieniem(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x && myszka.x<args->p_pozycja_x+args->X_kratka && myszka.y>args->p_pozycja_y && myszka.y<args->p_pozycja_y+args->Y_kratka;}
bool Gra::jest_nad_glowa(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+args->p_poprawka+args->X_kratka && myszka.x<args->p_pozycja_x+args->X_kratka+args->p_poprawka+args->X_kratka && myszka.y>args->p_pozycja_y && myszka.y<args->p_pozycja_y+args->Y_kratka;}
bool Gra::jest_nad_plecakiem(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+(args->p_poprawka+args->X_kratka)*2 && myszka.x<args->p_pozycja_x+args->X_kratka+(args->p_poprawka+args->X_kratka)*2 && myszka.y>args->p_pozycja_y && myszka.y<args->p_pozycja_y+args->Y_kratka;}
bool Gra::jest_nad_rekami(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x && myszka.x<args->p_pozycja_x+args->X_kratka && myszka.y>args->p_pozycja_y+args->p_poprawka+args->Y_kratka && myszka.y<args->p_pozycja_y+args->Y_kratka+args->p_poprawka+args->Y_kratka;}
bool Gra::jest_nad_korpusem(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+args->p_poprawka+args->X_kratka && myszka.x<args->p_pozycja_x+args->X_kratka+args->p_poprawka+args->X_kratka && myszka.y>args->p_pozycja_y+args->p_poprawka+args->Y_kratka && myszka.y<args->p_pozycja_y+args->Y_kratka+args->p_poprawka+args->Y_kratka;}
bool Gra::jest_nad_rekawicami(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+(args->p_poprawka+args->X_kratka)*2 && myszka.x<args->p_pozycja_x+args->X_kratka+(args->p_poprawka+args->X_kratka)*2 && myszka.y>args->p_pozycja_y+args->p_poprawka+args->Y_kratka && myszka.y<args->p_pozycja_y+args->Y_kratka+args->p_poprawka+args->Y_kratka;}
bool Gra::jest_nad_kieszenl(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x && myszka.x<args->p_pozycja_x+args->X_kratka && myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*2 && myszka.y<args->p_pozycja_y+args->Y_kratka+(args->p_poprawka+args->Y_kratka)*2;}
bool Gra::jest_nad_spodniami(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+args->p_poprawka+args->X_kratka && myszka.x<args->p_pozycja_x+args->X_kratka+args->p_poprawka+args->X_kratka && myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*2 && myszka.y<args->p_pozycja_y+args->Y_kratka+(args->p_poprawka+args->Y_kratka)*2;}
bool Gra::jest_nad_kieszenp(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+(args->p_poprawka+args->X_kratka)*2 && myszka.x<args->p_pozycja_x+args->X_kratka+(args->p_poprawka+args->X_kratka)*2 && myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*2 && myszka.y<args->p_pozycja_y+args->Y_kratka+(args->p_poprawka+args->Y_kratka)*2;}
bool Gra::jest_nad_butami(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x+args->p_poprawka+args->X_kratka && myszka.x<args->p_pozycja_x+args->X_kratka+args->p_poprawka+args->X_kratka && myszka.y>args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*3 && myszka.y<args->p_pozycja_y+args->Y_kratka+(args->p_poprawka+args->Y_kratka)*3;}
bool Gra::jest_nad_rzeczami_postaci(ALLEGRO_MOUSE_STATE myszka)
{return myszka.x>args->p_pozycja_x && myszka.x<args->p_pozycja_x+(args->p_poprawka+args->X_kratka)*3 && myszka.y>args->p_pozycja_y && myszka.y<args->p_pozycja_y+(args->p_poprawka+args->Y_kratka)*4;}
bool Gra::jest_nad_rzeczami_konkretnymi(ALLEGRO_MOUSE_STATE myszka)
{return jest_nad_ramieniem(myszka)||jest_nad_glowa(myszka)||jest_nad_plecakiem(myszka)||jest_nad_rekami(myszka)||jest_nad_korpusem(myszka)||jest_nad_rekawicami(myszka)||jest_nad_kieszenl(myszka)||jest_nad_spodniami(myszka)||jest_nad_kieszenp(myszka)||jest_nad_butami(myszka);}


Skrzynka* Gra::otwarty_ekw(ALLEGRO_MOUSE_STATE myszka,
         ALLEGRO_KEYBOARD_STATE klawiatura,dla_grafiki*args, Skrzynka*s)
{
         int f=300;
         Gracz*g=swiat->aktualny;
         g->otwiera=true; Sleep(f);
         args->skrzynki.reset();
         args->p_1=false;args->p_2=false;args->p_3=false;args->p_4=false;

         lewa=s;wersjal=lewa->getWersja()-1;
         bool prawy_to_plecak=false;
         if(g->p_plecak==NULL)prawa=new Skrzynka(0,0);
         else {prawy_to_plecak=true;prawa=((Plecak*)g->p_plecak)->s;}
         wersjap=prawa->getWersja()-1; ///prawym powinien byc plecak


         if(lewa!=NULL && lewa->y>11 )args->p_3=true;if(prawa!=NULL && prawa->y>11 )args->p_4=true;
         args->eq_przesuiniecie_z=0; args->eq_przesuiniecie_p=0;
         int roznica_pola_s,roznica_pola_p;
         if(lewa!=NULL){args->dlugosc_paska_s=(11*args->Y_kratka*9)/lewa->y; args->pozycja_paska_s=0; roznica_pola_s=args->dlugosc_paska_s/11;}
         if(prawa!=NULL){if(prawa->y==0)args->dlugosc_paska_p=(11*args->Y_kratka*9);else args->dlugosc_paska_p=(11*args->Y_kratka*9)/prawa->y; args->pozycja_paska_p=0; roznica_pola_p=args->dlugosc_paska_p/11;}
         args->otwarty_ekwipunek=true; bool zamykamy=false; int ostatnia_myszka=myszka.z,myszka_z=myszka.z, z_s=myszka_z, z_p=myszka_z;
         short dla_funkcji=1;
         bool akt;

         while (true)
         {
                  akt = true;
                  if(zamykamy) break;
                  al_get_mouse_state(&myszka);
                  al_get_keyboard_state(&klawiatura);
                  if(myszka.z!=ostatnia_myszka && ((myszka.x>args->X_kratka && myszka.x<args->X_kratka*11 && myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka)||(myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*22 && myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka)))
                  {
                           myszka_z+=myszka.z-ostatnia_myszka;
                           ostatnia_myszka=myszka.z;
                  }

                  if(al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))
                  {
                           while(true) {al_get_keyboard_state(&klawiatura); if(!al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))break;}
                           break;
                  }
                  else if(myszka.buttons&1 && myszka.x>args->X_kratka*3 && myszka.x<args->X_kratka*8 && myszka.y>12*args->Y_kratka && myszka.y<14*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1);break;
                  }
                  else if(myszka.buttons&1 && myszka.x>args->X_kratka*14 && myszka.x<args->X_kratka*19 && myszka.y>12*args->Y_kratka && myszka.y<14*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); crafting(myszka, klawiatura);
                  }
                  else if(lewa!=NULL && args->eq_przesuiniecie_z>0 && myszka.buttons&1 && myszka.x>args->X_kratka*10 && myszka.x<args->X_kratka*11 && myszka.y>1*args->Y_kratka && myszka.y<2*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); args->pozycja_paska_s-=roznica_pola_s;--args->eq_przesuiniecie_z; if(args->eq_przesuiniecie_z>0) args->p_1=true; else args->p_1=false; args->p_3=true;
                  }
                  else if(myszka_z>z_s && lewa!=NULL && myszka.x>args->X_kratka && myszka.x<args->X_kratka*11 && myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka)
                  {
                           for(;z_s<myszka_z;--myszka_z){if(args->eq_przesuiniecie_z>0) {args->pozycja_paska_s-=roznica_pola_s;--args->eq_przesuiniecie_z; if(args->eq_przesuiniecie_z>0) args->p_1=true; else args->p_1=false; args->p_3=true;}}
                  }
                  else if(prawa!=NULL && args->eq_przesuiniecie_p>0 && myszka.buttons&1 && myszka.x>args->X_kratka*21 && myszka.x<args->X_kratka*22 && myszka.y>1*args->Y_kratka && myszka.y<2*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); args->pozycja_paska_p-=roznica_pola_p;--args->eq_przesuiniecie_p; if(args->eq_przesuiniecie_p>0) args->p_2=true; else args->p_2=false; args->p_4=true;
                  }
                  else if(myszka_z>z_p && prawa!=NULL && myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*22 && myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka)
                  {
                           for(;z_p<myszka_z;--myszka_z){if(args->eq_przesuiniecie_p>0) {args->pozycja_paska_p-=roznica_pola_p;--args->eq_przesuiniecie_p; if(args->eq_przesuiniecie_p>0) args->p_2=true; else args->p_2=false; args->p_4=true;}}
                  }
                  else if(lewa!=NULL && lewa->y-args->eq_przesuiniecie_z>11 && myszka.buttons&1 && myszka.x>args->X_kratka*10 && myszka.x<args->X_kratka*11 && myszka.y>11*args->Y_kratka && myszka.y<12*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); args->pozycja_paska_s+=roznica_pola_s;++args->eq_przesuiniecie_z;if(lewa->y-args->eq_przesuiniecie_z>11) args->p_3=true; else args->p_3=false; args->p_1=true;
                  }
                  else if(myszka_z<z_s && lewa!=NULL && myszka.x>args->X_kratka && myszka.x<args->X_kratka*11 && myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka)
                  {
                           for(;z_s>myszka_z;++myszka_z){if(lewa->y-args->eq_przesuiniecie_z>11) {args->pozycja_paska_s+=roznica_pola_s;++args->eq_przesuiniecie_z;if(lewa->y-args->eq_przesuiniecie_z>11) args->p_3=true; else args->p_3=false; args->p_1=true;}}
                  }
                  else if(prawa!=NULL && prawa->y-args->eq_przesuiniecie_p>11 && myszka.buttons&1 && myszka.x>args->X_kratka*21 && myszka.x<args->X_kratka*22 && myszka.y>11*args->Y_kratka && myszka.y<12*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); args->pozycja_paska_p+=roznica_pola_p;++args->eq_przesuiniecie_p;if(prawa->y-args->eq_przesuiniecie_p>11) args->p_4=true; else args->p_4=false; args->p_2=true;
                  }
                  else if(myszka_z<z_p && prawa!=NULL && myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*22 && myszka.y>args->Y_kratka && myszka.y<12*args->Y_kratka)
                  {
                           for(;z_p>myszka_z;++myszka_z){if(prawa->y-args->eq_przesuiniecie_p>11) {args->pozycja_paska_p+=roznica_pola_p;++args->eq_przesuiniecie_p;if(prawa->y-args->eq_przesuiniecie_p>11) args->p_4=true; else args->p_4=false; args->p_2=true;}}
                  }

                  else if(lewa!=NULL && myszka.buttons&2 && myszka.x>args->X_kratka && myszka.x<args->X_kratka*10 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && myszka.x/args->X_kratka-1<lewa->x && myszka.y/args->Y_kratka-1<lewa->y-args->eq_przesuiniecie_z && lewa->przedmiot(myszka.x/args->X_kratka-1, myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_z)!=NULL)
                  {
                           poczekaj_na_myszke(2);


                           specyfikacja_menu**n=new specyfikacja_menu*[7]; for(int i=0;i<7;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 7, 3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);Przedmiot*ten=lewa->przedmiot(myszka.x/args->X_kratka-1, myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_z);
                           switch(wybor)
                           {
                                    case 0: break;
                                    case 1:
                                             if(!(prawy_to_plecak && ten->jest_plecakiem())){int xx=ten->x, yy=ten->y;lewa->wyjmij_przedmiot(ten);
                                             if(prawa==NULL ||  (prawy_to_plecak && !ten->item->mozna_do_plecaka()) || !prawa->wloz_przedmiot(ten))
                                                      lewa->wloz_przedmiot(xx,yy,ten);}

                                             break;
                                    case 2:{int r_x,r_y; r_x=myszka.x/args->X_kratka-1-ten->x; r_y=myszka.y/args->Y_kratka-1-ten->y+args->eq_przesuiniecie_z;
                                    int xx=ten->x, yy=ten->y; lewa->wyjmij_przedmiot(ten);
                                    while(true){al_rest(0.01);if(myszka.buttons&1){poczekaj_na_myszke(1);break;}al_get_mouse_state(&myszka);}
                                    int MX=myszka.x/args->X_kratka-1, MY=myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_z;
                                    if(lewa!=NULL && MX>=0 &&MX<lewa->x && MY>=0 && MY<lewa->y && lewa->wloz_przedmiot(MX-r_x, MY-r_y, ten));
                                    else if(!ten->jest_plecakiem() && !(prawy_to_plecak && !ten->item->mozna_do_plecaka())  && prawa!=NULL && MX-11>=0 &&MX-11<prawa->x && MY>=0 && MY<prawa->y && !(prawy_to_plecak && !ten->item->mozna_do_plecaka())  && prawa->wloz_przedmiot(MX-r_x-11, MY-r_y, ten));
                                    else lewa->wloz_przedmiot(xx,yy,ten);
                                    }
                                              break;
                                    case 3: {
                                             lewa->wyjmij_przedmiot(ten); Item*nasz=ten->item;delete ten;
                                             Item* aa=uzyj(nasz); if(aa!=NULL) lewa->wloz_przedmiot(new Przedmiot(aa));
                                             }break;
                                    case 4:{
                                             if(swiat->aktualny->p_rece==NULL)
                                             {
                                                      lewa->wyjmij_przedmiot(ten); swiat->aktualny->p_rece=ten->item; delete ten;
                                             }}
                                              break;
                                    case 5:
                                             {
                                                      if(g->ilosc_kieszeni>'0' && g->p_kieszenl==NULL && ten->item->mozna_do_kieszeni())
                                                      {lewa->wyjmij_przedmiot(ten); swiat->aktualny->p_kieszenl=ten->item; delete ten;}
                                                      else if(g->ilosc_kieszeni>'1' && g->p_kieszenp==NULL && ten->item->mozna_do_kieszeni())
                                                      {lewa->wyjmij_przedmiot(ten); swiat->aktualny->p_kieszenp=ten->item; delete ten;}
                                             } break;
                                    case 6:
                                             {
                                                      if(ten->jest_kapeluszem() && g->p_glowa==NULL){lewa->wyjmij_przedmiot(ten); g->p_glowa=ten->item; delete ten;}
                                                      else if(ten->jest_korpusem() && g->p_korpus==NULL){lewa->wyjmij_przedmiot(ten); g->p_korpus=ten->item; delete ten;}
                                                      else if(ten->jest_spodniami() && g->p_spodnie==NULL){lewa->wyjmij_przedmiot(ten); g->p_spodnie=ten->item; delete ten;}
                                                      else if(ten->jest_butami() && g->p_buty==NULL){lewa->wyjmij_przedmiot(ten); g->p_buty=ten->item; delete ten;}
                                                      else if(ten->jest_rekawicami() && g->p_rekawice==NULL){lewa->wyjmij_przedmiot(ten); g->p_rekawice=ten->item; delete ten;}
                                                      else if(ten->jest_bronia() && g->p_ramie==NULL){lewa->wyjmij_przedmiot(ten); g->p_ramie=ten->item; delete ten;}
                                                      else if(ten->jest_plecakiem() && g->p_plecak==NULL)
                                                               {

                                                                        lewa->wyjmij_przedmiot(ten);g->p_plecak=ten->item;delete ten;prawy_to_plecak=true;
                                                                        //args->ilosc_przedmiotow_plecak=0;
                                                                        args->p_2=false;args->p_4=false;
                                                                        Skrzynka *j=prawa;if(g->p_plecak==NULL)prawa=new Skrzynka(0,0);
                                                                        else {prawa=((Plecak*)g->p_plecak)->s;}delete j;
                                                                        wersjap=prawa->getWersja()-1; ///prawym powinien byc plecak
                                                                        if(prawa!=NULL && prawa->y>11 )args->p_4=true;
                                                                        args->eq_przesuiniecie_p=0;
                                                                        if(prawa!=NULL){if(prawa->y==0)args->dlugosc_paska_p=(11*args->Y_kratka*9);else args->dlugosc_paska_p=(11*args->Y_kratka*9)/prawa->y; args->pozycja_paska_p=0; roznica_pola_p=args->dlugosc_paska_p/11;}
                                                                        args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                                               }
                                             } break;
                                    case 7: {informacje(ten->item);}break;
                           }

                           delete menu; menu=NULL;
                  }
                  else if(prawa!=NULL && myszka.buttons&2 && myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*21 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && myszka.x/args->X_kratka-12<prawa->x && myszka.y/args->Y_kratka-1<prawa->y-args->eq_przesuiniecie_p && prawa->przedmiot(myszka.x/args->X_kratka-12, myszka.y/args->Y_kratka-1)!=NULL)
                  {
                           poczekaj_na_myszke(2);

                           specyfikacja_menu**n=new specyfikacja_menu*[7]; for(int i=0;i<7;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 7, 4);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);Przedmiot*ten=prawa->przedmiot(myszka.x/args->X_kratka-12, myszka.y/args->Y_kratka-1);
                           switch(wybor)
                           {
                                    case 0: break;
                                    case 1:
                                             {int xx=ten->x, yy=ten->y;prawa->wyjmij_przedmiot(ten);
                                             if(lewa==NULL || !lewa->wloz_przedmiot(ten))
                                                      prawa->wloz_przedmiot(xx,yy,ten);}

                                             break;
                                    case 2:{int r_x,r_y; r_x=myszka.x/args->X_kratka-12-ten->x; r_y=myszka.y/args->Y_kratka-1-ten->y;
                                    int xx=ten->x, yy=ten->y; prawa->wyjmij_przedmiot(ten);
                                    while(true){al_rest(0.01);if(myszka.buttons&1){poczekaj_na_myszke(1);break;}al_get_mouse_state(&myszka);}
                                    int MX=myszka.x/args->X_kratka-1, MY=myszka.y/args->Y_kratka-1;
                                    if(lewa!=NULL && MX>=0 &&MX<lewa->x && MY>=0 && MY<lewa->y && lewa->wloz_przedmiot(MX-r_x, MY-r_y, ten));
                                    else if(!ten->jest_plecakiem() && prawa!=NULL && MX-11>=0 &&MX-11<prawa->x && MY>=0 && MY<prawa->y && prawa->wloz_przedmiot(MX-r_x-11, MY-r_y, ten));
                                    else prawa->wloz_przedmiot(xx,yy,ten);
                                    }
                                              break;
                                    case 3: {
                                    prawa->wyjmij_przedmiot(ten); Item*nasz=ten->item;delete ten;
                                             Item* aa=uzyj(nasz); if(aa!=NULL) prawa->wloz_przedmiot(new Przedmiot(aa));
                                    }break;
                                    case 4: {
                                             if(swiat->aktualny->p_rece==NULL)
                                             {
                                                      prawa->wyjmij_przedmiot(ten); swiat->aktualny->p_rece=ten->item; delete ten;
                                             }}break;
                                    case 5: break;
                                    case 6: {
                                                      if(ten->jest_kapeluszem() && g->p_glowa==NULL){prawa->wyjmij_przedmiot(ten); g->p_glowa=ten->item; delete ten;}
                                                      else if(ten->jest_korpusem() && g->p_korpus==NULL){prawa->wyjmij_przedmiot(ten); g->p_korpus=ten->item; delete ten;}
                                                      else if(ten->jest_spodniami() && g->p_spodnie==NULL){prawa->wyjmij_przedmiot(ten); g->p_spodnie=ten->item; delete ten;}
                                                      else if(ten->jest_butami() && g->p_buty==NULL){prawa->wyjmij_przedmiot(ten); g->p_buty=ten->item; delete ten;}
                                                      else if(ten->jest_rekawicami() && g->p_rekawice==NULL){prawa->wyjmij_przedmiot(ten); g->p_rekawice=ten->item; delete ten;}
                                                      else if(ten->jest_bronia() && g->p_ramie==NULL){prawa->wyjmij_przedmiot(ten); g->p_ramie=ten->item; delete ten;}
                                                      else if(ten->jest_plecakiem() && g->p_plecak==NULL){prawa->wyjmij_przedmiot(ten); g->p_plecak=ten->item; delete ten;}
                                             }break;
                                    case 7:{informacje(ten->item);}break;
                           }

                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 && jest_nad_ramieniem(myszka) && g->p_ramie!=NULL)
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[4]; for(int i=0;i<4;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 4, 6);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch (wybor)
                           {
                                    case 1:{if(g->p_rece==NULL){g->p_rece=g->p_ramie; g->p_ramie=NULL;}
                                             else if(g->p_rece->jest_bronia_na_ramie()){Item *a=g->p_rece; g->p_rece=g->p_ramie; g->p_ramie=a;}
                                             }break;
                                    case 2:
                                             {Przedmiot*a=new Przedmiot(g->p_ramie);if(lewa!=NULL && lewa->wloz_przedmiot(a))g->p_ramie=NULL;
                                                      else delete a;}
                                                      break;
                                    case 3:{Przedmiot*a=new Przedmiot(g->p_ramie);if(prawa!=NULL && !(prawy_to_plecak && !a->item->mozna_do_plecaka())  && prawa->wloz_przedmiot(a))g->p_ramie=NULL;
                                                      else delete a;}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 && jest_nad_plecakiem(myszka) && g->p_plecak!=NULL)
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[3]; for(int i=0;i<3;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 3, 10);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch (wybor)
                           {
                                    case 1:{zamykamy=true;}break;
                                    case 2:
                                             {if(lewa!=NULL)
                                             {
                                                      Przedmiot *a=new Przedmiot(g->p_plecak);
                                                      if(lewa->wloz_przedmiot(a))
                                                      {
                                                               g->p_plecak=NULL;

                                                               args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                                      }else delete a;
                                             }else show_message("Nie ma gdzie wyrzucic");}
                                                      break;
                                    case 3:{informacje(g->p_plecak);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 && jest_nad_rekami(myszka) && g->p_rece!=NULL)
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[6]; for(int i=0;i<6;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 6, 8);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch (wybor)
                           {
                                    case 1:{
                                             Item*nasz=g->p_rece;g->p_rece=NULL;
                                             Item* aa=uzyj(nasz);
                                             if(aa!=NULL)
                                             {
                                                      if(g->p_rece==NULL) g->p_rece=aa;
                                                      else daj_aktualnemu_item(aa);
                                             }
                                    }break;
                                    case 2:{Przedmiot*a=new Przedmiot(g->p_rece);if(prawa!=NULL && !(prawy_to_plecak && !a->item->mozna_do_plecaka())  && prawa->wloz_przedmiot(a))g->p_rece=NULL;
                                                      else delete a;}break;
                                    case 3:{Przedmiot*a=new Przedmiot(g->p_rece);if(lewa!=NULL && lewa->wloz_przedmiot(a))g->p_rece=NULL;
                                                      else delete a;}break;
                                    case 4:{if(g->p_rece->jest_bronia_na_ramie() || g->p_rece->jest_ubraniem())
                                    {
                                             Item **a;
                                             if(g->p_rece->jest_bronia_na_ramie()) a=&g->p_ramie;
                                             else if(g->p_rece->jest_kapeluszem()) a=&g->p_glowa;
                                             else if(g->p_rece->jest_korpusem()) a=&g->p_korpus;
                                             else if(g->p_rece->jest_spodniami()) a=&g->p_spodnie;
                                             else if(g->p_rece->jest_butami()) a=&g->p_buty;
                                             else if(g->p_rece->jest_rekawicami()) a=&g->p_rekawice;
                                             if(*a==NULL) {*a=g->p_rece; g->p_rece=NULL;}
                                             else {Item *b=g->p_rece; g->p_rece=*a; *a=b;}
                                    }
                                    }break;
                                    case 5:{if(g->ilosc_kieszeni<'1') show_message("Nie masz kieszeni!");
                                    else if(g->ilosc_kieszeni<'2' && g->p_kieszenl==NULL && g->p_rece->mozna_do_kieszeni()){g->p_kieszenl=g->p_rece;g->p_rece=NULL;}
                                    else if(g->ilosc_kieszeni<'3' && g->p_kieszenp==NULL && g->p_rece->mozna_do_kieszeni()){g->p_kieszenp=g->p_rece;g->p_rece=NULL;}
                                    else if(g->ilosc_kieszeni<'2'){Item*a=g->p_rece;g->p_rece=g->p_kieszenl;g->p_kieszenl=a;}
                                    }break;
                                    case 6:{informacje(g->p_rece);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 && ((jest_nad_kieszenl(myszka) && g->p_kieszenl!=NULL)||(jest_nad_kieszenp(myszka) && g->p_kieszenp!=NULL)))
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[6]; for(int i=0;i<6;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 6, 9);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           Item**kieszen=&g->p_kieszenl;if(jest_nad_kieszenp(myszka))kieszen=&g->p_kieszenp;
                           switch (wybor)
                           {
                                    case 1:{
                                             Item*nasz=*kieszen;*kieszen=NULL;
                                             Item* aa=uzyj(nasz);
                                             if(aa!=NULL)
                                             {
                                                      if(*kieszen==NULL) *kieszen=aa;
                                                      else daj_aktualnemu_item(aa);
                                             }
                                    }
                                             break;
                                    case 2:{if(g->p_rece==NULL){g->p_rece=*kieszen;*kieszen=NULL;}
                                    else {Item*a=*kieszen;*kieszen=g->p_rece;g->p_rece=a;}}break;
                                    case 3:{if((*kieszen)->jest_bronia_na_ramie() || (*kieszen)->jest_ubraniem())
                                    {
                                             Item **a;
                                             if((*kieszen)->jest_bronia_na_ramie()) a=&g->p_ramie;
                                             else if((*kieszen)->jest_kapeluszem()) a=&g->p_glowa;
                                             else if((*kieszen)->jest_korpusem()) a=&g->p_korpus;
                                             else if((*kieszen)->jest_spodniami()) a=&g->p_spodnie;
                                             else if((*kieszen)->jest_butami()) a=&g->p_buty;
                                             else if((*kieszen)->jest_rekawicami()) a=&g->p_rekawice;
                                             if(*a==NULL) {*a=*kieszen; *kieszen=NULL;}
                                             else {Item *b=*kieszen; *kieszen=*a; *a=b;}
                                    }
                                    }break;
                                    case 4:{Przedmiot*a=new Przedmiot(*kieszen);if(lewa!=NULL && lewa->wloz_przedmiot(a))*kieszen=NULL;
                                                      else delete a;}
                                    break;
                                    case 5:{Przedmiot*a=new Przedmiot(*kieszen);if(prawa!=NULL && !(prawy_to_plecak && !a->item->mozna_do_plecaka())  && prawa->wloz_przedmiot(a))*kieszen=NULL;
                                                      else delete a;}break;
                                    case 6:{informacje(*kieszen);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 &&((jest_nad_glowa(myszka)&& g->p_glowa!=NULL) || (jest_nad_korpusem(myszka) && g->p_korpus!=NULL)
                                               || (jest_nad_spodniami(myszka) && g->p_spodnie!=NULL) || (jest_nad_butami(myszka) && g->p_buty!=NULL) || (jest_nad_rekawicami(myszka) && g->p_rekawice!=NULL)))
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[5]; for(int i=0;i<5;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 5, 7);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           Item** ubranie;
                           if(jest_nad_glowa(myszka))ubranie=&g->p_glowa;
                           else if(jest_nad_korpusem(myszka))ubranie=&g->p_korpus;
                           else if(jest_nad_spodniami(myszka))ubranie=&g->p_spodnie;
                           else if(jest_nad_butami(myszka))ubranie=&g->p_buty;
                           else if(jest_nad_rekawicami(myszka))ubranie=&g->p_rekawice;
                           switch (wybor)
                           {
                                    case 1:{Przedmiot*a=new Przedmiot(*ubranie);if(prawa!=NULL && !(prawy_to_plecak && !a->item->mozna_do_plecaka()) && prawa->wloz_przedmiot(a))*ubranie=NULL;else delete a;}break;
                                    case 2:{Przedmiot*a=new Przedmiot(*ubranie);if(lewa!=NULL && lewa->wloz_przedmiot(a))*ubranie=NULL;else delete a;}break;
                                    case 3:{if(g->p_rece==NULL) {g->p_rece=*ubranie;*ubranie=NULL;}
                                    else {Item*a=g->p_rece;g->p_rece=*ubranie;*ubranie=a;}
                                    }break;
                                    case 4:{if(g->ilosc_kieszeni<'1') show_message("Nie masz kieszeni!");
                                    else if(g->ilosc_kieszeni<'2' && g->p_kieszenl==NULL && (*ubranie)->mozna_do_kieszeni()){g->p_kieszenl=*ubranie;*ubranie=NULL;}
                                    else if(g->ilosc_kieszeni<'3' && g->p_kieszenp==NULL && (*ubranie)->mozna_do_kieszeni()){g->p_kieszenp=*ubranie;*ubranie=NULL;}
                                    else if(g->ilosc_kieszeni<'2'){Item*a=*ubranie;*ubranie=g->p_kieszenl;g->p_kieszenl=a;}
                                    }
                                    break;
                                    case 5:{informacje(*ubranie);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(lewa!=NULL && lewa->y>11 && myszka.buttons&1 && myszka.x>10*args->X_kratka+4 && myszka.x<11*args->X_kratka-4 &&myszka.y>=args->pozycja_paska_s+2*args->Y_kratka && myszka.y<=args->pozycja_paska_s+2*args->Y_kratka+args->dlugosc_paska_s)
                  {
                           int hhh=myszka.y-2*args->Y_kratka-args->pozycja_paska_s;hhh/=roznica_pola_s;
                           int akt_m_y1=hhh*roznica_pola_s+args->Y_kratka*2+args->pozycja_paska_s, akt_m_y2=akt_m_y1+roznica_pola_s;
                           int akt_wid_y1=args->Y_kratka*2+(hhh+1)*roznica_pola_s, akt_wid_y2=11*args->Y_kratka-args->dlugosc_paska_s+hhh*roznica_pola_s;
                           while(true)
                           {
                                    al_rest(0.01);
                                    al_get_mouse_state(&myszka);

                                    if(!(myszka.buttons&1))break;
                                    if(myszka.y<akt_wid_y1) {args->eq_przesuiniecie_z=0; args->p_1=false; args->p_3=true;akt_m_y1=akt_wid_y1-roznica_pola_s; akt_m_y2=akt_wid_y1;args->pozycja_paska_s=0;if(lewa->y>11) args->p_3=true; args->p_1=false;}
                                    else if(myszka.y>akt_wid_y2) {args->eq_przesuiniecie_z=lewa->y-11; args->p_1=false; args->p_3=true;akt_m_y1=akt_wid_y2; akt_m_y2=akt_wid_y2+roznica_pola_s;args->pozycja_paska_s=9*args->Y_kratka-args->dlugosc_paska_s;if(lewa->y>11) args->p_1=true; args->p_3=false;}
                                    else if(myszka.y<akt_m_y1)
                                    {
                                             int zmiana=(akt_m_y1+5)/roznica_pola_s-myszka.y/roznica_pola_s;
                                             akt_m_y1-=zmiana*roznica_pola_s; akt_m_y2-=zmiana*roznica_pola_s;
                                             args->eq_przesuiniecie_z-=zmiana;
                                             args->pozycja_paska_s-=zmiana*roznica_pola_s;
                                             args->p_3=lewa->y>11; args->p_1=args->eq_przesuiniecie_z>0;
                                    }
                                    else if(myszka.y>akt_m_y2)
                                    {
                                             int zmiana=myszka.y/roznica_pola_s-(akt_m_y1+5)/roznica_pola_s;
                                             akt_m_y1+=zmiana*roznica_pola_s; akt_m_y2+=zmiana*roznica_pola_s;
                                             args->eq_przesuiniecie_z+=zmiana;
                                             args->pozycja_paska_s+=zmiana*roznica_pola_s;
                                             args->p_3=lewa->y-args->eq_przesuiniecie_z>11; args->p_1=lewa->y>11;
                                    }
                           }
                  }
                  else if(prawa!=NULL && prawa->y>11 && myszka.buttons&1 && myszka.x>21*args->X_kratka+4 && myszka.x<22*args->X_kratka-4 &&myszka.y>=args->pozycja_paska_p+2*args->Y_kratka && myszka.y<=args->pozycja_paska_p+2*args->Y_kratka+args->dlugosc_paska_p)
                  {
                           int hhh=myszka.y-2*args->Y_kratka-args->pozycja_paska_p;hhh/=roznica_pola_p;
                           int akt_m_y1=hhh*roznica_pola_p+args->Y_kratka*2+args->pozycja_paska_p, akt_m_y2=akt_m_y1+roznica_pola_p;
                           int akt_wid_y1=args->Y_kratka*2+(hhh+1)*roznica_pola_p, akt_wid_y2=11*args->Y_kratka-args->dlugosc_paska_p+hhh*roznica_pola_p;
                           while(true)
                           {
                                    al_rest(0.01);
                                    al_get_mouse_state(&myszka);

                                    if(!(myszka.buttons&1))break;
                                    if(myszka.y<akt_wid_y1) {args->eq_przesuiniecie_p=0; args->p_1=false; args->p_3=true;akt_m_y1=akt_wid_y1-roznica_pola_p; akt_m_y2=akt_wid_y1;args->pozycja_paska_p=0;if(prawa->y>11) args->p_4=true; args->p_2=false;}
                                    else if(myszka.y>akt_wid_y2) {args->eq_przesuiniecie_p=prawa->y-11; args->p_1=false; args->p_3=true;akt_m_y1=akt_wid_y2; akt_m_y2=akt_wid_y2+roznica_pola_p;args->pozycja_paska_p=9*args->Y_kratka-args->dlugosc_paska_p;if(prawa->y>11) args->p_2=true; args->p_4=false;}
                                    else if(myszka.y<akt_m_y1)
                                    {
                                             int zmiana=(akt_m_y1+5)/roznica_pola_p-myszka.y/roznica_pola_p;
                                             akt_m_y1-=zmiana*roznica_pola_p; akt_m_y2-=zmiana*roznica_pola_p;
                                             args->eq_przesuiniecie_p-=zmiana;
                                             args->pozycja_paska_p-=zmiana*roznica_pola_p;
                                             args->p_4=prawa->y>11; args->p_2=args->eq_przesuiniecie_p>0;
                                    }
                                    else if(myszka.y>akt_m_y2)
                                    {
                                             int zmiana=myszka.y/roznica_pola_p-(akt_m_y1+5)/roznica_pola_p;
                                             akt_m_y1+=zmiana*roznica_pola_p; akt_m_y2+=zmiana*roznica_pola_p;
                                             args->eq_przesuiniecie_p+=zmiana;
                                             args->pozycja_paska_p+=zmiana*roznica_pola_p;
                                             args->p_4=prawa->y-args->eq_przesuiniecie_p>11; args->p_2=prawa->y>11;
                                    }
                           }
                  }
                  else if(lewa!=NULL && myszka.buttons&1 && myszka.x>args->X_kratka && myszka.x<args->X_kratka*10 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && myszka.x/args->X_kratka-1<lewa->x && myszka.y/args->Y_kratka-1<lewa->y-args->eq_przesuiniecie_z && lewa->przedmiot(myszka.x/args->X_kratka-1, myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_z)!=NULL)
                  {
                           Przedmiot *ten=lewa->przedmiot(myszka.x/args->X_kratka-1, myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_z);
                           int xx=ten->x, yy=ten->y; lewa->wyjmij_przedmiot(ten); args->p_nr_przedmiotu=ten->item->get_co_to();
                           int roznica_x=myszka.x-(ten->x+1)*args->X_kratka,
                           roznica_y=myszka.y-(ten->y+1-args->eq_przesuiniecie_z)*args->Y_kratka;
                           while(true)
                           {
                                    args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if(!(myszka.buttons&1)) break;
                           }
                           args->p_nr_przedmiotu=0;
                           if(myszka.x>args->X_kratka && myszka.x<args->X_kratka*10 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && myszka.x/args->X_kratka-1<lewa->x && myszka.y/args->Y_kratka-1<lewa->y-args->eq_przesuiniecie_z
                          && (lewa->wloz_przedmiot((myszka.x-roznica_x+0.5*args->X_kratka)/args->X_kratka-1,(myszka.y-roznica_y+0.5*args->Y_kratka)/args->Y_kratka-1+args->eq_przesuiniecie_z,ten)||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka-1+args->eq_przesuiniecie_z,ten)||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka-1,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_z,ten)||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_z,ten))
                              );
                           else if(myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*21 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && (myszka.x)/args->X_kratka-12<prawa->x && myszka.y/args->Y_kratka-1<prawa->y-args->eq_przesuiniecie_p && !(prawy_to_plecak && !ten->item->mozna_do_plecaka())
                          && (prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x+0.5*args->X_kratka)/args->X_kratka-1,(myszka.y-roznica_y+0.5*args->Y_kratka)/args->Y_kratka-1+args->eq_przesuiniecie_p,ten)||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka-1+args->eq_przesuiniecie_p,ten)||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka-1,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_p,ten)||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_p,ten))
                              );
                              else if(jest_nad_rekami(myszka)&&g->p_rece==NULL)
                              {
                                    g->p_rece=ten->item; delete ten;
                              }
                              else if(jest_nad_kieszenl(myszka)&&g->p_kieszenl==NULL && ten->item->mozna_do_kieszeni())
                              {
                                    g->p_kieszenl=ten->item; delete ten;
                              }
                              else if(jest_nad_kieszenp(myszka)&&g->p_kieszenp==NULL&& ten->item->mozna_do_kieszeni())
                              {
                                    g->p_kieszenp=ten->item; delete ten;
                              }
                              else if((ten->jest_kapeluszem() && g->p_glowa==NULL)||(ten->jest_korpusem() && g->p_korpus==NULL)||(ten->jest_spodniami() && g->p_spodnie==NULL)
                                      ||(ten->jest_butami() && g->p_buty==NULL)||(ten->jest_rekawicami() && g->p_rekawice==NULL)
                                      ||(ten->jest_bronia() && g->p_ramie==NULL)||(ten->jest_plecakiem() && g->p_plecak==NULL))
                              {
                                    {
                                                      if(ten->jest_kapeluszem() && g->p_glowa==NULL){g->p_glowa=ten->item; delete ten;}
                                                      else if(ten->jest_korpusem() && g->p_korpus==NULL){g->p_korpus=ten->item; delete ten;}
                                                      else if(ten->jest_spodniami() && g->p_spodnie==NULL){g->p_spodnie=ten->item; delete ten;}
                                                      else if(ten->jest_butami() && g->p_buty==NULL){g->p_buty=ten->item; delete ten;}
                                                      else if(ten->jest_rekawicami() && g->p_rekawice==NULL){g->p_rekawice=ten->item; delete ten;}
                                                      else if(ten->jest_bronia() && g->p_ramie==NULL){g->p_ramie=ten->item; delete ten;}
                                                      else if(ten->jest_plecakiem() && g->p_plecak==NULL)
                                                               {
                                                                        g->p_plecak=ten->item;delete ten;
                                                                        //args->ilosc_przedmiotow_plecak=0;
                                                                        args->p_2=false;args->p_4=false;
                                                                        Skrzynka *j=prawa;if(g->p_plecak==NULL)prawa=new Skrzynka(0,0);
                                                                        else {prawa=((Plecak*)g->p_plecak)->s;}delete j;
                                                                        wersjap=prawa->getWersja()-1; ///prawym powinien byc plecak
                                                                        if(prawa!=NULL && prawa->y>11 )args->p_4=true;
                                                                        args->eq_przesuiniecie_p=0;
                                                                        if(prawa!=NULL){if(prawa->y==0)args->dlugosc_paska_p=(11*args->Y_kratka*9);else args->dlugosc_paska_p=(11*args->Y_kratka*9)/prawa->y; args->pozycja_paska_p=0; roznica_pola_p=args->dlugosc_paska_p/11;}
                                                                        args->otwarty_ekwipunek=false;Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                                               }
                                             }
                              }
                          else lewa->wloz_przedmiot(xx,yy,ten);
                  }
                  else if(prawa!=NULL && myszka.buttons&1 && myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*21 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && (myszka.x)/args->X_kratka-12<prawa->x && myszka.y/args->Y_kratka-1<prawa->y-args->eq_przesuiniecie_p &&
                           prawa->przedmiot(myszka.x/args->X_kratka-12, myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_p)!=NULL)
                  {
                           Przedmiot *ten=prawa->przedmiot(myszka.x/args->X_kratka-12, myszka.y/args->Y_kratka-1+args->eq_przesuiniecie_p);
                           int xx=ten->x, yy=ten->y; prawa->wyjmij_przedmiot(ten); args->p_nr_przedmiotu=ten->item->get_co_to();
                           int roznica_x=myszka.x-(ten->x+12)*args->X_kratka,
                           roznica_y=myszka.y-(ten->y+1-args->eq_przesuiniecie_p)*args->Y_kratka;
                           while(true)
                           {
                                    args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if(!(myszka.buttons&1)) break;
                           }
                           args->p_nr_przedmiotu=0;
                           if(myszka.x>args->X_kratka && myszka.x<args->X_kratka*10 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && myszka.x/args->X_kratka-1<lewa->x && myszka.y/args->Y_kratka-1<lewa->y-args->eq_przesuiniecie_z
                          && (lewa->wloz_przedmiot((myszka.x-roznica_x+0.5*args->X_kratka)/args->X_kratka-1,(myszka.y-roznica_y+0.5*args->Y_kratka)/args->Y_kratka-1+args->eq_przesuiniecie_z,ten)||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka-1+args->eq_przesuiniecie_z,ten)||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka-1,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_z,ten)||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_z,ten))
                              );
                           else if(myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*21 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && (myszka.x)/args->X_kratka-12<prawa->x && myszka.y/args->Y_kratka-1<prawa->y-args->eq_przesuiniecie_p && !(prawy_to_plecak && ten->jest_plecakiem())
                          && (prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x+0.5*args->X_kratka)/args->X_kratka-1,(myszka.y-roznica_y+0.5*args->Y_kratka)/args->Y_kratka-1+args->eq_przesuiniecie_p,ten)||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka-1+args->eq_przesuiniecie_p,ten)||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka-1,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_p,ten)||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_p,ten))
                              );
                              else if(jest_nad_rekami(myszka)&&g->p_rece==NULL)
                              {
                                    g->p_rece=ten->item; delete ten;
                              }
                              else if(jest_nad_kieszenl(myszka)&&g->p_kieszenl==NULL && ten->item->mozna_do_kieszeni())
                              {
                                    g->p_kieszenl=ten->item; delete ten;
                              }
                              else if(jest_nad_kieszenp(myszka)&&g->p_kieszenp==NULL && ten->item->mozna_do_kieszeni())
                              {
                                    g->p_kieszenp=ten->item; delete ten;
                              }
                              else if((ten->jest_kapeluszem() && g->p_glowa==NULL)||(ten->jest_korpusem() && g->p_korpus==NULL)||(ten->jest_spodniami() && g->p_spodnie==NULL)
                                      ||(ten->jest_butami() && g->p_buty==NULL)||(ten->jest_rekawicami() && g->p_rekawice==NULL)
                                      ||(ten->jest_bronia() && g->p_ramie==NULL)||(ten->jest_plecakiem() && g->p_plecak==NULL))
                              {
                                    {
                                                      if(ten->jest_kapeluszem() && g->p_glowa==NULL){g->p_glowa=ten->item; delete ten;}
                                                      else if(ten->jest_korpusem() && g->p_korpus==NULL){g->p_korpus=ten->item; delete ten;}
                                                      else if(ten->jest_spodniami() && g->p_spodnie==NULL){g->p_spodnie=ten->item; delete ten;}
                                                      else if(ten->jest_butami() && g->p_buty==NULL){g->p_buty=ten->item; delete ten;}
                                                      else if(ten->jest_rekawicami() && g->p_rekawice==NULL){g->p_rekawice=ten->item; delete ten;}
                                                      else if(ten->jest_bronia() && g->p_ramie==NULL){g->p_ramie=ten->item; delete ten;}
                                                      else if(ten->jest_plecakiem() && g->p_plecak==NULL)
                                                               {
                                                                        g->p_plecak=ten->item;delete ten;
                                                                        //args->ilosc_przedmiotow_plecak=0;
                                                                        args->p_2=false;args->p_4=false;
                                                                        Skrzynka *j=prawa;if(g->p_plecak==NULL)prawa=new Skrzynka(0,0);
                                                                        else {prawa=((Plecak*)g->p_plecak)->s;}delete j;
                                                                        wersjap=prawa->getWersja()-1; ///prawym powinien byc plecak
                                                                        if(prawa!=NULL && prawa->y>11 )args->p_4=true;
                                                                        args->eq_przesuiniecie_p=0;
                                                                        if(prawa!=NULL){if(prawa->y==0)args->dlugosc_paska_p=(11*args->Y_kratka*9);else args->dlugosc_paska_p=(11*args->Y_kratka*9)/prawa->y; args->pozycja_paska_p=0; roznica_pola_p=args->dlugosc_paska_p/11;}
                                                                        args->otwarty_ekwipunek=false;Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                                               }
                                             }
                              }
                          else prawa->wloz_przedmiot(xx,yy,ten);
                  }
                  else if(myszka.buttons&1 && ((jest_nad_ramieniem(myszka) && g->p_ramie!=NULL && (dla_funkcji=1)==1 && ((mozna_do_pl=g->p_ramie->mozna_do_plecaka())||true))||
                                               (jest_nad_glowa(myszka) && g->p_glowa!=NULL && (dla_funkcji=2)==2 && ((mozna_do_pl=g->p_glowa->mozna_do_plecaka())||true))||
                                               (jest_nad_plecakiem(myszka) && g->p_plecak!=NULL && (dla_funkcji=3)==3 && ((mozna_do_pl=g->p_plecak->mozna_do_plecaka())||true))||
                                               (jest_nad_rekami(myszka) && g->p_rece!=NULL && (dla_funkcji=4)==4 && ((mozna_do_pl=g->p_rece->mozna_do_plecaka())||true))||
                                               (jest_nad_korpusem(myszka) && g->p_korpus!=NULL && (dla_funkcji=5)==5 && ((mozna_do_pl=g->p_korpus->mozna_do_plecaka())||true))||
                                               (jest_nad_rekawicami(myszka) && g->p_rekawice!=NULL && (dla_funkcji=6)==6 && ((mozna_do_pl=g->p_rekawice->mozna_do_plecaka())||true))||
                                               (jest_nad_kieszenl(myszka) && g->p_kieszenl!=NULL && (dla_funkcji=7)==7 && ((mozna_do_pl=g->p_kieszenl->mozna_do_plecaka())||true))||
                                               (jest_nad_spodniami(myszka) && g->p_spodnie!=NULL && (dla_funkcji=8)==8 && ((mozna_do_pl=g->p_spodnie->mozna_do_plecaka())||true))||
                                               (jest_nad_kieszenp(myszka) && g->p_kieszenp!=NULL && (dla_funkcji=9)==9 && ((mozna_do_pl=g->p_kieszenp->mozna_do_plecaka())||true))||
                                               (jest_nad_butami(myszka) && g->p_buty!=NULL && (dla_funkcji=10)==10 && ((mozna_do_pl=g->p_buty->mozna_do_plecaka())||true))))
                  {
                           Item*ten=NULL;
                           switch(dla_funkcji)
                           {
                                    case 1:{ten=g->p_ramie;g->p_ramie=NULL;break;}
                                    case 2:{ten=g->p_glowa;g->p_glowa=NULL;break;}
                                    case 3:{ten=g->p_plecak;g->p_plecak=NULL;break;}
                                    case 4:{ten=g->p_rece;g->p_rece=NULL;break;}
                                    case 5:{ten=g->p_korpus;g->p_korpus=NULL;break;}
                                    case 6:{ten=g->p_rekawice;g->p_rekawice=NULL;break;}
                                    case 7:{ten=g->p_kieszenl;g->p_kieszenl=NULL;break;}
                                    case 8:{ten=g->p_spodnie;g->p_spodnie=NULL;break;}
                                    case 9:{ten=g->p_kieszenp;g->p_kieszenp=NULL;break;}
                                    case 10:{ten=g->p_buty;g->p_buty=NULL;break;}
                           }
                           args->p_nr_przedmiotu=ten->get_co_to();
                           int roznica_x=args->X_kratka/2,roznica_y=args->Y_kratka/2;
                           while(true)
                           {
                                    args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if(!(myszka.buttons&1)) break;
                           }
                           args->p_nr_przedmiotu=0;
                           if(myszka.x>args->X_kratka && myszka.x<args->X_kratka*10 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && myszka.x/args->X_kratka-1<lewa->x && myszka.y/args->Y_kratka-1<lewa->y-args->eq_przesuiniecie_z
                          && (lewa->wloz_przedmiot((myszka.x-roznica_x+0.5*args->X_kratka)/args->X_kratka-1,(myszka.y-roznica_y+0.5*args->Y_kratka)/args->Y_kratka-1+args->eq_przesuiniecie_z,new Przedmiot(ten))||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka-1+args->eq_przesuiniecie_z,new Przedmiot(ten))||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka-1,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_z,new Przedmiot(ten))||
                              lewa->wloz_przedmiot((myszka.x-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_z,new Przedmiot(ten)))
                              )
                              {
                                             if(dla_funkcji==3)
                                             {
                                                     args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                             }
                              }
                           else if(myszka.x>args->X_kratka*12 && myszka.x<args->X_kratka*21 && myszka.y>args->Y_kratka && myszka.y<args->Y_kratka*12
                          && (myszka.x)/args->X_kratka-12<prawa->x && myszka.y/args->Y_kratka-1<prawa->y-args->eq_przesuiniecie_p && !(prawy_to_plecak && !mozna_do_pl)
                          && (prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x+0.5*args->X_kratka)/args->X_kratka-1,(myszka.y-roznica_y+0.5*args->Y_kratka)/args->Y_kratka-1+args->eq_przesuiniecie_p,new Przedmiot(ten))||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka-1+args->eq_przesuiniecie_p,new Przedmiot(ten))||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka-1,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_p,new Przedmiot(ten))||
                              prawa->wloz_przedmiot((myszka.x-11*args->X_kratka-roznica_x)/args->X_kratka,(myszka.y-roznica_y)/args->Y_kratka+args->eq_przesuiniecie_p,new Przedmiot(ten)))
                              )
                              {
                                             if(dla_funkcji==3)
                                             {
                                                     args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                             }
                              }
                              else if(jest_nad_rekami(myszka)&&g->p_rece==NULL)
                              {
                                    g->p_rece=ten;if(dla_funkcji==3){args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;}
                              }
                              else if(jest_nad_kieszenl(myszka)&&g->p_kieszenl==NULL && ten->mozna_do_kieszeni())
                              {
                                    g->p_kieszenl=ten;if(dla_funkcji==3){args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;}
                              }
                              else if(jest_nad_kieszenp(myszka)&&g->p_kieszenp==NULL && ten->mozna_do_kieszeni())
                              {
                                    g->p_kieszenp=ten;if(dla_funkcji==3){args->otwarty_ekwipunek=false; Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;}
                              }
                              else if(((ten->jest_kapeluszem() && g->p_glowa==NULL)||(ten->jest_korpusem() && g->p_korpus==NULL)||(ten->jest_spodniami() && g->p_spodnie==NULL)
                                      ||(ten->jest_butami() && g->p_buty==NULL)||(ten->jest_rekawicami() && g->p_rekawice==NULL)
                                      ||(ten->jest_bronia() && g->p_ramie==NULL)||(ten->jest_plecakiem() && g->p_plecak==NULL && dla_funkcji!=3)))
                                    {
                                                      if(ten->jest_kapeluszem() && g->p_glowa==NULL){g->p_glowa=ten;}
                                                      else if(ten->jest_korpusem() && g->p_korpus==NULL){g->p_korpus=ten;}
                                                      else if(ten->jest_spodniami() && g->p_spodnie==NULL){g->p_spodnie=ten;}
                                                      else if(ten->jest_butami() && g->p_buty==NULL){g->p_buty=ten;}
                                                      else if(ten->jest_rekawicami() && g->p_rekawice==NULL){g->p_rekawice=ten;}
                                                      else if(ten->jest_bronia() && g->p_ramie==NULL){g->p_ramie=ten;}
                                                      else if(ten->jest_plecakiem() && g->p_plecak==NULL && dla_funkcji!=3)
                                                               {
                                                                        g->p_plecak=ten;prawy_to_plecak=true;
                                                                        //args->ilosc_przedmiotow_plecak=0;
                                                                        args->p_2=false;args->p_4=false;
                                                                        Skrzynka *j=prawa;if(g->p_plecak==NULL)prawa=new Skrzynka(0,0);
                                                                        else {prawa=((Plecak*)g->p_plecak)->s;}delete j;
                                                                        wersjap=prawa->getWersja()-1; ///prawym powinien byc plecak
                                                                        if(prawa!=NULL && prawa->y>11 )args->p_4=true;
                                                                        args->eq_przesuiniecie_p=0;
                                                                        if(prawa!=NULL){if(prawa->y==0)args->dlugosc_paska_p=(11*args->Y_kratka*9);else args->dlugosc_paska_p=(11*args->Y_kratka*9)/prawa->y; args->pozycja_paska_p=0; roznica_pola_p=args->dlugosc_paska_p/11;}
                                                                        args->otwarty_ekwipunek=false;Sleep(f);g->otwiera=false;zalozylismy_nowy_plecak=true;return lewa;
                                                               }
                                             }

                          else
                          {
                                   switch(dla_funkcji)
                                    {
                                    case 1:{g->p_ramie=ten;break;}
                                    case 2:{g->p_glowa=ten;break;}
                                    case 3:{g->p_plecak=ten;break;}
                                    case 4:{g->p_rece=ten;break;}
                                    case 5:{g->p_korpus=ten;break;}
                                    case 6:{g->p_rekawice=ten;break;}
                                    case 7:{g->p_kieszenl=ten;break;}
                                    case 8:{g->p_spodnie=ten;break;}
                                    case 9:{g->p_kieszenp=ten;break;}
                                    case 10:{g->p_buty=ten;break;}
                                    }
                          }
                  }
                  else if(myszka.buttons&1 && myszka.x>22*args->X_kratka && myszka.y>args->p_pozycja_y+7*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1);anatomia(myszka,klawiatura);
                  }
                  else akt = false;

                  if(akt) {Gra::wersjal--;Gra::wersjap--;}


         al_rest(0.01);
         }

         if(prawy_to_plecak==false) delete prawa;
         args->otwarty_ekwipunek=false;
         Sleep(f); g->otwiera=false;
         return lewa;
}



void Gra::informacje(Item*a)
{
         ALLEGRO_MOUSE_STATE myszka;ALLEGRO_KEYBOARD_STATE klawiatura;
         if(a->jest_ubraniem())
         {
                  args->ocieplenie=((Ubranie*)a)->cieplo();
                  args->kamuflarz=((Ubranie*)a)->kamuflaz();
                  args->ochrona=((Ubranie*)a)->ochrona();
                  args->wytrzymalosc=((Ubranie*)a)->wytrzymalosc;
                  args->ubranie_info=true;
                  while(true)
                  {
                           al_get_mouse_state(&myszka);al_get_keyboard_state(&klawiatura);
                           if(myszka.buttons&1){poczekaj_na_myszke(1);break;}
                           else if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))
                           {while(true) {al_rest(0.01);if(!al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))break; al_get_keyboard_state(&klawiatura);}break;}
                           al_rest(0.01);
                  }
                  args->ubranie_info=false;
         }
         else if(a->jest_bronia())
         {
                  args->obrazen=(((Bron*)a)->obrazenia().y+((Bron*)a)->obrazenia().x)/2;
                  args->blo=(((Bron*)a)->blok().y+((Bron*)a)->blok().x)/2;
                  args->kryty=((Bron*)a)->get_krytyk();
                  args->bonus_uni=((Bron*)a)->UB();
                  args->szans=((Bron*)a)->get_szansa();
                  args->bonus_kop=((Bron*)a)->KB();
                  args->wytrzymalosc=((Bron*)a)->wytrzymalosc;if(a->jest_bronia_palna())args->wytrzymalosc=((Bron*)a)->mag;
                  args->bron_info=true;
                  while(true)
                  {
                           al_get_mouse_state(&myszka);al_get_keyboard_state(&klawiatura);
                           if(myszka.buttons&1){poczekaj_na_myszke(1);break;}
                           else if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))
                           {while(true) {al_rest(0.01);if(!al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))break; al_get_keyboard_state(&klawiatura);}break;}
                           al_rest(0.01);
                  }
                  args->bron_info=false;
         }
}

void Gra::przesuwanie(char strona,ALLEGRO_MOUSE_STATE myszka, ALLEGRO_KEYBOARD_STATE klawiatura)
{
        // std::cout<<"^1";
         przesun_mapy(strona,args,swiat);
         //std::cout<<"^2";
         for(int i=0;i<4;++i) args->way[i]=false; char powrotna;
         args->zostala_przesunieta=true;
         switch(strona)
         {
                  case 'p':args->way[2]=true;powrotna='l';break;
                  case 'd':args->way[3]=true;powrotna='g';break;
                  case 'l':args->way[0]=true;powrotna='p';break;
                  case 'g':args->way[1]=true;powrotna='d';break;
         }
         //std::cout<<"^3";
         while(true)
         {
                  al_get_mouse_state(&myszka); al_get_keyboard_state(&klawiatura);
                  if(al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))
                     {while(true){al_get_keyboard_state(&klawiatura);if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))break;}args->zostala_przesunieta=false;przesun_mapy(powrotna,args,swiat);return;break;}
                  if(myszka.buttons&1 && ((powrotna=='p' && jest_nad_strzalka_prawo(myszka))||(powrotna=='l' && jest_nad_strzalka_lewo(myszka))||
                                          (powrotna=='d' && jest_nad_strzalka_dol(myszka))||(powrotna=='g' && jest_nad_strzalka_gora(myszka))))
                  {
                           //std::cout<<"^4";
                           poczekaj_na_myszke(1);args->zostala_przesunieta=false; przesun_mapy(powrotna,args,swiat);//std::cout<<"^5";
                           return;
                  }
                  al_rest(0.01);
         }
        // std::cout<<"^8";
}

void Gra::anatomia(ALLEGRO_MOUSE_STATE myszka,ALLEGRO_KEYBOARD_STATE klawiatura)
{///moze byc otwarta podczas otwierania ekwipunku
         args->otwarte_menu_anatomii=true;
         args->klatka_max=40, args->klatka_a=30, args->brzuch_max=30, args->brzuch_a=30, args->l_ramie_max=10, args->l_ramie_a=10, args->p_ramie_max=10, args->p_ramie_a=10, args->l_dlon_max=5, args->l_dlon_a=5, args->p_dlon_max=5, args->p_dlon_a=5
          , args->l_udo_max=15, args->l_udo_a=15, args->p_udo_max=15, args->p_udo_a=15, args->l_golen_max=10, args->l_golen_a=10, args->p_golen_max=10, args->p_golen_a=10;
         while(true)
         {
                  al_get_mouse_state(&myszka); al_get_keyboard_state(&klawiatura);
                  if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))
                  {
                           while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))break;}
                           break;
                  }
                  else if(al_key_down(&klawiatura,ALLEGRO_KEY_H))
                  {
                           while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura, ALLEGRO_KEY_H))break;}
                           break;
                  }
                  else if(myszka.buttons&1 && myszka.x>22*args->X_kratka && myszka.y>args->p_pozycja_y+7*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); break;
                  }
         }
         args->otwarte_menu_anatomii=false;;
}

short* Gra::wsp_rzedow(Przepis *a, rozmiary_tabeli roz)
{
         short *j=new short[12], licznik = 0; j[licznik++] = args->Y_kratka*2.25;
         short pom = 0;
         for(short k=0; a[k].ilosc_substratow!=-1; ++k)
         {
                  j[licznik] = j[licznik-1] + a[k].potrzebne_wiersze(roz)*args->Y_kratka+args->Y_kratka*0.5;
                  licznik++;
         }
         short *wyn = new short[licznik+1];
         for(short g=0; g<licznik; ++g) wyn[g] = j[g];
         wyn[licznik] = -1;

         delete [] j;
         return wyn;
}

std::shared_ptr<co_ma_gracz> Gra::co_ma(Gracz *g, Przepis *p)
{
         short len=0; for(;p[len].ilosc_substratow!=-1;++len);
         std::shared_ptr<co_ma_gracz> co_ma(NULL);
         if(len>0) {co_ma.reset(new co_ma_gracz[len+1], std::default_delete<co_ma_gracz[]>());
         co_ma.get()[len].ilosc_substratow=-1;}
         for(len=0; p[len].ilosc_substratow!=-1; len++)
         {
                  co_ma.get()[len].ilosc_substratow = p[len].ilosc_substratow;
                  if(co_ma.get()[len].ilosc_substratow>0) co_ma.get()[len].substraty = new bool[p[len].ilosc_substratow];
                  for(short i=0;i<p[len].ilosc_substratow; ++i)
                  {
                           co_ma.get()[len].substraty[i] = g->posiada_przedmiot(((short*)p[len].substraty)[i*2], ((short*)p[len].substraty)[i*2+1], true);
                  }

                  co_ma.get()[len].ilosc_katalizatorow = p[len].ilosc_katalizatorow;
                  if(co_ma.get()[len].ilosc_katalizatorow>0) {co_ma.get()[len].katalizatory = new bool[p[len].ilosc_katalizatorow];}
                  for(short i=0;i<p[len].ilosc_katalizatorow; ++i)
                  {
                           co_ma.get()[len].katalizatory[i] = g->posiada_przedmiot(((short*)p[len].katalizatory)[i*2], ((short*)p[len].katalizatory)[i*2+1], true);
                  }

                  co_ma.get()[len].ilosc_objektow_w_poblizu = p[len].ilosc_objektow_w_poblizu;
                  if(co_ma.get()[len].ilosc_objektow_w_poblizu>0) co_ma.get()[len].objekty_w_poblizu = new bool[p[len].ilosc_objektow_w_poblizu];
                  for(short i=0;i<p[len].ilosc_objektow_w_poblizu; ++i)
                  {
                           co_ma.get()[len].objekty_w_poblizu[i] = g->jest_obok_objektu(((short*)p[len].objekty_w_poblizu)[i*2]);
                  }

                  co_ma.get()[len].ilosc_umiejetnosci = p[len].ilosc_umiejetnosci;
                  if(co_ma.get()[len].ilosc_umiejetnosci>0) co_ma.get()[len].skills = new bool[p[len].ilosc_umiejetnosci];
                  for(short i=0;i<p[len].ilosc_umiejetnosci; ++i)
                  {
                           co_ma.get()[len].skills[i] = g->ma_umiejetnosc(((short*)p[len].skills)[i*2]);
                  }
         }

         return co_ma;
}

void Gra::crafting(ALLEGRO_MOUSE_STATE myszka,ALLEGRO_KEYBOARD_STATE klawiatura)
{///moze byc otwarta podczas otwierania ekwipunku

         short *b = NULL;
         args->ktora_kategoria = 0; args->ktora_strona = 0;
         args->przepis = Krafting->daj_strone_z_kategorii(args->ktora_strona, args->ktora_kategoria); ///ostatni null
         args->co_ma = co_ma(swiat->aktualny, args->przepis);
         //std::cout<<args->co_ma[2].substraty[1]<<std::endl;throw "D";
         args->rozmiary.zmien(Krafting->rozmiary(args->ktora_strona, args->ktora_kategoria));
         args->wsp_r = wsp_rzedow(Krafting->daj_strone_z_kategorii(args->ktora_strona, args->ktora_kategoria), Krafting->rozmiary(args->ktora_strona, args->ktora_kategoria));
         args->da_sie_strone_w_prawo_w_craftingu=Krafting->jest_taka_strona_z_tej_kategorii(args->ktora_strona+1, args->ktora_kategoria);
         args->da_sie_strone_w_lewo_w_craftingu=args->ktora_strona>1;
         args->otwarte_menu_craftingu=true;
         while(true)
         {
                  al_get_mouse_state(&myszka); al_get_keyboard_state(&klawiatura);
                  if(al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE))
                  {
                           while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))break;}
                           break;
                  }
                  else if(myszka.buttons&1 && myszka.x>21*args->X_kratka && myszka.x<22*args->X_kratka && myszka.y>0*args->Y_kratka && myszka.y<args->Y_kratka*1)
                  {
                           poczekaj_na_myszke(1);
                           break;
                  }
                  else if(al_key_down(&klawiatura,ALLEGRO_KEY_H))
                  {
                           while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura, ALLEGRO_KEY_H))break;}
                           anatomia(myszka,klawiatura);
                  }
                  else if(myszka.buttons&1 && myszka.x>22*args->X_kratka && myszka.y>args->p_pozycja_y+7*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); anatomia(myszka,klawiatura);
                  }
                  /*else if(myszka.buttons&1 && myszka.x>22*args->X_kratka && myszka.y>args->p_pozycja_y+7*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1); break;
                  }*/
                  else if(myszka.buttons&1 && myszka.x>args->X_kratka*20 && myszka.x<args->X_kratka*22 && myszka.y>args->Y_kratka*2 && myszka.y<args->Y_kratka*12)
                  {
                           poczekaj_na_myszke(1);
                           for(short k=0; args->wsp_r[k]!=-1; ++k)
                           {
                                    short roznica = (args->wsp_r[k+1]==-1 ? args->Y_kratka*10.5 : args->wsp_r[k+1]) - args->wsp_r[k] - args->Y_kratka;
                                    roznica -= args->Y_kratka; roznica/=2; roznica+=args->wsp_r[k];
                                    if(myszka.y>=roznica && myszka.y<=roznica+args->Y_kratka)
                                    {
                                             ///wywolany k-ty przepis
                                             wykonaj_crafting(args->przepis+k, swiat->aktualny, args->co_ma.get()+k);
                                             args->co_ma = co_ma(swiat->aktualny, args->przepis);
                                    }
                           }
                  }
                  else if((args->da_sie_strone_w_lewo_w_craftingu && myszka.buttons&1 && myszka.x>args->X_kratka*15 && myszka.x<args->X_kratka*16 && myszka.y>13*args->Y_kratka && myszka.y<14*args->Y_kratka)
                           ||(args->da_sie_strone_w_prawo_w_craftingu && myszka.buttons&1 && myszka.x>args->X_kratka*20 && myszka.x<args->X_kratka*21 && myszka.y>13*args->Y_kratka && myszka.y<14*args->Y_kratka))
                  {
                           poczekaj_na_myszke(1);///strona w lewo
                           delete [] b;
                           b = args->wsp_r;

                           args->przepis = NULL; ///ostatni null
                           args->co_ma.reset();
                           args->wsp_r = NULL;

                           if(myszka.x<args->X_kratka*16) args->ktora_strona--; else args->ktora_strona++;

                           //std::cout<<"DDD";
                           args->przepis = Krafting->daj_strone_z_kategorii(args->ktora_strona, args->ktora_kategoria); ///ostatni null
                           //std::cout<<"XXX";
                           args->wsp_r = wsp_rzedow(Krafting->daj_strone_z_kategorii(args->ktora_strona, args->ktora_kategoria), Krafting->rozmiary(args->ktora_strona, args->ktora_kategoria));
                           args->co_ma = co_ma(swiat->aktualny, args->przepis);
                           args->rozmiary.zmien(Krafting->rozmiary(args->ktora_strona, args->ktora_kategoria));

                           args->da_sie_strone_w_prawo_w_craftingu=Krafting->jest_taka_strona_z_tej_kategorii(args->ktora_strona+1, args->ktora_kategoria);
                           args->da_sie_strone_w_lewo_w_craftingu=args->ktora_strona>0;

                  }
                  else if(myszka.buttons&1 && myszka.x>args->X_kratka*1 && myszka.x<args->X_kratka*11 && myszka.y>13*args->Y_kratka && myszka.y<14*args->Y_kratka)
                  {
                           poczekaj_na_myszke(1);
                           short ktora = (myszka.x-args->X_kratka)/args->X_kratka;
                           if(ktora<Krafting->ile_kategorii && ktora!=args->ktora_kategoria)
                           {
                                    delete [] b;
                                    b = args->wsp_r;

                                    args->przepis = NULL; ///ostatni null
                                    args->co_ma.reset();
                                    args->wsp_r = NULL;

                                    args->ktora_strona = 0;
                                    args->ktora_kategoria = ktora;

                                    args->przepis = Krafting->daj_strone_z_kategorii(args->ktora_strona, args->ktora_kategoria);

                                    args->wsp_r = wsp_rzedow(Krafting->daj_strone_z_kategorii(args->ktora_strona, args->ktora_kategoria), Krafting->rozmiary(args->ktora_strona, args->ktora_kategoria));
                                    args->co_ma = co_ma(swiat->aktualny, args->przepis);
                                    args->rozmiary.zmien(Krafting->rozmiary(args->ktora_strona, args->ktora_kategoria));

                                    args->da_sie_strone_w_prawo_w_craftingu=Krafting->jest_taka_strona_z_tej_kategorii(args->ktora_strona+1, args->ktora_kategoria);
                                    args->da_sie_strone_w_lewo_w_craftingu=args->ktora_strona>0;
                           }
                  }
         }
         args->otwarte_menu_craftingu=false;
         delete [] args->wsp_r; ////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         delete [] b;
         //args->co_ma.reset();
}

void Gra::wykonaj_crafting(Przepis *prz, Gracz *g, co_ma_gracz *co_mamy)
{
         bool t=1;
         for(short h=0; h<4; ++h)
         {
                  short i=0;
                  bool *g;
                  switch(h)
                  {
                           case 0: i=co_mamy->ilosc_substratow; g=co_mamy->substraty; break;
                           case 1: i=co_mamy->ilosc_katalizatorow; g=co_mamy->katalizatory; break;
                           case 2: i=co_mamy->ilosc_umiejetnosci; g=co_mamy->skills; break;
                           case 3: i=co_mamy->ilosc_objektow_w_poblizu; g=co_mamy->objekty_w_poblizu; break;
                  }
                  for(short y=0; y<i; ++y) if(!g[y]) {t=0; break;}
                  if(!t) break;
         }
         if(!t) return;


         std::list<std::pair<punkt, bool>> lista_punktow; ///punkt zajety oraz czy obiekt bedzie w otoczeniu
         Gracz* g = swiat->aktualny;

         for(short u=0; u<prz->ilosc_rezultatow; ++u)
         {
                  short nr = ((short*)prz->rezultaty)[0];
                  short ile = ((short*)prz->rezultaty)[1];
                  if((nr&(1<<15))==0) continue;

                  bool otoczenie = (nr&(1<<14))!=0;

                  for(short y=0; y<ile; ++y)
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           przywroc_ekw();

                           if(swiat->aktualna==swiat->zwroc_taka_aree(g->px, g->py, g->pz) && Strefa::w_planszy(aaa.x, aaa.y) &&g!=NULL && g->zaraz_obok(g->x, g->y, aaa.x, aaa.y)
                              && (!otoczenie || swiat->aktualna->otoczenie[aaa.y][aaa.x]==NULL))
                           {
                                    if(otoczenie)
                                    {
                                             for(auto it = lista_punktow.begin(); it!=lista_punktow.end(); ++it)
                                             {
                                                      if((*it).second && (*it).first.x==aaa.x && (*it).first.y==aaa.y)
                                                               return;
                                             }
                                             ///mozliwosc returna
                                    }
                                    lista_punktow.push_front(std::pair<punkt, bool>(aaa, otoczenie));
                           }
                  }
         }

         if(t)
         {
                  for(short h=0; h<3; ++h)
                  {
                           int *aaa;
                           short ile, co, ile_w_instancji;
                           switch(h)
                           {
                                    case 0: ile_w_instancji=prz->ilosc_substratow; aaa=prz->substraty; break;
                                    case 1: ile_w_instancji=prz->ilosc_katalizatorow; aaa=prz->katalizatory; break;
                                    case 2: ile_w_instancji=prz->ilosc_rezultatow; aaa=prz->rezultaty; break;
                                    //case 2: ile_w_instancji=co_mamy->ilosc_umiejetnosci; a=prz->skills; break;
                                    //case 3: ile_w_instancji=co_mamy->ilosc_objektow_w_poblizu; a=prz->objekty_w_poblizu; break;
                           }
                           for(short ggg=0; ggg<ile_w_instancji; ++ggg)
                           {
                                    int a = aaa[ggg];
                                    ile = ((short*)(&a))[1];
                                    co = ((short*)(&a))[0];
                                    if(h==2)
                                    {
                                             for(short k=0; k<ile; ++k)
                                             {
                                                      if((co&(1<<15))==0)
                                                      {
                                                               if(co==2012 || co==2014)///miesny wyjatek
                                                               {
                                                                        short bonus = co==2012 ? 50 : 130;
                                                                        if(prz->ilosc_katalizatorow==1 && ((short*)prz->katalizatory)[0]==4011)
                                                                                 bonus += co==2012 ? 20 : 60;
                                                                        if(prz->ilosc_substratow==2 &&  ((short*)prz->substraty)[2]==8021)
                                                                                 bonus += co==2012 ? 20 : 60;
                                                                        g->dostan_item(new Konsumpcjum(co, bonus));
                                                               }
                                                               else g->dostan_item(Item::stworz_obiekt(co));
                                                      }
                                                      else
                                                      {
                                                               co -= short(1<<15);
                                                               if((co&(1<<14))!=0) co -= short(1<<14);
                                                               Plansza *p = swiat->aktualna;
                                                               std::pair<punkt, bool> para = lista_punktow.back();
                                                               lista_punktow.pop_back();
                                                               if(para.second==false)
                                                               {
                                                                        swiat->aktualna->dodaj_do_srodowiska(para.first.x, para.first.y, Objekt::stworz_objekt_z_wykraftowania(co, para.first.x, para.first.y, p->x, p->y, p->z));
                                                               }
                                                               else
                                                               {
                                                                        if(swiat->aktualna->otoczenie[para.first.y][para.first.x]!=NULL)
                                                                        {
                                                                                 std::cout<<"wykonaj_crafting_tu_mialo_nic_nie_byc"; throw "D";
                                                                        }
                                                                        swiat->aktualna->otoczenie[para.first.y][para.first.x] = Objekt::stworz_objekt_z_wykraftowania(co, para.first.x, para.first.y, p->x, p->y, p->z);
                                                               }
                                                      }
                                             }
                                    }
                                    else for(short  k=0; k<ile; ++k) delete Item_wez_lub_wykorzystaj(g, h==0, co);
                           }
                  }
         }
}

///nie ruszamy naszego plecaka
Item* Gra::Item_wez_lub_wykorzystaj(Gracz *g, bool to_co_w_koncu, int jaki)///true to wez, false wykorzystaj
{
         Item **ten = NULL;
         if(g->p_rece!=NULL && g->p_rece->czym_jest==jaki) ten = &g->p_rece;
         if(g->p_glowa!=NULL && g->p_glowa->czym_jest==jaki) ten = &g->p_glowa;
         if(g->p_korpus!=NULL && g->p_korpus->czym_jest==jaki) ten = &g->p_korpus;
         if(g->p_spodnie!=NULL && g->p_spodnie->czym_jest==jaki) ten = &g->p_spodnie;
         if(g->p_buty!=NULL && g->p_buty->czym_jest==jaki) ten = &g->p_buty;
         if(g->p_rekawice!=NULL && g->p_rekawice->czym_jest==jaki) ten = &g->p_rekawice;
         if(g->p_ramie!=NULL && g->p_ramie->czym_jest==jaki) ten = &g->p_ramie;
         if(g->p_kieszenl!=NULL && g->p_kieszenl->czym_jest==jaki) ten = &g->p_kieszenl;
         if(g->p_kieszenp!=NULL && g->p_kieszenp->czym_jest==jaki) ten = &g->p_kieszenp;

         if(ten)
         {
                  if(to_co_w_koncu)
                  {
                           Item *a = *ten; *ten = NULL; return a;
                  }
                  else
                  {
                           if((*ten)->wykorzystaj())
                           {
                                    Item *a = *ten; *ten = NULL; delete a;
                           }
                           return NULL;
                  }
         }

         for(short i=0; i<2; ++i)
         {
                  Skrzynka *s = NULL;

                  if(!i)
                  {
                           if(!(lewa)) continue;
                           s = lewa;
                  }
                  else
                  {
                           if(!(g->p_plecak)) continue;
                           s = ((Plecak*)g->p_plecak)->s;
                  }

                  for(short i=0; i<s->lista_itemow()->ilosc; ++i)
                  {
                           if(s->lista_itemow()->obiekt[i]->czym_jest == jaki)
                           {
                                    Przedmiot *a = s->zwroc_przedmiot(s->lista_itemow()->obiekt[i]);
                                    if(to_co_w_koncu)
                                    {
                                             s->wyjmij_przedmiot(a);
                                             Item *ii = a->item;
                                             delete a;
                                             return ii;
                                    }
                                    else
                                    {
                                             if(a->item->wykorzystaj())
                                             {
                                                      s->wyjmij_przedmiot(a);
                                                      a->usun_calego();
                                                      return NULL;
                                             }
                                    }
                           }
                  }
         }
         return NULL;
}

void Gra::Rozpocznij_gre(struct dla_grafiki* arg)
{
         ALLEGRO_THREAD* obliczanie_grafiki;
         obliczanie_grafiki = al_create_thread(Obliczanie_grafiki,arg);
         al_start_thread(obliczanie_grafiki);

         ALLEGRO_MOUSE_STATE myszka;
         ALLEGRO_KEYBOARD_STATE klawiatura;
         Gracz*g;

         bool koniec=false;
         while (!koniec)
         {

                  al_get_mouse_state(&myszka);
                  al_get_keyboard_state(&klawiatura);


                  czy_moze_gracze_sie_skonczyli:
                  if(swiat->koniec || al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))
                  {
                           ///menu do zapisow i wyjscia
                           break;
                  }
                  if(swiat->aktualny==NULL)
                  {
                           swiat->Nastepna_runda();
                           goto czy_moze_gracze_sie_skonczyli;
                  }
                  if(swiat->aktualny!=NULL && swiat->aktualny->pozostalo_snu>0)
                  {
                           g=swiat->aktualny; --g->pozostalo_snu;
                           if(g->pozostalo_snu==0 || g->energia_a>=g->energia_max)
                           {
                                    g->pozostalo_snu=0;
                                    Plansza*p=swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);
                                    if(g->wstan_ze_snu());
                                    else {g->pozostalo_snu=1;swiat->Nastepna_runda();goto czy_moze_gracze_sie_skonczyli;/*p->upadnieci.dodaj_obiekt(new Upadly(g,g->x,g->y));*/}
                           }
                           else
                           {
                                    switch(g->gdzie_spi->czym_jest)
                                    {
                                             case 25:{if(g->energia_a<g->energia_max) g->energia_a+=2;if(swiat->czas%1==0 && g->jedzenie_a>0)--g->jedzenie_a;if(swiat->czas%1==0 && g->woda_a>0)--g->woda_a;if(g->kondycja<18)g->kondycja++;}break;
                                             case 32:{if(g->energia_a<g->energia_max) g->energia_a+=2;if(swiat->czas%1==0 && g->jedzenie_a>0)--g->jedzenie_a;if(swiat->czas%1==0 && g->woda_a>0)--g->woda_a;if(g->kondycja<18)g->kondycja++;}break;
                                             default:{if(swiat->czas%2==0 && g->energia_a<g->energia_max)++g->energia_a;if(g->jedzenie_a>0)--g->jedzenie_a;if(g->woda_a>0)--g->woda_a;}break;
                                    }
                                    swiat->Nastepna_runda();goto czy_moze_gracze_sie_skonczyli;
                           }
                  }

                  aktualny_upadl=swiat->zwroc_taka_aree(swiat->aktualny->px, swiat->aktualny->py, swiat->aktualny->pz)->aktualny_upadl();

                  if(aktualny_upadl){swiat->Nastepna_runda();goto czy_moze_gracze_sie_skonczyli;}
                  //opcje_zawsze_dostepne(arg);
                  if(swiat->teraz_gracz)
                  {
                           ruch_gracza(myszka,klawiatura,arg);
                  }

                  while(true) {al_get_mouse_state(&myszka);if(!(myszka.buttons & 1)) break; al_rest(0.02);}

         al_rest(0.01);
         }

         arg->koniec_sterowania=true;
         while(true)
         {
                 if(arg->skonczylem_sterowac)
                  {std::cout<<"niszczenie swiata";delete swiat;std::cout<<"swiat zniszczony";break;}
         }



}


std::shared_ptr<Upadly> Gra::daj_upadlego(int x, int y, Plansza *a)
{
         return a->ostatni_upadly(x, y);
}

punkt Gra::wybierz_kratke_na_planszy()
{
         bool h = args->otwarte_menu_anatomii;
         bool e = args->otwarty_ekwipunek;
         bool c = args->otwarte_menu_craftingu;
         args->otwarte_menu_anatomii = args->otwarty_ekwipunek = args->otwarte_menu_craftingu = false;
         args->myszka_aim = true;
         ALLEGRO_MOUSE_STATE myszka;
         punkt a(-2, -2);

         while(true)
         {
                  al_get_mouse_state(&myszka);
                  if((myszka.buttons&2)) break;
                  else if(myszka.buttons&1)
                  {
                           a.x = (myszka.x- args->X_kratka/2)/args->X_kratka ; a.y = (myszka.y- args->Y_kratka/2)/args->Y_kratka ; break;
                  }
                  al_rest(0.02);
         }

         args->myszka_aim = false;
         args->otwarte_menu_anatomii=h;
         args->otwarty_ekwipunek=e;
         args->otwarte_menu_craftingu=c;
         return a;
}



