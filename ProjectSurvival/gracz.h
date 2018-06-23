#include <iostream>

#ifndef GRACZ
#define GRACZ

enum warunki
{
         zle, srednie, dobre, bardzo_dobre
};

class Rana
{
         char pozostalo = 120;
         char stan = 1;///1 - czy prosta, 2 - czy krwotoczna, 4 - posmarowana zelem, 8 i  16 to wytrzymalosc banadaza (0-3), 32 - brudna, 64 - istnieje

         void zrob_krwotok(){stan|=2;}


         public:

         Rana(bool brudna = false)
         {
                  if(brudna) stan|=32;
         }

         bool rana_prosta() {return (stan&(1)) != 0;}
         bool krwotoczna() {return (stan&(2)) != 0;}
         bool posmarowana_zelem() {return (stan&4) != 0;}
         bool bandaz() {return ((stan&16) != 0) || ((stan&8) != 0);}
         bool brudna() {return (stan&32) != 0;}
         short obandazowanie(){return ((stan&16)!=0)+((stan&8)!=0)*2;}
         char stan_() {return stan;}

         void obandazuj(short wytrz_bandaza)
         {
                  if(wytrz_bandaza>2) {stan|=8; stan|=16;}
                  else if(wytrz_bandaza==2) {stan|=8;}
                  else if(wytrz_bandaza==1) {stan|=16;}
         }
         void posmaruj_zelem(){stan|=4;}
};


class czesc_ciala
{
         char hp, maxx;
         Rana rana;
         czesc_ciala *polaczone = NULL; ///czesci ciala bezposrednio polaczone

public:

         czesc_ciala(short hp, short maxx)
         {
                  this->hp = hp; this->maxx = maxx;
         }

         short ile_hp(){return short(hp);}
         short jaki_max(){return short(maxx);}
         bool da_sie_uleczyc(){return hp<maxx;}
         char stan_rany(){return rana.stan_();}

         void zadaj_obrazenia(short ile);
         void minela_runda(warunki war);
         void ulecz(short ile);

};


#endif // GRACZ
