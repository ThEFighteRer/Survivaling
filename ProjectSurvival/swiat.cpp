#include "swiat.h"
#include "swiat2.h"
#include <iostream>
#include <fstream>

Upadly::Upadly(Objekt*a,int x, int y)
{
         this->a=a;this->x=x;this->y=y;
}
int Upadly::getX(){return x;}
int Upadly::getY(){return y;}
Objekt* Upadly::getA(){return a;}
Upadly::~Upadly(){}

void Area::dodaj_upadlego(Objekt *a, short x, short y)
{
         al_lock_mutex(mutex);
         upadnieci.push_back(std::shared_ptr<Upadly>(new Upadly(a, x, y)));
         al_unlock_mutex(mutex);
}

void Area::usun_upadlego(Objekt *a)
{
         al_lock_mutex(mutex);
         std::list<std::shared_ptr<Upadly>>::iterator pos;
         for(std::list<std::shared_ptr<Upadly>>::iterator it=upadnieci.begin(); it!=upadnieci.end(); ++it)
                  if((*it)->a==a) {pos = it; break;}
         upadnieci.erase(pos);
         al_unlock_mutex(mutex);
}

std::vector<std::shared_ptr<Upadly>> Area::daj_wskazniki_do_upadlych()
{
         al_lock_mutex(mutex);
         std::vector<std::shared_ptr<Upadly>> tab (upadnieci.size());
         short g=0;

         for(std::list<std::shared_ptr<Upadly>>::iterator it=upadnieci.begin(); it!=upadnieci.end(); ++it)
                  tab[g++] = *it;
         al_unlock_mutex(mutex);
         return tab;
}

bool Area::aktualny_upadl()
{
         al_lock_mutex(mutex);
         for(std::list<std::shared_ptr<Upadly>>::iterator it=upadnieci.begin(); it!=upadnieci.end(); ++it)
                  if((*it)->a==Objekt::swiat->aktualny) {al_unlock_mutex(mutex);return true;}
         al_unlock_mutex(mutex);
         return false;
}

std::shared_ptr<Upadly> Area::ostatni_upadly(short x, short y)
{
         al_lock_mutex(mutex);
         for(std::list<std::shared_ptr<Upadly>>::iterator it=upadnieci.begin(); it!=upadnieci.end(); ++it)
                  if((*it)->getX()==x && (*it)->getY()==y) {al_unlock_mutex(mutex);return *it;}
                  al_unlock_mutex(mutex);
         return NULL;
}

void Area::powstan_mozliwych()
{
         if(!jest_plansza) return;
         al_lock_mutex(mutex);

         for(std::list<std::shared_ptr<Upadly>>::iterator it=upadnieci.begin(); it!=upadnieci.end(); ++it)
                  if(((Plansza*)this)->otoczenie[(*it)->getY()][(*it)->getX()]==NULL)
                  {
                           (*it)->a->x=(*it)->getX();
                           (*it)->a->y=(*it)->getY();
                           ((Plansza*)this)->otoczenie[(*it)->getY()][(*it)->getX()] = (*it)->a;
                           (*it)->a->powstan();
                           ((Plansza*)this)->zaktualizuj_widoki((*it)->a->x, (*it)->a->y, (*it)->a->x, (*it)->a->y);
                           (*it)->a->nie_wykonal_ruchu = false;
                           it = upadnieci.erase(it);
                  }
         al_unlock_mutex(mutex);
}


void Area ::Runda(){}
bool Swiat::zapisz(std::string nazwa_pliku)
{
         ///wielkosc, druzyny rzem z ich pozycjami, plansze

         std::ofstream ofs(nazwa_pliku+".bin", std::ios::binary);
         ofs.close();
         return true;
}

void Plansza::zapisz(std::ofstream *ofs)
{

}

void Strefa::zapisz(std::ofstream *ofs)
{

}











Plansza::Plansza(Strefa *a):Area(a->x, a->y, a->z)
{
         biom = a->getBiom();
         floors = a->floors;
         a->floors = NULL;
         jest_plansza=true;
         for(int i=0; i<21; i++)
         {
                  for(int j=0; j<13;j++)
                  {
                           if(a->otoczenie[j][i]==NULL) otoczenie[j][i]=NULL;
                           else {otoczenie[j][i]=Objekt::z_objektu_tymczasowego(a->otoczenie[j][i],i,j,x,y,z);}
                           ziemia[j][i]=a->ziemia[j][i];
                           if(a->srodowisko[j][i]!=NULL)srodowisko[j][i]=Srodowisko::zwroc_srodowisko(a->srodowisko[j][i], i, j, x, y, z);else srodowisko[j][i]=NULL;
                           oswietlenie[j][i]=1;
                           oswietlenie_z_innych_plansz[j][i]=30;
                  }
         }
}

Strefa::Strefa(Plansza *a):Area(a->x, a->y, a->z)
{
         biom = a->getBiom();
         floors = a->floors;
         a->floors = NULL;
         jest_plansza=false;
         short licznik_traw = 0;
         for(int i=0; i<21; i++)
         {
                  for(int j=0; j<13;j++)
                  {
                           if(a->otoczenie[j][i]==NULL) otoczenie[j][i]=NULL;
                           else if(a->otoczenie[j][i]->czym_jest==33 && !((Ukryty_pod*)a->otoczenie[j][i])->ukrywa_go(NULL)
                                   && ((Ukryty_pod*)a->otoczenie[j][i])->kto_sie_ukrywa->czym_jest!=33)
                           {
                                otoczenie[j][i]=Objekt_przejsciowy::z_objektu(((Ukryty_pod*)a->otoczenie[j][i])->kto_sie_ukrywa);
                           }
                           else
                           {
                               otoczenie[j][i]=Objekt_przejsciowy::z_objektu(a->otoczenie[j][i]);
                           }


                           ziemia[j][i]=a->ziemia[j][i];
                           if(a->srodowisko[j][i]!=NULL && !a->srodowisko[j][i]->do_usuniecia())
                           {
                                    srodowisko[j][i]=Srodowisko_przejsciowe::zwroc_przejsciowe_srodowisko(a->srodowisko[j][i]);
                                    if(a->srodowisko[j][i]->ma_to(22)) licznik_traw++;
                           }
                           else srodowisko[j][i]=NULL;
                  }
         }
         postaw_pare_obiektow_na_srodowisku<Trawa_przejsciowa>(losuj(0,14-licznik_traw), false);
}

int ilosc_w_zal_od_mocy(int moc)
{
         if(moc==0) return 5; ///zamiast 1 dla bezpieczenstwa
         int a=1, b=(moc-1)*2; if(moc!=0) a=(moc+1)*2; if(b<0) b=0;
         return a+b+ilosc_w_zal_od_mocy(moc-1);
}

void Plansza::zdeletuj_juz_martwych()
{
         for(std::list<Objekt*>::iterator i=juz_martwy.begin(); i!=juz_martwy.end(); ++i)
         {
                  delete (*i);
         }
}

void Plansza::dzwiek(bool moze_wyjsc_poza_plansze,int moc, int dx, int dy,int rodzaj)
{
         //std::cout<<"(";
         //moze_wyjsc_poza_plansze  = false;
         Plansza *ap,*ax,*ad,*aw,*al,*az,*ag,*ay;
         Swiat *swiat = Objekt::swiat;
         short px=x, pz=z, py=y;
         ap=swiat->zwroc_taka_plansze(px+1, py, pz);
         al=swiat->zwroc_taka_plansze(px-1, py, pz);
         ad=swiat->zwroc_taka_plansze(px, py+1, pz);
         ag=swiat->zwroc_taka_plansze(px, py-1, pz);
         az=swiat->zwroc_taka_plansze(px-1, py-1, pz);
         ay=swiat->zwroc_taka_plansze(px+1, py-1, pz);
         aw=swiat->zwroc_taka_plansze(px-1, py+1, pz);
         ax=swiat->zwroc_taka_plansze(px+1, py+1, pz);

         //std::cout<<")";
         //int ile=ilosc_w_zal_od_mocy(moc);
         c[0].a=dy; c[0].b=dx; int n=1,s=0,k=1;
         for(int j=0; j<moc; j++)
         {
                  for(int y=s;y<k;y++)
                  {
                           bool lewo=true,prawo=true,dol=true,gora=true;
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b+1 && c[u].a==c[y].a){prawo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b-1 && c[u].a==c[y].a){lewo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a-1){gora=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a+1){dol=false;break;}}

                           for(int h=0;h<4;h++)
                           {
                                    if (h==0 && prawo) {c[n].a=c[y].a; c[n].b=c[y].b+1;}
                                    else if (h==1 && lewo) {c[n].a=c[y].a; c[n].b=c[y].b-1;}
                                    else if (h==2 && gora) {c[n].a=c[y].a-1; c[n].b=c[y].b;}
                                    else  if (h==3 && dol) {c[n].a=c[y].a+1; c[n].b=c[y].b;}
                                    else continue;

                                    if(c[n].a<13 && c[n].a>-1 && c[n].b<21 && c[n].b>-1)
                                    {
                                             if(otoczenie[c[n].a][c[n].b]!=NULL && (c[n].a!=y || c[n].b!=x))
                                                      otoczenie[c[n].a][c[n].b]->uslysz_dzwiek(dx,dy,rodzaj);
                                    }
                                    else if(moze_wyjsc_poza_plansze)
                                    {
                                             ///dzwiek moze miec zasieg jednej planszy, wieksze nie beda dalej slyszane
                                             if(c[n].a<26 && c[n].a>-14 && c[n].b<42 && c[n].b>-21)
                                             {
                                                      if(c[n].b>20)
                                                      {
                                                               if(c[n].a<0)
                                                               {if(ay==NULL) continue;if(ay->otoczenie[c[n].a+13][c[n].b-21]!=NULL) ay->otoczenie[c[n].a+13][c[n].b-21]->uslysz_dzwiek(this,rodzaj);}
                                                               else if(c[n].a<13)
                                                               {if(ap==NULL) continue;if(ap->otoczenie[c[n].a][c[n].b-21]!=NULL) ap->otoczenie[c[n].a][c[n].b-21]->uslysz_dzwiek(this,rodzaj);}
                                                               else
                                                               {if(ax==NULL) continue;if(ax->otoczenie[c[n].a-13][c[n].b-21]!=NULL) ax->otoczenie[c[n].a-13][c[n].b-21]->uslysz_dzwiek(this,rodzaj);}
                                                      }
                                                      else if(c[n].b<0)
                                                      {
                                                               if(c[n].a<0)
                                                               {if(az==NULL) continue;if(az->otoczenie[c[n].a+13][c[n].b+21]!=NULL) az->otoczenie[c[n].a+13][c[n].b+21]->uslysz_dzwiek(this,rodzaj);}
                                                               else if(c[n].a<13)
                                                               {if(al==NULL) continue;if(al->otoczenie[c[n].a][c[n].b+21]!=NULL) al->otoczenie[c[n].a][c[n].b+21]->uslysz_dzwiek(this,rodzaj);}
                                                               else
                                                               {if(aw==NULL) continue;if(aw->otoczenie[c[n].a-13][c[n].b+21]!=NULL) aw->otoczenie[c[n].a-13][c[n].b+21]->uslysz_dzwiek(this,rodzaj);}
                                                      }
                                                      else
                                                      {
                                                               if(c[n].a<0)
                                                               {if(ag==NULL) continue; if(ag->otoczenie[c[n].a+13][c[n].b]!=NULL) ag->otoczenie[c[n].a+13][c[n].b]->uslysz_dzwiek(this,rodzaj);}
                                                               else if(c[n].a<13)
                                                               {if(otoczenie[c[n].a][c[n].b]!=NULL) otoczenie[c[n].a][c[n].b]->uslysz_dzwiek(this,rodzaj);}
                                                               else
                                                               {if(ad==NULL) continue;if(ad->otoczenie[c[n].a-13][c[n].b]!=NULL) ad->otoczenie[c[n].a-13][c[n].b]->uslysz_dzwiek(this,rodzaj);}
                                                      }
                                             }
                                    }
                                    n++;
                                    if(n>=2490) return;
                           }
                  }
                  s=k;k=n;
         }
}

#include <algorithm>

int max(int a, int b) {return a>b ? a : b;}

double oblicz_prosta_w_punkcie_x(float x1, float y1, float x2, float y2, float x)
{
         if(y1==y2) ++y1; if(x1==x2) ++x1;
         float a = (y1-y2)/(x1-x2);
         return a*x+(y1-a*x1);
}

double oblicz_prosta_w_punkcie_y(float x1, float y1, float x2, float y2, float y)
{
         if(y1==y2) ++y1; if(x1==x2) ++x1;
         float a = (y1-y2)/(x1-x2);
         return (y-(y1-a*x1))/a;
}

void Plansza::rozejdz_swiatlo(const short xxx, const short yyy, short moc, short spadki, short wysokosc_swiatla, bool tez_poza_plansze, short ktory_bufor, char jak)
{
         if(moc<30) moc=30; if(moc<1) moc = 1;
         Plansza *ap = NULL,*ad = NULL,*al = NULL,*ag = NULL;
         Swiat *swiat = Objekt::swiat;
         short px=x, pz=z, py=y;
         if(tez_poza_plansze)
         {
                  ap = swiat->zwroc_taka_plansze(px+1, py, pz);
                  al = swiat->zwroc_taka_plansze(px-1, py, pz);
                  ad = swiat->zwroc_taka_plansze(px, py+1, pz);
                  ag = swiat->zwroc_taka_plansze(px, py-1, pz);
                  //std::cout<<ad<<std::endl;
                  //ad->otoczenie[5][5]=new Niedzwiedz; al->oswietlenie[5][5]=253; ap->oswietlenie[5][5]=253; return;
                  for(short i=1; i<5; ++i)
                  {
                           Plansza *a;
                           switch(i)
                           {
                                    case 1: a=ag; break;
                                    case 2: a=al; break;
                                    case 3: a=ap; break;
                                    case 4: a=ad; break;
                           }
                           if(!a) continue;

                           for(short u=0;u<21;++u) for(short h=0;h<13;++h) pom[i][h][u] = a->otoczenie[h][u] ? (a->srodowisko[h][u] ? max(a->otoczenie[h][u]->wysokosc, a->srodowisko[h][u]->wysokosc()) : a->otoczenie[h][u]->wysokosc) :  (a->srodowisko[h][u] ? a->srodowisko[h][u]->wysokosc() : 0);
                  }

         }




         ///    1
         ///2 0 3
         ///    4
         for(short u=0;u<21;++u) for(short h=0;h<13;++h) pom[0][h][u] = otoczenie[h][u]!=NULL ? (srodowisko[h][u]!=NULL ? max(otoczenie[h][u]->wysokosc, srodowisko[h][u]->wysokosc()) : otoczenie[h][u]->wysokosc) :  (srodowisko[h][u]!=NULL ? srodowisko[h][u]->wysokosc() : 0);

         //std::cout<<xxx<<" "<<yyy<<'\n';
         c[0].a=yyy; c[0].b=xxx; int n=1,s=0,k=1;
         if(oswietlenie_extra[ktory_bufor][yyy][xxx]>moc) {oswietlenie_extra[ktory_bufor][yyy][xxx] = moc;}
         for(int natezenie = moc; natezenie<253; natezenie+=spadki)
         {
                  for(int y=s;y<k;y++)
                  {
                           bool lewo=true, prawo=true, dol=true, gora=true;
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b+1 && c[u].a==c[y].a){prawo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b-1 && c[u].a==c[y].a){lewo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a-1){gora=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a+1){dol=false;break;}}

                           for(int h=0;h<4;h++)
                           {
                                    if (h==0 && prawo) {c[n].a=c[y].a; c[n].b=c[y].b+1;}
                                    else if (h==1 && lewo) {c[n].a=c[y].a; c[n].b=c[y].b-1;}
                                    else if (h==2 && gora) {c[n].a=c[y].a-1; c[n].b=c[y].b;}
                                    else  if (h==3 && dol) {c[n].a=c[y].a+1; c[n].b=c[y].b;}
                                    else continue;

                                    if(Strefa::w_planszy(c[n].b, c[n].a))
                                    {
                                             if(jak==2) continue;
                                             //if(tez_poza_plansze) continue;
                                             if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, c[n].b*100+50, c[n].a*100+50))
                                                      if(oswietlenie_extra[ktory_bufor][c[n].a][c[n].b]>natezenie) {oswietlenie_extra[ktory_bufor][c[n].a][c[n].b] = natezenie;}
                                    }
                                    else
                                    {
                                             if(jak==3) continue;
                                             if(!tez_poza_plansze) continue;
                                             ///dzwiek moze miec zasieg jednej planszy, wieksze nie beda dalej slyszane
                                             if(c[n].a<26 && c[n].a>-14 && c[n].b<42 && c[n].b>-21)
                                             {
                                                      if(c[n].b>20)
                                                      {
                                                               if(!Strefa::w_planszy(c[n].b-21, c[n].a) || ap==NULL) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_x(xxx*100+50, yyy*100+50, c[n].b*100+50, c[n].a*100+50, 20*100+50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, 20*100+50, aaa) && wolna_prosta(pom[3], 50, aaa, (c[n].b-21)*100+50, c[n].a*100+50))
                                                                        if(ap->oswietlenie_z_innych_plansz[c[n].a][c[n].b-21]>natezenie) ap->oswietlenie_z_innych_plansz[c[n].a][c[n].b-21] = natezenie;
                                                      }
                                                      else if(c[n].b<0)
                                                      {
                                                               if(!Strefa::w_planszy(c[n].b+21, c[n].a) || al==NULL) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_x(xxx*100+50, yyy*100+50, c[n].b*100+50, c[n].a*100+50, 50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, 50, aaa) && wolna_prosta(pom[2], 20*100+50, aaa, (c[n].b+21)*100+50, c[n].a*100+50))
                                                                        if(al->oswietlenie_z_innych_plansz[c[n].a][c[n].b+21]>natezenie) al->oswietlenie_z_innych_plansz[c[n].a][c[n].b+21] = natezenie;
                                                      }
                                                      else if(c[n].a<0)
                                                      {
                                                               if(!Strefa::w_planszy(c[n].b, c[n].a+13) || ag==NULL) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_y(xxx*100+50, yyy*100+50, c[n].b*100+50, c[n].a*100+50, 50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, aaa, 50) && wolna_prosta(pom[1], aaa, 12*100+50, c[n].b*100+50, (c[n].a+13)*100+50))
                                                                        if(ag->oswietlenie_z_innych_plansz[c[n].a+13][c[n].b]>natezenie) ag->oswietlenie_z_innych_plansz[c[n].a+13][c[n].b] = natezenie;
                                                      }
                                                      else if(c[n].a>12)
                                                      {
                                                               if(!Strefa::w_planszy(c[n].b, c[n].a-13) || ad==NULL) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_y(xxx*100+50, yyy*100+50, c[n].b*100+50, c[n].a*100+50, 12*100+50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, aaa, 12*100+50) && wolna_prosta(pom[4], aaa, 50, c[n].b*100+50, (c[n].a-13)*100+50))
                                                                        if(ad->oswietlenie_z_innych_plansz[c[n].a-13][c[n].b]>natezenie) {ad->oswietlenie_z_innych_plansz[c[n].a-13][c[n].b] = natezenie;}

                                                      }
                                             }
                                    }
                                    n++;
                                    if(n>=2490) return;
                           }
                  }
                  s=k;k=n;
         }
}

void Plansza::rozejdz_swiatlo_reflektora(const short xxx, const short yyy, short moc, short zasieg, short spadki, short wysokosc_swiatla, char zwrot, bool tez_poza_plansze, short ktory_bufor, char jak)
{
         if(moc<30) moc=30;
         Plansza *ap,*ad,*al,*ag;
         Swiat *swiat = Objekt::swiat;
         short px=x, pz=z, py=y;
         if(tez_poza_plansze)
         {
                  ap = swiat->zwroc_taka_plansze(px+1, py, pz);
                  al = swiat->zwroc_taka_plansze(px-1, py, pz);
                  ad = swiat->zwroc_taka_plansze(px, py+1, pz);
                  ag = swiat->zwroc_taka_plansze(px, py-1, pz);

                  for(short i=1; i<5; ++i)
                  {
                           Plansza *a;
                           switch(i)
                           {
                                    case 1: a=ag; break;
                                    case 2: a=al; break;
                                    case 3: a=ap; break;
                                    case 4: a=ad; break;
                           }
                           if(!a) continue;
                           for(short u=0;u<21;++u) for(short h=0;h<13;++h) pom[i][h][u] = a->otoczenie[h][u]!=NULL ? (a->srodowisko[h][u]!=NULL ? max(a->otoczenie[h][u]->wysokosc, a->srodowisko[h][u]->wysokosc()) : a->otoczenie[h][u]->wysokosc) :  (a->srodowisko[h][u]!=NULL ? a->srodowisko[h][u]->wysokosc() : 0);
                  }
         }

         ///    1
         ///2 0 3
         ///    4
         for(short u=0;u<21;++u) for(short h=0;h<13;++h) pom[0][h][u] = otoczenie[h][u]!=NULL ? (srodowisko[h][u]!=NULL ? max(otoczenie[h][u]->wysokosc, srodowisko[h][u]->wysokosc()) : otoczenie[h][u]->wysokosc) :  (srodowisko[h][u]!=NULL ? srodowisko[h][u]->wysokosc() : 0);

         short szer=xxx, wys=yyy; if(zwrot=='p' || zwrot=='l') {szer=yyy; wys=xxx;}
         short natezenie;
         short ile_na_tej_mocy = 0;

         for(short i=0;true;++i)///dlugosc
         {
                  short f = i/2 + 1;
                  if(ile_na_tej_mocy++==zasieg)
                  {
                           ile_na_tej_mocy = 0; if(--zasieg==0) return; moc+=spadki; if(moc>252) return;
                  }

                  for(short e=szer-f; e<=szer+f; ++e)///szerokosc
                  {
                           natezenie = moc + spadki*abs(e-szer);
                           if(natezenie>253) continue;

                           for(int h=0;h<4;h++)
                           {
                                    short akt_x=e, akt_y=i+yyy + (zwrot=='g' ? -1 : 1); if(zwrot=='p' || zwrot=='l') {akt_x=i+xxx+(zwrot=='p' ? 1 : -1); akt_y=e;}

                                    if(akt_y<13 && akt_y>-1 && akt_x<21 && akt_x>-1)
                                    {
                                             if(jak==2) continue;
                                             //if(tez_poza_plansze) continue;
                                             if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, akt_x*100+50, akt_y*100+50))
                                                      if(oswietlenie_extra[ktory_bufor][akt_y][akt_x]>natezenie) {oswietlenie_extra[ktory_bufor][akt_y][akt_x] = natezenie;}
                                    }
                                    else
                                    {
                                             if(jak==3) continue;
                                             if(!tez_poza_plansze) continue;
                                             ///dzwiek moze miec zasieg jednej planszy, wieksze nie beda dalej slyszane
                                             if(akt_y<26 && akt_y>-14 && akt_x<42 && akt_x>-21)
                                             {
                                                      if(akt_x>20)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x-21, akt_y) || !ap) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_x(xxx*100+50, yyy*100+50, akt_x*100+50, akt_y*100+50, 20*100+50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, 20*100+50, aaa) && wolna_prosta(pom[3], 50, aaa, (akt_x-21)*100+50, akt_y*100+50))
                                                                        if(ap->oswietlenie_z_innych_plansz[akt_y][akt_x-21]>natezenie) ap->oswietlenie_z_innych_plansz[akt_y][akt_x-21] = natezenie;
                                                      }
                                                      else if(akt_x<0)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x+21, akt_y) || !al) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_x(xxx*100+50, yyy*100+50, akt_x*100+50, akt_y*100+50, 50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, 50, aaa) && wolna_prosta(pom[2], 20*100+50, aaa, (akt_x+21)*100+50, akt_y*100+50))
                                                                        if(al->oswietlenie_z_innych_plansz[akt_y][akt_x+21]>natezenie) al->oswietlenie_z_innych_plansz[akt_y][akt_x+21] = natezenie;
                                                      }
                                                      else if(akt_y<0)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x, akt_y+13) || !ag) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_y(xxx*100+50, yyy*100+50, akt_x*100+50, akt_y*100+50, 50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, aaa, 50) && wolna_prosta(pom[1], aaa, 12*100+50, akt_x*100+50, (akt_y+13)*100+50))
                                                                        if(ag->oswietlenie_z_innych_plansz[akt_y+13][akt_x]>natezenie) ag->oswietlenie_z_innych_plansz[akt_y+13][akt_x] = natezenie;
                                                      }
                                                      else if(akt_y>12)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x, akt_y-13) || !ad) continue;
                                                               float aaa = oblicz_prosta_w_punkcie_y(xxx*100+50, yyy*100+50, akt_x*100+50, akt_y*100+50, 12*100+50);
                                                               if(wolna_prosta(pom[0], xxx*100+50, yyy*100+50, aaa, 12*100+50) && wolna_prosta(pom[4], aaa, 50, akt_x*100+50, (akt_y-13)*100+50))
                                                                        if(ad->oswietlenie_z_innych_plansz[akt_y-13][akt_x]>natezenie) {ad->oswietlenie_z_innych_plansz[akt_y-13][akt_x] = natezenie;}

                                                      }
                                             }
                                    }
                           }
                  }
         }
}

void Plansza::wysrodkuj_swiatlo()
{

}

int min(int a, int b) {return a>b ? b : a;}

void Plansza::aktualizuj_swiatlo(short ktory_bufor, char co)
{
         if(co==1 || co==3) for(short yy=0; yy<21; ++yy) for(short u=0; u<13; ++u) {oswietlenie_extra[ktory_bufor][u][yy] = min(oswietlenie_z_innych_plansz[u][yy],Objekt::swiat->getJasnosc());}

         for(short u=0; u<13; ++u)
                  for(short j=0; j<21; ++j)
                  {
                           if(otoczenie[u][j] && otoczenie[u][j]->swiatlo().get_rodzaj()!=0)///na razie odrozniamy tylko jeden rodzaj swiatla
                           {
                                    if(otoczenie[u][j]->swiatlo().get_rodzaj()==1)
                                    rozejdz_swiatlo(j, u, otoczenie[u][j]->swiatlo().get_moc(), otoczenie[u][j]->swiatlo().get_spadki(), otoczenie[u][j]->wysokosc, 1, ktory_bufor, co);
                                    else if(otoczenie[u][j]->swiatlo().get_rodzaj()==2)
                                    rozejdz_swiatlo_reflektora(j, u, otoczenie[u][j]->swiatlo().get_moc(), 5,otoczenie[u][j]->swiatlo().get_spadki(), otoczenie[u][j]->wysokosc, otoczenie[u][j]->zwrot, 1, ktory_bufor, co);
                           }
                           if(srodowisko[u][j] && srodowisko[u][j]->swiatlo().get_rodzaj()!=0)
                           {
                                    if(srodowisko[u][j]->swiatlo().get_rodzaj()==1)
                                    rozejdz_swiatlo(j, u, srodowisko[u][j]->swiatlo().get_moc(), srodowisko[u][j]->swiatlo().get_spadki(), srodowisko[u][j]->wysokosc(), 1, ktory_bufor, co);
                                    else if(srodowisko[u][j]->swiatlo().get_rodzaj()==2)
                                    rozejdz_swiatlo_reflektora(j, u, srodowisko[u][j]->swiatlo().get_moc(), 5,srodowisko[u][j]->swiatlo().get_spadki(), srodowisko[u][j]->wysokosc(),'p', 1, ktory_bufor, co);
                           }
                           if(Objekt::args->wybuch[u][j] && Objekt::swiat->aktualna==this)
                           {
                                    rozejdz_swiatlo(j, u, 50, 100, 3, 1, ktory_bufor, co);
                           }
                  }
         if(co==1 || co==3) for(short yy=0; yy<21; ++yy) for(short u=0; u<13; ++u) oswietlenie[u][yy] = oswietlenie_extra[ktory_bufor][u][yy];
}

void Swiat::zaktualizuj_oddzialywanie_swietlne_plansz_na_siebie()
{/*return;
         for(short u=0; u<w_x; ++u)
                  for(short j=0; j<w_y; ++j)
                  {
                           if(area[u][j][0]->jest_plansza)
                           {
                                    Plansza *a = (Plansza*) area[u][j][0];
                                    for(short h=0; h<21; ++h)
                                             for(short g=0; g<13; ++g)
                                             {
                                                       a->oswietlenie_z_innych_plansz[g][h] = 253;
                                             }
                           }
                  }

         for(short q=0; q<w_x; ++q)
                  for(short s=0; s<w_y; ++s)
                  {
                           if(area[q][s][0]->jest_plansza)
                           {
                                    Plansza *a = (Plansza*) area[q][s][0];
                                    for(short h=0; h<21; ++h)
                                             for(short g=0; g<13; ++g)
                                             {
                                                      for(short u=0; u<13; ++u)
                                                               for(short j=0; j<21; ++j)
                                                               {
                                                                        if(a->otoczenie[u][j]->swiatlo().get_rodzaj()!=0)
                                                                        {
                                                                                 if(a->otoczenie[u][j]->swiatlo().get_rodzaj()==1)
                                                                                 a->rozejdz_swiatlo(j, u, a->otoczenie[u][j]->swiatlo().get_moc(), a->otoczenie[u][j]->swiatlo().get_spadki(), a->otoczenie[u][j]->wysokosc, 1, ktory_bufor);
                                                                                 else if(a->otoczenie[u][j]->swiatlo().get_rodzaj()==2)
                                                                                 a->rozejdz_swiatlo_reflektora(j, u, a->otoczenie[u][j]->swiatlo().get_moc(), 5, a->otoczenie[u][j]->swiatlo().get_spadki(), a->otoczenie[u][j]->wysokosc,a->otoczenie[u][j]->zwrot, 1, ktory_bufor);
                                                                        }
                                                                        if(a->srodowisko[u][j]->swiatlo().get_rodzaj()!=0)
                                                                        {
                                                                                 if(a->srodowisko[u][j]->swiatlo().get_rodzaj()==1)
                                                                                 a->rozejdz_swiatlo(j, u, a->srodowisko[u][j]->swiatlo().get_moc(), a->srodowisko[u][j]->swiatlo().get_spadki(), a->srodowisko[u][j]->wysokosc(), 1, ktory_bufor);
                                                                                 else if(a->srodowisko[u][j]->swiatlo().get_rodzaj()==2)
                                                                                 a->rozejdz_swiatlo_reflektora(j, u, a->srodowisko[u][j]->swiatlo().get_moc(), 5,a->srodowisko[u][j]->swiatlo().get_spadki(), a->srodowisko[u][j]->wysokosc(),'p', 1, ktory_bufor);
                                                                        }
                                                               }
                                             }
                           }
                  }*/
}



void Plansza::res_osw_inn_pl()
{
         for(short h=0;h<21;++h) for(short g=0;g<13;++g) oswietlenie_z_innych_plansz[g][h]=253;
}

void Plansza::zamieszanie_ze_swiatlem(bool inne_tez, short ktory_bufor)
{
         Swiat*swiat=Objekt::swiat;
         if(inne_tez)
         {
                  res_osw_inn_pl();
                  if(swiat->zwroc_taka_plansze(x+1, y, z)) {swiat->zwroc_taka_plansze(x+1, y, z)->res_osw_inn_pl();}
                  if(swiat->zwroc_taka_plansze(x, y+1, z)) {swiat->zwroc_taka_plansze(x, y+1, z)->res_osw_inn_pl();}
                  if(swiat->zwroc_taka_plansze(x-1, y, z)) {swiat->zwroc_taka_plansze(x-1, y, z)->res_osw_inn_pl();}
                  if(swiat->zwroc_taka_plansze(x, y-1, z)){swiat->zwroc_taka_plansze(x, y-1, z)->res_osw_inn_pl();}
         }
         aktualizuj_swiatlo(0, 1);

         if(inne_tez)
         {
                  //if(x==1 && y==0)std::cout<<oswietlenie_z_innych_plansz[5][0]<<std::endl;
                  //if(x==1 && y==0)((Plansza*)Objekt::swiat->area[x+1][y][z])->oswietlenie_z_innych_plansz[5][0] = 1;
                  //if(x==1 && y==0)std::cout<<oswietlenie_z_innych_plansz[5][0]<<std::endl;
                  if(swiat->zwroc_taka_plansze(x+1, y, z)) {swiat->zwroc_taka_plansze(x+1, y, z)->aktualizuj_swiatlo(1, 1);}
                  if(swiat->zwroc_taka_plansze(x, y+1, z)) {swiat->zwroc_taka_plansze(x, y+1, z)->aktualizuj_swiatlo(1, 1);}
                  if(swiat->zwroc_taka_plansze(x-1, y, z)) {swiat->zwroc_taka_plansze(x-1, y, z)->aktualizuj_swiatlo(1, 1);}
                  if(swiat->zwroc_taka_plansze(x, y-1, z)){swiat->zwroc_taka_plansze(x, y-1, z)->aktualizuj_swiatlo(1, 1);}
                  //if(x==1 && y==0)std::cout<<oswietlenie_z_innych_plansz[5][0]<<std::endl;
                  aktualizuj_swiatlo(0, 1);
                  //if(x==1 && y==0)std::cout<<oswietlenie_z_innych_plansz[5][0]<<std::endl<<std::endl;
         }



         ///1 - wszystko, 2 - tylko obce plansze, 3 tylko nasza plansza
         /*Swiat*swiat=Objekt::swiat;
         if(inne_tez)
         {
                  res_osw_inn_pl();
                  if(swiat->zwroc_taka_plansze(x+1, y, z)) {swiat->zwroc_taka_plansze(x+1, y, z)->res_osw_inn_pl();}
                  if(swiat->zwroc_taka_plansze(x, y+1, z)) {swiat->zwroc_taka_plansze(x, y+1, z)->res_osw_inn_pl();}
                  if(swiat->zwroc_taka_plansze(x-1, y, z)) {swiat->zwroc_taka_plansze(x-1, y, z)->res_osw_inn_pl();}
                  if(swiat->zwroc_taka_plansze(x, y-1, z)){swiat->zwroc_taka_plansze(x, y-1, z)->res_osw_inn_pl();}
                  aktualizuj_swiatlo(ktory_bufor, 2);
         }
         if(!inne_tez) aktualizuj_swiatlo(ktory_bufor, 3);


         if(inne_tez)
         {


                  if(swiat->zwroc_taka_plansze(x+2, y, z)) {swiat->zwroc_taka_plansze(x+2, y, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x-2, y, z)) {swiat->zwroc_taka_plansze(x-2, y, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x, y+2, z)) {swiat->zwroc_taka_plansze(x, y+2, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x, y-2, z)) {swiat->zwroc_taka_plansze(x, y-2, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x+1, y+1, z)) {swiat->zwroc_taka_plansze(x+1, y+1, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x+1, y-1, z)) {swiat->zwroc_taka_plansze(x+1, y-1, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x-1, y+1, z)) {swiat->zwroc_taka_plansze(x-1, y+1, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x-1, y-1, z)) {swiat->zwroc_taka_plansze(x-1, y-1, z)->aktualizuj_swiatlo(1, 2);}

                  if(swiat->zwroc_taka_plansze(x+1, y, z)) {swiat->zwroc_taka_plansze(x+1, y, z)->aktualizuj_swiatlo(1, 2);}
                  if(swiat->zwroc_taka_plansze(x, y+1, z)) {swiat->zwroc_taka_plansze(x, y+1, z)->aktualizuj_swiatlo(2, 2);}
                  if(swiat->zwroc_taka_plansze(x-1, y, z)) {swiat->zwroc_taka_plansze(x-1, y, z)->aktualizuj_swiatlo(3, 2);}
                  if(swiat->zwroc_taka_plansze(x, y-1, z)){swiat->zwroc_taka_plansze(x, y-1, z)->aktualizuj_swiatlo(4, 2);}

                  aktualizuj_swiatlo(ktory_bufor, 3);

                  if(swiat->zwroc_taka_plansze(x+1, y, z)) {swiat->zwroc_taka_plansze(x+1, y, z)->aktualizuj_swiatlo(1, 3);}
                  if(swiat->zwroc_taka_plansze(x, y+1, z)) {swiat->zwroc_taka_plansze(x, y+1, z)->aktualizuj_swiatlo(2, 3);}
                  if(swiat->zwroc_taka_plansze(x-1, y, z)) {swiat->zwroc_taka_plansze(x-1, y, z)->aktualizuj_swiatlo(3, 3);}
                  if(swiat->zwroc_taka_plansze(x, y-1, z)){swiat->zwroc_taka_plansze(x, y-1, z)->aktualizuj_swiatlo(4, 3);}
         }*/
}

void Plansza::ta_plansza_juz_nie_celem(Plansza *a)
{
         for(short i=0;i<21;++i)
                  for(short j=0;j<13; ++j)
                           if(otoczenie[j][i] && otoczenie[j][i]->zywy && ((Objekt_zywy*)otoczenie[j][i])->ktora_plansza==this)
                                    ((Objekt_zywy*)otoczenie[j][i])->ktora_plansza = NULL;
}

Area* Swiat::zwroc_taka_aree(short x, short y, short z)
{
         if(x>-1 && x<w_x && y>-1 && y<w_y && z==0)
         {
                  return area[x][y][z];
         }
         return NULL;
         //std::cout<<"Nie ma takiej arey"; throw "D";
}

Plansza* Swiat::zwroc_taka_plansze(short x, short y, short z)
{
         if(x>-1 && x<w_x && y>-1 && y<w_y && z==0)
         {
                  return area[x][y][z]->jest_plansza ? (Plansza*)area[x][y][z] : NULL;
         }
         return NULL;
         //std::cout<<"Nie ma takiej arey"; throw "D";
}

Plansza* Swiat::zwroc_taka_plansze_TYLKO(short x, short y, short z)
{
         if(x>-1 && x<w_x && y>-1 && y<w_y && z==0 && area[x][y][z]->jest_plansza)
         {
                  return (Plansza*)area[x][y][z];
         }
         std::cout<<"Nie ma takiej planszy"<<x<<" "<<y<<" "<<z<<" "<<w_x<<" "<<w_y; throw "D";
}

Strefa* Swiat::zwroc_taka_strefe_TYLKO(short x, short y, short z)
{
         if(x>-1 && x<w_x && y>-1 && y<w_y && z==0 && area[x][y][z]->jest_plansza==false)
         {
                  return (Strefa*)area[x][y][z];
         }
         std::cout<<"Nie ma takiej strefy"<<x<<" "<<y<<" "<<z<<" "; throw "D";
}

void Swiat::stworz_plansze(short x, short y, short z)
{
         Area *h = zwroc_taka_aree(x, y, z);
         if(h && h->jest_plansza==false)
         {
                  area[x][y][z] = new Plansza((Strefa*)h);
                  delete h;
         }
}

void Swiat::stworz_strefe(short x, short y, short z)
{
         Area *h = zwroc_taka_aree(x, y, z);
         if(h && h->jest_plansza)
         {
                  for(short int i=x-2; i<=x+2; ++i)
                           for(short int j=y-2; j<=y+2; ++j)
                                    if(zwroc_taka_plansze(i, j, z))
                                             zwroc_taka_plansze(i, j, z)->ta_plansza_juz_nie_celem((Plansza*)h);

                  area[x][y][z] = new Strefa((Plansza*)h);
                  wysypisko_plansz.push_back((Plansza*)h);
         }
}

void Swiat::jak_tam_wysypisko_plansz()
{
         for(std::list<Plansza*>::iterator i=wysypisko_plansz.begin(); i!=wysypisko_plansz.end();++i)
         {
                  if((*i)->x<a_x-1 || (*i)->x>a_x+1 || (*i)->y<a_y-1 || (*i)->y>a_y+1)
                  {
                           delete *(i);
                           i = wysypisko_plansz.erase(i);
                  }
         }
}


void Plansza::zaktualizuj_widoki(int x1,int y1, int x2, int y2, bool akt_widoki)///pola na ktorych byl ruch
{
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"#";

         if(Objekt::swiat->aktualny && x==Objekt::swiat->aktualny->px && y==Objekt::swiat->aktualny->py && z==Objekt::swiat->aktualny->pz)
         {
                  Objekt::args->pp=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('p');
                  Objekt::args->ll=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('l');
                  Objekt::args->dd=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('d');
                  Objekt::args->gg=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('g');
         }

         if(Objekt::args->melduj_co_robi_AI) std::cout<<"^";
         zamieszanie_ze_swiatlem(true, 0);

         if(Objekt::args->melduj_co_robi_AI) std::cout<<"@";

         Objekt *a;
         for(int i=0; i<21; i++)
         {
                  for(int j=0; j<13;j++)
                  {
                           a = otoczenie[j][i];
                           if(a!=NULL && a->zywy && !(a->zwrot=='p' && a->x>x1 && a->x>x2) && !(a->zwrot=='l' && a->x<x1 && a->x<x2)
                              && !(a->zwrot=='d' && a->y>y1 && a->y>y2) && !(a->zwrot=='g' && a->y<y1 && a->y<y2))
                              {
                                       a->patrz();
                              }

                  }
         }
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"!";
}

void Plansza::zaktualizuj_widoki(bool akt_widoki)
{
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"#";

         if(Objekt::swiat->aktualny && x==Objekt::swiat->aktualny->px && y==Objekt::swiat->aktualny->py && z==Objekt::swiat->aktualny->pz)
         {
                  Objekt::args->pp=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('p');
                  Objekt::args->ll=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('l');
                  Objekt::args->dd=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('d');
                  Objekt::args->gg=Objekt::swiat->aktualny->gracz_widzi_do_konca_w_strone('g');
         }

         if(Objekt::args->melduj_co_robi_AI) std::cout<<"^";
         zamieszanie_ze_swiatlem(true, 0);
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"@";

         for(int i=0; i<21; i++)
         {
                  for(int j=0; j<13;j++)
                  {
                           if(otoczenie[j][i]!=NULL && otoczenie[j][i]->zywy) otoczenie[j][i]->patrz();
                  }
         }
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"!";
}

Plansza :: Plansza (int x, int y, int z) : Area(x, y, z)
{
         jest_plansza=true;
         for(int i=0; i<13; i++)
         {
                  for(int j=0; j<21; j++)
                  {
                           oswietlenie[i][j]=0;
                           otoczenie[i][j] = NULL;
                           srodowisko[i][j] = NULL;
                           ziemia[i][j] = NULL;
                  }
         }



}
#include <windows.h>
void Plansza::Runda ()
{//std::cout<<"Plansza zaczela";
         zaktualizuj_widoki();
         dziej_ogien();
         zaktualizuj_widoki();


         powstan_mozliwych();

         Objekt*a=NULL; Srodowisko*s;
         bool miala_gracza;
         if(!(*Objekt::args->godmode))
         {
                if(ma_gracza) Objekt::swiat->Ustaw_aktualna(x,y,z); miala_gracza=ma_gracza;
                ma_gracza=Objekt::swiat->ma_gracza_niespiacego(this);
         }
         for(int i=0; i<21; i++)
         {
                  for(int j=0; j<13; j++)
                  {
                           if(otoczenie[j][i]!=NULL && otoczenie[j][i]->wykonuje_ruch && otoczenie[j][i]->nie_wykonal_ruchu)
                           {
                                    a=otoczenie[j][i];
                                    if(Objekt::args->melduj_co_robi_AI)
                                    {
                                    if(a->czym_jest==8||a->czym_jest==9) std::cout<<a->czym_jest<<" "<<((Objekt_zywy*)a)->jest_ofiara<<" "<<((Objekt_zywy*)a)->jest_cel<<" "<<((Objekt_zywy*)a)->celem_jest_plansza<<" "<<((Objekt_zywy*)a)->xc<<" "<<((Objekt_zywy*)a)->yc;
                                    else if(a->czym_jest == 2) std::cout<<a->czym_jest<<" "<<((Objekt_zywy*)a)->jest_ofiara<<" "<<((Objekt_zywy*)a)->jest_cel<<" "<<((Objekt_zywy*)a)->celem_jest_plansza<<" "<<((Zombie*)a)->wlasnie_przeszukuje<<" "<<((Objekt_zywy*)a)->xc<<" "<<((Objekt_zywy*)a)->yc;
                                    }
                                    a->nie_wykonal_ruchu=false;
                                    a->rusz_sie();
                                    if(Objekt::args->melduj_co_robi_AI)
                                    std::cout<<"  +"<<'\n';
                           }
                           if(srodowisko[j][i]!=NULL && srodowisko[j][i]->wykonuje_ruch())
                           {
                                    srodowisko[j][i]->Runda(i, j, this);
                           }
                  }
         }



         for(int i=0; i<21; i++){for(int j=0; j<13; j++){if(otoczenie[j][i]!=NULL){otoczenie[j][i]->nie_wykonal_ruchu=true;}}}
         if(!(*Objekt::args->godmode))ma_gracza=miala_gracza;
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"Plsa";
}

Plansza::~Plansza()
{
         delete floors;
         for(int i=0;i<21;i++)
         {
                  for(int j=0;j<13;j++)
                  {
                           if(otoczenie[j][i]!=NULL) {delete otoczenie[j][i];otoczenie[j][i]=NULL;}
                           if(srodowisko[j][i]!=NULL) {delete srodowisko[j][i];srodowisko[j][i]=NULL;}
                           //if(ziemia[j][i]!=NULL) {delete ziemia[j][i];ziemia[j][i]=NULL;}
                  }
         }
         zdeletuj_juz_martwych();
}

void Plansza::rzuc_na_ziemie(int xx, int yy, Item*aa)
{
         if(xx<0 || xx>20 || yy<0 || yy>12) return;
         if(ziemia[yy][xx]==NULL) ziemia[yy][xx]=new Kontener<Item>();
         ziemia[yy][xx]->dodaj_obiekt(aa);
}

void Plansza::rzuc_na_ziemie(int xx, int yy, Kontener<Item> *aa)
{
         if(xx<0 || xx>20 || yy<0 || yy>12) return;
         if(ziemia[yy][xx]==NULL) ziemia[yy][xx]=new Kontener<Item>();
         ziemia[yy][xx]->dodaj_obiekty(aa);
         aa->wywal_wszystkie_objekty();
         if(ziemia[yy][xx]->ilosc==0)
         {
                  Kontener<Item> *d = ziemia[yy][xx]; ziemia[yy][xx] = NULL; delete d;
         }
}

void Plansza::dodaj_do_srodowiska(int xx, int yy, Objekt*a)
{
         if(xx<0 || xx>20 || yy<0 || yy>12) return;
         if(srodowisko[yy][xx]==NULL) srodowisko[yy][xx]=new Srodowisko();
         srodowisko[yy][xx]->dodaj_objekt(a,xx,yy);
}

void Plansza::usun_ziemie()
{
         for(int i=0;i<21;i++)
         {
                  for(int j=0;j<13;j++)
                  {if(ziemia[j][i]!=NULL) {delete ziemia[j][i];ziemia[j][i]=NULL;}}
         }
}

bool Area::to_jest_na_podlodze(int x, int y)
{
         if(x<0 || x>20 || y<0 || y>12) return false;
         Kontener<podloga> *p = floors;
         for(int i=0; i<p->ilosc; ++i)
         {
                  short wiekszy = p->obiekt[i]->a.y >= p->obiekt[i]->b.y ? p->obiekt[i]->a.y : p->obiekt[i]->b.y;
                  short mniejszy = p->obiekt[i]->a.y >= p->obiekt[i]->b.y ? p->obiekt[i]->b.y : p->obiekt[i]->a.y;
                  if(x>=p->obiekt[i]->a.x && x<=p->obiekt[i]->b.x && y>=mniejszy && y<=wiekszy-1)
                           return true;
         }
         return false;
}

bool Strefa::srodowisko_ma_to(int co, int x, int y)
{
         if(srodowisko[y][x]==NULL) return false;
         for(short i=0; i<srodowisko[y][x]->zawartosc->ilosc; ++i) if(srodowisko[y][x]->zawartosc->obiekt[i]->czym_jest==co) return true;
         return false;
}

void Strefa::srodowisko_wrzuc(Objekt_przejsciowy *a, int x, int y)
{
         if(srodowisko[y][x]==NULL) srodowisko[y][x]=new Srodowisko_przejsciowe;
         srodowisko[y][x]->zawartosc->dodaj_obiekt(a);
}

bool Strefa::nie_blokuje_drzwi(short x, short y)
{
         return !((w_planszy(x+1, y) && otoczenie[y][x+1] && otoczenie[y][x+1]->czym_jest==27)||(w_planszy(x-1, y) && otoczenie[y][x-1] && otoczenie[y][x-1]->czym_jest==27)
                  ||(w_planszy(x, y-1) && otoczenie[y-1][x] && otoczenie[y-1][x]->czym_jest==27)||(w_planszy(x, y+1) && otoczenie[y+1][x] && otoczenie[y+1][x]->czym_jest==27));
}

template<typename T>
void Strefa::postaw_pare_obiektow_na_srodowisku(int ilosc, bool moze_byc_na_podlodze)
{
         for(int i=0;i<ilosc;i++)
         {
                  bool kon=false;
                  int xx=losuj(0,20), yy=losuj(0,12);//std::cout<<x<<" "<<y<<std::endl

                  for(int b=xx;b<21;++b) {if(otoczenie[yy][b]==NULL && srodowisko[yy][b]==NULL &&  (moze_byc_na_podlodze || !to_jest_na_podlodze(b, yy))) {srodowisko_wrzuc(new T(), b, yy);kon=true;break;}}if(kon)continue;
                  for(int v=yy+1;v<13;++v){for(int b=0;b<21;++b) {if(otoczenie[v][b]==NULL && srodowisko[v][b]==NULL && (moze_byc_na_podlodze || !to_jest_na_podlodze(b, v))) {srodowisko_wrzuc(new T(), b,v);kon=true;break;}}if(kon)break;}if(kon)continue;
                  for(int v=0;v<yy;++v){for(int b=0;b<21;++b) {if(otoczenie[v][b]==NULL && srodowisko[v][b]==NULL &&  (moze_byc_na_podlodze || !to_jest_na_podlodze(b, v))) {srodowisko_wrzuc(new T(), b, v);kon=true;break;}}if(kon)break;}if(kon)continue;
                  for(int b=0;b<xx;++b) {if(otoczenie[yy][b]==NULL && srodowisko[yy][b]==NULL &&  (moze_byc_na_podlodze || !to_jest_na_podlodze(b, yy))) {srodowisko_wrzuc(new T(), b, yy);;kon=true;break;}}if(kon)continue;
                  break;
         }
}

template<typename T>
void Strefa::postaw_pare_obiektow(T*obiekt, int ilosc_obiektow, bool moze_byc_na_podlodze)
{
         delete obiekt;
         for(int i=0;i<ilosc_obiektow;i++)
         {
                  bool kon=false;
                  int xx=losuj(0,20), yy=losuj(0,12);//std::cout<<x<<" "<<y<<std::endl


                  for(int b=xx;b<21;++b) {if(nie_blokuje_drzwi(b, yy) && otoczenie[yy][b]==NULL &&  (moze_byc_na_podlodze || !to_jest_na_podlodze(b, yy))) {otoczenie[yy][b]=new T();kon=true;break;}}if(kon)continue;
                  for(int v=yy+1;v<13;++v){for(int b=0;b<21;++b) {if(nie_blokuje_drzwi(b, v) && otoczenie[v][b]==NULL && (moze_byc_na_podlodze || !to_jest_na_podlodze(b, v))) {otoczenie[v][b]=new T();kon=true;break;}}if(kon)break;}if(kon)continue;
                  for(int v=0;v<yy;++v){for(int b=0;b<21;++b) {if(nie_blokuje_drzwi(b,v) && otoczenie[v][b]==NULL &&  (moze_byc_na_podlodze || !to_jest_na_podlodze(b, v))) {otoczenie[v][b]=new T();kon=true;break;}}if(kon)break;}if(kon)continue;
                  for(int b=0;b<xx;++b) {if(nie_blokuje_drzwi(b, yy) && otoczenie[yy][b]==NULL &&  (moze_byc_na_podlodze || !to_jest_na_podlodze(b, yy))) {otoczenie[yy][b]=new T();kon=true;break;}}if(kon)continue;
                  break;
         }
}

Strefa::Strefa(int x, int y, int z):Area(x, y, z)
{
         jest_plansza=false;
         for(int i=0; i<13; i++)
         {
                  for(int j=0; j<21; j++)
                  {
                           otoczenie[i][j] = NULL;
                           srodowisko[i][j] = NULL;
                           ziemia[i][j] = NULL;
                  }
         }

         if(losuj(1,3)==1) generuj_pseudo_miasto();
         else generuj_las();
         //generuj_probe();
}

Strefa::~Strefa()
{
         delete floors;
         for(int i=0;i<21;i++)
         {
                  for(int j=0;j<13;j++)
                  {
                           if(otoczenie[j][i]!=NULL) {delete otoczenie[j][i];otoczenie[j][i]=NULL;}
                           if(srodowisko[j][i]!=NULL) {delete srodowisko[j][i];srodowisko[j][i]=NULL;}
                           //if(ziemia[j][i]!=NULL) {delete ziemia[j][i];ziemia[j][i]=NULL;}
                  }
         }
}

void Strefa::usun_ziemie()
{
         for(int i=0;i<21;i++)
         {
                  for(int j=0;j<13;j++)
                  {if(ziemia[j][i]!=NULL) {delete ziemia[j][i];ziemia[j][i]=NULL;}}
         }
}

void Strefa::generuj_probe()
{
         biom = 0;
         stworz_budynek(0);
         postaw_pare_obiektow(new WLampa_przejsciowa, 10, true);
}

void Strefa::generuj_las()
{
         biom = 0;
         if(true)//losuj(1,25)<10)
         {
                  int xx, yy;
                  while (true)
                  {
                           xx=losuj(0,20), yy=losuj(0,12); if(otoczenie[yy][xx]==NULL) {break;}
                  }
                  otoczenie[yy][xx]=new Woda_przejsciowa();//otoczenie[yy][xx]->px=x;otoczenie[yy][xx]->py=y; otoczenie[yy][xx]->pz=z;
                  //otoczenie[yy][xx]->x=xx; otoczenie[yy][xx]->y=yy;
                  struct punct*c=new struct punct[101];c[0].a=yy;c[0].b=xx;int n=1,s=0,k=1;
                  while(true)
                  {
                           if(s==k) break;
                           for(int y=s;y<k;y++)
                           {
                                    if(losuj(0,3)==0) continue;
                                    int szansa=4;

                                    bool lewo=true,prawo=true,dol=true,gora=true;
                                    for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b+1 && c[u].a==c[y].a){prawo=false;break;}}
                                    for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b-1 && c[u].a==c[y].a){lewo=false;break;}}
                                    for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a-1){gora=false;break;}}
                                    for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a+1){dol=false;break;}}
                                    int f=losuj(0,3);
                                    for(int h=0;h<4;h++)
                                    {
                                             bool udalo=true;
                                             switch(f)
                                             {
                                                      case 0: if (prawo && losuj(1,10)<=szansa && c[y].b+1<21 && otoczenie[c[y].a][c[y].b+1]==NULL) {c[n].a=c[y].a; c[n].b=c[y].b+1;++f;}else {++szansa;++f;udalo=false;}break;
                                                      case 1:  if (lewo && losuj(1,10)<=szansa && c[y].b-1>-1 && otoczenie[c[y].a][c[y].b-1]==NULL) {c[n].a=c[y].a; c[n].b=c[y].b-1;++f;}else {++szansa;++f;udalo=false;}break;
                                                      case 2: if (gora && losuj(1,10)<=szansa && c[y].a-1>-1 && otoczenie[c[y].a-1][c[y].b]==NULL) {c[n].a=c[y].a-1; c[n].b=c[y].b;++f;}else {++szansa;++f;udalo=false;}break;
                                                      case 3: if (dol && losuj(1,10)<=szansa && c[y].a+1<13 && otoczenie[c[y].a+1][c[y].b]==NULL) {c[n].a=c[y].a+1; c[n].b=c[y].b;f=0;}else {++szansa;f=0;udalo=false;}break;
                                             }
                                             if(!udalo) continue;

                                             if(c[n].a<13 && c[n].a>-1 && c[n].b<21 && c[n].b>-1)
                                             {
                                                      Woda_przejsciowa *w=new Woda_przejsciowa();otoczenie[c[n].a][c[n].b]=w;
                                             }

                                             n++;if(n==98) break;
                                    }
                                    if(n==98) break;
                           }
                           if(n==98) break;s=k;k=n;
                  }
         }

         if(losuj(0,1)) stworz_budynek(0);
         else postaw_pare_obiektow(new Drzewo_przejsciowe, losuj(0, 20));

         postaw_pare_obiektow(new Drzewo_przejsciowe, losuj(0, 20));
         postaw_pare_obiektow(new Beczka_przejsciowa, 1);
         postaw_pare_obiektow(new Schowek_przejsciowy, 1);

         if(x!=1 || y!=0)
         {postaw_pare_obiektow(new Zombie_przejsciowe, losuj(0, 6));
         if(losuj(1,5)==1)postaw_pare_obiektow(new Zombie_przejsciowe, losuj(0, 15));
         postaw_pare_obiektow(new Sarna_przejsciowa, losuj(0, 1));
         if(losuj(1,4)==1)postaw_pare_obiektow(new Niedzwiedz_przejsciowy, losuj(0, 1));
         if(losuj(1,4)==1)postaw_pare_obiektow(new Niedzwiedz_przejsciowy, losuj(0, 3));
         }

         if(losuj(0,1)) postaw_pare_obiektow_na_srodowisku<Lampa_przejsciowa>(losuj(0,2), true);

         postaw_pare_obiektow_na_srodowisku<Trawa_przejsciowa>(losuj(4,14), false);
         postaw_pare_obiektow_na_srodowisku<Zlamana_galaz_przejsciowa>(losuj(0,3), false);

         //postaw_pare_obiektow(new Zombie_przejsciowe,3);//////////////////////////
                  //postaw_pare_obiektow(new Sarna_przejsciowa,11);
                  //postaw_pare_obiektow(new Niedzwiedz_przejsciowy,4);

}

void Strefa::generuj_pseudo_miasto()
{
         biom = 1;

         if(losuj(0,1)) stworz_budynek(1);

         if(losuj(0,1)) postaw_pare_obiektow_na_srodowisku<Lampa_przejsciowa>(losuj(0,2), true);
         if(losuj(0,1)) postaw_pare_obiektow_na_srodowisku<Reflektor_przejsciowy>(losuj(0,2), true);

         postaw_pare_obiektow(new Beczka_przejsciowa, 1);
         if(losuj(0,1)) postaw_pare_obiektow(new Beczka_przejsciowa, 1);

         postaw_pare_obiektow(new Staly_przejsciowy, losuj(3, 8));

         postaw_pare_obiektow(new Zombie_przejsciowe, losuj(0, 6)); postaw_pare_obiektow(new Schowek_przejsciowy, losuj(0, 2));
         //postaw_pare_obiektow(new Zombie_przejsciowe, losuj(0, 6));
         postaw_pare_obiektow(new Schowek_przejsciowy, losuj(0, 2));
         postaw_pare_obiektow(new Zombie_przejsciowe, losuj(0, 6)); postaw_pare_obiektow(new Schowek_przejsciowy, losuj(0, 2));

}

void Strefa::stworz_budynek(short ktory)
{
         short typ = losuj(1, 10);
         //typ = typ <= 6 ? 1 : typ - 5; na razie tylko typ 1
         typ = 1;
         int wymiar_x = losuj(4, 19), wymiar_y = losuj(4, 11);
         punkt_na_planszy a;
         //if(x==1 && y==0) std::cout<<wymiar_x<<" "<<wymiar_y;

         if(typ == 1)

         {
                  while((a=czy_da_sie_taki_postawic(wymiar_x, wymiar_y)).x == 0)
                  {
                           if(--wymiar_x<4 || --wymiar_y<4)
                                    return;
                  }
                  floors->dodaj_obiekt(new podloga(a, punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y), ktory));

                  for(int i=a.x; i<a.x+wymiar_x; ++i)
                  {
                           if(otoczenie[a.y][i]==NULL)
                                    otoczenie[a.y][i] = new Sciana_przejsciowa(ktory);
                           if(otoczenie[a.y+wymiar_y-1][i]==NULL)
                                    otoczenie[a.y+wymiar_y-1][i] = new Sciana_przejsciowa(ktory);
                  }
                  for(int j=a.y; j<a.y+wymiar_y; ++j)
                  {
                           if(otoczenie[j][a.x]==NULL)
                                    otoczenie[j][a.x] = new Sciana_przejsciowa(ktory);
                           if(otoczenie[j][a.x+wymiar_x-1]==NULL)
                                    otoczenie[j][a.x+wymiar_x-1] = new Sciana_przejsciowa(ktory);
                  }

                  zrob_pokoj(ktory, a, punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1),8);// losuj(1,10) < 8 ? 4 : 6);

                  for(short yy=0; yy<losuj(1,3); ++yy)
                  {
                           int los = losuj(1,4);
                           bool aaa = false;
                           while(true)
                           {
                                    switch(los)
                                    {
                                             case 1: if(postaw_drzwi_na_odcinku(ktory, a, punkt_na_planszy(a.x+wymiar_x-1, a.y), true)){aaa=true;break;}
                                             case 2: if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, a.y+wymiar_y-1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1), true)){aaa=true;break;}
                                             case 3: if(postaw_drzwi_na_odcinku(ktory, a, punkt_na_planszy(a.x, a.y+wymiar_y-1), true)){aaa=true;break;}
                                             case 4: if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x+wymiar_x-1, a.y), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1), true)){aaa=true;break;}
                                    }
                                    if(aaa) break;
                                    aaa=true; los = 1;
                           }
                  }

                  short h = losuj(5,12);
                  postaw_okna_na_odcinku(a, punkt_na_planszy(a.x+wymiar_x-1, a.y), true, h, true);
                  postaw_okna_na_odcinku(punkt_na_planszy(a.x, a.y+wymiar_y-1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1), false, h, false);
                  postaw_okna_na_odcinku(a, punkt_na_planszy(a.x, a.y+wymiar_y-1), true, h, true);
                  postaw_okna_na_odcinku(punkt_na_planszy(a.x+wymiar_x-1, a.y), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1), false, h, false);

                  short pole = wymiar_x*wymiar_y;

                  if(true || ktory==0)
                  {
                  rozstaw_losowo_obiekty<Krzeslo_przejsciowe>(losuj(0,pole/20),punkt_na_planszy(a.x+1,a.y+1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1));
                  rozstaw_losowo_obiekty<Szafa_przejsciowa>(losuj(0, pole/25),punkt_na_planszy(a.x+1,a.y+1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1));
                  rozstaw_losowo_obiekty<Lozko_przejsciowe>(losuj(0, 1),punkt_na_planszy(a.x+1,a.y+1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1));
                  rozstaw_losowo_obiekty<WLampa_przejsciowa>(losuj(0, 2),punkt_na_planszy(a.x+1,a.y+1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1));
                  }


                  rozstaw_losowo_obiekty<Stol_przejsciowy>(losuj(0, pole/30),punkt_na_planszy(a.x+1,a.y+1), punkt_na_planszy(a.x+wymiar_x-1, a.y+wymiar_y-1));
         }
}

template<typename co>
void Strefa::rozstaw_losowo_obiekty(short ile, punkt_na_planszy a, punkt_na_planszy b)
{
         if(!w_planszy(a.x,a.y)||!w_planszy(b.x, b.y)) {std::cout<<"rozstaw losowo obiekty"; throw "F";}
         short t; bool przewinal; short xx, yy;
         for(short i=0; i<ile; ++i)
         {
                  dadavfava:
                  if(i>=ile) return;
                  t = losuj(0, abs(a.x-b.x+1)*abs(a.y-b.y+1)-1);
                  przewinal = false;
                  xx = a.x+(t%abs(a.x-b.x+1)); yy = a.y+t/abs(a.x-b.x+1);
                  while(true)
                  {
                           for(; yy<=b.y; ++yy)
                           {
                                    if(xx==b.x+1) xx = a.x;
                                    for(; xx<=b.x; ++xx)
                                    {
                                             if(!otoczenie[yy][xx])
                                             {
                                                      otoczenie[yy][xx] = new co();
                                                      ++i;
                                                      goto dadavfava;
                                             }
                                    }
                           }
                           if(przewinal) return;
                           przewinal = true;
                           xx = a.x; yy = a.y;
                  }
         }
}

void Strefa::postaw_okna_na_odcinku(punkt_na_planszy a, punkt_na_planszy b, bool prawo_dol, short min_odstep, bool budynek_jest_p_d)
{
         if(a.y == b.y)
         {
                  short m = a.x >= b.x ? b.x : a.x;
                  short w = a.x >= b.x ? a.x : b.x;
                  short i = 0, naj_od_lewej = w + min_odstep + 1, ile_juz_odl = min_odstep;
                  short odl_innych_z_lewej = min_odstep , odl_innych_z_prawej = min_odstep; ///dodatnie odleglosci od krancow odcinka

                  for(int k=1; k<min_odstep; ++k)
                  {
                           if(!budynek_jest_p_d)
                           {
                                    if(!to_jest_na_podlodze(m, a.y-k) || w_planszy(m, a.y-k)) break;
                                    if(otoczenie[a.y-k][m]!=NULL && otoczenie[a.y-k][m]->czym_jest==26)
                                    {odl_innych_z_lewej = k-1;
                                             break;}
                           }
                           else
                           {
                                    if(!to_jest_na_podlodze(m, a.y+k) || w_planszy(m, a.y+k)) break;
                                    if(otoczenie[a.y+k][m]!=NULL && otoczenie[a.y+k][m]->czym_jest==26)
                                    {odl_innych_z_lewej = k-1;
                                             break;}
                           }
                  }
                  for(int k=1; k<min_odstep; ++k)
                  {
                           if(!budynek_jest_p_d)
                           {
                                    if(!to_jest_na_podlodze(w, a.y-k) || w_planszy(w, a.y-k)) break;
                                    if(otoczenie[a.y-k][w]!=NULL && otoczenie[a.y-k][w]->czym_jest==26)
                                    {odl_innych_z_prawej = k-1;
                                             break;}
                           }
                           else
                           {
                                    if(!to_jest_na_podlodze(w, a.y+k) || w_planszy(w, a.y+k)) break;
                                    else if(otoczenie[a.y+k][w]!=NULL && otoczenie[a.y+k][w]->czym_jest==26)
                                    {odl_innych_z_prawej = k-1;
                                             break;}
                           }
                  }

                  int h = losuj(m, w);
                  ile_juz_odl = odl_innych_z_lewej + h - m;
                  for(int k = h; true; ++k)
                  {
                           ++ile_juz_odl;
                           if(++i == w-m+2) return;
                           if(k == w+1)
                           {
                                    k = m;
                                    ile_juz_odl = odl_innych_z_lewej;
                           }
                           if(otoczenie[a.y][k] != NULL && otoczenie[a.y][k]->czym_jest ==26)
                           {
                                    ile_juz_odl = -1;
                                    continue;
                           }
                           if(k>=naj_od_lewej-min_odstep && k<=naj_od_lewej)///to oznacza ze przeszlismy calosc
                           {
                                    return;
                           }

                           if(ile_juz_odl >= min_odstep && w-k+odl_innych_z_prawej>min_odstep &&
                              (!w_planszy(k, a.y+1) || otoczenie[a.y+1][k]==NULL) && (!w_planszy(k, a.y-1) || otoczenie[a.y-1][k]==NULL)
                               && (!w_planszy(k+1, a.y) || otoczenie[a.y][k+1]==NULL || otoczenie[a.y][k+1]->czym_jest!=27)
                               && (!w_planszy(k-1, a.y) || otoczenie[a.y][k-1]==NULL || otoczenie[a.y][k-1]->czym_jest!=27)
                              && (otoczenie[a.y][k]==NULL || otoczenie[a.y][k]->czym_jest==28))
                           {
                                    ile_juz_odl = -1;
                                    if(naj_od_lewej == w + min_odstep + 1)
                                             naj_od_lewej = k;
                                    delete otoczenie[a.y][k];
                                    otoczenie[a.y][k] = new Okno_przejsciowe(prawo_dol ? 'd' : 'g');
                           }
                  }





         }
         else if(a.x == b.x)
         {
                  short m = a.y >= b.y ? b.y : a.y;
                  short w = a.y >= b.y ? a.y : b.y;
                  short i = 0, naj_od_gory = w + min_odstep + 1, ile_juz_odl = min_odstep;
                  short odl_innych_z_gory = min_odstep , odl_innych_z_dolu = min_odstep; ///dodatnie odleglosci od krancow odcinka

                  for(int k=1; k<min_odstep; ++k)
                  {
                           if(!budynek_jest_p_d)
                           {
                                    if(!to_jest_na_podlodze(a.x-k, m) || w_planszy(a.x-k, m)) break;
                                    if(otoczenie[m][a.x-k]!=NULL && otoczenie[m][a.x-k]->czym_jest==26)
                                    {odl_innych_z_gory = k-1;
                                             break;}
                           }
                           else
                           {
                                    if(!to_jest_na_podlodze(a.x+k, m) || w_planszy(a.x+k, m)) break;
                                    if(otoczenie[m][a.x+k]!=NULL && otoczenie[m][a.x+k]->czym_jest==26)
                                    {odl_innych_z_gory = k-1;
                                             break;}
                           }
                  }
                  for(int k=1; k<min_odstep; ++k)
                  {
                           if(!budynek_jest_p_d)
                           {
                                    if(!to_jest_na_podlodze(a.x-k, w) || w_planszy(a.x-k, w)) break;
                                    if(otoczenie[w][a.x-k]!=NULL && otoczenie[w][a.x-k]->czym_jest==26)
                                    {odl_innych_z_dolu = k-1;
                                             break;}
                           }
                           else
                           {
                                    if(!to_jest_na_podlodze(a.x+k, w) || w_planszy(a.x+k, w)) break;
                                    else if(otoczenie[w][a.x+k]!=NULL && otoczenie[w][a.x+k]->czym_jest==26)
                                    {odl_innych_z_dolu = k-1;
                                             break;}
                           }
                  }

                  int h = losuj(m, w);
                  ile_juz_odl = odl_innych_z_gory + h - m;
                  for(int k = h; true; ++k)
                  {
                           ++ile_juz_odl;
                           if(++i == w-m+2) return;
                           if(k == w+1)
                           {
                                    k = m;
                                    ile_juz_odl = odl_innych_z_gory;
                           }
                           if(otoczenie[k][a.x] != NULL && otoczenie[k][a.x]->czym_jest ==26)
                           {
                                    ile_juz_odl = -1;
                                    continue;
                           }
                           if(k>=naj_od_gory-min_odstep && k<=naj_od_gory)///to oznacza ze przeszlismy calosc
                           {
                                    return;
                           }

                           if(ile_juz_odl >= min_odstep && w-k+odl_innych_z_dolu>min_odstep &&
                              (!w_planszy(a.x+1, k) || otoczenie[k][a.x+1]==NULL) && (!w_planszy(a.x-1, k) || otoczenie[k][a.x-1]==NULL)
                               && (!w_planszy(a.x, k+1) || otoczenie[k+1][a.x]==NULL || otoczenie[k+1][a.x]->czym_jest!=27)
                               && (!w_planszy(a.x, k-1) || otoczenie[k-1][a.x]==NULL || otoczenie[k-1][a.x]->czym_jest!=27)
                              && (otoczenie[k][a.x]==NULL || otoczenie[k][a.x]->czym_jest==28))
                           {
                                    ile_juz_odl = -1;
                                    if(naj_od_gory == w + min_odstep + 1)
                                             naj_od_gory = k;
                                    delete otoczenie[k][a.x];
                                    otoczenie[k][a.x] = new Okno_przejsciowe(prawo_dol ? 'p' : 'l');
                           }
                  }
         }
}

bool Strefa::postaw_drzwi_na_odcinku(short ktore, punkt_na_planszy a, punkt_na_planszy b, bool bezwzglednie)
{
         if(a.y == b.y)
         {
                  short m = a.x >= b.x ? b.x : a.x;
                  short w = a.x >= b.x ? a.x : b.x;
                  short i = 0;

                  for(int k = losuj(m, w); true; ++k)
                  {
                           if(++i == w-m+4)
                                    return false;
                           if(k == w+1) k = m;
                           if((!w_planszy(k, a.y+1) || otoczenie[a.y+1][k]==NULL) && (!w_planszy(k, a.y-1) || otoczenie[a.y-1][k]==NULL)
                               && (!w_planszy(k+1, a.y) || otoczenie[a.y][k+1]==NULL || otoczenie[a.y][k+1]->czym_jest!=27)
                               && (!w_planszy(k-1, a.y) || otoczenie[a.y][k-1]==NULL || otoczenie[a.y][k-1]->czym_jest!=27))
                           {
                                    delete otoczenie[a.y][k];
                                    otoczenie[a.y][k] = NULL;
                                   if(bezwzglednie || ((w-m>2) && (!w_planszy(k+1, a.y-1) || otoczenie[a.y-1][k+1]==NULL || !w_planszy(k-1, a.y-1) || otoczenie[a.y-1][k-1]==NULL)
                                              && (!w_planszy(k+1, a.y+1) || otoczenie[a.y+1][k+1]==NULL || !w_planszy(k-1, a.y+1) || otoczenie[a.y+1][k-1]==NULL)))
                                    otoczenie[a.y][k] = new Drzwi_przejsciowe(ktore);

                                    return true;
                           }

                  }
         }
         else if(a.x == b.x)
         {
                  short m = a.y >= b.y ? b.y : a.y;
                  short w = a.y >= b.y ? a.y : b.y;
                  short i = 0;

                  for(int k = losuj(m, w); true; ++k)
                  {
                           if(++i == w-m+4) return false;
                           if(k == w+1) k = m;
                           if((!w_planszy(a.x+1, k) || otoczenie[k][a.x+1]==NULL) && (!w_planszy(a.x-1, k) || otoczenie[k][a.x-1]==NULL)
                               && (!w_planszy(a.x, k+1) || otoczenie[k+1][a.x]==NULL || otoczenie[k+1][a.x]->czym_jest!=27)
                               && (!w_planszy(a.x, k-1) || otoczenie[k-1][a.x]==NULL || otoczenie[k-1][a.x]->czym_jest!=27))
                           {
                                    delete otoczenie[k][a.x];
                                    otoczenie[k][a.x] = NULL;
                                    if(bezwzglednie || ((w-m>2) && (!w_planszy(a.x-1, k+1) || otoczenie[k+1][a.x-1]==NULL || !w_planszy(a.x-1, k-1) || otoczenie[k-1][a.x-1]==NULL)
                                              && (!w_planszy(a.x+1, k+1) || otoczenie[k+1][a.x+1]==NULL || !w_planszy(a.x+1, k-1) || otoczenie[k-1][a.x+1]==NULL)))
                                    otoczenie[k][a.x] = new Drzwi_przejsciowe(ktore);
                                    return true;
                           }

                  }
         }
         return false;


         ///moga ja zaklucac elementy z zewnatrz
         ///nie obok drzwi
         ///nie obok okien
         ///nie w sciane


}

void Strefa::zrob_pokoj(short ktory, punkt_na_planszy a, punkt_na_planszy b, short r)
{
         if(a.x>b.x)
         {
                  punkt_na_planszy c = a; a = b; b = c;
         }
         int wiek = a.y >= b.y ? a.y : b.y;
         int mniej = a.y >= b.y ? b.y : a.y;
         short rozmiar = 4; ///parzysta!
         rozmiar = r;
         if(rozmiar%2 != 0) rozmiar += 1;

         switch(losuj(0, 1))
         {
                  case 0:
                  {
                           if(b.x-a.x+1>rozmiar)
                           {
                                    int gdzie_sciana = losuj(a.x+rozmiar/2, b.x-rozmiar/2);
                                    for(int k=mniej; k<=wiek; ++k)
                                             if(otoczenie[k][gdzie_sciana] == NULL)
                                             otoczenie[k][gdzie_sciana] = new Sciana_przejsciowa(ktory);

                                    zrob_pokoj(ktory, punkt_na_planszy(a.x, mniej), punkt_na_planszy(gdzie_sciana, wiek));
                                    zrob_pokoj(ktory, punkt_na_planszy(gdzie_sciana, mniej), punkt_na_planszy(b.x, wiek));

                                    if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(gdzie_sciana, mniej), punkt_na_planszy(gdzie_sciana, wiek)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, mniej), punkt_na_planszy(b.x, mniej)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, wiek), punkt_na_planszy(b.x, wiek)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, mniej), punkt_na_planszy(a.x, wiek)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(b.x, mniej), punkt_na_planszy(b.x, wiek)));
                           }
                  }break;
                  case 1:
                  {
                           if(wiek-mniej+1>rozmiar)
                           {
                                    int gdzie_sciana = losuj(mniej+rozmiar/2, wiek-rozmiar/2);
                                    for(int k=a.x; k<=b.x; ++k)
                                             if(otoczenie[gdzie_sciana][k] == NULL)
                                             otoczenie[gdzie_sciana][k] = new Sciana_przejsciowa(ktory);

                                    zrob_pokoj(ktory, punkt_na_planszy(a.x, mniej), punkt_na_planszy(b.x, gdzie_sciana), r);
                                    zrob_pokoj(ktory, punkt_na_planszy(a.x, gdzie_sciana), punkt_na_planszy(b.x, wiek), r);

                                    if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, gdzie_sciana), punkt_na_planszy(b.x, gdzie_sciana)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, mniej), punkt_na_planszy(b.x, mniej)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, wiek), punkt_na_planszy(b.x, wiek)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(a.x, mniej), punkt_na_planszy(a.x, wiek)));
                                    else if(postaw_drzwi_na_odcinku(ktory, punkt_na_planszy(b.x, mniej), punkt_na_planszy(b.x, wiek)));
                           }
                  }break;
         }
}

bool Strefa::czy_da_sie_taki_postawic_tu(int wx, int wy, int x, int y)
{ ///nie uwzglednia odleglosci 1 od budynkow i samych budynkow
         //bool porazka = false;
         //porazka = false;
         for(int w = x; w<x+wx; ++w)
         {
                  for(int v = y; v<y+wy; ++v)
                  {
                           if(otoczenie[v][w]!=NULL)
                           {
                                    return false;
                           }
                  }
         }
         return true;
}

punkt_na_planszy Strefa::czy_da_sie_taki_postawic(int wx, int wy)
{///nie sprawdza czy sa inne rzeczy niz budynki wokol budynkow
         bool porazka = false;
         for(int i=1; i<20-wx+1; ++i)
         {
                  for(int j=1; j<12-wy+1; ++j)
                  {
                           porazka = false;
                           ///jesli chcesz aby budynki byly obok siebie to to linijka 0
                           ///usun -1 przy inicjalizacji k i g; usun rowna sie z 2 srodkowych warunkow ponizszych petli for
                           for(int k=i-1; k<=i+wx; k+=4)
                           {
                                    for(int g=j-1; g<=j+wy; g+=4)
                                    {
                                             if(to_jest_na_podlodze(k, j)) {porazka=true;break;}
                                    }
                                    if(porazka) break;
                           }
                           if(porazka) continue;

                           for(int w = i; w<i+wx; ++w)
                           {
                                    for(int v=j; v<j+wy; ++v)
                                    {
                                             if(otoczenie[v][w]!=NULL || to_jest_na_podlodze(w, v))
                                             {
                                                      porazka = true;
                                                      break;
                                             }
                                    }
                                    if(porazka) break;
                           }
                           if(!porazka)
                                    return punkt_na_planszy(i,j);
                  }
         }
         return punkt_na_planszy(0,0);
}

bool Strefa::w_planszy(short x, short y)
{
         return x>=0 && x<=20 && y>=0 && y<=12;
}

void Strefa::Runda()
{

}

Swiat* Objekt::swiat;
dla_grafiki*Objekt::args;
Swiat::Swiat(bool*p, int X, int Y,dla_grafiki*arg, bool godmode)
{
         gracz->dodaj_obiekt(new Gracz());
         gracz->obiekt[0]->px=1;gracz->obiekt[0]->py=0;gracz->obiekt[0]->pz=0;
         gracz ->obiekt[0]-> x = 10;aktualny=gracz->obiekt[0];//aktualny->klatka_a=4;
         gracz->obiekt[0]-> y = 5;
         if(godmode) gracz->obiekt[0]->p_ruchu = 99;


         Objekt::swiat=this;
         Objekt::args=arg;
         this->X=X; this->Y=Y;
         pauza=p;


         area = new Area***[w_x];
         for(int i=0; i<w_x; i++)
         {
                  area[i] = new Area**[w_y];
                  for(int h=0;h<w_y;h++)
                  {
                           area[i][h]=new Area*[w_z];
                           for(int g=0;g<w_z;g++)
                           {
                                    area[i][h][g]=new Strefa(i,h,g);
                           }
                  }
         }

         //////////////////////////////////////////////////////////////////////////

         for(int i=0; i<w_x; i++)
         {
                  for(int h=0;h<w_y;h++)
                  {
                           for(int g=0;g<w_z;g++)
                           {
                                    if(w_zasiegu_gracza(i,h,g))
                                    {
                                             Strefa* aa=(Strefa*)area[i][h][g];
                                             area[i][h][g]=new Plansza(aa);
                                             delete aa;
                                    }
                           }
                  }
         }
         zaktualizuj_oddzialywanie_swietlne_plansz_na_siebie();
         for(int i=0; i<w_x; i++)
         {
                  for(int h=0;h<w_y;h++)
                  {
                           for(int g=0;g<w_z;g++)
                           {
                                    if(area[i][h][g]->jest_plansza)
                                    {
                                             ((Plansza*)area[i][h][g])->zaktualizuj_widoki();
                                    }
                           }
                  }
         }

         //area[0][0][0]->ma_gracza=true;
         area[1][0][0]->ma_gracza=true;
         Plansza* plansza=(Plansza*)area[1][0][0];
         aktualna = plansza;
         aktualna -> otoczenie[5][10]=gracz->obiekt[0];//aktualna -> otoczenie[6][10]=gracz->obiekt[1];
         //aktualna -> otoczenie[5][5]=gracz->obiekt[1];gracz->obiekt[1]->jedzenie_a=44;
         //stada_zombie->dodaj_obiekt(new Stado_zombie(0,0,0));

         Ustaw_aktualna(gracz->obiekt[0]->px,gracz->obiekt[0]->py,gracz->obiekt[0]->pz);


         Plecak*pl=new Plecak(3001);gracz->obiekt[0]->p_plecak=pl;
         //Bron*pll=new Bron(4252);pll->mag=30;
         //gracz->obiekt[0]->p_rece=pll;
         //gracz->obiekt[0]->p_glowa=new Ubranie(5001);
         //gracz->obiekt[0]->p_glowa=new Ubranie(5001);
         //gracz->obiekt[0]->p_rece=Item::stworz_obiekt(8017);


        ///gracz->obiekt[0]->p_rece=Item::stworz_obiekt(2003);
        ////gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2007));
        /*gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(4252));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2101));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2010));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8002));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8002));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8002));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8002));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8017));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(4010));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2011));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2011));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8021));

        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(4011));
        gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(4501));


         //gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(4010));*/

         /*gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(4003));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8022));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8023));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2020));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2005));*/
         //gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2020));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2007));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8024));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8025));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8020));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2008));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2021));
         gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(8018));


         //for(short t=0;t<16; ++t) gracz->obiekt[0]->dostan_item(Item::stworz_obiekt(2007));



         /*gracz->obiekt[1]->px=1;gracz->obiekt[1]->py=0;gracz->obiekt[1]->pz=0;
         gracz ->obiekt[1]-> x = 10;//aktualny=gracz->obiekt[1];
         gracz->obiekt[1]-> y = 6; gracz->obiekt[1]->woda_a = 300;gracz->obiekt[1]->jedzenie_a =0;*/
         /*gracz->dodaj_obiekt(new Gracz());
         gracz->obiekt[1]->px=1;gracz->obiekt[1]->py=0;gracz->obiekt[1]->pz=0;
         gracz ->obiekt[1]-> x = 5;
         gracz->obiekt[1]-> y = 5;*/

}

Swiat::~Swiat()
{return;
         for(int i=0; i<w_x; i++)
         {
                  for(int h=0;h<w_y;h++)
                  {
                           for(int g=0;g<w_z;g++) {area[i][h][g]->usun_ziemie();delete area[i][h][g];area[i][h][g]=NULL;}
                           delete [] area[i][h]; area[i][h]=NULL;
                  }
                  delete [] area[i]; area[i]=NULL;
         }
         delete [] area;
         area=NULL;

         //delete [] gracz; gracz sie przeciez gdzies znajduje
}

void Swiat::Ustaw_aktualna(int x, int y, int z)
{
         if(a_x!=x || a_y!=y || a_z!=z)
         {
                  if(zwroc_taka_plansze(x, y, z))
                  {
                           aktualna=zwroc_taka_plansze(x,y,z);
                           a_x = x; a_y = y; a_z = z;
                           aktualna->zaktualizuj_widoki();
                  }
                  else
                  {
                           std::cout<<"USTAW AKTUALNA ERRORR"<<x<<" "<<y<<" "<<z<<" "; throw "D";
                  }
         }
}

void Swiat::Ustaw_aktualna(Plansza*a)
{
         if(a!=aktualna)
         {a_x=a->x; a_y=a->y; a_z=a->z; aktualna=a;}
}

bool Swiat::ma_gracza_niespiacego(Plansza*a)
{
         for(int i=0;i<gracz->ilosc;++i) if(gracz->obiekt[i]->px==a->x && gracz->obiekt[i]->py==a->y && gracz->obiekt[i]->pz==a->z &&gracz->obiekt[i]->pozostalo_snu<=0) return true;
         return false;
}

void Swiat :: Nastepna_runda()///nie returnuje poki nie ma aktualnego lub gra nie przepadla
{
         //std::cout<<gracz->obiekt[0]->px<<gracz->obiekt[0]->py<<gracz->obiekt[0]->pz<<std::endl;

         teraz_gracz=false;
         int nr = 0;
         if(!zaczynamy_rundy_od_poczatku){if(aktualny!=NULL)nr=gracz->nr_obiektu(aktualny);else nr=0;}//std::cout<<nr<<std::endl;

         ///jakis gracz tu wlasnie konczy
         if(!gracz->obiekt[nr]->zaktualizuj_po_rundzie())
         {
                  gracz->usun_objekt(gracz->obiekt[nr]);
                  nr--;
         }
         if(gracz->ilosc==0) {koniec=true; return;}

         back_to_the_game:

         if(zaczynamy_rundy_od_poczatku)
         {
                  if(gracz->ilosc<=0) {koniec=true; return;}
                  zaczynamy_rundy_od_poczatku=false;
                  aktualny=gracz->obiekt[0];
                  aktualny->zaktualizuj_przed_runda();
                  if(!(*Objekt::args->godmode))aktualna->ma_gracza = true;
                  teraz_gracz=true;
                  if(!*(Objekt::args->godmode)) Ustaw_aktualna(aktualny->px,aktualny->py,aktualny->pz);
         }
         else if(nr<gracz->ilosc-1)
         {
                  aktualny=gracz->obiekt[nr+1];
                  aktualny->zaktualizuj_przed_runda();
                  if(!(*Objekt::args->godmode))aktualna->ma_gracza = true;
                  teraz_gracz=true;
                  if(!*(Objekt::args->godmode)) Ustaw_aktualna(aktualny->px,aktualny->py,aktualny->pz);
         }
         else
         {
                  Objekt::args->runda_swiata = true;
                  teraz_gracz=false;
                  Runda_swiata_bez_graczy();
                  Aktualizuj_pogode();
                  aktualna->zaktualizuj_widoki();
                  Objekt::args->runda_swiata = false;

                  zaczynamy_rundy_od_poczatku=true;
                  goto back_to_the_game;
         }
}

void Swiat::Aktualizuj_pogode()
{
         if(czas<1439)++czas;else czas=0;

         if(czas>1320 || czas<240)
         {
                  if(jasnosc_ogolna<240) jasnosc_ogolna++;
         }
         else if(czas>1200 && czas<1320)
         {
                  if(jasnosc_ogolna<120) jasnosc_ogolna++;
         }
         else
         {
                  if(jasnosc_ogolna>30) jasnosc_ogolna--;
         }

         od_ostatniej_zmiany_pogody-=2;if(losuj(1,100)<(100-od_ostatniej_zmiany_pogody))
         {
                  if(losuj(1,5)<3){if(pogoda<5)++pogoda;}
                  else if(pogoda>0) --pogoda;
                  od_ostatniej_zmiany_pogody=losuj(120,160);
         }
}

void Swiat::Runda_swiata_bez_graczy()
{
         for(int i=0; i<stada_zombie->ilosc; ++i) stada_zombie->obiekt[i]->Runda();
         int lx=gracz->obiekt[0]->px, px=gracz->obiekt[0]->px, gy=gracz->obiekt[0]->py, dy=gracz->obiekt[0]->py, gz=gracz->obiekt[0]->pz, dz=gracz->obiekt[0]->pz;
         for(int i=1; i<gracz->ilosc; i++)
         {
                  if(gracz->obiekt[i]->px<lx)lx=gracz->obiekt[i]->px;
                  if(gracz->obiekt[i]->px>px)px=gracz->obiekt[i]->px;
                  if(gracz->obiekt[i]->py<gy)gy=gracz->obiekt[i]->py;
                  if(gracz->obiekt[i]->py>dy)dy=gracz->obiekt[i]->py;
                  if(gracz->obiekt[i]->pz<dz)dz=gracz->obiekt[i]->pz;
                  if(gracz->obiekt[i]->pz>gz)gz=gracz->obiekt[i]->pz;
         }
         for(int i=lx-promien_obszaru_zywego; i<=px+promien_obszaru_zywego; i++)
         {
                  for(int j=gy-promien_obszaru_zywego-1; j<=dy+promien_obszaru_zywego+1; j++)
                  {
                           for(int z=dz-1; z<=gz+1; z++)
                           {
                                    if(z>-1 &&  z<w_z && i>-1 && j>-1 && i<w_x && j<w_y)
                                    {area[i][j][z]->Runda();}
                           }
                  }
         }
}

bool Swiat::w_zasiegu_gracza(Area *a)
{
         if(a==NULL) return false;
         for(int i=0; i<gracz->ilosc; i++)
         {
                  if(a->x>=gracz->obiekt[i]->px-promien_obszaru_zywego && a->x<=gracz->obiekt[i]->px+promien_obszaru_zywego &&
                     a->y>=gracz->obiekt[i]->py-(promien_obszaru_zywego+1) && a->y<=gracz->obiekt[i]->py+(promien_obszaru_zywego+1))
                  return true;
         }
         return false;
}

bool Swiat::w_zasiegu_gracza(int x, int y, int z)
{
         for(int i=0; i<gracz->ilosc; i++)
         {
                  if(x>=gracz->obiekt[i]->px-promien_obszaru_zywego && x<=gracz->obiekt[i]->px+promien_obszaru_zywego &&
                     y>=gracz->obiekt[i]->py-(promien_obszaru_zywego+1) && y<=gracz->obiekt[i]->py+(promien_obszaru_zywego+1))
                  return true;
         }
         return false;
}












Srodowisko::Srodowisko()
{

}

Objekt* Srodowisko::wierzch()
{
         if(stos->empty())
                  {return NULL;}
         else {return stos->front();}
}

bool Srodowisko::czy_usuwamy(int x, int y, Plansza*pl)
{
         /*al_lock_mutex(srodowiskowy);
         if(stos->empty() && stan == 0)
         {
                pl->srodowisko[y][x] = NULL; delete this; al_unlock_mutex(srodowiskowy); return true;
         }
         al_unlock_mutex(srodowiskowy); */
         return false;
}

bool Srodowisko::do_usuniecia()
{
         if(stos->empty() && stan == 0)
         {
                return true;
         }
         else return false;
}

short Srodowisko::wysokosc()
{
         short a=0;
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->wysokosc>a) a = (*it)->wysokosc;
         }
         if(a<2 && (stan&1)) a=2;
         return a;
}

void Srodowisko::dodaj_objekt(Objekt*a, int xx, int yy)
{
         a->x = xx; a->y = yy; bool wstawilismy = false;

         al_lock_mutex(srodowiskowy);
         if(a->wykonuje_ruch) rusza_sie=true;

         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->priorytet_w_srodowisku()>=a->priorytet_w_srodowisku())
                  {
                           stos->insert(it, a);
                           wstawilismy = true;
                           break;
                  }
         }
         if(!wstawilismy) stos->push_back(a);
         al_unlock_mutex(srodowiskowy);

}

void Srodowisko::dodaj_objekt(Objekt*a, int xx, int yy, Plansza*p)
{
         if(p->srodowisko[yy][xx]==NULL) p->srodowisko[yy][xx]=new Srodowisko();
         p->srodowisko[yy][xx]->dodaj_objekt(a,xx,yy);
}

Objekt* Srodowisko::usun_objekt(int czym_ma_byc, short x, short y, Plansza *pl)
{
         Objekt *a=NULL;

         al_lock_mutex(srodowiskowy);
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->czym_jest == czym_ma_byc)
                  {
                           a = *it;
                           ostatni_usuwany = stos->erase(it);
                           break;
                  }
         }
         if(a)
         {
                  ogarnij_sie_z_wykonywaniem_ruchu();
                  a->x = x; a->y = y;
         }
         al_unlock_mutex(srodowiskowy);
         return a;
}

Objekt* Srodowisko::usun_objekt(Objekt*a, short x, short y, Plansza *pl)
{
         al_lock_mutex(srodowiskowy);
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)==a)
                  {
                           ostatni_usuwany = stos->erase(it); break;
                  }
         }
         ogarnij_sie_z_wykonywaniem_ruchu();
         a->x = x; a->y = y;
         al_unlock_mutex(srodowiskowy);
         return a;
}

void Srodowisko::zostan_uderzony_ogolnie(short obr, short rodzaj)
{
            for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
             {
                      ostatni_usuwany = it;
                        (*it)->zostan_uderzony(obr, rodzaj, 0, 0);
                        it = ostatni_usuwany;
             }
}

bool Srodowisko::ma_to(int czym_ma_to_byc)
{
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->czym_jest == czym_ma_to_byc)
                  {
                           return true;
                  }
         }
         return false;
}

bool Srodowisko::ma_to(Objekt*a)
{
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)==a)
                  {
                           return true;
                  }
         }
         return false;
}

Objekt* Srodowisko::zwroc_objekt(int czym_ma_to_byc)
{
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->czym_jest==czym_ma_to_byc)
                  {
                           return *it;
                  }
         }
         return NULL;
}

void Srodowisko::ogarnij_sie_z_wykonywaniem_ruchu()
{
         rusza_sie = false;
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->wykonuje_ruch)
                  {
                           rusza_sie = true;
                           return;
                  }
         }
}

od_srodowiska Srodowisko::rysunek()
{
         al_lock_mutex(srodowiskowy);
         od_srodowiska a(stan, przesuniecie_x, przesuniecie_y, 0);
         if(stos->empty()==false)
         {
                  a.rys = stos->front()->get_co_to();
         }
         al_unlock_mutex(srodowiskowy); return a;
}

bool Srodowisko::wykonuje_ruch()
{
         return rusza_sie;
}

void Srodowisko::Runda(short x, short y, Plansza *pl)
{
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  ostatni_usuwany = it;
                  (*it)->rusz_sie();////////tu bez mutexow, mutexy tylko w atomowych funkcjach
                  it = ostatni_usuwany;
         }
}

Srodowisko* Srodowisko:: zwroc_srodowisko(Srodowisko_przejsciowe*a, int x, int y, int px, int py, int pz)
{
         if(a==NULL) return NULL;
         Srodowisko*b=new Srodowisko(); b->stan = a->stan; b->paliwo_do_palenia=0;
         for(int i=0; i<a->zawartosc->ilosc; ++i)
         {
                  b->dodaj_objekt(Objekt::z_objektu_tymczasowego(a->zawartosc->obiekt[i],x,y,px,py,pz), x, y);
         }
         b->rusza_sie=false; b->ogarnij_sie_z_wykonywaniem_ruchu();
         return b;
}

bool Srodowisko_przejsciowe::ma_to(int czym_ma_to_byc)
{
         for(int i=0; i<zawartosc->ilosc; i++) if(zawartosc->obiekt[i]->czym_jest==czym_ma_to_byc) return true;
         return false;
}

Srodowisko_przejsciowe*Srodowisko_przejsciowe:: zwroc_przejsciowe_srodowisko(Srodowisko*a)
{
         if(a==NULL) return NULL;
         Srodowisko_przejsciowe*b=new Srodowisko_przejsciowe(); b->stan = a->stan;
         for(std::list<Objekt*>::iterator it = a->stos->begin(); it!=a->stos->end(); ++it)
         {
                  b->zawartosc->dodaj_obiekt(Objekt_przejsciowy::z_objektu(*it));
         }
         return b;
}

bool Srodowisko::zjedz_rosline(int jaka)
{
         al_lock_mutex(srodowiskowy);
         if(jaka==22)
         {
                  for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
                  {
                           if((*it)->czym_jest==jaka)
                           {
                                    if(((Trawa*)*it)->wysokosc>1){((Trawa*)*it)->wysokosc--;((Trawa*)*it)->rosniecie=0;}
                                    else
                                    {
                                             Trawa * a = (Trawa*)*it;
                                             ostatni_usuwany = stos->erase(it);
                                             delete a;//////////////////bo sa mutexy
                                    }
                                    al_unlock_mutex(srodowiskowy);
                                    return true;
                           }
                  }
         }
         al_unlock_mutex(srodowiskowy);
         return false;
}

Srodowisko::~Srodowisko()
{
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  delete (*it);
         }
         delete stos;
         al_destroy_mutex(srodowiskowy);
}

Srodowisko_przejsciowe::~Srodowisko_przejsciowe()
{
         if(zawartosc!=NULL) zawartosc->deletuj_obiekty();
         delete zawartosc;
}

bool Srodowisko::ma_na_wierzchu(int co)
{
         return stos->empty()==false && stos->front()->czym_jest == co;
}

void Srodowisko::wydaj_dzwiek_bycia_deptanym(Plansza *a)
{
         if(this==NULL) return;
         if(stan&2) a->dzwiek(false, 2, 0, 0, 0);
}

zrodlo_swiatla Srodowisko::swiatlo()
{
         if(this==NULL) return zrodlo_swiatla(0,0);
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if((*it)->swiatlo().get_rodzaj()!=0)
                           return (*it)->swiatlo();
         }
         if(this->stan&1) return zrodlo_swiatla(1, 70, 50);
         return zrodlo_swiatla(0,0);
}

Stado_zombie::Stado_zombie(int a, int b, int c)
{
         x=a; y=b; z=c;
}

Stado_zombie::~Stado_zombie()
{

}

void Stado_zombie::zaszczep_stado()
{return;
         /*if(Objekt::swiat->area[x][y][z]->jest_plansza)
         {
                  Plansza*p=(Plansza*)Objekt::swiat->area[x][y][z];
                  for(int i=0; i<13; ++i)
                  {
                           for(int j=0; j<21; ++j)
                           {
                                    if(p->otoczenie[i][j]!=NULL && p->otoczenie[i][j]->czym_jest==2)
                                             ((Zombie*)p->otoczenie[i][j])->stado=this;
                           }
                  }
         }*/
}

void Stado_zombie::Runda()
{
         ++czas;
         zaszczep_stado();
         int a=losuj(1,3);
         if(czas>=15)
         {
                  switch(gdzie_skrecamy)
                  {
                  case 'p':
                           {
                                    bool ss=false;
                                    while(true)
                                    {
                                             switch(a)
                                             {
                                                      case 1:if(y-1>-1){gdzie_skrecamy='g';--y;ss=true;break;}
                                                      case 2:if(x+1<Objekt::swiat->w_x){gdzie_skrecamy='p';++x;ss=true;break;}
                                                      case 3:if(y+1<Objekt::swiat->w_y){gdzie_skrecamy='d';++y;ss=true;break;}
                                             }
                                             if(ss) break; ss=true; a=1;
                                    }
                           break;}
                  case 'l':
                           {
                                    bool ss=false;
                                    while(true)
                                    {
                                             switch(a)
                                             {
                                                      case 1:if(y-1>-1){gdzie_skrecamy='g';--y;ss=true;break;}
                                                      case 2:if(x-1>-1){gdzie_skrecamy='l';--x;ss=true;break;}
                                                      case 3:if(y+1<Objekt::swiat->w_y){gdzie_skrecamy='d';++y;ss=true;break;}
                                             }
                                             if(ss) break; ss=true; a=1;
                                    }
                           break;}
                  case 'd':
                           {
                                    bool ss=false;
                                    while(true)
                                    {
                                             switch(a)
                                             {
                                                      case 1:if(y-1>-1){gdzie_skrecamy='g';--y;ss=true;break;}
                                                      case 2:if(x+1<Objekt::swiat->w_x){gdzie_skrecamy='p';++x;ss=true;break;}
                                                      case 3:if(x-1>-1){gdzie_skrecamy='l';--x;ss=true;break;}
                                             }
                                             if(ss) break; ss=true; a=1;
                                    }
                           break;}
                  case 'g':
                           {
                                    bool ss=false;
                                    while(true)
                                    {
                                             switch(a)
                                             {
                                                      case 1:if(x-1>-1){gdzie_skrecamy='l';--x;ss=true;break;}
                                                      case 2:if(x+1<Objekt::swiat->w_x){gdzie_skrecamy='p';++x;ss=true;break;}
                                                      case 3:if(y+1<Objekt::swiat->w_y){gdzie_skrecamy='d';++y;ss=true;break;}
                                             }
                                             if(ss) break; ss=true; a=1;
                                    }
                           break;}
                  }
         }
}

void Srodowisko::podpal()
{
         paliwo_do_palenia = 0;
         stan|=1;
}

void Srodowisko::palenie(short x, short y, Plansza *pl)
{
         Objekt::wstrzymaj_animacje=true;
         if(stan&4)
         {
                  stan-=4;
                  paliwo_do_palenia+=10;
         }
         if(pl->ziemia[y][x])
         {
                  Kontener<Item> *a = pl->ziemia[y][x];
                  if(a->ilosc>0)
                  {
                           Item * ddd = a->usun_objekt(0);
                           delete ddd;
                           paliwo_do_palenia += 3;
                  }
                  if(a->ilosc==0)
                  {
                           pl->ziemia[y][x] = NULL;
                           delete a;
                  }
         }
         for(std::list<Objekt*>::iterator it = stos->begin(); it!=stos->end(); ++it)
         {
                  if(!((*it)->stan&1))
                  {
                           (*it)->sproboj_podpalic();
                  }
                  else
                  {
                           paliwo_do_palenia+=5;
                           ostatni_usuwany = it;
                           (*it)->zostan_uderzony(losuj(10, 20),obrazenia_od_ognia,0,0);
                           it = ostatni_usuwany;
                  }
         }
         Objekt::wstrzymaj_animacje=false;
         if(--paliwo_do_palenia<=0)
         {
                  if(stan&1) stan-=1;
                  czy_usuwamy(x, y, pl);
         }
}

void Plansza::animacja_iskry(short x, short y)
{
         if(!Strefa::w_planszy(x, y)) return;
         dla_grafiki *args = Objekt::args;
         args->x_iskry=x*args->X_kratka+args->X_kratka/2; args->y_iskry=y*args->Y_kratka+args->Y_kratka/2;
         oswietlenie_z_innych_plansz[y][x] = 60;
         if(Strefa::w_planszy(x, y+1)) oswietlenie_z_innych_plansz[y+1][x] = 100;
         if(Strefa::w_planszy(x+1, y)) oswietlenie_z_innych_plansz[y][x+1] = 100;
         if(Strefa::w_planszy(x-1, y)) oswietlenie_z_innych_plansz[y][x-1] = 100;
         if(Strefa::w_planszy(x, y-1)) oswietlenie_z_innych_plansz[y-1][x] = 100;
         zaktualizuj_widoki(false);
         for(short j=1; j<6; ++j)
         {
                  args->iskra = j;
                  al_rest(0.1);
         }
         args->iskra = 0;
         zaktualizuj_widoki();
}

void Plansza::iskra(short x, short y)
{
         if(!Strefa::w_planszy(x, y)) return;
         animacja_iskry(x, y);
         //std::cout<<y<<" "<<x<<std::endl;

         if(srodowisko[y][x] && (srodowisko[y][x]->wierzch()==NULL || srodowisko[y][x]->wierzch()->czym_jest!=24))
         {
                  srodowisko[y][x]->sproboj_podpalic();
         }
         else if(losuj(1,10)<4) ((Ognisko*)srodowisko[y][x]->wierzch())->podpal();
         zaktualizuj_widoki();
}

bool Srodowisko::sproboj_podpalic()
{
         if(wierzch()!=NULL && wierzch()->czym_jest==24) ((Ognisko*)wierzch())->podpal();
         if(!this || (stan&1)) return false;
         if(stos->empty()==false && stos->front()->sproboj_podpalic())
                                    {podpal(); return true;}
         if(stan&4)
                  {podpal(); return true;}
         return false;
}

void Plansza::dziej_ogien()
{
         for(short u=0; u<13; ++u) for(short g=0;g<21;++g) {pom[0][u][g] = false;pom[1][u][g] = false;}///otoczenie, srodowisko
         for(short u=0;u<13;++u)
         {
                  for(short g=0;g<21;++g)
                  {
                           if(pom[1][u][g] == false && srodowisko[u][g] && srodowisko[u][g]->stan&1)
                           {
                                    if(Strefa::w_planszy(g, u+1)) if(srodowisko[u+1][g]->sproboj_podpalic()) pom[1][u+1][g]=true;
                                    if(Strefa::w_planszy(g, u-1)) if(srodowisko[u-1][g]->sproboj_podpalic()) pom[1][u-1][g]=true;
                                    if(Strefa::w_planszy(g+1, u)) if(srodowisko[u][g+1]->sproboj_podpalic()) pom[1][u][g+1]=true;
                                    if(Strefa::w_planszy(g-1, u)) if(srodowisko[u][g-1]->sproboj_podpalic()) pom[1][u][g-1]=true;
                                    if(otoczenie[u][g] && !(otoczenie[u][g]->stan&1)) if(otoczenie[u][g]->sproboj_podpalic()) pom[0][u][g]=true;
                                    srodowisko[u][g]->palenie(g, u, this);
                           }
                           if(pom[0][u][g] == false && otoczenie[u][g] && otoczenie[u][g]->stan&1)
                           {
                                    if(Strefa::w_planszy(g, u+1)) if(otoczenie[u+1][g]->sproboj_podpalic()) pom[0][u+1][g]=true;
                                    if(Strefa::w_planszy(g, u-1)) if(otoczenie[u-1][g]->sproboj_podpalic()) pom[0][u-1][g]=true;
                                    if(Strefa::w_planszy(g+1, u)) if(otoczenie[u][g+1]->sproboj_podpalic()) pom[0][u][g+1]=true;
                                    if(Strefa::w_planszy(g-1, u)) if(otoczenie[u][g-1]->sproboj_podpalic()) pom[0][u][g-1]=true;
                                    if(srodowisko[u][g] && !(srodowisko[u][g]->stan&1)) if(srodowisko[u][g]->sproboj_podpalic()) pom[1][u][g]=true;
                                    Objekt::wstrzymaj_animacje=true;
                                    otoczenie[u][g]->zostan_uderzony(losuj(10, 20),obrazenia_od_ognia,0,0);
                                    Objekt::wstrzymaj_animacje=false;
                           }
                  }
         }
}

void Plansza::wybuch(punkt **p)///ostatni to NULL
{
         for(short k=1; k<18; ++k)
         {
                  for(short i=0; p[i]; ++i)
                  {
                           if(Strefa::w_planszy(p[i]->x, p[i]->y) && this == Objekt::swiat->aktualna)
                                    Objekt::args->wybuch[p[i]->y][p[i]->x] = k;
                  }
                  if(k==1) {zaktualizuj_widoki();}
                  if(ma_gracza) Sleep(58);
         }
         for(short i=0; p[i]; ++i)
         {
                  if(Strefa::w_planszy(p[i]->x, p[i]->y))
                           Objekt::args->wybuch[p[i]->y][p[i]->x] = 0;
                  if(Strefa::w_planszy(p[i]->x, p[i]->y) && losuj(1,5)==3)
                  {
                           if(!srodowisko[p[i]->y][p[i]->x]) srodowisko[p[i]->y][p[i]->x] = new Srodowisko();
                           if(!(srodowisko[p[i]->y][p[i]->x]->stan&1)) srodowisko[p[i]->y][p[i]->x]->stan++;
                           srodowisko[p[i]->y][p[i]->x]->paliwo_do_palenia += 5;
                  }
         }

         zaktualizuj_widoki();

         for(short i=0; p[i]; ++i)
         {
                  if(Strefa::w_planszy(p[i]->x, p[i]->y))
                  {
                           if(otoczenie[p[i]->y][p[i]->x])
                                    otoczenie[p[i]->y][p[i]->x] ->zostan_uderzony(60, obrazenia_od_wybuchu, 0, 0);
                            if(srodowisko[p[i]->y][p[i]->x])
                                    srodowisko[p[i]->y][p[i]->x] ->zostan_uderzony_ogolnie(60, obrazenia_od_wybuchu);
                           dzwiek(1, 10, p[i]->x, p[i]->y, 0);
                  }
         }
         std::vector<std::shared_ptr<Upadly>> upadli = daj_wskazniki_do_upadlych();
         for(auto it = upadli.begin(); it!=upadli.end(); ++it)
         {
                for(short i=0; p[i]; ++i)
                 {
                          if(Strefa::w_planszy(p[i]->x, p[i]->y) && (*it)->getX()==p[i]->x && (*it)->getY()==p[i]->y && (*it)->getA()->czym_jest==2)
                          {
                                    (*it)->getA()->zostan_uderzony(60, obrazenia_od_wybuchu,0,0);
                          }
                 }
         }
}

short Plansza::wstaw_w_punkty(punkt **a, short index, short odl, short x, short y)
{
         short akt_x=x, akt_y=y;
         if(!odl) return (a[index]=new punkt(x, y)) || true ? index+1 : throw "XD";

         for(akt_x=x-odl; akt_x!=x || akt_y!=y-odl;)
         {
                  a[index++] = new punkt(akt_x, akt_y); ++akt_x; --akt_y;
         }
         for(; akt_x!=x+odl || akt_y!=y;)
         {
                  a[index++] = new punkt(akt_x, akt_y); ++akt_x; ++akt_y;
         }
         for(; akt_x!=x || akt_y!=y+odl;)
         {
                  a[index++] = new punkt(akt_x, akt_y); --akt_x; ++akt_y;
         }
         for(; akt_x!=x-odl || akt_y!=y;)
         {
                  a[index++] = new punkt(akt_x, akt_y); --akt_x; --akt_y;
         }
         return index;
}

short Plansza::ile(short odl, short x, short y)
{
         short akt_x=x, akt_y=y;
         if(!odl) return 1;
         short aaa = 0;


         for(akt_x=x-odl; (akt_x!=x || akt_y!=y-odl);)
         {
                  aaa++;--akt_y;++akt_x;
         }
         for(; akt_x!=x+odl || akt_y!=y; )
         {
                  aaa++;++akt_x; ++akt_y;
         }
         for(; akt_x!=x || akt_y!=y+odl;)
         {
                  aaa++; --akt_x; ++akt_y;
         }
         for(; akt_x!=x-odl || akt_y!=y;)
         {
                  aaa++; --akt_x; --akt_y;
         }
         return aaa + ile(odl-1, x, y);
}

void Plansza::wybuch_o_mocy(short moc, short x, short y)
{
         short h=ile(moc, x, y);
         punkt **a = new punkt*[h+1];
         a[h] = NULL;
         short l=0;
         for(short t=0; t<=moc; ++t)
                  l = wstaw_w_punkty(a, l, t, x, y);

         wybuch(a);

         for(short t=0; a[t]; ++t) delete a[t];
         delete [] a;
         return;
}

void Plansza::podpalenie_o_mocy(short moc, short x, short y, short paliwo)
{
         short h=ile(moc, x, y);
         punkt **p = new punkt*[h+1];
         p[h] = NULL;
         short l=0;
         for(short t=0; t<=moc; ++t)
                  l = wstaw_w_punkty(p, l, t, x, y);

         for(short i=0; p[i]; ++i)
         {
                  if(Strefa::w_planszy(p[i]->x, p[i]->y))
                  {
                           if(!srodowisko[p[i]->y][p[i]->x]) srodowisko[p[i]->y][p[i]->x] = new Srodowisko();
                           if(!(srodowisko[p[i]->y][p[i]->x]->stan&1)) srodowisko[p[i]->y][p[i]->x]->stan++;
                           srodowisko[p[i]->y][p[i]->x]->paliwo_do_palenia += paliwo;
                  }
         }

         zaktualizuj_widoki();

         for(short t=0; p[t]; ++t) delete p[t];
         delete [] p;
         return;
}




