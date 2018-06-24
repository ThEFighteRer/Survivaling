#include "gra.h"







Item* Gra::uzyj(Item*a, bool wybralem_miejsce, punkt mysz)///wsparcie tylko dla medycznych rzeczy, jesli chodzi o wczesniejszy wybor pozycji
{
         short spanie = 500;
         ALLEGRO_MOUSE_STATE myszka;
         if(wybralem_miejsce) {myszka.x = mysz.x; myszka.y = mysz.y;}
         ALLEGRO_KEYBOARD_STATE klawiatura; Gracz*g=swiat->aktualny;
         switch(a->czym_jest)
         {
                  case 2003: {dodaj_wody(50);delete a; return Item::stworz_obiekt(2003);}break;
                  case 2004: {dodaj_wody(50); delete a; return Item::stworz_obiekt(2005);}break;
                  case 2009: {dodaj_wody(50); dodaj_jedzenia(-losuj(10, 80)); delete a; return Item::stworz_obiekt(2010);}break;
                  case 2010: {dodaj_wody(50); dodaj_jedzenia(-losuj(10, 80)); delete a; return Item::stworz_obiekt(2005);}break;
                  case 2020: {dodaj_jedzenia(50); dodaj_wody(-losuj(0, 20)); delete a; swiat->zwroc_taka_plansze_TYLKO(g->px, g->py,g->pz)->dzwiek(false, 3, g->x, g->y, 10); return NULL;}break;

                  case 2201:{Item *k = new Konsumpcjum(2202, ((Konsumpcjum*)a)->get_uzycia()); delete a; swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz)->zaktualizuj_widoki(); return k;}
                  case 2202:if(((Konsumpcjum*)a)->get_uzycia()>0){Item *k = new Konsumpcjum(2201, ((Konsumpcjum*)a)->get_uzycia()); delete a; swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz)->zaktualizuj_widoki(); return k;} return a;
                  case 2203:{return zaladuj_konsumpcjum(2202,(Konsumpcjum*)a, 2203);}break;

                  case 2001: {dodaj_jedzenia(50);return NULL;}break;
                  //case 2011: {dodaj_jedzenia();return NULL;}break;
                  case 2012: {dodaj_jedzenia(((Konsumpcjum*)a)->get_uzycia());return NULL;}break;
                  //case 2013: {dodaj_jedzenia();return NULL;}break;
                  case 2014: {dodaj_jedzenia(((Konsumpcjum*)a)->get_uzycia());return NULL;}break;
                  case 2006: {dodaj_wody(50);return NULL;}break;
                  case 2007:
                  {
                           bool bylo_otw = args->otwarte_menu_anatomii;
                           if(!wybralem_miejsce)
                           {
                                    myszka = wybierz_miejsce_uzycia_w_menu_anatomii(a->czym_jest);
                           }

                           if(jest_nad_klatka(myszka) && g->klatka.da_sie_uleczyc()){g->klatka.ulecz(20); delete a;a=NULL;}
                           else if(jest_nad_brzuch(myszka) && g->brzuch.da_sie_uleczyc()){g->brzuch.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_l_ramie(myszka) && g->ramie_l.da_sie_uleczyc()){g->ramie_l.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_p_ramie(myszka) && g->ramie_p.da_sie_uleczyc()){g->ramie_p.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_l_dlon(myszka) && g->l_dlon.da_sie_uleczyc()){g->l_dlon.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_p_dlon(myszka) && g->p_dlon.da_sie_uleczyc()){g->p_dlon.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_l_udo(myszka) && g->l_udo.da_sie_uleczyc()){g->l_udo.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_p_udo(myszka) && g->p_udo.da_sie_uleczyc()){g->p_udo.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_l_golen(myszka) && g->l_golen.da_sie_uleczyc()){g->l_golen.ulecz(20);delete a;a=NULL;}
                           else if( jest_nad_p_golen(myszka) && g->p_golen.da_sie_uleczyc()){g->p_golen.ulecz(20);delete a;a=NULL;}
                           Sleep(spanie);

                           if(!wybralem_miejsce)  args->otwarte_menu_anatomii=false || bylo_otw;
                           return a;
                  }break;
                  case 8024: case 8025: case 8020:
                  {
                           bool bylo_otw = args->otwarte_menu_anatomii;
                           if(!wybralem_miejsce)
                           {
                                    myszka = wybierz_miejsce_uzycia_w_menu_anatomii(a->czym_jest);
                           }
                           czesc_ciala * r = wybierz_rane_czesci_ciala(myszka);
                           if(r!=NULL && (r->stan_rany()&64)!=0)
                           {
                                    short ile=0;
                                    switch(a->czym_jest)
                                    {
                                             case 8024: ile=2;break; case 8025: ile=3;break; case 8020: ile=1;break;
                                    }
                                    if((r->bandaze_rany()==0 && a->czym_jest==8020) || (r->bandaze_rany()<=1 && a->czym_jest==8024) || a->czym_jest==8025)
                                    {
                                             r->bandazuj_rane(ile);
                                             delete a;
                                             a = NULL;
                                    }
                           }

                           if(!wybralem_miejsce)
                           {
                                    Sleep(spanie); args->otwarte_menu_anatomii=false || bylo_otw;
                           }
                           return a;
                  }break;
                  case 2008:
                  {
                           bool bylo_otw = args->otwarte_menu_anatomii;
                           if(!wybralem_miejsce)
                           {
                                    myszka = wybierz_miejsce_uzycia_w_menu_anatomii(a->czym_jest);
                           }

                           czesc_ciala * r = wybierz_rane_czesci_ciala(myszka);
                           if(r!=NULL && (r->stan_rany()&64)!=0 && (r->stan_rany()&32)!=0)
                           {
                                    if(r->oczysc_rane() && a->wykorzystaj())
                                    {
                                             delete a; a = NULL;
                                    }
                           }
                           if(!wybralem_miejsce)
                           {
                                    Sleep(spanie); args->otwarte_menu_anatomii=false || bylo_otw;
                           }
                           return a;
                  }break;
                  case 2021:
                  {
                           bool bylo_otw = args->otwarte_menu_anatomii;
                           if(!wybralem_miejsce)
                           {
                                    myszka = wybierz_miejsce_uzycia_w_menu_anatomii(a->czym_jest);
                           }

                           czesc_ciala * r = wybierz_rane_czesci_ciala(myszka);
                           if(r!=NULL && (r->stan_rany()&64)!=0 && (r->stan_rany()&32)!=0 && (r->stan_rany()&4)==0)
                           {
                                    if(r->posmaruj_rane() && a->wykorzystaj())
                                    {
                                             delete a; a = NULL;
                                    }
                           }
                           if(!wybralem_miejsce)
                           {
                                    Sleep(spanie); args->otwarte_menu_anatomii=false || bylo_otw;
                           }
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
                  case 8022:
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           Plansza *p = swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);
                           if(p!=NULL && Strefa::w_planszy(aaa.x, aaa.y) && g->mozna_rzucic(aaa.x, aaa.y) && pobierz_punkty_ruchu(3))
                           {
                                    g->animacja_rzutu_przedmiotu(args,aaa.x, aaa.y, a);
                                    p->dzwiek(false, 4, aaa.x, aaa.y, 0);
                                    if(losuj(0,2)==0)
                                    {
                                             p->rzuc_na_ziemie(aaa.x, aaa.y, Item::stworz_obiekt(8023));
                                             delete a;
                                    }
                                    else
                                    {
                                             p->rzuc_na_ziemie(aaa.x, aaa.y, a);
                                    }
                                    Sleep(500);
                                    przywroc_ekw();
                                    return NULL;
                           }
                           przywroc_ekw();
                           return a;
                  }break;
                  case 4009:
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           Plansza *p = swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);
                           if(p!=NULL && Strefa::w_planszy(aaa.x, aaa.y) && g->zaraz_obok(g->x, g->y, aaa.x, aaa.y) && p->otoczenie[aaa.y][aaa.x]==NULL && pobierz_punkty_ruchu(3))
                           {
                                    p->otoczenie[aaa.y][aaa.x] = new Krzeslo(aaa.x, aaa.y, g->px, g->py, g->pz, 1); delete a;
                                    przywroc_ekw(); return NULL;
                           }
                           przywroc_ekw();
                           return a;
                  }break;
                  case 4012:
                  {
                           ukryj_ekw();
                           punkt aaa = wybierz_kratke_na_planszy();
                           Plansza *p = swiat->zwroc_taka_plansze_TYLKO(g->px, g->py, g->pz);
                           if(p!=NULL && Strefa::w_planszy(aaa.x, aaa.y) && g->zaraz_obok(g->x, g->y, aaa.x, aaa.y) && p->otoczenie[aaa.y][aaa.x]==NULL && pobierz_punkty_ruchu(3))
                           {
                                    WLampa *l= new WLampa(aaa.x, aaa.y, g->px, g->py, g->pz, 1); if(((Bron*)a)->mag==1) l->wlacz(); else l->wylacz();
                                    p->otoczenie[aaa.y][aaa.x] = l;
                                    p->zaktualizuj_widoki();
                                    delete a;
                                    przywroc_ekw(); return NULL;
                           }
                           przywroc_ekw();
                           return a;
                  }break;

                  default: return a;
         }
}

ALLEGRO_MOUSE_STATE Gra::wybierz_miejsce_uzycia_w_menu_anatomii(int nr)
{
         ALLEGRO_MOUSE_STATE myszka;
         args->otwarte_menu_anatomii=true;
         args->p_nr_przedmiotu=nr;
         int roznica_x=args->X_kratka/2,
         roznica_y=args->Y_kratka/2;
         while(true)
         {
                  args->p_x=myszka.x-roznica_x; args->p_y=myszka.y-roznica_y; al_rest(0.01); al_get_mouse_state(&myszka); if((myszka.buttons&1)) break;
         }
         args->p_nr_przedmiotu=0;
         return myszka;
}

void Gra::uzycie_przedmiotu(Przedmiot*a, Skrzynka*s)
{
         ALLEGRO_MOUSE_STATE myszka;
         Gracz*g=swiat->aktualny;

         switch(a->item->czym_jest)
         {
                  case 2101:
                  {
                           poczekaj_na_myszke(1);
                           int xx=a->x, yy=a->y; s->wyjmij_przedmiot(a);
                           while(true)
                           {
                                    al_get_mouse_state(&myszka);
                                    if(myszka.buttons&1)break;
                           }
                           if(jest_nad_ramieniem(myszka)&&g->p_ramie->czym_jest==4002)
                           {
                                    Item * aaa = g->p_ramie;
                                    g->p_ramie=Item::stworz_obiekt(4003);
                                    delete a; delete aaa;
                           }
                           else if(jest_nad_rekami(myszka)&&g->p_rece->czym_jest==4002)
                           {
                                    Item *aaa = g->p_rece;
                                    g->p_rece=Item::stworz_obiekt(4003);
                                    delete a; delete aaa;
                           }
                           else if(args->otwarty_ekwipunek);






                  }break;










                  default:break;
         }

}



bool Gra::jest_nad_klatka(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>9*args->X_kratka&&myszka.x<13*args->X_kratka&&myszka.y>1*args->Y_kratka&&myszka.y<2*args->Y_kratka)||
(myszka.x>10*args->X_kratka&&myszka.x<12*args->X_kratka&&myszka.y>2*args->Y_kratka&&myszka.y<3*args->Y_kratka);}
bool Gra::jest_nad_brzuch(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>10*args->X_kratka&&myszka.x<12*args->X_kratka&&myszka.y>4*args->Y_kratka&&myszka.y<6*args->Y_kratka);}
bool Gra::jest_nad_l_ramie(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>13*args->X_kratka&&myszka.x<17*args->X_kratka&&myszka.y>3*args->Y_kratka&&myszka.y<4*args->Y_kratka)||
(myszka.x>13*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>4*args->Y_kratka&&myszka.y<5*args->Y_kratka);}
bool Gra::jest_nad_p_ramie(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>6*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>3*args->Y_kratka&&myszka.y<4*args->Y_kratka)||
(myszka.x>7*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>4*args->Y_kratka&&myszka.y<5*args->Y_kratka);}
bool Gra::jest_nad_l_dlon(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>14*args->X_kratka&&myszka.x<17*args->X_kratka&&myszka.y>6*args->Y_kratka&&myszka.y<7*args->Y_kratka)||
(myszka.x>15*args->X_kratka&&myszka.x<17*args->X_kratka&&myszka.y>7*args->Y_kratka&&myszka.y<8*args->Y_kratka);}
bool Gra::jest_nad_p_dlon(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>5*args->X_kratka&&myszka.x<8*args->X_kratka&&myszka.y>6*args->Y_kratka&&myszka.y<7*args->Y_kratka)||
(myszka.x>5*args->X_kratka&&myszka.x<7*args->X_kratka&&myszka.y>7*args->Y_kratka&&myszka.y<8*args->Y_kratka);}
bool Gra::jest_nad_l_udo(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>12*args->X_kratka&&myszka.x<15*args->X_kratka&&myszka.y>8*args->Y_kratka&&myszka.y<9*args->Y_kratka)||
(myszka.x>12*args->X_kratka&&myszka.x<14*args->X_kratka&&myszka.y>9*args->Y_kratka&&myszka.y<10*args->Y_kratka);}
bool Gra::jest_nad_p_udo(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>7*args->X_kratka&&myszka.x<10*args->X_kratka&&myszka.y>8*args->Y_kratka&&myszka.y<9*args->Y_kratka)||
(myszka.x>8*args->X_kratka&&myszka.x<10*args->X_kratka&&myszka.y>9*args->Y_kratka&&myszka.y<10*args->Y_kratka);}
bool Gra::jest_nad_p_golen(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>6*args->X_kratka&&myszka.x<10*args->X_kratka&&myszka.y>11*args->Y_kratka&&myszka.y<12*args->Y_kratka)||
(myszka.x>7*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>12*args->Y_kratka&&myszka.y<13*args->Y_kratka);}
bool Gra::jest_nad_l_golen(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>12*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>11*args->Y_kratka&&myszka.y<12*args->Y_kratka)||
(myszka.x>13*args->X_kratka&&myszka.x<15*args->X_kratka&&myszka.y>12*args->Y_kratka&&myszka.y<13*args->Y_kratka);}

czesc_ciala* Gra::wybierz_czesc_ciala(ALLEGRO_MOUSE_STATE myszka)
{
         if(jest_nad_klatka(myszka)) return &swiat->aktualny->klatka;
         if(jest_nad_brzuch(myszka)) return &swiat->aktualny->brzuch;
         if(jest_nad_l_ramie(myszka)) return &swiat->aktualny->ramie_l;
         if(jest_nad_p_ramie(myszka)) return &swiat->aktualny->ramie_p;
         if(jest_nad_l_dlon(myszka)) return &swiat->aktualny->l_dlon;
         if(jest_nad_p_dlon(myszka)) return &swiat->aktualny->p_dlon;
         if(jest_nad_l_udo(myszka)) return &swiat->aktualny->l_udo;
         if(jest_nad_p_udo(myszka)) return &swiat->aktualny->p_udo;
         if(jest_nad_p_golen(myszka)) return &swiat->aktualny->p_golen;
         if(jest_nad_l_golen(myszka)) return &swiat->aktualny->l_golen;
         return NULL;
}

czesc_ciala* Gra::wybierz_rane_czesci_ciala(ALLEGRO_MOUSE_STATE myszka)
{
         if(jest_nad_klatka_rana(myszka)) return &swiat->aktualny->klatka;
         if(jest_nad_brzuch_rana(myszka)) return &swiat->aktualny->brzuch;
         if(jest_nad_l_ramie_rana(myszka)) return &swiat->aktualny->ramie_l;
         if(jest_nad_p_ramie_rana(myszka)) return &swiat->aktualny->ramie_p;
         if(jest_nad_l_dlon_rana(myszka)) return &swiat->aktualny->l_dlon;
         if(jest_nad_p_dlon_rana(myszka)) return &swiat->aktualny->p_dlon;
         if(jest_nad_l_udo_rana(myszka)) return &swiat->aktualny->l_udo;
         if(jest_nad_p_udo_rana(myszka)) return &swiat->aktualny->p_udo;
         if(jest_nad_p_golen_rana(myszka)) return &swiat->aktualny->p_golen;
         if(jest_nad_l_golen_rana(myszka)) return &swiat->aktualny->l_golen;
         return NULL;
}

bool Gra::jest_nad_klatka_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>10*args->X_kratka&&myszka.x<11*args->X_kratka&&myszka.y>3*args->Y_kratka&&myszka.y<4*args->Y_kratka);}
bool Gra::jest_nad_brzuch_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>10*args->X_kratka&&myszka.x<11*args->X_kratka&&myszka.y>6*args->Y_kratka&&myszka.y<7*args->Y_kratka);}
bool Gra::jest_nad_l_ramie_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>13*args->X_kratka&&myszka.x<14*args->X_kratka&&myszka.y>5*args->Y_kratka&&myszka.y<6*args->Y_kratka);}
bool Gra::jest_nad_p_ramie_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>7*args->X_kratka&&myszka.x<8*args->X_kratka&&myszka.y>5*args->Y_kratka&&myszka.y<6*args->Y_kratka);}
bool Gra::jest_nad_l_dlon_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>15*args->X_kratka&&myszka.x<16*args->X_kratka&&myszka.y>8*args->Y_kratka&&myszka.y<9*args->Y_kratka);}
bool Gra::jest_nad_p_dlon_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>5*args->X_kratka&&myszka.x<6*args->X_kratka&&myszka.y>8*args->Y_kratka&&myszka.y<9*args->Y_kratka);}
bool Gra::jest_nad_l_udo_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>12*args->X_kratka&&myszka.x<13*args->X_kratka&&myszka.y>10*args->Y_kratka&&myszka.y<11*args->Y_kratka);}
bool Gra::jest_nad_p_udo_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>8*args->X_kratka&&myszka.x<9*args->X_kratka&&myszka.y>10*args->Y_kratka&&myszka.y<11*args->Y_kratka);}
bool Gra::jest_nad_p_golen_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>7*args->X_kratka&&myszka.x<8*args->X_kratka&&myszka.y>13*args->Y_kratka&&myszka.y<14*args->Y_kratka);}
bool Gra::jest_nad_l_golen_rana(ALLEGRO_MOUSE_STATE myszka)
{return (myszka.x>13*args->X_kratka&&myszka.x<14*args->X_kratka&&myszka.y>13*args->Y_kratka&&myszka.y<14*args->Y_kratka);}






