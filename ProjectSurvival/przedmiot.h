
#ifndef Przedmioty
#define Przemioty

#include <iostream>
#include "structy.h"

class Przedmiot;class Item;

class Skrzynka
{
         private:
         void init();
         int wersja=0;
         ALLEGRO_MUTEX *mutex = NULL;
         Przedmiot *** zawartosc=NULL; /// najpierw y potem x
         Kontener<Przedmiot> items;

         public:

         const int x,y; ///rozmiary

         static Kontener<Item> *zamien_skrzynke_na_itemy(Skrzynka*);
         static Skrzynka *zamien_itemy_na_skrzynke(Kontener<Item> *a,int,int);

         Skrzynka(int xx, int yy);
         Skrzynka(Kontener<Item> *a,int xx, int yy);
         void ustanow_mutex(ALLEGRO_MUTEX *m);
         int getWersja(){return wersja;}


         ~Skrzynka();
         Kontener<Item> *lista_itemow();
         bool wloz_przedmiot(Przedmiot *a);
         bool wloz_przedmiot(int xx, int yy, Przedmiot *a); ///gdzie ma byc wlozony, patrzac na lewy gorny rog
         bool wyjmij_przedmiot(Przedmiot *a);
         Przedmiot* zwroc_przedmiot(Item *a);
         void wyjmij_wszystko_z_usunieciem_tylko_oslonki_itemow_czyli_przedmiotow();
         Przedmiot* przedmiot(int xx, int yy);///przedmiot z danych wspolrzednych
         std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>> raport_obrazkowy();
         void usun_mutex();
};

class Przedmiot
{
         public:
         Item* item=NULL;
         int x=-1,y=-1;///pozycja w skrzynce

         Przedmiot(Item* item);
         ~Przedmiot();///!!!!!!!!!! nie usuwa zawartosci
         void usun_calego();
         int get_co_to();
         int typ_wielkosci();
         bool jest_ubraniem(),jest_plecakiem(), jest_kapeluszem(), jest_korpusem(), jest_spodniami(), jest_butami(), jest_rekawicami(), jest_bronia_na_ramie(),jest_bronia();
};

class Item
{
         public:

         virtual ~Item(){};

         int czym_jest; /// 2000+ konsumpcjum, 3000+ plecak, 4000+bron na ramie, 4500+ bron nie na ramie, 5000+glowa, 5500+korpus, 6000+spodnie, 6500+buty, 7000+rekawice, 8000+ inne

         bool jest_klodkom(),jest_kluczem(),jest_mala_bronia(),jest_bronia_biala(),jest_bronia_palna(),jest_ubraniem(),jest_plecakiem(), jest_kapeluszem(), jest_korpusem(), jest_spodniami(), jest_butami(), jest_rekawicami(), jest_bronia(),jest_bronia_na_ramie();

         int get_co_to();
         int typ_wielkosci();///1 1x1, 2 1x2, 3 2x8, 4 9x6, 5 2x6, 6 9x3, 7 8x1, 8 2x2, 9 2x1, 10 2x11, 11 9x2, 12 1x8, 13 1x5, 14 1x4, 15 3x2, 16 1x6
         int wartosc_ataku_rzucanego();
         void destruct(){delete this;}
         static Item* stworz_obiekt(int co);
         static Item* wylosuj_item(int szansa_na_ubranie,int szansa_na_plecak,int szansa_na_bron,int szansa_na_inne,int szansa_na_jedzenie,int szansa_na_medykamenty);
         static Item* wylosuj_item(char skad); /// s-standard,
         static Item** wylosuj_liste_itemow(int szansa_na_ubranie,int szansa_na_plecak,int szansa_na_bron,int szansa_na_inne,int szansa_na_jedzenie,int szansa_na_medykamenty);
         ///ostatni to NULL
         bool mozna_do_plecaka();
         bool mozna_do_kieszeni();
         virtual bool wykorzystaj(){if(this==NULL) return false;}; ///true jesli wykorzystany
         bool jest_ostrzem();
};

class Ubranie:public Item
{
         public:
         int wytrzymalosc=20;

         Ubranie(int ktore);
         ~Ubranie();
         short na_co(); ///0 glowa, 1 korpus, 2 spodnie, 3 buty, 4 rekawice
         int ochrona();///w procentach
         int cieplo();
         int kamuflaz();
         bool wykorzystaj();
         short obrazenia_butow();

};

class Konsumpcjum:public Item
{
         short pozostalo_uzyc=1;
         public:

         Konsumpcjum(int ktore, int pozostalo_uz);
         ~Konsumpcjum();
         short get_uzycia() {return pozostalo_uzyc;}
         bool wykorzystaj(); ///true jesli wykorzystany
         void dodaj_uzyc(short ile){if(ile>0) pozostalo_uzyc+=ile;}
};

class Plecak:public Item
{
         public:
         Skrzynka* s=NULL;

         Plecak(int ktore);
         ~Plecak();
         int kamuflaz();
         bool wykorzystaj(){return false;}
};

class Bron:public Item
{
         public:
         int wytrzymalosc=20;
         int mag=0;

         Bron(int ktore);
         ~Bron();
         struct punkt obrazenia();
         struct punkt blok();
         int get_obrazenia();
         int get_szansa();///w procentach
         int get_krytyk();
         int get_blok();///w procentach
         int UB();
         int KB();
         bool wykorzystaj();

         int ilosc_strzalow_w_serii();
         int grubosc_strzalu();
         int glosnosc_broni();
         bool dwureczna();

};

class Inne:public Item
{
         public:
         Inne(int co);
         bool wykorzystaj(){return false;}
};
class Klodka:public Item
{
         public:
         int HP=300;
         Klodka(int co);
         int max_hp();
         bool wykorzystaj(){return false;}
};
class Klucz:public Item
{
         public:
         Klodka*do_czego=NULL;
         Klucz(int co);
         Klucz(int co, Klodka*do_cz);
         bool wykorzystaj(){return false;}
};

















struct Crafting_recipes
{
         Przepis *** kategoria = NULL; ///[kategoria az do null][strona az do null][przepisy az do null]
         short ile_kategorii = 0;
         short *ile_w_kategorii = NULL;

         Przepis** daj_liste_przepisow(short kategoria);///ostatni null

         Crafting_recipes();
         ~Crafting_recipes();

         Przepis* daj_strone_z_kategorii(short strona, short kategoria);
         rozmiary_tabeli rozmiary(short strona, short kategoria);

         bool jest_taka_strona_z_tej_kategorii(short strona, short kategoria);
};

#endif // Przedmioty


///2001 to puszka
///2002 jablko
///2003 woda pelna czysta
///2004 woda polpelna czysta

///2005 butelka pusta
///2006 pepsi
///2007 bloodbag
///2008 alkohol
///2009 woda pelna brudna
///2010 woda polpelna brudna
///2011 mieso male surowe
///2012 mieso male upieczone
///2013 mieso surowe
///2014 mieso upieczone
///2020 czipsy

///2101 magazynek AK
///2102 magazynek Glock
///2103 magazynek Magnum
///2104 magazynek M107

///2201 lampa naftowa palaca sie
///2202 lampa naftowa nie palaca sie
///2203 nafta

///3001 to reklamowka
///3002 plecak wojskowy 1
///3003 plecak niebieski
///3004 czarna torba
///3005 plecak gorski
///3006 plecak wojskowy 2
///4003 to kij baseballowy
///4004 to kij baseballowy z gwozdziami
///4005 to siekiera
///4006 to lopata
///4007 to lom
///4008 to maczeta
///4009 to krzeslo
///4010 to patyk
///4011 to patelnia
///4012 to lampa
///4251 to AK z magazynkiem //////////////////////////////////////////////////////////////////////////abstract
///4252 to AK bez magazynka WLASCIWY
///4253 m107 z magazynkiem z dwunogiem //////////////////////////////////////////////////////////////////////////abstract
///4254 m107 z magazynkiem bez dwunogiem //////////////////////////////////////////////////////////////////////////abstract
///4255 m107 bez magazynka z dwunogiem WLASCIWY
///4256 m107 bez magazynka bez dwunogiem WLASCIWY
///4260 strzelba
///4501 to noz
///4502 to noz lowiecki
///4503 to srubokret
///4751 glock z magazynkiem /////////////////////////////////////////////////////////////abstract
///4752 glock bez magazynka WLASCIWY
///4753 magnum

///5001 to ruska czapka
///5002  zielona czapka
///5501 kurtka skorzana
///5502 niebieska bluza
///5503 kurtka pozarowa
///6001 jeanasy
///6002 spodnie wojskowe
///6003 zolte shorty
///6004 sliskie dresy
///6501 jasne buty sportowe
///6502 buty wyjsciowe
///6503 buty szare
///6504 buty czarne
///6505 buty zimowe

///8001 lornetka
///8002 drewno
///8003 dwunog do m107
///8004 raca
///8005 raca odpalona//////////////////////abstract
///8006 przescieradlo
///8007 klodka1
///8008 klodka2
///8009 klodka3
///8010 klucz1
///8011 klucz2
///8012 klucz3
///8013 wytrych
///8014 klucz1 ///////abstract
///8015 klucz2 ///////abstract
///8016 klucz3 ///////abstract
///8017 zapalki
///8018 granat
///8019 molotov
///8020 cloth
///8021 przyprawa
///8022 butelka z gwozdziami w srodku
///8023 gwozdzie

















