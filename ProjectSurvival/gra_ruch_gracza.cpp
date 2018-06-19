#include "gra.h"








void Gra::ruch_gracza(ALLEGRO_MOUSE_STATE myszka,
         ALLEGRO_KEYBOARD_STATE klawiatura, dla_grafiki* args)
{
         std::shared_ptr<Upadly> u = 0;
         short dla_funkcji=0;
         Gracz *gracz=swiat->aktualny, *g=swiat->aktualny; int X=args->X_kratka, Y=args->Y_kratka, mx=(myszka.x-args->X_kratka/2)/args->X_kratka
         , my=(myszka.y-args->Y_kratka/2)/args->Y_kratka;
         Plansza*p=swiat->aktualna;
         if(swiat->aktualny==NULL) return;
         else if(!g->ukryty && (myszka.buttons & 1) && jest_na_polu(args, myszka, gracz->x, gracz->y))
         {
                  args->lewy_krok=false;args->prawy_krok=false;args->gora_krok=false;args->dol_krok=false;
                  if(args->kroki==false)
                  {
                           if(Strefa::w_planszy(gracz->x-1, gracz->y) && swiat->aktualna->otoczenie[gracz->y][gracz->x-1]==NULL){args->lewy_krok=true; args->x1=gracz->x-1; args->y1=gracz->y;}
                           if(Strefa::w_planszy(gracz->x+1, gracz->y) && swiat->aktualna->otoczenie[gracz->y][gracz->x+1]==NULL){args->prawy_krok=true; args->x2=gracz->x+1; args->y2=gracz->y;}
                           if(Strefa::w_planszy(gracz->x, gracz->y-1) && swiat->aktualna->otoczenie[gracz->y-1][gracz->x]==NULL){args->gora_krok=true; args->x3=gracz->x; args->y3=gracz->y-1;}
                           if(Strefa::w_planszy(gracz->x, gracz->y+1) && swiat->aktualna->otoczenie[gracz->y+1][gracz->x]==NULL){args->dol_krok=true; args->x4=gracz->x; args->y4=gracz->y+1;}
                           args->kroki=true;
                  }
                  else
                  {
                           args->kroki=false;
                  }
         }
         else if(!g->ukryty && (((myszka.buttons &1) && args->kroki)||al_key_down(&klawiatura, ALLEGRO_KEY_A)||al_key_down(&klawiatura, ALLEGRO_KEY_D)
                 ||al_key_down(&klawiatura, ALLEGRO_KEY_S)||al_key_down(&klawiatura, ALLEGRO_KEY_W)))
         {
                  //swiat->aktualna->ma_gracza = false;
                  what_happened aaa;
                  bool poszlo=false,to_byla_myszka=(myszka.buttons &1)==1; char k; Plansza*p=swiat->zwroc_taka_plansze_TYLKO(gracz->px, gracz->py, gracz->pz);Gracz*g=swiat->aktualny;
                  if(((to_byla_myszka&&args->prawy_krok && jest_na_polu(args,myszka,gracz->x+1,gracz->y))||(al_key_down(&klawiatura, ALLEGRO_KEY_D)&&((gracz->x+1<21&&p->otoczenie[gracz->y][gracz->x+1]==NULL)||(g->x==20 && swiat->zwroc_taka_plansze(g->px+1, g->py, g->pz) && swiat->zwroc_taka_plansze(g->px+1, g->py, g->pz)->otoczenie[g->y][0]==NULL))))&&((g ->postawa=='r' && (pobierz_punkty_ruchu_i_kondycje(3,1) || pobierz_punkty_ruchu_i_kondycje(5,0)))||(g ->postawa=='s' && pobierz_punkty_ruchu(4))||((g->postawa=='c' && pobierz_punkty_ruchu(6))))) {poszlo=true;k='p';args->kroki=false;aaa=gracz->przesun('p');}
                  else if(((to_byla_myszka&&args->lewy_krok && jest_na_polu(args,myszka,gracz->x-1,gracz->y))||(al_key_down(&klawiatura, ALLEGRO_KEY_A)&&((gracz->x-1>-1&&p->otoczenie[gracz->y][gracz->x-1]==NULL)||(g->x==0 && swiat->zwroc_taka_plansze(g->px-1, g->py, g->pz) && swiat->zwroc_taka_plansze(g->px-1, g->py, g->pz)->otoczenie[g->y][20]==NULL))))&&((g ->postawa=='r' && (pobierz_punkty_ruchu_i_kondycje(3,1)||pobierz_punkty_ruchu_i_kondycje(5,0)))||(g ->postawa=='s' && pobierz_punkty_ruchu(4))||((g->postawa=='c' && pobierz_punkty_ruchu(6))))){poszlo=true;k='l';args->kroki=false;aaa=gracz->przesun('l');}
                  else if(((to_byla_myszka&&args->gora_krok && jest_na_polu(args,myszka,gracz->x,gracz->y-1)) ||(al_key_down(&klawiatura, ALLEGRO_KEY_W)&&((gracz->y-1>-1&&p->otoczenie[gracz->y-1][gracz->x]==NULL)||(g->y==0 && swiat->zwroc_taka_plansze(g->px, g->py-1, g->pz) && swiat->zwroc_taka_plansze(g->px, g->py-1, g->pz)->otoczenie[12][g->x]==NULL))))&&((g ->postawa=='r' && (pobierz_punkty_ruchu_i_kondycje(3,1)||pobierz_punkty_ruchu_i_kondycje(5,0)))||(g ->postawa=='s' && pobierz_punkty_ruchu(4))||((g->postawa=='c' && pobierz_punkty_ruchu(6))))){poszlo=true;k='g';args->kroki=false;aaa=gracz->przesun('g');}
                  else if(((to_byla_myszka&&args->dol_krok && jest_na_polu(args,myszka,gracz->x,gracz->y+1)) ||(al_key_down(&klawiatura, ALLEGRO_KEY_S)&&((gracz->y+1<13&&p->otoczenie[gracz->y+1][gracz->x]==NULL)||(g->y==12 && swiat->zwroc_taka_plansze(g->px, g->py+1, g->pz) && swiat->zwroc_taka_plansze(g->px, g->py+1, g->pz)->otoczenie[0][g->x]==NULL))))&&((g ->postawa=='r' && (pobierz_punkty_ruchu_i_kondycje(3,1)||pobierz_punkty_ruchu_i_kondycje(5,0)))||(g ->postawa=='s' && pobierz_punkty_ruchu(4))||((g->postawa=='c' && pobierz_punkty_ruchu(6))))){poszlo=true;k='d';args->kroki=false;aaa=gracz->przesun('d');}
                           if(aaa==dead) return;
                           if(poszlo&&!to_byla_myszka)
                           {
                                    while(1){al_rest(0.01);al_get_keyboard_state(&klawiatura);
                                    if((k=='p' && !al_key_down(&klawiatura, ALLEGRO_KEY_D))||(k=='l' && !al_key_down(&klawiatura, ALLEGRO_KEY_A))||
                                    (k=='g' && !al_key_down(&klawiatura, ALLEGRO_KEY_W))||(k=='d' && !al_key_down(&klawiatura, ALLEGRO_KEY_S)))break;}
                           }
         }


       //if((myszka)||((klawiatura&&((wolne_pole)||(1))))&&(p_ruchu))
         //if(((myszka)||(klawiatura&&((wolne_pole)||(1))))&&(p_ruchu))

         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_RIGHT))
         {
                  while(true) {al_rest(0.01);if(!al_key_down(&klawiatura,ALLEGRO_KEY_RIGHT))break; al_get_keyboard_state(&klawiatura);}
                  if(swiat->zwroc_taka_plansze(swiat->aktualna->x+1, swiat->aktualna->y, swiat->aktualna->z))
                  {
                           swiat->aktualna->ma_gracza = false;
                           przesun_mapy('p', args, swiat);
                           swiat->aktualna->zaktualizuj_widoki();
                           swiat->aktualna->ma_gracza = true;
                  }
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_LEFT))
         {
                  while(true) {al_rest(0.01);if(!al_key_down(&klawiatura,ALLEGRO_KEY_LEFT))break; al_get_keyboard_state(&klawiatura);}
                  if(swiat->zwroc_taka_plansze(swiat->aktualna->x-1, swiat->aktualna->y, swiat->aktualna->z))
                  {swiat->aktualna->ma_gracza = false;
                           przesun_mapy('l', args, swiat);
                           swiat->aktualna->zaktualizuj_widoki();
                           swiat->aktualna->ma_gracza = true;
                  }
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_UP))
         {
                  while(true) {al_rest(0.01);if(!al_key_down(&klawiatura,ALLEGRO_KEY_UP))break; al_get_keyboard_state(&klawiatura);}
                  if(swiat->zwroc_taka_plansze(swiat->aktualna->x, swiat->aktualna->y-1, swiat->aktualna->z))
                  {swiat->aktualna->ma_gracza = false;
                           przesun_mapy('g', args, swiat);
                           swiat->aktualna->zaktualizuj_widoki();
                           swiat->aktualna->ma_gracza = true;
                  }
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_DOWN))
         {
                  while(true) {al_rest(0.01);if(!al_key_down(&klawiatura,ALLEGRO_KEY_DOWN))break; al_get_keyboard_state(&klawiatura);}
                  if(swiat->zwroc_taka_plansze(swiat->aktualna->x, swiat->aktualna->y+1, swiat->aktualna->z))
                  {swiat->aktualna->ma_gracza = false;
                           przesun_mapy('d', args, swiat);
                           swiat->aktualna->zaktualizuj_widoki();
                           swiat->aktualna->ma_gracza = true;
                  }
         }
         else if(!g->ukryty && (myszka.buttons & 2) && jest_na_polu(args, myszka, gracz->x, gracz->y))
         {
                  poczekaj_na_myszke(2);
                  specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,1);
                  for(int l=0; l<3; l++)
                  {menu->item[l]=new  specyfikacja_menu( new  specyfikacja_menu *[4-l],4-l,l+2);
                  for(int k=0; k<4-l;k++){menu->item[l]->item[k]=new  specyfikacja_menu(NULL, 0, (l+1)*10+k+1);} }
                  int wybor=Menu(myszka.x, myszka.y, args, menu);
                  switch(wybor)
                  {
                           case 11: if(gracz->zwrot!='p') {if(pobierz_punkty_ruchu(1)) {gracz->zwrot='p';} else show_message("za malo punktow ruchu"); } break;
                           case 12: if(gracz->zwrot!='l') {if(pobierz_punkty_ruchu(1)) {gracz->zwrot='l';} else show_message("za malo punktow ruchu"); } break;
                           case 13: if(gracz->zwrot!='g') {if(pobierz_punkty_ruchu(1)) {gracz->zwrot='g';} else show_message("za malo punktow ruchu"); } break;
                           case 14: if(gracz->zwrot!='d') {if(pobierz_punkty_ruchu(1)) {gracz->zwrot='d';} else show_message("za malo punktow ruchu"); } break;
                           case 21: if(gracz->postawa!='r' && g->stan_nog()!=1 && g->stan_nog()!=2) {if(pobierz_punkty_ruchu(2)) {gracz->postawa='r';gracz->wysokosc=3;swiat->aktualna->zaktualizuj_widoki(gracz->x, gracz->y);} else show_message("za malo punktow ruchu"); } break;
                           case 22: if(gracz->postawa!='s' && g->stan_nog()!=1 && g->stan_nog()!=2) {if(pobierz_punkty_ruchu(2)) {gracz->postawa='s';gracz->wysokosc=2;swiat->aktualna->zaktualizuj_widoki(gracz->x, gracz->y);} else show_message("za malo punktow ruchu"); } break;
                           case 23: if(gracz->postawa!='c') {if(pobierz_punkty_ruchu(2)) {gracz->postawa='c';gracz->wysokosc=1;swiat->aktualna->zaktualizuj_widoki(gracz->x, gracz->y);} else show_message("za malo punktow ruchu"); } break;
                           case 31:  {if(pobierz_punkty_ruchu(2)) {gracz->gwizdze=true;Sleep(750);gracz->wydaj_dzwiek(false,4,g->x,g->y,0);gracz->gwizdze=false;} else show_message("za malo punktow ruchu"); } break;
                           case 32: {if(pobierz_punkty_ruchu(3)) {gracz->krzyczy=true;Sleep(750);gracz->wydaj_dzwiek(false,20,g->x,g->y,0);gracz->krzyczy=false;} else show_message("za malo punktow ruchu"); } break;
                  }

                  delete menu; menu=NULL;
         }
         else if(!g->ukryty && al_key_down(&klawiatura, ALLEGRO_KEY_X))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_X))break;}
                    if(gracz->postawa!='c') {if(pobierz_punkty_ruchu(2)) {gracz->postawa='c';gracz->wysokosc=1;swiat->aktualna->zaktualizuj_widoki(gracz->x, gracz->y);} else show_message("za malo punktow ruchu"); }
         }
         else if(!g->ukryty && al_key_down(&klawiatura, ALLEGRO_KEY_C))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_C))break;}
                    if(gracz->postawa!='s' && g->stan_nog()!=1 && g->stan_nog()!=2) {if(pobierz_punkty_ruchu(2)) {gracz->postawa='s';gracz->wysokosc=2;swiat->aktualna->zaktualizuj_widoki(gracz->x, gracz->y);} else show_message("za malo punktow ruchu"); }
         }
         else if(!g->ukryty && al_key_down(&klawiatura, ALLEGRO_KEY_V))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_V))break;}
                    if(gracz->postawa!='r' && g->stan_nog()!=1 && g->stan_nog()!=2) {if(pobierz_punkty_ruchu(2)) {gracz->postawa='r';gracz->wysokosc=3;swiat->aktualna->zaktualizuj_widoki(gracz->x, gracz->y);} else show_message("za malo punktow ruchu"); }
         }
         else if(!g->ukryty && al_key_down(&klawiatura, ALLEGRO_KEY_LCTRL))
         {
                   while(true)
                   {
                        al_rest(0.01);al_get_keyboard_state(&klawiatura);
                        if(al_key_down(&klawiatura, ALLEGRO_KEY_W))
                        {
                                if(pobierz_punkty_ruchu(1)) {gracz->zwrot='g';} else show_message("za malo punktow ruchu");
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_W))break;}
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_LCTRL))break;}
                                break;
                        }
                        if(al_key_down(&klawiatura, ALLEGRO_KEY_D))
                        {
                                if(pobierz_punkty_ruchu(1)) {gracz->zwrot='p';} else show_message("za malo punktow ruchu");
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_D))break;}
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_LCTRL))break;}
                                break;
                        }
                        if(al_key_down(&klawiatura, ALLEGRO_KEY_A))
                        {
                                if(pobierz_punkty_ruchu(1)) {gracz->zwrot='l';} else show_message("za malo punktow ruchu");
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_A))break;}
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_LCTRL))break;}
                                break;
                        }
                        if(al_key_down(&klawiatura, ALLEGRO_KEY_S))
                        {
                                if(pobierz_punkty_ruchu(1)) {gracz->zwrot='d';} else show_message("za malo punktow ruchu");
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_S))break;}
                                while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_LCTRL))break;}
                                break;
                        }
                        if(!al_key_down(&klawiatura,ALLEGRO_KEY_LCTRL)) break;
                   }
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_ALT))
         {swiat->aktualna->ma_gracza=false;
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_ALT))break;}
                   //args->myszka_zajeta=true;for(int i=0; i<60;++i)swiat->Nastepna_runda();args->myszka_zajeta=false;swiat->aktualna->ma_gracza=true;
                   static bool lewo = true;
                   while(1) {if(lewo) swiat->aktualny->przesun('l'); else swiat->aktualny->przesun('p'); lewo=!lewo;}
         }
         else if(al_key_down(&klawiatura, ALLEGRO_KEY_O))
         {swiat->aktualna->ma_gracza=false;
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_O))break;}
                   args->myszka_zajeta=true;for(int i=0; i<360;++i)swiat->Nastepna_runda();args->myszka_zajeta=false;swiat->aktualna->ma_gracza=true;
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_P))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_P))break;}
                   //args->myszka_zajeta=true;for(int i=0; i<480;++i)swiat->Nastepna_runda();args->myszka_zajeta=false;swiat->aktualna->ma_gracza=true;
                   while(1){for(short aaa=0;aaa<21;++aaa)
                   {
                            for(short ttt=0;ttt<13;++ttt)
                            {
                                     if(swiat->aktualna->otoczenie[ttt][aaa]) swiat->aktualna->otoczenie[ttt][aaa]->przewroc();
                            }
                   }
                   swiat->Nastepna_runda();}


         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_Q))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_Q))break;}
                   /*for(int jed=0;jed<21;++jed) for(int dwa=0;dwa<13;++dwa) if(swiat->aktualna->otoczenie[dwa][jed]!=NULL && swiat->aktualna->otoczenie[dwa][jed]->czym_jest==2)
                   {
                            ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->jest_ofiara = true;
                            ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->ofiara = swiat->aktualny;
                             ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->jest_cel=false;
                              ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->celem_jest_plansza=false;
                   }*/
                   swiat->aktualna->wybuch_o_mocy(3, 1, 11);
         }
         else if(al_key_down(&klawiatura, ALLEGRO_KEY_G))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_G))break;}
                   /*for(int jed=0;jed<21;++jed) for(int dwa=0;dwa<13;++dwa) if(swiat->aktualna->otoczenie[dwa][jed]!=NULL && swiat->aktualna->otoczenie[dwa][jed]->czym_jest==2)
                   {
                            ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->jest_ofiara = true;
                            ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->ofiara = swiat->aktualny;
                             ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->jest_cel=false;
                              ((Zombie*)swiat->aktualna->otoczenie[dwa][jed])->celem_jest_plansza=false;
                   }*/
                  ///((Plansza*)swiat->area[g->px+1][g->py][g->pz])->oswietlenie_z_innych_plansz[5][0] = 1;
                  // ((Plansza*)swiat->area[g->px+1][g->py][g->pz])->zaktualizuj_widoki();

                   //((Plansza*)swiat->area[g->px][g->py][g->pz])->zaktualizuj_widoki();
                   //std::cout<<swiat->area[1][0][0]->x<<swiat->area[1][0][0]->y<<swiat->area[1][0][0]->z;
                   //std::cout<<std::endl<<swiat->aktualny->posiada_przedmiot(8020, 1, 1);
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_E))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_E))break;}
                   swiat->aktualna->zaktualizuj_widoki();
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_Z))
         {
                if(swiat->aktualna)
                {
                    Srodowisko *s; Objekt *o;
                    for(short j=0; j<13; ++j)
                        for(short h=0; h<21; ++h)
                            args->wys[j][h] = (o=swiat->aktualna->otoczenie[j][h]) ? ((s=swiat->aktualna->srodowisko[j][h]) ?
                                                                                (s->wysokosc()>o->wysokosc ? s->wysokosc() : o->wysokosc) : o->wysokosc) : ((s=swiat->aktualna->srodowisko[j][h]) ? s->wysokosc() : 0);
                            args->wysokosci = true;
                }
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_Z))break;}
                   args->wysokosci = false;
         }
         else if(godmode && al_key_down(&klawiatura, ALLEGRO_KEY_G))
         {
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_G))break;}
                   swiat->aktualna->dodaj_do_srodowiska(10,12,new Zwloki(2,1|2|4|8|16|32,10,7,1,0,0));
                 //swiat->aktualna->otoczenie[7][10] = new Ukryty_pod();
         }
         else if(al_key_down(&klawiatura, ALLEGRO_KEY_SPACE))
         {
                  args->lewy_krok=false;args->dol_krok=false;args->gora_krok=false;args->prawy_krok=false;
                   while(true) {al_rest(0.01);al_get_keyboard_state(&klawiatura);if(!al_key_down(&klawiatura,ALLEGRO_KEY_SPACE))break;}
                   args->myszka_zajeta=true;swiat->Nastepna_runda();args->myszka_zajeta=false;
         }
         else if(myszka.buttons&1 && myszka.x>22*args->X_kratka && myszka.y<args->Y_kratka*2.5)
         {
                  args->lewy_krok=false;args->dol_krok=false;args->gora_krok=false;args->prawy_krok=false;poczekaj_na_myszke(1);
                  args->myszka_zajeta=true;swiat->Nastepna_runda();args->myszka_zajeta=false;
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
                                             {if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                    swiat->aktualna->ziemia[g->y][g->x]->dodaj_obiekt(g->p_ramie); g->p_ramie=NULL;
                                                      }
                                                      break;
                                    case 3:{Przedmiot*a=new Przedmiot(g->p_ramie);if(g->p_plecak!=NULL && ((Plecak*)g->p_plecak)->s->wloz_przedmiot(a))g->p_ramie=NULL;
                                                      else delete a;}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && jest_nad_plecakiem(myszka) && g->p_plecak!=NULL)
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[3]; for(int i=0;i<3;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 3, 2);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch (wybor)
                           {
                                    case 1:if(pobierz_punkty_ruchu(3)){zn:zalozylismy_nowy_plecak=false;
                                             if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                             swiat->aktualna->ziemia[g->y][g->x]=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args, new Skrzynka( swiat->aktualna->ziemia[g->y][g->x],9,20)));
                                    if(swiat->aktualna->ziemia[g->y][g->x]->ilosc==0) {delete swiat->aktualna->ziemia[g->y][g->x];swiat->aktualna->ziemia[g->y][g->x]=NULL;}
                                    if(zalozylismy_nowy_plecak)goto zn;}
                                    break;
                                    case 2:
                                              {if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                    swiat->aktualna->ziemia[g->y][g->x]->dodaj_obiekt(g->p_plecak); g->p_plecak=NULL;
                                                      }
                                                      break;
                                    case 3:{informacje(g->p_plecak);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && jest_nad_plecakiem(myszka) && g->p_plecak==NULL)
                  {
                            poczekaj_na_myszke(2);specyfikacja_menu**n=new specyfikacja_menu*[1]; for(int i=0;i<1;++i)n[i]=new specyfikacja_menu(NULL,0,i+1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 1, 25);int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch (wybor)
                           {
                                    case 1:if(pobierz_punkty_ruchu(3)){zno:zalozylismy_nowy_plecak=false;
                                             if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                             swiat->aktualna->ziemia[g->y][g->x]=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args, new Skrzynka( swiat->aktualna->ziemia[g->y][g->x],9,20)));
                                    if(swiat->aktualna->ziemia[g->y][g->x]->ilosc==0) {delete swiat->aktualna->ziemia[g->y][g->x];swiat->aktualna->ziemia[g->y][g->x]=NULL;}
                                    if(zalozylismy_nowy_plecak)goto zno;}
                                    break;
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
                                             Item* aa=uzyj(nasz); if(aa!=NULL) g->p_rece=aa;
                                    }break;
                                    case 2:{Przedmiot*a=new Przedmiot(g->p_rece);if(g->p_plecak!=NULL && ((Plecak*)g->p_plecak)->s->wloz_przedmiot(a))g->p_rece=NULL;
                                                      else delete a;}break;
                                    case 3:{if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                    swiat->aktualna->ziemia[g->y][g->x]->dodaj_obiekt(g->p_rece); g->p_rece=NULL;
                                                      }break;
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
                                    else if(g->ilosc_kieszeni<'2' && g->p_kieszenl==NULL){g->p_kieszenl=g->p_rece;g->p_rece=NULL;}
                                    else if(g->ilosc_kieszeni<'3' && g->p_kieszenp==NULL){g->p_kieszenp=g->p_rece;g->p_rece=NULL;}
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
                                             Item* aa=uzyj(nasz); if(aa!=NULL) *kieszen=aa;
                                    }break;
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
                                    case 4:{if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                    swiat->aktualna->ziemia[g->y][g->x]->dodaj_obiekt(*kieszen); *kieszen=NULL;}
                                    break;
                                    case 5:{Przedmiot*a=new Przedmiot(*kieszen);if(g->p_plecak!=NULL && ((Plecak*)g->p_plecak)->s->wloz_przedmiot(a))*kieszen=NULL;
                                                      else delete a;}break;
                                    case 6:{informacje(*kieszen);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 && ((jest_nad_glowa(myszka)&& g->p_glowa!=NULL) || (jest_nad_korpusem(myszka) && g->p_korpus!=NULL)
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
                                    case 1:{{Przedmiot*a=new Przedmiot(*ubranie);if(g->p_plecak!=NULL && ((Plecak*)g->p_plecak)->s->wloz_przedmiot(a))*ubranie=NULL;else delete a;}}break;
                                    case 2:{if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                    swiat->aktualna->ziemia[g->y][g->x]->dodaj_obiekt(*ubranie); *ubranie=NULL;}break;
                                    case 3:{if(g->p_rece==NULL) {g->p_rece=*ubranie;*ubranie=NULL;}
                                    else {Item*a=g->p_rece;g->p_rece=*ubranie;*ubranie=a;}
                                    }break;
                                    case 4:{if(g->ilosc_kieszeni<'1') show_message("Nie masz kieszeni!");
                                    else if(g->ilosc_kieszeni<'2' && g->p_kieszenl==NULL){g->p_kieszenl=*ubranie;*ubranie=NULL;}
                                    else if(g->ilosc_kieszeni<'3' && g->p_kieszenp==NULL){g->p_kieszenp=*ubranie;*ubranie=NULL;}
                                    else if(g->ilosc_kieszeni<'2'){Item*a=*ubranie;*ubranie=g->p_kieszenl;g->p_kieszenl=a;}
                                    }
                                    break;
                                    case 5:{informacje(*ubranie);}break;
                                    case 0:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&1 && ((jest_nad_ramieniem(myszka) && g->p_ramie!=NULL && (dla_funkcji=1)==1)||
                                               (jest_nad_glowa(myszka) && g->p_glowa!=NULL && (dla_funkcji=2)==2)||
                                               (jest_nad_plecakiem(myszka) && g->p_plecak!=NULL && (dla_funkcji=3)==3)||
                                               (jest_nad_rekami(myszka) && g->p_rece!=NULL && (dla_funkcji=4)==4)||
                                               (jest_nad_korpusem(myszka) && g->p_korpus!=NULL && (dla_funkcji=5)==5)||
                                               (jest_nad_rekawicami(myszka) && g->p_rekawice!=NULL && (dla_funkcji=6)==6)||
                                               (jest_nad_kieszenl(myszka) && g->p_kieszenl!=NULL && (dla_funkcji=7)==7)||
                                               (jest_nad_spodniami(myszka) && g->p_spodnie!=NULL && (dla_funkcji=8)==8)||
                                               (jest_nad_kieszenp(myszka) && g->p_kieszenp!=NULL && (dla_funkcji=9)==9)||
                                               (jest_nad_butami(myszka) && g->p_buty!=NULL && (dla_funkcji=10)==10)))
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
                           if(myszka.x>0 && myszka.x<args->X_kratka*22 && myszka.y>0 && myszka.y<args->Y_kratka*14)
                              {
                                    if(swiat->aktualna->ziemia[g->y][g->x]==NULL)swiat->aktualna->ziemia[g->y][g->x]=new Kontener<Item>();
                                    swiat->aktualna->ziemia[g->y][g->x]->dodaj_obiekt(ten);
                              }
                              else if(jest_nad_rekami(myszka)&&g->p_rece==NULL)
                              {
                                    g->p_rece=ten;
                              }
                              else if(jest_nad_kieszenl(myszka)&&g->p_kieszenl==NULL && ten->mozna_do_kieszeni())
                              {
                                    g->p_kieszenl=ten;
                              }
                              else if(jest_nad_kieszenp(myszka)&&g->p_kieszenp==NULL && ten->mozna_do_kieszeni())
                              {
                                    g->p_kieszenp=ten;
                              }
                              else if(((ten->jest_kapeluszem() && g->p_glowa==NULL)||(ten->jest_korpusem() && g->p_korpus==NULL)||(ten->jest_spodniami() && g->p_spodnie==NULL)
                                      ||(ten->jest_butami() && g->p_buty==NULL)||(ten->jest_rekawicami() && g->p_rekawice==NULL)
                                      ||(ten->jest_bronia() && g->p_ramie==NULL)||(ten->jest_plecakiem() && g->p_plecak==NULL)))
                              {
                                    {
                                                      if(ten->jest_kapeluszem() && g->p_glowa==NULL){g->p_glowa=ten;}
                                                      else if(ten->jest_korpusem() && g->p_korpus==NULL){g->p_korpus=ten;}
                                                      else if(ten->jest_spodniami() && g->p_spodnie==NULL){g->p_spodnie=ten;}
                                                      else if(ten->jest_butami() && g->p_buty==NULL){g->p_buty=ten;}
                                                      else if(ten->jest_rekawicami() && g->p_rekawice==NULL){g->p_rekawice=ten;}
                                                      else if(ten->jest_bronia() && g->p_ramie==NULL){g->p_ramie=ten;}
                                                      else if(ten->jest_plecakiem() && g->p_plecak==NULL){g->p_plecak=ten;}
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
                  else if(!g->ukryty && myszka.buttons&1 && jest_nad_strzalka_prawo(myszka) && swiat->zwroc_taka_plansze(g->px+1, g->py, g->pz)!=NULL && args->pp)
                  {
                           poczekaj_na_myszke(1);przesuwanie('p',myszka,klawiatura);
                  }
                  else if(!g->ukryty && myszka.buttons&1 && jest_nad_strzalka_dol(myszka) && swiat->zwroc_taka_plansze(g->px, g->py+1, g->pz)!=NULL &&args->dd)
                  {
                           poczekaj_na_myszke(1);przesuwanie('d',myszka,klawiatura);
                  }
                  else if(!g->ukryty && myszka.buttons&1 && jest_nad_strzalka_lewo(myszka) && swiat->zwroc_taka_plansze(g->px-1, g->py, g->pz)!=NULL &&args->ll)
                  {
                           poczekaj_na_myszke(1);przesuwanie('l',myszka,klawiatura);
                  }
                  else if(!g->ukryty && myszka.buttons&1 && jest_nad_strzalka_gora(myszka) && swiat->zwroc_taka_plansze(g->px, g->py-1, g->pz)!=NULL &&args->gg)
                  {
                           poczekaj_na_myszke(1);przesuwanie('g',myszka,klawiatura);
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

                  else if(Strefa::w_planszy(mx, my))
                  {
                  if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2&&Objekt::jest_prostopadle(g->x, g->y, mx,my))
                  {
                           //gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,1);
                           poczekaj_na_myszke(2);
                           Zombie*z=(Zombie*)p->otoczenie[my][mx];// Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [5],5,11);
                                    menu->item[0]=new specyfikacja_menu(new specyfikacja_menu*[3],3,16);
                                    menu->item[0]->item[0]=new specyfikacja_menu(NULL, 0, 1);menu->item[0]->item[1]=new specyfikacja_menu(NULL, 0, 2);menu->item[0]->item[2]=new specyfikacja_menu(NULL, 0, 3);
                                    menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[4],4,17);
                                    menu->item[1]->item[0]=new specyfikacja_menu(NULL, 0, 4);menu->item[1]->item[1]=new specyfikacja_menu(NULL, 0,5);menu->item[1]->item[2]=new specyfikacja_menu(NULL, 0, 6);menu->item[1]->item[3]=new specyfikacja_menu(NULL, 0, 7);
                                    menu->item[2]=new specyfikacja_menu(new specyfikacja_menu*[2],2,18);
                                    menu->item[2]->item[0]=new specyfikacja_menu(NULL, 0, 8);menu->item[2]->item[1]=new specyfikacja_menu(NULL, 0, 9);
                                    menu->item[3]=new specyfikacja_menu(new specyfikacja_menu*[2],2,19);
                                    menu->item[3]->item[0]=new specyfikacja_menu(NULL, 0, 10);menu->item[3]->item[1]=new specyfikacja_menu(NULL, 0, 11);
                                    menu->item[4]=new specyfikacja_menu(NULL,0,12);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:case 2: case 3:if(pobierz_punkty_ruchu_i_kondycje(3,1)){
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      int obr=g->obrazenia((Bron*)g->p_rece);
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      switch(pozycja_w_zwarciu(g->x, g->y, my,mx,p->otoczenie[my][mx]->zwrot))
                                                      {case 'p':break; case 'b':szansa=szansa*120/100;obr=obr*115/100;break;case 't':szansa=szansa*150/100;obr=obr*130/100;break;}
                                                      if(z->ofiara!=g) szansa=100;
                                                      if(z->ofiara!=g && g->p_rece->jest_mala_bronia()){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-10,0, g->wart_zajecia());}
                                                      else if(losuj(1,100)<=szansa){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-wybor,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      }break;
                                                      case 4:if(!g->jest_wsrod_blokow(z) && pobierz_punkty_ruchu(3)){///blok
                                                      int blok=int(((Bron*)g->p_rece)->get_blok());
                                                      if(z->oszolomiony()){blok=blok*120/100;}if(g->jest_wsrod_skupien(z)){blok=blok*150/100;}
                                                      blok=blok*(70+g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/100;
                                                      g->dodaj_blok((Zombie*)swiat->aktualna->otoczenie[my][mx], blok);
                                                      }break;
                                                      case 5:if(g->kratka_z_tylu_jest_wolna(mx,my) && pobierz_punkty_ruchu_i_kondycje(2,1)){
                                                      g->zwrot = g->daj_zwrot_do_punktu(mx, my);
                                                      int ub=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) ub=((Bron*)g->p_rece)->UB();
                                                      float wsp = g->postawa == 'r' ? 1 : (g->postawa == 's' ? 0.7 : 0.4);
                                                      if(g->przesun(g->kratka_z_tylu(mx,my),false)==dead) break;
                                                      if(p->otoczenie[my][mx]==z)
                                                      {if(z->oszolomiony()){ub+=10;}if(g->jest_wsrod_skupien(z)){ub+=30;}
                                                      if(losuj(1,100)<(40+ub)*wsp){g->dodaj_unik(swiat->aktualna->otoczenie[my][mx]);}
                                                      else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();}
                                                      }break;
                                                      case 6:if(((g->y>my && g->x+1<21 && p->otoczenie[g->y][g->x+1]==NULL && p->otoczenie[g->y-1][g->x+1]==NULL)||
                                                                 (g->y<my && g->x-1>-1 && p->otoczenie[g->y][g->x-1]==NULL && p->otoczenie[g->y+1][g->x-1]==NULL)||
                                                                 (g->x>mx && g->y-1>-1 && p->otoczenie[g->y-1][g->x]==NULL && p->otoczenie[g->y-1][g->x-1]==NULL)||
                                                                 (g->x<mx && g->y+1<13 && p->otoczenie[g->y+1][g->x]==NULL && p->otoczenie[g->y+1][g->x+1]==NULL))
                                                                && pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      int ub=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) ub=((Bron*)g->p_rece)->UB();
                                                      float wsp = g->postawa == 'r' ? 1 : (g->postawa == 's' ? 0.7 : 0.4);
                                                      if(g->y>my){if(g->przesun('p')==dead) break;;g->zwrot='d';if(g->przesun('g',false)==dead) break;;}
                                                      else if(g->y<my){if(g->przesun('l')==dead) break;g->zwrot='g';if(g->przesun('d',false)==dead) break;}
                                                      else if(g->x>mx){if(g->przesun('g')==dead) break;g->zwrot='p';if(g->przesun('l',false)==dead) break;}
                                                      else if(g->x<mx){if(g->przesun('d')==dead) break;g->zwrot='l';if(g->przesun('p',false)==dead) break;}
                                                      if(p->otoczenie[my][mx]==z){if(z->oszolomiony()){ub+=10;}if(g->jest_wsrod_skupien(z)){ub+=30;}
                                                      if(losuj(1,100)<(60+ub)*wsp){g->dodaj_unik((Zombie*)swiat->aktualna->otoczenie[my][mx]);}
                                                      else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();}
                                                      }break;
                                                      case 7:if(((g->y>my && g->x-1>-1 && p->otoczenie[g->y][g->x-1]==NULL && p->otoczenie[g->y-1][g->x-1]==NULL)||
                                                                 (g->y<my && g->x+1<21 && p->otoczenie[g->y][g->x+1]==NULL && p->otoczenie[g->y+1][g->x+1]==NULL)||
                                                                 (g->x>mx && g->y+1<13 && p->otoczenie[g->y+1][g->x]==NULL && p->otoczenie[g->y+1][g->x-1]==NULL)||
                                                                 (g->x<mx && g->y-1>-1 && p->otoczenie[g->y-1][g->x]==NULL && p->otoczenie[g->y-1][g->x+1]==NULL))
                                                                && pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      int ub=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) ub=((Bron*)g->p_rece)->UB();
                                                      float wsp = g->postawa == 'r' ? 1 : (g->postawa == 's' ? 0.7 : 0.4);
                                                      if(g->y>my){if(g->przesun('l')==dead) break;;g->zwrot='d';if(g->przesun('g',false)==dead) break;;}
                                                      else if(g->y<my){if(g->przesun('p')==dead) break;;g->zwrot='g';if(g->przesun('d',false)==dead) break;;}
                                                      else if(g->x>mx){if(g->przesun('d')==dead) break;;g->zwrot='p';if(g->przesun('l',false)==dead) break;;}
                                                      else if(g->x<mx){if(g->przesun('g')==dead) break;;g->zwrot='l';if(g->przesun('p',false)==dead) break;;}
                                                      if(p->otoczenie[my][mx]==z){if(z->oszolomiony()){ub+=10;}if(g->jest_wsrod_skupien(z)){ub+=30;}
                                                      if(losuj(1,100)<=(60+ub)*wsp){g->dodaj_unik((Zombie*)swiat->aktualna->otoczenie[my][mx]);}
                                                      else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();}
                                                      }break;
                                                      case 8:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///zmien sie pozycja
                                                      g->zwrot=w_ktora_to_strone(g->x,g->y,mx,my);
                                                      int do_czego=args->X_kratka; if(mx==g->x) do_czego=args->Y_kratka;
                                                      g->przesuniecie_x=0;g->przesuniecie_y=0;z->przesuniecie_x=0;z->przesuniecie_y=0;g->przesuwamy=true;z->przesuwamy=true;
                                                      for(int i=0; i<do_czego; i++)
                                                      {
                                                               if(g->x<mx) {g->przesuniecie_x=i;z->przesuniecie_x=-i;}
                                                               else if(g->x>mx) {g->przesuniecie_x=-i;z->przesuniecie_x=i;}
                                                               else if(g->y<my) {g->przesuniecie_y=i;z->przesuniecie_y=-i;}
                                                               else if(g->y>my) {g->przesuniecie_y=-i;z->przesuniecie_y=i;}
                                                               Sleep(375/do_czego);
                                                      }
                                                      g->przesuniecie_x=0;g->przesuniecie_y=0;z->przesuniecie_x=0;z->przesuniecie_y=0;g->przesuwamy=true;z->przesuwamy=true;
                                                      p->otoczenie[my][mx]=g;p->otoczenie[g->y][g->x]=z;
                                                      if(g->x<mx) {z->zwrot='l';}
                                                      else if(g->x>mx) {z->zwrot='p';}
                                                      else if(g->y<my) {z->zwrot='g';}
                                                      else if(g->y>my) {z->zwrot='d';}
                                                      p->zaktualizuj_widoki(mx,my,g->x,g->y); z->x=g->x; z->y=g->y; g->x=mx; g->y=my;
                                                      g->wydaj_dzwiek(false, 1,g->x,g->y,0);
                                                      z->reakcja_na_podloze(); if(g->reakcja_na_podloze()==dead) return;
                                                      }
                                                      case 9:if(pobierz_punkty_ruchu_i_kondycje(6,1)){///przewroc
                                                               z->przewroc();
                                                      }break;
                                                      case 10:if(pobierz_punkty_ruchu_i_kondycje(2,1)){///pchniecie
                                                               g->animacja_ataku(w_ktora_to_strone(g->x, g->y, mx, my));
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='t' && losuj(1,100)<=50+kb/2)||(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='b' || losuj(1,100)<=40+kb/2)||losuj(1,100)<=30+kb/2||(g->x<z->x &&(g->x+2>=21 || p->otoczenie[g->y][g->x+2]!=NULL))
                                                               ||(g->x>z->x &&(g->x-2<=-1 || p->otoczenie[g->y][g->x-2]!=NULL))||(g->y<z->y &&(g->y+2>=13 || p->otoczenie[g->y+2][g->x]!=NULL))
                                                               ||(g->y>z->y &&(g->y-2<=-1 || p->otoczenie[g->y-2][g->x]!=NULL));
                                                               if(z->przesun(Objekt::przeciwna(w_ktora_to_strone(z->x,z->y,g->x,g->y)),false)!=dead && p->otoczenie[my][mx]==z)
                                                               {if(przewrocenie)z->przewroc();if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}
                                                      }break;
                                                      case 11:if(pobierz_punkty_ruchu_i_kondycje(4,1)){///kopniecie
                                                               g->animacja_ataku(w_ktora_to_strone(g->x, g->y, mx, my));
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='t' && losuj(1,100)<=80+kb)||(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='b' && losuj(1,100)<=40+kb)||losuj(1,100)<=30+kb||(g->x<z->x &&(g->x+3>=21 || p->otoczenie[g->y][g->x+2]!=NULL || p->otoczenie[g->y][g->x+3]!=NULL))
                                                               ||(g->x>z->x &&(g->x-3<=-1 || p->otoczenie[g->y][g->x-2]!=NULL || p->otoczenie[g->y][g->x-3]!=NULL))
                                                               ||(g->y<z->y &&(g->y+3>=13 || p->otoczenie[g->y+2][g->x]!=NULL || p->otoczenie[g->y+3][g->x]!=NULL))
                                                               ||(g->y>z->y &&(g->y-3<=-1 || p->otoczenie[g->y-2][g->x]!=NULL || p->otoczenie[g->y-3][g->x]!=NULL));
                                                               char str=Objekt::przeciwna(w_ktora_to_strone(z->x,z->y,g->x,g->y));
                                                               if(z->przesun(str,false)!=dead){
                                                               if(z->przesun(str,false)!=dead){
                                                               if(przewrocenie)z->przewroc();
                                                               if(swiat->aktualny!=NULL && !g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                               if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}}
                                                      }break;
                                                      case 12:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                               g->dodaj_skupienie(z);
                                                      }break;
                                                      default:break;


                           }


                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece!=NULL && g->p_rece->jest_bronia_palna())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2&&Objekt::jest_prostopadle(g->x, g->y, mx,my))
                  {
                           poczekaj_na_myszke(2);
                           Zombie*z=(Zombie*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [5],5,29);
                                    menu->item[0]=new specyfikacja_menu(new specyfikacja_menu*[3],3,41);
                                    menu->item[0]->item[0]=new specyfikacja_menu(NULL, 0, 1);menu->item[0]->item[1]=new specyfikacja_menu(NULL, 0, 2);menu->item[0]->item[2]=new specyfikacja_menu(NULL, 0, 3);
                                    menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[3],3,42);
                                    menu->item[1]->item[0]=new specyfikacja_menu(NULL, 0, 4);menu->item[1]->item[1]=new specyfikacja_menu(NULL, 0,5);menu->item[1]->item[2]=new specyfikacja_menu(NULL, 0, 6);
                                    menu->item[2]=new specyfikacja_menu(new specyfikacja_menu*[2],2,18);
                                    menu->item[2]->item[0]=new specyfikacja_menu(NULL, 0, 8);menu->item[2]->item[1]=new specyfikacja_menu(NULL, 0, 9);
                                    menu->item[3]=new specyfikacja_menu(new specyfikacja_menu*[2],2,19);
                                    menu->item[3]->item[0]=new specyfikacja_menu(NULL, 0, 10);menu->item[3]->item[1]=new specyfikacja_menu(NULL, 0, 11);
                                    menu->item[4]=new specyfikacja_menu(NULL,0,12);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:case 2: case 3:if(g->mozna_strzelic(z) && pobierz_punkty_ruchu(3)){
                                             Bron* bron=(Bron*)g->p_rece;
                                             for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                             {
                                                      gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                      int obr=bron->get_obrazenia();int szansa=bron->get_szansa();
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=g->szansa(bron);
                                                      if(wybor==1) szansa=szansa*80/100;
                                                      int gdzie=-1; if(wybor!=1) gdzie=-wybor-2;
                                                      if(losuj(1,100)<=szansa)swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,gdzie,bron->get_krytyk(), g->wart_zajecia());
                                                      else Sleep(150);
                                                      g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                      --bron->mag;
                                             }
                                    }break;
                                                      case 4:if(!g->jest_wsrod_blokow(z) && pobierz_punkty_ruchu(3)){///blok
                                                      ///nie ma
                                                      }break;
                                                      case 5:if(g->kratka_z_tylu_jest_wolna(mx,my) && pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      int ub=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) ub=((Bron*)g->p_rece)->UB();
                                                      if(g->przesun(g->kratka_z_tylu(mx,my),false)==dead) break;;
                                                      float wsp = g->postawa == 'r' ? 1 : (g->postawa == 's' ? 0.7 : 0.4);
                                                      if(z==p->otoczenie[my][mx])
                                                      {if(z->oszolomiony()){ub+=10;}if(g->jest_wsrod_skupien(z)){ub+=30;}
                                                      if(losuj(1,100)<(40+ub)*wsp){g->dodaj_unik((Zombie*)swiat->aktualna->otoczenie[my][mx]);}
                                                      else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();}
                                                      }break;
                                                      case 6:if(((g->y>my && g->x+1<21 && p->otoczenie[g->y][g->x+1]==NULL && p->otoczenie[g->y-1][g->x+1]==NULL)||
                                                                 (g->y<my && g->x-1>-1 && p->otoczenie[g->y][g->x-1]==NULL && p->otoczenie[g->y+1][g->x-1]==NULL)||
                                                                 (g->x>mx && g->y-1>-1 && p->otoczenie[g->y-1][g->x]==NULL && p->otoczenie[g->y-1][g->x-1]==NULL)||
                                                                 (g->x<mx && g->y+1<13 && p->otoczenie[g->y+1][g->x]==NULL && p->otoczenie[g->y+1][g->x+1]==NULL))
                                                                && pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      int ub=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) ub=((Bron*)g->p_rece)->UB();
                                                      float wsp = g->postawa == 'r' ? 1 : (g->postawa == 's' ? 0.7 : 0.4);
                                                      if(g->y>my){if(g->przesun('p')==dead) break;;g->zwrot='d';if(g->przesun('g',false)==dead) break;;}
                                                      else if(g->y<my){if(g->przesun('l')==dead) break;;g->zwrot='g';if(g->przesun('d',false)==dead) break;;}
                                                      else if(g->x>mx){if(g->przesun('g')==dead) break;;g->zwrot='p';if(g->przesun('l',false)==dead) break;;}
                                                      else if(g->x<mx){if(g->przesun('d')==dead) break;;g->zwrot='l';if(g->przesun('p',false)==dead) break;;}
                                                      if(p->otoczenie[my][mx]==z){if(z->oszolomiony()){ub+=10;}if(g->jest_wsrod_skupien(z)){ub+=30;}
                                                      if(losuj(1,100)<(60+ub)*wsp){g->dodaj_unik((Zombie*)swiat->aktualna->otoczenie[my][mx]);}
                                                      else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();}
                                                      }break;
                                                      case 7:if(((g->y>my && g->x-1>-1 && p->otoczenie[g->y][g->x-1]==NULL && p->otoczenie[g->y-1][g->x-1]==NULL)||
                                                                 (g->y<my && g->x+1<21 && p->otoczenie[g->y][g->x+1]==NULL && p->otoczenie[g->y+1][g->x+1]==NULL)||
                                                                 (g->x>mx && g->y+1<13 && p->otoczenie[g->y+1][g->x]==NULL && p->otoczenie[g->y+1][g->x-1]==NULL)||
                                                                 (g->x<mx && g->y-1>-1 && p->otoczenie[g->y-1][g->x]==NULL && p->otoczenie[g->y-1][g->x+1]==NULL))
                                                                && pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      int ub=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) ub=((Bron*)g->p_rece)->UB();
                                                      float wsp = g->postawa == 'r' ? 1 : (g->postawa == 's' ? 0.7 : 0.4);
                                                      if(g->y>my){if(g->przesun('l')==dead) break;;g->zwrot='d';if(g->przesun('g',false)==dead) break;;}
                                                      else if(g->y<my){if(g->przesun('p')==dead) break;;g->zwrot='g';if(g->przesun('d',false)==dead) break;;}
                                                      else if(g->x>mx){if(g->przesun('d')==dead) break;;g->zwrot='p';if(g->przesun('l',false)==dead) break;;}
                                                      else if(g->x<mx){if(g->przesun('g')==dead) break;;g->zwrot='l';if(g->przesun('p',false)==dead) break;;}
                                                      if(p->otoczenie[my][mx]==z){if(z->oszolomiony()){ub+=10;}if(g->jest_wsrod_skupien(z)){ub+=30;}
                                                      if(losuj(1,100)<=(60+ub)*wsp){g->dodaj_unik((Zombie*)swiat->aktualna->otoczenie[my][mx]);}
                                                      else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();}
                                                      }break;
                                                      case 8:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///zmien sie pozycja
                                                      g->zwrot=w_ktora_to_strone(g->x,g->y,mx,my);
                                                      int do_czego=args->X_kratka; if(mx==g->x) do_czego=args->Y_kratka;
                                                      g->przesuniecie_x=0;g->przesuniecie_y=0;z->przesuniecie_x=0;z->przesuniecie_y=0;g->przesuwamy=true;z->przesuwamy=true;
                                                      for(int i=0; i<do_czego; i++)
                                                      {
                                                               if(g->x<mx) {g->przesuniecie_x=i;z->przesuniecie_x=-i;}
                                                               else if(g->x>mx) {g->przesuniecie_x=-i;z->przesuniecie_x=i;}
                                                               else if(g->y<my) {g->przesuniecie_y=i;z->przesuniecie_y=-i;}
                                                               else if(g->y>my) {g->przesuniecie_y=-i;z->przesuniecie_y=i;}
                                                               Sleep(375/do_czego);
                                                      }
                                                      g->przesuniecie_x=0;g->przesuniecie_y=0;z->przesuniecie_x=0;z->przesuniecie_y=0;g->przesuwamy=true;z->przesuwamy=true;
                                                      p->otoczenie[my][mx]=g;p->otoczenie[g->y][g->x]=z;
                                                      if(g->x<mx) {z->zwrot='l';}
                                                      else if(g->x>mx) {z->zwrot='p';}
                                                      else if(g->y<my) {z->zwrot='g';}
                                                      else if(g->y>my) {z->zwrot='d';}
                                                      p->zaktualizuj_widoki(mx,my,g->x,g->y); z->x=g->x; z->y=g->y; g->x=mx; g->y=my;
                                                      g->wydaj_dzwiek(false, 1,g->x,g->y,0);
                                                      z->reakcja_na_podloze(); if(g->reakcja_na_podloze()==dead) return;
                                                      }
                                                      case 9:if(pobierz_punkty_ruchu_i_kondycje(6,1)){///przewroc
                                                               z->przewroc();
                                                      }break;
                                                      case 10:if(pobierz_punkty_ruchu_i_kondycje(2,1)){///pchniecie
                                                               g->animacja_ataku(w_ktora_to_strone(g->x, g->y, mx, my));
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='t' && losuj(1,100)<=50+kb/2)||(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='b' || losuj(1,100)<=40+kb/2)||losuj(1,100)<=30+kb/2||(g->x<z->x &&(g->x+2>=21 || p->otoczenie[g->y][g->x+2]!=NULL))
                                                               ||(g->x>z->x &&(g->x-2<=-1 || p->otoczenie[g->y][g->x-2]!=NULL))||(g->y<z->y &&(g->y+2>=13 || p->otoczenie[g->y+2][g->x]!=NULL))
                                                               ||(g->y>z->y &&(g->y-2<=-1 || p->otoczenie[g->y-2][g->x]!=NULL));
                                                               if(z->przesun(Objekt::przeciwna(w_ktora_to_strone(z->x,z->y,g->x,g->y)),false)!=dead && p->otoczenie[my][mx]==z)
                                                               {if(przewrocenie)z->przewroc();if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}

                                                      }break;
                                                      case 11:if(pobierz_punkty_ruchu_i_kondycje(4,1)){///kopniecie
                                                               g->animacja_ataku(w_ktora_to_strone(g->x, g->y, mx, my));
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='t' && losuj(1,100)<=80+kb)||(pozycja_w_zwarciu(z->x,z->y,g->x,g->y,z->zwrot)=='b' && losuj(1,100)<=40+kb)||losuj(1,100)<=30+kb||(g->x<z->x &&(g->x+3>=21 || p->otoczenie[g->y][g->x+2]!=NULL || p->otoczenie[g->y][g->x+3]!=NULL))
                                                               ||(g->x>z->x &&(g->x-3<=-1 || p->otoczenie[g->y][g->x-2]!=NULL || p->otoczenie[g->y][g->x-3]!=NULL))
                                                               ||(g->y<z->y &&(g->y+3>=13 || p->otoczenie[g->y+2][g->x]!=NULL || p->otoczenie[g->y+3][g->x]!=NULL))
                                                               ||(g->y>z->y &&(g->y-3<=-1 || p->otoczenie[g->y-2][g->x]!=NULL || p->otoczenie[g->y-3][g->x]!=NULL));
                                                               char str=Objekt::przeciwna(w_ktora_to_strone(z->x,z->y,g->x,g->y));
                                                               if(z->przesun(str,false)!=dead){
                                                               if(z->przesun(str,false)!=dead){
                                                               if(przewrocenie)z->przewroc();
                                                               if(swiat->aktualny!=NULL && !g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                               if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}}
                                                      }break;
                                                      case 12:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                              g->dodaj_skupienie(z);
                                                      }break;
                                                      default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2&&Objekt::jest_z_ukosa(g->x, g->y, mx, my))
                  {
                           //gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,1);
                           poczekaj_na_myszke(2);Zombie*z=(Zombie*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [5],5,20);
                                    menu->item[0]=new specyfikacja_menu(new specyfikacja_menu*[2],2,20);
                                    menu->item[0]->item[0]=new specyfikacja_menu(NULL, 0, 1);menu->item[0]->item[1]=new specyfikacja_menu(NULL, 0, 2);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,3);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,4);
                                    menu->item[3]=new specyfikacja_menu(new specyfikacja_menu*[2],2,21);
                                    menu->item[3]->item[0]=new specyfikacja_menu(NULL, 0, 5);menu->item[3]->item[1]=new specyfikacja_menu(NULL, 0, 6);
                                    menu->item[4]=new specyfikacja_menu(NULL,0,7);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:case 2:if(pobierz_punkty_ruchu_i_kondycje(3,1)){
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      int obr=g->obrazenia((Bron*)g->p_rece);
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      obr=obr*(100-g->l_ramie_a-g->p_ramie_a-g->p_dlon_a-g->l_dlon_a)/100;
                                                      szansa=szansa*(100-g->l_ramie_a-g->p_ramie_a-g->p_dlon_a-g->l_dlon_a)/100;
                                                      switch(pozycja_w_zwarciu(g->x, g->y, my,mx,p->otoczenie[my][mx]->zwrot))
                                                      {case 'p':break; case 'b':szansa=szansa*120/100;obr=obr*115/100;break;case 't':szansa=szansa*150/100;obr=obr*130/100;break;}
                                                      if(z->ofiara!=g) szansa=100;
                                                      if(z->ofiara!=g && g->p_rece->jest_mala_bronia()){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-10,0,g->wart_zajecia());}
                                                      else if(losuj(1,100)<=szansa){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-wybor-1,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      }break;
                                    case 3:if(pobierz_punkty_ruchu_i_kondycje(6,1)){///zamach
                                                      g->przesuwamy=true;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                      int i,j;
                                                      for(i=0; i<args->X_kratka/2; i++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(j=0; j<args->Y_kratka/2; j++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(; i>0; --i){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(; j>0; --j){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      g->przesuwamy=false;g->przesuniecie_x=0;g->przesuniecie_y=0;

                                                      int szansa1=g->szansa((Bron*)g->p_rece);
                                                      int szansa2=g->szansa((Bron*)g->p_rece);
                                                      int szansa3=g->szansa((Bron*)g->p_rece);
                                                      int obr1=g->obrazenia((Bron*)g->p_rece),obr2=g->obrazenia((Bron*)g->p_rece),obr3=g->obrazenia((Bron*)g->p_rece);
                                                      szansa1=szansa1*9/10;szansa2=szansa2*9/10;szansa3=szansa3*9/10;
                                                      Zombie *z1=NULL,*z2=NULL,*z3=NULL;
                                                      int a1,a2;
                                                      if(g->x-1==mx && g->y-1==my){a1=g->x-1;a2=g->y-1;}
                                                      else if(g->x+1==mx && g->y-1==my){a1=g->x+1;a2=g->y-1;}
                                                      else if(g->x-1==mx && g->y+1==my){a1=g->x-1;a2=g->y+1;}
                                                      else if(g->x+1==mx && g->y+1==my){a1=g->x+1;a2=g->y+1;}
                                                      if(p->otoczenie[g->y][a1]!=NULL && p->otoczenie[g->y][a1]->czym_jest==2) z1=(Zombie*)p->otoczenie[g->y][a1];
                                                      if(p->otoczenie[a2][a1]!=NULL && p->otoczenie[a2][a1]->czym_jest==2) z2=(Zombie*)p->otoczenie[a2][a1];
                                                      if(p->otoczenie[a2][g->x]!=NULL && p->otoczenie[a2][g->x]->czym_jest==2) z3=(Zombie*)p->otoczenie[a2][g->x];
                                                      if(z1!=NULL && z1->oszolomiony()){szansa1=szansa1*110/100;obr1=obr1*120/100;}if(g->jest_wsrod_skupien(z1)){szansa1=szansa1*130/100;obr1=obr1*130/100;}
                                                      if(z2!=NULL && z2->oszolomiony()){szansa2=szansa2*110/100;obr2=obr2*120/100;}if(g->jest_wsrod_skupien(z2)){szansa2=szansa2*130/100;obr2=obr2*130/100;}
                                                      if(z3!=NULL && z3->oszolomiony()){szansa3=szansa3*110/100;obr3=obr3*120/100;}if(g->jest_wsrod_skupien(z3)){szansa3=szansa3*130/100;obr3=obr3*130/100;}
                                                      if(z1!=NULL){if(losuj(1,100)<=szansa1)z1->zostan_uderzony(obr1*45/100,-2,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());}
                                                      if(z2!=NULL){if(losuj(1,100)<=szansa2)z2->zostan_uderzony(obr2*65/100,-2,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());}
                                                      if(z3!=NULL){if(losuj(1,100)<=szansa3)z3->zostan_uderzony(obr3*45/100,-2,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());}
                                                      }break;
                                             case 4:if(!g->jest_wsrod_blokow(z) && pobierz_punkty_ruchu(3)){///blok
                                                      int blok=int(((Bron*)g->p_rece)->get_blok());
                                                      if(z->oszolomiony()){blok=blok*120/100;}if(g->jest_wsrod_skupien(z)){blok=blok*150/100;}
                                                      blok=blok*(70+g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/100;
                                                      g->dodaj_blok((Zombie*)swiat->aktualna->otoczenie[my][mx], blok);
                                                      }break;
                                             case 5:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      g->przesuwamy=true;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                      int i,j;
                                                      for(i=0; i<args->X_kratka/2; i++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(j=0; j<args->Y_kratka/2; j++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(; j>0; --j){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(; i>0; --i){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      g->przesuwamy=false;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=losuj(1,100)<=30+kb||(g->y<z->y && g->x<z->x &&(g->y+3>=13 || p->otoczenie[g->y+2][g->x+1]!=NULL || p->otoczenie[g->y+3][g->x+1]!=NULL))
                                                               ||(g->y>z->y && g->x<z->x  &&(g->y-3<=-1 || p->otoczenie[g->y-2][g->x+1]!=NULL || p->otoczenie[g->y-3][g->x+1]!=NULL))
                                                               ||(g->y<z->y && g->x>z->x  &&(g->y+3>=13 || p->otoczenie[g->y+2][g->x-1]!=NULL || p->otoczenie[g->y+3][g->x-1]!=NULL))
                                                               ||(g->y>z->y && g->x>z->x  &&(g->y-3<=-1 || p->otoczenie[g->y-2][g->x-1]!=NULL || p->otoczenie[g->y-3][g->x-1]!=NULL));
                                                               char str;if(g->y-1==my){str='g';}else if(g->y+1==my){str='d';}
                                                               if(z->przesun(str,false)!=dead){
                                                               if(z->przesun(str,false)!=dead){
                                                               if(swiat->aktualny!=NULL && !g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                               if(przewrocenie)z->przewroc();if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}}
                                             }break;
                                             case 6:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      g->przesuwamy=true;g->przesuniecie_x=0;g->przesuniecie_y=0;int i,j;
                                                      for(j=0; j<args->Y_kratka/2; j++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(i=0; i<args->X_kratka/2; i++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(; i>0; --i){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(; j>0; --j){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      g->przesuwamy=false;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=losuj(1,100)<=30+kb||(g->y<z->y && g->x<z->x &&(g->x+3>=21 || p->otoczenie[g->y+1][g->x+2]!=NULL || p->otoczenie[g->y+1][g->x+3]!=NULL))
                                                               ||(g->y>z->y && g->x<z->x  &&(g->x+3>=21 || p->otoczenie[g->y-1][g->x+2]!=NULL || p->otoczenie[g->y-1][g->x+3]!=NULL))
                                                               ||(g->y<z->y && g->x>z->x  &&(g->x-3<=-1 || p->otoczenie[g->y+1][g->x-2]!=NULL || p->otoczenie[g->y+1][g->x-3]!=NULL))
                                                               ||(g->y>z->y && g->x>z->x  &&(g->x-3<=-1 || p->otoczenie[g->y-1][g->x-2]!=NULL || p->otoczenie[g->y-1][g->x-3]!=NULL));
                                                               char str;if(g->x-1==mx){str='l';}else if(g->x+1==mx){str='p';}
                                                               else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                               if(z->przesun(str,false)!=dead){
                                                               if(z->przesun(str,false)!=dead){
                                                               if(przewrocenie)z->przewroc();if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}}
                                             }break;
                                             case 7:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                               g->dodaj_skupienie(z);
                                                      }break;
                                             default:break;
                           }


                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece!=NULL && g->p_rece->jest_bronia_palna())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2&&Objekt::jest_z_ukosa(g->x, g->y, mx, my))
                  {
                           //gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,1);
                           poczekaj_na_myszke(2);Zombie*z=(Zombie*)p->otoczenie[my][mx];// Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,34);
                                    menu->item[0]=new specyfikacja_menu(new specyfikacja_menu*[3],3,41);
                                    menu->item[0]->item[0]=new specyfikacja_menu(NULL, 0, 1);menu->item[0]->item[1]=new specyfikacja_menu(NULL, 0, 2);menu->item[0]->item[2]=new specyfikacja_menu(NULL, 0,3);
                                    menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[2],2,21);
                                    menu->item[1]->item[0]=new specyfikacja_menu(NULL, 0, 5);menu->item[1]->item[1]=new specyfikacja_menu(NULL, 0, 6);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,7);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:case 2:case 3:if(g->mozna_strzelic(z) && pobierz_punkty_ruchu(3)){
                                             Bron* bron=(Bron*)g->p_rece;
                                             for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                             {
                                                      gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                      int obr=g->obrazenia((Bron*)g->p_rece);
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                      if(wybor==1) szansa=szansa*80/100;
                                                      int gdzie=-1; if(wybor!=1) gdzie=-wybor-2;
                                                      if(losuj(1,100)<=szansa)swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,gdzie,bron->get_krytyk(),g->wart_zajecia());
                                                      else Sleep(150);
                                                      g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                      --bron->mag;
                                             }
                                    }break;
                                             case 5:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      g->przesuwamy=true;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                      int i,j;
                                                      for(i=0; i<args->X_kratka/2; i++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(j=0; j<args->Y_kratka/2; j++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(; j>0; --j){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(; i>0; --i){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      g->przesuwamy=false;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=losuj(1,100)<=30+kb||(g->y<z->y && g->x<z->x &&(g->y+3>=13 || p->otoczenie[g->y+2][g->x+1]!=NULL || p->otoczenie[g->y+3][g->x+1]!=NULL))
                                                               ||(g->y>z->y && g->x<z->x  &&(g->y-3<=-1 || p->otoczenie[g->y-2][g->x+1]!=NULL || p->otoczenie[g->y-3][g->x+1]!=NULL))
                                                               ||(g->y<z->y && g->x>z->x  &&(g->y+3>=13 || p->otoczenie[g->y+2][g->x-1]!=NULL || p->otoczenie[g->y+3][g->x-1]!=NULL))
                                                               ||(g->y>z->y && g->x>z->x  &&(g->y-3<=-1 || p->otoczenie[g->y-2][g->x-1]!=NULL || p->otoczenie[g->y-3][g->x-1]!=NULL));
                                                               char str;if(g->y-1==my){str='g';}else if(g->y+1==my){str='d';}
                                                               if(z->przesun(str,false)!=dead){
                                                               if(z->przesun(str,false)!=dead){
                                                               if(swiat->aktualny!=NULL && !g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                               if(przewrocenie)z->przewroc();if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}}
                                             }break;
                                             case 6:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      g->przesuwamy=true;g->przesuniecie_x=0;g->przesuniecie_y=0;int i,j;
                                                      for(j=0; j<args->Y_kratka/2; j++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      for(i=0; i<args->X_kratka/2; i++){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(; i>0; --i){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x-1==mx && g->y+1==my)){g->przesuniecie_x=-i;}
                                                               else if((g->x+1==mx && g->y-1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_x=i;}
                                                               Sleep(300/args->X_kratka);
                                                      }
                                                      for(; j>0; --j){
                                                               if((g->x-1==mx && g->y-1==my)||(g->x+1==mx && g->y-1==my)){g->przesuniecie_y=-j;}
                                                               else if((g->x-1==mx && g->y+1==my)||(g->x+1==mx && g->y+1==my)){g->przesuniecie_y=j;}
                                                               Sleep(300/args->Y_kratka);
                                                      }
                                                      g->przesuwamy=false;g->przesuniecie_x=0;g->przesuniecie_y=0;
                                                               int kb=0; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) kb=((Bron*)g->p_rece)->KB(); else if(g->p_rece==NULL) kb=20;
                                                               if(z->oszolomiony()){kb+=10;}if(g->jest_wsrod_skupien(z)){kb+=30;}
                                                               bool przewrocenie=losuj(1,100)<=30+kb||(g->y<z->y && g->x<z->x &&(g->x+3>=21 || p->otoczenie[g->y+1][g->x+2]!=NULL || p->otoczenie[g->y+1][g->x+3]!=NULL))
                                                               ||(g->y>z->y && g->x<z->x  &&(g->x+3>=21 || p->otoczenie[g->y-1][g->x+2]!=NULL || p->otoczenie[g->y-1][g->x+3]!=NULL))
                                                               ||(g->y<z->y && g->x>z->x  &&(g->x-3<=-1 || p->otoczenie[g->y+1][g->x-2]!=NULL || p->otoczenie[g->y+1][g->x-3]!=NULL))
                                                               ||(g->y>z->y && g->x>z->x  &&(g->x-3<=-1 || p->otoczenie[g->y-1][g->x-2]!=NULL || p->otoczenie[g->y-1][g->x-3]!=NULL));
                                                               char str;if(g->x-1==mx){str='l';}else if(g->x+1==mx){str='p';}
                                                               else if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                               if(z->przesun(str,false)!=dead){
                                                               if(z->przesun(str,false)!=dead){
                                                               if(przewrocenie)z->przewroc();if(swiat->aktualny!=NULL && !z->jest_ofiara){z->jest_cel=true; z->xc=g->x; z->yc=g->y;}}}
                                             }break;
                                             case 7:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                               g->dodaj_skupienie(z);
                                                      }break;
                                             default:break;
                           }


                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2
                          &&((g->x+2==mx && g->y==my)||(g->x-2==mx && g->y==my)||(g->x==mx && g->y+2==my)||(g->x==mx && g->y-2==my)))
                  {
                           poczekaj_na_myszke(2);Zombie*z=(Zombie*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,23);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,2);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      if(g->przesun(w_ktora_to_strone(g->x,g->y,mx,my))==dead) break;
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      int obr=g->obrazenia((Bron*)g->p_rece); obr=obr*120/100;
                                                      if(p->otoczenie[my][mx]==z)
                                                      {if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=szansa*110/100;
                                                      if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                      if(z->ofiara!=g) szansa=100;
                                                      if(z->ofiara!=g && g->p_rece->jest_mala_bronia()){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-10,0,g->wart_zajecia());}
                                                      else if(losuj(1,100)<=szansa){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-1,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());
                                                       if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      if(swiat->aktualna->otoczenie[my][mx]!=NULL && losuj(1,100) < szansa*0.4) z->przewroc();
                                                      }
                                    }break;
                                    case 2:if(g->p_rece!=NULL && g->mozna_strzelic(z) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Item*a=g->p_rece; g->p_rece=NULL;
                                             g->animacja_rzutu_przedmiotu(args,z->x, z->y, a);
                                             p->rzuc_na_ziemie(mx,my,a);
                                             int obr=a->wartosc_ataku_rzucanego(); int szansa=80-2*g->odleglosc_w_kratkach(z);
                                             if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                             if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                             if(losuj(1,100)<=szansa)z->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 3:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                      g->dodaj_skupienie(z);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2&&!Objekt::jest_z_ukosa(g->x, g->y, mx, my)&&!Objekt::jest_prostopadle(g->x, g->y, mx,my))
                  {
                           //gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,1);
                           poczekaj_na_myszke(2);Zombie*z=(Zombie*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,24);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(g->p_rece!=NULL && g->mozna_strzelic(z) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Bron*a=(Bron*)g->p_rece; g->p_rece=NULL;int obr=a->wartosc_ataku_rzucanego();
                                             g->animacja_rzutu_przedmiotu(args,z->x, z->y, a);
                                             if(a && a->wykorzystaj()){delete a;}else p->rzuc_na_ziemie(mx,my,a);
                                             int szansa=80-2*g->odleglosc_w_kratkach(z);
                                             if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                             if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                             if(losuj(1,100)<=szansa)z->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                    }break;
                                    case 2:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                      g->dodaj_skupienie(z);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece!=NULL && g->p_rece->jest_bronia_palna())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==2&&!Objekt::jest_z_ukosa(g->x, g->y, mx, my)&&!Objekt::jest_prostopadle(g->x, g->y, mx,my))
                  {
                           poczekaj_na_myszke(2);Zombie*z=(Zombie*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,37);
                                    menu->item[0]=new specyfikacja_menu(new specyfikacja_menu*[3],3,41);
                                    menu->item[0]->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[0]->item[1]=new specyfikacja_menu(NULL,0,2);
                                    menu->item[0]->item[2]=new specyfikacja_menu(NULL,0,3);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,4);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,5);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:case 2: case 3:if(g->mozna_strzelic(z) && pobierz_punkty_ruchu(3)){
                                             Bron* bron=(Bron*)g->p_rece;
                                             for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                             {
                                                      gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                      int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(z);
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=g->szansa(bron);
                                                      if(wybor==1) szansa=szansa*80/100;
                                                      int gdzie=-1; if(wybor!=1) gdzie=-wybor-2;
                                                      if(losuj(1,100)<=szansa)swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,gdzie,bron->get_krytyk(),g->wart_zajecia());
                                                      else Sleep(150);
                                                      g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                      --bron->mag;
                                             }
                                    }break;
                                    case 4:if(g->p_rece!=NULL && g->mozna_strzelic(z) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Item*a=g->p_rece; g->p_rece=NULL;
                                             g->animacja_rzutu_przedmiotu(args,z->x, z->y, a);
                                             p->rzuc_na_ziemie(mx,my,a);
                                             int obr=a->wartosc_ataku_rzucanego(); int szansa=80-2*g->odleglosc_w_kratkach(z);
                                             if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                             if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                             if(losuj(1,100)<=szansa)z->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 5:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){ ///skupienie
                                                      g->dodaj_skupienie(z);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && (p->otoczenie[my][mx]->czym_jest==8||p->otoczenie[my][mx]->czym_jest==9)
                          &&((g->x+2==mx && g->y==my)||(g->x-2==mx && g->y==my)||(g->x==mx && g->y+2==my)||(g->x==mx && g->y-2==my)))
                  {
                           poczekaj_na_myszke(2); Objekt_zywy *z=(Objekt_zywy*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,23);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,2);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                                      if(g->przesun(w_ktora_to_strone(g->x,g->y,mx,my))==dead) break;
                                                      if(p->otoczenie[my][mx]==z)
                                                      {g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      int obr=g->obrazenia((Bron*)g->p_rece); obr=obr*120/100;
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=szansa*110/100;
                                                      if(!g->jest_wsrod_skupien(z) && !z->oszolomiony()) z->zoszolom();
                                                      if((z->czym_jest==8 && z->jest_ofiara==false)||(z->czym_jest==9 &&z->ofiara!=g)) szansa=100;
                                                      if(losuj(1,100)<=szansa){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-1,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}}
                                    }break;
                                    case 2:if(g->p_rece!=NULL && g->mozna_strzelic(z) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Item*a=g->p_rece; g->p_rece=NULL;
                                             g->animacja_rzutu_przedmiotu(args,z->x, z->y, a);
                                             p->rzuc_na_ziemie(mx,my,a);
                                             int obr=a->wartosc_ataku_rzucanego(); int szansa=80-2*g->odleglosc_w_kratkach(z);
                                             if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                             if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                             if(losuj(1,100)<=szansa)z->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 3:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                      g->dodaj_skupienie(z);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && (p->otoczenie[my][mx]->czym_jest==8||p->otoczenie[my][mx]->czym_jest==9)&&!Objekt::jest_z_ukosa(g->x, g->y, mx, my)&&!Objekt::jest_prostopadle(g->x, g->y, mx,my))
                  {
                           poczekaj_na_myszke(2); Plansza*p=swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);;
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,24);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(g->p_rece!=NULL && g->mozna_strzelic(p->otoczenie[my][mx]) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Bron*a=(Bron*)g->p_rece; g->p_rece=NULL;int obr=a->wartosc_ataku_rzucanego();
                                             g->animacja_rzutu_przedmiotu(args,mx, my, a);
                                             if(a && a->wykorzystaj()){delete a;}else p->rzuc_na_ziemie(mx,my,a);
                                             int szansa=80-2*g->odleglosc_w_kratkach(p->otoczenie[my][mx]);
                                             if(((Objekt_zywy*)p->otoczenie[my][mx])->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                             if(g->jest_wsrod_skupien(p->otoczenie[my][mx])){szansa=szansa*130/100;obr=obr*130/100;}
                                             if(losuj(1,100)<=szansa)p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                    }break;
                                    case 2:if(!g->jest_wsrod_skupien(p->otoczenie[my][mx]) && pobierz_punkty_ruchu(2)){///skupienie
                                                      g->dodaj_skupienie(p->otoczenie[my][mx]);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && (p->otoczenie[my][mx]->czym_jest==8||p->otoczenie[my][mx]->czym_jest==9)&&(Objekt::jest_z_ukosa(g->x, g->y, mx, my)||Objekt::jest_prostopadle(g->x, g->y, mx, my)))
                  {
                           //gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,1);
                           poczekaj_na_myszke(2);Objekt_zywy*z=(Objekt_zywy*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,40);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu_i_kondycje(3,1)){
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      int obr=g->obrazenia((Bron*)g->p_rece);
                                                      if(z->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      obr=obr*(100-g->l_ramie_a-g->p_ramie_a-g->p_dlon_a-g->l_dlon_a)/100;
                                                      szansa=szansa*(100-g->l_ramie_a-g->p_ramie_a-g->p_dlon_a-g->l_dlon_a)/100;
                                                      switch(pozycja_w_zwarciu(g->x, g->y, my,mx,p->otoczenie[my][mx]->zwrot))
                                                      {case 'p':break; case 'b':szansa=szansa*120/100;obr=obr*115/100;break;case 't':szansa=szansa*150/100;obr=obr*130/100;break;}
                                                      if((z->czym_jest==8 && z->jest_ofiara==false)||(z->czym_jest==9 && z->ofiara!=g)) szansa=100;
                                                      if(losuj(1,100)<=szansa){swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,-wybor-1,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());}
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                                      }break;
                                             case 2:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                               g->dodaj_skupienie(z);
                                                      }break;
                                             default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece!=NULL && g->p_rece->jest_bronia_palna())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && (p->otoczenie[my][mx]->czym_jest==8||p->otoczenie[my][mx]->czym_jest==9)&&(Objekt::jest_prostopadle(g->x, g->y, mx,my)||Objekt::jest_prostopadle(g->x, g->y, mx,my)))
                  {
                           poczekaj_na_myszke(2);
                           Objekt*z=p->otoczenie[my][mx]; Plansza*p=swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);;
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,40);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(g->mozna_strzelic(z) && pobierz_punkty_ruchu(3)){
                                             Bron* bron=(Bron*)g->p_rece;
                                             for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                             {
                                                      gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                      int obr=bron->get_obrazenia();int szansa=bron->get_szansa();
                                                      if(((Objekt_zywy*)z)->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=g->szansa(bron);
                                                      if(wybor==1) szansa=szansa*80/100;
                                                      int gdzie=-1; if(wybor!=1) gdzie=-wybor-2;
                                                      if(losuj(1,100)<=szansa)swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,gdzie,bron->get_krytyk(),g->wart_zajecia());
                                                      else Sleep(150);
                                                      g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                      --bron->mag;
                                             }}break;
                                             case 2:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){///skupienie
                                                               g->dodaj_skupienie(z);
                                                      }break;
                                                      default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece!=NULL && g->p_rece->jest_bronia_palna())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && (p->otoczenie[my][mx]->czym_jest==8||p->otoczenie[my][mx]->czym_jest==9)&&!Objekt::jest_z_ukosa(g->x, g->y, mx, my)&&!Objekt::jest_prostopadle(g->x, g->y, mx,my))
                  {
                           poczekaj_na_myszke(2);Objekt*z=p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,41);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,2);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(g->mozna_strzelic(z) && pobierz_punkty_ruchu(3)){
                                             Bron* bron=(Bron*)g->p_rece;
                                             for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                             {
                                                      gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                      int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(z);
                                                      if(((Objekt_zywy*)z)->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=g->szansa(bron);
                                                      if(wybor==1) szansa=szansa*80/100;
                                                      int gdzie=-1; if(wybor!=1) gdzie=-wybor-2;
                                                      if(losuj(1,100)<=szansa)swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,gdzie,bron->get_krytyk(),g->wart_zajecia());
                                                      else Sleep(150);
                                                      g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                      --bron->mag;
                                             }
                                    }break;
                                    case 2:if(g->p_rece!=NULL && g->mozna_strzelic(z) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Item*a=g->p_rece; g->p_rece=NULL;
                                             g->animacja_rzutu_przedmiotu(args,z->x, z->y, a);
                                             p->rzuc_na_ziemie(mx,my,a);
                                             int obr=a->wartosc_ataku_rzucanego(); int szansa=80-2*g->odleglosc_w_kratkach(z);
                                             if(((Objekt_zywy*)z)->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                             if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                             if(losuj(1,100)<=szansa)z->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 3:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){ ///skupienie
                                                      g->dodaj_skupienie(z);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && (g->p_rece!=NULL && g->p_rece->jest_bronia_palna())&&myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && (p->otoczenie[my][mx]->czym_jest==8||p->otoczenie[my][mx]->czym_jest==9)&&(Objekt::jest_z_ukosa(g->x, g->y, mx, my)||Objekt::jest_prostopadle(g->x, g->y, mx,my)))
                  {
                           poczekaj_na_myszke(2);Objekt*z=p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,40);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(g->mozna_strzelic(z) && pobierz_punkty_ruchu(3)){
                                             Bron* bron=(Bron*)g->p_rece;
                                             for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                             {
                                                      gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                      int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(z);
                                                      if(((Objekt_zywy*)z)->oszolomiony()){szansa=szansa*110/100;obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100;obr=obr*130/100;}
                                                      szansa=g->szansa(bron);
                                                      if(wybor==1) szansa=szansa*80/100;
                                                      int gdzie=-1; if(wybor!=1) gdzie=-wybor-2;
                                                      if(losuj(1,100)<=szansa)swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,gdzie,bron->get_krytyk(),g->wart_zajecia());
                                                      else Sleep(150);
                                                      g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                      --bron->mag;
                                             }
                                    }break;
                                    case 3:if(!g->jest_wsrod_skupien(z) && pobierz_punkty_ruchu(2)){ ///skupienie
                                                      g->dodaj_skupienie(z);
                                                      }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }


                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==23&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Schowek*s=(Schowek*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,26);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu(3)){if(!s->otwarty) {s->zawartosc->dodaj_obiekt(Item::wylosuj_item('s'));s->otwarty=true;}
                                    znow:zalozylismy_nowy_plecak=false;
                                    s->zawartosc=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args,new Skrzynka(s->zawartosc, 9, s->zawartosc->ilosc*2+20)));
                                    if(zalozylismy_nowy_plecak)goto znow;
                                    }break;
                                    case 2:if(Objekt::jest_prostopadle(g->x,g->y,mx,my)&&pobierz_punkty_ruchu(3)){
                                             if(s->przesun(w_ktora_to_strone(g->x,g->y,mx,my))!=dead)
                                             {s->przesuwamy=false;s->przesuniecie_x=0; s->przesuniecie_y=0;}
                                    }break;
                                    case 3:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==25&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Schowek*s=(Schowek*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,39);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(true){spij(25, s);}break;
                                    case 2:if(pobierz_punkty_ruchu(3)){
                                    znoww:zalozylismy_nowy_plecak=false;
                                    s->zawartosc=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args,new Skrzynka(s->zawartosc, 9, s->zawartosc->ilosc*2+20)));
                                    if(zalozylismy_nowy_plecak)goto znoww;
                                    }break;
                                    case 3:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==20&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Schowek*s=(Schowek*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [1],1,27);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu_i_kondycje(4,1) && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())){
                                             g->animacja_ataku(w_ktora_to_strone(g->x, g->y, mx, my));
                                             int obr=1; if(g->p_rece!=NULL && g->p_rece->jest_bronia()) {obr=((Bron*)g->p_rece)->get_obrazenia();if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=((Bron*)g->p_rece);g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==26 && ((Okno*)p->otoczenie[my][mx])->mozna_stad_podejsc(g->x,g->y)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))
                          &&((Okno*)p->otoczenie[my][mx])->get_otwarte()==false&&((Okno*)p->otoczenie[my][mx])->get_wybite()==false&&((Okno*)p->otoczenie[my][mx])->get_jest_zaslona()&&((Okno*)p->otoczenie[my][mx])->get_zasloniete()==false)
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [4],4,43);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);menu->item[3]=new specyfikacja_menu(NULL,0,4);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:
                                             if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite()&&g->p_rece && g->p_rece->jest_bronia_palna() && g->mozna_strzelic(s) &&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL&& p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(4)){
                                             s->otworz();
                                            }break;
                                    case 3:if(pobierz_punkty_ruchu(3)){
                                             s->zaslon();
                                             }break;
                                    case 4:if(pobierz_punkty_ruchu(6)){
                                             s->zdejmij_zaslone();g->dostan_item(Item::stworz_obiekt(8006));
                                             }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==26 && ((Okno*)p->otoczenie[my][mx])->mozna_stad_podejsc(g->x,g->y)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))
                          &&((Okno*)p->otoczenie[my][mx])->get_otwarte()==false&&((Okno*)p->otoczenie[my][mx])->get_wybite()==false)
                  {
                           //std::cout<<"TTT";
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           int men=42; if(s->get_zasloniete()) men=45;
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,men);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:
                                             if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() &&g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL&& p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    case 2:if((men==42 && pobierz_punkty_ruchu(4))||(men==45 && pobierz_punkty_ruchu(3))){
                                             if(men==42) s->otworz();
                                             else if(men==45) s->odslon();
                                            }break;
                                    case 3:if((men==42 && g->p_rece!=NULL && g->p_rece->czym_jest==8006 && pobierz_punkty_ruchu(6))||(men==45 && pobierz_punkty_ruchu(6))){
                                             if(men==42){Item*a=g->p_rece;g->p_rece=NULL;delete a;s->zaloz_zaslone();}
                                             else if(men==45) {s->zdejmij_zaslone();g->dostan_item(Item::stworz_obiekt(8006));}
                                            }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==26 &&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [1],1,48);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:
                                    if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() && g->p_rece &&  g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL&& p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==26 && !(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,47);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(!s->get_wybite() && g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3)){
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite() &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                    }break;
                                    case 2:if(!s->get_wybite() && g->p_rece!=NULL && g->mozna_strzelic(p->otoczenie[my][mx]) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Bron*a=(Bron*)g->p_rece; g->p_rece=NULL;int obr=a->wartosc_ataku_rzucanego();
                                             g->animacja_rzutu_przedmiotu(args,mx, my, a);
                                             if(a && a->wykorzystaj()){delete a;}else p->rzuc_na_ziemie(mx,my,a);
                                             int szansa=80-2*g->odleglosc_w_kratkach(p->otoczenie[my][mx]);
                                             if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                    }break;

                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==27 &&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))
                  && (((Drzwi*)p->otoczenie[my][mx])->get_co_zamkniete()&1)!=1&& (((Drzwi*)p->otoczenie[my][mx])->get_co_zamkniete()&2)!=2&&(((Drzwi*)p->otoczenie[my][mx])->get_co_zamkniete()&128)!=128)
                  {
                           poczekaj_na_myszke(2);Drzwi*s=(Drzwi*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [5],5,49);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);menu->item[3]=new specyfikacja_menu(NULL,0,4);menu->item[4]=new specyfikacja_menu(NULL,0,5);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(4)){
                                              s->otworz();
                                              }break;
                                    case 3:if(pobierz_punkty_ruchu(2)){
                                             s->wydaj_dzwiek(false,10,s->x,s->y,27); s->otworz();
                                             }break;
                                    case 4:if(g->p_rece!=NULL && g->p_rece->jest_kluczem() && pobierz_punkty_ruchu(3)){
                                             s->zamknij_na_klucz((Klucz*)g->p_rece);
                                             }break;
                                    case 5:if(((s->get_co_zamkniete()&2)!=2 || (s->get_co_zamkniete()&1)!=1)&&g->p_rece!=NULL && g->p_rece->jest_klodkom() && pobierz_punkty_ruchu(5)){
                                             if(s->zaloz_klodke((Klodka*)g->p_rece)) g->p_rece=NULL;
                                             }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==27 &&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Drzwi*s=(Drzwi*)p->otoczenie[my][mx]; //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [4],4,50);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);menu->item[3]=new specyfikacja_menu(NULL,0,4);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(g->p_rece!=NULL && g->p_rece->jest_kluczem() && pobierz_punkty_ruchu(4)){
                                             s->otworz_klodke((Klucz*)g->p_rece);
                                    }break;
                                    case 3:if(g->p_rece!=NULL && (g->p_rece->czym_jest==8013) && pobierz_punkty_ruchu(4)){
                                             s->wylam_klodke(g->p_rece->czym_jest); Item*t=g->p_rece; g->p_rece=NULL; delete t;
                                              }
                                    case 4:if((s->get_co_zamkniete()&2!=2 || s->get_co_zamkniete()&1!=1)&&g->p_rece!=NULL && g->p_rece->jest_klodkom() && pobierz_punkty_ruchu(5)){
                                             if(s->zaloz_klodke((Klodka*)g->p_rece)) g->p_rece=NULL;
                                             }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==30 && ((Szafa*)p->otoczenie[my][mx])->ukrywa_go(g))
                  {///szafa gdy sie w niej ukrywamy

                           poczekaj_na_myszke(2); Szafa *s = (Szafa*)p->otoczenie[my][mx];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3, 256+512+4096);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,2);
                                    menu->item[2]=new specyfikacja_menu(NULL,0,3);

                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){

                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(3)){s->stworz_loot();
                                    znow1:zalozylismy_nowy_plecak=false;
                                    s->zawartosc=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args,new Skrzynka(s->zawartosc, 9, s->zawartosc->ilosc*2+20)));
                                    if(zalozylismy_nowy_plecak)goto znow1;
                                    }break;
                                    case 3:if(pobierz_punkty_ruchu_i_kondycje(5,1)){
                                             s->wyjdz();
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==30 && !(p->otoczenie[my][mx]->jest_naprzeciw_nas(g->x, g->y)) && Objekt::zaraz_obok(g->x,g->y,mx,my))
                  {///szafa gdy jestesmy nie od frontu
                           poczekaj_na_myszke(2); Szafa *s = (Szafa*)p->otoczenie[my][mx];
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [1+prost],1+prost,256+prost*1024);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    if(prost)
                                    {
                                             menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[2],2,45);
                                             menu->item[1]->item[0] = new specyfikacja_menu(NULL,0,2);
                                             menu->item[1]->item[1] = new specyfikacja_menu(NULL,0,3);
                                    }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             s->przesun(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 3:if(pobierz_punkty_ruchu_i_kondycje(4,1)){
                                             g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa = g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(s==p->otoczenie[my][mx]) s->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if (aaa==dead) break;
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==30 && p->otoczenie[my][mx]->jest_naprzeciw_nas(g->x, g->y))
                  {///szafa gdy jestesmy od frontu
                           poczekaj_na_myszke(2); Szafa *s = (Szafa*)p->otoczenie[my][mx];
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3+prost],3+prost,256+prost*1024+512+2048);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(NULL,0,2);
                                    if(prost)
                                    {
                                             menu->item[2]=new specyfikacja_menu(new specyfikacja_menu*[2],2,45);
                                             menu->item[2]->item[0] = new specyfikacja_menu(NULL,0,5);
                                             menu->item[2]->item[1] = new specyfikacja_menu(NULL,0,6);
                                             menu->item[3]=new specyfikacja_menu(NULL,0,3);
                                    }
                                    else
                                    {
                                             menu->item[2]=new specyfikacja_menu(NULL,0,3);
                                    }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(3)){s->stworz_loot();
                                    znow2:zalozylismy_nowy_plecak=false;
                                    s->zawartosc=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args,new Skrzynka(s->zawartosc, 9, s->zawartosc->ilosc*2+20)));
                                    if(zalozylismy_nowy_plecak)goto znow2;
                                    }break;
                                    case 3:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///ukryj sie
                                             s->wejdz(g);
                                    }break;
                                    case 5:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///pchnij
                                             s->przesun(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 6:if(pobierz_punkty_ruchu_i_kondycje(4,1)){///pociagnij
                                             g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa = g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(p->otoczenie[my][mx]==s) s->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if (aaa==dead) break;
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==29 && Objekt::zaraz_obok(g->x,g->y,mx,my))
                  {
                           poczekaj_na_myszke(2); Krzeslo *s = (Krzeslo*)p->otoczenie[my][mx];
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2+prost],2+prost,256+32768+prost*1024);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    if(prost)
                                    {
                                             menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[2],2,45);
                                             menu->item[1]->item[0] = new specyfikacja_menu(NULL,0,5);
                                             menu->item[1]->item[1] = new specyfikacja_menu(NULL,0,6);
                                             menu->item[2]=new specyfikacja_menu(NULL,0,3);
                                    }
                                    else
                                    {
                                             menu->item[1]=new specyfikacja_menu(NULL,0,3);
                                    }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 3:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///wez
                                            swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz)->otoczenie[s->y][s->x] = NULL;
                                             delete s; s=NULL;
                                             g->dostan_item(Item::stworz_obiekt(4009));
                                    }break;
                                    case 5:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///pchnij
                                             s->przesun(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 6:if(pobierz_punkty_ruchu_i_kondycje(4,1)){///pociagnij
                                             g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa = g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(p->otoczenie[my][mx]==s) s->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if (aaa==dead) break;
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==31 && ((Stol*)p->otoczenie[my][mx])->ukrywa_go(g))
                  {///stole gdy sie w nim my ukrywamy
                           poczekaj_na_myszke(2); Stol *s = (Stol*)p->otoczenie[my][mx];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2, 256+4096);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[4],4,48);
                                    menu->item[1]->item[0]=new specyfikacja_menu(NULL,0,2);
                                    menu->item[1]->item[1]=new specyfikacja_menu(NULL,0,3);
                                    menu->item[1]->item[2]=new specyfikacja_menu(NULL,0,4);
                                    menu->item[1]->item[3]=new specyfikacja_menu(NULL,0,5);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(5)){s->wyjdz('p');}break;
                                    case 3:if(pobierz_punkty_ruchu(5)){s->wyjdz('l');}break;
                                    case 4:if(pobierz_punkty_ruchu(5)){s->wyjdz('g');}break;
                                    case 5:if(pobierz_punkty_ruchu(5)){s->wyjdz('d');}break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==31 && Objekt::zaraz_obok(g->x,g->y,mx,my))
                  {///stol
                           poczekaj_na_myszke(2); Stol *s = (Stol*)p->otoczenie[my][mx];
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           specyfikacja_menu* menu=
                                    new specyfikacja_menu(new  specyfikacja_menu* [1+(!s->przewrocony)*2+prost+prost+s->jest_obrus],
                                                          1+(!s->przewrocony)*2+prost+s->jest_obrus+prost,
                                                          256+512*(!s->przewrocony)+prost*1024+prost*65536+2048*s->jest_obrus+8192*s->jest_obrus+16384*(!s->przewrocony&&!s->jest_obrus));
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    if(s->przewrocony)
                                    {
                                             if(prost)
                                             {
                                                      menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[3],3,47);
                                                      menu->item[1]->item[0] = new specyfikacja_menu(NULL,0,5);
                                                      menu->item[1]->item[1] = new specyfikacja_menu(NULL,0,6);
                                                      menu->item[1]->item[2] = new specyfikacja_menu(NULL,0,8);
                                                      menu->item[2]=new specyfikacja_menu(NULL,0,10);
                                             }
                                    }
                                    else
                                    {
                                             menu->item[1] = new specyfikacja_menu(NULL,0,2);
                                             if(prost)
                                             {
                                                      menu->item[2]=new specyfikacja_menu(new specyfikacja_menu*[3],3,46);
                                                      menu->item[2]->item[0] = new specyfikacja_menu(NULL,0,5);
                                                      menu->item[2]->item[1] = new specyfikacja_menu(NULL,0,6);
                                                      menu->item[2]->item[2] = new specyfikacja_menu(NULL,0,9);
                                             }
                                             if(s->jest_obrus)
                                             {
                                                      menu->item[2+prost]=new specyfikacja_menu(NULL,0,7);
                                                      menu->item[3+prost]=new specyfikacja_menu(NULL,0,4);
                                                      menu->item[4+prost]=new specyfikacja_menu(NULL, 0, 10);
                                             }
                                             else
                                             {
                                                      menu->item[2+prost]=new specyfikacja_menu(NULL,0,3);
                                                      menu->item[3+prost]=new specyfikacja_menu(NULL, 0, 10);
                                             }
                                    }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2: if(pobierz_punkty_ruchu(3)){///przeszukaj
                                    znow3:zalozylismy_nowy_plecak=false;
                                    s->zawartosc=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args,new Skrzynka(s->zawartosc, 9, s->zawartosc->ilosc*2+20)));
                                    if(zalozylismy_nowy_plecak)goto znow3;
                                    }break;
                                             break;
                                    case 3:if(g->p_rece!=NULL && g->p_rece->czym_jest == 8006 && pobierz_punkty_ruchu_i_kondycje(3,1)){///daj_obrus
                                                      Inne*o = (Inne*)g->p_rece; g->p_rece = NULL; delete o; s->jest_obrus = true;
                                    }break;
                                    case 4:if(pobierz_punkty_ruchu(4))///wez_obrus
                                             {
                                                      g->dostan_item(Item::stworz_obiekt(8006)); s->jest_obrus = false;
                                             }
                                             break;
                                    case 5:if(s->ukrywa_go(NULL) && pobierz_punkty_ruchu_i_kondycje(3,1)){///pchnij
                                             s->przesun(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 6:if(s->ukrywa_go(NULL) && pobierz_punkty_ruchu_i_kondycje(4,1)){///pociagnij
                                             g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa = g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(p->otoczenie[my][mx]==s) s->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if (aaa==dead) break;
                                    }break;
                                    case 7:if(s->ukrywa_go(NULL) && pobierz_punkty_ruchu(3))///ukryj sie
                                    {
                                             s->wejdz(g);
                                    }break;
                                    case 8:if(pobierz_punkty_ruchu(5))///podnies
                                    {
                                             s->przewrocony = false;
                                    }break;
                                    case 9:if(s->ukrywa_go(NULL) && pobierz_punkty_ruchu(3))///przewroc
                                    {
                                             if(s->jest_obrus)
                                             {
                                                      s->jest_obrus = false; s->zawartosc->dodaj_obiekt(Item::stworz_obiekt(8006));
                                             }
                                             s->przewrocony = true; swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz)->rzuc_na_ziemie(s->x, s->y, s->zawartosc);
                                    }break;
                                    case 10:
                                             {
                                                      if(g->p_ruchu>=4  && pobierz_punkty_ruchu(4)&& g->przejdz_nad_pod_objektem(mx, my));///przejdz nad pod
                                             }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==32 && Objekt::zaraz_obok(g->x,g->y,mx,my))
                  {///lozko
                           poczekaj_na_myszke(2); Lozko *s = (Lozko*)p->otoczenie[my][mx];
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           bool przes = s->jest_przescieradlo;
                           specyfikacja_menu* menu=
                                    new specyfikacja_menu(new  specyfikacja_menu* [3+prost*2],3+prost*2,
                                                          256+prost*1024+8192*przes+16384*(!przes)+prost*65536+131072);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    if(prost)
                                    {
                                             menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[2],2,45);
                                             menu->item[1]->item[0] = new specyfikacja_menu(NULL,0,5);
                                             menu->item[1]->item[1] = new specyfikacja_menu(NULL,0,6);

                                             menu->item[2]=new specyfikacja_menu(NULL,0,przes ? 4 : 3);
                                             menu->item[3]=new specyfikacja_menu(NULL,0,10);
                                             menu->item[4]=new specyfikacja_menu(NULL,0,7);
                                    }
                                    else
                                    {
                                             menu->item[1]=new specyfikacja_menu(NULL,0,przes ? 4 : 3);
                                             menu->item[2]=new specyfikacja_menu(NULL,0,7);
                                    }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 3:if(g->p_rece!=NULL && g->p_rece->czym_jest == 8006 && pobierz_punkty_ruchu_i_kondycje(3,1)){///daj_obrus
                                                      Inne*o = (Inne*)g->p_rece; g->p_rece = NULL; delete o; s->jest_przescieradlo = true;
                                    }break;
                                    case 4:if(pobierz_punkty_ruchu(4))///wez_obrus
                                             {
                                                      g->dostan_item(Item::stworz_obiekt(8006)); s->jest_przescieradlo = false;
                                             }
                                             break;
                                    case 5:if(s->spi_tu(NULL) && pobierz_punkty_ruchu_i_kondycje(3,1)){///pchnij
                                             s->przesun(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 6:if(s->spi_tu(NULL) && pobierz_punkty_ruchu_i_kondycje(4,1)){///pociagnij
                                             g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa = g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(p->otoczenie[my][mx]==s) s->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if (aaa==dead) break;
                                    }break;
                                    case 7:if(s->spi_tu(NULL) && pobierz_punkty_ruchu(3))///spij
                                    {
                                             spij(32, s);
                                    }break;
                                    case 10:
                                             {
                                                      if(g->p_ruchu>=4 && g->przejdz_nad_pod_objektem(mx, my) && pobierz_punkty_ruchu(4));///przejdz nad pod
                                             }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==33 && ((Ukryty_pod*)p->otoczenie[my][mx])->ukrywa_go(g))
                  {///zwloki gdy sie w nich my ukrywamy
                           poczekaj_na_myszke(2); Ukryty_pod *s = (Ukryty_pod*)p->otoczenie[my][mx];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [1],1, 4096);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu_i_kondycje(5,1)){
                                        s->wyjdz_spod();
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->otoczenie[my][mx]!=NULL && p->otoczenie[my][mx]->czym_jest==34 && (Objekt::zaraz_obok(g->x,g->y,mx,my)||(g->p_rece && g->p_rece->jest_bronia_palna())))
                  {///beczka
                           poczekaj_na_myszke(2); Beczka *s = (Beczka*)p->otoczenie[my][mx];
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           bool obok = Objekt::zaraz_obok(g->x,g->y,mx,my);

                           specyfikacja_menu* menu=
                                    new specyfikacja_menu(new  specyfikacja_menu* [1+(prost&&obok)+(obok&&!(s->lezy()&&s->jest_otwarta()&&!s->jest_Ropa()))],
                                                          1+(prost&&obok)+(obok&&!(s->lezy()&&s->jest_otwarta()&&!s->jest_Ropa())),
                                                          256+(prost&&obok)*1024+(obok&&!(s->lezy()&&s->jest_otwarta()&&!s->jest_Ropa()))*262144*(s->jest_otwarta() ? 2 : 1));

                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);

                                    if(prost&&obok)
                                    {
                                             if(s->lezy())
                                             {
                                                      menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[5],5,49);
                                                      for(short i=2;i<7;++i)
                                                               menu->item[1]->item[i-2] = new specyfikacja_menu(NULL, 0, i);
                                             }
                                             else
                                             {
                                                      menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[3],3,46);
                                                      menu->item[1]->item[0] = new specyfikacja_menu(NULL, 0, 4);
                                                      menu->item[1]->item[1] = new specyfikacja_menu(NULL, 0, 2);
                                                      menu->item[1]->item[2] = new specyfikacja_menu(NULL, 0, 9);
                                             }
                                             if(obok&&!(s->lezy()&&s->jest_otwarta()&&!s->jest_Ropa()))
                                                      {menu->item[2]=new specyfikacja_menu(NULL, 0, s->jest_otwarta() ? 8 : 7);}
                                    }
                                    else if(obok&&!(s->lezy()&&s->jest_otwarta()&&!s->jest_Ropa()))
                                    {
                                             menu->item[1]=new specyfikacja_menu(NULL, 0, s->jest_otwarta() ? 8 : 7);
                                    }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             if(g->p_rece==NULL || g->p_rece->jest_bronia_biala())
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      p->otoczenie[my][mx]->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                             else if(g->p_rece && g->p_rece->jest_bronia_palna() && g->mozna_strzelic(s))
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && p->otoczenie[my][mx]!=NULL;++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=g->obrazenia((Bron*)g->p_rece);
                                                               int szansa=g->szansa((Bron*)g->p_rece);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa) swiat->aktualna->otoczenie[my][mx]->zostan_uderzony(obr,0,bron->get_krytyk(),-1);
                                                               else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               swiat->aktualna->dzwiek(false, 5, mx, my, 34);
                                                               --bron->mag;
                                                      }
                                             }

                                    }break;
                                    case 2: if(pobierz_punkty_ruchu(4)){///pociagnij
                                             g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa = g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(p->otoczenie[my][mx]==s) s->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if (aaa==dead) break;
                                    }break;
                                             break;
                                    case 3:if(pobierz_punkty_ruchu(5)){///podnies
                                                      s->podnies();
                                    }break;
                                    case 4:if(pobierz_punkty_ruchu(3)){///pchnij o 1
                                             s->przesun(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 5:if(pobierz_punkty_ruchu(4)){///pchnij o 4
                                             for(short i=0; i<4; ++i) if(s->przesun(w_ktora_to_strone(g->x,g->y,mx,my))==dead) break;
                                    }break;
                                    case 6:if(pobierz_punkty_ruchu(4))///ochnij o 8
                                    {
                                             for(short i=0; i<8; ++i) if(s->przesun(w_ktora_to_strone(g->x,g->y,mx,my))==dead) break;
                                    }break;
                                    case 7:if(pobierz_punkty_ruchu(3))///otworz
                                    {
                                             s->otworz();
                                    }break;
                                    case 8:///zamknij
                                             if(pobierz_punkty_ruchu(3)){
                                                      s->zamknij();
                                             }break;
                                    case 9:if(pobierz_punkty_ruchu(5))///przewroc
                                    {
                                             s->przewroc_mnie(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }































                  else if(!g->ukryty && (g->p_rece==NULL || g->p_rece->jest_bronia_biala())&&myszka.buttons&2&& (u=daj_upadlego(mx, my, swiat->aktualna))!=NULL&& u->getA()->czym_jest==2 &&(Objekt::jest_prostopadle(g->x, g->y, u->getX(), u->getY()) || Objekt::jest_z_ukosa(g->x, g->y, u->getX(), u->getY())))
                  {

                           //gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,1);
                           poczekaj_na_myszke(2);
                           Zombie*z=(Zombie*)(u->getA()); Plansza*p=swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,52);
                                    menu->item[0]=new specyfikacja_menu(new specyfikacja_menu*[3],3,16);
                                    menu->item[0]->item[0]=new specyfikacja_menu(NULL, 0, 1);
                                    menu->item[0]->item[1]=new specyfikacja_menu(NULL, 0, 2);
                                    menu->item[0]->item[2]=new specyfikacja_menu(NULL, 0, 3);
                                    menu->item[1]=new specyfikacja_menu(new specyfikacja_menu*[3],3,16);
                                    menu->item[1]->item[0]=new specyfikacja_menu(NULL, 0, 4);
                                    menu->item[1]->item[1]=new specyfikacja_menu(NULL, 0, 5);
                                    menu->item[1]->item[2]=new specyfikacja_menu(NULL, 0, 6);

                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:case 2: case 3:if(pobierz_punkty_ruchu_i_kondycje(3,1)){
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int szansa=g->szansa((Bron*)g->p_rece);
                                                      int obr=g->obrazenia((Bron*)g->p_rece);
                                                      if(wybor==1)szansa=szansa*70/100;
                                                      else if(wybor ==3) szansa = 100;
                                                      else if(wybor == 2) szansa *= 1.3;
                                                      if((((Objekt_zywy*)z)->oszolomiony())){szansa=szansa*110/100; obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100; obr=obr*130/100;}
                                                      if(z->ofiara!=g) szansa=100;
                                                      obr *= 1.5;
                                                      if(z->ofiara!=g && g->p_rece->jest_mala_bronia()){z->zostan_uderzony(obr,-10,0, g->wart_zajecia());}
                                                      else if(losuj(1,100)<=szansa){z->zostan_uderzony(obr,-wybor,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia());}
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                                      }break;
                                    case 4:case 5: case 6:if(pobierz_punkty_ruchu_i_kondycje(3,1)){
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));int szansa=100;
                                                      int obr=((Ubranie*)g->p_buty)->obrazenia_butow();
                                                      obr=obr*(75+(g->l_udo_a+g->l_golen_a>g->p_udo_a+g->p_golen_a?g->l_udo_a+g->l_golen_a:g->p_udo_a+g->p_golen_a))/100;;
                                                      if(wybor-3==1)szansa=40;
                                                      if((((Objekt_zywy*)z)->oszolomiony())){szansa=szansa*110/100; obr=obr*120/100;}
                                                      if(g->jest_wsrod_skupien(z)){szansa=szansa*130/100; obr=obr*130/100;}
                                                      if(z->ofiara!=g) szansa=100;
                                                      obr *= 1.5;
                                                      if(losuj(1,100)<=szansa){z->zostan_uderzony(obr,-wybor+3,((Bron*)g->p_rece)->get_krytyk(),g->wart_zajecia()-3);}
                                                      if(g->p_buty && ((Ubranie*)g->p_buty)->wykorzystaj()){Ubranie*a=(Ubranie*)g->p_buty;g->p_buty=NULL;delete a;}
                                                      }break;




                                                      default:break;


                           }


                           delete menu; menu=NULL;
                  }


                  else if(!g->ukryty && (myszka.buttons & 2) && mx>=gracz->x-1 && mx<=gracz->x+1 && my>=gracz->y-1 && my<=gracz->y+1 && swiat->aktualna->ziemia[my][mx]!=NULL && pobierz_punkty_ruchu(3))
                  {
                           poczekaj_na_myszke(2);specyfikacja_menu** n=new specyfikacja_menu*(); n[0]=new specyfikacja_menu(NULL, 0, 1);
                           specyfikacja_menu* menu=new specyfikacja_menu(n, 1, 5);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 1:if(pobierz_punkty_ruchu(3)){


                                             znowu:

                                             zalozylismy_nowy_plecak=false;
                                             Kontener<Item>*z=swiat->aktualna->ziemia[my][mx];
                                             swiat->aktualna->ziemia[my][mx]=Skrzynka::zamien_skrzynke_na_itemy(otwarty_ekw(myszka,klawiatura,args, new Skrzynka(swiat->aktualna->ziemia[my][mx],9,20+swiat->aktualna->ziemia[my][mx]->ilosc*2)));
                                             z->wywal_wszystkie_objekty();///XD wczesniej dzialalo bez tego
                                             delete z;
                                             if(zalozylismy_nowy_plecak) goto znowu;

                                             if(swiat->aktualna->ziemia[my][mx]->ilosc==0) {delete swiat->aktualna->ziemia[my][mx];swiat->aktualna->ziemia[my][mx]=NULL;}}
                                             break;
                                    default: case 0: break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2  &&mx>=gracz->x-1 && mx<=gracz->x+1 && my>=gracz->y-1 && my<=gracz->y+1 && swiat->aktualna->srodowisko[my][mx]!=NULL&&
                          swiat->aktualna->srodowisko[my][mx]->wierzch()->czym_jest==100)
                  {
                           poczekaj_na_myszke(2); Gracz*g=swiat->aktualny;
                           Plansza*pl=swiat->aktualna;
                           Zwloki*o=(Zwloki*)swiat->aktualna->srodowisko[my][mx]->wierzch();
                           bool prost = Objekt::jest_prostopadle(g->x,g->y,mx,my);
                           bool zombie = (o->czyje_zwloki==2);
                           specyfikacja_menu* menu=new specyfikacja_menu(new specyfikacja_menu*[2+prost+zombie], 2+prost+zombie
                                                                         , 256+512+prost*1024+zombie*2048);

                           menu->item[0]=new specyfikacja_menu(NULL,0,1);
                           menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           if(prost)
                           {
                                    menu->item[2]=new specyfikacja_menu(new specyfikacja_menu*[2],2,45);
                                    menu->item[2]->item[0] = new specyfikacja_menu(NULL,0,5);
                                    menu->item[2]->item[1] = new specyfikacja_menu(NULL,0,6);
                           }
                           if(zombie)
                           {
                                    menu->item[prost+2]=new specyfikacja_menu(NULL,0,3);
                           }
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {



                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             o->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;///zniszcz
                                    case 2:break;///przeszukaj
                                    case 3:if(pl->otoczenie[my][mx]==NULL && pobierz_punkty_ruchu(3)){
                                            o->ukryj_sie_pod(g);


                                        }break;///schowaj sie
                                    case 5:if(pobierz_punkty_ruchu_i_kondycje(3,1)){///pchnij
                                            o->przesun_po_srodowisku(w_ktora_to_strone(g->x,g->y,mx,my));
                                    }break;
                                    case 6:if(pobierz_punkty_ruchu_i_kondycje(4,1)){///pociagnij
                                        g->zwrot=g->daj_zwrot_do_punktu(mx,my);
                                             what_happened aaa;
                                             if((aaa=g->przesun(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)), false))==success)
                                             {
                                                      if(p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(o)) o->przesun_po_srodowisku(Objekt::przeciwna(w_ktora_to_strone(g->x,g->y,mx,my)));
                                             }
                                             else if(aaa==dead) break;
                                    }break;
                                    default: case 0: break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2  &&mx>=gracz->x-1 && mx<=gracz->x+1 && my>=gracz->y-1 && my<=gracz->y+1 && swiat->aktualna->srodowisko[my][mx]!=NULL&&
                          swiat->aktualna->srodowisko[my][mx]->wierzch()->czym_jest==35)
                  {
                           poczekaj_na_myszke(2); Gracz*g=swiat->aktualny;
                           Plansza*pl=swiat->aktualna;
                           Zlamana_galaz*o=(Zlamana_galaz*)swiat->aktualna->srodowisko[my][mx]->wierzch();
                           specyfikacja_menu* menu=new specyfikacja_menu(new specyfikacja_menu*[1], 1, 256); menu->item[0]=new specyfikacja_menu(NULL,0,1);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){///zniszcz
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             o->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;///zniszcz
                                    default: case 0: break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2  &&mx>=gracz->x-1 && mx<=gracz->x+1 && my>=gracz->y-1 && my<=gracz->y+1 && swiat->aktualna->srodowisko[my][mx]!=NULL&&
                          swiat->aktualna->srodowisko[my][mx]->wierzch()->czym_jest==24)
                  {
                           poczekaj_na_myszke(2); Gracz*g=swiat->aktualny;
                           Ognisko*o=(Ognisko*)swiat->aktualna->srodowisko[my][mx]->wierzch();
                           specyfikacja_menu* menu=new specyfikacja_menu(new specyfikacja_menu*[3], 3, 28);
                           menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 1:if(g->p_rece!=NULL && g->p_rece->czym_jest==2201 && pobierz_punkty_ruchu(3)){
                                             if(losuj(1,10)<4) o->pali_sie=true;
                                             if(g->p_rece && ((Konsumpcjum*)g->p_rece)->wykorzystaj()){Konsumpcjum*a=(Konsumpcjum*)g->p_rece;g->p_rece=NULL;delete a;}
                                             }break;
                                    case 2:if(g->p_rece!=NULL && g->p_rece->czym_jest==8002 && pobierz_punkty_ruchu(2)){
                                             o->paliwo+=5; Inne*a=(Inne*)g->p_rece; g->p_rece=NULL; delete a;
                                             }break;
                                    case 3:if(o->pali_sie && pobierz_punkty_ruchu(4)){
                                             int a=g->cieplo_a+losuj(20,40); if(a<g->cieplo_max) g->cieplo_a=a; else g->cieplo_a=g->cieplo_max;
                                             }break;
                                    default: case 0: break;
                           }
                           delete menu; menu=NULL;
                  }

                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(26)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->mozna_stad_podejsc(g->x,g->y)
                          &&((((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona()==false)
                             ||(((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_wybite()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona())
                             ||(((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_wybite()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona()==false)))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->srodowisko[my][mx]->zwroc_objekt(26); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           int men; if(s->get_jest_zaslona()){men=43;if(s->get_otwarte())men=46;} else{men=44;if(s->get_wybite())men=42;}
                           if(!s->get_jest_zaslona() && s->get_wybite() && s->get_otwarte()) men=46;
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,men);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() && g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    case 2:if((men==45 && pobierz_punkty_ruchu(3))||(men!=45 && pobierz_punkty_ruchu(4))){
                                             if(men==44) s->zamknij();
                                             else if(men==45) s->odslon();
                                             else if(men==46) s->zamknij();
                                             else if(men==42) s->otworz();
                                            }break;
                                    case 3:if(((men==44 || men==42) && g->p_rece!=NULL && g->p_rece->czym_jest==8006 && pobierz_punkty_ruchu(6))||((men!=44&&men!=42) && pobierz_punkty_ruchu(6))){
                                             if(men==44 || men==42){Item*a=g->p_rece;g->p_rece=NULL;delete a;s->zaloz_zaslone();}
                                             else {s->zdejmij_zaslone();g->dostan_item(Item::stworz_obiekt(8006));}
                                            }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(26)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->mozna_stad_podejsc(g->x,g->y)
                          &&(((((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_wybite()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona()==false))
                          ||((((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona()))))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->srodowisko[my][mx]->zwroc_objekt(26); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           int men=42; if(!s->get_wybite()) {men=45;if(s->get_otwarte())men=46;} if(s->get_zasloniete()) men=45;
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,men);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() &&g->p_rece &&  g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    case 2:if((men==45 && pobierz_punkty_ruchu(3))||(men!=45 && pobierz_punkty_ruchu(4))){
                                             if(men==44) s->zamknij();
                                             else if(men==45) s->odslon();
                                             else if(men==46) s->zamknij();
                                            }break;
                                    case 3:if((men==44 && g->p_rece!=NULL && g->p_rece->czym_jest==8006 && pobierz_punkty_ruchu(6))||(men!=44 && pobierz_punkty_ruchu(6))){
                                             if(men==44){Item*a=g->p_rece;g->p_rece=NULL;delete a;s->zaloz_zaslone();}
                                             else {s->zdejmij_zaslone();g->dostan_item(Item::stworz_obiekt(8006));}
                                            }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(26)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->mozna_stad_podejsc(g->x,g->y)
                          &&((((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_wybite()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona())))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->srodowisko[my][mx]->zwroc_objekt(26); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,46);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() && g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(4)){
                                             s->zamknij();
                                            }break;
                                    case 3:if(pobierz_punkty_ruchu(6)){
                                             s->zdejmij_zaslone();g->dostan_item(Item::stworz_obiekt(8006));
                                            }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(26)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my))&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->mozna_stad_podejsc(g->x,g->y)
                          &&((((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_otwarte()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_wybite()&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_zasloniete()==false&&((Okno*)p->srodowisko[my][mx]->zwroc_objekt(26))->get_jest_zaslona())))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->srodowisko[my][mx]->zwroc_objekt(26); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [4],4,43);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);menu->item[3]=new specyfikacja_menu(NULL,0,4);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() && g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(4)){
                                             s->otworz();
                                            }break;
                                    case 3:if(pobierz_punkty_ruchu(3)){
                                             s->zaslon();
                                            }break;
                                    case 4:if(pobierz_punkty_ruchu(6)){
                                             s->zdejmij_zaslone();g->dostan_item(Item::stworz_obiekt(8006));
                                            }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(26)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->srodowisko[my][mx]->zwroc_objekt(26); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [1],1,48);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);
                                    int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1))||(!s->get_wybite() && g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3))){
                                             if(g->p_rece!=NULL && g->p_rece->jest_bronia_palna())
                                             {
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite()  &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                             }
                                             else
                                             {
                                                      g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                                      int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                                      if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                                      s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             }
                                    }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }
                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(26)&&!(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Okno*s=(Okno*)p->srodowisko[my][mx]->zwroc_objekt(26); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [2],2,47);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if(!s->get_wybite() && g->p_rece && g->p_rece->jest_bronia_palna()&& g->mozna_strzelic(s)&&pobierz_punkty_ruchu(3)){
                                                      Bron* bron=(Bron*)g->p_rece;
                                                      for(int j=0;bron->mag>0 && j<bron->ilosc_strzalow_w_serii() && !s->get_wybite() &&
                                                      (p->otoczenie[my][mx]==s || (p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(s)));++j)
                                                      {
                                                               gracz->animacja_strzalu((gracz->x+1)*args->X_kratka,(gracz->y+1)*args->Y_kratka,(p->otoczenie[my][mx]->x+1)*args->X_kratka,(p->otoczenie[my][mx]->y+1)*args->Y_kratka,bron->grubosc_strzalu());
                                                               int obr=bron->get_obrazenia();int szansa=bron->get_szansa()-2*g->odleglosc_w_kratkach(s);
                                                               szansa=szansa*(100-(g->l_ramie_a+g->p_ramie_a+g->p_dlon_a+g->l_dlon_a)/3)/100;
                                                               if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,bron->get_krytyk(),g->wart_zajecia()); else Sleep(150);
                                                               g->wydaj_dzwiek(true,bron->glosnosc_broni(),g->x,g->y,0);
                                                               --bron->mag;
                                                      }
                                    }break;
                                    case 2:if(!s->get_wybite() && g->p_rece!=NULL && g->mozna_strzelic(p->otoczenie[my][mx]) && pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             Bron*a=(Bron*)g->p_rece; g->p_rece=NULL;int obr=a->wartosc_ataku_rzucanego();
                                             g->animacja_rzutu_przedmiotu(args,mx, my, a);
                                             if(a && a->wykorzystaj()){delete a;}else p->rzuc_na_ziemie(mx,my,a);
                                             int szansa=80-2*g->odleglosc_w_kratkach(p->otoczenie[my][mx]);
                                             if(losuj(1,100)<=szansa)s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}
                                    }break;

                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }




                  else if(!g->ukryty && myszka.buttons&2 && p->srodowisko[my][mx]!=NULL && p->srodowisko[my][mx]->ma_to(27)&&(Objekt::jest_prostopadle(g->x,g->y,mx,my)||Objekt::jest_z_ukosa(g->x,g->y,mx,my)))
                  {
                           poczekaj_na_myszke(2);Drzwi*s=(Drzwi*)p->srodowisko[my][mx]->zwroc_objekt(27); //Plansza*p=(Plansza*)swiat->area[g->px][g->py][g->pz];
                           specyfikacja_menu* menu=new specyfikacja_menu(new  specyfikacja_menu* [3],3,51);
                                    menu->item[0]=new specyfikacja_menu(NULL,0,1);menu->item[1]=new specyfikacja_menu(NULL,0,2);menu->item[2]=new specyfikacja_menu(NULL,0,3);
                           int wybor=Menu(myszka.x, myszka.y, args, menu);
                           switch(wybor)
                           {
                                    case 0:break;
                                    case 1:if((g->p_rece==NULL || g->p_rece->jest_bronia_biala()) &&pobierz_punkty_ruchu_i_kondycje(3,1)){
                                             g->animacja_ataku(w_ktora_to_strone(g->x,g->y,mx,my));
                                             int obr=losuj(1,6); if(g->p_rece!=NULL) {obr=((Bron*)g->p_rece)->get_obrazenia();
                                             if(g->p_rece && ((Bron*)g->p_rece)->wykorzystaj()){Bron*a=(Bron*)g->p_rece;g->p_rece=NULL;delete a;}}
                                             s->zostan_uderzony(obr,0,0,g->wart_zajecia());
                                    }break;
                                    case 2:if(pobierz_punkty_ruchu(5)){
                                             s->zamknij();
                                            }break;
                                    case 3:if(pobierz_punkty_ruchu(2)){
                                             s->zamknij(); s->wydaj_dzwiek(false,10,s->x,s->y,27);
                                            }break;
                                    default:break;
                           }
                           delete menu; menu=NULL;
                  }}











}
