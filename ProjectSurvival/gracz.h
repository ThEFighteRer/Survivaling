#include <iostream>

#ifndef GRACZ
#define GRACZ

class Rana
{
         char pozostalo = 0;
         char stan = 0;///1 - czy prosta, 2 - czy krwotoczna, 4 - posmarowana zelem, 8 i  16 to wytrzymalosc banadaza (0-3), 32 - brudna, 64 - istnieje


         void zrob_krwotok(){stan|=2; if(brudna()) stan-=32; if(posmarowana_zelem()) stan-=4;}
         ///krwawienie wymywa posmarowanie ale tez brud

         void zabrudz(){if(!krwotoczna() && !bandaz()) stan|=32;}///zabrudzic rane mozemy tylko, gdy nie krwawi nie ma bandaza
         void ustaw_bandaz_na(short ile)
         {
                  if(istnieje())
                  {
                           if(ile>2) {stan|=8; stan|=16;}
                           else if(ile==2) {stan|=8; if((stan|16)!=0) stan-=16;}
                           else if(ile==1) {stan|=16;if((stan|8)!=0) stan-=8;}
                           else if(ile==0) {if((stan|16)!=0) stan-=16;if((stan|8)!=0) stan-=8;}
                  }
         }


         public:

         Rana()
         {

         }

         bool rana_prosta() {return istnieje() && (stan&(1)) != 0;}
         bool krwotoczna() {return istnieje() && (stan&(2)) != 0;}
         bool posmarowana_zelem() {return istnieje() && (stan&4) != 0;}
         bool bandaz() {return istnieje() && (((stan&16) != 0) || ((stan&8) != 0));}
         bool brudna() {return istnieje() && (stan&32) != 0;}
         short obandazowanie(){if(istnieje()) return ((stan&16)!=0)+((stan&8)!=0)*2; else return 0;}
         char stan_() {return stan;}
         bool istnieje() {return (stan&64)!=0;}
         bool krew_cieknie(){return istnieje() && krwotoczna() && !bandaz();}

         bool oczysc(){if(istnieje() && !bandaz() && brudna()) {stan-=32; return true;} return false;}
         void obandazuj(short wytrz_bandaza)
         {
                  if(istnieje())
                  {
                           short a = obandazowanie();
                           if(wytrz_bandaza>2) {stan|=8; stan|=16;}
                           else if(wytrz_bandaza==2) {stan|=8; if(a>0) stan|=16;}
                           else if(wytrz_bandaza==1) {stan|=16; if(a==1) {stan-=16; stan|=8;} else if(a>1) stan|=8;}
                  }
         }
         bool posmaruj_zelem(){if(istnieje() && !bandaz()) {stan|=4; return true;} return false;}
         void minela_runda(short war);
         void kontakt();
         void zerwij_bandaze(){if((stan&16)!=0) stan-=16;if((stan&8)!=0) stan-=8;}
};


class czesc_ciala
{
         czesc_ciala **sasiednie = NULL;///ostatni to null
         const char max_bezwzgledny;
         char hp=0, maxx=0, leczenie=0, glikogen = 60; ///leczymy co 60; glokogen to magazynowanie maksymalne leczenia
         Rana rana;
         czesc_ciala *polaczone = NULL; ///czesci ciala bezposrednio polaczone

public:

         czesc_ciala(short hp, short maxx):max_bezwzgledny(maxx)
         {
                  this->hp = hp; this->maxx = maxx;
         }
         ~czesc_ciala()
         {
                  delete [] sasiednie;
         }

         short ile_hp(){return short(hp);}
         short jaki_max_bezwzgledny(){return short(max_bezwzgledny);}
         bool da_sie_uleczyc(){return hp<maxx;}
         char stan_rany(){return rana.stan_();}
         void set_czesci_sasiednie(czesc_ciala **c){if(sasiednie==NULL) sasiednie = c; else {std::cout<<"juz sa sasiednie"; throw "G";}}

         void zadaj_obrazenia(short ile);
         void minela_runda(short war);
         void ulecz(short ile);
         void zwitaminuj(short ile){if(glikogen+ile<=300) glikogen+=ile; else glikogen=300;}
         void bandazuj_rane(short ile){if(rana.istnieje()) rana.obandazuj(ile);}
         void oczysc_rane(){if(rana.istnieje()) rana.oczysc();}
         void zerwij_bandaze_rany(){if(rana.istnieje()) rana.zerwij_bandaze();}
         void posmaruj_rane(){if(rana.istnieje()) rana.posmarowana_zelem();}
};


#endif // GRACZ
