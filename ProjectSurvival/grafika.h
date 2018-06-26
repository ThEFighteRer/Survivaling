
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include <string>
#include "structy.h"



void * grafika(ALLEGRO_THREAD *thr,void *arg); ///musi byc nieobjektowo bo tego wymaga funkcja biblioteki allegro

class dane_rysownicze
{
         public:
         int x=0,y=0;
         ALLEGRO_BITMAP*a;
};

class graficzny
{
         const short najlewiejszy_bit = 1<<15;
         int cross_x, cross_y;

         public:

         void rysuj();

         static ALLEGRO_BITMAP * wyskaluj_menu (ALLEGRO_BITMAP* obrazek, int menu_x, int menu_y);
         static ALLEGRO_BITMAP * wyskaluj (ALLEGRO_BITMAP* obrazek, int X, int Y);
         void narysuj_duze_cyfry(int x, int y, int a);
         void namaluj_paski();
         static int najmniej_zero(int a);
         void namaluj_paskek_anatomii(stan_czesci_ciala s, const int a, const int maxx, const int x, const int y, char czesc_ciala, char rozklad);
         void namaluj_rane(int x, int y, char stan);
         void namaluj_siniak(int x, int y, char stan);
         void namaluj_bol(int x, int y, char stan);


         dane_rysownicze jak_narysowac(int nr);
         void namaluj_rzecz(ALLEGRO_BITMAP*a, int nr, int x, int y, int wsp_x, bool brac_doslownie_wymiary=false);
         ALLEGRO_BITMAP *ktore_menu();
         ALLEGRO_BITMAP *ktore_submenu();
         void narysuj_zegarek();
         void narysuj_roznego_rodzaju_mena();
         void narysuj_miniature_rzeczy(int nr, int x, int y);
         void narysuj_ekw_po_prawej();
         void rysuj_atrybut_tabeli_craftingu(short ktora, short jaki_wiersz, Przepis przepis, co_ma_gracz *co_ma_g, rozmiary_tabeli rozmiary);

         void rysuj_menu_anatomii();
         void rysuj_objawy();
         void rysuj_crafting(ALLEGRO_BITMAP *target);
         void rysuj_ekwipunek();
         void draw_cross();

         void narysuj_warsztat(int nr, int x, int y);
         void narysuj_umiejetnosc(int nr, int x, int y);
         void narysuj_cyfry_takie_czarne_z_x(int x, int y, short l); ///wsp kratki

         struct dla_grafiki *args;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_BITMAP** tlo;
         ALLEGRO_BITMAP* zombie;
         ALLEGRO_BITMAP** podklad;
         ALLEGRO_BITMAP* mp;
         ALLEGRO_BITMAP* mp1;
         ALLEGRO_BITMAP* mp2;
         ALLEGRO_BITMAP* mp3;
         ALLEGRO_BITMAP* bufor;
         ALLEGRO_BITMAP* plansza1;
         ALLEGRO_BITMAP* plansza2;
         ALLEGRO_BITMAP* avatar;
         ALLEGRO_BITMAP* el_stale;
         ALLEGRO_BITMAP* drzewa;
         ALLEGRO_BITMAP*cyfry1,*rzeczy,*rzeczy2, *menu_okno1,*menu_okno2,*menu_okno3,*menu_okno4,*menu_okno5,*zniszcz,*zniszcz_;
         ALLEGRO_BITMAP*equ, *zegarek, *zegarek_, *r_liczby, *rr_liczby, *_liczby, *kondycja_paski,*klodki;
         ALLEGRO_BITMAP*menu_plecak, *menu_ramie, *menu_ubranie, *menu_rece, *menu_kieszen,*menu_schowek, *wys;
         ALLEGRO_BITMAP*equip;ALLEGRO_BITMAP*equ_akcesoria,*menu_ognisko,*ubranie_info,*bron_info;
         ALLEGRO_BITMAP *eq1, *eq2, *menu_s, *menu_p, *menu_ziemia, *menu_plecak_s, *equ_pasek, *equ_bron;
         int szerokosc_cyfr_0, wysokosc_cyfr_0,szerokosc_cyfr_0r, wysokosc_cyfr_0r,szerokosc_zegarka, wysokosc_zegarka;
         ALLEGRO_BITMAP *anatomia, * pasek_anatomii,*czczionka_paski,*pasek_ogolny, *napisy,*pasek_uzytkowy;
         ALLEGRO_BITMAP *menu_walka1_1,*menu_walka1_2,*menu_walka1_3,*menu_walka1_4,*menu_walka1,
         *menu_walka11,*menu_walka12,*menu_walka13,*menu_walka14,*HP,*way,*pogoda,*menu_drzewo,*menu_ataku_zwiarzeta,*menu_strzelanie_zwierzeta,
         *menu_walka2,*menu_walka2_1,*menu_walka2_2,*menu_walka21,*menu_walka22, *menu_walka3, *menu_walka4, *block,*menu_pust_plecak,*beczka_sub,
         *strzelanie_menu1,*strzelanie_menu1_1,*strzelanie_menu1_2,*strzelanie_menu1_3,*strzelanie_menu1_4,*strzelanie_menu2,*strzelanie_menu2_1,*strzelanie_menu2_2,
         *strzelanie_menu3,*strzelanie_menu3_1,*strzelanie_menu11,*strzelanie_menu12, *menu_szalasu, *menu_spania, *cyfry_duze,
         *menu_drzwi1,*menu_drzwi2,*menu_drzwi3, *submenu_przemieszcz, *uniwersalne_menu,*stol_sub_2,*stol_sub_1,*menu_strony,*zjawiska, *crafting_tlo, *woda_menu,
         *crafting_el,*crafting_napisy, *menu_walka_lezacy, *menu_walka_lezacy_1, *menu_walka_lezacy_2, *efekty_medyczne, *cross, *objaw, *menuplecakanatomia;
         ALLEGRO_BITMAP **message = new ALLEGRO_BITMAP*[1], *kursor_aim;


         int h_1,h_2,h_3,h_4,h_y,p_1,p_y,pozycja_zegarka_x,pozycja_zegarka_y;

         int animacja;
         bool mysza_jest_zajeta;
         z_planszy*plansza_1=NULL;
         z_planszy*plansza_2=NULL;
         ALLEGRO_BITMAP* krajobraz;
         z_planszy*acc;
         int X;
         int Y;
         ALLEGRO_BITMAP* zwierzeta;


         ALLEGRO_BITMAP *aktualne_dynamiczie_robione_menu = NULL;
         int ktore_aktualnie_mamy_menu = -1;

         graficzny(struct dla_grafiki *argumenty);

         ~graficzny();
};










