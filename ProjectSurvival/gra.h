#include "swiat.h"
#include "swiat2.h"
#include "structy.h"
#include <string>
#include <iostream>
#include <windows.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"



class Gra
{
         Swiat* swiat;
         bool przerwa=false;
         public:
         bool godmode=1;
         ALLEGRO_MUTEX *dla_lewej = al_create_mutex(), *dla_prawej = al_create_mutex();


         private:



         friend void *Obliczanie_grafiki(ALLEGRO_THREAD * aaa, void * arg);
         std::shared_ptr<co_ma_gracz> co_ma(Gracz *g, Przepis *p);
         Item* Item_wez_lub_wykorzystaj(Gracz *g, bool to_co_w_koncu, int czym_jest);///true to wez, false wykorzystaj

         public:
         static int wersjal,wersjap;
         Skrzynka *lewa=NULL, *prawa=NULL;
         dla_grafiki*args;
         Crafting_recipes * Krafting = new Crafting_recipes();
         static void message(struct dla_grafiki*args,short = 1);
         short *wsp_rzedow(Przepis *a, rozmiary_tabeli roz);

         private:
         void opcje_zawsze_dostepne(struct dla_grafiki* arg);

         int Menu(int x, int y, struct dla_grafiki*args, struct specyfikacja_menu* menu);

         void poczekaj_na_puszczenie_klawisza(short k);

         bool jest_na_polu (dla_grafiki*args,ALLEGRO_MOUSE_STATE myszka, int x, int y);///pole standardowe, poz myszki, poz pola
         static void poczekaj_na_myszke(int przycisk);
         void koncz_z_menami(dla_grafiki*args);
         std::shared_ptr<Upadly> daj_upadlego(int x, int y, Plansza *a);


         void ruch_gracza(ALLEGRO_MOUSE_STATE myszka,
         ALLEGRO_KEYBOARD_STATE klawiatura,dla_grafiki*args);

         void anatomia(ALLEGRO_MOUSE_STATE myszka,
         ALLEGRO_KEYBOARD_STATE klawiatura);

         void crafting(ALLEGRO_MOUSE_STATE myszka,
         ALLEGRO_KEYBOARD_STATE klawiatura);

         bool mozna_do_pl;
         Skrzynka* otwarty_ekw(ALLEGRO_MOUSE_STATE myszka,
         ALLEGRO_KEYBOARD_STATE klawiatura,dla_grafiki*args, Skrzynka*s);///bierze skrzynke i z niej wypluwa nowa, czyli stara niszczy

         void uzycie_przedmiotu(Przedmiot*a, Skrzynka*s);
         static Gra *gra;
         bool pobierz_punkty_ruchu(int ile);
         bool pobierz_punkty_ruchu_i_kondycje(int ile_p_ruchu, int ile_kondycji);

         void informacje(Item*a);

         void show_message(std::string a);
         void przesun_mapy(char strona, dla_grafiki *args, Swiat*swiat);
         bool zalozylismy_nowy_plecak=false;

         czesc_ciala* wybierz_rane_czesci_ciala(ALLEGRO_MOUSE_STATE myszka);
         void wykonaj_crafting(Przepis *p, Gracz *g, co_ma_gracz *co_mamy);


         bool ekw, anat, craft;
         inline void ukryj_ekw() {ekw=args->otwarty_ekwipunek; anat=args->otwarte_menu_anatomii; craft=args->otwarte_menu_craftingu;args->otwarty_ekwipunek=args->otwarte_menu_anatomii=args->otwarte_menu_craftingu=false; }
         inline void przywroc_ekw(){args->otwarty_ekwipunek=ekw; args->otwarte_menu_anatomii=anat; args->otwarte_menu_craftingu=craft;}

         punkt wybierz_kratke_na_planszy();

         public:

         Gra(struct dla_grafiki* arg);

         Item* uzyj(Item*a);
         void dodaj_jedzenia(int ile);void dodaj_wody(int ile);

         void Rozpocznij_gre(struct dla_grafiki* arg);
bool jest_nad_ramieniem(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_glowa(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_plecakiem(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_rekami(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_korpusem(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_rekawicami(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_kieszenl(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_spodniami(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_kieszenp(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_butami(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_rzeczami_konkretnymi(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_rzeczami_postaci(ALLEGRO_MOUSE_STATE myszka);

bool jest_nad_lewa(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_prawa(ALLEGRO_MOUSE_STATE myszka);

void daj_aktualnemu_item(Item*a);
Item* zaladuj_konsumpcjum(int jej_nr,  Konsumpcjum*mag, int = 0); ///cale magazynki

Item* zaladuj_bron(int jej_nr,  Konsumpcjum*mag,int=0); ///cale magazynki
Item* rozladuj_bron(Bron*a,int); ///cale magazynki
Item* zamien_jeden_na_drugi_za_pomoca_tego(int,int,Item*a);
void spij(int gdzie, Objekt_martwy *na_czym);
int ile_czasu_spac();

bool jest_nad_klatka(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_brzuch(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_ramie(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_ramie(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_dlon(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_dlon(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_udo(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_udo(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_golen(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_golen(ALLEGRO_MOUSE_STATE myszka);

bool jest_nad_klatka_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_brzuch_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_ramie_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_ramie_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_dlon_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_dlon_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_udo_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_udo_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_l_golen_rana(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_p_golen_rana(ALLEGRO_MOUSE_STATE myszka);

bool jest_nad_strzalka_gora(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_strzalka_prawo(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_strzalka_dol(ALLEGRO_MOUSE_STATE myszka);
bool jest_nad_strzalka_lewo(ALLEGRO_MOUSE_STATE myszka);

void przesuwanie(char strona,ALLEGRO_MOUSE_STATE myszka, ALLEGRO_KEYBOARD_STATE klawiatura);
bool gracz_widzi_do_konca_w_strone(char strona);
bool aktualny_upadl;
};

void* Obliczanie_grafiki(ALLEGRO_THREAD * aaa, void * arg);
















