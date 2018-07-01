#include "swiat.h"


void Zombie::uslysz_dzwiek(int dx,int dy,int rodzaj)
{
         if(rodzaj==2) return;
         if(!jest_ofiara) {jest_cel=true;celem_jest_plansza=false;xc=dx;yc=dy;}
}

void Zombie::uslysz_dzwiek(Plansza* a,int rodzaj)
{
         if(rodzaj==2) return;
         jest_cel=true; celem_jest_plansza=true; ktora_plansza=a;
}

what_happened Zombie::zostan_uderzony(int obr, int kto, int ekstra, short wsp_zajecia)
{
         if(this==NULL) {std::cout<<"NULL na Zombie::zostan_uderzony"; return dead;}
         punkty_ruchu -= wsp_zajecia;
         if(kto==-10)
         {
                  obr=10;
                  hp_glowa-=obr; if(hp_glowa<0) hp_glowa=0;
                  animacja_damage(obr);
         }
         else if(kto==-1)///gora i okolice glowy
         {
                  animacja_damage(obr);
                  if(losuj(1,100)<=ekstra){hp_glowa-=obr;}
                  else
                  {
                           int g=losuj(1,100);
                           if(g<=15){if(hp_reka_1>0){hp_reka_1-=obr;if(hp_reka_1<0)hp_reka_1=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}}
                           else if(g<=30)if(hp_reka_2>0){hp_reka_2-=obr;if(hp_reka_2<0)hp_reka_2=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
                           else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
                  }
         }
         else if(kto==-2)///bok
         {
                  animacja_damage(obr);
                  int g=losuj(1,100);
                  if(g<=30){if(hp_reka_1>0){hp_reka_1-=obr;if(hp_reka_1<0)hp_reka_1=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}}
                  else if(g<=30)if(hp_reka_2>0){hp_reka_2-=obr;if(hp_reka_2<0)hp_reka_2=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
                  else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
         }
         else if(kto==-3)///na nogi
         {
                  animacja_damage(obr);
                  int g=losuj(1,100);
                  if(g<=50){if(hp_noga_1>0){hp_noga_1-=obr;if(hp_noga_1<0)hp_noga_1=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}}
                  else if(hp_noga_2>0){hp_noga_2-=obr;if(hp_noga_2<0)hp_noga_2=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
         }
         else if(kto==-4)///okolice klatki
         {
                  animacja_damage(obr);
                  int g=losuj(1,100);
                  if(g<=25){if(hp_reka_1>0){hp_reka_1-=obr;if(hp_reka_1<0)hp_reka_1=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}}
                  else if(g<=25)if(hp_reka_2>0){hp_reka_2-=obr;if(hp_reka_2<0)hp_reka_2=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
                  else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
         }
         else if(kto==-5)///okolice nog
         {
                  animacja_damage(obr);
                  int g=losuj(1,100);
                  if(g<=35){if(hp_noga_1>0){hp_noga_1-=obr;if(hp_noga_1<0)hp_noga_1=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}}
                  else if(g<=35)if(hp_noga_2>0){hp_noga_2-=obr;if(hp_noga_2<0)hp_noga_2=0;}else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
                  else {hp_korpus-=obr;if(hp_korpus<0)hp_korpus=0;}
         }
         else
         {
                  bool udalo=false;int aaa=losuj(1,7);
                  animacja_damage(obr);
                  while(true)
                  {
                           switch(aaa)
                           {
                                    case 1: if(hp_reka_1>=0){hp_reka_1-=obr;udalo=true;break;}
                                    case 2: if(hp_reka_2>=0){hp_reka_2-=obr;udalo=true;break;}
                                    case 3: if(hp_korpus>=0){hp_korpus-=obr;udalo=true;break;}
                                    case 4: if(hp_noga_1>=0){hp_noga_1-=obr;udalo=true;break;}
                                    case 5: if(hp_noga_2>=0){hp_noga_2-=obr;udalo=true;break;}
                                    case 6: if(hp_korpus>=0){hp_korpus-=obr;udalo=true;break;}
                                    case 7: if(hp_glowa>=0){hp_glowa-=obr;udalo=true;break;}
                           }
                           if(udalo) break; aaa=1; udalo=true; continue;
                  }
         }
         ///pamietaj o widokach po smierci
         ///i o zdeofiarowaniu
         if(hp_korpus<=0 || hp_glowa<=0)
         {
                  przestan_byc_ofiara(1);
                  if(!lezy) swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]=NULL;
                  else
                  {
                           Area *a = swiat->zwroc_taka_aree(px,py,pz);
                           if(a)
                           {
                                    a->usun_upadlego(this);
                           }
                  }
                  unsigned char t=0; if(hp_glowa>0) t|=16;
                  if(hp_reka_1>0) t|=1; if(hp_reka_2>0) t|=2;
                  if(hp_noga_1>0) t|=4; if(hp_noga_2>0) t|=8;
                  Srodowisko::dodaj_objekt((new Zwloki(czym_jest,t,x,y,px,py,pz)),x,y,swiat->zwroc_taka_plansze_TYLKO(px,py,pz));
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->zaktualizuj_widoki(x,y,x,y);
                  smierc();
                  return dead;
         }
         else if(kto==9) {if(losuj(1,3)==1)przewroc();}
         return success;
}

short Zombie::latwopalnosc(){return 90;}

what_happened Zombie::uderz(char strona)
{
         if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<" udr ";
         animacja_ataku(strona);int obr=losuj(4,10); if(rozpedzony) obr += losuj(4, 10); if(hp_reka_1<=0) obr-=3; if(hp_reka_2<=0) obr-=3; if(obr<0) obr=0;
         struct punkt p=punkt_przed(strona, x, y);
         short zajecie = rozpedzony ? 3 : 2;
         zwrot = daj_zwrot_do_punktu(p.x, p.y);
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);int ggg=0;
         if(p.x<21 && p.x>-1 && p.y<13 && p.y>-1 && plansza->otoczenie[p.y][p.x]!=NULL && plansza->otoczenie[p.y][p.x]->czym_jest==10 && ((Gracz*)plansza->otoczenie[p.y][p.x])->jest_wsrod_blokow(this)) {zajecie--;if(zajecie<0)zajecie=0;obr-=((Gracz*)plansza->otoczenie[p.y][p.x])->ile_bloku(this);}
         if(p.x<21 && p.x>-1 && p.y<13 && p.y>-1 && plansza->otoczenie[p.y][p.x]!=NULL && plansza->otoczenie[p.y][p.x]->czym_jest==10 && ((Gracz*)plansza->otoczenie[p.y][p.x])->jest_wsrod_unikow(this)) {zajecie-=2;if(zajecie<0)zajecie=0;obr=0;}
         if(oszolomiony()) {obr=obr*90/100;}
         if(p.x<21 && p.x>-1 && p.y<13 && p.y>-1 && plansza->otoczenie[p.y][p.x]!=NULL && plansza->otoczenie[p.y][p.x]->czym_jest==10 && ((Gracz*)plansza->otoczenie[p.y][p.x])->jest_wsrod_skupien(this)) {zajecie--;if(zajecie<0)zajecie=0;obr=obr*70/100;}
         short zajecie_bon = 1;
         if(strona!='l' &&strona!='p' &&strona!='g' &&strona!='d') {obr*=0.7;zajecie--;if(zajecie<0)zajecie=0;}
         if(obr<1) obr = 1;
         if(p.x<21 && p.x>-1 && p.y<13 && p.y>-1 && plansza->otoczenie[p.y][p.x]!=NULL) {plansza->otoczenie[p.y][p.x]->zostan_uderzony(obr*2,2,ggg, zajecie); {rozpedzony = false; return success;}}
         rozpedzony = false;
         return fail;
}

what_happened Zombie::przesun_sie(char decyzja)
{
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(decyzja=='n') {return fail;}
         struct punkt p=punkt_przed(decyzja, x, y);
         if((p.y>12 || p.y<0 || p.x>20 || p.x<0)||(plansza->otoczenie[p.y][p.x]==NULL))
         {
                  what_happened aaa = przesun(decyzja);
                  if(aaa==success) rozpedzony = true;
                  return aaa;
         }
         else if(plansza->otoczenie[p.y][p.x]->czym_jest==2) {return success;}
         else {return uderz(decyzja);}
}

bool Zombie::mamy_niepoinformowanego_zombie(Plansza* p)
{
         for(int i=x-5;i<=x+5;++i)
         {
                  for(int j=y-5;j<=y+5;++j)
                  {
                           if(Strefa::w_planszy(i, j) && p->otoczenie[j][i] && p->otoczenie[j][i]->czym_jest==2 && ((Zombie*)p->otoczenie[j][i])->jest_ofiara==false)
                                    return true;
                  }
         }
         return false;
}

bool Zombie::rusz_sie()
{
         OSZOLOMION = oszolomion;
         oszolomion = false;
         rozpedzony = false;
         short p_ruchu = punkty_ruchu;
         bool lezy_przez_nogi = false;
         punkty_ruchu = 10;
         if(Objekt::args->melduj_co_robi_AI)
                           std::cout<<"ZRS "<<zwrot<<" ";
         Swiat* swiat=Objekt::swiat;
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         krzyczy = false;
         short h = 0;
         for(short kk=p_ruchu; kk>0;)
         {
                  if(++h>10) {return 1;}
                  plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
                  if(hp_noga_1<=0 || hp_noga_2<=0) lezy_przez_nogi=true;
                  if(lezy)
                  {
                          if(wlasnie_przeszukuje)
                           {
                                    if(co_juz_przeszukane) delete [] co_juz_przeszukane;
                                    co_juz_przeszukane = NULL;
                                    wlasnie_przeszukuje = false;
                           }
                           ///wstawanie  o ile k==0 bo jak k==1 to lezymy dalej
                           czekanie=0;
                            return true;
                  }
                  else if(jest_ofiara)
                  {
                           if(wlasnie_przeszukuje)
                           {
                                    if(co_juz_przeszukane) delete [] co_juz_przeszukane;
                                    co_juz_przeszukane = NULL;
                                    wlasnie_przeszukuje = false;
                           }
                           if(ofiara==NULL) {jest_ofiara=false; continue;}
                           if(ofiara->px!=px || ofiara->py!=py || ofiara->pz!=pz)
                           {
                                    jest_ofiara=false;
                                    jest_cel=true;
                                    celem_jest_plansza=true;
                                    if(ofiara->px==px+1 && ofiara->py==py && ofiara->pz==pz)
                                    {
                                             if(swiat->zwroc_taka_plansze(px+1,py,pz))
                                             ktora_plansza=swiat->zwroc_taka_plansze_TYLKO(px+1,py,pz);
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    else if(ofiara->px==px-1 && ofiara->py==py && ofiara->pz==pz)
                                    {
                                             if(swiat->zwroc_taka_plansze(px-1,py,pz))
                                             ktora_plansza=swiat->zwroc_taka_plansze_TYLKO(px-1,py,pz);
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    else if(ofiara->px==px && ofiara->py==py+1 && ofiara->pz==pz)
                                    {
                                             if(swiat->zwroc_taka_plansze(px,py+1,pz))
                                             ktora_plansza=swiat->zwroc_taka_plansze_TYLKO(px,py+1,pz);
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    else if(ofiara->px==px && ofiara->py==py-1 && ofiara->pz==pz)
                                    {
                                             if(swiat->zwroc_taka_plansze(px,py-1,pz))
                                             ktora_plansza=swiat->zwroc_taka_plansze_TYLKO(px,py-1,pz);
                                             else {jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;}
                                    }
                                    ///KEJZY NA PLANSZE W GORE I PLANSZE W DOL
                                    else {jest_cel=false;celem_jest_plansza=false; jest_ofiara=false;}
                                    continue;
                           }
                           if((ofiara->x<x-3 || ofiara->x>x+3 || ofiara->y<y-3 || ofiara->y>y+3)&& mamy_niepoinformowanego_zombie(plansza))
                           {
                                    krzyczy=true;Plansza*p=plansza;
                                    for(int i=x-5;i<=x+5;++i)
                                    {
                                             for(int j=y-5;j<=y+5;++j)
                                             {
                                                      if(Strefa::w_planszy(i, j))
                                                      {
                                                               if(p->otoczenie[j][i] && p->otoczenie[j][i]->czym_jest==2 && ((Zombie*)p->otoczenie[j][i])->jest_ofiara==false)
                                                               {
                                                                        Zombie*z=(Zombie*)p->otoczenie[j][i]; z->jest_cel=false; z->celem_jest_plansza=false; z->ofiara = ofiara; z->jest_ofiara = true;
                                                                        //Zombie*z=(Zombie*)p->otoczenie[j][i]; z->jest_cel=true; z->celem_jest_plansza=false; z->xc=ofiara->x; z->yc=ofiara->y;
                                                               }
                                                               else if(p->otoczenie[j][i] && p->otoczenie[j][i]->zywy)
                                                               {
                                                                        Objekt_zywy*o=(Objekt_zywy*)p->otoczenie[j][i]; o->uslysz_dzwiek(x,y,2);
                                                               }
                                                      }
                                             }
                                    }
                                    return true;
                           }
                           //czekanie=0;

                                    char gdzie;
                                    if(jest_zaraz_obok(ofiara))
                                    {
                                             ///if i==1 to kopniak
                                             //std::cout<<"uderzam"<<std::endl;
                                             czekanie = 0;
                                             if(ma_tyle_i_odejmij(kk, 5)) {if(uderz(w_ktora_to_strone(x,y,ofiara->x, ofiara->y))==dead) return false;}return true;
                                    }
                                    else
                                    {
                                            ///powinien sie wczesniej rozejrzec aby uniknac pomijania zywych stworzen spoza gatunkow

                                             char decyzja=znajdz_droge(true,ofiara->x,ofiara->y,x,y,plansza);
                                             //std::cout<<ofiara->x<<" "<<ofiara->y<<" "<<decyzja<<std::endl;
                                             what_happened aaa;
                                             if(ma_tyle_i_odejmij(kk, lezy_przez_nogi ? 6 : 4 )) {if((aaa=przesun_sie(decyzja))==dead) return false; else if(aaa==fail) czekanie++; else if(aaa==success) czekanie=0;} else return true;
                                    }
                  }
                  else if(jest_cel)
                  {
                           if(wlasnie_przeszukuje)
                           {
                                    if(co_juz_przeszukane) delete [] co_juz_przeszukane;
                                    co_juz_przeszukane = NULL;
                                    wlasnie_przeszukuje = false;
                           }
                           if(celem_jest_plansza)
                           {
                                    if(ktora_plansza==NULL) {std::cout<<"Mam isc na plansze ale nwm na ktora"; throw "Mam isc na plansze ale nwm na ktora";}
                                    if(ktora_plansza==plansza)
                                    {
                                             jest_cel=false; celem_jest_plansza=false; jest_ofiara=false;

                                             /*przeszukuje = true; co_przeszukane = new bool[12];  for(short dd=0;dd<12;++dd) co_przeszukane[dd] = false;
                                             skad_przeszukuje.x = losuj(3, 17); skad_przeszukuje.y = losuj(3, 9);
                                             dostosuj_cel_przeszukan_do_budynkow();*/

                                             jest_cel = true; xc = losuj(0, 20); yc = losuj(0, 12);

                                             ///znalezlismy nasza plansze
                                             continue;
                                    }
                                    //if(px==1 && py==0 && pz==0)std::cout<<std::endl<<x<<" "<<y<<" "<<p.x<<" "<<p.y<<std::endl;
                                    what_happened aaa;
                                    if(ma_tyle_i_odejmij(kk, 4))
                                    {
                                             if((aaa=przesun_sie(jak_dojsc_na_plansze(ktora_plansza,true)))==fail)
                                             {
                                                      ++czekanie; if(czekanie>5) {jest_ofiara=false;jest_cel=false;celem_jest_plansza=false;}
                                             }
                                             else if(aaa==dead) {return false;}
                                             else if(aaa==success) {czekanie=0;}
                                    }
                                    else return true;
                           }
                           else
                           {
                                    if(!Strefa::w_planszy(xc, yc) || (x==xc && y==yc) || (zaraz_obok(xc,yc,x,y) && (plansza->otoczenie[yc][xc]==NULL || plansza->otoczenie[yc][xc]->czym_jest == 2)))
                                    {
                                             jest_ofiara=false; jest_cel=false; celem_jest_plansza=false;
                                             //std::cout<<" "<<g<<" "<<xc<<" "<<" "<<yc<<" ";
                                             zwrot=daj_zwrot_do_punktu(xc,yc);
                                             patrz();
                                             if(!jest_cel && !jest_ofiara && !wlasnie_przeszukuje)
                                             {
                                                      wlasnie_przeszukuje = true; co_juz_przeszukane = new bool[12];  for(short dd=0;dd<12;++dd) co_juz_przeszukane[dd] = false;
                                                      skad_przeszukuje.x = xc; skad_przeszukuje.y = yc;
                                                      dostosuj_cel_przeszukan_do_budynkow();
                                             }
                                             continue;
                                    }
                                    what_happened aaa;
                                    if(ma_tyle_i_odejmij(kk, lezy_przez_nogi ? 6 : 4)) {if((aaa=przesun_sie(znajdz_droge(true,xc,yc,x,y,plansza)))==dead) return false; else if(aaa==fail) czekanie++; else if(aaa==success) czekanie=0;}else return true;
                           }
                  }
                  else if(wlasnie_przeszukuje)
                  {
                           if(zwrot != 'p' && zwrot != 'l' && zwrot != 'g' && zwrot != 'd') {std::cout<<"zly zwrott ";throw "a";}
                           if(!Strefa::w_planszy(skad_przeszukuje.x, skad_przeszukuje.y)){std::cout<<"zly skad_przeszukuje ";throw "a";}

                           short gx, gy, ktt=-1, ile_nieprzeszukanych = 0, odl = 40;

                           for(short dd = 0; dd < 12; ++dd)
                           {
                                    if(!co_juz_przeszukane[dd])
                                    {
                                             ++ile_nieprzeszukanych;
                                             if(Strefa::w_planszy(zwroc_punkt_przeszukania(dd).x, zwroc_punkt_przeszukania(dd).y) && (ktt ==-1
                                                  || odl>odleglosc_w_kratkach(zwroc_punkt_przeszukania(dd).x, zwroc_punkt_przeszukania(dd).y)))
                                             {ktt = dd; odl = odleglosc_w_kratkach(zwroc_punkt_przeszukania(dd).x, zwroc_punkt_przeszukania(dd).y);}
                                    }
                           }
                           if(ile_nieprzeszukanych<4 || ktt==-1)
                           {
                                    wlasnie_przeszukuje = false; if(co_juz_przeszukane) delete [] co_juz_przeszukane; co_juz_przeszukane = NULL; continue;
                           }
                           /// wyznacz najblizszy
                           gx = zwroc_punkt_przeszukania(ktt).x; gy = zwroc_punkt_przeszukania(ktt).y;

                           if(x==gx && y==gy)
                           {
                                    if(co_juz_przeszukane && ktt>-1 && ktt<12)
                                    co_juz_przeszukane[ktt] = true;
                                    else {std::cout<<"ZOMBIE_PRZESZUKUJE_BLAD1"; throw "D";}
                                    continue;
                           }
                           else if(zaraz_obok(gx,gy,x,y))
                           {
                                    zwrot=daj_zwrot_do_punktu(gx,gy);
                                    if(zwrot!='l'&&zwrot!='p'&&zwrot!='d'&&zwrot!='g')
                                    {std::cout<<"TUUU";throw "DDDDDDD";}
                                    if(co_juz_przeszukane && ktt>-1 && ktt<12)
                                    co_juz_przeszukane[ktt] = true;
                                    else {std::cout<<"ZOMBIE_PRZESZUKUJE_BLAD2"; throw "D";}
                                    patrz();
                                    if(zwrot != 'p' && zwrot != 'l' && zwrot != 'g' && zwrot != 'd') {std::cout<<"zly zwroott ";throw "a";}
                                    continue;
                           }
                           else
                           {
                                    char r = znajdz_droge(true,gx,gy,x,y,plansza);
                                    if(r == 'n')
                                    {
                                             if(co_juz_przeszukane && ktt>-1 && ktt<12)
                                             co_juz_przeszukane[ktt] = true;
                                             else {std::cout<<"ZOMBIE_PRZESZUKUJE_BLAD3"; throw "D";}
                                             continue;
                                    }
                                    else {if(ma_tyle_i_odejmij(kk, lezy_przez_nogi ? 6 : 4)) {if(przesun_sie(r)==dead) return false;}else return true;}
                           }
                           if(zwrot != 'p' && zwrot != 'l' && zwrot != 'g' && zwrot != 'd') {std::cout<<"zly zwroott ";throw "a";}

                  }
                  /*else if(stado!=NULL)
                  {
                           if(stado->x==px && stado->y==py && stado->z==pz)
                           {
                                    jest_cel=true; celem_jest_plansza=false;
                                    switch(stado->gdzie_skrecamy)
                                    {
                                             case 'p':yc=y; xc=18;break;
                                             case 'l':yc=y; xc=4;break;
                                             case 'g':xc=x; yc=2;break;
                                             case 'd':xc=x; yc=10;break;
                                    }
                           }
                           else
                           {
                                    if(px+1==stado->x && stado->y==py && stado->z==pz && swiat->area[px+1][py][pz]->jest_plansza)
                                    {
                                             jest_cel=true; celem_jest_plansza=true; ktora_plansza=(Plansza*)swiat->area[px+1][py][pz];--k;continue;
                                    }
                                    else if(px-1==stado->x && stado->y==py && stado->z==pz && swiat->area[px-1][py][pz]->jest_plansza)
                                    {
                                             jest_cel=true; celem_jest_plansza=true; ktora_plansza=(Plansza*)swiat->area[px-1][py][pz];--k;continue;
                                    }
                                    else if(px==stado->x && stado->y==py+1 && stado->z==pz && swiat->area[px][py+1][pz]->jest_plansza)
                                    {
                                             jest_cel=true; celem_jest_plansza=true; ktora_plansza=(Plansza*)swiat->area[px][py+1][pz];--k;continue;
                                    }
                                    else if(px==stado->x && stado->y==py-1 && stado->z==pz && swiat->area[px][py-1][pz]->jest_plansza)
                                    {
                                             jest_cel=true; celem_jest_plansza=true; ktora_plansza=(Plansza*)swiat->area[px][py-1][pz];--k;continue;
                                    }
                                    else
                                    {
                                             stado=NULL;--k;continue;
                                    }
                           }
                  }*/
                  else
                  {
                           if(Objekt::args->melduj_co_robi_AI)
                           std::cout<<"Zl";
                           czekanie=0;
                           if(losuj(0,4)!=0)
                           {
                                    char dzie=zwrot;
                                    if(w_poprzedniej_stal && losuj(0,2)==0)
                                    {
                                             switch(losuj(0,1)) {case 0:dzie=skrec('p', zwrot);break;case 1:dzie=skrec('l', zwrot);break;}
                                    }
                                             struct punkt p=punkt_przed(dzie,x,y);
                                             what_happened aaa;
                                             if(p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun(dzie);else return true;}
                                             else if(dzie==zwrot)
                                             {
                                                      char cos='p'; if(losuj(0,1)==0) cos='l';
                                                      if((p=punkt_przed(skrec(cos,zwrot),x,y)).x+2 && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                                      {if(ma_tyle_i_odejmij(kk, 6))aaa=przesun(skrec(cos, zwrot));else return true;}
                                                      else if((p=punkt_przed(skrec(skrec('z',cos),zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                                      {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun(skrec(skrec('z', cos), zwrot));else return true;}
                                                      else {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun(skrec('z', zwrot));else return true;}
                                             }
                                             else
                                             {
                                                      if((p=punkt_przed(skrec('z', dzie),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                                      {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun(skrec('z', dzie));else return true;}
                                                      else if((p=punkt_przed(zwrot,x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                                      {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun(zwrot);else return true;}
                                                      else if((p=punkt_przed(skrec('z',zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                                      {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun(skrec('z', zwrot));else return true;}
                                             }
                                    if(aaa==dead) return false;
                                    w_poprzedniej_stal=false;
                           }
                           else w_poprzedniej_stal=true;
                           if(Objekt::args->melduj_co_robi_AI)
                           std::cout<<"ENd";
                           kk-=3;
                  }
         }

         if(Objekt::args->melduj_co_robi_AI)
                           std::cout<<"ZRSK "<<zwrot<<" ";
                           if(zwrot != 'p' && zwrot != 'l' && zwrot != 'd' && zwrot != 'g') throw "D";
}

punkt_na_planszy Zombie::zwroc_punkt_przeszukania(short nr)
{
         switch(nr)
         {
                  case 0: return punkt_na_planszy(skad_przeszukuje.x-3, skad_przeszukuje.y-3);
                  case 1: return punkt_na_planszy(skad_przeszukuje.x+3, skad_przeszukuje.y-3);
                  case 2: return punkt_na_planszy(skad_przeszukuje.x-2, skad_przeszukuje.y-2);
                  case 3: return punkt_na_planszy(skad_przeszukuje.x+2, skad_przeszukuje.y-2);
                  case 4: return punkt_na_planszy(skad_przeszukuje.x-1, skad_przeszukuje.y-1);
                  case 5: return punkt_na_planszy(skad_przeszukuje.x+1, skad_przeszukuje.y-1);
                  case 6: return punkt_na_planszy(skad_przeszukuje.x-1, skad_przeszukuje.y+1);
                  case 7: return punkt_na_planszy(skad_przeszukuje.x+1, skad_przeszukuje.y+1);
                  case 8: return punkt_na_planszy(skad_przeszukuje.x-2, skad_przeszukuje.y+2);
                  case 9: return punkt_na_planszy(skad_przeszukuje.x+2, skad_przeszukuje.y+2);
                  case 10: return punkt_na_planszy(skad_przeszukuje.x-3, skad_przeszukuje.y+3);
                  case 11: return punkt_na_planszy(skad_przeszukuje.x+3, skad_przeszukuje.y+3);
                  default: {std::cout<<"zwroc_punkt_przeszukania ma zly arg"; throw "S";}
                  }
}

bool oba_takie_same(bool a, bool b)
{
         return (!a && !b) || (a && b);
}

void Zombie::dostosuj_cel_przeszukan_do_budynkow()///stara sie dac obszar poszukiwac w calosci w budynku albo poza nim
{
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         while(skad_przeszukuje.x<3) ++skad_przeszukuje.x;
         while(skad_przeszukuje.y<3) ++skad_przeszukuje.y;
         while(skad_przeszukuje.x>17) --skad_przeszukuje.x;
         while(skad_przeszukuje.y>9) --skad_przeszukuje.y;

         if(co_juz_przeszukane == NULL)
         {
                  std::cout<<" co przeszukane is null ";
                  wlasnie_przeszukuje = false;
                  return;
         }

         bool w_budynku = p->to_jest_na_podlodze(skad_przeszukuje.x, skad_przeszukuje.y);

         short d = losuj(0,1) == 0 ? 1 : -1;
         for(int k = 3; k<3; ++k)
         {
                  bool a = oba_takie_same(w_budynku, p->to_jest_na_podlodze(skad_przeszukuje.x+k, skad_przeszukuje.y))
                           , b = oba_takie_same(w_budynku, p->to_jest_na_podlodze(skad_przeszukuje.x-k, skad_przeszukuje.y));
                  if(a != b)
                  {
                           if(!a)
                           {
                                    d = 1; break;
                           }
                           else
                           {
                                    d = -1; break;
                           }
                  }
         }
         for(int k = 0; k < 3; ++k)
                  if(//!Strefa::w_planszy(skad_przeszukuje.x+d*3, skad_przeszukuje.y)||
                      oba_takie_same(w_budynku, p->to_jest_na_podlodze(skad_przeszukuje.x+d*3, skad_przeszukuje.y))
                     || (//Strefa::w_planszy(skad_przeszukuje.x-d*3, skad_przeszukuje.y)&&
                         !oba_takie_same(w_budynku,p->to_jest_na_podlodze(skad_przeszukuje.x-d*3, skad_przeszukuje.y))))
                           break;
                  else
                  {
                           skad_przeszukuje.x -= d*1;
                  }

         d = losuj(0,1) == 0 ? 1 : -1;
         for(int k = 3; k<3; ++k)
         {
                  bool a = oba_takie_same(w_budynku, p->to_jest_na_podlodze(skad_przeszukuje.x, skad_przeszukuje.y+k))
                           , b = oba_takie_same(w_budynku, p->to_jest_na_podlodze(skad_przeszukuje.x, skad_przeszukuje.y-k));
                  if(a != b)
                  {
                           if(!a)
                           {
                                    d = 1; break;
                           }
                           else
                           {
                                    d = -1; break;
                           }
                  }
         }
         for(int k = 0; k < 3; ++k)
                  if(//!Strefa::w_planszy(skad_przeszukuje.x, skad_przeszukuje.y+d*3)||
                      oba_takie_same(w_budynku, p->to_jest_na_podlodze(skad_przeszukuje.x, skad_przeszukuje.y+d*3))
                     || (//Strefa::w_planszy(skad_przeszukuje.x, skad_przeszukuje.y-d*3)&&
                         !oba_takie_same(w_budynku,p->to_jest_na_podlodze(skad_przeszukuje.x, skad_przeszukuje.y-d*3))))
                           break;
                  else
                  {
                           skad_przeszukuje.y -= d*1;
                  }

         ///wyfalsowanie punktow spoza planszy
         if(skad_przeszukuje.x < 3)
         {
                  co_juz_przeszukane[0] = true; co_juz_przeszukane[10] = true;
                  if(skad_przeszukuje.x<2)
                  {
                           co_juz_przeszukane[2] = true; co_juz_przeszukane[8] = true;
                           if(skad_przeszukuje.x<1)
                           {co_juz_przeszukane[4] = true; co_juz_przeszukane[6] = true;}
                  }
         }
         else if(skad_przeszukuje.x > 17)
         {
                  co_juz_przeszukane[1] = true; co_juz_przeszukane[11] = true;
                  if(skad_przeszukuje.x>18)
                  {
                           co_juz_przeszukane[3] = true; co_juz_przeszukane[9] = true;
                           if(skad_przeszukuje.x>19)
                           {co_juz_przeszukane[5] = true; co_juz_przeszukane[7] = true;}
                  }
         }

         if(skad_przeszukuje.y < 3)
         {
                  co_juz_przeszukane[0] = true; co_juz_przeszukane[1] = true;
                  if(skad_przeszukuje.y<2)
                  {
                           co_juz_przeszukane[2] = true; co_juz_przeszukane[3] = true;
                           if(skad_przeszukuje.y<1)
                           {co_juz_przeszukane[4] = true; co_juz_przeszukane[5] = true;}
                  }
         }
         else if(skad_przeszukuje.y > 9)
         {
                  co_juz_przeszukane[10] = true; co_juz_przeszukane[11] = true;
                  if(skad_przeszukuje.y>10)
                  {
                           co_juz_przeszukane[8] = true; co_juz_przeszukane[9] = true;
                           if(skad_przeszukuje.y>11)
                           {co_juz_przeszukane[6] = true; co_juz_przeszukane[7] = true;}
                  }
         }
}

int Zombie::get_co_to()
{
         int a=590;
         if(lezy)
         {
                  a+=135;if(jest_ofiara) a+=18; else if(jest_cel || wlasnie_przeszukuje) a+=9;
         }
         else
         {
                  if(krzyczy) a+=126;
                  else
                  {
                  switch(zwrot) {case 'p': a+=27;case 'l':a+=27;case 'g':a+=27; case 'd':break;}
                  if(jest_ofiara) a+=18; else if(jest_cel || wlasnie_przeszukuje) a+=9;
                  }

         }
         if(hp_noga_1<=0) a+=3; if(hp_noga_2<=0) a+=3;if(hp_reka_1<=0) a+=1; if(hp_reka_2<=0) a+=1;
         return a;
}

#include "swiat2.h"

void Zombie::patrz()
{
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" z% "<<" "<<zwrot<<" ";
         if(lezy) {if(Objekt::args->melduj_co_robi_AI)std::cout<<" z pptrzyl ";return;}
         //int wiodaca=x; if(zwrot=='g' || zwrot=='d') wiodaca=y; ///ktora pokazuje strone
         int poszerzajaca=x; if(zwrot=='l' || zwrot=='p') poszerzajaca=y; ///ktora pokazuje strone
         int xw, yw;Plansza*a=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" A ";
         for(int i=3; i<47; i+=2)
         {
                  for(int j=poszerzajaca-(i/2); j<=poszerzajaca+(i/2);j++)
                  {
                           switch(zwrot){case 'd':{xw=j;yw=y+(i-3)/2;break;}case 'g':{xw=j;yw=y-(i-3)/2;break;}case 'p':{yw=j;xw=x+(i-3)/2;break;}case'l':{yw=j;xw=x-(i-3)/2;break;}}

                           if((xw!=x || yw!=y) && Strefa::w_planszy(xw, yw) && a->otoczenie[yw][xw]!=NULL &&
                                    (a->otoczenie[yw][xw]->zywy || (a->otoczenie[yw][xw]->czym_jest==32 && ((Lozko*)a->otoczenie[yw][xw])->ktos_tu_spi()))
                                             && a->otoczenie[yw][xw]->czym_jest!=2)
                           {
                                    if(Objekt::args->melduj_co_robi_AI)std::cout<<" X ";//////////////////////////////////////////////////////////////////////////////////
                                    bool na_pewno_w_zasiegu=true;
                                    int skrot=0; ///skrocenie_widzialnej_odl
                                    int odciecia=0; ///odciecia zasiegu wzroku
                                    int poprawka=0; ///wzgl postawy
                                    int kamuflaz=0;


                                    if(a->otoczenie[yw][xw]->czym_jest==10)
                                    {
                                             Gracz *g=(Gracz*)a->otoczenie[yw][xw];
                                             switch(g->postawa) {case 'c':odciecia+=2;poprawka+=10;skrot+=5;case's':odciecia+=2;poprawka+=10;skrot+=7;case 'r':break;}
                                             switch(g->kamuflaz()){case 26:++odciecia; case 20:++odciecia; case 16:++odciecia; case 12:++odciecia; case 8:++odciecia;}
                                             poprawka+=g->kamuflaz();
                                             skrot+=g->kamuflaz()/2;

                                             if(g->postawa=='r')
                                             {
                                                      if(skrot>9) skrot=9;
                                                      if(poprawka>30) poprawka=30;
                                             }
                                             else if(g->postawa=='s')
                                             {
                                                      if(skrot>12) skrot=12;
                                                      if(poprawka>40) poprawka=40;
                                             }
                                             else
                                             {
                                                      if(skrot>17) skrot=17;
                                             }
                                             kamuflaz=g->kamuflaz();
                                    }
                                    if(Objekt::args->melduj_co_robi_AI)std::cout<<"K";

                                    skrot += a->oswietlenie[yw][xw]/17;
                                    skrot -= (a->oswietlenie[y][x] - a->oswietlenie[yw][xw])/17;

                                    na_pewno_w_zasiegu=!((zwrot=='p' && xw-x>20-skrot)||(zwrot=='l' && x-xw>20-skrot)
                                       ||(zwrot=='g' && y-yw>20-skrot)||(zwrot=='d' && yw-y>20-skrot)||czy_widzi_wzgl_zwezania(3,2,odciecia,xw,yw));
                                       if(Objekt::args->melduj_co_robi_AI)std::cout<<"D";

                                    if(na_pewno_w_zasiegu && widzi_obiekt(a,xw,yw,x,y,kamuflaz,poprawka))
                                    {if(Objekt::args->melduj_co_robi_AI)std::cout<<"L";

                                             if(wlasnie_przeszukuje)
                                             {
                                                      delete [] co_juz_przeszukane; co_juz_przeszukane = NULL;
                                                      wlasnie_przeszukuje = false;
                                             }
                                             jest_ofiara=true; jest_cel=false; celem_jest_plansza=false; ofiara=a->otoczenie[yw][xw];
                                             //if(ofiara!=NULL)std::cout<<"Znalazlem cos"<<ofiara->zywy<<std::endl;else std::cout<<"NULL"<<std::endl;
                                             if(Objekt::args->melduj_co_robi_AI)std::cout<<" z& ";
                                             return;
                                    }
                                    else if(Objekt::args->melduj_co_robi_AI)std::cout<<"T";
                           }
                           else if((xw!=x || yw!=y) && wlasnie_przeszukuje && Strefa::w_planszy(xw, yw))
                           {
                                    if(co_juz_przeszukane == NULL) {std::cout<<"przeszukuje a co_przeszukane null"; throw "DDD";}
                                    //std::cout<<" "<<skad_przeszukuje.x<<" "<<skad_przeszukuje.y<<" ";

                                    if(xw>=skad_przeszukuje.x-3 && xw<=skad_przeszukuje.x+3 && yw>=skad_przeszukuje.y-3 && yw<=skad_przeszukuje.y+3
                                       && abs(skad_przeszukuje.x - xw) == abs(skad_przeszukuje.y - yw) && !((zwrot=='p' && xw-x>20)||(zwrot=='l' && x-xw>20)
                                       ||(zwrot=='g' && y-yw>20)||(zwrot=='d' && yw-y>20)||czy_widzi_wzgl_zwezania(3,2,0,xw,yw))
                                       &&  widzi_obiekt(a,xw,yw,x,y,0,0))
                                    {
                                             short d = xw < skad_przeszukuje.x ? 0 : 1, u = x < skad_przeszukuje.x ? -1 : 1;
                                             if(yw > skad_przeszukuje.y)
                                             {
                                                      if(xw == skad_przeszukuje.x + u*1 && yw == skad_przeszukuje.y + 1)
                                                      co_juz_przeszukane[6 + d] = true;
                                                      else if(xw == skad_przeszukuje.x + u*2 && yw == skad_przeszukuje.y + 2)
                                                      co_juz_przeszukane[8 + d] = true;
                                                      else if(xw == skad_przeszukuje.x + u*3 && yw == skad_przeszukuje.y + 3)
                                                      co_juz_przeszukane[10 + d] = true;
                                             }
                                             else if(yw < skad_przeszukuje.y)
                                             {
                                                      if(xw == skad_przeszukuje.x + u*1 && yw == skad_przeszukuje.y - 1)
                                                      co_juz_przeszukane[4 + d] = true;
                                                      else if(xw == skad_przeszukuje.x + u*2 && yw == skad_przeszukuje.y - 2)
                                                      co_juz_przeszukane[2 + d] = true;
                                                      else if(xw == skad_przeszukuje.x + u*3 && yw == skad_przeszukuje.y - 3)
                                                      co_juz_przeszukane[0 + d] = true;
                                             }
                                    }
                           }
                  }
         }
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" z& ";
}

void Zombie :: zapisz(std::ofstream *ofs)
{

}

Zombie::Zombie(Zombie_przejsciowe*a, int xx, int yy,int ppx,int ppy,int ppz):Objekt_zywy(2)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=3;
         co_to=0; px=ppx;py=ppy;pz=ppz;
         ///jest_ofiara=true; ofiara=swiat->aktualny;
}

Zombie_przejsciowe::Zombie_przejsciowe(Zombie*a)
{
         czym_jest=2;
}

void Zombie_przejsciowe :: zapisz(std::ofstream *ofs)
{

}

Zombie::Zombie():Objekt_zywy(2)
{
         wykonuje_ruch=true;wysokosc=3;
}

Zombie::~Zombie()
{
         if(co_juz_przeszukane)
                  delete [] co_juz_przeszukane;
}

void Zombie::dzwiek_przesuniecia(int xx, int yy)
{
         wydaj_dzwiek(false, 3, xx,yy,2);
}

Zombie_przejsciowe::Zombie_przejsciowe()
{
         czym_jest=2;
}



