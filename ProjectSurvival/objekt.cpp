#include "swiat.h"
#include "swiat2.h"
#include <windows.h>



void Objekt::smierc()
{
         poza_tym_swiatem = true;
         if(swiat->zwroc_taka_plansze(px, py, pz))
                  swiat->zwroc_taka_plansze(px, py, pz)->juz_martwy.push_back(this);
         //swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->juz_martwy.push_back(this);
}

int Objekt :: get_co_to()
{
         return co_to;
}

int Objekt :: get_animacja()
{
         return animacja;
}

void Objekt::wydaj_dzwiek(bool moze_wyjsc_poza_plansze,int moc, int dx, int dy,int rodzaj)
{
         Plansza *aa=swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         aa->dzwiek(moze_wyjsc_poza_plansze, moc, dx, dy, rodzaj);
}

char Objekt::gdzie_isc(int cx, int cy, int ppx, int ppy,bool p[13][21])
{
         if((cx==ppx && cy==ppy)) return 'n';if(cx==ppx+1 && cy==ppy)return 'p';
         if(cx==ppx-1 && cy==ppy)return 'l';if(cx==ppx && cy==ppy+1)return 'd';
         if(cx==ppx && cy==ppy-1)return 'g';//if(cx==ppx+2 && cy==ppy)return'p';else if(cx==ppx-2 && cy==ppy)return'l';
         //if(cx==px && cy==py+2)return'd';else if(cx==px && cy==py-2)return'g';
         //if(cx==px+2 && cy==py)return'd';else if(cx==px && cy==py)return'g';
         int licznik_dla_n=0;int ile=300;
         c[0].a=ppy; c[0].b=ppx; c[0].odn=0;int n=1,s=0,k=1;bool endd=false;
         //int kor_x_22=0, kor_y_14=0, kor_x_0=0, kor_y_0=0;
         //if(cx==0) kor_x_0=1; else if(cx==21) kor_x_22=1; else if(cy==0) kor_y_0=1; else if(cy==13) kor_y_14=1;
         while(true)
         {
                  licznik_dla_n++;if(licznik_dla_n==ile){return 'n';}
                  for(int y=s;y<k;y++)
                  {
                           bool lewo=true,prawo=true,dol=true,gora=true;
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b+1 && c[u].a==c[y].a){prawo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b-1 && c[u].a==c[y].a){lewo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a-1){gora=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a+1){dol=false;break;}}
                           if (c[y].b+1<21 && prawo && (p[c[y].a][c[y].b+1]==false || (c[y].a==cy && c[y].b+1==cx)))
                  {
                           c[n].odn=y;c[n].a=c[y].a;c[n].b=c[y].b+1; if (c[n].a==cy && c[n].b==cx)
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
                if (c[y].b-1>-1 && lewo && (p[c[y].a][c[y].b-1]==false || (c[y].a==cy && c[y].b-1==cx)))
                    {
                           c[n].odn=y;c[n].a=c[y].a;c[n].b=c[y].b-1; if (c[n].a==cy && c[n].b==cx)
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
                if (c[y].a-1>-1 && gora && (p[c[y].a-1][c[y].b]==false || (c[y].a-1==cy && c[y].b==cx)))
                    {
                           c[n].odn=y;c[n].a=c[y].a-1;c[n].b=c[y].b; if (c[n].a==cy && c[n].b==cx)
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
                if (c[y].a+1<13 && dol && (p[c[y].a+1][c[y].b]==false || (c[y].a+1==cy && c[y].b==cx)))
                    {
                           c[n].odn=y;c[n].a=c[y].a+1;c[n].b=c[y].b; if (c[n].a==cy && c[n].b==cx)
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
            }
            s=k;k=n;if (endd) break;
        }
    return 'n';
}

char Objekt_zywy::znajdz_droge(bool umiemy_niszczyc_przedmioty,int cx, int cy, int ppx, int ppy,Plansza* a)
{
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<" szd ";
         if(cx==-1 || cx==21 || cy==13 || cy==-1)
         {
                  int a=0; if(cx==-1) ++a;if(cx==21) ++a;if(cy==-1) ++a;if(cy==13) ++a;if(a>=2) {std::cout<<"chcial na rog mapy";throw "ddd";}
                  if(cx==-1 && ppx==0 && ppy==cy) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return 'l';}
                  else if(cx==21 && ppx==20 && cy==ppy) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return 'p';}
                  else if(cy==-1 && ppy==0 && cx==ppx) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return 'g';}
                  else if(cy==13 && ppy==12 && cx==ppx) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return 'd';}
                  if(cx==-1) cx=0; else if(cx==21) cx=20; if(cy==-1) cy=0; else if(cy==13) cy=12;
         }
         bool tab[13][21]; for(int i=0;i<13;i++){for(int j=0;j<21;j++){if(a->otoczenie[i][j]==NULL)tab[i][j]=false;else tab[i][j]=true;}}
         char gdzie; if((gdzie=gdzie_isc(cx,cy,ppx,ppy,tab))!='n') {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return gdzie;}
                  for(int i=0;i<13;i++){for(int j=0;j<21;j++){if(tab[i][j] && a->otoczenie[i][j]->zywy)tab[i][j]=false;}}
                  if((gdzie=gdzie_isc(cx,cy,ppx,ppy,tab))!='n') {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return gdzie;}

         if(umiemy_niszczyc_przedmioty)
         {
                  //for(int i=0;i<13;++i){for(int j=0;j<21;++j){tab[i][j]=a->otoczenie[i][j]!=NULL;}}
                  char f;int k=300;
                  while(true)
                  {
                           for(int i=0;i<13;i++)
                           {
                                    for(int j=0;j<21;j++)
                                    {
                                             if(a->otoczenie[i][j]==NULL) tab[i][j]=false;
                                             else
                                             {
                                                      /*(if(a->otoczenie[i][j]->czym_jest==26)
                                                      {
                                                               ///tab[i][j]=!wolna_prosta(tab_widocznosci,x*100+50,y*100+50,cx*100+50,cy*100+50);///////////
                                                      }*/
                                                      tab[i][j]=a->otoczenie[i][j]->na_ile_hp_wyglada()>k;
                                             }
                                    }
                           }
                  f=gdzie_isc(cx,cy,ppx,ppy,tab);
                  if(f!='n') {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return f;}
                  if(k==300) k=600; else if(k==600) k=1000; else if(k==1000) k=10000; else break;
                  }
         }
         else {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return 'n';}
         {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn ";return 'n';}
}

char Objekt_zywy::znajdz_ucieczke(int ominiecie,int cx, int cy, int ppx, int ppy,Plansza* a)
{
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<"szu";
         bool tab[13][21]; if(ominiecie<0) {std::cout<<"znajdz ucieczke ma ominiecie mniejsze od 0";throw "ddd";}
         if(cx==-1 || cx==21 || cy==13 || cy==-1)
         {
                  int a=0; if(cx==-1) ++a;if(cx==21) ++a;if(cy==-1) ++a;if(cy==13) ++a;if(a>=2) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn";return 'n';}
                  if(cx==-1 && ppx==0 && ppy==cy) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn";return 'l';}
                  else if(cx==21 && ppx==20 && cy==ppy) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn";return 'p';}
                  else if(cy==-1 && ppy==0 && cx==ppx) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn";return 'g';}
                  else if(cy==13 && ppy==12 && cx==ppx) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn";return 'd';}
                  if(cx==-1) cx=0; else if(cx==21) cx=20; if(cy==-1) cy=0; else if(cy==13) cy=12;
         }
         for(int k=ominiecie; k>=0; --k)
         {
                  for(int i=0;i<13;i++){for(int j=0;j<21;j++){tab[i][j]=false;}}
                  for(int i=0;i<13;i++)
                  {
                           for(int j=0;j<21;j++)
                           {
                                    if(a->otoczenie[i][j]!=NULL)
                                    {
                                             tab[i][j]=true;
                                             if(a->otoczenie[i][j]->zywy && a->otoczenie[i][j]->czym_jest!=8)///nikt nie boi sie sarn
                                             {
                                                      for(int g=i-k; g<=i+k; ++g)
                                                      {
                                                               for(int f=j-k; f<=j+k; ++f)
                                                               {
                                                                        if(g>-1 && g<13 && f>-1 && f<21) tab[g][f]=true;
                                                               }
                                                      }
                                             }
                                    }
                           }
                  }
                  char gdzie=gdzie_isc(cx,cy,ppx,ppy,tab);
                  /*if(swiat->a_x==px && swiat->a_y==py)
                  {
                           std::cout<<cx<<" "<<cy<<" "<<ppx<<" "<<ppy<<" "<<std::endl;
                           for(int i=0;i<21;i++){for(int j=0;j<13;j++){std::cout<<tab[j][i]<<" ";}std::cout<<std::endl;}
                  }*/

                  if((gdzie)!='n') {if(Objekt::args->melduj_co_robi_AI)std::cout<<" zn";return gdzie;}
         }
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<" zn";
         return 'n';
}

bool Objekt::czy_lezy()
{
         if(czym_jest==2) return ((Zombie*)this)->lezy;
         return false;
}

what_happened Objekt::reakcja_na_podloze()
{
         Srodowisko *s = NULL;
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         if(p->srodowisko[y][x]!=NULL) s = p->srodowisko[y][x];
         else return success;

         if(s->stan&4)
         {
                  switch(czym_jest)
                  {
                           case 2: {if(losuj(0, 1))((Zombie*)this)->przewroc();}break;
                           default: break;
                  }
         }
         if(s->stan&2)
         {
                  switch(czym_jest)
                  {
                           case 2: {if(((Zombie*)this)->moze_chodzic()) {if(zostan_uderzony(losuj(2, 5) , -3, 0, 2)==dead) return dead;} else {if(zostan_uderzony(losuj(7, 13) , 0, 0, 2)==dead) return dead;}}break;
                           case 10: {if(((Gracz*)this)->postawa=='c') {if(zostan_uderzony(losuj(2, 5) , 0, 0, 2)==dead) return dead;}
                                    else if(((Gracz*)this)->postawa=='s') {if(zostan_uderzony(losuj(4, 8) , -4, 0, 2)) return dead;}
                                    else {if(zostan_uderzony(losuj(7, 13) , -3, 0, 2)==dead) return dead;}}break;
                           default: if(zostan_uderzony(losuj(5, 7), 0, 0, 2)==dead) return dead;
                  }
         }
         if(s->stan&1)
         {
                  if(zostan_uderzony(losuj(4, 9) , obrazenia_od_ognia, 0, 0)==dead) return dead;
         }


         if(s->ma_na_wierzchu(35))
         {
                  Objekt *aaa = s->zwroc_objekt(35);
                  switch(czym_jest)
                  {
                           default: aaa->zostan_uderzony(15, 0,0,0); if(zostan_uderzony(30, 0, 0, 0)==dead) return dead; break;
                  }
         }



         return success;
}

what_happened Objekt::przesun(char strona, bool czy_zmieniac_zwrot)
{
         if(czy_lezy()) return fail;
         if(this==NULL) {std::cout<<"NULL na Objekt::przesun"; return fail;}
         if(strona!='n' && strona!='p' && strona!='l' && strona!='d' && strona!='g')
         {std::cout<<" zly zwrot dla f przesun "; throw "ff";}
         if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" prz ";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         int kx=px, ky=py, kz=pz;
         if(strona=='n')  {if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" przM ";return fail;}
         Swiat* swiat=Objekt::swiat;
         Plansza* nasza=swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         Area* dawna=swiat->zwroc_taka_aree(px, py, pz);
         int sx=x, sy=y;///ku pamieci widokow
         int s_x=x, s_y=y; switch(strona) {case 'p': s_x++;break;case 'l': s_x--;break;case 'g': s_y--;break;case 'd': s_y++;break;}

         if(czym_jest==30 && Strefa::w_planszy(s_x, s_y) && nasza->otoczenie[s_y][s_x]!=NULL && nasza->otoczenie[s_y][s_x]->czym_jest==2)
         {
                  Zombie *z = (Zombie*)nasza->otoczenie[s_y][s_x];
                  z->przewroc();
                  z->zostan_uderzony(losuj(20, 30), 0,0, 10);
         }

         if(!((s_y>-1 && s_y<13 && s_x>-1 && s_x<21 && nasza->otoczenie[s_y][s_x]==NULL)
            ||((s_x==21 && swiat->zwroc_taka_plansze(px+1, py, pz) && swiat->zwroc_taka_plansze(px+1, py, pz)->otoczenie[y][0]==NULL)
               ||(s_x==-1 && swiat->zwroc_taka_plansze(px-1, py, pz) && swiat->zwroc_taka_plansze(px-1, py, pz)->otoczenie[y][20]==NULL)
               ||(s_y==13 && swiat->zwroc_taka_plansze(px, py+1, pz) && swiat->zwroc_taka_plansze(px, py+1, pz)->otoczenie[0][x]==NULL)
               ||(s_y==-1 && swiat->zwroc_taka_plansze(px, py-1, pz) && swiat->zwroc_taka_plansze(px, py-1, pz)->otoczenie[12][x]==NULL))))
               {if(Objekt::args->melduj_co_robi_AI)std::cout<<" pMM ";return fail;}

         int do_czego=swiat->X;if(strona=='g' || strona=='d') do_czego=swiat->Y;
         if(nasza->ma_gracza)
         {
                  przesuniecie_x=0; przesuniecie_y=0; przesuwamy=true;
                  for(int i=0; i<do_czego/2; i++) {switch(strona)
                  {case 'p':przesuniecie_x=i;break;case 'l':przesuniecie_x=-i;break;case 'g':przesuniecie_y=-i;break;case 'd':przesuniecie_y=i;break;}Sleep(375/do_czego);}
                  przesuwamy=false;
         }

         if(czy_zmieniac_zwrot)
         {
                  zwrot=strona;
                  if(zwrot=='l' || zwrot=='p')
                  {
                           switch (czym_jest)
                           {
                                    case 8: {Sarna*rzut=(Sarna*)this;rzut->zwrot_ostatni=zwrot;}break;
                                    case 9: {Niedzwiedz*rzut=(Niedzwiedz*)this;rzut->zwrot_ostatni=zwrot;}break;
                                    case 37: {Reflektor*rzut=(Reflektor*)this;rzut->kierunek=zwrot;}break;
                                    default:break;
                           }
                  }
         }
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"$1";

         dzwiek_przesuniecia(x,y);
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"$5";
         nasza->otoczenie[y][x]=NULL;
         if(Objekt::args->melduj_co_robi_AI) std::cout<<"$6";
         if(s_x!=-1 && s_x!=21 && s_y!=-1 && s_y!=13)
         {
                  przesuniecie_x=0; przesuniecie_y=0;
                  nasza->otoczenie[s_y][s_x]=this;
                  if(Objekt::args->melduj_co_robi_AI) std::cout<<" $2 ";
                  x=s_x; y=s_y;
                  if(nasza->ma_gracza)
                  {
                           przesuwamy=true;
                           for(int i=do_czego/2; i>=0; i--) {switch(strona)
                           {case 'p':przesuniecie_x=-i;break;case 'l':przesuniecie_x=i;break;case 'g':przesuniecie_y=i;break;case 'd':przesuniecie_y=-i;break;}Sleep(375/do_czego);}
                  }
                  nasza->zaktualizuj_widoki(x,y, sx, sy);

         }
         else
         {
                  if(czym_jest == 8) ((Sarna*)this)->na_ktorej_ost_bylem = nasza;
                  else if(czym_jest == 9) ((Niedzwiedz*)this)->na_ktorej_ost_bylem = nasza;

                  if(false)
                  {
                           brak_plansz:
                           nasza->otoczenie[y][x]=this;
                           przesuwamy=false;
                           if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" MMM ";
                           return fail;
                  }

                   int n_x=x,n_y=y;
                  switch(strona)
                  {case 'p':n_x=0;if(px+1<swiat->w_x)px++;else goto brak_plansz; break;
                  case 'l':n_x=20;if(px-1>=0)px--;else goto brak_plansz;break;
                  case 'g':n_y=12;if(py-1>=0)py--;else goto brak_plansz;break;
                  case 'd':n_y=0;if(py+1<swiat->w_y)py++;else goto brak_plansz;break;
                  default: goto brak_plansz;nasza->otoczenie[y][x]=this;przesuwamy=false;if(Objekt::args->melduj_co_robi_AI)std::cout<<" MMMM ";return fail;}
                  if(Objekt::args->melduj_co_robi_AI) std::cout<<"$7";
                  //Area *kol=swiat->zwroc_taka_aree(px,py,pz);


                  if(czym_jest==10 && swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->otoczenie[n_y][n_x]==NULL)
                  {
                           int r=swiat->promien_obszaru_zywego;
                           int i,dok,star;
                           if(strona=='p')i=px+r; else if(strona=='l') i=px-r;else if(strona=='g')i=py-r-1; else i=py+r+1;
                           if(strona=='p' || strona=='l') {star=py-r-1;dok=py+r+1;}  else {dok=px+r;star=px-r;}
                           for(int j=star; j<=dok; j++)
                           {
                                    int xx=j,yy=i; if(strona=='p' || strona=='l') {xx=i;yy=j;}
                                    if(yy>-1 && yy<swiat->w_y &&xx<swiat->w_x && xx>-1)
                                    {
                                             if(swiat->zwroc_taka_plansze(xx,yy,pz)==NULL)
                                             {
                                                      swiat->stworz_plansze(xx, yy, pz);
                                             }
                                    }
                           }
                           if(Objekt::args->melduj_co_robi_AI) std::cout<<"*";
                           if(strona=='p')i=px-r-1;else if(strona=='l') i=px+r+1;else if(strona=='g')i=py+r+2;else i=py-r-2;
                           for(int j=star; j<=dok; j++)
                           {
                                    int xx=j,yy=i; if(strona=='p' || strona=='l') {xx=i;yy=j;}
                                    if(yy>-1 && yy<swiat->w_y && xx<swiat->w_x && xx>-1)
                                    {
                                             if(swiat->zwroc_taka_aree(xx, yy, pz) && swiat->w_zasiegu_gracza(swiat->zwroc_taka_aree(xx, yy, pz)) && !swiat->zwroc_taka_aree(xx, yy, pz)->jest_plansza)
                                             {
                                                      swiat->stworz_plansze(xx, yy, pz);
                                                      if(kx==xx && ky==yy && kz==pz) dawna=swiat->zwroc_taka_aree(xx, yy, pz);
                                             }
                                             else if(swiat->zwroc_taka_aree(xx,yy,pz) && !swiat->w_zasiegu_gracza(swiat->zwroc_taka_aree(xx,yy,pz)) &&swiat->zwroc_taka_aree(xx,yy,pz)->jest_plansza)
                                             {
                                                      swiat->stworz_strefe(xx,yy,pz);
                                                      if(kx==xx && ky==yy && kz==pz) dawna=swiat->zwroc_taka_aree(xx,yy,pz);
                                             }
                                    }
                           }
                           if(Objekt::args->melduj_co_robi_AI) std::cout<<"*";

                           if(swiat->zwroc_taka_aree(px, py, pz)) swiat->zwroc_taka_aree(px, py, pz)->ma_gracza=true;
                           //std::cout<<px<<py<<pz<<std::endl;
                           //std::cout<<swiat->gracz->obiekt[0]->px<<swiat->gracz->obiekt[0]->py<<swiat->gracz->obiekt[0]->pz<<std::endl;
                           //std::cout<<dawna->x<<dawna->y<<dawna->z<<std::endl;

                           if(dawna)
                           {
                                    dawna->ma_gracza=false;
                                    for(int i=0; i<swiat->gracz->ilosc; i++) {if(swiat->gracz->obiekt[i]->px==dawna->x && swiat->gracz->obiekt[i]->py==dawna->y && swiat->gracz->obiekt[i]->pz==dawna->z){dawna->ma_gracza=true;}}
                           }
                           if(Objekt::args->melduj_co_robi_AI) std::cout<<"*";
                           swiat->jak_tam_wysypisko_plansz();

                  }
                  if(Objekt::args->melduj_co_robi_AI) std::cout<<"$8";
                  switch (czym_jest)
                  {
                           case 8: {Sarna*rzut=(Sarna*)this;rzut->pamiec=0;}break;
                           case 9: {Niedzwiedz*rzut=(Niedzwiedz*)this;rzut->pamiec=0;}break;
                           default:break;
                  }


                  if(swiat->zwroc_taka_aree(px, py, pz) && swiat->zwroc_taka_aree(px, py, pz)->jest_plansza && swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->otoczenie[n_y][n_x]==NULL)
                  {
                           if(czym_jest==8) {((Sarna*)this)->pamiec=0;}
                           Plansza*kolejna=NULL;

                           kolejna=swiat->zwroc_taka_plansze_TYLKO(px, py, pz);

                           kolejna->otoczenie[n_y][n_x]=this;
                           x=n_x; y=n_y;
                           if(Objekt::args->melduj_co_robi_AI) std::cout<<"$9";

                           if(kolejna->ma_gracza)
                           {
                                    swiat->Ustaw_aktualna(kolejna);
                                    for(int i=do_czego/2; i>=0; i--) {switch(strona)
                                    {case 'p':przesuniecie_x=-i;break;case 'l':przesuniecie_x=i;break;case 'g':przesuniecie_y=i;break;case 'd':przesuniecie_y=-i;break;}Sleep(375/do_czego);}
                           }
                           if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" PAKT ";
                           kolejna->zaktualizuj_widoki(x,y, x, y);
                           if(kolejna->ma_gracza) Sleep(500);

                           if(dawna->ma_gracza) swiat->Ustaw_aktualna(nasza);//////////
                           if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" DwaKT ";
                           if(dawna->jest_plansza){nasza->zaktualizuj_widoki(sx,sy, sx, sy);}
                           if(nasza->ma_gracza) Sleep(500);

                  }
                  else
                  {
                           nasza->otoczenie[y][x]=this;
                           przesuwamy=false;
                           px=kx, py=ky, pz=kz;
                  }


         }
         if(Objekt::args->melduj_co_robi_AI) std::cout<<" $3 ";
         przesuwamy=false; przesuniecie_x=0; przesuniecie_x=0;
         dzwiek_przesuniecia(x,y);

         if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" pm ";

         what_happened aaa = reakcja_na_podloze();
         if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" ak ";
         return aaa;
}

short Objekt::priorytet_w_srodowisku()///im mniejszy tym wiekszy
{
         switch(czym_jest)
         {
                  case 22: return 10;
                  case 24: return 5;
                  case 26: return 2;
                  case 27:return 1;
                  case 35: return 10;
                  case 36: return 10;
                  case 37: return 10;
                  case 100: return 10;
                  default: return 100;
         }
}

Objekt* Objekt::z_objektu_tymczasowego(Objekt_przejsciowy*a, int xx, int yy,int ppx, int ppy, int ppz)
{
         if(a == NULL) return NULL;
         Objekt *cos;
         switch(a->czym_jest)
         {

                  case 2:(cos=new Zombie((Zombie_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 8:(cos=new Sarna((Sarna_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 9:(cos=new Niedzwiedz((Niedzwiedz_przejsciowy*)a,xx,yy,ppx, ppy,ppz));break;
                  //case 11:return (cos=new Wilk((Wilk_przejsciowy*)a,xx,yy,ppx, ppy,ppz));
                  case 20: (cos=new Drzewo((Drzewo_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 21: (cos=new Woda((Woda_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 22: (cos=new Trawa((Trawa_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 23: (cos=new Schowek((Schowek_przejsciowy*)a,xx,yy,ppx, ppy,ppz));break;
                  case 24: (cos=new Ognisko((Ognisko_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 25: (cos=new Szalas((Szalas_przejsciowy*)a,xx,yy,ppx, ppy,ppz));break;
                  case 26: (cos=new Okno((Okno_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 27: (cos=new Drzwi((Drzwi_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 28: (cos=new Sciana((Sciana_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 29: (cos=new Krzeslo((Krzeslo_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 30: (cos=new Szafa((Szafa_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 31: (cos=new Stol((Stol_przejsciowy*)a,xx,yy,ppx, ppy,ppz));break;
                  case 32: (cos=new Lozko((Lozko_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  case 34: (cos=new Beczka((Beczka_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 35: (cos=new Zlamana_galaz((Zlamana_galaz_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 36: (cos=new Lampa((Lampa_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 37: (cos=new Reflektor((Reflektor_przejsciowy*)a,xx,yy,ppx, ppy,ppz));break;
                  case 38: (cos=new Staly((Staly_przejsciowy*)a,xx,yy,ppx, ppy,ppz));break;
                  case 39: (cos=new WLampa((WLampa_przejsciowa*)a,xx,yy,ppx, ppy,ppz));break;
                  case 100: (cos=new Zwloki((Zwloki_przejsciowe*)a,xx,yy,ppx, ppy,ppz));break;
                  default:{std::cout<<a->czym_jest<<" "<<"nie ma takiego obiektu"<<std::endl;throw "nie ma takiego obiektu";}
         }
         cos->stan = a->stan;
         return cos;
}

Objekt_przejsciowy* Objekt_przejsciowy::z_objektu(Objekt*a)
{
         if(a == NULL) return NULL;
         Objekt_przejsciowy *cos;
         switch(a->czym_jest)
         {
                  case 2:(cos=new Zombie_przejsciowe((Zombie*)a));break;
                  case 8:(cos=new Sarna_przejsciowa((Sarna*)a));break;
                  case 9:(cos=new Niedzwiedz_przejsciowy((Niedzwiedz*)a));break;
                  //case 11:return (cos=new Wilk_przejsciowy((Wilk*)a));
                  case 20:(cos=new Drzewo_przejsciowe((Drzewo*)a));break;
                  case 21:(cos=new Woda_przejsciowa((Woda*)a));break;
                  case 22:(cos=new Trawa_przejsciowa((Trawa*)a));break;
                  case 23:(cos=new Schowek_przejsciowy((Schowek*)a));break;
                  case 24:(cos=new Ognisko_przejsciowe((Ognisko*)a));break;
                  case 25:(cos=new Szalas_przejsciowy((Szalas*)a));break;
                  case 26:(cos=new Okno_przejsciowe((Okno*)a));break;
                  case 27:(cos=new Drzwi_przejsciowe((Drzwi*)a));break;
                  case 28:(cos=new Sciana_przejsciowa((Sciana*)a));break;
                  case 29:(cos=new Krzeslo_przejsciowe((Krzeslo*)a));break;
                  case 30:(cos=new Szafa_przejsciowa((Szafa*)a));break;
                  case 31:(cos=new Stol_przejsciowy((Stol*)a));break;
                  case 32:(cos=new Lozko_przejsciowe((Lozko*)a));break;
                  case 34:(cos=new Beczka_przejsciowa((Beczka*)a));break;
                  case 35:(cos=new Zlamana_galaz_przejsciowa((Zlamana_galaz*)a));break;
                  case 36:(cos=new Lampa_przejsciowa((Lampa*)a));break;
                  case 37:(cos=new Reflektor_przejsciowy((Reflektor*)a));break;
                  case 38:(cos=new Staly_przejsciowy((Staly*)a));break;
                  case 39:(cos=new WLampa_przejsciowa((WLampa*)a));break;
                  case 100:(cos=new Zwloki_przejsciowe((Zwloki*)a));break;
                  default: {std::cout<<a->czym_jest<<" "<<"nie ma takiego obiektu"<<std::endl;throw "nie ma takiego obiektu";}
         }
         cos->stan = a->stan;
         return cos;
}

zrodlo_swiatla Objekt::swiatlo()
{
         if(this==NULL) return zrodlo_swiatla(0,0);
         if(czym_jest==36 &&  ((Lampa*)this)->swieci()) return ((Lampa*)this)->jak_swieci();
         if(czym_jest==37 && ((Reflektor*)this)->swieci()) return ((Reflektor*)this)->jak_swieci();
         if(czym_jest==39 && ((WLampa*)this)->swieci()) return ((WLampa*)this)->jak_swieci();
         if(czym_jest==10)
         {
                  Gracz *g=(Gracz*)this;
                  if(g->p_rece!=NULL && g->p_rece->czym_jest==4012 && ((Bron*)(g->p_rece))->mag==1
                      && swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->to_jest_na_podlodze(x, y)) return zrodlo_swiatla(1, 38);
                  else if(g->p_ramie!=NULL && g->p_ramie->czym_jest==4012 && ((Bron*)(g->p_ramie))->mag==1
                      && swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->to_jest_na_podlodze(x, y)) return zrodlo_swiatla(1, 38);
                  else if(g->p_rece!=NULL && g->p_rece->czym_jest==2201) return zrodlo_swiatla(1, 70);
                  else if(g->p_kieszenl!=NULL && g->p_kieszenl->czym_jest==2201) return zrodlo_swiatla(1, 38);
                  else if(g->p_kieszenp!=NULL && g->p_kieszenp->czym_jest==2201) return zrodlo_swiatla(1, 38);
         }




         if(this->stan&1) return zrodlo_swiatla(1, 90, 33);
         return zrodlo_swiatla(0,0);
}

bool Objekt_martwy::rusz_sie()
{

}

void Objekt_martwy::uslysz_dzwiek(int dx,int dy,int rodzaj){}

void Objekt_martwy::uslysz_dzwiek(Plansza *a,int rodzaj){}

void Objekt_martwy::patrz(){};

void Objekt_pol_martwy::uslysz_dzwiek(int dx,int dy,int rodzaj){}

void Objekt_pol_martwy::uslysz_dzwiek(Plansza *a,int rodzaj){}

void Objekt_pol_martwy::patrz(){};

void Objekt::zbliz_lub_oddal(bool co_zrob, short xx, short yy)
{
        Plansza *pl = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
        if(pl->ma_gracza)
        {
                przesuniecie_x=0; przesuniecie_y=0;
                short do_czego=swiat->X;
                for(int i=0;i<=do_czego/2; i++)
                {
                                if(x<xx)
                                {
                                        przesuniecie_x=-i*(-1)*co_zrob;
                                }
                                else if(x>xx)
                                {
                                        przesuniecie_x=i*(-1)*co_zrob;
                                }

                                if(y<yy)
                                {
                                        przesuniecie_y=-i*(-1)*co_zrob;
                                }
                                else if(y>yy)
                                {
                                        przesuniecie_y=i*(-1)*co_zrob;
                                }
                        Sleep(375/do_czego);
                }
                 przesuniecie_x=0; przesuniecie_y=0;
        }
}

void Objekt::wyjdz_animacja(short xx, short yy)///wsp skad
{
        Plansza *pl = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
        if(pl->ma_gracza)
        {
                przesuniecie_x=0; przesuniecie_y=0;
                short do_czego=swiat->X;
                for(int i=do_czego/2;i>-1; i--)
                {
                        if(x<xx){przesuniecie_x=i;}
                        else if(x>xx) {przesuniecie_x=-i;}
                        if(y<yy)  {przesuniecie_y=i;}
                        else if(y>yy){przesuniecie_y=-i;}

                        Sleep(375/do_czego);
                }
                 przesuniecie_x=0; przesuniecie_y=0;
        }
}

inline double procent(double co, double ile) {int x=co, y=ile; x%=y; return x;}
bool wolna_prosta(planszowa<bool> o, int x1, int y1, int x2, int y2)
{
         if(y1/100==y2/100){
                  int wiekszy=x1/100, mniejszy=x2/100; if(x1/100<x2/100) {int g=wiekszy; wiekszy=mniejszy; mniejszy=g;}
                  for(int i=mniejszy+1; i<wiekszy; i++){if(o[y1/100][i])return false;}
         }
         else if(x1/100==x2/100){
                  int wiekszy=y1/100, mniejszy=y2/100; if(y1/100<y2/100) {int g=wiekszy; wiekszy=mniejszy; mniejszy=g;}
                  for(int i=mniejszy+1; i<wiekszy; i++){if(o[i][x1/100 ])return false;}
         }
         else
         {
                  if(x2<x1){int g=x1; x1=x2; x2=g; g=y1; y1=y2; y2=g;}
                  int BX1=x1/100,BX2=x2/100,BY1=y1/100,BY2=y2/100;
                  double X1=x1, X2=x2, Y1=y1, Y2=y2,a=(Y1-Y2)/(X1-X2),b=Y1-a*X1;
                  if(y1>y2)
                  {
                           double nx=BX1*100+100, z=a*nx+b;z=(z-(procent(z,100)))/100;
                           int zakres=z;
                           for(;zakres<BY1; zakres++) if(o[zakres][BX1]) return false;
                           nx=BX2*100; z=a*nx+b; z=(z-procent(z,100))/100;
                           zakres=z;
                           for(;zakres>BY2;zakres--) if(o[zakres][BX2]) return false;
                  }
                  else
                  {
                           double nx=BX2*100, z=a*nx+b; z=(z-procent(z,100))/100;
                           int zakres=z;
                           for(;zakres<BY2; zakres++) if(o[zakres][BX2]) return false;
                           nx=BX1*100+100; z=a*nx+b; z=(z-procent(z,100))/100;
                           zakres=z;
                           for(;zakres>BY1;zakres--) if(o[zakres][BX1]) return false;
                  }
                  for(int i=1; i<BX2-BX1;++i)
                  {
                           double nx1=BX1*100+i*100,nx2=nx1+100;
                           double ny1=a*nx1+b, ny2=a*nx2+b;
                           int j1=ny1, j2=ny2; j1/=100;j2=j2/100;
                           int wieksza=j1, mniejsza=j2; if(j2>j1) {int g=wieksza; wieksza=mniejsza; mniejsza=g;}
                           for(;mniejsza<=wieksza;++mniejsza) if(o[mniejsza][BX1+i]) return false;
                  }
         }
         return true;
}

bool Objekt_zywy::czy_widzi_wzgl_zwezania(int dx, int dy, int odciecia, int xw, int yw)///patrzac jak patrzy w gore dy to 2, chyba czy nie widzi ;)
{
         switch(zwrot)
         {
                  case 'p': return (yw>y+dx && xw>x+dy && xw-x-dy<odciecia+yw-dx-y)||(yw<y-dx && xw>x+dy && xw-x-dy<odciecia+y-yw-dx);
                  case 'l': return (yw>y+dx && xw<x-dy && x-xw-dy<odciecia+yw-dx-y)||(yw<y-dx && xw<x-dy && x-xw-dy<odciecia+y-yw-dx);
                  case 'g': return (yw<y-dy && xw>x+dx && y-yw-dy<odciecia+xw-x-dx)||(yw<y-dy && xw<x-dx && y-yw-dy<odciecia+x-xw-dx);
                  case 'd': return (yw>y+dy && xw>x+dx && yw-y-dy<odciecia+xw-x-dx)||(yw>y+dy && xw<x-dx && yw-y-dy<odciecia+x-xw-dx);
                  default:{std::cout<<"funkcja czy_widzi_wzgl_zwezania dostala zly zwrot"<<std::endl; throw "funkcja czy_widzi_wzgl_zwezania dostala zly zwrot";}
         }
}

bool Objekt::widzi_obiekt(const Plansza *p,const int xc, const int yc, const int xz, const int yz, int kamuflaz, int poprawka)
{
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" wt "<<xc<<" "<<yc<<'\n';
         if(p->srodowisko[yc][xc]!=NULL && p->otoczenie[yc][xc]!=NULL && p->otoczenie[yc][xc]->wysokosc<=p->srodowisko[yc][xc]->wysokosc() && odleglosc_w_kratkach(p->otoczenie[yc][xc])>0)
         {
                  if(Objekt::args->melduj_co_robi_AI)std::cout<<" we "<<'\n';
                  return false;
         }
         ///int poprawka=0; ///jak daleko od srodka rysujemy linie, do 48

         if(poprawka>48) poprawka=48; if(poprawka<0) poprawka=0;
         ///czy cos jest czy niena podst tab

         int najwx=xc,najmx=xz,najwy=yc,najmy=yz;

         if(najwx<najmx) {int g=najwx;najwx=najmx;najmx=g;}if(najwy<najmy) {int g=najwy;najwy=najmy;najmy=g;}///optymalizacja

         if(Objekt::args->melduj_co_robi_AI) std::cout<<" w0 "<<'\n';

         short wys = p->otoczenie[yc][xc] == NULL ? 0 : p->otoczenie[yc][xc]->wysokosc;
         for(int i=najmx; i<=najwx; i++)
                  {
                           for(int j=najmy;j<=najwy;j++)
                           {
                                    if(!Strefa::w_planszy(i, j)) {std::cout<<"widzi oviekt out of"; throw "D";}
                                    obstacles[j][i] = (p->otoczenie[j][i]!=NULL && p->otoczenie[j][i]->wysokosc>0 && wys<=p->otoczenie[j][i]->wysokosc)||
                                    (p->srodowisko[j][i]!=NULL && p->srodowisko[j][i]->wysokosc()>0 && wys<=p->srodowisko[j][i]->wysokosc()) ;
                           }
                  }
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" w1 "<<xc<<" "<<yc<<'\n';

         bool wynik;
         short dos = 25;
         if((xc==xz)||(yc==yz)) wynik=wolna_prosta(obstacles, xc*100+1, yc*100+1, xz*100+1,yz*100+1);

         else if(xz<xc && yz<yc) wynik=(wolna_prosta(obstacles, xc*100+99-poprawka,yc*100+1+poprawka, xz*100+50,yz*100+50)&&wolna_prosta(obstacles, xc*100+1+poprawka,yc*100+99-poprawka, xz*100+50,yz*100+50))||
                  (zwrot=='p' && wolna_prosta(obstacles, xc*100+50-poprawka,yc*100, xz*100+75-dos,yz*100+50)&&wolna_prosta(obstacles, xc*100+50+poprawka,yc*100, xz*100+75-dos,yz*100+50))||
                   (zwrot=='d' && wolna_prosta(obstacles, xc*100,yc*100+50-poprawka, xz*100+50,yz*100+75-dos)&&wolna_prosta(obstacles, xc*100,yc*100+50+poprawka, xz*100+50,yz*100+75-dos));

         else if(xz<xc && yz>yc) wynik=(wolna_prosta(obstacles, xc*100+1+poprawka,yc*100+1+poprawka, xz*100+50,yz*100+50)&&wolna_prosta(obstacles, xc*100+99-poprawka,yc*100+99-poprawka, xz*100+50,yz*100+50))||
                  (zwrot=='g' && wolna_prosta(obstacles, xc*100,yc*100+50-poprawka, xz*100+50,yz*100+25+dos)&&wolna_prosta(obstacles, xc*100,yc*100+50+poprawka, xz*100+50,yz*100+25+dos))||
                   (zwrot=='p' && wolna_prosta(obstacles, xc*100+50-poprawka,yc*100+100, xz*100+75-dos,yz*100+50)&&wolna_prosta(obstacles, xc*100+50+poprawka,yc*100+100, xz*100+75-dos,yz*100+50));

         else if(xz>xc && yz>yc) wynik=(wolna_prosta(obstacles, xc*100+99-poprawka,yc*100+1+poprawka, xz*100+50,yz*100+50)&&wolna_prosta(obstacles, xc*100+1+poprawka,yc*100+99-poprawka, xz*100+50,yz*100+50))||
                  (zwrot=='g' && wolna_prosta(obstacles, xc*100+100,yc*100+50-poprawka, xz*100+50,yz*100+25+dos)&&wolna_prosta(obstacles, xc*100+100,yc*100+50+poprawka, xz*100+50,yz*100+25+dos))||
                   (zwrot=='l' && wolna_prosta(obstacles, xc*100+50-poprawka,yc*100+100, xz*100+25+dos,yz*100+50)&&wolna_prosta(obstacles, xc*100+50+poprawka,yc*100+100, xz*100+25+dos,yz*100+50));

         else if(xz>xc && yz<yc) wynik=(wolna_prosta(obstacles, xc*100+1+poprawka,yc*100+1+poprawka, xz*100+50,yz*100+50)&&wolna_prosta(obstacles, xc*100+99-poprawka,yc*100+99-poprawka, xz*100+50,yz*100+50))||
                  (zwrot=='l' && wolna_prosta(obstacles, xc*100+50-poprawka,yc*100, xz*100+25+dos,yz*100+50)&&wolna_prosta(obstacles, xc*100+50+poprawka,yc*100, xz*100+25+dos,yz*100+50))||
                  (zwrot=='d' && wolna_prosta(obstacles, xc*100+100,yc*100+50-poprawka, xz*100+50,yz*100+75-dos)&&wolna_prosta(obstacles, xc*100+100,yc*100+50+poprawka, xz*100+50,yz*100+75-dos));

         //std::cout<<" ka "<<xc<<" "<<yc<<std::endl;
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" we "<<'\n';
         return wynik;
}

void Objekt::animacja_ataku(char strona)
{
         if(!swiat->zwroc_taka_aree(px,py,pz)->jest_plansza) return;
         if(!swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->ma_gracza) return;
         /*if(strona=='p') strona='l';
         else if(strona=='l') strona='p';
         else if(strona=='g') strona='d';
         else if(strona=='d') strona='g';*/
         int meta,wiekszy,do_czego;;
         if(strona=='x' || strona=='w' || strona=='z' || strona=='y')
         {
                  if(strona=='x' && zwrot!='p' && zwrot!='d') {if(zwrot=='g') zwrot='p'; else zwrot='l';}
                  else if(strona=='y' && zwrot!='p' && zwrot!='g') {if(zwrot=='d') zwrot='p'; else zwrot='g';}
                  else if(strona=='z' && zwrot!='g' && zwrot!='l') {if(zwrot=='p') zwrot='g'; else zwrot='l';}
                  else if(strona=='w' && zwrot!='d' && zwrot!='l') {if(zwrot=='g') zwrot='l'; else zwrot='d';}
                  meta=swiat->X; if(swiat->Y>swiat->X) meta=swiat->Y;
         }
         else
         {
                  zwrot=strona;
                  meta=swiat->X;if(strona=='g' || strona=='d') meta=swiat->Y;
         }
         przesuniecie_x=0; przesuniecie_y=0; przesuwamy=true;
         for(int i=0; i<meta/2; i++) {switch(strona)
         {case 'p':przesuniecie_x=i;break;case 'l':przesuniecie_x=-i;break;case 'g':przesuniecie_y=-i;break;case 'd':przesuniecie_y=i;break;
         case 'y':przesuniecie_x=i;przesuniecie_y=-i;break;case 'x':przesuniecie_x=i;przesuniecie_y=i;break;
         case 'w':przesuniecie_x=-i;przesuniecie_y=i;break;case 'z':przesuniecie_x=-i;przesuniecie_y=-i;break;
         }Sleep(375/meta);}
         przesuwamy=false;

         przesuwamy=true;
         for(int i=meta/2; i>=0; i--) {switch(strona)
         {case 'p':przesuniecie_x=i;break;case 'l':przesuniecie_x=-i;break;case 'g':przesuniecie_y=-i;break;case 'd':przesuniecie_y=i;break;
         case 'y':przesuniecie_x=i;przesuniecie_y=-i;break;case 'x':przesuniecie_x=i;przesuniecie_y=i;break;
         case 'w':przesuniecie_x=-i;przesuniecie_y=i;break;case 'z':przesuniecie_x=-i;przesuniecie_y=-i;break;
         }Sleep(375/meta);}
}

bool Objekt::jest_roslinozerca()
{
         return czym_jest == 8;
}

bool Objekt::jest_drapieznikiem()
{
         return czym_jest == 2 || czym_jest == 9 || czym_jest == 10;
}

short Objekt::srednia_odl_od_wrogow(Objekt **wr, short xx, short yy)
{
         if(wr == NULL) return 100;
         double ile = 0;
         double srednia = 0;
         for(int i=0; wr[i] != NULL; ++i)
         {
                  srednia += wr[i]->odleglosc_w_kratkach(xx, yy);
                  ++ile;
         }
         if(ile == 0) return 100;
         return (short)(srednia/ile);
}

Objekt** Objekt::zwroc_tablice_wrogow_z_tej_planszy()
{
         Plansza* p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         short ile = 0; short rozm = 10;
         Objekt **tab = new Objekt*[rozm];

         for(short i=0; i<13; ++i)
         {
                  for(short j=0; j<21; ++j)
                  {
                           if(p->otoczenie[i][j]!=NULL && p->otoczenie[i][j] != this && p->otoczenie[i][j]->jest_drapieznikiem())
                           {
                                    if(ile == rozm)
                                    {
                                             Objekt **b = new Objekt*[rozm*2]; rozm*=2;
                                             for(short i=0; i<ile; ++i) b[i] = tab[i];
                                             delete [] tab; tab = b;
                                    }
                                    tab[ile++] = p->otoczenie[i][j];
                           }
                  }
         }
         if(ile!=rozm+1)
         {
                  Objekt **b = new Objekt*[ile+1];
                  for(short i=0; i<ile; ++i) b[i] = tab[i];
                  delete [] tab; tab = b;
         }
         tab[ile] = NULL;
         return tab;
}

short Objekt::najblizszy_przeciwnik(short xx, short yy, Objekt **wr)
{
         short i;
         for(i = 1; i<10; ++i)
         {
                  for(short j=0; wr[j]!=NULL; ++j)
                  if(wr[j]->x>=xx-i && wr[j]->x<=xx+i && wr[j]->y>=yy-i && wr[j]->y<=yy+i)
                           return i;
         }
         return i;
}



void Objekt::zrownowaz_sciezki_wagowo(short ktory)///funkcja nie sprawdza czy mozna przejac d, ona jedynie rownowazy juz przejeta sciezke w wagach
{
         short k = 0;
         short t = 0;
         for(short i=1; i<300 && d[i].odn != -1; ++i)///do 1 sa tylko odnosniki, ona nie odnosi sie do niczego; &&; patrzymy tylko te uzyte
                  if(d[i].odn == ktory)
                  {
                           k = d[i].od_wrogow;
                           d[i].od_wrogow = d[i].od_wrogow_wlasny < d[ktory].od_wrogow ? d[i].od_wrogow_wlasny: d[ktory].od_wrogow;
                           if (k != d[i].od_wrogow) zrownowaz_sciezki_wagowo(i); ///rownowazymy wtedy, kiedy rzeczywiscie sie cos zmienilo
                           if(++t == 4) break;
                  }
}

zwrot_odl Objekt::wyznacz_punkt_ucieczki_w_obrebie_planszy()///zwraca tez jak blisko trzeba isc od wrogow zeby do niego dojsc
{
         Plansza *pl = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         bool **p = new bool*[13]; for(short i=0; i<13; ++i) p[i] = new bool[21];
         for(short i=0; i<13; ++i) for(short j=0; j<21; ++j) p[i][j] = pl->otoczenie[i][j] != NULL;
         Objekt **wrogowie = zwroc_tablice_wrogow_z_tej_planszy();
         //for(int i=0;wrogowie[i]!=NULL;++i) std::cout<<std::endl<<"WRUG: "<<wrogowie[i]->czym_jest<<std::endl;

         for(short i=0; i<300; ++i)///dla funckji zrownowaz...
                  d[i].odn = -1;

         int licznik_dla_n = 0; int ile=300;
         d[0].a=y; d[0].b=x; d[0].odn=0; int n=1,s=0,k=1;
         d[0].od_wrogow = Objekt::najblizszy_przeciwnik(x, y, wrogowie);

         bool lewo, prawo, dol, gora;
         short lewo_odl, prawo_odl, dol_odl, gora_odl;

         while(true)
         {
                  licznik_dla_n++;
                  if(licznik_dla_n==ile)
                  {break;}
                  for(int y=s; y<k; y++)
                  {
                           lewo=true,prawo=true,dol=true,gora=true;
                           lewo_odl=-1, prawo_odl=-1, dol_odl=-1, gora_odl=-1;

                           if(d[y].b+1<21 && p[d[y].a][d[y].b+1]==false)
                           {
                                    for (int u=n-1; u>-1; u--)
                                    {
                                             if(d[u].b==d[y].b+1 && d[u].a==d[y].a)///jesli zdarzy sie, ze cos tu jest to to przemianowujemy albo nie
                                             {
                                                      if(d[u].od_wrogow < (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow))
                                                      {
                                                               d[u].od_wrogow = (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow); d[u].odn = y;
                                                               zrownowaz_sciezki_wagowo(u);
                                                      }
                                                      prawo = false;
                                                      break;
                                             }
                                    }
                                    if(prawo)///jesli jednak nic nie bedzie to wstawiamy wlasny
                                    {
                                             prawo_odl = Objekt::najblizszy_przeciwnik(d[y].b+1, d[y].a, wrogowie);
                                             d[n].od_wrogow = d[y].od_wrogow > prawo_odl ? prawo_odl : d[y].od_wrogow;
                                             d[n].odn = y; d[n].a = d[y].a; d[n].b = d[y].b + 1;
                                             d[n].od_wrogow_wlasny = prawo_odl;
                                             n++;
                                    }
                           }
                           if(d[y].b-1>-1 && p[d[y].a][d[y].b-1]==false)
                           {
                                    for (int u=n-1; u>-1; u--)
                                    {
                                             if(d[u].b==d[y].b-1 && d[u].a==d[y].a)///jesli zdarzy sie, ze cos tu jest to to przemianowujemy albo nie
                                             {
                                                      if(d[u].od_wrogow < (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow))
                                                      {
                                                               d[u].od_wrogow = (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow); d[u].odn = y;
                                                               zrownowaz_sciezki_wagowo(u);
                                                      }
                                                      lewo = false;
                                                      break;
                                             }
                                    }
                                    if(lewo)///jesli jednak nic nie bedzie to wstawiamy wlasny
                                    {
                                             lewo_odl = Objekt::najblizszy_przeciwnik(d[y].b-1, d[y].a, wrogowie);
                                             d[n].od_wrogow = d[y].od_wrogow > lewo_odl ? lewo_odl : d[y].od_wrogow;
                                             d[n].odn = y; d[n].a = d[y].a; d[n].b = d[y].b - 1;
                                             d[n].od_wrogow_wlasny = lewo_odl;
                                             n++;
                                    }
                           }
                           if(d[y].a-1>-1 && p[d[y].a-1][d[y].b]==false)
                           {
                                    for (int u=n-1; u>-1; u--)
                                    {
                                             if(d[u].b==d[y].b && d[u].a==d[y].a-1)///jesli zdarzy sie, ze cos tu jest to to przemianowujemy albo nie
                                             {
                                                      if(d[u].od_wrogow < (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow))
                                                      {
                                                               d[u].od_wrogow = (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow); d[u].odn = y;
                                                               zrownowaz_sciezki_wagowo(u);
                                                      }
                                                      gora = false;
                                                      break;
                                             }
                                    }
                                    if(gora)///jesli jednak nic nie bedzie to wstawiamy wlasny
                                    {
                                             gora_odl = Objekt::najblizszy_przeciwnik(d[y].b, d[y].a-1, wrogowie);
                                             d[n].od_wrogow = d[y].od_wrogow > gora_odl ? gora_odl : d[y].od_wrogow;
                                             d[n].odn = y; d[n].a = d[y].a - 1; d[n].b = d[y].b;
                                             d[n].od_wrogow_wlasny = gora_odl;
                                             n++;
                                    }
                           }
                           if(d[y].a+1<13 && p[d[y].a+1][d[y].b]==false)
                           {
                                    for (int u=n-1; u>-1; u--)
                                    {
                                             if(d[u].b==d[y].b && d[u].a==d[y].a+1)///jesli zdarzy sie, ze cos tu jest to to przemianowujemy albo nie
                                             {
                                                      if(d[u].od_wrogow < (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow))
                                                      {
                                                               d[u].od_wrogow = (d[y].od_wrogow > d[u].od_wrogow_wlasny ? d[u].od_wrogow_wlasny : d[y].od_wrogow); d[u].odn = y;
                                                               zrownowaz_sciezki_wagowo(u);
                                                      }
                                                      dol = false;
                                                      break;
                                             }
                                    }
                                    if(dol)///jesli jednak nic nie bedzie to wstawiamy wlasny
                                    {
                                             dol_odl = Objekt::najblizszy_przeciwnik(d[y].b, d[y].a+1, wrogowie);
                                             d[n].od_wrogow = d[y].od_wrogow > dol_odl ? dol_odl : d[y].od_wrogow;
                                             d[n].odn = y; d[n].a = d[y].a + 1; d[n].b = d[y].b;
                                             d[n].od_wrogow_wlasny = dol_odl;
                                             n++;
                                    }
                           }
                  }
            s=k;k=n;
        }

         for(short i=0; i<13; ++i) delete [] p[i]; delete [] p;
    ///tu mamy poczatkowy zbior punktow c, w ilosci n-1

         short najw_odl = 0; ///wyznaczamy najdalsze od wrogow

         for(short i = 0; i<n-1; ++i) if(d[i].od_wrogow > najw_odl) najw_odl = d[i].od_wrogow;
         if(najw_odl == 0)
         {
                  delete [] wrogowie;
                  return zwrot_odl(-1, 0, -1);
         }
         short ucieczkowa_odl = najw_odl;

         for(short i = 0; i<n-1; ++i) if(d[i].od_wrogow < najw_odl) d[i].odn = -1;///odrzucamy te blizsze wrogow
         else d[i].od_wrogow = srednia_odl_od_wrogow(wrogowie, d[i].b, d[i].a);

         //std::cout<<std::endl<<"DDDD "<<n<<'\n'; /////////////////////////////////////////////////////////////////////////////////////////////
         //for(short i = 0; i<n-1; ++i) if(d[i].odn!=-1)std::cout<<d[i].odn<<" "<<d[i].od_wrogow<<" "<<d[i].b<<" "<<d[i].a<<std::endl; /////////////////////////////////////////////////////////////////////////////////////////////



         najw_odl = -1; ///zanzaczamy srednie odl
         for(short i = 0; i<n-1; ++i) if(d[i].odn != -1 && d[i].od_wrogow > najw_odl) najw_odl = d[i].od_wrogow;
         if(najw_odl == -1)
         {
                  delete [] wrogowie;
                  return zwrot_odl(0, 0, -1);
         }

         for(short i = 0; i<n-1; ++i) if(d[i].odn != -1 && d[i].od_wrogow < najw_odl) d[i].odn = -1; ///odrzucamy te gorsze w sredniej odl
         else d[i].od_wrogow = odleglosc_w_kratkach(d[i].b, d[i].a);

         //std::cout<<std::endl;
         //std::cout<<std::endl<<"DDDD "<<n<<'\n'; /////////////////////////////////////////////////////////////////////////////////////////////
         //for(short i = 0; i<n-1; ++i) if(d[i].odn!=-1) std::cout<<d[i].odn<<" "<<d[i].od_wrogow<<" "<<d[i].b<<" "<<d[i].a<<std::endl; /////////////////////////////////////////////////////////////////////////////////////////////


         najw_odl = 30; ///zanzaczamy srednie odl od sarenki, zmienna powinna sie nazywac najmniejsza odl ;)
         for(short i = 0; i<n-1; ++i) if(d[i].odn != -1 && d[i].od_wrogow < najw_odl) najw_odl = d[i].od_wrogow;
         if(najw_odl == 30)
         {
                  delete [] wrogowie;
                  return zwrot_odl(0, 0, -1);
         }
         for(short i = 0; i<n-1; ++i) if(d[i].odn != -1 && d[i].od_wrogow > najw_odl) d[i].odn = -1; ///odrzucamy te dalsze od sarenki

         //std::cout<<std::endl<<"DDDD "<<n<<'\n'; /////////////////////////////////////////////////////////////////////////////////////////////
        //for(short i = 0; i<n-1; ++i) if(d[i].odn!=-1) std::cout<<d[i].odn<<" "<<d[i].od_wrogow<<" "<<d[i].b<<" "<<d[i].a<<std::endl; /////////////////////////////////////////////////////////////////////////////////////////////


         short ktory = losuj(0, 299); ///tu zwykla czesc losujaca z tych, ktore zostaly
         zwrot_odl zwr(-1, -1, -1);
         for(short i = ktory; i<301; ++i)
         {
                  if(i==300) i=0;
                  if(d[i].odn != -1 && d[i].od_wrogow == najw_odl)
                  {
                           zwr.x = d[i].b; zwr.y = d[i].a; zwr.u = ucieczkowa_odl; break;
                  }
         }



         delete [] wrogowie;
         return zwr;
}

Plansza* Objekt::wyznacz_plansze_ucieczkowa(Plansza* tylko_nie_ta, bool mozna_niszcz)
{
         if(Objekt::args->melduj_co_robi_AI) std::cout<<" pip ";
         Plansza *taaa = NULL; bool mozna_niszczyc = false; short aaa;
         if(tylko_nie_ta == swiat->zwroc_taka_aree(px,py,pz)) {tylko_nie_ta = NULL;} ///takie zabezpieczenie niech juz bedzie

         moze_jednak_mozna_niszczyc:

         aaa = losuj(1,4);
         for(short t=0;t<2;++t)
         {
                  switch(aaa)
                  {
                           case 1:if(swiat->zwroc_taka_plansze(px+1, py, pz) && tylko_nie_ta !=swiat->zwroc_taka_plansze(px+1, py, pz) && jak_dojsc_na_plansze(swiat->zwroc_taka_plansze(px+1, py, pz), mozna_niszczyc)!='n'){taaa=swiat->zwroc_taka_plansze(px+1, py, pz);break;}
                           case 2:if(swiat->zwroc_taka_plansze(px-1, py, pz) && tylko_nie_ta !=swiat->zwroc_taka_plansze(px-1, py, pz) && jak_dojsc_na_plansze(swiat->zwroc_taka_plansze(px-1, py, pz), mozna_niszczyc)!='n'){taaa=swiat->zwroc_taka_plansze(px-1, py, pz);break;}
                           case 3:if(swiat->zwroc_taka_plansze(px, py+1, pz) && tylko_nie_ta !=swiat->zwroc_taka_plansze(px, py+1, pz) && jak_dojsc_na_plansze(swiat->zwroc_taka_plansze(px, py+1, pz), mozna_niszczyc)!='n'){taaa=swiat->zwroc_taka_plansze(px, py+1, pz);break;}
                           case 4:if(swiat->zwroc_taka_plansze(px, py-1, pz) && tylko_nie_ta !=swiat->zwroc_taka_plansze(px, py-1, pz) && jak_dojsc_na_plansze(swiat->zwroc_taka_plansze(px, py-1, pz) , mozna_niszczyc)!='n'){taaa=swiat->zwroc_taka_plansze(px, py-1, pz) ;break;}
                           break;
                  }
                  if(taaa!=NULL)break;
                  aaa=1;
         }

         if(taaa == NULL)
         {
                  if(tylko_nie_ta!=NULL && ((swiat->w_x>px+1 && tylko_nie_ta==swiat->zwroc_taka_aree(px+1, py,pz))
                                            ||(-1<px-1 && tylko_nie_ta==swiat->zwroc_taka_aree(px-1, py,pz))
                                             ||(swiat->w_y>py+1 && tylko_nie_ta==swiat->zwroc_taka_aree(px, py+1,pz))
                                            || (-1<py-1 && tylko_nie_ta==swiat->zwroc_taka_aree(px, py-1,pz)))
                      && tylko_nie_ta->jest_plansza && jak_dojsc_na_plansze(tylko_nie_ta, mozna_niszczyc)!='n')
                           {taaa=tylko_nie_ta;}
         }

         if(!taaa && mozna_niszcz && !mozna_niszczyc) {mozna_niszczyc = true; goto moze_jednak_mozna_niszczyc;}

         if(Objekt::args->melduj_co_robi_AI) std::cout<<" zip ";
         return taaa;
}

char Objekt::jak_dojsc_na_plansze(Plansza *pl_ucieczkowa, bool mozna_niszczyc_przedmioty)
{
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<" G ";
         if(pl_ucieczkowa==NULL) {std::cout<<" nie ma planszy a musze na nia isc ";throw "a";}
         Plansza*plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);

         punkt_na_planszy a,b;
         bool *wykluczone = NULL;

         char ktora_strona;
         if(pl_ucieczkowa->y<plansza->y)
         {
                  wykluczone = new bool[21];
                  a = punkt_na_planszy(0,0), b = punkt_na_planszy(20,0); ktora_strona = 'g';
                  for(short i = 0; i < 21; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[12][i]!=NULL;
         }
         else if(pl_ucieczkowa->y>plansza->y)
         {
                  wykluczone = new bool[21];
                  a = punkt_na_planszy(0,12), b = punkt_na_planszy(20,12); ktora_strona = 'd';
                  for(short i = 0; i < 21; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[0][i]!=NULL;
         }
         else if(pl_ucieczkowa->x<plansza->x)
         {
                  wykluczone = new bool[13];
                  a = punkt_na_planszy(0,0), b = punkt_na_planszy(0,12); ktora_strona = 'l';
                  for(short i = 0; i < 13; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[i][20]!=NULL;
         }
         else if(pl_ucieczkowa->x>plansza->x)
         {
                  wykluczone = new bool[13];
                  a = punkt_na_planszy(20,0); b = punkt_na_planszy(20,12); ktora_strona = 'p';
                  for(short i = 0; i < 13; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[i][0]!=NULL;
         }
         else {if(Objekt::args->melduj_co_robi_AI)std::cout<<" M ";return 'n';}

         if((ktora_strona == 'l' && x==0 && !wykluczone[y]) || (ktora_strona == 'p' && x==20 && !wykluczone[y]) ||
                  (ktora_strona == 'g' && y==0 && !wykluczone[x]) || (ktora_strona == 'd' && y==12 && !wykluczone[x]))
          {delete [] wykluczone;if(Objekt::args->melduj_co_robi_AI)std::cout<<" MM ";return ktora_strona;}

         bool **tab_widocznosci = new bool*[13]; for(short k = 0; k<13; ++k) tab_widocznosci[k] = new bool[21];
         for(short i = 0; i<13; ++i) for(short j=0; j<21; ++j) tab_widocznosci[i][j] = plansza->otoczenie[i][j] != NULL;

         /*if(px==1 && py==0)
         {std::cout<<"dojscie"<<std::endl<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<ktora_strona<<std::endl;
         for(short i=0;i<(ktora_strona == 'p' || ktora_strona =='l' ? 13 : 21);++i) std::cout<<wykluczone[i]<<" ";
         std::cout<<std::endl;
         for(int i=0;i<13;++i) {for(int j=0;j<21;++j) std::cout<<tab_widocznosci[i][j]<<" "; std::cout<<std::endl;}}*/

         char t = jak_dotrzec_do_obszaru(a, b, wykluczone, ktora_strona == 'p' || ktora_strona == 'l' ? false : true, tab_widocznosci);

         //std::cout<<t<<" ";

         if(t != 'n')
         {
                  for(short i = 0; i<13; ++i) delete [] tab_widocznosci[i]; delete [] tab_widocznosci;delete [] wykluczone;
                  if(Objekt::args->melduj_co_robi_AI)std::cout<<" MMM ";return t;
         }

         if(mozna_niszczyc_przedmioty)
         {
                  //for(int i=0;i<13;++i){for(int j=0;j<21;++j){tab_widocznosci[i][j]=plansza->otoczenie[i][j]!=NULL;}}
                  char f='n';int k=300;
                  while(true)
                  {
                           for(int i=0;i<13;i++)
                           {
                                    for(int j=0;j<21;j++)
                                    {
                                             if(plansza->otoczenie[i][j]==NULL) tab_widocznosci[i][j]=false;
                                             else
                                             {
                                                      /*(if(a->otoczenie[i][j]->czym_jest==26)
                                                      {
                                                               ///tab[i][j]=!wolna_prosta(tab_widocznosci,x*100+50,y*100+50,cx*100+50,cy*100+50);///////////
                                                      }*/
                                                      tab_widocznosci[i][j]=plansza->otoczenie[i][j]->na_ile_hp_wyglada()>k;
                                             }
                                    }
                           }
                           f=jak_dotrzec_do_obszaru(a, b, wykluczone, ktora_strona == 'p' || ktora_strona == 'l' ? false : true, tab_widocznosci);
                           if(f!='n')
                           {
                                    for(short i = 0; i<13; ++i) delete [] tab_widocznosci[i]; delete [] tab_widocznosci;delete [] wykluczone;
                                    if(Objekt::args->melduj_co_robi_AI)std::cout<<" MMMM ";return f;
                           }
                           if(k==300) k=600; else if(k==600) k=1000; else if(k==1000) k=10000; else break;
                  }
         }


         delete [] wykluczone;for(short i = 0; i<13; ++i) delete [] tab_widocznosci[i]; delete [] tab_widocznosci;
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" MMMMM ";
         return 'n';
}

char Objekt::jak_uciec_na_plansze(Plansza *pl_ucieczkowa)
{
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<" Gp ";
         if(pl_ucieczkowa==NULL) {std::cout<<" nie ma planszy a musze na nia isc ";throw "a";}
         Plansza*plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);

         punkt_na_planszy a,b;
         bool *wykluczone=NULL;

         char ktora_strona;
         if(pl_ucieczkowa->y<plansza->y)
         {
                  wykluczone = new bool[21];
                  a = punkt_na_planszy(0,0), b = punkt_na_planszy(20,0); ktora_strona = 'g';
                  for(short i = 0; i < 21; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[12][i]!=NULL;
         }
         else if(pl_ucieczkowa->y>plansza->y)
         {
                  wykluczone = new bool[21];
                  a = punkt_na_planszy(0,12), b = punkt_na_planszy(20,12); ktora_strona = 'd';
                  for(short i = 0; i < 21; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[0][i]!=NULL;
         }
         else if(pl_ucieczkowa->x<plansza->x)
         {
                  wykluczone = new bool[13];
                  a = punkt_na_planszy(0,0), b = punkt_na_planszy(0,12); ktora_strona = 'l';
                  for(short i = 0; i < 13; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[i][20]!=NULL;
         }
         else if(pl_ucieczkowa->x>plansza->x)
         {
                  wykluczone = new bool[13];
                  a = punkt_na_planszy(20,0); b = punkt_na_planszy(20,12); ktora_strona = 'p';
                  for(short i = 0; i < 13; ++i) wykluczone[i] = pl_ucieczkowa->otoczenie[i][0]!=NULL;
         }
         else {if(Objekt::args->melduj_co_robi_AI)std::cout<<" M ";return 'n';}

         if((ktora_strona == 'l' && x==0 && !wykluczone[y]) || (ktora_strona == 'p' && x==20 && !wykluczone[y]) ||
                  (ktora_strona == 'g' && y==0 && !wykluczone[x]) || (ktora_strona == 'd' && y==12 && !wykluczone[x]))
          {if(Objekt::args->melduj_co_robi_AI)std::cout<<" M ";delete [] wykluczone;return ktora_strona;}

         bool **tab_widocznosci = new bool*[13]; for(short k = 0; k<13; ++k) tab_widocznosci[k] = new bool[21];
         //for(short i = 0; i<13; ++i) for(short j=0; j<21; ++j) tab_widocznosci[i][j] = plansza->otoczenie[i][j]!= NULL;

         for(short k=3; k>=0; --k)
         {
                  for(int i=0;i<13;i++){for(int j=0;j<21;j++){tab_widocznosci[i][j]=false;}}
                  for(int i=0;i<13;i++)
                  {
                           for(int j=0;j<21;j++)
                           {
                                    //tab_widocznosci[i][j]=plansza->otoczenie[i][j]!=NULL;
                                    if(plansza->otoczenie[i][j]!=NULL)
                                    {
                                             tab_widocznosci[i][j]=true;
                                             if(plansza->otoczenie[i][j]->zywy && plansza->otoczenie[i][j]->czym_jest!=8)///nikt nie boi sie sarn
                                             {
                                                      for(int g=i-k; g<=i+k; ++g)
                                                      {
                                                               for(int f=j-k; f<=j+k; ++f)
                                                               {
                                                                        if(g>-1 && g<13 && f>-1 && f<21)tab_widocznosci[g][f]=true;
                                                               }
                                                      }
                                             }
                                    }
                           }
                  }
                  /*if(k==0)
                  {
                           for(short i = 0; i<13; ++i) for(short j=0; j<21; ++j)
                           if(tab_widocznosci[i][j] != (plansza->otoczenie[i][j] ! = NULL))
                           {
                                    std::cout<<"NIE ZGADZA SIE"; throw "F";
                           }
                  }*/

         /*if(px==1 && py==0)
          {std::cout<<"ucieczka"<<std::endl<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<ktora_strona<<std::endl;
                                    for(short i=0;i<(ktora_strona == 'p' || ktora_strona =='l' ? 13 : 21);++i) std::cout<<wykluczone[i]<<" ";
                                    std::cout<<std::endl;
                                    for(int i=0;i<13;++i) {for(int j=0;j<21;++j) std::cout<<tab_widocznosci[i][j]<<" "; std::cout<<std::endl;}}*/

                  char gdzie = jak_dotrzec_do_obszaru(a, b, wykluczone, ktora_strona == 'p' || ktora_strona == 'l' ? false : true, tab_widocznosci);

                  //std::cout<<std::endl<<gdzie<<" "<<k<<" "<<x<<" "<<y<<std::endl;
                  /*if(k==0)
                  {
                           char d = jak_dojsc_na_plansze(pl_ucieczkowa, false);
                           if(d!=gdzie)
                           {
                                    std::cout<<"DASDSADAD"<<std::endl;

                                    std::cout<<"ucieczka"<<std::endl<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<ktora_strona<<std::endl;
                                    for(short i=0;i<(ktora_strona == 'p' || ktora_strona =='l' ? 13 : 21);++i) std::cout<<wykluczone[i]<<" ";
                                    std::cout<<std::endl;
                                    std::cout<<jak_dotrzec_do_obszaru(a, b, wykluczone, ktora_strona == 'p' || ktora_strona == 'l' ? false : true, tab_widocznosci);
                                    std::cout<<std::endl;
                                    std::cout<<jak_dotrzec_do_obszaru(a, b, wykluczone, ktora_strona == 'p' || ktora_strona == 'l' ? false : true, tab_widocznosci);
                                    std::cout<<std::endl;

                                    std::cout<<jak_dotrzec_do_obszaru(a, b, wykluczone, ktora_strona == 'p' || ktora_strona == 'l' ? false : true, tab_widocznosci);
                                    std::cout<<std::endl;
                                    std::cout<<d;



                                    throw "H";
                           }
                  }*/




                  if(gdzie!='n')
                  {
                           for(short i = 0; i<13; ++i) delete [] tab_widocznosci[i]; delete [] tab_widocznosci;delete [] wykluczone;
                           if(Objekt::args->melduj_co_robi_AI)std::cout<<" M ";

                           /*if((gdzie=='p'&&x==20&&((Plansza*)swiat->area[px+1][py][pz])->otoczenie[y][0]!=NULL)
                                    ||(gdzie=='l'&&x==0&&((Plansza*)swiat->area[px-1][py][pz])->otoczenie[y][20]!=NULL)
                                    ||(gdzie=='d'&&y==12&&((Plansza*)swiat->area[px][py+1][pz])->otoczenie[0][x]!=NULL)
                                    ||(gdzie=='g'&&y==0&&((Plansza*)swiat->area[px][py-1][pz])->otoczenie[12][x]!=NULL))
                           {
                                    std::cout<<"UUHUUUHUHUHU";throw "G";
                           }*/
                           return gdzie;
                  }
         }

         if(Objekt::args->melduj_co_robi_AI)std::cout<<" M ";
         delete [] wykluczone;for(short i = 0; i<13; ++i) delete [] tab_widocznosci[i]; delete [] tab_widocznosci;return 'n';
}

bool Objekt::w_obszarze_i_niewykluczony(short x, short y, punkt_na_planszy a, punkt_na_planszy b, bool *punkty, bool po_szer)
{
         return x >= a.x && x <= b.x && y >= a.y && y <=b.y && ((po_szer && !punkty[x]) || (!po_szer && !punkty[y]));
}

char Objekt::jak_dotrzec_do_obszaru(punkt_na_planszy f, punkt_na_planszy g, bool*w, bool po_szer, bool **p)
{///wykluczone punkty beda traktowane wylacznie jako oznaka checi przejscai na inna plansze
         short ppy = y, ppx = x;
         if(f.x > g.x) {punkt_na_planszy b = f; f = g; g = b;}
         if(f.y > g.y) {short b = f.y; f.y = g.y; g.y = b;}

         if(w_obszarze_i_niewykluczony(ppx, ppy, f, g, w, po_szer)) return 'n';
         if(w_obszarze_i_niewykluczony(ppx+1, ppy, f, g, w, po_szer) && p[ppy][ppx+1]==false)return 'p';
         if(w_obszarze_i_niewykluczony(ppx-1, ppy, f, g, w, po_szer) && p[ppy][ppx-1]==false)return 'l';
         if(w_obszarze_i_niewykluczony(ppx, ppy+1, f, g, w, po_szer) && p[ppy+1][ppx]==false)return 'd';
         if(w_obszarze_i_niewykluczony(ppx, ppy-1, f, g, w, po_szer) && p[ppy-1][ppx]==false)return 'g';
         //if(w_obszarze_i_niewykluczony(ppx, ppy, f, g, w, po_szer)cx==ppx+2 && cy==ppy)return'p';
         //else if(cx==ppx-2 && cy==ppy)return'l';

         int licznik_dla_n=0;int ile=300;
         c[0].a=ppy;c[0].b=ppx;c[0].odn=0;int n=1,s=0,k=1;bool endd=false;

         while(true)
         {
                  licznik_dla_n++;if(licznik_dla_n==ile){return 'n';}
                  for(int y=s;y<k;y++)
                  {
                           bool lewo=true,prawo=true,dol=true,gora=true;
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b+1 && c[u].a==c[y].a){prawo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b-1 && c[u].a==c[y].a){lewo=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a-1){gora=false;break;}}
                           for (int u=n-1;u>-1;u--) {if(c[u].b==c[y].b && c[u].a==c[y].a+1){dol=false;break;}}
                           if (c[y].b+1<21 && prawo && (p[c[y].a][c[y].b+1]==false/* || c[y].a==cy && c[y].b+1==cx*/))
                  {
                           c[n].odn=y;c[n].a=c[y].a;c[n].b=c[y].b+1; if (w_obszarze_i_niewykluczony(c[n].b, c[n].a, f, g, w, po_szer))
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
                if (c[y].b-1>-1 && lewo && (p[c[y].a][c[y].b-1]==false/* || c[y].a==cy && c[y].b-1==cx*/))
                    {
                           c[n].odn=y;c[n].a=c[y].a;c[n].b=c[y].b-1; if (w_obszarze_i_niewykluczony(c[n].b, c[n].a, f, g, w, po_szer))
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
                if (c[y].a-1>-1 && gora && (p[c[y].a-1][c[y].b]==false/* || c[y].a-1==cy && c[y].b==cx*/))
                    {
                           c[n].odn=y;c[n].a=c[y].a-1;c[n].b=c[y].b; if (w_obszarze_i_niewykluczony(c[n].b, c[n].a, f, g, w, po_szer))
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
                if (c[y].a+1<13 && dol && (p[c[y].a+1][c[y].b]==false/* || c[y].a+1==cy && c[y].b==cx*/))
                    {
                           c[n].odn=y;c[n].a=c[y].a+1;c[n].b=c[y].b; if (w_obszarze_i_niewykluczony(c[n].b, c[n].a, f, g, w, po_szer))
                           {int i=0;z[0]=c[n];int h=c[n].odn;for (int u=1;u>0;u++) {z[u]=c[h];h=c[h].odn; if (h==0) {i=u;break;}}
                           if (z[i].a==c[0].a && z[i].b==c[0].b+1) {return 'p';}
                           if (z[i].a==c[0].a && z[i].b==c[0].b-1) {return 'l';}
                           if (z[i].a==c[0].a-1 && z[i].b==c[0].b) {return 'g';}
                           if (z[i].a==c[0].a+1 && z[i].b==c[0].b) {return 'd';}
                    }n++;}
            }
            s=k;k=n;if (endd) break;
        }
    return 'n';
}

void Objekt::animacja_damage(int a)
{
         if((swiat->zwroc_taka_aree(px,py,pz) && !swiat->zwroc_taka_aree(px,py,pz)->jest_plansza)||(!swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->ma_gracza)||swiat->aktualna->x!=px || swiat->aktualna->y!=py || swiat->aktualna->z!=pz) return;
         args->obrazenia=new int(a);
         args->gdzie_obrazenia=new struct punkt; args->gdzie_obrazenia->x=x*args->X_kratka;args->gdzie_obrazenia->y=y*args->Y_kratka+args->Y_kratka/2;
         args->ilosc_zadan=1;
         for(args->ile_nad=0;args->ile_nad<args->X_kratka;++args->ile_nad)Sleep(500/args->X_kratka);
         args->ilosc_zadan=0;
         delete args->obrazenia; delete args->gdzie_obrazenia;
}

void Objekt::animacja_obrazen()
{/*return;
         if(!swiat->area[px][py][pz]->jest_plansza) return;
         if(!((Plansza*)swiat->area[px][py][pz])->ma_gracza) return;
         args->obrazenia=new int(4);
         struct punkt* gdzie_obrazenia;
         int ile_nad;
         int ilosc_zadan;
         bool zadajemy;*/
}

double odl_miedzy_p(double x1,double y1,double x2,double y2)
{
         return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

double f(double a, double b, double x)
{
         return a*x+b;
}

void Objekt::animacja_rzutu_przedmiotu(dla_grafiki*args,double xx, double yy, Item*aaa)
{
         int pred=50; ///predkosc na kratke w ms
         double pr;
         xx*=args->X_kratka; yy*=args->Y_kratka;

         double X=x*args->X_kratka, Y=y*args->Y_kratka,xp=x*args->X_kratka, yp=y*args->Y_kratka;

         ++X;++yy;

         double c,d,a=xx,b=yy,r;
         c=(yy-Y)/(xx-X); d=Y-c*X;

         double x1,x2,delta, pom1=pow(2*c*d-2*b*c-2*a,2),pom2=4*(1+c*c),pom3=a*a+d*d-2*b*d+b*b;
         double l1=-2*c*d+2*b*c+2*a,l2=2+2*c*c;



         args->rzucana_bron_kat=0;///wyznaczanie kata
         double M_PI = 3.14159265359;
         double wsp_a = 1, wsp_b=Y-X; ///dla linii oryginalnej rotacji objektu z lewa na prawo dol
         double wsp_a2 = -1, wsp_b2=Y+X; ///dla linii oryginalnej rotacji objektu
         double tangens = ((c-wsp_a)/(1+wsp_a*c));
         if(tangens<0) tangens*=-1;

         double alfa = atan(tangens), beta= M_PI - alfa; if(beta<alfa) {double f =beta; beta=alfa; alfa=f;}
         short strefa=1;
         if(f(wsp_a, wsp_b, xx)>=yy)
         {
                  if(f(wsp_a2,wsp_b2,xx)>=yy)
                  {
                           strefa = 1;
                  }
                  else
                  {
                           strefa = 2;
                  }
         }
         else
         {
                  if(f(wsp_a2,wsp_b2,xx)>=yy)
                  {
                           strefa = 4;
                  }
                  else
                  {
                           strefa = 3;
                  }
         }
         switch(strefa)
         {
                  case 1: args->rzucana_bron_kat=alfa; break;
                  case 2: args->rzucana_bron_kat=beta; break;
                  case 3: args->rzucana_bron_kat=M_PI+alfa; break;
                  case 4: args->rzucana_bron_kat=M_PI+beta; break;
         }



         args->rzucana_bron_id=aaa->czym_jest;
         for(double r_kwadrat=pow(odl_miedzy_p(xx,yy,X,Y),2); r_kwadrat>0;)
         {
                  delta=pom1-pom2*(pom3-r_kwadrat);
                  x1=(l1-sqrt(delta))/l2;
                  x2=(l1+sqrt(delta))/l2;

                  if(odl_miedzy_p(x1,d+c*x1, xp,yp)>odl_miedzy_p(x2,d+c*x2, xp,yp)) X=x2; else X=x1;
                  Y=X*c+d;
                  args->rzucana_bron_x=X+args->X_kratka/2;args->rzucana_bron_y=Y+args->Y_kratka/2;
                  r=sqrt(r_kwadrat); r-=5; if(r<0) r=0; r_kwadrat=r*r;

                  pr=ceil(pred/args->X_kratka); if(pr<2) pr=2; Sleep(pr);
         }

         args->rzucana_bron_id=0;
}

void Objekt::powstan()
{
         if(czym_jest==2) {((Zombie*)this)->lezy=false;}
}

bool Objekt_zywy::ma_tyle_i_odejmij(short &skad, short ile)
{
         if(skad-ile<0) return false;
         skad-=ile;
         return true;
}

void Objekt::przewroc()
{
         Plansza*p=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(czym_jest==2) {p->dodaj_upadlego(this, x, y);p->otoczenie[y][x]=NULL;((Zombie*)this)->lezy=true;}
         else if(czym_jest==34) {((Beczka*)p->otoczenie[y][x])->przewroc_mnie(zwrot);}
         p->zaktualizuj_widoki(x,y,x,y);
}

bool Objekt::jest_zaraz_obok(Objekt*a)
{
         return x-1<=a->x && y-1<=a->y && x+1>=a->x && y+1>=a->y;
}

int Objekt::odleglosc_w_kratkach(Objekt*a)
{
         int suma; if(a->x>x)suma=a->x-x;else suma=x-a->x; if(a->y>y)suma+=a->y-y;else suma+=y-a->y; return suma;
}

int Objekt::odleglosc_w_kratkach(short xx, short yy)
{
         short suma; if(xx>x)suma=xx-x;else suma=x-xx; if(yy>y)suma+=yy-y;else suma+=y-yy; return suma;
}

short Objekt::odleglosc_w_kratkach(short xx, short yy, short cx, short cy)
{
         short suma; if(xx>cx)suma=xx-cx;else suma=cx-xx; if(yy>cy)suma+=yy-cy;else suma+=cy-yy; return suma;
}

void Objekt::animacja_strzalu(int x1, int y1, int x2, int y2, int szerokosc)
{
         if(swiat->zwroc_taka_aree(px,py,pz) && !swiat->zwroc_taka_aree(px,py,pz)->jest_plansza) return;
         if(!swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->ma_gracza) return;
         args->x1=x1;args->x2=x2;args->y1=y1;args->y2=y2;
         args->szerokosc=szerokosc;
         args->prosta=true;
         Sleep(100);
         args->prosta=false;
}

bool Objekt::mozna_strzelic(Objekt*a)
{
         Plansza*p=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         planszowa<bool> o = obstacles;
         for(int i=0; i<13; ++i)
         {
                  //std::cout<<std::endl;
                  for(int j=0;j<21;++j)
                  {
                           if(p->otoczenie[i][j]!=NULL &&(p->otoczenie[i][j]->wysokosc>=wysokosc || p->otoczenie[i][j]->wysokosc>=a->wysokosc))
                                    o[i][j]=true;
                           else o[i][j]=false;
                           //std::cout<<o[i][j]<<" ";

                  }
         }
         //o[y][x]=false;o[a->y][a->x]=false;


         bool aaaaa=wolna_prosta(o,x*100+50, y*100+50, a->x*100+50,a->y*100+50);//std::cout<<std::endl<<aaaaa<<" "<<x*100+50<<" "<< y*100+50<<" "<< a->x*100+50<<" "<<a->y*100+50<<std::endl;
         return aaaaa;


}

bool Objekt::mozna_rzucic(short xx, short yy)
{
         Plansza*p=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         planszowa<bool> o = obstacles;
         for(int i=0; i<13; ++i)
         {
                  //std::cout<<std::endl;
                  for(int j=0;j<21;++j)
                  {
                           if(p->otoczenie[i][j]!=NULL &&(p->otoczenie[i][j]->wysokosc>=wysokosc || p->otoczenie[i][j]->wysokosc>=3))
                                    o[i][j]=true;
                           else o[i][j]=false;
                           //std::cout<<o[i][j]<<" ";

                  }
         }
         //o[y][x]=false;o[a->y][a->x]=false;


         bool aaaaa=wolna_prosta(o,x*100+50, y*100+50, xx*100+50,yy*100+50);//std::cout<<std::endl<<aaaaa<<" "<<x*100+50<<" "<< y*100+50<<" "<< a->x*100+50<<" "<<a->y*100+50<<std::endl;
         return aaaaa || (!p->to_jest_na_podlodze(xx, yy) && !p->to_jest_na_podlodze(x, y));
}

void Objekt::animacja_bycia_uderzanym_jak_drzewo(int hpp,int obrazenia,int max_hp)
{
         if(swiat->zwroc_taka_aree(px,py,pz) && swiat->zwroc_taka_aree(px,py,pz)->ma_gracza){args->plansza1->otoczenie[y+1][x+1][1]=hpp*100/max_hp; Sleep(300);animacja_damage(obrazenia);}
         hpp-=obrazenia; if(hpp<0) hpp=0;
         if(swiat->zwroc_taka_aree(px,py,pz) && swiat->zwroc_taka_aree(px,py,pz)->ma_gracza){args->plansza1->otoczenie[y+1][x+1][1]=hpp*100/max_hp;Sleep(400);args->plansza1->otoczenie[y+1][x+1][1]=-1;}
}

int Objekt::bycie_uderzanym_jak_drzewo(int hpp,int obrazenia,int max_hp)
{
         if(!Objekt::wstrzymaj_animacje) animacja_bycia_uderzanym_jak_drzewo(hpp,obrazenia,max_hp);
         hpp -= obrazenia;
         if(hpp<=0)
         {
                  if(swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]==this)swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]=NULL;
                  //if(((Plansza*)swiat->area[px][py][pz])->srodowisko[y][x]->ma_to(this))((Plansza*)swiat->area[px][py][pz])->srodowisko[y][x]->usun_objekt(this);
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->zaktualizuj_widoki(x,y,x,y);
                  return 0;
         }
         else return hpp;
}

bool Objekt::da_sie_dojsc(int xc, int yc, int x, int y, Plansza*a)
{
         if(xc==x && yc==y) return true;
         bool t[13][21];
         for(int i=0;i<13;++i){for(int j=0;j<21;++j){t[i][j]=a->otoczenie[i][j]!=NULL;}}
         return gdzie_isc(xc,yc,x,y,t)!='n';
}

/*struct punkt Objekt_zywy::gdzie_na_plansze(Plansza* a)
{
         throw "d";
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<"Gdzie ta plansza";
         if(a==NULL) {std::cout<<"nie ma planszy a musze na nia isc";throw "a";}
         Plansza*plansza=(Plansza*)swiat->area[px][py][pz];
         int _x, _y;
         char ktora_strona;
         if(a->y<plansza->y) ktora_strona='g';
         else if(a->y>plansza->y) ktora_strona='d';
         else if(a->x<plansza->x) ktora_strona='l';
         else if(a->x>plansza->x) ktora_strona='p';
         switch(ktora_strona){case'p':{_x=21;_y=y;break;}case'l':{_x=-1;_y=y;break;}case'd':{_x=x;_y=13;break;}case'g':{_x=x;_y=-1;break;}}
         bool udalo_sie=false;
         if(ktora_strona=='g' || ktora_strona=='d')
         {
                  for(int i=0;i<23;i++) {int yy=_y;if(yy==-1) yy=0;if(yy==13)yy=12;if(_x+i<21 && (plansza->otoczenie[yy][_x+i]==NULL||(yy==y && _x+i==x)) && ((ktora_strona=='g' && a->otoczenie[12][_x+i]==NULL)||(ktora_strona=='d' && a->otoczenie[0][_x+i]==NULL)) && ((yy==y && _x+i==x)||da_sie_dojsc(_x+i,yy,x,y,plansza))) {_x+=i;udalo_sie=true;break;}
                  if(_x-i>-1 && (plansza->otoczenie[yy][_x-i]==NULL || (yy==y && _x-i==x))&&((ktora_strona=='g' && a->otoczenie[12][_x-i]==NULL)||(ktora_strona=='d' && a->otoczenie[0][_x-i]==NULL)) && ((yy==y && _x-i==x)||da_sie_dojsc(_x-i,yy,x,y,plansza))) {_x-=i;udalo_sie=true;break;}}
         }
         else if(ktora_strona=='l' || ktora_strona=='p')
         {
                  for(int i=0;i<15;i++) {int xx=_x;if(xx==-1) xx=0;if(xx==21)xx=20;if(_y+i<13 && (plansza->otoczenie[_y+i][xx]==NULL||(_y+i==y && xx==x))&&((ktora_strona=='p' && a->otoczenie[_y+i][0]==NULL)||(ktora_strona=='l' && a->otoczenie[_y+i][20]==NULL)) && ((xx==x && _y+i==y)||da_sie_dojsc(xx,_y+i,x,y,plansza))) {_y+=i;udalo_sie=true;break;}
                  if(_y-i>-1 && (plansza->otoczenie[_y-i][xx]==NULL || (_y-i==y && xx==x))&&((ktora_strona=='p' && a->otoczenie[_y-i][0]==NULL)||(ktora_strona=='l' && a->otoczenie[_y-i][20]==NULL)) && ((xx==x && _y-i==y)||da_sie_dojsc(xx,_y-i,x,y,plansza))) {_y-=i;udalo_sie=true;break;}}
         }
         struct punkt r; r.x=_x; r.y=_y;
         if(Objekt::args->melduj_co_robi_AI)
         std::cout<<"Tu ta plansza";
         return r;
}*/

void Objekt_zywy::przestan_byc_ofiara(int promien_plansz=1, short xxc, short yyc)
{
         int xx=px, yy=py;
         for(int j=xx-promien_plansz; j<=xx+promien_plansz; ++j)
         {
                  for(int i=yy-promien_plansz; i<=yy+promien_plansz; ++i)
                  {
                           if(swiat->zwroc_taka_plansze(j,i,pz))
                           {
                                    Plansza*a=swiat->zwroc_taka_plansze(j,i,pz);
                                    for(int v=0;v<21;++v)
                                    {
                                             for(int w=0;w<13;++w)
                                             {
                                                      if(a->otoczenie[w][v]!=NULL && a->otoczenie[w][v]->zywy)
                                                      {
                                                               if(((Objekt_zywy*)a->otoczenie[w][v])->ofiara==this)
                                                               {
                                                                        Objekt_zywy*c=(Objekt_zywy*)a->otoczenie[w][v];
                                                                        c->ofiara=NULL;
                                                                        c->jest_ofiara=false;
                                                                        c->jest_cel=true;
                                                                        if(a!=swiat->zwroc_taka_plansze_TYLKO(px,py,pz))
                                                                        {
                                                                                 c->celem_jest_plansza=true; c->ktora_plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
                                                                        }
                                                                        else if(xxc != -1 && yyc !=-1)
                                                                        {
                                                                                 c->celem_jest_plansza=false; c->xc=xxc; c->yc=yyc;
                                                                        }
                                                                        else
                                                                        {
                                                                                 c->celem_jest_plansza=false; c->xc=x; c->yc=y;
                                                                        }
                                                               }
                                                      }
                                             }
                                    }
                           }
                  }
         }
}

char skrec(char gdzie, char zwrot){if(gdzie=='p')
switch(zwrot){case 'p':return 'd';case 'd':return 'l';case 'l':return 'g';case 'g':return 'p';break;default:{std::cout<<"funkcja skrec dostala zly zwrot"<<zwrot<<" "<<gdzie<<std::endl; throw "funkcja skrec dostala zly zwrot";}}
else if (gdzie=='l')switch(zwrot){case 'p':return 'g';case 'g':return 'l';case 'l':return 'd';case 'd':return 'p';break;default:{std::cout<<"funkcja skrec dostala zly zwrot"<<zwrot<<" "<<gdzie<<std::endl; throw "funkcja skrec dostala zly zwrot";}}
else if (gdzie=='z')switch(zwrot){case 'p':return 'l';case 'g':return 'd';case 'l':return 'p';case 'd':return 'g';break;default:{std::cout<<"funkcja skrec dostala zly zwrot "<<zwrot<<" "<<gdzie<<std::endl; throw "funkcja skrec dostala zly zwrot";}}
else {std::cout<<"funkcja skrec dostala zly gdzie"<<zwrot<<" "<<gdzie<<std::endl; throw "funkcja skrec dostala zly gdzie";}}

struct punkt punkt_przed(char zwrot, int x, int y) {struct punkt p;p.x=x;p.y=y;
switch (zwrot){case 'p':++p.x;break;case 'l':--p.x;break;case 'g':--p.y;break;case 'd':++p.y;break;
case 'z':--p.x;--p.y;break;case 'y':++p.x;--p.y;break;case 'w':--p.x;++p.y;break;case 'x':++p.x;++p.y;break;}return p;}

char w_ktora_to_strone(int x, int y, int xc, int yc)
{
         if(y==yc&&x+1==xc) return 'p'; else if(y==yc&&x-1==xc) return 'l';
         else if(x==xc&&y+1==yc) return 'd'; else if(x==xc&&y-1==yc) return 'g';
         else if(x+1==xc&&y+1==yc)return 'x'; else if(x+1==xc&&y-1==yc)return 'y';
         else if(x-1==xc&&y+1==yc)return 'w'; else if(x-1==xc&&y-1==yc)return 'z';
         else if(y==yc) {if(x<xc) return 'p'; else if(x>xc) return 'l';}
         else if(x==xc) {if(y<yc) return 'd'; else if(y>yc) return 'g';}
         return 'n';
}

bool Objekt::ktos_ma_go_za_ofiare(Plansza*p)
{
         for(int i=0;i<21;++i)
         {
                  for(int j=0;j<13;++j)
                  {
                           if(p->otoczenie[j][i]!=NULL && p->otoczenie[j][i]->zywy && ((Objekt_zywy*)p->otoczenie[j][i])->jest_ofiara && ((Objekt_zywy*)p->otoczenie[j][i])->ofiara==this)
                           return true;
                  }
         }
         std::vector<std::shared_ptr<Upadly>> upadnieci(p->daj_wskazniki_do_upadlych());
         for(std::vector<std::shared_ptr<Upadly>>::iterator it = upadnieci.begin(); it!=upadnieci.end(); ++it)
                  if((*it)->a->zywy && ((Objekt_zywy*)((*it)->a))->jest_ofiara && ((Objekt_zywy*)((*it)->a))->ofiara==this)return true;
         return false;
}

char Objekt::daj_zwrot_do_punktu(int xc, int yc)
{
         if(y==yc&&x+1==xc) return 'p'; else if(y==yc&&x-1==xc) return 'l';
         else if(x==xc&&y+1==yc) return 'd'; else if(x==xc&&y-1==yc) return 'g';
         else if(x+1==xc&&y+1==yc)return 'd'; else if(x+1==xc&&y-1==yc)return 'g';
         else if(x-1==xc&&y+1==yc)return 'd'; else if(x-1==xc&&y-1==yc)return 'g';
         else if(y==yc) {if(x<xc) return 'p'; else if(x>xc) return 'l';}
         else if(x==xc) {if(y<yc) return 'd'; else if(y>yc) return 'g';}
         return zwrot;
}

bool Objekt::zaraz_obok(int xc,int yc, int x ,int y)
{
         return (xc==x+1 && yc==y)||(xc==x-1 && yc==y)||(xc==x && yc==y+1)||(xc==x && yc==y-1)||
         (xc==x+1 && yc==y-1)||(xc==x+1 && yc==y+1)||(xc==x-1 && yc==y-1)||(xc==x-1 && yc==y+1);
}

bool Objekt::jest_prostopadle(int xc,int yc, int xx ,int yy)
{
         return (xc+1==xx && yc==yy)||(xc-1==xx && yc==yy)||(xc==xx && yc+1==yy)||(xc==xx && yc-1==yy);
}

bool Objekt::jest_z_ukosa(int xc,int yc, int x ,int y)
{
         return (xc+1==x && yc+1==y)||(xc+1==x && yc-1==y)||(xc-1==x && yc+1==y)||(xc-1==x && yc-1==y);
}

bool Objekt::jest_naprzeciw_nas(short xx, short yy)
{
         if(zwrot == 'p') return xx==x+1 && yy >=y-1 && yy<=y+1;
         else if(zwrot == 'l') return xx==x-1 && yy >=y-1 && yy<=y+1;
         else if(zwrot == 'g') return yy==y-1 && xx >=x-1 && xx<=x+1;
         else return yy==y+1 && xx >=x-1 && xx<=x+1;
}

char Objekt::przeciwna(char strona)
{
         if(strona=='l') return 'p';if(strona=='p') return 'l';if(strona=='g') return 'd';if(strona=='d') return 'g';return 'n';
}

char pozycja_w_zwarciu(int xc,int yc, int x ,int y, char zwrot)///n zadne, p przod, b bok, t tyl
{
         if(Objekt::jest_prostopadle(xc,yc, x ,y))
         {
                  if(x<xc)switch(zwrot){case 'p': return 't'; case 'l': return 'p'; default: return 'b';}
                  else if(x>xc)switch(zwrot){case 'p': return 'p'; case 'l': return 't'; default: return 'b';}
                  else if(y<yc)switch(zwrot){case 'd': return 't'; case 'g': return 'p'; default: return 'b';}
                  else if(y>yc)switch(zwrot){case 'g': return 't'; case 'd': return 'p'; default: return 'b';}
         }
         else if(Objekt::jest_z_ukosa(xc,yc, x ,y))
         {
                  if(x<xc)
                  {
                           if(yc>y)switch(zwrot){case 'g': case 'l': return 'p'; default: return 't';}
                           else if(yc<y)switch(zwrot){case 'd': case 'l': return 'p'; default: return 't';}
                  }
                  else if(x>xc)
                  {
                           if(yc>y)switch(zwrot){case 'p': case 'g': return 'p'; default: return 't';}
                           else if(yc<y)switch(zwrot){case 'p': case 'd': return 'p'; default: return 't';}
                  }
         }
         return 'n';
}

bool Objekt::kratka_z_tylu_jest_wolna(int xz,int yz)
{
         Plansza *p=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         return jest_prostopadle(xz,yz,x,y)&&((x<xz && x-1>-1 && p->otoczenie[y][x-1]==NULL)||(x>xz && x+1<21 && p->otoczenie[y][x+1]==NULL)||(y<yz && y-1>-1 && p->otoczenie[y-1][x]==NULL)||(y>yz && y+1<13 && p->otoczenie[y+1][x]==NULL));
}

void Objekt_zywy::zoszolom()
{
         oszolomion = true;
}

bool Objekt_zywy::oszolomiony()
{
         return oszolomion||OSZOLOMION;
}

char Objekt::kratka_z_tylu(int xz,int yz)
{
         if(!jest_prostopadle(x,y,xz,yz)) return 'n';
         if(x<xz) return 'l';
         if(x>xz) return 'p';
         if(y<yz) return 'g';
         if(y>yz) return 'd';
         return 'n';
}

char Objekt::losuj_zwrot()
{
         switch(losuj(1,4))
         {
                  case 1: return 'p';
                  case 2: return 'l';
                  case 3: return 'd';
                  case 4: return 'g';
         }

}

punkt Objekt::naprzeciwko()
{
         if(zwrot == 'p') if(x+1<21) return punkt(x+1,y);
         else if(zwrot == 'l') if(x-1>-1) return punkt(x-1,y);
         else if(zwrot == 'd') if(y+1<13) return punkt(x,y+1);
         else if(zwrot == 'g') if(y-1>-1) return punkt(x,y-1);
         return punkt(-1,-1);
}

punkt Objekt::kratka_za_gosciem_jak_chce_go_kopnac(short x_goscia, short y_goscia)
{
         if(!jest_prostopadle(x,y,x_goscia,y_goscia)) return punkt(-1,-1);
         if(x<x_goscia) return punkt(x+2,y);
         else if(x>x_goscia) return punkt(x-2,y);
         else if(y<y_goscia) return punkt(x,y+2);
         return punkt(x,y-2);
}


Objekt::~Objekt(){}
Objekt_zywy::~Objekt_zywy(){}

Objekt_martwy::~Objekt_martwy(){}

Objekt_pol_martwy::~Objekt_pol_martwy(){}

Sarna::~Sarna(){}

Woda::~Woda(){}

Objekt_przejsciowy::~Objekt_przejsciowy(){}

Trawa_przejsciowa::~Trawa_przejsciowa(){}

Woda_przejsciowa::~Woda_przejsciowa(){}

Zombie_przejsciowe::~Zombie_przejsciowe(){}

Drzewo_przejsciowe::~Drzewo_przejsciowe(){}


bool Objekt_martwy::przesun_po_srodowisku(char strona)
{
         if(this==NULL) {std::cout<<"NULL na Objekt_martwy::przesun_po_srodowisku"; return false;}
         if(strona!='n' && strona!='p' && strona!='l' && strona!='d' && strona!='g')
         {std::cout<<" zly zwrot dla f przesun_pol_martwy "; throw "ff";}
         if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" przm ";
         short kx=px, ky=py, kz=pz;
         if(strona=='n')  {if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" prM ";return false;}

         Plansza* nasza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         Area* dawna=nasza;
         int sx=x, sy=y;///ku pamieci widokow
         int s_x=x, s_y=y; switch(strona) {case 'p': s_x++;break;case 'l': s_x--;break;case 'g': s_y--;break;case 'd': s_y++;break;}
         if(!((s_y>-1 && s_y<13 && s_x>-1 && s_x<21 && nasza->otoczenie[s_y][s_x]==NULL)
            ||((s_x==21 && swiat->zwroc_taka_plansze(px+1, py, pz) && swiat->zwroc_taka_plansze_TYLKO(px+1,py,pz)->otoczenie[y][0]==NULL)
               ||(s_x==-1 && swiat->zwroc_taka_plansze(px-1, py, pz) && swiat->zwroc_taka_plansze_TYLKO(px-1,py,pz)->otoczenie[y][20]==NULL)
               ||(s_y==13 && swiat->zwroc_taka_plansze(px, py+1, pz) &&swiat->zwroc_taka_plansze_TYLKO(px,py+1,pz)->otoczenie[0][x]==NULL)
               ||(s_y==-1 && swiat->zwroc_taka_plansze(px, py-1, pz) && swiat->zwroc_taka_plansze_TYLKO(px,py-1,pz)->otoczenie[12][x]==NULL))))
               {if(Objekt::args->melduj_co_robi_AI)std::cout<<" MM ";return false;}
         Srodowisko *sss = nasza->srodowisko[y][x];

         int do_czego=swiat->X;if(strona=='g' || strona=='d') do_czego=swiat->Y;

         if(nasza->ma_gracza)
         {
                  sss->przesuniecie_x=0; sss->przesuniecie_y=0;
                  for(int i=0; i<do_czego/2; i++) {switch(strona)
                  {case 'p':sss->przesuniecie_x=i;break;case 'l':sss->przesuniecie_x=-i;break;case 'g':sss->przesuniecie_y=-i;break;case 'd':sss->przesuniecie_y=i;break;}Sleep(375/do_czego);}
         }

         dzwiek_przesuniecia(x,y);
         sss->przesuniecie_x = 0; sss->przesuniecie_y = 0;
         sss->usun_objekt(this,x, y, nasza);


         if(s_x!=-1 && s_x!=21 && s_y!=-1 && s_y!=13)
         {
                if(nasza->srodowisko[s_y][s_x]==NULL) nasza->srodowisko[s_y][s_x] = new Srodowisko();
                Srodowisko *sss2 = nasza->srodowisko[s_y][s_x];
                sss2->dodaj_objekt(this, s_x, s_y);

                short i = do_czego/2;
                 switch(strona)
                 {case 'p':sss2->przesuniecie_x=-i;break;case 'l':sss2->przesuniecie_x=i;break;case 'g':sss2->przesuniecie_y=i;break;case 'd':sss2->przesuniecie_y=-i;break;}

                  x=s_x; y=s_y;
                  if(nasza->ma_gracza)
                  {
                           for(i=do_czego/2; i>=0; i--) {switch(strona)
                           {case 'p':sss2->przesuniecie_x=-i;break;case 'l':sss2->przesuniecie_x=i;break;case 'g':sss2->przesuniecie_y=i;break;case 'd':sss2->przesuniecie_y=-i;break;}Sleep(375/do_czego);}
                  }
                  sss2->przesuniecie_x=0; sss2->przesuniecie_y=0;
                  nasza->zaktualizuj_widoki(x,y, sx, sy);
         }
         else
         {
                int n_x=x,n_y=y;
                  switch(strona)
                  {case 'p':px++;n_x=0;break;
                  case 'l':px--;n_x=20;break;
                  case 'g':py--;n_y=12;break;
                  case 'd':py++;n_y=0;break;
                  default: return false;}

                Plansza*kolejna=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);

                x=n_x; y=n_y;
                kolejna->dodaj_do_srodowiska(x, y, this);

                /*if(kolejna->ma_gracza)
                {
                        swiat->Ustaw_aktualna(kolejna);
                        for(int i=do_czego/2; i>=0; i--) {switch(strona)
                        {case 'p':przesuniecie_x=-i;break;case 'l':przesuniecie_x=i;break;case 'g':przesuniecie_y=i;break;case 'd':przesuniecie_y=-i;break;}Sleep(375/do_czego);}
                }*/
                kolejna->zaktualizuj_widoki(x,y, x, y);
                //if(kolejna->ma_gracza) Sleep(500);
                //if(dawna->ma_gracza) swiat->Ustaw_aktualna(nasza);
                if(dawna->jest_plansza){nasza->zaktualizuj_widoki(sx,sy, sx, sy);}
                if(nasza->ma_gracza) Sleep(400);
         }
         dzwiek_przesuniecia(x,y);
         if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" pm ";
         return true;
}



bool Objekt_martwy::wejdz(Objekt *a, Objekt **kto_sie_chowa)
{
         if(*kto_sie_chowa != NULL) return false;
         Plansza*pl = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);

         if(a->czym_jest==10) ((Gracz*)a)->ukryty = true;
         a->zwrot = a->daj_zwrot_do_punktu(x,y);
         //a->zbliz_lub_oddal(1, x, y);

         if(a->zywy) ((Objekt_zywy*)a) -> przestan_byc_ofiara(0, x, y);
         *kto_sie_chowa = a;
         pl->otoczenie[a->y][a->x] = NULL;
         pl->zaktualizuj_widoki(x,y, a->x, a->y);
         return true;
}

bool Objekt_martwy::wyjdz(Objekt **kto_sie_chowa, char strona)
{
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(czym_jest==30)
         {
                  punkt a= punkt_przed(zwrot, x, y);
                  if(a.x!=-1 && a.y!=-1 && p->otoczenie[a.y][a.x]==NULL)
                  {
                           (*kto_sie_chowa)->px = px; (*kto_sie_chowa)->py = py; (*kto_sie_chowa)->pz = pz;
                           (*kto_sie_chowa)->x = a.x; (*kto_sie_chowa)->y = a.y;
                           swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[a.y][a.x] = *kto_sie_chowa;
                            (*kto_sie_chowa)->wyjdz_animacja(x, y);

                           if((*kto_sie_chowa)->czym_jest==10) ((Gracz*)(*kto_sie_chowa))->ukryty = false;
                           *kto_sie_chowa = NULL;
                           return true;
                  }
                  else return false;
         }
         else if(strona != 'n')
         {
                  punkt a = punkt_przed(strona, x, y);
                  if(Strefa::w_planszy(a.x, a.y) && p->otoczenie[a.y][a.x]==NULL)
                  {
                           (*kto_sie_chowa)->px = px; (*kto_sie_chowa)->py = py; (*kto_sie_chowa)->pz = pz;
                           (*kto_sie_chowa)->x = a.x; (*kto_sie_chowa)->y = a.y;
                           if((*kto_sie_chowa)->czym_jest==10) ((Gracz*)(*kto_sie_chowa))->ukryty = false;

                           p->otoczenie[a.y][a.x] = *kto_sie_chowa;
                           Objekt *a = *kto_sie_chowa;
                           *kto_sie_chowa = NULL;

                           //a->wyjdz_animacja(x, y);
                           p->zaktualizuj_widoki(x, y, a->x, a->y);

                           return true;
                  }
                  else return false;
         }
         else
         {
                  std::cout<<"Nie umiem z czegos takiego uciekac"; throw "W";
         }

         /*if(((Plansza*)Objekt::swiat->area[px][py][pz])->otoczenie[(*kto_sie_chowa)->y][(*kto_sie_chowa)->x] == NULL)
         {
                  ((Plansza*)Objekt::swiat->area[px][py][pz])->otoczenie[(*kto_sie_chowa)->y][(*kto_sie_chowa)->x] = *kto_sie_chowa;
                  (*kto_sie_chowa)->px = px; (*kto_sie_chowa)->py = py; (*kto_sie_chowa)->pz = pz;
                  *kto_sie_chowa = NULL;
         }
         else return wywal_gdzies_obok(kto_sie_chowa);
         return true;*/
}

void Objekt_martwy::kryjowka_destroyer(Objekt **kto_sie_chowa)
{
         if((*kto_sie_chowa)!=NULL)
         {
                  if((*kto_sie_chowa)->czym_jest==10)
                  {
                           ((Gracz*)(*kto_sie_chowa))->ukryty = false;
                  }
                  (*kto_sie_chowa)->nie_wykonal_ruchu = false;
                  (*kto_sie_chowa)->x = x; (*kto_sie_chowa)->y = y;
                  (*kto_sie_chowa)->px = px; (*kto_sie_chowa)->py = py; (*kto_sie_chowa)->pz = pz;
                  if(swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]==NULL)
                           swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x] = *kto_sie_chowa;
                  else if(wywal_gdzies_obok(kto_sie_chowa));
                  else delete *kto_sie_chowa;
                  *kto_sie_chowa = NULL; ///just in case
         }
}

bool Objekt_martwy::wywal_gdzies_obok(Objekt **kto_sie_chowa)///nie tylko kryjowka ale tez spanie
{
         ///nulluj *kto_sie_chowa jesli sie uda
         (*kto_sie_chowa)->x = x; (*kto_sie_chowa)->y = y;
         (*kto_sie_chowa)->px = px; (*kto_sie_chowa)->py = py; (*kto_sie_chowa)->pz = pz;
         (*kto_sie_chowa) -> przewroc();
}

bool Objekt_martwy::ukrywa_go(Objekt*kogo, Objekt* ukryty)
{
         return kogo == ukryty;
}




void Objekt_martwy::stworz_loot(Kontener<Item> *zawartosc, int szansa_na_ubranie,int szansa_na_plecak,int szansa_na_bron,int szansa_na_inne,int szansa_na_jedzenie,int szansa_na_medykamenty)
{
         Item **tab = Item::wylosuj_liste_itemow(szansa_na_ubranie, szansa_na_plecak, szansa_na_bron, szansa_na_inne, szansa_na_jedzenie, szansa_na_medykamenty);
         for(short i = 0; tab[i] != NULL; ++i) zawartosc->dodaj_obiekt(tab[i]);
         delete [] tab;
}

what_happened Objekt_zywy::przejdz_nad_pod_objektem(short xx, short yy)
{
         Plansza* p = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         punkt b = kratka_za_gosciem_jak_chce_go_kopnac(xx,yy);
         if(p->otoczenie[yy][xx]==NULL || !jest_zaraz_obok(p->otoczenie[yy][xx]) || !jest_prostopadle(xx,yy,x,y) || p->otoczenie[b.y][b.x]!=NULL) return fail;

         zwrot = daj_zwrot_do_punktu(xx,yy);
         przesuniecie_x=0; przesuniecie_y=0;
         int do_czego=swiat->X; if(zwrot=='g' || zwrot=='d') do_czego=swiat->Y;
         if(p->ma_gracza)
         {
                  for(int i=0;i<=do_czego*2; i++)
                  {
                           switch(zwrot)
                           {
                                    case 'p':przesuniecie_x=i;break;
                                    case 'l':przesuniecie_x=-i;break;
                                    case 'g':przesuniecie_y=-i;break;
                                    case 'd':przesuniecie_y=i;break;
                           }
                           Sleep(375/do_czego);
                  }
         }
         p->otoczenie[y][x]=NULL;
         przesuniecie_x=0; przesuniecie_y=0;
         x = b.x; y =b.y;
         p->otoczenie[y][x] = this;
         p->zaktualizuj_widoki(x,y, x, y);
         return reakcja_na_podloze();
}


///objekt spiacy sam sie budzi
bool Objekt_martwy::przespij_sie_w(int ile_czasu, Objekt *kto, Objekt **miejsce_do_spania)
{
         if(kto->czym_jest!=10) return false;
         if(ile_czasu<=0) return false;
         if(*miejsce_do_spania != NULL) return false;

         Plansza*pl = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);

         if(kto->czym_jest==10)
         {
                  Gracz *g = (Gracz*)kto;
                  g->pozostalo_snu=ile_czasu; g->gdzie_spi=this;
                  g->ukryty = true;
         }

         kto->zwrot = kto->daj_zwrot_do_punktu(x,y);

         kto->zbliz_lub_oddal(1, x, y);
         swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[kto->y][kto->x] = NULL;
         if(kto->zywy) ((Objekt_zywy*)kto) -> przestan_byc_ofiara(0, x, y);
         *miejsce_do_spania = kto;
         pl->zaktualizuj_widoki(x,y, kto->x, kto->y);
         pl->ma_gracza = false;
         return true;
}

void Objekt_martwy::lozko_destroyer(Objekt **kto_spi)
{
         if((*kto_spi)!=NULL)
         {
                  if((*kto_spi)->czym_jest==10)
                  {
                           ((Gracz*)(*kto_spi))->ukryty = false;
                           ((Gracz*)(*kto_spi))->gdzie_spi = NULL;
                           ((Gracz*)(*kto_spi))->pozostalo_snu = 0;
                            swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->ma_gracza = true;
                  }
                  (*kto_spi)->nie_wykonal_ruchu = false;
                  (*kto_spi)->x = x; (*kto_spi)->y = y;
                  (*kto_spi)->px = px; (*kto_spi)->py = py; (*kto_spi)->pz = pz;
                  if(swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]==NULL)
                           swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x] = *kto_spi;
                  else if(wywal_gdzies_obok(kto_spi));
                  else delete *kto_spi;
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->zaktualizuj_widoki();
                  *kto_spi = NULL; ///just in case
         }
}

bool Objekt::sproboj_podpalic()
{
         if(!this) return false;
         if(czym_jest==24)
         {
                  ((Ognisko*)this)->podpal();
         }
         else if(czym_jest==34)
         {
                  if(((Beczka*)this)->jest_Ropa()) ((Beczka*)this)->zostan_uderzony(30, obrazenia_od_ognia,0,0);
                  return false;
         }

         if(losuj(1,100)<=latwopalnosc())
                  {stan|=1; return true;}
         return false;
}

Objekt* Objekt::stworz_objekt_z_wykraftowania(int co, int a, int b, int c, int d , int e)
{
         switch(co)
         {
                  case 24: return new Ognisko(a, b, c, d, e);
                  default: std::cout<<"stworz_objekt_wykraftowany_nie_ma_takiego"<<co; throw "D";
         }
}



