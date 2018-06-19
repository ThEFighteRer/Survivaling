#ifndef SWIAT2_H
#define SWIAT2_H

#include "swiat.h"

class Krzeslo_przejsciowe;
class Krzeslo:public Objekt_martwy///29
{
         friend class Krzeslo_przejsciowe;
         int HP=25;
         short ktore = 1;
         public:

         ~Krzeslo();
         Krzeslo(Krzeslo_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc();
};

class Krzeslo_przejsciowe:public Objekt_przejsciowy
{
         public:
         int HP=25;
         short ktore = 1;

         Krzeslo_przejsciowe();
         Krzeslo_przejsciowe(Krzeslo*a);
         ~Krzeslo_przejsciowe();
         void zapisz(std::ofstream *a);
};

class Szafa_przejsciowa;
class Szafa:public Objekt_martwy///30
{
         friend class Szafa_przejsciowa;
         int HP=200;
         short ktora = 1;
         Objekt *kto_sie_chowa = NULL;
         bool przeszukana = false;
         public:

         Kontener<Item> *zawartosc = NULL;
         ~Szafa();
         Szafa(Szafa_przejsciowa* a,int,int,int,int,int);
         void stworz_loot();
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}

         bool wejdz(Objekt *a) {return Objekt_martwy::wejdz(a, &kto_sie_chowa);}
         bool wyjdz() {return Objekt_martwy::wyjdz(&kto_sie_chowa,'n');}
         bool ukrywa_go(Objekt*kogo){return Objekt_martwy::ukrywa_go(kogo, kto_sie_chowa);}
         short latwopalnosc();
};

class Szafa_przejsciowa:public Objekt_przejsciowy
{
         public:
         int HP=200;
         short ktora = 1;
         bool przeszukana = false;
         Objekt_przejsciowy *kto_sie_chowa = NULL;
         Kontener<Item> *zawartosc = NULL;
         char zwrot;

         Szafa_przejsciowa();
         Szafa_przejsciowa(Szafa*a);
         ~Szafa_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Stol_przejsciowy;
class Stol:public Objekt_martwy///31
{
         friend class Stol_przejsciowy;
         int HP=200;
         short ktory = 1;
         Objekt *kto_sie_chowa = NULL;
         public:

         bool przewrocony = false;
         bool jest_obrus = losuj(0,1);
         Kontener<Item> *zawartosc = NULL;

         ~Stol();
         Stol(Stol_przejsciowy* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}

         bool wejdz(Objekt *a) {return Objekt_martwy::wejdz(a, &kto_sie_chowa);}
         bool wyjdz(char strona) {return Objekt_martwy::wyjdz(&kto_sie_chowa,strona);}
         bool ukrywa_go(Objekt*kogo){return Objekt_martwy::ukrywa_go(kogo, kto_sie_chowa);}
         short latwopalnosc();
};

class Stol_przejsciowy:public Objekt_przejsciowy
{
         public:
         int HP=200;
         short ktory = 1;
         bool przewrocony = false;
         bool jest_obrus = losuj(0,1);
         Kontener<Item> *zawartosc = NULL;
         Objekt_przejsciowy *kto_sie_chowa = NULL;

         Stol_przejsciowy();
         Stol_przejsciowy(Stol*a);
         ~Stol_przejsciowy();
         void zapisz(std::ofstream *a);
};

class Lozko_przejsciowe;
class Lozko:public Objekt_martwy///32
{
         friend class Lozko_przejsciowe;
         int HP=200;
         short ktore = 1;
         Objekt *kto_spi = NULL;
         public:

         bool jest_przescieradlo = losuj(0,1);

         ~Lozko();
         Lozko(Lozko_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}

         bool ktos_tu_spi() {return kto_spi != NULL;}
         bool spi_tu(Objekt*kogo){return Objekt_martwy::ukrywa_go(kogo, kto_spi);}
         bool przespij_sie_w(int ile_czasu, Objekt *kto){return Objekt_martwy::przespij_sie_w(ile_czasu,kto,&kto_spi);}
         short latwopalnosc();
};

class Lozko_przejsciowe:public Objekt_przejsciowy
{
         public:
         int HP=200;
         short ktore = 1;
         bool jest_przescieradlo = losuj(0,1);
         Objekt_przejsciowy *kto_spi = NULL;

         Lozko_przejsciowe();
         Lozko_przejsciowe(Lozko*a);
         ~Lozko_przejsciowe();
         void zapisz(std::ofstream *a);
};

class Beczka_przejsciowa;
class Beczka:public Objekt_martwy///34
{
         friend class Beczka_przejsciowa;
         int HP=70;
         unsigned char stan_b = 1; ///1-jest ropa, 2-otwarta, 4 - lezy, 8 - w lewo lezy bo jesli 0 to w prawo

         public:

         ~Beczka();
         Beczka(Beczka_przejsciowa* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}
         void wybuchnij();
         void rozlej_w_kierunku(char gdzie);
         void rozlej_w_miejscu();
         short latwopalnosc();
         bool jest_Ropa(){return stan_b&1;}
         bool jest_otwarta(){return stan_b&2;}
         void otworz();
         void zamknij();
         void przewroc_mnie(char zwr);
         void podnies();
         bool lezy(){return stan_b&4;}
};

class Beczka_przejsciowa:public Objekt_przejsciowy
{
         public:
         int HP=70;
         unsigned char stan_b = 1; ///1-jest ropa, 2-otwarta, 4 - lezy, 8 - w lewo lezy bo jesli 0 to w prawo

         Beczka_przejsciowa();
         Beczka_przejsciowa(Beczka*a);
         ~Beczka_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Ukryty_pod:public Objekt_martwy///33
{
         int HP=100;
         short ktore = 1;

         public:
         Objekt *kto_sie_ukrywa = NULL;
         Zwloki *ktore_zwl = NULL;

         Ukryty_pod(Objekt *kto_sie_ukrywa, Zwloki *ktore_zwl, short x, short y);
         ~Ukryty_pod();
         //Ukryty_pod(Lozko_przejsciowe* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}
         void wyjdz_spod();

         bool ukrywa_go(Objekt*kogo){return Objekt_martwy::ukrywa_go(kogo, kto_sie_ukrywa);}
         //bool przespij_sie_w(int ile_czasu, Objekt *kto){return Objekt_martwy::przespij_sie_w(ile_czasu,kto,&kto_sie_ukrywa);}
         short latwopalnosc();

};

class Zlamana_galaz_przejsciowa;
class Zlamana_galaz : public Objekt_pol_martwy ///35
{
         public:
         short HP = 50;

         ~Zlamana_galaz();
         Zlamana_galaz(Zlamana_galaz_przejsciowa*a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void zapisz(std::ofstream *a);
         int get_co_to();
         bool rusz_sie();
         int na_ile_hp_wyglada(){return 0;}
         short latwopalnosc();

};

class  Zlamana_galaz_przejsciowa : public Objekt_przejsciowy
{
         public:
         short HP = 50;

         Zlamana_galaz_przejsciowa(Zlamana_galaz*a);
         Zlamana_galaz_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Lampa_przejsciowa;
class Lampa : public Objekt_pol_martwy ///36
{
         bool wlaczona = true;

         public:
         short HP = 20;

         ~Lampa();
         Lampa(Lampa_przejsciowa*a,int,int,int,int,int);
         void wlacz();
         void wylacz();
         zrodlo_swiatla jak_swieci(){return wlaczona ? zrodlo_swiatla(1, 38) : zrodlo_swiatla(0,0);}
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra,short wsp_zajecia) override;
         void zapisz(std::ofstream *a);
         int get_co_to();
         bool rusz_sie();
         int na_ile_hp_wyglada(){return 0;}
         short latwopalnosc();
         bool swieci(){return wlaczona;}
};

class  Lampa_przejsciowa : public Objekt_przejsciowy
{
         public:
         short HP = 20;

         Lampa_przejsciowa(Lampa*a);
         Lampa_przejsciowa();
         void zapisz(std::ofstream *a);
};

class Reflektor_przejsciowy;
class Reflektor:public Objekt_martwy///37
{
         bool wlaczony = true;
         friend class Reflektor_przejsciowy;
         int HP=30;

         public:
         char kierunek = 'p';

         ~Reflektor();
         zrodlo_swiatla jak_swieci(){return wlaczony ? zrodlo_swiatla(2, 38) : zrodlo_swiatla(0,0);}
         Reflektor(Reflektor_przejsciowy* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc();
         void wlacz();
         void wylacz();
         bool swieci(){return wlaczony;}
};

class Reflektor_przejsciowy:public Objekt_przejsciowy
{
         public:
         int HP=30;

         Reflektor_przejsciowy();
         Reflektor_przejsciowy(Reflektor*a);
         ~Reflektor_przejsciowy();
         void zapisz(std::ofstream *a);
};

class Staly_przejsciowy;
class Staly:public Objekt_martwy///38
{
         friend class Staly_przejsciowy;
         short HP;

         public:

         const short ktory;
         ~Staly();
         zrodlo_swiatla jak_swieci(){return zrodlo_swiatla(0,0);}
         Staly(Staly_przejsciowy* a,int,int,int,int,int);
         what_happened zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia=0) override;
         int get_co_to();
         void zapisz(std::ofstream *a);
         int get_HP();
         int na_ile_hp_wyglada(){return HP;}
         short latwopalnosc();
};

class Staly_przejsciowy:public Objekt_przejsciowy
{
         public:
         short HP;
         const short ktory;

         Staly_przejsciowy();
         Staly_przejsciowy(short kt);
         Staly_przejsciowy(Staly*a);
         ~Staly_przejsciowy();
         static short max_hp(short ktory);
         short wys();
         void zapisz(std::ofstream *a);
};



#endif
