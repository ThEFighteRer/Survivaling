#include "swiat.h"
#include <windows.h>
/*
int Wilk::get_co_to()
{
         int a=253;
         switch(zwrot) {case 'd':a+=8;case 'g':a+=8;case 'p':a+=8;case 'l':break;}

         if(zaalarmowany)
         {
                  a+=6;
         }
         else if(atakujacy)
         {
                  if(zwrot_ostatni=='l') a+=1;
         }
         else if(biegnie)
         {
                  if(zwrot_ostatni=='l') a+=1; a+=2;
         }
         else
         {
                  if(zwrot_ostatni=='l') a+=1; a+=4;
         }
         return a;
}

void Wilk :: zapisz(std::ofstream *ofs)
{

}

void Wilk::zostan_uderzony(int obrazenia, int kto, int ekstra)
{
         animacja_damage(obrazenia);

         Plansza *a=(Plansza*)swiat->area[px][py][pz];
         int aaa=losuj(1,8); bool zna=false, br=false;
         while(true)
         {
                  switch(aaa)
                  {
                           case 1:if(x+1<21 && a->otoczenie[y][x+1]!=NULL && a->otoczenie[y][x+1]->zywy) {ofiara=a->otoczenie[y][x+1];jest_ofiara=true; br=true;}
                           case 2:if(x-1>-1 && a->otoczenie[y][x-1]!=NULL&& a->otoczenie[y][x-1]->zywy) {ofiara=a->otoczenie[y][x-1];jest_ofiara=true; br=true;}
                           case 3:if(y+1<13 && a->otoczenie[y+1][x]!=NULL&& a->otoczenie[y+1][x]->zywy) {ofiara=a->otoczenie[y+1][x];jest_ofiara=true; br=true;}
                           case 4:if(y-1>-1 && a->otoczenie[y-1][x]!=NULL&& a->otoczenie[y-1][x]->zywy) {ofiara=a->otoczenie[y-1][x];jest_ofiara=true; br=true;}
                           case 5:if(y-1>-1 && x-1>-1 && a->otoczenie[y-1][x-1]!=NULL&& a->otoczenie[y-1][x-1]->zywy) {ofiara=a->otoczenie[y-1][x-1];jest_ofiara=true; br=true;}
                           case 6:if(y-1>-1 && x+1<21 && a->otoczenie[y-1][x+1]!=NULL&& a->otoczenie[y-1][x+1]->zywy) {ofiara=a->otoczenie[y-1][x+1]; jest_ofiara=true;br=true;}
                           case 7:if(y+1<13 && x+1<21 && a->otoczenie[y+1][x+1]!=NULL && a->otoczenie[y+1][x+1]->zywy) {ofiara=a->otoczenie[y+1][x+1];jest_ofiara=true; br=true;}
                           case 8:if(y+1<13 && x-1>-1 && a->otoczenie[y+1][x-1]!=NULL && a->otoczenie[y+1][x-1]->zywy) {ofiara=a->otoczenie[y+1][x-1];jest_ofiara=true; br=true;}
                  }
                  if(br) break;
                  aaa=1; br=true;
         }

         HP-=obrazenia;
         if(HP<=0)
         {
                  przestan_byc_ofiara(1);
                  ((Plansza*)swiat->area[px][py][pz])->otoczenie[y][x]=NULL;
                  Srodowisko::dodaj_objekt((new Zwloki(czym_jest,0,x,y,px,py,pz)),x,y,((Plansza*)swiat->area[px][py][pz]));
                  ((Plansza*)swiat->area[px][py][pz])->zaktualizuj_widoki(x,y,x,y);
                  delete this;
         }
         return;
}

Wilk::Wilk()
{
         czym_jest=11; zywy=true; nie_wykonal_ruchu=true;wykonuje_ruch=true; wysokosc=1;
}

Wilk::~Wilk()
{

}

bool Wilk::przesun_sie(char decyzja)
{
         if(Objekt::args->melduj_co_robi_AI) std::cout<<" rozmyslamPrzesuwanie ";
         Plansza* plansza=(Plansza*)Objekt::swiat->area[px][py][pz];
         if(decyzja=='n') {if(Objekt::args->melduj_co_robi_AI) std::cout<<" rozmyslilemPrzesuwanie ";return false;}
         struct punkt p=punkt_przed(decyzja, x, y);
         if((p.y>12 || p.y<0 || p.x>20 || p.x<0)||(plansza->otoczenie[p.y][p.x]==NULL)) {przesun(decyzja);if(Objekt::args->melduj_co_robi_AI) std::cout<<" rozmyslilemPrzesuwanie ";return true;}
         else {uderz(decyzja);if(Objekt::args->melduj_co_robi_AI) std::cout<<" rozmyslilemPrzesuwanie ";return true;}
}

void Wilk::uslysz_dzwiek(int dx,int dy,int rodzaj)
{
         if(jest_ofiara) {if((px==ofiara->px && py==ofiara->py && pz==ofiara->pz)&&(std::sqrt((float)((ofiara->x-x)*(ofiara->x-x)+(ofiara->y-y)*(ofiara->y-y)))<std::sqrt((float)((dx-x)*(dx-x)+(dy-y)*(dy-y)))))return;}
         jest_ofiara=false; jest_cel=true; celem_jest_plansza=false; zaalarmowany=true; xc=dx, yc=dy;
}

void Wilk::uslysz_dzwiek(Plansza *a,int rodzaj)
{
         if(!jest_ofiara) {jest_ofiara=false; jest_cel=true; celem_jest_plansza=true; zaalarmowany=true; ktora_plansza=a;}
}

void Wilk::dzwiek_przesuniecia(int xx, int yy)
{
         if(biegnie) wydaj_dzwiek(false, 2, xx,yy,11); else wydaj_dzwiek(false, 1, xx,yy,11);
}

bool Wilk::uderz(char strona)
{
         if(strona == 'p' || strona == 'l') zwrot = strona;
         animacja_ataku(strona);struct punkt p=punkt_przed(strona, x, y);
         Plansza* plansza=(Plansza*)Objekt::swiat->area[px][py][pz];
         if(p.x<21 && p.x>-1 && p.y<13 && p.y>-1 && plansza->otoczenie[p.y][p.x]!=NULL) {plansza->otoczenie[p.y][p.x]->zostan_uderzony(losuj(12,22)-(9-HP/10),9,0);return true;}
         return false;
}

void Wilk::rusz_sie()
{
         --jedzenie; --woda;
         Swiat* swiat=Objekt::swiat;
         Plansza* plansza=(Plansza*)swiat->area[px][py][pz];
         zaalarmowany=false;
         for(int k=0; k<3; ++k)
         {
                  if(jest_ofiara)
                  {
                           if(ofiara->px!=px || ofiara->py!=py || ofiara->pz!=pz)
                           {
                                    jest_ofiara=false;
                                    jest_cel=true;
                                    celem_jest_plansza=true;
                                    if(ofiara->px==px+1 && ofiara->py==py && ofiara->pz==pz)
                                    {
                                             if(swiat->area[px+1][py][pz]->jest_plansza)
                                             ktora_plansza=(Plansza*)swiat->area[px+1][py][pz];
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    else if(ofiara->px==px-1 && ofiara->py==py && ofiara->pz==pz)
                                    {
                                             if(swiat->area[px-1][py][pz]->jest_plansza)
                                             ktora_plansza=(Plansza*)swiat->area[px-1][py][pz];
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    else if(ofiara->px==px && ofiara->py==py+1 && ofiara->pz==pz)
                                    {
                                             if(swiat->area[px][py+1][pz]->jest_plansza)
                                             ktora_plansza=(Plansza*)swiat->area[px][py+1][pz];
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    else if(ofiara->px==px && ofiara->py==py-1 && ofiara->pz==pz)
                                    {
                                             if(swiat->area[px][py-1][pz]->jest_plansza)
                                             ktora_plansza=(Plansza*)swiat->area[px][py-1][pz];
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    ///KEJZY NA PLANSZE W GORE I PLANSZE W DOL
                                    else {jest_cel=false;celem_jest_plansza=false; jest_ofiara=false;}
                                    --k;continue;
                           }
                           czekanie=0;

                                    zaalarmowany=false;
                                    char gdzie;
                                    if(jest_zaraz_obok(ofiara))
                                    {
                                             if(ofiara->czy_lezy()==false)
                                             {biegnie=false;atakujacy=true;uderz(w_ktora_to_strone(x,y,ofiara->x, ofiara->y));}
                                    }
                                    else
                                    {
                                            ///powinien sie wczesniej rozejrzec aby uniknac pomijania zywych stworzen spoza gatunkow

                                             char decyzja=znajdz_droge(true,ofiara->x,ofiara->y,x,y,plansza);
                                             //std::cout<<ofiara->x<<" "<<ofiara->y<<" "<<decyzja<<std::endl;
                                             atakujacy=false;biegnie=true;przesun_sie(decyzja);
                                    }

                  }
                  else if(jest_cel)
                  {
                           if(celem_jest_plansza)
                           {
                                    if(ktora_plansza==NULL) {std::cout<<"Mam isc na plansze ale nwm na ktora"; throw "Mam isc na plansze ale nwm na ktora";}
                                    if(ktora_plansza==plansza)
                                    {
                                             jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;


                                             ///znalezlismy nasza plansze
                                             --k;continue;
                                    }
                                    else
                                    {
                                             char r = jak_dojsc_na_plansze(ktora_plansza, true);
                                             if(r != 'n')
                                             {
                                                      atakujacy=false;biegnie=true;
                                                      przesun_sie(r);
                                                      czekanie=0;
                                             }
                                             else
                                             {
                                                      ++czekanie; if(czekanie>5) {jest_ofiara=false;jest_cel=false;celem_jest_plansza=false;}
                                                      if(Objekt::args->melduj_co_robi_AI)
                                                      std::cout<<" Nie moge znalezc drogi";
                                             }
                                    }
                           }
                           else
                           {
                                    bool najadl_sie =false;
                                    if(zaraz_obok(xc,yc,x,y))
                                    {
                                             if(Objekt::args->melduj_co_robi_AI) std::cout<<" Jestem_obok_celu ";
                                             zwrot=daj_zwrot_do_punktu(xc,yc); patrz();
                                             if(jest_ofiara) {--k; continue;}

                                             biegnie=false; atakujacy=false;
                                             if(Strefa::w_planszy(xc,yc) && plansza->otoczenie[yc][xc]!=NULL && plansza->otoczenie[yc][xc]->czym_jest==21)
                                             {
                                                      if(woda<200)woda+=20;if(woda>=120)najadl_sie=true;
                                             }
                                             else if(Strefa::w_planszy(xc,yc) && plansza->srodowisko[yc][xc]!=NULL && plansza->srodowisko[yc][xc]->ma_to(22))
                                             {
                                                      if(plansza->srodowisko[yc][xc]->zjedz_rosline(22))jedzenie+=20; else {if(plansza->ma_gracza)Sleep(1);}
                                                      plansza->zaktualizuj_widoki(x,y,x,y);if(jedzenie>=120 || (plansza->srodowisko[yc][xc]!=NULL && !plansza->srodowisko[yc][xc]->ma_to(22))) najadl_sie=true;
                                             }
                                             else
                                             {
                                                      atakujacy=false;biegnie=true;przesun_sie(znajdz_droge(true,xc,yc,x,y,plansza));czekanie=0;
                                             }
                                             if(najadl_sie){jest_cel=false;celem_jest_plansza=false;}
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<" Zjadlem ";return;
                                    }
                                    else
                                    {
                                             if(Objekt::args->melduj_co_robi_AI) std::cout<<" Cel jest daleko, ide tam ";
                                             atakujacy=false; biegnie=true;
                                             char r = znajdz_droge(true,xc,yc,x,y,plansza);
                                             if(r=='n' && czekanie++>5) {jest_cel = false;celem_jest_plansza=false;}
                                             if (r!='n') czekanie=0;
                                             przesun_sie(r);
                                    }
                           }
                  }
                  else if(jedzenie<100 || woda<100)
                  {
                           biegnie=false;
                           if(pamiec&1!=1 || pamiec&2!=2 || pamiec&4!=4)
                           {
                                    if(x<7 && pamiec&2!=2 && znajdz_droge(true,10,y,x,y,plansza)!='n'){xc=10;yc=y;jest_cel=true;--k;continue;}
                                    else if(x<7 && pamiec&4!=4 && znajdz_droge(true,18,y,x,y,plansza)!='n'){xc=18;yc=y;jest_cel=true;--k;continue;}
                                    else if(x<15 && pamiec&1!=1 && znajdz_droge(true,3,y,x,y,plansza)!='n'){xc=3;yc=y;jest_cel=true;--k;continue;}
                                    else if(x<15 && pamiec&4!=4 && znajdz_droge(true,18,y,x,y,plansza)!='n'){xc=18;yc=y;jest_cel=true;--k;continue;}
                                    else if(pamiec&2!=2 && znajdz_droge(true,10,y,x,y,plansza)!='n'){xc=10;yc=y;jest_cel=true;--k;continue;}
                                    else if(pamiec&1!=1 && znajdz_droge(true,3,y,x,y,plansza)!='n'){xc=3;yc=y;jest_cel=true;--k;continue;}
                                    else
                                    {
                                             ktora_plansza =wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, true);
                                             celem_jest_plansza = ktora_plansza != NULL; jest_cel = ktora_plansza != NULL;
                                             --k; continue;
                                    }
                           }
                           else
                           {
                                    ktora_plansza =wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, true);
                                    celem_jest_plansza = ktora_plansza != NULL; jest_cel = ktora_plansza != NULL;
                                    --k;continue;
                           }
                  }
                  else
                  {
                           biegnie=false;atakujacy=false;
                           if(losuj(0,4)!=0)
                           {
                                    char dzie=zwrot;
                                    if(losuj(0,2)==0)
                                    {
                                             switch(losuj(0,2)) {case 0:dzie=skrec('p', zwrot);break;case 1:dzie=skrec('l', zwrot);break;case 2:break;}
                                    }
                                    struct punkt p=punkt_przed(dzie,x,y);
                                    if(p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                    przesun_sie(dzie);
                                    else if(dzie==zwrot)
                                    {
                                             char cos='p'; if(losuj(0,1)==0) cos='l';
                                             if((p=punkt_przed(skrec(cos,zwrot),x,y)).x+2 && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             przesun_sie(skrec(cos, zwrot));
                                             else if((p=punkt_przed(skrec(skrec('z',cos),zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             przesun_sie(skrec(skrec('z', cos), zwrot));
                                             else przesun_sie(skrec('z', zwrot));
                                    }
                                    else
                                    {
                                             if((p=punkt_przed(skrec('z', dzie),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             przesun_sie(skrec('z', dzie));
                                             else if((p=punkt_przed(zwrot,x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             przesun_sie(zwrot);
                                             else if((p=punkt_przed(skrec('z',zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             przesun_sie(skrec('z', zwrot));
                                    }
                           }
                           return;
                  }
         }
}

void Wilk::patrz()
{
         if(x<7) pamiec=pamiec|1;else if(x<15) pamiec=pamiec|2; else pamiec=pamiec|4;
         int poszerzajaca=x; if(zwrot=='l' || zwrot=='p') poszerzajaca=y; ///ktora pokazuje strone
         int xw, yw;Plansza*a=(Plansza*)Objekt::swiat->area[px][py][pz];
         bool jest_woda=false, jest_trawa=false; int wx,wy,tx,ty;
         for(int i=3; i<47; i+=2)
         {
                  for(int j=poszerzajaca-(i/2); j<=poszerzajaca+(i/2);j++)
                  {
                           switch(zwrot){case 'd':{xw=j;yw=y+(i-3)/2;break;}case 'g':{xw=j;yw=y-(i-3)/2;break;}case 'p':{yw=j;xw=x+(i-3)/2;break;}case'l':{yw=j;xw=x-(i-3)/2;break;}}

                           if(yw>-1 && yw<13 && xw>-1 && xw<21 && (xw!=x || yw!=y))
                           {
                                    if(a->otoczenie[yw][xw]!=NULL && a->otoczenie[yw][xw]->zywy)
                                    {
                                             bool na_pewno_w_zasiegu=true;
                                             int skrot=0; ///skrocenie_widzialnej_odl
                                             int odciecia=0; ///odciecia zasiegu wzroku
                                             int poprawka=0; ///wzgl postawy
                                             int kamuflaz=0;

                                             if(a->otoczenie[yw][xw]->czym_jest==10)
                                             {
                                                      Gracz *g=(Gracz*)a->otoczenie[yw][xw];
                                                      switch(g->postawa) {case 'c':poprawka+=10;skrot+=5;case's':poprawka+=10;skrot+=7;case 'r':break;}
                                                      poprawka+=g->kamuflaz();
                                                      skrot+=g->kamuflaz()/4;

                                                      if(g->postawa=='r')
                                                      {
                                                               if(skrot>15) skrot=15;
                                                               if(poprawka>30) poprawka=30;
                                                      }
                                                      else if(g->postawa=='s')
                                                      {
                                                               if(skrot>12) skrot=12;
                                                               if(poprawka>40) poprawka=40;
                                                      }
                                                      else
                                                      {
                                                               if(skrot>4) skrot=4;
                                                               if(skrot<17) skrot=17;
                                                      }
                                                      kamuflaz=g->kamuflaz();
                                             }
                                             na_pewno_w_zasiegu=!((zwrot=='p' && xw-x>20-skrot)||(zwrot=='l' && x-xw>20-skrot)
                                                ||(zwrot=='g' && y-yw>20-skrot)||(zwrot=='d' && yw-y>20-skrot)||czy_widzi_wzgl_zwezania(3,2,odciecia,xw,yw));

                                             if(!jest_ofiara && na_pewno_w_zasiegu && widzi_obiekt(a,xw,yw,x,y,kamuflaz,poprawka))
                                             {
                                                      jest_ofiara=true; ofiara=a->otoczenie[yw][xw]; jest_cel=false; celem_jest_plansza=false; zaalarmowany=true;
                                             }
                                    }
                                    else if(!jest_woda && woda<100  && a->otoczenie[yw][xw]!=NULL && a->otoczenie[yw][xw]->czym_jest==21)
                                    {
                                             jest_woda=true; wx=xw; wy=yw;
                                    }
                                    else if(!jest_trawa && jedzenie<100 && a->otoczenie[yw][xw]==NULL && a->srodowisko[yw][xw]!=NULL && a->srodowisko[yw][xw]->ma_to(22))
                                    {
                                             jest_trawa=true; tx=xw; ty=yw;
                                    }
                           }

                  }
         }
         if(jest_woda && woda<100 && ((!jest_trawa && (jedzenie>50 || woda<20)) || (jedzenie>50 || woda<jedzenie+10)))
         {
                  jest_cel=true; xc=wx; yc=wy; celem_jest_plansza = false;
         }
         else if(jest_trawa && jedzenie<100)
         {
                  jest_cel=true; xc=tx; yc=ty; celem_jest_plansza = false;
         }
}

Wilk::Wilk(Wilk_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz)
{
         czym_jest=11;x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=1;
         co_to=0; px=ppx;py=ppy;pz=ppz;zywy=true;
         HP=a->HP; zwrot_ostatni='p'; atakujacy=false;zaalarmowany=false;biegnie=false;
         jedzenie=a->jedzenie;woda=a->woda;pamiec=0;
}

Wilk_przejsciowy::Wilk_przejsciowy(Wilk*a)
{
         czym_jest=11;
         HP=a->HP;jedzenie=a->jedzenie;woda=a->woda;
}

Wilk_przejsciowy::~Wilk_przejsciowy()
{

}

void Wilk_przejsciowy::zapisz(std::ofstream *a)
{

}

Wilk_przejsciowy::Wilk_przejsciowy()
{
         czym_jest=11;
}
*/
