
#ifndef SWIAT_H
#define SWIAT_H

#include <cstdio>
#include "structy.h"
#include <iostream>
#include <stack>
#include <list>
#include "przedmiot.h"



bool wolna_prosta(planszowa<bool> o, int x1, int y1, int x2, int y2);

class Punkt{public: int a,b,odn;};

struct punct{int a,b;};

char skrec(char gdzie, char zwrot);
struct punkt punkt_przed(char zwrot, int x, int y);
char w_ktora_to_strone(int x, int y, int xc, int yc);

bool jest_prostopadle(int xc,int yc, int x ,int y);
bool jest_z_ukosa(int xc,int yc, int x ,int y);
char pozycja_w_zwarciu(int xc,int yc, int x ,int y, char zwrot);
char przeciwna(char strona);


class zrodlo_swiatla
{
         short rodzaj = 0;
         short moc = 0;
         short spadki = 50;

         public:
         zrodlo_swiatla(short a, short m, short s = 50)
         {
                  rodzaj = a;
                  moc = m;
                  spadki = s;
         }

         short get_rodzaj(){return rodzaj;}
         short get_moc(){return moc;}
         short get_spadki(){return spadki;}
};



class Objekt;class Gracz;class Druzyna;class Strefa;class Objekt_przejsciowy;class Zombie_przejsciowe;class Drzewo_przejsciowe;
class Woda_przejsciowa;class  Trawa_przejsciowa; class Plansza; class Stado_zombie; class Zombie;class Sarna;class Niedzwiedz;class Zwloki;
class Srodowisko;class Schowek_przejsciowy;class Ognisko_przejsciowe;class Szalas_przejsciowy;class Okno_przejsciowe;class Drzwi_przejsciowe;
class Wilk_przejsciowy; class Ognisko;

class Upadly
{
         private:

         int x,y;
         public:Objekt *a;
         Upadly(Objekt*a,int x, int y);
         int getX();
         int getY();
         Objekt* getA();
         ~Upadly();
};



class Area
{
         ALLEGRO_MUTEX * mutex = al_create_mutex();
         std::list<std::shared_ptr<Upadly>> upadnieci;

         protected:
         short biom = 0;/// 0 las, 1 pseudo miasto

         public:

         const short x,y,z;

         Kontener<podloga> *floors = new Kontener<podloga>();

         Area(short xx, short yy, short zz) : x(xx), y(yy), z(zz) {}
         virtual ~Area(){al_destroy_mutex(mutex);};
         bool ma_gracza=false;
         virtual void usun_ziemie()=0;
         virtual void Runda()=0;
         virtual void zapisz(std::ofstream *ofs)=0;
         bool jest_plansza=true;
         bool to_jest_na_podlodze(int x, int y);
         short getBiom() {return biom;}

         void dodaj_upadlego(Objekt *a, short x, short y);
         void usun_upadlego(Objekt *a);
         std::vector<std::shared_ptr<Upadly>> daj_wskazniki_do_upadlych();
         bool aktualny_upadl();
         std::shared_ptr<Upadly> ostatni_upadly(short x, short y);
         void powstan_mozliwych();
};

class Srodowisko_przejsciowe
{
         public:
         Kontener<Objekt_przejsciowy>* zawartosc=new Kontener<Objekt_przejsciowy>();
         char stan = 0;

         static Srodowisko_przejsciowe* zwroc_przejsciowe_srodowisko(Srodowisko*a);
         ~Srodowisko_przejsciowe();
         bool ma_to(int czym_ma_to_byc);
};

class Srodowisko
{
         bool czy_usuwamy(int x, int y, Plansza*p);
         bool rusza_sie=false;
         std::list<Objekt*>* stos = new std::list<Objekt*>(); ///pierwszy element to front
         ALLEGRO_MUTEX *srodowiskowy = al_create_mutex();
         std::list<Objekt*>::iterator ostatni_usuwany;

         friend class Srodowisko_przejsciowe;

         public:
         //Kontener<Objekt>* zawartosc=new Kontener<Objekt>();

         unsigned char stan = 0;
         ///bity od lewej: 1 - pali sie, 2 - szklo, 4 - wylany oil
         short przesuniecie_x=0, przesuniecie_y=0;
         short paliwo_do_palenia = 0;///rosnie gdy cos spalimy i oznacza liczbe rund palenia sie

         static void dodaj_objekt(Objekt*a, int x, int y, Plansza*p);
         Srodowisko();
         ~Srodowisko();
         static Srodowisko* zwroc_srodowisko(Srodowisko_przejsciowe*a, int x, int y, int px, int py, int pz);
         void dodaj_objekt(Objekt *a, int xx, int yy);
         short wysokosc();
         bool ma_to(int czym_ma_to_byc);
         bool ma_to(Objekt*a);
         Objekt* zwroc_objekt(int czym_ma_to_byc);
         od_srodowiska rysunek();
         void Runda(short x, short y, Plansza *pl);
         bool wykonuje_ruch();
         bool zjedz_rosline(int jaka);
         Objekt* usun_objekt(int czym_ma_byc, short x, short y, Plansza *pl);
         Objekt* usun_objekt(Objekt*a, short x, short y, Plansza *pl);
         bool ma_na_wierzchu(int co);
         void wydaj_dzwiek_bycia_deptanym(Plansza*);
         void podpal();
         void zgas(short x, short y, Plansza *p);
         void palenie(short x, short y, Plansza *pl);
         bool sproboj_podpalic();
         Objekt* wierzch();
         bool do_usuniecia();
         void ogarnij_sie_z_wykonywaniem_ruchu();
         void zostan_uderzony_ogolnie(short obr, short rodzaj);

         zrodlo_swiatla swiatlo();
};

class Plansza : public Area ///objekt
{
         inline void wysrodkuj_swiatlo();

         public:
         static struct Punkt *c;

         planszowa<Objekt*> otoczenie;
         planszowa<Srodowisko *> srodowisko;
         planszowa<Kontener<Item> *> ziemia;
         std::list<Objekt*> juz_martwy;


         planszowa<short> oswietlenie; ///0 nic, 1 prawo, dol, lewo, gora
         planszowa<short> oswietlenie_z_innych_plansz;
         static planszowa <short> pomocnicza;
         static planszowa<bool> pom[5];
         static planszowa<short> oswietlenie_extra[5];

         static short wstaw_w_punkty(punkt **a, short index, short odl, short x, short y);
         static short ile(short odl, short x, short y);


         Plansza(int,int,int);
         Plansza(Strefa* a);
         ~Plansza();

         void zdeletuj_juz_martwych();
         void usun_ziemie();
         void rzuc_na_ziemie(int xx, int yy, Item *aa);
         void rzuc_na_ziemie(int xx, int yy, Kontener<Item> *aa);///czysci aa z przedmiotow
         void dodaj_do_srodowiska(int xx, int yy, Objekt*a);
         void zapisz(std::ofstream *ofs);
         bool wczytaj();
         void Runda();
         void zaktualizuj_widoki(int x1,int y1, int x2, int y2, bool akt_poboczne=true);
         void zaktualizuj_widoki(int x1,int y1, bool akt_poboczne=true){return zaktualizuj_widoki(x1, y1, x1, y1,akt_poboczne);}
         void zaktualizuj_widoki(bool akt_poboczne=true); ///bezwzglednie
         void iskra(short x, short y);
         void rozejdz_swiatlo(const short x, const short y, short moc,short, short, bool poza_plansze, short ktory_bufor, char jak);
         void rozejdz_swiatlo_reflektora(const short xxx, const short yyy, short moc, short zasieg, short spadki, short wysokosc_swiatla, char zwrot, bool tez_poza_plansze, short ktory_bufor, char jak);
         void animacja_iskry(short x, short y);

         void dzwiek(bool moze_wyjsc_poza_plansze,int moc, int dx, int dy,int rodzaj);
         void aktualizuj_swiatlo(short ktory_bufor, char co); ///1 - wszystko, 2 - tylko obce plansze, 3 tylko nasza plansza
         void dziej_ogien();
         void wybuch(punkt **p);///ostatni to NULL
         void podpalenie_o_mocy(short moc, short x, short y, short paliwo);
         void wybuch_o_mocy(short moc, short x, short y);
         void res_osw_inn_pl();
         void zamieszanie_ze_swiatlem(bool, short ktory_bufor);
         void ta_plansza_juz_nie_celem(Plansza *a);
};

#include "allegro5/allegro.h"

class Strefa : public Area ///struct
{
         void stworz_budynek(short ktory);
         //void stworz_pokoj(short ktory, punkt_na_planszy a, punkt_na_planszy b);
         punkt_na_planszy czy_da_sie_taki_postawic(int wx, int wy);
         bool czy_da_sie_taki_postawic_tu(int wx, int wy, int x, int y);
         void postaw_okna_na_odcinku(punkt_na_planszy a, punkt_na_planszy b, bool prawo_dol, short min_odstep, bool budynek_jest_p_d);
         bool postaw_drzwi_na_odcinku(short ktore, punkt_na_planszy a, punkt_na_planszy b, bool = false);
         void zrob_pokoj(short ktory, punkt_na_planszy a, punkt_na_planszy b, short = 4);
         template<typename co>
         void rozstaw_losowo_obiekty(short ile, punkt_na_planszy a, punkt_na_planszy b);
         bool nie_blokuje_drzwi(short x, short y);

         void generuj_las();
         void generuj_pseudo_miasto();
         void generuj_probe();

         public:

         planszowa<Objekt_przejsciowy*> otoczenie;
         planszowa<Srodowisko_przejsciowe *> srodowisko;
         planszowa<Kontener<Item>*> ziemia;

         template<typename T>
         void postaw_pare_obiektow(T*obiekt, int ilosc, bool = false);
         template<typename co>
         void postaw_pare_obiektow_na_srodowisku(int ilosc, bool = false);
         Strefa(int,int,int);
         Strefa(Plansza* a);
         ~Strefa();
         void usun_ziemie();
         void Runda();
         void zapisz(std::ofstream *ofs);
         static bool w_planszy(short x, short y);

         bool srodowisko_ma_to(int co, int x, int y);
         void srodowisko_wrzuc(Objekt_przejsciowy *a, int x, int y);
};

class Swiat ///kostka do gry
{
         unsigned char jasnosc_ogolna = 30;
         int a_x=0, a_y=0, a_z=0; ///aktualna
         Area **** area;
         std::list<Plansza*> wysypisko_plansz;

         public:

         inline unsigned char getJasnosc() {return jasnosc_ogolna;}

         Kontener<Gracz>*gracz=new Kontener<Gracz>;

         //Kontener<Objekt> Objekty;
         //Objekt* objekt; ///objekty ktore musza wykonac runde NIE DRZEWA!
         //void dodaj_objekt(Objekt* o); int ile=0, miejsce=0;


         bool koniec=false;

         Kontener<Stado_zombie>* stada_zombie=new Kontener<Stado_zombie>();
         //Druzyna *druzyna;
         bool* pauza ;
         const int promien_obszaru_zywego=2;//3; ///to wartosc x, yto x+1
         int czas=1080;//720;
         short pogoda=0; ///0 1 2 3 4 5
         int od_ostatniej_zmiany_pogody=140;
         bool zaczynamy_rundy_od_poczatku=false;///zmienna porzadkowa

         const int w_x=40, w_y=40, w_z=1; ///wymiary

         Swiat(FILE f);
         Swiat(bool* p,int X,int Y,dla_grafiki*arg, bool godmode);
         ~Swiat();

         void jak_tam_wysypisko_plansz();
         bool zapisz(std::string nazwa_pliku);
         void Nastepna_runda();
         void Runda_swiata_bez_graczy();
         void Aktualizuj_pogode();
         void Ustaw_aktualna(int x,int y,int z);
         void Ustaw_aktualna(Plansza*a);
         bool w_zasiegu_gracza(Area *a); ///okresla czy area nalezy do swiata zywego czy do uspionego
         bool w_zasiegu_gracza(int x, int y, int z);
         bool ma_gracza_niespiacego(Plansza*a);
         void zaktualizuj_oddzialywanie_swietlne_plansz_na_siebie();

         Area* zwroc_taka_aree(short x, short y, short z);
         Plansza* zwroc_taka_plansze(short x, short y, short z);
         Plansza* zwroc_taka_plansze_TYLKO(short x, short y, short z);
         Strefa* zwroc_taka_strefe_TYLKO(short x, short y, short z);
         void stworz_strefe(short x, short y, short z);
         void stworz_plansze(short x, short y, short z);

         Plansza *aktualna = NULL, *przewijana = NULL;
         bool czy_przesuwamy = false;

         bool teraz_gracz = true;
         Gracz *aktualny;

         int X,Y; ///rozmiary kratki
};

class Objekt_przejsciowy
{
         public:
         virtual ~Objekt_przejsciowy();
         int czym_jest;
         char stan=0;
         //int x,y;
         static Objekt_przejsciowy* z_objektu(Objekt*a);
         virtual void zapisz(std::ofstream *a)=0;
};

class zwrot_odl
{
         public:
         short x, y, u=0;
         zwrot_odl(short x, short y, short u)
         {
                  this->x=x; this->y=y; this->u=u;
         }
};

class Punkt_wagowy
{
         public:
         short od_wrogow = 3; ///jak blisko wrogow trzeba przejsc
         short a = -1, b = -1;
         short odn = -1;
         short od_wrogow_wlasny = 3;
};

class Objekt
{
         protected:

         bool poza_tym_swiatem = false;
         void smierc();


         public:


         static struct Punkt *c, *z;
         static Punkt_wagowy *d;
         static bool wstrzymaj_animacje;
         const short czym_jest=0;

         Objekt(short a, bool z) : czym_jest(a), zywy(z){}

         const bool zywy;

         virtual ~Objekt();
         static Objekt* stworz_objekt_z_wykraftowania(int co, int, int, int, int, int);
         bool nie_wykonal_ruchu=true;
         bool wykonuje_ruch=true;
         unsigned char stan = 0;///bity od lewej, 1 - plonie
         static Swiat*swiat;
         static dla_grafiki*args;
         short wysokosc=3;
         int co_to=0;///dla grafiki
         int animacja=0;
         short x,y; ///wspolrzedne na planszy
         int px, py, pz; ///wspolrzedne planszy
         bool przesuwamy=false;
         int przesuniecie_x=0,przesuniecie_y=0;
         char zwrot='p';
         static planszowa<bool> obstacles;

         bool sproboj_podpalic();
         bool exists() {return !poza_tym_swiatem;}


         virtual what_happened reakcja_na_podloze();
         void animacja_ataku(char strona);
         bool widzi_obiekt(const Plansza*, const int,const int,const int,const int,int,int);
         int get_animacja();
         void powstan();
         void przewroc();
         bool ktos_ma_go_za_ofiare(Plansza*p);


         void animacja_strzalu(int x1, int y1, int x2, int y2, int szerokosc);
         bool mozna_strzelic(Objekt*a);
         bool mozna_rzucic(short x, short y);

         void animacja_bycia_uderzanym_jak_drzewo(int HP,int obrazenia,int max_hp);
         void animacja_obrazen();
         void animacja_damage(int a);
         void wydaj_dzwiek(bool moze_wyjsc_poza_plansze,int moc, int dx, int dy, int rodzaj);///x i y to cel sluchacza, zwykle to uzytkownik ale np ten sam gatunek moze sie ostrzegac
         static Objekt* z_objektu_tymczasowego(Objekt_przejsciowy*a,int,int,int,int,int);
         virtual what_happened zostan_uderzony(int obrazenia, int kto, int w_co, short wsp_zajecia=0)=0;///zwraca tylko dead i success
         virtual void uslysz_dzwiek(int dx,int dy,int rodzaj)=0;///x i y to cel do ktorego sluchacz przyjdzie
         virtual void uslysz_dzwiek(Plansza *a,int rodzaj)=0;
          virtual bool rusz_sie()=0;
          virtual int get_co_to();
          virtual void patrz()=0;
          virtual void zapisz(std::ofstream *a)=0;
          virtual short latwopalnosc()=0;
          void animacja_rzutu_przedmiotu(dla_grafiki*args,double xx, double yy, Item*a);
          bool jest_zaraz_obok(Objekt*a);
          int bycie_uderzanym_jak_drzewo(int HP,int obrazenia,int max_hp);
          virtual what_happened przesun(char strona, bool=true);
          virtual void dzwiek_przesuniecia(int xx, int yy)=0;
          bool czy_lezy();
         virtual int na_ile_hp_wyglada()=0;
         zrodlo_swiatla swiatlo();
         short priorytet_w_srodowisku();

         int odleglosc_w_kratkach(short xx, short yy);
         static short odleglosc_w_kratkach(short xx, short yy, short cx, short cy);
         int odleglosc_w_kratkach(Objekt*a);
         bool kratka_z_tylu_jest_wolna(int xcc,int ycc);///przeciwlegla
         char kratka_z_tylu(int xcc,int ycc);///przeciwlegla
         char daj_zwrot_do_punktu(int xc, int yc);
         static char losuj_zwrot();
         bool jest_naprzeciw_nas(short xx, short yy);
         static bool jest_prostopadle(int xc,int yc, int xx ,int yy);
         static char przeciwna(char strona);
         punkt naprzeciwko();
         punkt kratka_za_gosciem_jak_chce_go_kopnac(short x_goscia, short y_goscia);
         static bool jest_z_ukosa(int xc,int yc, int x ,int y);
         static bool zaraz_obok(int xc,int yc, int x ,int y);

         bool jest_roslinozerca();
         bool jest_drapieznikiem();

         Plansza* wyznacz_plansze_ucieczkowa(Plansza*, bool mozna_niszcz);
         char jak_dojsc_na_plansze(Plansza *a, bool mozna_niszczyc_przedmioty);
         char jak_uciec_na_plansze(Plansza *a);
         char jak_dotrzec_do_obszaru(punkt_na_planszy pier, punkt_na_planszy dru, bool*wykluczone_punkty, bool po_szerokosci, bool **p);
         bool w_obszarze(short x, short y, punkt_na_planszy a, punkt_na_planszy b, bool *punkty, bool po_szer);
         bool w_obszarze_i_niewykluczony(short x, short y, punkt_na_planszy a, punkt_na_planszy b, bool *punkty, bool po_szer);
         char gdzie_isc(int cx, int cy, int ppx, int ppy, bool p[13][21]);
         bool da_sie_dojsc(int xc, int yc, int x, int y, Plansza*a);

         zwrot_odl wyznacz_punkt_ucieczki_w_obrebie_planszy();
         void zrownowaz_sciezki_wagowo(short); ///rownowazy rekurencyjnie sciezki do funckji z gory

         short srednia_odl_od_wrogow(Objekt **wr, short xx, short yy);
         Objekt** zwroc_tablice_wrogow_z_tej_planszy();
         static short najblizszy_przeciwnik(short xx, short yy, Objekt **wr);
         void zbliz_lub_oddal(bool co_zrob, short x, short y);
         void wyjdz_animacja(short xx, short yy);
};

char gdzie_isc(int cx, int cy, int ppx, int ppy,bool p[13][21]);

class Objekt_zywy : public Objekt
{
         protected:
         bool OSZOLOMION = false; ///wewnetrzna zmienna dla objektu
         bool oszolomion = 0;///zmienna na nast runde, ktora bedzie przeinaczana przez srodowisko

         public:

         Objekt_zywy(short a) : Objekt(a, true) {}

         short czekanie=0;
         Objekt* ofiara=NULL;
         bool jest_cel=false;
         bool celem_jest_plansza=false;
         Plansza* ktora_plansza=NULL;
         bool jest_ofiara=false;
         int xc, yc;

         void zoszolom();
         bool oszolomiony();


         void przestan_byc_ofiara(int promien_plansz, short = -1, short = -1); ///uzywane podczas smierci, sprawdza czy ktos nie jest na nas sfokusowany, zakladajac ze calej dlugosci planszy w ciagu rundy nikt nie zrobi to zadziala

         bool ma_tyle_i_odejmij(short &skad, short ile);
         int na_ile_hp_wyglada(){return 100;}
         //struct punkt gdzie_na_plansze(Plansza* a);
         virtual what_happened uderz(char gdzie)=0;
         virtual ~Objekt_zywy();
         bool czy_widzi_wzgl_zwezania(int dx, int dy, int odciecia, int xw, int yw);
         virtual bool rusz_sie()=0;
         char znajdz_droge(bool umiemy_niszczyc_przedmioty,int cx, int cy, int px, int py,Plansza* a);
         char znajdz_ucieczke(int ominiecie,int cx, int cy, int px, int py,Plansza* a);



         what_happened przejdz_nad_pod_objektem(short xx, short yy);

};

class Objekt_martwy : public Objekt
{
         public:


         Objekt_martwy(short a) : Objekt(a, false) {}
         virtual ~Objekt_martwy();
         void patrz();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         bool rusz_sie();
         void dzwiek_przesuniecia(int xx, int yy){}
         virtual int na_ile_hp_wyglada()=0;

         ///interface kryjowkowy odnosi sie tylko do typu Objekt, typ Objekt_przejsciwoy musi sam rozporzadzac tym, co ma
         protected:
         bool wejdz(Objekt *a, Objekt **kto_sie_chowa);
         bool wyjdz(Objekt **kto_sie_chowa, char strona);
         bool wywal_gdzies_obok(Objekt **kto_sie_chowa);
         void kryjowka_destroyer(Objekt **kto_sie_chowa);
         bool ukrywa_go(Objekt*kogo, Objekt* ukryty);


         static void stworz_loot(Kontener<Item> *zawartosc, int szansa_na_ubranie,int szansa_na_plecak,int szansa_na_bron,int szansa_na_inne,int szansa_na_jedzenie,int szansa_na_medykamenty);

         bool przespij_sie_w(int ile_czasu, Objekt *kto, Objekt **miejsce_do_spania);
         void lozko_destroyer(Objekt **kto_spi);


         public:
         bool przesun_po_srodowisku(char gdzie);

};

class Objekt_pol_martwy : public Objekt
{
         public:

         Objekt_pol_martwy(short a) :Objekt(a, false) {}
         virtual ~Objekt_pol_martwy();
         void patrz();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         virtual bool rusz_sie()=0;
         void dzwiek_przesuniecia(int xx, int yy){}
         virtual int na_ile_hp_wyglada()=0;

};

class Gracz : public Objekt_zywy///10
{
         void ogrzej_sie_od_zrodel_ognia();

         Objekt_zywy * sprzymierzeni = nullptr;
         int ilosc_sprzymierzonych = 0;

         std::list<std::pair<Objekt*, short>> zablokowani;
         std::list<Objekt*> uniknieci;
         std::list<Objekt*> skupieni;
         ALLEGRO_MUTEX *mutex_blokow = al_create_mutex();
         ALLEGRO_MUTEX *mutex_unikow = al_create_mutex();
         ALLEGRO_MUTEX *mutex_skupien = al_create_mutex();

         ALLEGRO_MUTEX *mutex_itemow_zalozonych = al_create_mutex();
         int *graph = new int[10];///to tablica tylko dla grafiki



         public:

         bool powinien_zerknac_w_medycyne = false;

         Item *p_glowa=NULL, *p_korpus=NULL, *p_spodnie=NULL, *p_buty=NULL, *p_rekawice=NULL, *p_rece=NULL,
                  *p_plecak=NULL, *p_ramie=NULL, *p_kieszenl=NULL, *p_kieszenp=NULL;

         int* worn_items_graphics();///tylko ta jest dla grafiki
         /*Item * GETp_glowa() {return p_glowa;}///nie dla grafiki
         Item * GETp_korpus() {return p_korpus;}///nie dla grafiki
         Item * GETp_spodnie() {return p_spodnie;}///nie dla grafiki
         Item * GETp_buty() {return p_buty;}///nie dla grafiki
         Item * GETp_rekawice() {return p_rekawice;}///nie dla grafiki
         Item * GETp_rece() {return p_rece;}///nie dla grafiki
         Item * GETp_plecak() {return p_plecak;}///nie dla grafiki
         Item * GETp_ramie() {return p_ramie;}///nie dla grafiki
         Item * GETp_kieszenl() {return p_kieszenl;}///nie dla grafiki
         Item * GETp_kieszenp() {return p_kieszenp;}///nie dla grafiki

         void SETp_glowa(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_glowa = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_korpus(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_korpus = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_spodnie(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_spodnie = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_buty(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_buty = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_rekawice(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_rekawice = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_rece(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_rece = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_plecak(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_plecak = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_ramie(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_ramie = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_kieszenl(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_kieszenl = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki
         void SETp_kieszenp(Item *i) {al_lock_mutex(mutex_itemow_zalozonych); p_kieszenp = i; al_unlock_mutex(mutex_itemow_zalozonych);}///nie dla grafiki*/




         bool ukryty = false;

         czesc_ciala klatka, brzuch, ramie_l, ramie_p, l_dlon, p_dlon, l_udo, p_udo, l_golen, p_golen;

          ///short klatka_max=40, klatka_a=40, brzuch_max=30, brzuch_a=30, l_ramie_max=10, l_ramie_a=10, p_ramie_max=10, p_ramie_a=10, l_dlon_max=5, l_dlon_a=5, p_dlon_max=5, p_dlon_a=5
           ///     , l_udo_max=15, l_udo_a=15, p_udo_max=15, p_udo_a=15, l_golen_max=10, l_golen_a=10, p_golen_max=10, p_golen_a=10;

         Skrzynka *otwarta = NULL; ///wykorzystywana wylacznie w craftingu

         bool otwiera=false, gwizdze=false, krzyczy=false;
         //////short leczenie=0;
         char ilosc_kieszeni='2';
         char postawa='r';
         int p_ruchu=10;
         short pozostalo_snu=0;
         Objekt_martwy *gdzie_spi = NULL;
         int kondycja=18;

         short woda_max=300, woda_a=300,jedzenie_max=300, jedzenie_a=300,cieplo_max=300, cieplo_a=300,energia_max=300, energia_a=300;

         Gracz();
         ~Gracz();

         std::vector<punkt> blokowani();
         std::vector<punkt> unikani();
         std::vector<punkt> skupiani();
         bool jest_wsrod_blokow(Objekt *a);
         bool jest_wsrod_unikow(Objekt *a);
         bool jest_wsrod_skupien(Objekt *a);
         void dodaj_blok(Objekt *a, short blok);
         void dodaj_unik(Objekt *a);
         void dodaj_skupienie(Objekt *a);
         short ile_bloku(Objekt *a);
         short suma_hp_rak() {return ramie_l.ile_hp() + ramie_p.ile_hp() + p_dlon.ile_hp() + l_dlon.ile_hp();}

         void dodaj_cieplo(short ile) {if(cieplo_a+ile<cieplo_max) cieplo_a+=ile; else cieplo_a=cieplo_max;}

         bool wstan_ze_snu();
         short stan_nog();
         int kamuflaz();
         int ocieplenie();
         bool odejmij_hp_z_powodu_niedozywienia();
         bool czy_zyje();
         int uzycie_ubrania(Item **ubr, int obrazenia, char='n');
         bool zaktualizuj_po_rundzie();
         void zaktualizuj_przed_runda();///nie zabija!!!!!
         short wart_zajecia();
         int obrazenia(Bron *b);
         int szansa(Bron *b);
         bool moze_chodzic() {return stan_nog()!=1 && stan_nog()!=2;}

         int zasieg_wzroku();
         void strzel(Objekt*a);
         what_happened uderz(char gdzie){return success;};
         void dzwiek_przesuniecia(int xx, int yy);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void patrz();
         bool rusz_sie();
         int get_co_to();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         void zapisz(std::ofstream *a);
         void dostan_item(Item *a);
         short latwopalnosc();
         bool gracz_widzi_do_konca_w_strone(char strona);

         bool posiada_przedmiot(int jaki, short w_ilosci,bool=false);
         Item** odbierz_przedmiot(int jaki, short w_ilosci, bool=true);
         bool ma_umiejetnosc(short jaka);
         bool jest_obok_objektu(short jakiego);
         void wykorzystaj_item(short jaki);
};

class Czlowiek : public Objekt_zywy
{

         void dzwiek_przesuniecia(int xx, int yy);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         bool rusz_sie();
         void patrz();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         void zapisz(std::ofstream *a);
         short latwopalnosc();
};

class Czlowiek_przejsciowy : public Objekt_przejsciowy
{
         void zapisz(std::ofstream *a);
};

class Drzewo : public Objekt_martwy ///20
{
         public:
         short HP=100;
         short ktore = losuj(0,2);

         ~Drzewo();
         Drzewo();
         Drzewo(Drzewo_przejsciowe*a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void zapisz(std::ofstream *a);
         int na_ile_hp_wyglada(){return HP;}
         int get_co_to();
         short latwopalnosc();
};

class Woda : public Objekt_martwy ///21
{
         public:

         ~Woda();
         Woda();
         Woda(Woda_przejsciowa*a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void zapisz(std::ofstream *a);
         int na_ile_hp_wyglada(){return 20000;}
         short latwopalnosc();
};

class  Drzewo_przejsciowe : public Objekt_przejsciowy
{
         public:
         short HP=100;
         short ktore = losuj(0,2);

         Drzewo_przejsciowe(Drzewo*a);
         Drzewo_przejsciowe();
         ~Drzewo_przejsciowe();
         void zapisz(std::ofstream *a);
};

class  Woda_przejsciowa : public Objekt_przejsciowy
{
         public:
         Woda_przejsciowa(Woda*a);
         Woda_przejsciowa();
         ~Woda_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Trawa : public Objekt_pol_martwy ///22
{
         public:
         int rosniecie=0; ///w gore to 120
         short ktora=losuj(0,1);

         Trawa();
         ~Trawa();
         Trawa(Trawa_przejsciowa*a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void zapisz(std::ofstream *a);
         int get_co_to();
         bool rusz_sie();
         int na_ile_hp_wyglada(){return 0;}
         short latwopalnosc();

};

class  Trawa_przejsciowa : public Objekt_przejsciowy
{
         public:
         short ktora=losuj(0,1);
         int wysokosc;

         Trawa_przejsciowa(Trawa*a);
         Trawa_przejsciowa();
         ~Trawa_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Stado_zombie
{
         public:
         int x,y,z;
         char gdzie_skrecamy='p';
         short czas=0;

         Stado_zombie(int,int,int);
         ~Stado_zombie();
         void Runda();
         void zaszczep_stado();
};

class Zombie : public Objekt_zywy///2
{
         private:
         short hp_reka_1=15,hp_reka_2=15,hp_noga_1=25,hp_noga_2=25,hp_korpus=70, hp_glowa=10;
         short punkty_ruchu = 10;

         bool rozpedzony = false;
         public:

         bool lezy=false;
         bool w_poprzedniej_stal=false;
         bool krzyczy=false;

         bool wlasnie_przeszukuje = false;
         bool *co_juz_przeszukane = NULL;
         punkt_na_planszy skad_przeszukuje;

         //Stado_zombie* stado=NULL;

         bool moze_chodzic(){return hp_noga_1>0 && hp_noga_2>0;}
         Zombie();
         ~Zombie();
         what_happened przesun_sie(char decyzja);
         Zombie(Zombie_przejsciowe* a,int,int,int,int,int);
         void dzwiek_przesuniecia(int xx, int yy);
         what_happened uderz(char strona);
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         void patrz();
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         int get_co_to();
         bool rusz_sie();
         void zapisz(std::ofstream *a);
         void dostosuj_cel_przeszukan_do_budynkow();
         punkt_na_planszy zwroc_punkt_przeszukania(short nr);
         short latwopalnosc();
         bool mamy_niepoinformowanego_zombie(Plansza* p);
};

class  Zombie_przejsciowe : public Objekt_przejsciowy
{
         public:
          ///reka, reka, noga, noga
         Zombie_przejsciowe(Zombie*a);
         Zombie_przejsciowe();
         ~Zombie_przejsciowe();
         void zapisz(std::ofstream *a);
};

class  Sarna_przejsciowa : public Objekt_przejsciowy
{
         public:
         short HP=100;
         int jedzenie=60;
         int woda=60;

         Sarna_przejsciowa();
         Sarna_przejsciowa(Sarna*a);
         ~Sarna_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Sarna : public Objekt_zywy ///8
{
         friend class Objekt;
         Plansza *z_ktorej_uciekam = NULL;
         Plansza *na_ktorej_ost_bylem = NULL;

         public:
         short HP=100;
         short punkty_ruchu = 25;

         char zwrot_ostatni='l'; ///to, jak obrocona bedzie grafika
         bool jedzaca=false;
         bool zaalarmowana=false;
         bool biegnie=false;
         int jedzenie=60;
         int woda=60;
         char pamiec=0; ///od lewej gory, dwie warstwy

         Sarna();
         ~Sarna();
         Sarna(Sarna_przejsciowa* a,int,int,int,int,int);
         what_happened uderz(char gdzie){return fail;};
         void dzwiek_przesuniecia(int xx, int yy);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void patrz();
         bool rusz_sie();
         int get_co_to();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         void zapisz(std::ofstream *a);
         what_happened przesun_sie_losowo();
         short latwopalnosc();
};

class  Niedzwiedz_przejsciowy : public Objekt_przejsciowy
{
         public:
         short HP=400;
         int jedzenie=120;
         int woda=120;

         Niedzwiedz_przejsciowy();
         Niedzwiedz_przejsciowy(Niedzwiedz*a);
         ~Niedzwiedz_przejsciowy();
         void zapisz(std::ofstream *a);
};

class Niedzwiedz : public Objekt_zywy ///9
{
         friend class Objekt;
         Plansza *na_ktorej_ost_bylem = NULL;

         public:
         bool rozpedzony = false;

         short HP=400;
         short punkty_ruchu = 10;

         char zwrot_ostatni='p'; ///to, jak obrocona bedzie grafika
         bool atakujacy=false;
         bool zaalarmowany=false;
         bool biegnie=false;
         int jedzenie=120;
         int woda=120;
         char pamiec=0; ///od lewej gory, dwie warstwy

         what_happened przesun_sie(char decyzja);
         Niedzwiedz();
         ~Niedzwiedz();
         Niedzwiedz(Niedzwiedz_przejsciowy* a,int,int,int,int,int);
         what_happened uderz(char strona);
         void dzwiek_przesuniecia(int xx, int yy);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void patrz();
         bool rusz_sie();
         int get_co_to();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         void zapisz(std::ofstream *a);
         short latwopalnosc();
};

class Wilk;
class  Wilk_przejsciowy : public Objekt_przejsciowy
{
         public:
         short HP=90;
         int jedzenie=120;
         int woda=120;
         short punkty_ruchu = 10;

         Wilk_przejsciowy();
         Wilk_przejsciowy(Wilk*a);
         ~Wilk_przejsciowy();
         void zapisz(std::ofstream *a);
};

class Wilk : public Objekt_zywy ///9
{
         friend class Objekt;
         Plansza *na_ktorej_ost_bylem = NULL;

         public:
         short HP=90;

         char zwrot_ostatni='p'; ///to, jak obrocona bedzie grafika
         bool atakujacy=false;
         bool zaalarmowany=false;
         bool biegnie=false;
         int jedzenie=120;
         int woda=120;
         char pamiec=0; ///od lewej gory, dwie warstwy

         what_happened przesun_sie(char decyzja);
         Wilk();
         ~Wilk();
         Wilk(Wilk_przejsciowy* a,int,int,int,int,int);
         what_happened uderz(char strona);
         void dzwiek_przesuniecia(int xx, int yy);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void patrz();
         bool rusz_sie();
         int get_co_to();
         void uslysz_dzwiek(int x,int y,int rodzaj);
         void uslysz_dzwiek(Plansza *a,int rodzaj);
         void zapisz(std::ofstream *a);
         short latwopalnosc();
};

class  Zwloki_przejsciowe : public Objekt_przejsciowy
{
         public:
         int czyje_zwloki;
         unsigned char stan_zwlok;

         Zwloki_przejsciowe(Zwloki*a);
         ~Zwloki_przejsciowe();
         void zapisz(std::ofstream *a);
};

class Zwloki:public Objekt_martwy///100
{
         public:
         int czyje_zwloki;
         unsigned char stan_zwlok;
         short HP = 100;

         Zwloki(int,unsigned char,int,int,int,int,int);
         ~Zwloki();
         Zwloki(Zwloki_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int na_ile_hp_wyglada(){return 0;}
         short latwopalnosc();
         void ukryj_sie_pod(Objekt *a);
};

class Schowek:public Objekt_martwy///23
{
         public:
         Kontener<Item> *zawartosc = NULL;
         int HP=50;
         bool otwarty=false;

         Schowek();
         ~Schowek();
         Schowek(Schowek_przejsciowy* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc();
};

class Schowek_przejsciowy:public Objekt_przejsciowy
{
         public:
         Kontener<Item> *zawartosc = NULL;
         int HP=50;
         bool otwarty=false;

         Schowek_przejsciowy();
         Schowek_przejsciowy(Schowek*a);
         ~Schowek_przejsciowy();
         void zapisz(std::ofstream *a);
};

class Ognisko:public Objekt_pol_martwy///24
{
         friend class Ognisko_przejsciowe;

         short HP=30;
         short paliwo=0;
         bool pali_sie=false;

         public:

         Ognisko(int,int,int,int,int);
         ~Ognisko();
         Ognisko(Ognisko_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         int get_co_to();
         bool getPaliSie(){return pali_sie;}
         void dorzuc_paliwa(short ile){paliwo+=ile;}
         void podpal(){pali_sie=true;}
         void zapisz(std::ofstream *a);
         bool rusz_sie();
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc(){return 100;}
};

class Ognisko_przejsciowe:public Objekt_przejsciowy
{
         public:
         int HP=30;
         short paliwo=0;

         Ognisko_przejsciowe();
         Ognisko_przejsciowe(Ognisko*a);
         ~Ognisko_przejsciowe();
         void zapisz(std::ofstream *a);
};

class Szalas:public Objekt_martwy///25
{
         public:
         Kontener<Item> *zawartosc = NULL;
         int HP=100;
         Objekt *kto_spi=NULL;

         Szalas();
         ~Szalas();
         Szalas(Szalas_przejsciowy* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int na_ile_hp_wyglada(){return HP;}
         bool przespij_sie_w(int ile_czasu, Objekt *kto){return Objekt_martwy::przespij_sie_w(ile_czasu,kto,&kto_spi);}
         short latwopalnosc();
};

class Szalas_przejsciowy:public Objekt_przejsciowy
{
         public:
         Kontener<Item> *zawartosc = NULL;
         int HP=100;
         Objekt_przejsciowy *kto_spi=NULL;

         Szalas_przejsciowy();
         Szalas_przejsciowy(Szalas*a);
         ~Szalas_przejsciowy();
         void zapisz(std::ofstream *a);
};

class Okno:public Objekt_martwy///26
{
         private:
         bool jest_zaslona=losuj(0,1), wybite=false, otwarte=false,zasloniete=false;

         public:
         int HP=25;

         bool get_wybite(),get_otwarte(),get_zasloniete(),get_jest_zaslona();
         void zaloz_zaslone(),zdejmij_zaslone(),otworz(),zamknij(),odslon(),zaslon();
         Okno();
         ~Okno();
         Okno(Okno_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia=0) override;
         void ogarnij_sie_z_wysokoscia(bool=false);
         int get_co_to();
         void zapisz(std::ofstream *a);
         bool mozna_stad_podejsc(int xx, int yy);
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc();
};

class Okno_przejsciowe:public Objekt_przejsciowy
{
         public:
         int HP=25;
         bool jest_zaslona=losuj(0,1), wybite=false, otwarte=false,zasloniete=false;
         char zwrot='g';

         Okno_przejsciowe();
         Okno_przejsciowe(char dzie);
         Okno_przejsciowe(Okno*a);
         ~Okno_przejsciowe();
         void zapisz(std::ofstream *a);
};

class Drzwi:public Objekt_martwy///27
{
         friend class Drzwi_przejsciowe;

         Klodka *klodka1=NULL,*klodka2=NULL,*nasza=NULL;
         short ktore = 0;
         char co_zamkniete=0;
         int HP=200;
         bool otwarte=false;
         public:

         //Drzwi();
         ~Drzwi();
         Drzwi(Drzwi_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         Klodka* otworz_klodke(Klucz*a);
         bool zamknij_na_klucz(Klucz*a);
         void wylam_klodke(int czym);
         bool zaloz_klodke(Klodka*a);
         void otworz();
         void zamknij();
         int na_ile_hp_wyglada(){return HP;}
         char get_co_zamkniete();
         short latwopalnosc();
};

class Drzwi_przejsciowe:public Objekt_przejsciowy
{
         public:

         short ktore=0;
         Klodka *klodka1=NULL,*klodka2=NULL,*nasza=NULL;
         int HP=200;
         char co_zamkniete=0;

         Drzwi_przejsciowe(short ktore);
         Drzwi_przejsciowe(Drzwi*a);
         ~Drzwi_przejsciowe();
         void zapisz(std::ofstream *a);
};



class Sciana_przejsciowa;
class Sciana:public Objekt_martwy///28
{
         friend class Sciana_przejsciowa;
         short ktora = 0;
         int HP=10000;

         public:

         ~Sciana();
         Sciana(Sciana_przejsciowa* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc();
};

class Sciana_przejsciowa:public Objekt_przejsciowy
{
         public:
         int HP=10000;
         short ktora = 0;
         char co_zamkniete=0;

         Sciana_przejsciowa(short ktora);
         Sciana_przejsciowa(Sciana*a);
         ~Sciana_przejsciowa();
         void zapisz(std::ofstream *a);
};



#endif
