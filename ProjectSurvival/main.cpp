
#include "grafika.h"
#include "gra.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
         //ios_base::sync_with_stdio(false);
         //for(short h=0;h<100;++h) std::cout<<losuj(1,6);throw"F";


         cin.tie(NULL);

         //A* s=new B; B*y=(B*)s;
        // cout<<y->a<<std::endl;
         //for(int g=0; g<1000; g++) cout<<losuj(0, 14)<<endl; return 0;

         /*std::list<int> aaa;
         aaa.push_back(1);
         aaa.push_back(2);
         aaa.push_back(3);
         aaa.push_back(4);
         aaa.push_back(5);
         aaa.push_back(6);
         for(std::list<int>::iterator i=aaa.begin(); i!=aaa.end();++i)
         {
                  cout<<*i;
                  if(*i==3) i=aaa.erase(i);

         }
         for(std::list<int>::iterator i=aaa.begin(); i!=aaa.end();++i)
         {
                  std::cout<<*i<<std::endl;
         }*/









         /*int *a = new int(9);
         int **b = &a;
         int *h = *b;
         *b = new int(8);
         cout<<*a;*/

    //int rozdz_X=1024, rozdz_Y=768;

    //int rozdz_X=640, rozdz_Y=480;
    al_init();
    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE klawiatura;

    ALLEGRO_THREAD* Grafika;

    al_install_mouse();


    ALLEGRO_MONITOR_INFO monitor;
    al_get_monitor_info(0, &monitor);
    int rozdz_X=monitor.x2, rozdz_Y=monitor.y2;



    //int rozdz_X=640, rozdz_Y=480;

    ///bool t[13][21]; for(int i=0; i<14; i++) {for(int j=0; j<22;j++){t[i][j]=true;}}
   ///t[1][2]=false;t[1][3]=false; t[2][1]=false;t[2][2]=false; t[2][3]=false;t[3][1]=false; t[3][2]=false;//t[0][3]=true;//t[5][1]=true;t[4][1]=true;
   ///cout<<wolna_prosta(t, 150,150, 350,350)<<endl;
    ////test do prostej

    struct dla_grafiki Dla_grafiki;
    Dla_grafiki.melduj_co_robi_AI =1;
    Dla_grafiki.melduj_grafike=0;
    Dla_grafiki.melduj_pom = false ;

    double s_X=75*rozdz_X/1920, s_Y=75*rozdz_Y/1080;
         int X=s_X-1,Y=s_Y-1;
         if(s_X>0.5)  ++X; if(s_Y>0.5) ++Y;
    Dla_grafiki.X_kratka=X; Dla_grafiki.Y_kratka=Y;Dla_grafiki.zostala_przesunieta=false;

    Dla_grafiki.menu=false; Dla_grafiki.submenu=false; Dla_grafiki.kroki=false; Dla_grafiki.screen=true; Dla_grafiki.przesuwamy_plansze=false;

    Dla_grafiki.plansza1=new z_planszy;Dla_grafiki.plansza2=new z_planszy;Dla_grafiki.myszka_zajeta=false;Dla_grafiki.koniec_sterowania=false;
    Dla_grafiki.skonczylem_sterowac=false;
    Dla_grafiki.ilosc_zadan=0;Dla_grafiki.cyfry1_x=0;Dla_grafiki.cyfry1_y=0;Dla_grafiki.ile_nad=0;Dla_grafiki.gdzie_obrazenia=NULL;
    Dla_grafiki.obrazenia=NULL;Dla_grafiki.kondycja=0;
    Dla_grafiki.p_glowa=0, Dla_grafiki.p_korpus=0, Dla_grafiki.p_spodnie=0, Dla_grafiki.p_buty=0, Dla_grafiki.p_rekawice=0, Dla_grafiki.p_rece=0,
          Dla_grafiki.p_plecak=0, Dla_grafiki.p_ramie=0, Dla_grafiki.p_kieszenl=0, Dla_grafiki.p_kieszenp=0;Dla_grafiki.pogoda=0;

          Dla_grafiki.p_poprawka=1;Dla_grafiki.p_pozycja_x=22*X+(rozdz_X-25*X-2)/2;Dla_grafiki.p_pozycja_y=5*Y;//rozdz_Y/4;
         Dla_grafiki.otwarty_ekwipunek=false;

         //Dla_grafiki.lista_przedmiotow_ziemia=NULL,Dla_grafiki.lista_przedmiotow_plecak=NULL;
         //Dla_grafiki.ilosc_przedmiotow_ziemia=0,Dla_grafiki.ilosc_przedmiotow_plecak=0;
          //Dla_grafiki.pozycje_przedmiotow_ziemia=NULL,Dla_grafiki.pozycje_przedmiotow_plecak=NULL;
          //Dla_grafiki.p_p_x=0;Dla_grafiki.p_p_y=0;Dla_grafiki.p_s_x=0;Dla_grafiki.p_s_y=0;


          Dla_grafiki.ubranie_info=0;Dla_grafiki.bron_info=0;

          Dla_grafiki.eq_przesuiniecie_z=0;Dla_grafiki.eq_przesuiniecie_z=0;
          Dla_grafiki.dlugosc_paska_s=0;Dla_grafiki.pozycja_paska_s=0;
          Dla_grafiki.dlugosc_paska_p=0;Dla_grafiki.pozycja_paska_p=0;
          Dla_grafiki.p_nr_przedmiotu=0;Dla_grafiki.p_x=0;Dla_grafiki.p_y=0;
          Dla_grafiki.czas=1435;Dla_grafiki.p_x=0;Dla_grafiki.punkty_ruchu=4;Dla_grafiki.otwarte_menu_anatomii=false;
          Dla_grafiki.otwarty_ekwipunek=false;Dla_grafiki.prosta=false;
          Dla_grafiki.rzucana_bron_id=0;Dla_grafiki.rzucana_bron_x=0;Dla_grafiki.rzucana_bron_y=0;

          for(int i=0; i<20;++i){Dla_grafiki.bloki[i].x=-1;Dla_grafiki.bloki[i].y=-1;Dla_grafiki.uniki[i].x=-1;Dla_grafiki.uniki[i].y=-1;
          Dla_grafiki.skupienia[i].x=-1;Dla_grafiki.skupienia[i].y=-1;

    for(int i=0; i<13; i++)
         {
                  for(int j=0; j<21; j++)
                           {
                                    Dla_grafiki.plansza1->przesuniecie[i][j].x=0;Dla_grafiki.plansza1->przesuniecie[i][j].y=0;
                                    Dla_grafiki.plansza1->otoczenie[i][j][0]=0;Dla_grafiki.plansza1->otoczenie[i][j][1]=-1;
                                    Dla_grafiki.plansza1->srodowisko[i][j][0]=0;Dla_grafiki.plansza1->srodowisko[i][j][1]=0;
                                    Dla_grafiki.plansza2->przesuniecie[i][j].x=0;Dla_grafiki.plansza2->przesuniecie[i][j].y=0;
                                    Dla_grafiki.plansza2->otoczenie[i][j][0]=0;Dla_grafiki.plansza2->otoczenie[i][j][1]=-1;
                                    Dla_grafiki.plansza2->srodowisko[i][j][0]=0;Dla_grafiki.plansza2->srodowisko[i][j][1]=0;
                           }
         }
         for(int i=0; i<15; i++)
         {
                  for(int j=0; j<23; j++)
                           {
                                    Dla_grafiki.plansza1->ziemia[i][j]=false;
                                    Dla_grafiki.plansza2->ziemia[i][j]=false;
                                    Dla_grafiki.plansza1->upadli[i][j]=0;
                                    Dla_grafiki.plansza2->upadli[i][j]=0;
                                    Dla_grafiki.plansza1->stany_obiektow[i][j] = 0;
                                    Dla_grafiki.plansza2->stany_obiektow[i][j] = 0;
                                    Dla_grafiki.plansza1->stany_srodowisk[i][j] = 0;
                                    Dla_grafiki.plansza2->stany_srodowisk[i][j] = 0;
                           }
         }
         for(int i=0;i<4;++i)Dla_grafiki.way[i]=false;


    Dla_grafiki.flaga_zakoncz = 0;
    Dla_grafiki.zakonczylem = 0;
    Dla_grafiki.rozdz_X = rozdz_X; Dla_grafiki.rozdz_Y=rozdz_Y;Dla_grafiki.menu_spania=false;


    Grafika = al_create_thread(grafika, &Dla_grafiki);
    al_start_thread(Grafika);

    Gra gra(&Dla_grafiki);
    Dla_grafiki.godmode = &gra.godmode;
    try
    {
    gra.Rozpocznij_gre(&Dla_grafiki);
    }
    catch(char* t)
    {
             cout<<t<<'\n';
    }


    /*ALLEGRO_MOUSE_STATE state;
    bool koniec=false;
    while (!koniec)
    {
        al_get_mouse_state(&state);
        if (state.buttons & 1)
        {

        }
        if (state.buttons & 2)
        {
            koniec = true;
        }
        if (state.buttons & 4)
        {

        }
    al_rest(0.01);
    }*/

    Dla_grafiki.flaga_zakoncz=1;
    while(true)
    {
             if(Dla_grafiki.zakonczylem==1)
                  break;
             al_rest(0.2);
    }

         cout<<"Koniec";

       return 0;
}}
