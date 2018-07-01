#include "swiat.h"
#include <windows.h>











int Sarna::get_co_to()
{
         int a=210;
         switch(zwrot) {case 'd':a+=8;case 'g':a+=8;case 'p':a+=8;case 'l':break;}
         if(zwrot_ostatni=='l') a+=1;

         if(zaalarmowana)
         {

         }
         else if(jedzaca)
         {
                  a+=2;
         }
         else if(biegnie)
         {
                  a+=4;
         }
         else
         {
                  a+=6;
         }
         return a;
}

void Sarna :: zapisz(std::ofstream *ofs)
{

}

what_happened Sarna::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         if(this==NULL) {std::cout<<"NULL na Sarna::zostan_uderzony"; return dead;}
         punkty_ruchu -= wsp_zajecia;
         //args->obrazenia=new int(212);
         //args->gdzie_obrazenia=new struct punkt; args->gdzie_obrazenia->x=x;args->gdzie_obrazenia->y=y+args->X_kratka/2;
         //args->ilosc_zadan=1;
        // for(;args->ile_nad<args->X_kratka;++args->ile_nad)Sleep(500/(float)args->X_kratka);
         //args->ilosc_zadan=0;
         animacja_damage(obrazenia);

          jest_cel=false; celem_jest_plansza=false; zaalarmowana=true;
         ktora_plansza = wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem ,false);
         jest_ofiara = ktora_plansza!=NULL;

         HP-=obrazenia;
         if(HP<=0)
         {
                  przestan_byc_ofiara(1);
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]=NULL;
                  Srodowisko::dodaj_objekt((new Zwloki(czym_jest,0,x,y,px,py,pz)),x,y,swiat->zwroc_taka_plansze_TYLKO(px,py,pz));
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->zaktualizuj_widoki(x,y,x,y);
                  smierc();
                   return dead;
         }
         return success;
}

short Sarna::latwopalnosc(){return 0;}

Sarna::Sarna():Objekt_zywy(8)
{
         nie_wykonal_ruchu=true;wykonuje_ruch=true; wysokosc=2;
}

void Sarna::uslysz_dzwiek(int dx,int dy,int rodzaj)
{
         if(rodzaj==8) return;
         if(jest_ofiara) return;
         jest_ofiara=true; jest_cel=false; celem_jest_plansza=false; zaalarmowana=true;
         int aaa=losuj(1,4);
         while(true)
         {
                  switch(aaa)
                  {
                  case 1:if(swiat->zwroc_taka_plansze(px+1,py,pz)){ktora_plansza=swiat->zwroc_taka_plansze(px+1,py,pz);return;}
                  case 2:if(swiat->zwroc_taka_plansze(px-1,py,pz)){ktora_plansza=swiat->zwroc_taka_plansze(px-1,py,pz);return;}
                  case 3:if(swiat->zwroc_taka_plansze(px,py+1,pz)){ktora_plansza=swiat->zwroc_taka_plansze(px,py+1,pz);return;}
                  case 4:if(swiat->zwroc_taka_plansze(px,py-1,pz)){ktora_plansza=swiat->zwroc_taka_plansze(px,py-1,pz);return;}
                  }
                  aaa=1;
         }
}

void Sarna::uslysz_dzwiek(Plansza *a,int rodzaj)
{
         if(rodzaj==8) return;
}

void Sarna::dzwiek_przesuniecia(int xx, int yy)
{
         if(biegnie) wydaj_dzwiek(false, 2, xx,yy,8);
}

bool Sarna::rusz_sie()
{
         short p_ruchu = punkty_ruchu;
         punkty_ruchu = 25;
         if(jedzenie>0) --jedzenie; if(woda>0) --woda;
         Swiat* swiat=Objekt::swiat;
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         zaalarmowana=false;jedzaca=false;
         short h=0;
         for(int kk=p_ruchu; kk>0; kk-=5)
         {
                  if(++h>10) return 1;
                  plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);

                  if(Objekt::args->melduj_co_robi_AI)
                  std::cout<<"S"<<jest_ofiara<<jest_cel<<celem_jest_plansza<<"A";

                  if(jest_ofiara)///ucieka
                  {
                           if(ktora_plansza==NULL)
                           {
                                    ktora_plansza = wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, false);
                                    if(ktora_plansza != NULL) {if(Objekt::args->melduj_pom) std::cout<<"5"; kk-=5; continue;}

                                    biegnie=true; jedzaca=false; zaalarmowana=false;
                                    if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<"u_w_p";
                                    zwrot_odl a = wyznacz_punkt_ucieczki_w_obrebie_planszy();
                                    if(Objekt::args->melduj_co_robi_AI)
                                    std::cout<<" "<<a.x<<" "<<a.y<<" "<<a.u<<" ";
                                    if(a.u != -1)
                                    {
                                             if(przesun(znajdz_ucieczke(a.u, a.x, a.y, x, y, plansza))==dead) return false;
                                    }
                           }
                           else if(ktora_plansza==plansza)
                           {
                                    jest_ofiara=false; celem_jest_plansza=false; jest_cel=false;biegnie =false;jedzaca=false;
                                    ///znalezlismy nasza plansze
                                    if(Objekt::args->melduj_pom) std::cout<<"0"; kk-=5; continue;
                           }
                           else
                           {
                                    biegnie=true; jedzaca=false; zaalarmowana=false;
                                    what_happened aaa = przesun(jak_uciec_na_plansze(ktora_plansza));
                                    if(aaa == dead)
                                    {
                                             return false;
                                    }
                                    else if(aaa == fail)
                                    {
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<"Wip";
                                             ktora_plansza = wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, false);
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<"Wyb";
                                             if(Objekt::args->melduj_pom) std::cout<<"1"; kk-=5; continue;
                                    }
                                    else if(aaa==success);
                           }
                           ///tu nie moze nic byc
                  }
                  else if(jest_cel)
                  {
                           if(celem_jest_plansza)
                           {
                                    if(ktora_plansza==NULL) {if(przesun_sie_losowo()==dead) return false; jest_cel=false; celem_jest_plansza=false; return true;}
                                    else if(ktora_plansza==plansza)
                                    {
                                             jest_ofiara=false; celem_jest_plansza=false; jest_cel=false;biegnie =false;jedzaca=false;pamiec=0;
                                             ///znalezlismy nasza plansze
                                             if(Objekt::args->melduj_pom) std::cout<<"2"; kk-=5;continue;
////////////////////////////////////////
                                    }
                                    else
                                    {
                                             char r = jak_uciec_na_plansze(ktora_plansza);
                                             if(r != 'n')
                                             {
                                                      biegnie=true;jedzaca=false;zaalarmowana=false;
                                                      if(przesun(r)==dead) return false;
                                             }
                                             else
                                             {
                                                      //if(jak_dojsc_na_plansze(ktora_plansza,false)!='n') {std::cout<<std::endl<<"DDDD"<<std::endl;throw "fff";}
                                                      if(Objekt::args->melduj_co_robi_AI)
                                                      std::cout<<" Wip";
                                                      //Plansza *d =ktora_plansza;
                                                      ktora_plansza = wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, false);
                                                      /*if(d==ktora_plansza)
                                                      {
                                                               std::cout<<"ASFASFSAFASF";throw "D";
                                                      }*/
                                                      if(ktora_plansza!=NULL)
                                                      {
                                                               if(Objekt::args->melduj_co_robi_AI)
                                                               std::cout<<" O ta ";
                                                               if(Objekt::args->melduj_pom) std::cout<<"3"; kk-=5; continue;
                                                      }
                                                      else
                                                      {
                                                               if(Objekt::args->melduj_co_robi_AI)
                                                               std::cout<<" Ndmp ";
                                                               biegnie=false;jedzaca=false; jest_cel = false; celem_jest_plansza = false;
                                                               if(Objekt::args->melduj_co_robi_AI) std::cout<<" Nie moge znalezc drogi";
                                                      }
                                             }
                                    }
                           }
                           else
                           {
                                    if(zaraz_obok(xc,yc,x,y))
                                    {
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<"Jzozj";
                                             jedzaca=true;biegnie=false; bool najadla_sie=false;
                                             if(yc<13 && yc>-1 && xc >-1 && xc<21 && plansza->otoczenie[yc][xc]!=NULL && plansza->otoczenie[yc][xc]->czym_jest==21)
                                                      {if(woda<200)woda+=20;if(woda>=120)najadla_sie=true;}
                                             else if(yc<13 && yc>-1 && xc >-1 && xc<21 && plansza->srodowisko[yc][xc]!=NULL && plansza->srodowisko[yc][xc]->ma_to(22))
                                             {
                                                      if(plansza->srodowisko[yc][xc]->zjedz_rosline(22))jedzenie+=20; else {if(plansza->ma_gracza)Sleep(500);jedzaca=false;}
                                                      plansza->zaktualizuj_widoki(x,y,x,y);if(jedzenie>=120 || (plansza->srodowisko[yc][xc]!=NULL && !plansza->srodowisko[yc][xc]->ma_to(22))) najadla_sie=true;
                                             }
                                             else
                                             {
                                                      jedzaca = false; najadla_sie = true;
                                             }
                                             if(najadla_sie){jest_cel=false;celem_jest_plansza=false;}
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<"Zjd";return true;
                                    }
                                    else
                                    {
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<"Jd";
                                             if(!(jedzenie+woda<100 || jedzenie<50 || woda<50)){biegnie=false;kk-=10;} else biegnie=true;
                                             char s=znajdz_ucieczke(3,xc,yc,x,y,plansza);zaalarmowana=false;
                                             if(s=='n' && czekanie++>5) {jest_cel = false;celem_jest_plansza=false;}
                                                      if (s!='n') czekanie=0;
                                             if(przesun(s)==dead) return false;
                                    }

                           }
                  }
                  else if(jedzenie<100 || woda<100)
                  {
                           biegnie=false;jedzaca=false;
                           if((pamiec&1)!=1 || (pamiec&2)!=2 || (pamiec&4)!=4)
                           {
                                    if(x<7 && (pamiec&2)!=2 && znajdz_droge(false,10,y,x,y,plansza)!='n'){xc=10;yc=y;jest_cel=true;celem_jest_plansza=false;if(Objekt::args->melduj_pom) std::cout<<"8"; continue;}
                                    else if(x<7 && (pamiec&4)!=4 && znajdz_droge(false,18,y,x,y,plansza)!='n'){xc=18;yc=y;jest_cel=true;celem_jest_plansza=false;if(Objekt::args->melduj_pom) std::cout<<"9";;continue;}
                                    else if(x<15 && (pamiec&1)!=1 && znajdz_droge(false,3,y,x,y,plansza)!='n'){xc=3;yc=y;jest_cel=true;celem_jest_plansza=false;if(Objekt::args->melduj_pom) std::cout<<"10";continue;}
                                    else if(x<15 && (pamiec&4)!=4 && znajdz_droge(false,18,y,x,y,plansza)!='n'){xc=18;yc=y;jest_cel=true;celem_jest_plansza=false;if(Objekt::args->melduj_pom) std::cout<<"11";;continue;}
                                    else if((pamiec&2)!=2 && znajdz_droge(false,10,y,x,y,plansza)!='n'){xc=10;yc=y;jest_cel=true;celem_jest_plansza=false;if(Objekt::args->melduj_pom) std::cout<<"12";continue;}
                                    else if((pamiec&1)!=1 && znajdz_droge(false,3,y,x,y,plansza)!='n'){xc=3;yc=y;jest_cel=true;celem_jest_plansza=false;if(Objekt::args->melduj_pom) std::cout<<"13";continue;}
                                    else
                                    {
                                             ktora_plansza =wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, false);
                                             celem_jest_plansza = true; jest_cel = true;
 ///////////////////////////////
                                             if(Objekt::args->melduj_pom) std::cout<<"4"; kk-=5; continue;
                                    }
                           }
                           else
                           {
                                    ktora_plansza =wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, false);
                                    //if(ktora_plansza != NULL && jak_uciec_na_plansze(ktora_plansza)=='n')
                                   //    {std::cout<<"HAHHHA";throw "G";}
                                    //std::cout<<" "<<ktora_plansza<<" ";
                                    celem_jest_plansza = true; jest_cel = true;
                                    //--k; continue;
                           }
                  }
                  else
                  {
                           zaalarmowana=false;
                           biegnie=false;
                           return przesun_sie_losowo()==success;
                           return true;
                  }
         }
         return true;
}

what_happened Sarna::przesun_sie_losowo()
{
         Plansza *plansza = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(losuj(0,4)!=0)
         {
                  char dzie=zwrot;
                  if(losuj(0,2)==0)
                  {
                           switch(losuj(0,2)) {case 0:dzie=skrec('p', zwrot);break;case 1:dzie=skrec('l', zwrot);break;case 2:break;}
                  }
                  struct punkt p=punkt_przed(dzie,x,y);
                  if(p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                  return przesun(dzie);
                  else if(dzie==zwrot)
                  {
                           char cos='p'; if(losuj(0,1)==0) cos='l';
                           if((p=punkt_przed(skrec(cos,zwrot),x,y)).x+2 && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                           return przesun(skrec(cos, zwrot));
                           else if((p=punkt_przed(skrec(skrec('z',cos),zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                           return przesun(skrec(skrec('z', cos), zwrot));
                           else return przesun(skrec('z', zwrot));
                  }
                  else
                  {
                           if((p=punkt_przed(skrec('z', dzie),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                           return przesun(skrec('z', dzie));
                           else if((p=punkt_przed(zwrot,x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                           return przesun(zwrot);
                           else if((p=punkt_przed(skrec('z',zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                           return przesun(skrec('z', zwrot));
                  }
         }
}

void Sarna::patrz()
{
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" s% "<<" "<<zwrot<<" ";
         if(x<7) pamiec=pamiec|1;else if(x<15) pamiec=pamiec|2; else pamiec=pamiec|4;
         int poszerzajaca=x; if(zwrot=='l' || zwrot=='p') poszerzajaca=y; ///ktora pokazuje strone
         int xw, yw;Plansza*a=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         bool jest_woda=false, jest_trawa=false; int wx,wy,tx,ty;if(Objekt::args->melduj_co_robi_AI)std::cout<<"A";
         for(int i=3; i<47; i+=2)
         {
                  for(int j=poszerzajaca-(i/2); j<=poszerzajaca+(i/2);j++)
                  {
                           switch(zwrot){case 'd':{xw=j;yw=y+(i-3)/2;break;}case 'g':{xw=j;yw=y-(i-3)/2;break;}
                           case 'p':{yw=j;xw=x+(i-3)/2;break;}case'l':{yw=j;xw=x-(i-3)/2;break;}}

                           if(yw>-1 && yw<13 && xw>-1 && xw<21 && (xw!=x || yw!=y))
                           {
                                    if(a->otoczenie[yw][xw]!=NULL && a->otoczenie[yw][xw]->zywy && a->otoczenie[yw][xw]->czym_jest!=8)
                                    {
                                             if(Objekt::args->melduj_co_robi_AI)std::cout<<"X";
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
                                             if(Objekt::args->melduj_co_robi_AI)std::cout<<"K";
                                             na_pewno_w_zasiegu=!((zwrot=='p' && xw-x>20-skrot)||(zwrot=='l' && x-xw>20-skrot)
                                                ||(zwrot=='g' && y-yw>20-skrot)||(zwrot=='d' && yw-y>20-skrot)||czy_widzi_wzgl_zwezania(3,2,odciecia,xw,yw));
                                             if(Objekt::args->melduj_co_robi_AI)std::cout<<"D";
                                             if(!jest_ofiara && na_pewno_w_zasiegu && widzi_obiekt(a,xw,yw,x,y,kamuflaz,poprawka))
                                             {
                                                      if(Objekt::args->melduj_co_robi_AI)std::cout<<"L";
                                                      jest_ofiara=true; jest_cel=false; celem_jest_plansza=false; zaalarmowana=true;
                                                      ktora_plansza = wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem ,false);
                                                      jest_ofiara = true;
                                                      return;
                                             }
                                             else if(Objekt::args->melduj_co_robi_AI)std::cout<<"L";
                                    }
                                    else if(!jest_woda && woda<100 && a->otoczenie[yw][xw]!=NULL && a->otoczenie[yw][xw]->czym_jest==21)
                                    {
                                             jest_woda=true; wx=xw; wy=yw;
                                    }
                                    else if(!jest_trawa && jedzenie<100 &&  a->otoczenie[yw][xw]==NULL && a->srodowisko[yw][xw] && a->srodowisko[yw][xw]->wierzch()
                                            && a->srodowisko[yw][xw]->wierzch()->czym_jest==22 && ((Trawa*)a->srodowisko[yw][xw]->wierzch())->ktora==0)
                                    {
                                             jest_trawa=true; tx=xw; ty=yw;
                                    }
                           }

                  }
         }
         if(jest_woda && woda<100 && ((!jest_trawa && (jedzenie>50 || woda<20)) || (jedzenie>50 || woda<jedzenie+10)))
         {
                  jest_cel=true; xc=wx; yc=wy; celem_jest_plansza=false;
         }
         else if(jest_trawa && jedzenie<100)
         {
                  jest_cel=true; xc=tx; yc=ty; celem_jest_plansza=false;
         }
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" s& "<<" "<<zwrot<<" ";
}

Sarna::Sarna(Sarna_przejsciowa* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_zywy(8)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=3;
         co_to=0; px=ppx;py=ppy;pz=ppz;
         zwrot_ostatni='l';jedzaca=false;zaalarmowana=false;biegnie=false;
         jedzenie=a->jedzenie;woda=a->woda;HP=a->HP;
}

Sarna_przejsciowa::Sarna_przejsciowa(Sarna*a)
{
         czym_jest=8;
         jedzenie=a->jedzenie;woda=a->woda;HP=a->HP;
}

Sarna_przejsciowa::~Sarna_przejsciowa()
{

}

void Sarna_przejsciowa::zapisz(std::ofstream *a)
{

}

Sarna_przejsciowa::Sarna_przejsciowa()
{
         czym_jest=8;
}





int Niedzwiedz::get_co_to()
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

void Niedzwiedz :: zapisz(std::ofstream *ofs)
{

}

what_happened Niedzwiedz::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         if(this==NULL) {std::cout<<"NULL na Niedzwiedz::zostan_uderzony"; return dead;}
         punkty_ruchu -= wsp_zajecia;
         animacja_damage(obrazenia);
         zaalarmowany=true;
         Plansza *a=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         int aaa=losuj(1,8); bool  br=false;
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
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->otoczenie[y][x]=NULL;
                  Srodowisko::dodaj_objekt((new Zwloki(czym_jest,0,x,y,px,py,pz)),x,y,swiat->zwroc_taka_plansze_TYLKO(px,py,pz));
                  swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->zaktualizuj_widoki(x,y,x,y);
                   smierc();
                  return dead;
         }
         return success;
}

Niedzwiedz::Niedzwiedz():Objekt_zywy(9)
{
         nie_wykonal_ruchu=true;wykonuje_ruch=true; wysokosc=3;
}

Niedzwiedz::~Niedzwiedz()
{

}

what_happened Niedzwiedz::przesun_sie(char decyzja)
{
         if(Objekt::args->melduj_co_robi_AI) std::cout<<" rPrz ";
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(decyzja=='n') {if(Objekt::args->melduj_co_robi_AI) std::cout<<" rzPrz ";return fail;}
         struct punkt p=punkt_przed(decyzja, x, y);
         if((p.y>12 || p.y<0 || p.x>20 || p.x<0)||(plansza->otoczenie[p.y][p.x]==NULL))
         {
                  what_happened aaa = przesun(decyzja);
                  if(aaa==success) rozpedzony=true;
                  if(Objekt::args->melduj_co_robi_AI) std::cout<<" rozPrz ";return aaa;
         }
         else {what_happened aaa = uderz(decyzja);if(Objekt::args->melduj_co_robi_AI) std::cout<<" rzPrz ";return aaa;}
}

void Niedzwiedz::uslysz_dzwiek(int dx,int dy,int rodzaj)
{
         if(jest_ofiara) {if((px==ofiara->px && py==ofiara->py && pz==ofiara->pz)&&(std::sqrt((float)((ofiara->x-x)*(ofiara->x-x)+(ofiara->y-y)*(ofiara->y-y)))<std::sqrt((float)((dx-x)*(dx-x)+(dy-y)*(dy-y)))))return;}
         jest_ofiara=false; jest_cel=true; celem_jest_plansza=false; zaalarmowany=true; xc=dx, yc=dy;
}

void Niedzwiedz::uslysz_dzwiek(Plansza *a,int rodzaj)
{
         if(!jest_ofiara) {jest_ofiara=false; jest_cel=true; celem_jest_plansza=true; zaalarmowany=true; ktora_plansza=a;}
}

void Niedzwiedz::dzwiek_przesuniecia(int xx, int yy)
{
         if(biegnie) wydaj_dzwiek(false, 3, xx,yy,9); else wydaj_dzwiek(false, 2, xx,yy,9);
}

what_happened Niedzwiedz::uderz(char strona)
{
         if(strona == 'p' || strona == 'l') zwrot = strona;
         animacja_ataku(strona);struct punkt p=punkt_przed(strona, x, y);
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         zwrot = daj_zwrot_do_punktu(p.x, p.y);
         if((daj_zwrot_do_punktu(p.x, p.y) == 'p' && zwrot_ostatni=='l') || (daj_zwrot_do_punktu(p.x, p.y) =='l' && zwrot_ostatni=='p'))
                  zwrot_ostatni = daj_zwrot_do_punktu(p.x, p.y);
         if(p.x<21 && p.x>-1 && p.y<13 && p.y>-1 && plansza->otoczenie[p.y][p.x]!=NULL) {plansza->otoczenie[p.y][p.x]->zostan_uderzony(losuj(40,60)-(30-HP/10)+(rozpedzony ? losuj(20,40)-(30-HP/10) : 0),9,0, rozpedzony ? 5 : 3);{rozpedzony=false; return success;}}
         rozpedzony = false;
         return fail;
}

bool Niedzwiedz::rusz_sie()
{
         rozpedzony = false;
         short p_ruchu = punkty_ruchu;
         punkty_ruchu = 10;
         if(jedzenie>0) --jedzenie; if(woda>0) --woda;
         Swiat* swiat=Objekt::swiat;
         Plansza* plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         zaalarmowany=false;
         short h=0;
         for(short kk=p_ruchu; kk>0;)
         {
                  if(++h>10) {/*std::cout<<jest_ofiara<<" "<<jest_cel<<" "<<xc<<" "<<yc<<" "<<celem_jest_plansza<<" "<<jedzenie<<" "<<woda<<std::endl;*/return 1;}
                  plansza=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
                  if(jest_ofiara)
                  {
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
                           czekanie=0;

                                    zaalarmowany=false;


                                    if(jest_zaraz_obok(ofiara))
                                    {
                                             if(ofiara->czy_lezy()==false)
                                             {biegnie=false;atakujacy=true; if(ma_tyle_i_odejmij(kk, 4)) {if(uderz(w_ktora_to_strone(x,y,ofiara->x, ofiara->y))==dead) return false;} else return true;}
                                             else
                                             {
                                                      return true;
                                             }
                                    }
                                    else
                                    {
                                            ///powinien sie wczesniej rozejrzec aby uniknac pomijania zywych stworzen spoza gatunkow
                                             char decyzja=znajdz_droge(true,ofiara->x,ofiara->y,x,y,plansza);
                                             //std::cout<<ofiara->x<<" "<<ofiara->y<<" "<<decyzja<<std::endl;
                                             atakujacy=false;biegnie=true; if(ma_tyle_i_odejmij(kk, 3)) {if(przesun_sie(decyzja)==dead) return false;} else return true;
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
                                             continue;
                                    }
                                    else
                                    {
                                             char r = jak_dojsc_na_plansze(ktora_plansza, true);
                                             if(r != 'n')
                                             {
                                                      atakujacy=false;biegnie=true;
                                                      if(ma_tyle_i_odejmij(kk, 3)) {if(przesun_sie(r)==dead) return false;;} else return true;
                                                      czekanie=0;
                                             }
                                             else
                                             {
                                                      ++czekanie; if(czekanie>5) {jest_ofiara=false;jest_cel=false;celem_jest_plansza=false;}
                                                      if(Objekt::args->melduj_co_robi_AI)
                                                      std::cout<<" Nzndr";
                                             }
                                    }
                           }
                           else
                           {
                                    bool najadl_sie =false;
                                    if(zaraz_obok(xc,yc,x,y))
                                    {
                                             if(Objekt::args->melduj_co_robi_AI) std::cout<<" Joc ";
                                             zwrot=daj_zwrot_do_punktu(xc,yc); patrz();
                                             if(jest_ofiara) { continue;}

                                             biegnie=false; atakujacy=false;
                                             if(Strefa::w_planszy(xc,yc) && plansza->otoczenie[yc][xc]!=NULL && plansza->otoczenie[yc][xc]->czym_jest==21)
                                             {
                                                      kk-=4; if(woda<200)woda+=20;if(woda>=120)najadl_sie=true;
                                             }
                                             else if(Strefa::w_planszy(xc,yc) && plansza->srodowisko[yc][xc]!=NULL && plansza->srodowisko[yc][xc]->ma_to(22))
                                             {
                                                      kk-=4;
                                                      if(plansza->srodowisko[yc][xc]->zjedz_rosline(22))jedzenie+=20; else {if(plansza->ma_gracza)Sleep(1);}
                                                      plansza->zaktualizuj_widoki(x,y,x,y);if(jedzenie>=120 || (plansza->srodowisko[yc][xc]!=NULL && !plansza->srodowisko[yc][xc]->ma_to(22))) najadl_sie=true;
                                             }
                                             else
                                             {
                                                      atakujacy=false;biegnie=true; if(ma_tyle_i_odejmij(kk, 3))  {if(przesun_sie(znajdz_droge(true,xc,yc,x,y,plansza))==dead) return false;} else return true; czekanie=0;
                                             }
                                             if(najadl_sie){jest_cel=false;celem_jest_plansza=false;}
                                             if(Objekt::args->melduj_co_robi_AI)
                                             std::cout<<" Zjd ";return true;
                                    }
                                    else
                                    {
                                             if(Objekt::args->melduj_co_robi_AI) std::cout<<" Cd ";
                                             atakujacy=false; biegnie=true;
                                             char r = znajdz_droge(true,xc,yc,x,y,plansza);
                                             if(r=='n' && czekanie++>5) {jest_cel = false;celem_jest_plansza=false;}
                                             if (r!='n') czekanie=0;
                                             if(ma_tyle_i_odejmij(kk, 3))
                                             {if(przesun_sie(r)==dead) return false;} else return true;
                                    }
                           }
                  }
                  else if(jedzenie<100 || woda<100)
                  {
                           biegnie=false;
                           if((pamiec&1)!=1 || (pamiec&2)!=2 ||(pamiec&4)!=4)
                           {
                                    if(x<7 && (pamiec&2)!=2 && znajdz_droge(true,10,y,x,y,plansza)!='n'){xc=10;yc=y;jest_cel=true;continue;}
                                    else if(x<7 && (pamiec&4)!=4 && znajdz_droge(true,18,y,x,y,plansza)!='n'){xc=18;yc=y;jest_cel=true;continue;}
                                    else if(x<15 && (pamiec&1)!=1 && znajdz_droge(true,3,y,x,y,plansza)!='n'){xc=3;yc=y;jest_cel=true;continue;}
                                    else if(x<15 && (pamiec&4)!=4 && znajdz_droge(true,18,y,x,y,plansza)!='n'){xc=18;yc=y;jest_cel=true;continue;}
                                    else if((pamiec&2)!=2 && znajdz_droge(true,10,y,x,y,plansza)!='n'){xc=10;yc=y;jest_cel=true;continue;}
                                    else if((pamiec&1)!=1 && znajdz_droge(true,3,y,x,y,plansza)!='n'){xc=3;yc=y;jest_cel=true;continue;}
                                    else
                                    {
                                             ktora_plansza =wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, true);
                                             celem_jest_plansza = ktora_plansza != NULL; jest_cel = ktora_plansza != NULL;
                                             continue;
                                    }
                           }
                           else
                           {
                                    ktora_plansza =wyznacz_plansze_ucieczkowa(na_ktorej_ost_bylem, true);
                                    celem_jest_plansza = ktora_plansza != NULL; jest_cel = ktora_plansza != NULL;
                                    continue;
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
                                    what_happened aaa;
                                    if(p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                    if(ma_tyle_i_odejmij(kk, 6))aaa=przesun_sie(dzie); else return true;
                                    else if(dzie==zwrot)
                                    {
                                             char cos='p'; if(losuj(0,1)==0) cos='l';
                                             if((p=punkt_przed(skrec(cos,zwrot),x,y)).x+2 && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun_sie(skrec(cos, zwrot)); else return true;}
                                             else if((p=punkt_przed(skrec(skrec('z',cos),zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun_sie(skrec(skrec('z', cos), zwrot)); else return true;}
                                             else {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun_sie(skrec('z', zwrot)); else return true;}
                                    }
                                    else
                                    {
                                             if((p=punkt_przed(skrec('z', dzie),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun_sie(skrec('z', dzie)); else return true;}
                                             else if((p=punkt_przed(zwrot,x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun_sie(zwrot); else return true;}
                                             else if((p=punkt_przed(skrec('z',zwrot),x,y)).x+2  && p.y<13 && p.y>-1 && p.x >-1 && p.x<21 && plansza->otoczenie[p.y][p.x]==NULL)
                                             {if(ma_tyle_i_odejmij(kk, 6)) aaa=przesun_sie(skrec('z', zwrot)); else return true;}
                                    }
                                    if(aaa==dead) return false;
                           }
                           return true;
                  }
         }
         return true;
}


short Niedzwiedz::latwopalnosc(){return 0;}

#include "swiat2.h"

void Niedzwiedz::patrz()
{
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" n% "<<" "<<zwrot<<" ";
         if(x<7) pamiec=pamiec|1;else if(x<15) pamiec=pamiec|2; else pamiec=pamiec|4;
         int poszerzajaca=x; if(zwrot=='l' || zwrot=='p') poszerzajaca=y; ///ktora pokazuje strone
         int xw, yw;Plansza*a=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         bool jest_woda=false, jest_trawa=false; int wx,wy,tx,ty;if(Objekt::args->melduj_co_robi_AI)std::cout<<"A";
         for(int i=3; i<47; i+=2)
         {
                  for(int j=poszerzajaca-(i/2); j<=poszerzajaca+(i/2);j++)
                  {
                           switch(zwrot){case 'd':{xw=j;yw=y+(i-3)/2;break;}case 'g':{xw=j;yw=y-(i-3)/2;break;}case 'p':{yw=j;xw=x+(i-3)/2;break;}case'l':{yw=j;xw=x-(i-3)/2;break;}}

                           if(yw>-1 && yw<13 && xw>-1 && xw<21 && (xw!=x || yw!=y))
                           {
                                    //if(a->otoczenie[yw][xw]!=NULL && std::cout<<"notnull" && (a->otoczenie[yw][xw]->zywy || (std::cout<<" stwz" && (a->otoczenie[yw][xw]->zywy=(a->otoczenie[yw][xw]->zywy||a->otoczenie[yw][xw]->zywy) || std::cout<<" przyp" || true) && false)))
                                    if(a->otoczenie[yw][xw]!=NULL&& (a->otoczenie[yw][xw]->zywy || (a->otoczenie[yw][xw]->czym_jest==32 && ((Lozko*)a->otoczenie[yw][xw])->ktos_tu_spi()))  )
                                    {
                                             if(Objekt::args->melduj_co_robi_AI)std::cout<<"X";
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
                                             if(Objekt::args->melduj_co_robi_AI)std::cout<<"K";
                                             na_pewno_w_zasiegu=!((zwrot=='p' && xw-x>20-skrot)||(zwrot=='l' && x-xw>20-skrot)
                                                ||(zwrot=='g' && y-yw>20-skrot)||(zwrot=='d' && yw-y>20-skrot)||czy_widzi_wzgl_zwezania(3,2,odciecia,xw,yw));
                                                if(Objekt::args->melduj_co_robi_AI)std::cout<<"D";

                                             if(!jest_ofiara && na_pewno_w_zasiegu && widzi_obiekt(a,xw,yw,x,y,kamuflaz,poprawka))
                                             {
                                                      if(Objekt::args->melduj_co_robi_AI)std::cout<<"L";
                                                      jest_ofiara=true; ofiara=a->otoczenie[yw][xw]; jest_cel=false; celem_jest_plansza=false; zaalarmowany=true;
                                             }
                                             else if(Objekt::args->melduj_co_robi_AI)std::cout<<"L";
                                    }
                                    else if(!jest_woda && woda<100  && a->otoczenie[yw][xw]!=NULL && a->otoczenie[yw][xw]->czym_jest==21)
                                    {
                                             jest_woda=true; wx=xw; wy=yw;
                                    }
                                    else if(!jest_trawa && jedzenie<100 &&  a->otoczenie[yw][xw]==NULL && a->srodowisko[yw][xw] && a->srodowisko[yw][xw]->wierzch()
                                            && a->srodowisko[yw][xw]->wierzch()->czym_jest==22 && ((Trawa*)a->srodowisko[yw][xw]->wierzch())->ktora==0)
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
         if(Objekt::args->melduj_co_robi_AI)std::cout<<" n& "<<" "<<zwrot<<" ";
}

Niedzwiedz::Niedzwiedz(Niedzwiedz_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_zywy(9)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=3;
         co_to=0; px=ppx;py=ppy;pz=ppz;
         HP=a->HP; zwrot_ostatni='p'; atakujacy=false;zaalarmowany=false;biegnie=false;
         jedzenie=a->jedzenie;woda=a->woda;pamiec=0;
}

Niedzwiedz_przejsciowy::Niedzwiedz_przejsciowy(Niedzwiedz*a)
{
         czym_jest=9;
         HP=a->HP;jedzenie=a->jedzenie;woda=a->woda;
}

Niedzwiedz_przejsciowy::~Niedzwiedz_przejsciowy()
{

}

void Niedzwiedz_przejsciowy::zapisz(std::ofstream *a)
{

}

Niedzwiedz_przejsciowy::Niedzwiedz_przejsciowy()
{
         czym_jest=9;
}



