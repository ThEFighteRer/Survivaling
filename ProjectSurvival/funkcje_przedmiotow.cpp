#include "gra.h"



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















