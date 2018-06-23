#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>
#include <iostream>

#include <algorithm>
#include <memory>
#include <mutex>
#include "allegro5/allegro.h"

#ifndef GRANDFATHER_H
#define GRANDFATHER_H

#include "gracz.h"


#define SITEM std::shared_ptr<Item>

#define obrazenia_od_wybuchu -99
#define obrazenia_od_ognia -100






template <typename T>
class szerokosc
{
         T width[21];

public:
         const T& operator[](int index) const
         {
                  if(index<0 || index>21) {std::cout<<"Poza zasiegiem"; throw "D";}
                  return width[index];
         }
         T& operator[](int index)
         {
                  if(index<0 || index>21) {std::cout<<"Poza zasiegiem"; throw "D";}
                  return width[index];
         }
};

template <typename T>
class planszowa
{
         szerokosc<T> height[13];

public:
         const szerokosc<T>& operator[](int index) const
         {
                  if(index<0 || index>12) {std::cout<<"Poza zasiegiem"; throw "D";}
                  return height[index];
         }
         szerokosc<T>& operator[](int index)
         {
                  if(index<0 || index>12) {std::cout<<"Poza zasiegiem"; throw "D";}
                  return height[index];
         }
};

class od_srodowiska
{
         public:
         unsigned char stan;
         short przesuniecie_x,przesuniecie_y;
         int rys;
         od_srodowiska(unsigned char a, short b, short c, int d)
         {
                  stan = a; przesuniecie_x = b; przesuniecie_y = c; rys = d;
         }
};

struct Przepis;

template<typename T>
class Kontener
{
         public:
         Kontener<T>();
         ~Kontener();
         T** obiekt=NULL;
         int ilosc=0, miejsce=0;
         void dodaj_obiekt(T* o);
         T* usun_objekt(int nr);///od 0
         void usun_objekt(T *o);///od 0
         void wywal_wszystkie_objekty();
         bool jest_tu(T*o);
         void deletuj_obiekty();
         void dodaj_obiekty(Kontener<T>*a);
         int nr_obiektu(T*o);
};
template<typename T>
Kontener <T>::Kontener()
{

}

template<typename T>
Kontener <T>::~Kontener()
{
         deletuj_obiekty();
}

template<typename T>
void Kontener<T> :: dodaj_obiekt(T* o)
{
         if(o==NULL)return;
         if(miejsce==0) {miejsce=2; obiekt=new T*[miejsce]; }
         else if(miejsce==ilosc) {miejsce*=2; T**u=obiekt; obiekt=new T*[miejsce]; for(int i=0; i<miejsce/2; i++) obiekt[i]=u[i]; delete [] u;}
         obiekt[ilosc++]=o;
}

template<typename T>
T* Kontener<T> :: usun_objekt(int nr)
{
         if(nr<0 || nr>=ilosc) {std::cout<<"nie ma tyle obiektow w kontenerze";throw "nie ma tyle obiektow w kontenerze";}
         T**u; if(ilosc-1<miejsce/2) miejsce/=2;
         u=new T*[miejsce]; int n=0;
         T* o=NULL;
         for(int i=0; i<ilosc; i++)
         {
                  if(i==nr) {o=obiekt[i]; n=1; continue;}
                  u[i-n]=obiekt[i];
         }
         --ilosc; delete [] obiekt; obiekt=u;
         return o;
}

template<typename T>
void Kontener<T> :: usun_objekt(T *o)
{
         T**u; if(ilosc-1<miejsce/2) miejsce/=2;
         u=new T*[miejsce]; int n=0;
         for(int i=0; i<ilosc; i++)
         {
                  if(obiekt[i]==o) {n=1; continue;}
                  u[i-n]=obiekt[i];
         }
         --ilosc; delete [] obiekt; obiekt=u;
}

template<typename T>
void Kontener<T> :: wywal_wszystkie_objekty()
{
         delete [] obiekt;
         obiekt=NULL;ilosc=0;miejsce=0;
}

template<typename T>
bool Kontener<T>:: jest_tu(T*o)
{
         for(int i=0;i<ilosc;++i)
         {
                  if(obiekt[i]==o)return true;
         }
         return false;
}

template<typename T>
void Kontener <T>::deletuj_obiekty()
{
         if(ilosc!=0)
         {
                  for(int i=0; i<ilosc; ++i) delete obiekt[i];
         }
         delete [] obiekt;ilosc=0;miejsce=0;
         obiekt=NULL;
}

template<typename T>
void Kontener<T>::dodaj_obiekty(Kontener<T>*a)
{
         for(int i=0; i<a->ilosc; ++i)
                  dodaj_obiekt(a->obiekt[i]);
}

template<typename T>
int Kontener<T>::nr_obiektu(T*a)
{
         for(int i=0; i<ilosc; ++i)
                  if(obiekt[i]==a) return i;
         return -1;
}

struct Przesuniecie
{
         int x;
         int y;
};

class specyfikacja_menu
{
         public:
         specyfikacja_menu **item=NULL;
         int ilosc=0;
         int ktore=0;

         specyfikacja_menu();
         specyfikacja_menu(struct specyfikacja_menu **item,int ilosc,int ktore);
         ~ specyfikacja_menu();
};

struct punkt
{
         punkt(short x, short y)
         {
                  this->x=x; this->y=y;
         }
         punkt()
         {

         }
         short x,y;
};

class punkt_na_planszy
{
         public:
         short x,y;
         punkt_na_planszy()
         {

         }
         punkt_na_planszy(short a, short b)
         {
                  if(a<0 || a>20 || b<0 || b>12)
                           std::cout<<"punkt poza mapa";
                  x = a; y = b;
         }
};

class podloga
{
         public:
         punkt_na_planszy a, b;
         short jaka;
         podloga(punkt_na_planszy a, punkt_na_planszy b, short jaka)
         {
                  if(a.x>b.x)
                  {
                           punkt_na_planszy c = a;
                           a = b;
                           b = c;
                  }
                  this->a = a; this->b = b; this->jaka = jaka;
         }
};

class z_planszy
{
         public:
         short b_akt=0, b_left=0, b_high=0, b_down=0, b_right=0;

         int otoczenie [15][23][2];
         int srodowisko[15][23][2];
         bool ziemia [15][23];
         int stany_obiektow[15][23];
         int stany_srodowisk[15][23];
         short oswietlenie[15][23];
         struct Przesuniecie przesuniecie[15][23];
         struct Przesuniecie przesuniecie_srodowisk[15][23];
         bool bylo_przesuwane;
         int upadli [15][23];
         Kontener<podloga> *podlogi;
         bool **oszolomiony;

         z_planszy()
         {
                  for(int i=0;i<15;++i) for(int j=0;j<23;++j) {przesuniecie_srodowisk[i][j].x=0; przesuniecie_srodowisk[i][j].y=0;}
                  oszolomiony = new bool*[13]; for(short i=0;i<13;++i) {oszolomiony[i] = new bool[21]; for(short t=0;t<21;++t) oszolomiony[i][t]=false;}
         }
};

struct co_ma_gracz
{
         bool *substraty = NULL;///przedmiot
         bool *objekty_w_poblizu = NULL;///objekt
         bool *katalizatory = NULL;///przedmiot
         //bool *rezultaty = NULL;///przedmiot
         bool *skills = NULL; ///wymagane umiejetnosci itd
         short ilosc_substratow = 0, ilosc_objektow_w_poblizu = 0, ilosc_katalizatorow = 0, /*ilosc_rezultatow = 0,*/ ilosc_umiejetnosci = 0;

         ~co_ma_gracz()
         {
                  delete [] substraty; delete [] objekty_w_poblizu; delete [] katalizatory; /*delete [] rezultaty;*/ delete [] skills;
         }
};


struct rozmiary_tabeli
{
         short I=0,II=0,III=0,IV=0,V=0;
         void zmien(short a,short b,short c,short d,short e)
         {
                  I=a; II=b; III=c; IV=d; V=e;
                  I = I+II+III+IV+V>=10 ? I : I + 10 - (I+II+III+IV+V);
         }
         void zmien(rozmiary_tabeli a)
         {
                  I=a.I; II=a.II; III=a.III; IV=a.IV; V=a.V;
         }
         rozmiary_tabeli(){}
         rozmiary_tabeli(short a,short b,short c,short d,short e)
         {
                  zmien(a,b,c,d,e);
         }
};

class obrazki_ze_skrzynki
{
         std::vector<std::pair<int, punkt>> plecak, ziemia;
         int p_s_x=0, p_s_y=0, p_p_x=0, p_p_y=0;
         ALLEGRO_MUTEX *mutex = al_create_mutex();

public:
         obrazki_ze_skrzynki(){}
         ~obrazki_ze_skrzynki(){al_destroy_mutex(mutex);}

         void reset()
         {
                  al_lock_mutex(mutex);
                  plecak.clear(); ziemia.clear();
                  p_s_x=0, p_s_y=0, p_p_x=0, p_p_y=0;
                  al_unlock_mutex(mutex);
         }

         void aktualizuj(std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>> pl, std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>> zm)
         {
                  al_lock_mutex(mutex);
                  plecak.clear(); ziemia.clear();
                  p_s_x=zm.second.first, p_s_y=zm.second.second, p_p_x=pl.second.first, p_p_y=pl.second.second;
                  plecak = pl.first; ziemia = zm.first;
                  al_unlock_mutex(mutex);
         }
         void aktualizuj_lewo(std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>> zm)
         {
                  al_lock_mutex(mutex);
                  ziemia.clear(); ziemia = zm.first;
                  p_s_x=zm.second.first, p_s_y=zm.second.second;
                  al_unlock_mutex(mutex);
         }
         void aktualizuj_prawo(std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>> pl)
         {
                  al_lock_mutex(mutex);
                  plecak.clear(); plecak = pl.first;
                  p_p_x=pl.second.first, p_p_y=pl.second.second;
                  al_unlock_mutex(mutex);
         }
         std::pair<std::vector<std::pair<int, punkt>>, std::pair<int, int>> getPlecak()
         {
                  al_lock_mutex(mutex);
                  auto g =  std::pair<std::vector<std::pair<int, punkt>> , std::pair<int,int>>(plecak, std::pair<int, int>(p_p_x, p_p_y));
                  al_unlock_mutex(mutex);
                  return g;
         }
         std::pair<std::vector<std::pair<int, punkt>>, std::pair<int, int>> getZiemia()
         {
                  al_lock_mutex(mutex);
                  auto g =  std::pair<std::vector<std::pair<int, punkt>> , std::pair<int,int>>(ziemia, std::pair<int, int>(p_s_x, p_s_y));
                  al_unlock_mutex(mutex);
                  return g;
         }
};

struct stan_czesci_ciala
{
         char stan_rany;
};

class dla_grafiki
{
         public:

         unsigned char nat_osw = 1; ///naturalne oswietlenie calego swiata
         unsigned char nat_osw_alt = 0;
         unsigned char max_przyciemnienie_interfejsu = 180;

         bool wysokosci = false;
         short wys[13][21];

         bool cos_nowego_w_medycynie = 0;

         bool *godmode;
         bool melduj_grafike = true;

         bool melduj_pom = false;

         bool gotowy_do_przesuwania = false;

         z_planszy *plansza1,*plansza2;

         bool melduj_co_robi_AI;

         short wiadomosc = 0;

         bool menu;
         int ktore_menu;
         int wmx, wmy;

         bool submenu;
         int ktore_sub_menu;
         int wsmx,wsmy;

         bool kroki,lewy_krok,prawy_krok,gora_krok,dol_krok;
         int x1,x2,x3,x4,y1,y2,y3,y4;

         bool screen;
         int rozdz_X, rozdz_Y;
         int menu_x, menu_y;

         int cyfry1_x,cyfry1_y;
         int*obrazenia;
         struct punkt* gdzie_obrazenia;
         int ile_nad;
         int ilosc_zadan;




         bool myszka_zajeta;
         bool myszka_aim=false;

         short iskra = 0; short x_iskry, y_iskry;

         void *world;
         int X_kratka, Y_kratka;
         int flaga_zakoncz, zakonczylem;

         bool przesuwamy_plansze;
         char strona;
         int przesuniecie;

         void*plansza_docelowa;
         bool koniec_sterowania;
         bool skonczylem_sterowac;

         int p_glowa, p_korpus, p_spodnie, p_buty, p_rekawice, p_rece,
          p_plecak, p_ramie, p_kieszenl, p_kieszenp;
          int p_pozycja_x, p_pozycja_y,p_poprawka;


          /*int *lista_przedmiotow_ziemia,*lista_przedmiotow_plecak;
          int ilosc_przedmiotow_ziemia,ilosc_przedmiotow_plecak;
          struct punkt *pozycje_przedmiotow_ziemia,*pozycje_przedmiotow_plecak;
          int p_s_x, p_s_y, p_p_x, p_p_y;*/


          obrazki_ze_skrzynki skrzynki;


          bool otwarty_ekwipunek;
          bool p_1, p_2, p_3, p_4;
          int eq_przesuiniecie_z,eq_przesuiniecie_p;///wspolrzedne x dla lewego gornego

          int dlugosc_paska_s, pozycja_paska_s,dlugosc_paska_p, pozycja_paska_p;///w pikselach
          int p_nr_przedmiotu, p_x, p_y;

          int czas, punkty_ruchu;

          planszowa<short> wybuch;

          bool prosta;
          int xx1,yy1,xx2,yy2, szerokosc;

          bool otwarte_menu_anatomii;
          int klatka_max, klatka_a, brzuch_max, brzuch_a, l_ramie_max, l_ramie_a, p_ramie_max, p_ramie_a, l_dlon_max, l_dlon_a, p_dlon_max, p_dlon_a
          , l_udo_max, l_udo_a, p_udo_max, p_udo_a, l_golen_max, l_golen_a, p_golen_max, p_golen_a;
          stan_czesci_ciala rklatka, rbrzuch, rramie_l, rramie_p, rl_dlon, rp_dlon, rl_udo, rp_udo, rl_golen, rp_golen; ///stany ran

         int jedzenie_max,jedzenie_a,woda_max,woda_a,cieplo_max,cieplo_a,energia_max,energia_a;

         struct punkt bloki[20];
         struct punkt uniki[20];
         struct punkt skupienia[20];

         int rzucana_bron_id, rzucana_bron_x, rzucana_bron_y;
         double rzucana_bron_kat=0;

         bool way[4]; ///od prawej zgodnie z zegarem
         bool pp,ll,gg,dd;

         bool zostala_przesunieta;

         int pogoda;

         int cyfry_duze_x,cyfry_duze_y;
         bool menu_spania; int ile_spac;

         int kondycja;

         bool ubranie_info;
         int ocieplenie,ochrona,kamuflarz,wytrzymalosc;
         bool bron_info;
         int obrazen, blo,szans,kryty,bonus_uni,bonus_kop;


         bool da_sie_strone_w_lewo_w_craftingu=false,da_sie_strone_w_prawo_w_craftingu=false;
         bool otwarte_menu_craftingu = false;
         short ktora_kategoria = 0;
         short ktora_strona = 0;
         short *wsp_r = NULL;
         Przepis*przepis = NULL; ///ostatni null
         std::shared_ptr<co_ma_gracz> co_ma;
         rozmiary_tabeli rozmiary;

         bool runda_swiata = false;

         dla_grafiki()
         :rozmiary(0,0,0,0,0)
         {
                  for(short h=0;h<13;++h) for(short g=0;g<21;++g) wybuch[h][g]=0;
         }
};

struct Przepis
{
         ///!!!! pierwszy short to id przedmiotu a drugi to jego ilosc
         short koszt = 0;
         int *substraty = NULL;///przedmiot
         int *objekty_w_poblizu = NULL;///objekt
         ///jesli numer jest ujemny, to jest to stan szczegolny konkretnego przedmiotu, ktory bedzie rozpatrzany osobno
         ///trzeba uzupelnic narysuj_warszstat oraz jest_obok_obiektu
         ///-24 to ognisko, ktore sie pali

         int *katalizatory = NULL;///przedmiot ///ilosc to ilosc uzyc jaka bedzie wykonana na przedmiocie
         int *rezultaty = NULL;///przedmiot jesli bit stanowiacy o ujemnosci jest 0 lub objekt w p p; bit w id przedmiotu/obiektu
         ///drugi od lewej bit mowi, czy wstawiamy objekt do otoczenia
         ///zakladam, ze do srodowiska zawsze mozna cos wlozyc

         int *skills = NULL; ///wymagane umiejetnosci itd
         int ilosc_substratow = 0, ilosc_objektow_w_poblizu = 0, ilosc_katalizatorow = 0, ilosc_rezultatow = 0, ilosc_umiejetnosci = 0;

         void init(int *subs, int *obj, int *kat, int *rez, int*umj, short sub, short ob, short ka, short re, short um);

         Przepis();
         Przepis(int *subs, int *obj, int *kat, int *rez, int*umj, short sub, short ob, short ka, short re, short um);
         Przepis(short k, int *subs, int *obj, int *kat, int *rez, int*umj, short sub, short ob, short ka, short re, short um);
         void przenies(Przepis *a);
         ~Przepis();

         short potrzebne_wiersze(rozmiary_tabeli rozmiary);
         short potrzebne_wiersze_na_atrybut(rozmiary_tabeli rozmiary,short ktora);///od 0
};

enum what_happened
{
         success, fail, dead
};






int losuj(int min, int max);




#endif /* GRANDFATHER_H */






