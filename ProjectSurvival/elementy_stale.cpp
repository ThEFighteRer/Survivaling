#include "swiat.h"
#include "windows.h"
#include "swiat2.h"

Drzewo :: Drzewo()
: Objekt_martwy(20)
{
         wykonuje_ruch=false;
         co_to=191;
         wysokosc=3;
}

void Drzewo :: zapisz(std::ofstream *ofs)
{

}

what_happened Drzewo::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,100))<=0)
         {
                  Plansza*p=((Plansza*)swiat->zwroc_taka_plansze_TYLKO(px, py, pz));
                  int h=losuj(1,3);
                  if(kto!=obrazenia_od_ognia)
                  {
                           for(int i=0;i<h;++i)p->rzuc_na_ziemie(x, y, Item::stworz_obiekt(8002));
                           h=losuj(0,2);
                           for(int i=0;i<h;++i)p->rzuc_na_ziemie(x, y, Item::stworz_obiekt(4010));
                  }
                  smierc(); return dead;
         }else HP=a;
         return success;
}

Drzewo::~Drzewo()
{

}

int Drzewo::get_co_to()
{
         return 51 + ktore;
}

Drzewo::Drzewo(Drzewo_przejsciowe*a, int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(20)
{
         x=xx;y=yy;px=ppx;py=ppy;pz=ppz; ktore=a->ktore;
         nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=3;
         co_to=191; animacja=0; HP=a->HP;
}
Drzewo_przejsciowe::Drzewo_przejsciowe(Drzewo*a){ktore=a->ktore;czym_jest=20;HP=a->HP;}

void Drzewo_przejsciowe :: zapisz(std::ofstream *ofs)
{

}

Drzewo_przejsciowe::Drzewo_przejsciowe()
{
         czym_jest=20;
}

short Drzewo::latwopalnosc(){return 60;}

Woda :: Woda():Objekt_martwy(21)
{
         wykonuje_ruch=false;
         co_to=246;
         wysokosc=0;
}

void Woda :: zapisz(std::ofstream *ofs)
{

}

what_happened Woda::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         return success;
}


Woda::Woda(Woda_przejsciowa*a, int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(21)
{
         x=xx;y=yy;px=ppx;py=ppy;pz=ppz;
         nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=0;
         co_to=246; animacja=0;
}
Woda_przejsciowa::Woda_przejsciowa(Woda*a){czym_jest=21;}

void Woda_przejsciowa :: zapisz(std::ofstream *ofs)
{

}

Woda_przejsciowa::Woda_przejsciowa()
{
         czym_jest=21;
}

short Woda::latwopalnosc(){return 0;}

Trawa::~Trawa()
{

}

short Trawa::latwopalnosc(){return 60;}

Trawa :: Trawa():Objekt_pol_martwy(22)
{
         wykonuje_ruch=false;
         co_to=247;
         wysokosc=1; if(ktora==1) wysokosc=2;
         rosniecie=0;
}

void Trawa :: zapisz(std::ofstream *ofs)
{

}

what_happened Trawa::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         Plansza *p=swiat->zwroc_taka_plansze_TYLKO(px, py, pz);

         if(ktora==0 && wysokosc>1) {wysokosc-=1; rosniecie=0;}
         else if(ktora==1 && rosniecie>6){rosniecie=5;}
         else if(ktora==1 && rosniecie<7 && rosniecie>0){rosniecie-=2;}
         else
         {///zawsze w srodowisku
                  p->srodowisko[y][x]->usun_objekt(this, x, y,p);
                  p->zaktualizuj_widoki(x,y,x,y);
                  smierc(); return dead;
         }

         return success;
}

int Trawa::get_co_to()
{
         return 3000+wysokosc-1+ktora*3;
}

bool Trawa :: rusz_sie()
{
         if(ktora==0){++rosniecie; if(rosniecie>120) {if(wysokosc<3)++wysokosc; rosniecie=0;}}

         return true;
}

Trawa::Trawa(Trawa_przejsciowa*a, int xx, int yy,int ppx,int ppy,int ppz):Objekt_pol_martwy(22)
{
         x=xx;y=yy;px=ppx;py=ppy;pz=ppz;
         nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=a->wysokosc;
         co_to=247; animacja=0;rosniecie=0; ktora = a->ktora;
}
Trawa_przejsciowa::Trawa_przejsciowa(Trawa*a){ktora=a->ktora;czym_jest=22;wysokosc=a->wysokosc;}

void Trawa_przejsciowa :: zapisz(std::ofstream *ofs)
{

}

Trawa_przejsciowa::Trawa_przejsciowa()
{
         czym_jest=22;
         switch(ktora)
         {
                  case 0: wysokosc = 1; break;
                  case 1: wysokosc = 2; break;
         }
}

short Zwloki::latwopalnosc(){return 30;}

Zwloki::Zwloki(int a, unsigned char b,int k1,int k2,int k3,int k4,int k5):Objekt_martwy(100)
{
         x=k1; y=k2; px=k3; py=k4; pz=k5;
         wykonuje_ruch=false;wysokosc=1; stan_zwlok=b;
         czyje_zwloki=a; ///to samo co czym jest
         co_to=291;
         if(czyje_zwloki==8){}
         else if(czyje_zwloki==9){++co_to;}
         else if(czyje_zwloki==2)
         {
                  co_to+=2;if((b&((unsigned char)16))!=16)co_to+=9;
                  if((b&((unsigned char)1))!=1)co_to+=1; if((b&((unsigned char)2))!=2)co_to+=1;
                  if((b&((unsigned char)4))!=4)co_to+=3; if((b&((unsigned char)8))!=8)co_to+=3;
         }/// 311 nastepny


}

Zwloki::~Zwloki()
{

}

what_happened Zwloki::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int max_hp=100;
         animacja_bycia_uderzanym_jak_drzewo(HP,obrazenia,max_hp);

         if(HP-obrazenia>0) {HP-=obrazenia;wydaj_dzwiek(false,1,x,y,100);}
         else
         {///zawsze w srodowisku
                  wydaj_dzwiek(false,1,x,y,100);
                  Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
                  p->srodowisko[y][x]->usun_objekt(this, x, y, p);
                  p->zaktualizuj_widoki(x,y,x,y);
                  smierc(); return dead;
         }
         return success;
}

int Zwloki::get_co_to()
{
         return co_to;
}

void Zwloki::zapisz(std::ofstream *a)
{

}

Zwloki::Zwloki(Zwloki_przejsciowe* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(100)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=1;
         co_to=0; px=ppx;py=ppy;pz=ppz;
         czyje_zwloki=a->czyje_zwloki;stan_zwlok=a->stan_zwlok;
}

Zwloki_przejsciowe::Zwloki_przejsciowe(Zwloki*a)
{
         czym_jest=100;
         czyje_zwloki=a->czyje_zwloki;stan_zwlok=a->stan_zwlok;
}

Zwloki_przejsciowe::~Zwloki_przejsciowe()
{

}

void Zwloki_przejsciowe::zapisz(std::ofstream *a)
{

}

short Schowek::latwopalnosc(){return 20;}

Schowek::Schowek():Objekt_martwy(23)
{
        zawartosc =new Kontener<Item>();
}

Schowek::~Schowek()
{
         delete zawartosc;
}

what_happened Schowek::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,50))==0)
         {
                  if(!otwarty) zawartosc->dodaj_obiekt(Item::wylosuj_item('s'));
                  Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
                  if(p->ziemia[y][x]==NULL)p->ziemia[y][x]=new Kontener<Item>();
                  p->ziemia[y][x]->dodaj_obiekty(zawartosc);
                  zawartosc->wywal_wszystkie_objekty();
                  if(p->ziemia[y][x]->ilosc==0) {delete p->ziemia[y][x];p->ziemia[y][x]=NULL;}
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Schowek::get_co_to()
{
         int a=0; if(!otwarty)++a;
         return 765+a;
}

void Schowek::zapisz(std::ofstream *a)
{

}

Schowek::Schowek(Schowek_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(23)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=2;
         co_to=765; px=ppx;py=ppy;pz=ppz;
         zawartosc=a->zawartosc; a->zawartosc = NULL; HP=a->HP; otwarty=a->otwarty;
}

Schowek_przejsciowy::Schowek_przejsciowy(Schowek*a)
{
         czym_jest=23;zawartosc=a->zawartosc; a->zawartosc = NULL; HP=a->HP; otwarty=a->otwarty;
}

Schowek_przejsciowy::~Schowek_przejsciowy()
{
         delete zawartosc;
}

Schowek_przejsciowy::Schowek_przejsciowy()
{
         czym_jest=23; zawartosc =new Kontener<Item>();
}

void Schowek_przejsciowy::zapisz(std::ofstream *a)
{

}

Ognisko::Ognisko(int xx,int yy ,int xxx,int yyy, int zzz):Objekt_pol_martwy(24)
{
        x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=1;
        co_to=765; px=xxx;py=yyy;pz=zzz; HP=30; paliwo=5; pali_sie=false;
}

Ognisko::~Ognisko()
{

}

bool Ognisko::rusz_sie()
{
         if(pali_sie)
         {
                  if(paliwo>1) --paliwo;
                  else
                  {
                           paliwo=0; pali_sie=false;
                           Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
                           p->srodowisko[y][x]->usun_objekt(this, x, y, p);
                           p->zaktualizuj_widoki(x,y,x,y);
                           smierc();
                           return false;
                  }
         }
         return true;
}

what_happened Ognisko::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,30))==0)
         {

         } else HP=a;
         return success;
}

int Ognisko::get_co_to()
{
         if(pali_sie==false)
         {
                  //if(paliwo<=0) return 593;
                  //else
                           return 590;
         }
         else if(paliwo>10) return 592;
         else return 591;
}

void Ognisko::zapisz(std::ofstream *a)
{

}

Ognisko::Ognisko(Ognisko_przejsciowe* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_pol_martwy(24)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=true;wysokosc=0;
         co_to=765; px=ppx;py=ppy;pz=ppz; HP=a->HP; paliwo=a->paliwo; pali_sie=false;
}

Ognisko_przejsciowe::Ognisko_przejsciowe(Ognisko*a)
{
         czym_jest=24;HP=a->HP; paliwo=a->paliwo;
}

Ognisko_przejsciowe::~Ognisko_przejsciowe()
{

}

Ognisko_przejsciowe::Ognisko_przejsciowe()
{
         czym_jest=24; paliwo=20;
}

void Ognisko_przejsciowe::zapisz(std::ofstream *a)
{

}













short Szalas::latwopalnosc(){return 40;}

Szalas::Szalas():Objekt_martwy(25)
{

}

Szalas::~Szalas()
{
         if(kto_spi) delete kto_spi;
         delete zawartosc;
}

what_happened Szalas::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,100))==0)
         {

                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->rzuc_na_ziemie(x, y, zawartosc); ///to wywala z zawartosci przedmioty
                  lozko_destroyer(&kto_spi);
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Szalas::get_co_to()
{
         return 767;
}

void Szalas::zapisz(std::ofstream *a)
{

}

Szalas::Szalas(Szalas_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(25)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=2;
         co_to=767; px=ppx;py=ppy;pz=ppz;
         zawartosc=a->zawartosc; a->zawartosc = NULL; HP=a->HP;
         kto_spi = a->kto_spi == NULL ? NULL :Objekt::z_objektu_tymczasowego(a->kto_spi, xx, yy, ppx, ppy, ppz); a->kto_spi = NULL;
}

Szalas_przejsciowy::Szalas_przejsciowy(Szalas*a)
{
         czym_jest=25;zawartosc=a->zawartosc; a->zawartosc = NULL; HP=a->HP;
         kto_spi = a->kto_spi == NULL ? NULL :Objekt_przejsciowy::z_objektu(a->kto_spi); a->kto_spi = NULL;
}

Szalas_przejsciowy::~Szalas_przejsciowy()
{
         delete zawartosc;
}

Szalas_przejsciowy::Szalas_przejsciowy()
{
         czym_jest=25; zawartosc = new Kontener<Item>;
}

void Szalas_przejsciowy::zapisz(std::ofstream *a)
{

}








short Okno::latwopalnosc(){return 0;}

Okno::Okno():Objekt_martwy(26)
{

}

Okno::~Okno()
{

}

what_happened Okno::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         Plansza*pl =swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         int max_hp=25; if(wybite) max_hp=200;
         animacja_bycia_uderzanym_jak_drzewo(HP,obrazenia,max_hp);

         if(HP-obrazenia>0) {HP-=obrazenia;wydaj_dzwiek(false,2,x,y,26);}
         else if(!wybite && !otwarte)
         {///w otoczeniu
                  wydaj_dzwiek(false,16,x,y,26);
                  HP=200; wybite=true;
                  pl->otoczenie[y][x] = NULL;
                  pl->dodaj_do_srodowiska(x,y,this);
                  pl->srodowisko[y][x]->stan|=2;
                  ogarnij_sie_z_wysokoscia();
         }
         else if(!wybite && otwarte)
         {///srodowisko
                  wydaj_dzwiek(false,10,x,y,26); wybite=true; HP=200; ogarnij_sie_z_wysokoscia();
         }
         else
         {///zawsze w srodowisku
                  wydaj_dzwiek(false,10,x,y,26);
                  Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
                  p->srodowisko[y][x]->usun_objekt(this, x, y, p);
                  p->zaktualizuj_widoki(x,y,x,y);
                  smierc();return dead;
         }
         return success;
}

int Okno::get_co_to()
{
         int a=769;
         if(zwrot=='l') a+=9; else if(zwrot=='g') a+=18; else if(zwrot=='p') a+=27;
         if(zasloniete) return a+8;
         if(jest_zaslona) a+=4;
         if(wybite) a+=2;
         if(otwarte) ++a;
         return a;
}

void Okno::zapisz(std::ofstream *a)
{

}

Okno::Okno(Okno_przejsciowe* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(26)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;
         co_to=769; px=ppx;py=ppy;pz=ppz;
         HP=a->HP;
         jest_zaslona=a->jest_zaslona, wybite=a->wybite, otwarte=a->otwarte,zasloniete=a->zasloniete;

         ogarnij_sie_z_wysokoscia(true); zwrot=a->zwrot;
}

void Okno::ogarnij_sie_z_wysokoscia(bool sdsd)
{
         int wys=wysokosc;
         if(zasloniete) wysokosc=3;
         else if(otwarte || wybite) wysokosc=1;
         else wysokosc=2;
         if(!sdsd && wys!=wysokosc && swiat->zwroc_taka_plansze(px, py, pz)) swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(x,y,x,y);
}

Okno_przejsciowe::Okno_przejsciowe(Okno*a)
{
         czym_jest=26;HP=a->HP;
         jest_zaslona=a->get_jest_zaslona(), wybite=a->get_wybite(), otwarte=a->get_otwarte(),zasloniete=a->get_zasloniete();
         zwrot=a->zwrot;
}

Okno_przejsciowe::~Okno_przejsciowe()
{

}

Okno_przejsciowe::Okno_przejsciowe()
{
         czym_jest=26; zwrot='d';
}

Okno_przejsciowe::Okno_przejsciowe(char dzie)
{
         czym_jest=26; zwrot='p'; if(dzie=='p'||dzie=='l'||dzie=='g'||dzie=='d') zwrot=dzie;
}

void Okno_przejsciowe::zapisz(std::ofstream *a)
{

}

bool Okno::mozna_stad_podejsc(int xx, int yy)
{
         return Objekt::zaraz_obok(xx,yy,x,y)&&!(zwrot=='d' && yy==y-1)&&!(zwrot=='g' && yy==y+1)
         &&!(zwrot=='p' && xx==x-1)&&!(zwrot=='l' && xx==x+1);
}

bool Okno::get_wybite(){return wybite;}
bool Okno::get_otwarte(){return otwarte;}
bool Okno::get_zasloniete(){return zasloniete;}
bool Okno::get_jest_zaslona(){return jest_zaslona;}
void Okno::zaloz_zaslone()
{
         jest_zaslona=true;
}
void Okno::zdejmij_zaslone()
{
         jest_zaslona=false; zasloniete=false; ogarnij_sie_z_wysokoscia();
}
void Okno::otworz()
{
         zasloniete=false; otwarte=true;
         if(!wybite)
         {
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->otoczenie[y][x]=NULL;
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->dodaj_do_srodowiska(x,y,this);
         }
         ogarnij_sie_z_wysokoscia();
}
void Okno::zamknij()
{
         if(swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->otoczenie[y][x]!=NULL) return;
         otwarte=false;
         if(!wybite)
         {
                  Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
                  p->srodowisko[y][x]->usun_objekt(this, x, y, p);
                  p->otoczenie[y][x]=this;
         }
         ogarnij_sie_z_wysokoscia();
}
void Okno::odslon()
{
         zasloniete=false; ogarnij_sie_z_wysokoscia();
}
void Okno::zaslon()
{
         if(jest_zaslona && !otwarte) {zasloniete=true; ogarnij_sie_z_wysokoscia();}
}















/*Drzwi::Drzwi()
{
         czym_jest=27;
}*/

short Drzwi::latwopalnosc(){return 30;}

Drzwi::~Drzwi()
{
         //if(klodka1!=NULL) delete klodka1; if(klodka2!=NULL) delete klodka2; if(nasza!=NULL) delete nasza;


}

what_happened Drzwi::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int max_hp=200;
         //if(co_zamkniete&1==0 && co_zamkniete&2==0) max_hp=300+nasza->max_hp();
         //else if(co_zamkniete&2==2) max_hp=klodka2->max_hp();
         //else if(co_zamkniete&1==1) max_hp=klodka1->max_hp();
         //else max_hp=nasza->max_hp();
         animacja_bycia_uderzanym_jak_drzewo(HP,otwarte ? 1.5*obrazenia : obrazenia,max_hp);
         if(otwarte) obrazenia*=1.5;
         if(HP-obrazenia>0) {wydaj_dzwiek(false,8,x,y,27);HP-=obrazenia;}
         /*else if((co_zamkniete&1)==1 || (co_zamkniete&2)==2)
         {
                  wydaj_dzwiek(false,10,x,y,27);
                  if((co_zamkniete&2)==2)
                  {
                           Klodka*t=klodka2; klodka2=NULL; delete t; HP=klodka1->HP;
                  }
                  else
                  {
                           Klodka*t=klodka1; klodka1=NULL; delete t; HP=nasza->HP;
                  }
         }*/
         else
         {
                  wydaj_dzwiek(false,12,x,y,27);
                  if(otwarte)
                  {
                           swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->srodowisko[y][x]->usun_objekt(this, x, y, swiat->zwroc_taka_plansze_TYLKO(px, py, pz));
                  }
                  else
                  {
                           swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->otoczenie[y][x]=NULL;
                  }
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(x,y,x,y);
                  smierc(); return dead;
         }
         return success;
}

int Drzwi::get_co_to()
{
         ///std::cout<<(0&1!=1)<<" ";
         int a=812 + 512*ktore;
         if(otwarte) {a+=256;}
         //int ilosc_klodek_zamknietych=(co_zamkniete&128)==128+(co_zamkniete&1)==1+(co_zamkniete&2)==2;
         //a+=(ilosc_klodek_zamknietych/2)*128; a+=(ilosc_klodek_zamknietych%2)*64;

         /*if(ilosc_klodek_zamknietych==3)
         {
                  a+=(klodka2->czym_jest>8007)*32;
                  a+=(klodka2->czym_jest!=8008)*16;
                  a+=(klodka1->czym_jest>8007)*8;
                  a+=(klodka1->czym_jest!=8008)*4;
                  a+=(nasza->czym_jest>8007)*2;
                  a+=(nasza->czym_jest!=8008)*1;
         }
         else if(ilosc_klodek_zamknietych==2)
         {
                  if(co_zamkniete&128==128)
                  {
                           a+=(klodka1->czym_jest>8007)*32;
                           a+=(klodka1->czym_jest!=8008)*16;
                           a+=(nasza->czym_jest>8007)*8;
                           a+=(nasza->czym_jest!=8008)*4;
                  }
                  else
                  {
                           a+=(klodka2->czym_jest>8007)*32;
                           a+=(klodka2->czym_jest!=8008)*16;
                           a+=(klodka1->czym_jest>8007)*8;
                           a+=(klodka1->czym_jest!=8008)*4;
                  }
         }
         else if(ilosc_klodek_zamknietych==1)
         {
                  if(co_zamkniete&128==128)
                  {
                           a+=(nasza->czym_jest>8007)*32;
                           a+=(nasza->czym_jest!=8008)*16;
                  }
                  else
                  {
                           a+=(klodka1->czym_jest>8007)*32;
                           a+=(klodka1->czym_jest!=8008)*16;
                  }
         }*/
         //if(a>811)std::cout<<a<<" ";

         return a;
}

void Drzwi::zapisz(std::ofstream *a)
{

}

int Drzwi::get_HP(){return HP;}

Drzwi::Drzwi(Drzwi_przejsciowe* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(27)
{
         klodka1=a->klodka1; klodka2=a->klodka2; nasza=a->nasza; a->klodka1=NULL; a->klodka2=NULL; a->nasza=NULL;
         otwarte=false; co_zamkniete=a->co_zamkniete;
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=3;
         co_to=780; px=ppx;py=ppy;pz=ppz;HP=a->HP; ktore = a->ktore;
}

Drzwi_przejsciowe::Drzwi_przejsciowe(Drzwi*a)
{
         klodka1=a->klodka1; klodka2=a->klodka2; nasza=a->nasza; a->klodka1=NULL; a->klodka2=NULL; a->nasza=NULL;
         czym_jest=27;HP=a->HP; co_zamkniete=a->co_zamkniete; ktore = a->ktore;
}

Drzwi_przejsciowe::~Drzwi_przejsciowe()
{
         //if(klodka1!=NULL) delete klodka1; if(klodka2!=NULL) delete klodka2; if(nasza!=NULL) delete nasza;
}

Drzwi_przejsciowe::Drzwi_przejsciowe(short kto)
{
         nasza=new Klodka(losuj(8007,8009)); nasza->HP+=300;
         czym_jest=27; ktore = kto;
}

void Drzwi_przejsciowe::zapisz(std::ofstream *a)
{

}

Klodka* Drzwi::otworz_klodke(Klucz*a)
{
         if(a->do_czego==NULL)
         {
                  if((co_zamkniete&2)==2) a->do_czego=klodka2;
                  else if((co_zamkniete&1)==1) a->do_czego=klodka1;
                  else if((co_zamkniete&128)==128) a->do_czego=nasza;
                  else return NULL;
         }
         if((co_zamkniete&2)==2 && klodka2!=NULL && a->do_czego==klodka2)
         {
                  co_zamkniete&=(co_zamkniete-2); Klodka*t=klodka2; klodka2=NULL; HP=klodka1->HP; return t;
         }
         else if(klodka1!=NULL && a->do_czego==klodka1)
         {
                  co_zamkniete&=(co_zamkniete-1); Klodka*t=klodka1; klodka1=NULL;
                  if((co_zamkniete&2)==2)
                  {
                           klodka1=klodka2; klodka2=NULL; co_zamkniete&=co_zamkniete-2; co_zamkniete|=1; HP=klodka1->HP;
                  }
                  else
                  {
                           HP=nasza->HP;
                  }
                  return t;
         }
         else if(nasza!=NULL && a->do_czego==nasza)
         {
                  co_zamkniete|=(co_zamkniete-128);
         }
         return NULL;
}

void Drzwi::wylam_klodke(int czym)
{
         /*if(czym==8013) if(losuj(1,2)==1)
         if((co_zamkniete&2)==2) {co_zamkniete&=co_zamkniete-2; Klodka*t=klodka2; klodka2=NULL; HP=klodka1->HP; delete t;}
         else if((co_zamkniete&1)==1) {co_zamkniete&=co_zamkniete-1; Klodka*t=klodka1; klodka1=NULL; HP=nasza->HP; delete t;}
         if((co_zamkniete&128)==128) {co_zamkniete&=co_zamkniete-128;}*/
}

bool Drzwi::zaloz_klodke(Klodka*a)
{
         if(!otwarte) return false;
         if((co_zamkniete&1)!=1) {klodka1=a; co_zamkniete+=1; HP=klodka1->HP;}
         else if((co_zamkniete&2)!=2) {klodka2=a; co_zamkniete+=2; HP=klodka2->HP;}
         return false;
}

bool Drzwi::zamknij_na_klucz(Klucz*a)
{
         if(a==NULL) return false;
         if((co_zamkniete&128)!=128 && a->do_czego==nasza)
         {
                  co_zamkniete+=128; return true;
         }
         return false;
}

void Drzwi::otworz()
{
         otwarte=true; wysokosc=0;
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         p->otoczenie[y][x]=NULL;
         p->dodaj_do_srodowiska(x,y,this);
         p->zaktualizuj_widoki(x,y,x,y);
}
void Drzwi::zamknij()
{
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         if(p->otoczenie[y][x]!=NULL) return;
         otwarte=false; wysokosc=3;
         p->srodowisko[y][x]->usun_objekt(this,x, y, swiat->zwroc_taka_plansze_TYLKO(px, py, pz));
         p->otoczenie[y][x]=this;
}

char Drzwi::get_co_zamkniete()
{
         return co_zamkniete;
}









short Sciana::latwopalnosc(){return 0;}

Sciana::~Sciana()
{

}

what_happened Sciana::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         wydaj_dzwiek(false,2, x,y,czym_jest);
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,10000))==0)
         {
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Sciana::get_co_to()
{
         return 3001 + ktora;
}

void Sciana::zapisz(std::ofstream *a)
{

}

Sciana::Sciana(Sciana_przejsciowa* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(28)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=3;
         co_to=3001; px=ppx;py=ppy;pz=ppz; HP=a->HP; ktora = a->ktora;
}

Sciana_przejsciowa::Sciana_przejsciowa(Sciana*a)
{
         czym_jest=28; HP=a->HP; ktora = a->ktora;
}

Sciana_przejsciowa::~Sciana_przejsciowa()
{

}

Sciana_przejsciowa::Sciana_przejsciowa(short kt)
{
         czym_jest=28;
         ktora = kt;
         switch(ktora)
         {
                  default: HP = 10000;
         }
}

void Sciana_przejsciowa::zapisz(std::ofstream *a)
{

}









short Krzeslo::latwopalnosc(){return 60;}

Krzeslo::~Krzeslo(){}

what_happened Krzeslo::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         wydaj_dzwiek(false,3, x,y,czym_jest);
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,25))==0)
         {for(short h=losuj(0,1);h>0;--h)(swiat->zwroc_taka_plansze_TYLKO(px, py, pz))->rzuc_na_ziemie(x,y,Item::stworz_obiekt(8002));smierc(); return dead;} else HP=a; return success;
}

int Krzeslo::get_co_to() {return 3500 + ktore;}

void Krzeslo::zapisz(std::ofstream *a) {}

Krzeslo::Krzeslo(Krzeslo_przejsciowe* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(29)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=3501; px=ppx;py=ppy;pz=ppz; HP=a->HP; ktore = a->ktore;
}

Krzeslo::Krzeslo(int xx, int yy,int ppx,int ppy,int ppz, short ktore):Objekt_martwy(29)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=3501; px=ppx;py=ppy;pz=ppz; HP=25; this->ktore = ktore;
}

Krzeslo_przejsciowe::Krzeslo_przejsciowe(Krzeslo*a)
{
         czym_jest=29; HP=a->HP; ktore = ktore;
}

Krzeslo_przejsciowe::~Krzeslo_przejsciowe(){}

Krzeslo_przejsciowe::Krzeslo_przejsciowe() {czym_jest=29;}

void Krzeslo_przejsciowe::zapisz(std::ofstream *a) {}


short Szafa::latwopalnosc(){return 60;}

Szafa::~Szafa()
{
         delete zawartosc;
         if(kto_sie_chowa) delete kto_sie_chowa;
}

what_happened Szafa::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         wydaj_dzwiek(false,5, x,y,czym_jest);
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,200))==0)
         {
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->rzuc_na_ziemie(x, y, zawartosc); ///to wywala z zawartosci przedmioty
                  for(short h=losuj(1,4);h>0;--h)swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->rzuc_na_ziemie(x,y,Item::stworz_obiekt(8002));
                  kryjowka_destroyer(&kto_sie_chowa);
                  smierc(); return dead;
         }else HP=a;
         return success;
}

int Szafa::get_co_to()
{
         short zwr = zwrot == 'd' ? 0 : (zwrot == 'l' ? 1 : (zwrot == 'g' ? 2 : 3));
         return 3800+ (int)przeszukana*4 + (ktora-1)*9 + zwr;
}

void Szafa::zapisz(std::ofstream *a) {}

Szafa::Szafa(Szafa_przejsciowa* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(30)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=3;
         co_to=3601; px=ppx;py=ppy;pz=ppz; HP=a->HP; ktora = ktora;
         zawartosc = a->zawartosc; a->zawartosc = NULL;
         kto_sie_chowa = a->kto_sie_chowa == NULL ? NULL :Objekt::z_objektu_tymczasowego(a->kto_sie_chowa, xx, yy, ppx, ppy, ppz); a->kto_sie_chowa = NULL;
         przeszukana = a->przeszukana; zwrot = a->zwrot;
}

void Szafa::stworz_loot() {if(!przeszukana && (przeszukana=true))Objekt_martwy::stworz_loot(zawartosc, 60, 30, 10, 30, 10, 10);}

Szafa_przejsciowa::Szafa_przejsciowa(Szafa*a)
{
         czym_jest=30; HP=a->HP; ktora = ktora; zawartosc = a->zawartosc; a->zawartosc = NULL;
         kto_sie_chowa = a->kto_sie_chowa == NULL ? NULL :Objekt_przejsciowy::z_objektu(a->kto_sie_chowa); a->kto_sie_chowa = NULL;
         przeszukana = a->przeszukana; zwrot = a->zwrot;
}

Szafa_przejsciowa::~Szafa_przejsciowa(){delete zawartosc; delete kto_sie_chowa;}

Szafa_przejsciowa::Szafa_przejsciowa()
{
         zwrot = Objekt::losuj_zwrot(); czym_jest=30; zawartosc = new Kontener<Item>;
}

void Szafa_przejsciowa::zapisz(std::ofstream *a) {}




short Stol::latwopalnosc(){return 60;}

Stol::~Stol(){delete zawartosc; if(kto_sie_chowa) delete kto_sie_chowa;}

what_happened Stol::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         wydaj_dzwiek(false,5, x,y,czym_jest);
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,200))==0)
         {
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->rzuc_na_ziemie(x, y, zawartosc); ///to wywala z zawartosci przedmioty
                   for(short h=losuj(0,2);h>0;--h)swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->rzuc_na_ziemie(x,y,Item::stworz_obiekt(8002));
                   kryjowka_destroyer(&kto_sie_chowa);
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Stol::get_co_to() {return 3700 + (ktory-1)*5 + (przewrocony ? 4 : (jest_obrus ? (zawartosc->ilosc>0? 3: 1) : (zawartosc->ilosc>0? 2: 0)));}

void Stol::zapisz(std::ofstream *a) {}

Stol::Stol(Stol_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(31)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=0; przewrocony = a->przewrocony;
         co_to=3701; px=ppx;py=ppy;pz=ppz; HP=a->HP; ktory = ktory; zawartosc = a->zawartosc; a->zawartosc = NULL;
         kto_sie_chowa = a->kto_sie_chowa == NULL ? NULL :Objekt::z_objektu_tymczasowego(a->kto_sie_chowa, xx, yy, ppx, ppy, ppz); a->kto_sie_chowa = NULL;
         jest_obrus = a->jest_obrus;
}

Stol_przejsciowy::Stol_przejsciowy(Stol*a)
{
         czym_jest=31; HP=a->HP; ktory = ktory; zawartosc = a->zawartosc; a->zawartosc = NULL; przewrocony = a->przewrocony;
         kto_sie_chowa = a->kto_sie_chowa == NULL ? NULL :Objekt_przejsciowy::z_objektu(a->kto_sie_chowa); a->kto_sie_chowa = NULL;
         jest_obrus = a->jest_obrus;
}

Stol_przejsciowy::~Stol_przejsciowy(){delete zawartosc; delete kto_sie_chowa;}

Stol_przejsciowy::Stol_przejsciowy() {czym_jest=31; zawartosc = new Kontener<Item>; Objekt_martwy::stworz_loot(zawartosc, 10,10,20,20,30,30);}

void Stol_przejsciowy::zapisz(std::ofstream *a) {}










short Lozko::latwopalnosc(){return 40;}

Lozko::~Lozko()
{
        if(kto_spi) delete kto_spi;
}

what_happened Lozko::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,200))==0)
         {
                  lozko_destroyer(&kto_spi);
                  smierc();return dead;
         } else HP=a;
         return success;
}

int Lozko::get_co_to()
{
         return 4100 + jest_przescieradlo + 2*(kto_spi!=NULL) + 4*(ktore-1);
}

void Lozko::zapisz(std::ofstream *a)
{

}

Lozko::Lozko(Lozko_przejsciowe* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(32)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=767; px=ppx;py=ppy;pz=ppz;
         kto_spi = a->kto_spi == NULL ? NULL :Objekt::z_objektu_tymczasowego(a->kto_spi, xx, yy, ppx, ppy, ppz); a->kto_spi = NULL;
         ktore = a->ktore; jest_przescieradlo = a->jest_przescieradlo;
}

Lozko_przejsciowe::Lozko_przejsciowe(Lozko*a)
{
         czym_jest=32; HP=a->HP;
         kto_spi = a->kto_spi == NULL ? NULL :Objekt_przejsciowy::z_objektu(a->kto_spi); a->kto_spi = NULL;
         ktore = a->ktore; jest_przescieradlo = a->jest_przescieradlo;
}

Lozko_przejsciowe::~Lozko_przejsciowe()
{

}

Lozko_przejsciowe::Lozko_przejsciowe()
{
         czym_jest=32;
}

void Lozko_przejsciowe::zapisz(std::ofstream *a)
{

}








short Ukryty_pod::latwopalnosc(){return 70;}

Ukryty_pod::~Ukryty_pod()
{
         if(kto_sie_ukrywa) delete kto_sie_ukrywa; delete ktore_zwl;
}

what_happened Ukryty_pod::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         short a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,100))==0)
         {
                  kryjowka_destroyer(&kto_sie_ukrywa);
                  smierc(); return dead;
         }else HP=a;
         return success;
}

int Ukryty_pod::get_co_to()
{
         return 4400+(ktore-1)*2+(kto_sie_ukrywa!=NULL);
}

void Ukryty_pod::zapisz(std::ofstream *a)
{

}

Ukryty_pod::Ukryty_pod(Objekt *kto_sie_ukrywa, Zwloki *ktore_zwl, short x, short y):Objekt_martwy(33)
{
        this->kto_sie_ukrywa = kto_sie_ukrywa; this->ktore_zwl = ktore_zwl; kto_sie_ukrywa->x = x; kto_sie_ukrywa->y= y;
        this->x=x; this->y=y;
        nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1; co_to=0;
        px = kto_sie_ukrywa->px; py = kto_sie_ukrywa->py; pz = kto_sie_ukrywa->pz;
}

void Ukryty_pod::wyjdz_spod()
{
        Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);

        kto_sie_ukrywa->px = px; kto_sie_ukrywa->py = py; kto_sie_ukrywa->pz = pz;
        kto_sie_ukrywa->x = x; kto_sie_ukrywa->y = y;
        if(kto_sie_ukrywa->czym_jest==10) ((Gracz*)kto_sie_ukrywa)->ukryty = false;

        p->dodaj_do_srodowiska(x, y, ktore_zwl);
        ktore_zwl = NULL;

        p->otoczenie[y][x] = kto_sie_ukrywa;
        kto_sie_ukrywa = NULL;
        p->zaktualizuj_widoki(x, y, x, y);
        smierc();
}

void Zwloki::ukryj_sie_pod(Objekt *a)
{
         Plansza*pl = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         if(czyje_zwloki!=2 || a->czym_jest!=10 || pl->otoczenie[y][x]!=NULL) return;

         if(a->czym_jest==10) ((Gracz*)a)->ukryty = true;
         a->zwrot = a->daj_zwrot_do_punktu(x,y);
         a->przesuniecie_x=0; a->przesuniecie_y=0;
         char strona = a->daj_zwrot_do_punktu(x, y);
         int do_czego=swiat->X; if(strona=='g' || strona=='d') do_czego=swiat->Y;
         if(pl->ma_gracza)
         {
                  for(int i=0;i<=do_czego/2; i++)
                  {
                           switch(strona)
                           {
                                    case 'p':a->przesuniecie_x=i;break;
                                    case 'l':a->przesuniecie_x=-i;break;
                                    case 'g':a->przesuniecie_y=-i;break;
                                    case 'd':a->przesuniecie_y=i;break;
                           }
                           Sleep(375/do_czego);
                  }
         }
         a->przesuniecie_x=0; a->przesuniecie_y=0;

         pl->otoczenie[a->y][a->x] = NULL;
         pl->srodowisko[y][x]->usun_objekt(this, x, y, pl);
         pl->otoczenie[y][x] = new Ukryty_pod(a, this, x, y);

         if(a->zywy) ((Objekt_zywy*)a) -> przestan_byc_ofiara(0, x, y);
         pl->zaktualizuj_widoki(x,y, a->x, a->y);
}




short Zlamana_galaz::latwopalnosc(){return 70;}

void Zlamana_galaz :: zapisz(std::ofstream *ofs)
{

}

what_happened Zlamana_galaz::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int max_hp=50;
         animacja_bycia_uderzanym_jak_drzewo(HP,obrazenia,max_hp);
         Plansza *p=swiat->zwroc_taka_plansze_TYLKO(px, py, pz);

         if(HP-obrazenia>0) {HP-=obrazenia;wydaj_dzwiek(false,1,x,y,czym_jest);}
         else
         {///zawsze w srodowisku
                  wydaj_dzwiek(false,1,x,y,czym_jest);
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->srodowisko[y][x]->usun_objekt(this, x, y, swiat->zwroc_taka_plansze_TYLKO(px, py, pz));
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(x,y,x,y);
                  int h=losuj(1,2);
                  if(kto!=obrazenia_od_ognia)
                  {
                           for(int i=0;i<h;++i) p->rzuc_na_ziemie(x, y, Item::stworz_obiekt(8002));
                           h=losuj(1, 5);
                           for(int i=0;i<h;++i) p->rzuc_na_ziemie(x, y, Item::stworz_obiekt(4010));
                  }
                  smierc(); return dead;
         }
         return success;
}

int Zlamana_galaz::get_co_to()
{
         return 4500+(HP<40)+(HP<25);
}

bool Zlamana_galaz :: rusz_sie()
{
         return true;
}

Zlamana_galaz::~Zlamana_galaz() {}

Zlamana_galaz::Zlamana_galaz(Zlamana_galaz_przejsciowa*a, int xx, int yy,int ppx,int ppy,int ppz):Objekt_pol_martwy(35)
{
         x=xx;y=yy;px=ppx;py=ppy;pz=ppz;
         nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=0; animacja=0; HP=a->HP;
}

Zlamana_galaz_przejsciowa::Zlamana_galaz_przejsciowa(Zlamana_galaz*a){czym_jest=35;HP=a->HP;}

void Zlamana_galaz_przejsciowa :: zapisz(std::ofstream *ofs)
{

}

Zlamana_galaz_przejsciowa::Zlamana_galaz_przejsciowa()
{
         czym_jest=35;
}



















void Lampa::wlacz()
{

}

void Lampa::wylacz()
{

}

short Lampa::latwopalnosc(){return 10;}

void Lampa :: zapisz(std::ofstream *ofs)
{

}

what_happened Lampa::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int max_hp=20;
         animacja_bycia_uderzanym_jak_drzewo(HP,obrazenia,max_hp);
         Plansza *p=swiat->zwroc_taka_plansze_TYLKO(px, py, pz);

         if(HP-obrazenia>0) {HP-=obrazenia;wydaj_dzwiek(false,1,x,y,czym_jest);}
         else
         {///zawsze w srodowisku
                  wydaj_dzwiek(false,6,x,y,czym_jest);
                  p->srodowisko[y][x]->stan|=2;
                  p->srodowisko[y][x]->usun_objekt(this, x, y, p);
                  p->zaktualizuj_widoki(x,y,x,y);
                  //int h=losuj(1,2);for(int i=0;i<h;++i) p->rzuc_na_ziemie(x, y, Item::stworz_obiekt(8002));
                  smierc(); return dead;
         }
         return success;
}

int Lampa::get_co_to()
{
         return 4600 + wlaczona;
}

bool Lampa :: rusz_sie()
{
         return true;
}

Lampa::~Lampa() {}

Lampa::Lampa(Lampa_przejsciowa*a, int xx, int yy,int ppx,int ppy,int ppz):Objekt_pol_martwy(36)
{
         x=xx;y=yy;px=ppx;py=ppy;pz=ppz;
         nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=0; animacja=0; HP=a->HP;
}

Lampa_przejsciowa::Lampa_przejsciowa(Lampa*a){czym_jest=36;HP=a->HP;}

void Lampa_przejsciowa :: zapisz(std::ofstream *ofs)
{

}

Lampa_przejsciowa::Lampa_przejsciowa()
{
         czym_jest=36;
}













short Reflektor::latwopalnosc(){return 20;}

Reflektor::~Reflektor()
{

}

what_happened Reflektor::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,30))==0)
         {
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki();
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Reflektor::get_co_to()
{
         short a=0;
         if(zwrot=='p') a = 0;
         else if(zwrot=='l') a = 2;
         else if(zwrot=='d') a = 4;
         else if(zwrot=='g') a = 6;
         //std::cout<<(4700+(kierunek=='l')+a+wlaczony*8)<<'\n';
         return 4700+(kierunek=='l')+a+wlaczony*8;
}

void Reflektor::zapisz(std::ofstream *a)
{

}

Reflektor::Reflektor(Reflektor_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(37)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=767; px=ppx;py=ppy;pz=ppz;
}

Reflektor_przejsciowy::Reflektor_przejsciowy(Reflektor*a)
{
         czym_jest=37; HP=a->HP;
}

Reflektor_przejsciowy::~Reflektor_przejsciowy()
{

}

Reflektor_przejsciowy::Reflektor_przejsciowy()
{
         czym_jest=37;
}

void Reflektor_przejsciowy::zapisz(std::ofstream *a)
{

}










short Beczka::latwopalnosc(){return 0;}

Beczka::~Beczka()
{

}

what_happened Beczka::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,70))==0)
         {
                  Plansza *pl = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
                  pl->zaktualizuj_widoki();
                  if(stan_b&1 && ((wsp_zajecia==-1) || (pl->srodowisko[y][x] && pl->srodowisko[y][x]->stan&1) || kto==obrazenia_od_wybuchu || kto==obrazenia_od_ognia))
                           wybuchnij();////////////////////////////////////////////////////////////////////////////////////////?????
                  else if(stan_b&1)
                           rozlej_w_miejscu();
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Beczka::get_co_to()
{
         return 4800 + ((stan_b&2)==2)*3 + (((stan_b&4)==4) ? (((stan_b&8)==8) ? 1 : 2) : 0);
}

void Beczka::zapisz(std::ofstream *a)
{

}

void Beczka::wybuchnij()
{
         swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->wybuch_o_mocy(3, x, y);
}

void Beczka::rozlej_w_miejscu()
{
         Plansza *pl = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         short h=Plansza::ile(3, x, y);
         punkt **a = new punkt*[h+1];
         a[h] = NULL;
         short l=0;
         for(short t=0; t<=3; ++t)
                  l = Plansza::wstaw_w_punkty(a, l, t, x, y);

         for(short k=0; a[k]; ++k)
         {
                  if(Strefa::w_planszy(a[k]->x, a[k]->y) && da_sie_dojsc(x, y, a[k]->x, a[k]->y, pl))
                  {
                       if(!pl->srodowisko[a[k]->y][a[k]->x]) pl->srodowisko[a[k]->y][a[k]->x]=new Srodowisko;
                       if(!(pl->srodowisko[a[k]->y][a[k]->x]->stan&4)) pl->srodowisko[a[k]->y][a[k]->x]->stan+=4;
                  }
         }

         for(short t=0; a[t]; ++t) delete a[t];
         delete [] a;
         return;
}

void Beczka::rozlej_w_kierunku(char gdzie)
{
         Swiat *swiat = Objekt::swiat;
         Plansza *ap,*ad,*al,*ag, *akt = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         if(true)
         {
                  ap = swiat->zwroc_taka_plansze(px+1, py, pz);
                  al = swiat->zwroc_taka_plansze(px-1, py, pz);
                  ad = swiat->zwroc_taka_plansze(px, py+1, pz);
                  ag = swiat->zwroc_taka_plansze(px, py-1, pz);
         }///g i l 18:23

         ///    1
         ///2 0 3
         ///    4

         short szer=x, wys=y; if(zwrot=='p' || zwrot=='l') {szer=y; wys=x;}


         for(short i=0;i<5;++i)///dlugosc
         {
                  short f = (i+1)/2 + 1;

                  for(short e=szer-f; e<=szer+f; ++e)///szerokosc
                  {
                                    short akt_x=e, akt_y=y + (zwrot=='g' ? -1-i : 1+i); if(zwrot=='p' || zwrot=='l') {akt_x=x+(zwrot=='p' ? 1+i : -1-i); akt_y=e;}

                                    if(akt_y<13 && akt_y>-1 && akt_x<21 && akt_x>-1)
                                    {
                                             //if(tez_poza_plansze) continue;
                                             if(da_sie_dojsc(akt_x, akt_y, x, y, akt))
                                             {
                                                      if(akt->srodowisko[akt_y][akt_x]==NULL) akt->srodowisko[akt_y][akt_x]=new Srodowisko;
                                                      akt->srodowisko[akt_y][akt_x]->stan|=4;
                                             }
                                    }
                                    else
                                    {
                                             ///dzwiek moze miec zasieg jednej planszy, wieksze nie beda dalej slyszane
                                             if(akt_y<26 && akt_y>-14 && akt_x<42 && akt_x>-21)
                                             {
                                                      if(akt_x>20)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x-21, akt_y) || !ap) continue;
                                                               if(da_sie_dojsc(akt_x-21, akt_y, 0, y, ap) && da_sie_dojsc(20, y, x, y, akt))
                                                               {
                                                                        if(ap->srodowisko[akt_y][akt_x-21]==NULL) ap->srodowisko[akt_y][akt_x-21]=new Srodowisko;
                                                                        ap->srodowisko[akt_y][akt_x-21]->stan|=4;
                                                               }
                                                      }
                                                      else if(akt_x<0)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x+21, akt_y) || !al) continue;
                                                               if(da_sie_dojsc(akt_x+21, akt_y, 20, y, al) && da_sie_dojsc(0, y, x, y, akt))
                                                               {
                                                                        if(al->srodowisko[akt_y][akt_x+21]==NULL) al->srodowisko[akt_y][akt_x+21]=new Srodowisko;
                                                                        al->srodowisko[akt_y][akt_x+21]->stan|=4;
                                                               }
                                                      }
                                                      else if(akt_y<0)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x, akt_y+13) || !ag) continue;
                                                               if(da_sie_dojsc(akt_x, akt_y+13, x, 12, ag) && da_sie_dojsc(x, 0, x, y, akt))
                                                               {
                                                                        if(ag->srodowisko[akt_y+13][akt_x]==NULL) ag->srodowisko[akt_y+13][akt_x]=new Srodowisko;
                                                                        ag->srodowisko[akt_y+13][akt_x]->stan|=4;
                                                               }
                                                      }
                                                      else if(akt_y>12)
                                                      {
                                                               if(!Strefa::w_planszy(akt_x, akt_y-13) || !ad) continue;
                                                               if(da_sie_dojsc(akt_x, akt_y-13, x, 0, ad) && da_sie_dojsc(x, 12, x, y, akt))
                                                               {
                                                                        if(ad->srodowisko[akt_y-13][akt_x]==NULL) ad->srodowisko[akt_y-13][akt_x]=new Srodowisko;
                                                                        ad->srodowisko[akt_y-13][akt_x]->stan|=4;
                                                               }
                                                      }
                                             }
                                    }
                  }
         }
}

void Beczka::otworz()
{
         stan_b|=2;
         if((stan_b&1)&&(stan_b&4))
         {
                  stan_b-=1; rozlej_w_kierunku(zwrot);
         }
         swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(x, y);
         ///////////////////////
}

void Beczka::zamknij()
{
         if(stan_b&2) stan_b-=2;
}

void Beczka::przewroc_mnie(char zwr)
{
         zwrot = zwr;
         stan_b|=4;
         wysokosc = 1;
         if(zwrot=='l') stan_b|=8; else if(stan_b&8) stan_b-=8;
         if((stan_b&1) && (stan_b&2))
         {
                  stan_b-=1; rozlej_w_kierunku(zwr);
         }
         swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(x, y);
}

void Beczka::podnies()
{
         if(stan_b&4)
         {
                  wysokosc = 2;
                  stan_b -= 4; swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(x, y);
         }
}

Beczka::Beczka(Beczka_przejsciowa* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(34)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=2;
         co_to=767; px=ppx;py=ppy;pz=ppz; stan_b = a->stan_b;
}

Beczka_przejsciowa::Beczka_przejsciowa(Beczka*a)
{
         czym_jest=34; HP=a->HP; stan_b = a->stan_b;
}

Beczka_przejsciowa::~Beczka_przejsciowa()
{

}

Beczka_przejsciowa::Beczka_przejsciowa()
{
         czym_jest=34;
}

void Beczka_przejsciowa::zapisz(std::ofstream *a)
{

}














short Staly_przejsciowy::wys()
{
         switch(ktory)
         {
                  case 0: return 2;///opony
                  default: return 0;
         }
}

short Staly_przejsciowy::max_hp(short ktory)
{
         switch(ktory)
         {
                  case 0: return 200;///opony
                  default: return 100;
         }
}

short Staly::latwopalnosc(){switch(ktory){default: return 20;}}

Staly::~Staly()
{

}

what_happened Staly::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,Staly_przejsciowy::max_hp(czym_jest)))==0)
         {
                  swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki();
                  smierc(); return dead;
         } else HP=a;
         return success;
}

int Staly::get_co_to()
{
         return 4900 + ktory;
}

void Staly::zapisz(std::ofstream *a)
{

}

Staly::Staly(Staly_przejsciowy* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(38), ktory(a->ktory)
{
         x=xx; y=yy; nie_wykonal_ruchu=true; wykonuje_ruch=false; wysokosc = a->wys();
         co_to=767; px=ppx;py=ppy;pz=ppz; HP = a->HP;
}

Staly_przejsciowy::Staly_przejsciowy(Staly*a):ktory(a->ktory)
{
         czym_jest=38; HP=a->HP;
}

Staly_przejsciowy::~Staly_przejsciowy()
{

}

Staly_przejsciowy::Staly_przejsciowy(short kt):ktory(kt)
{
         czym_jest=38; HP = max_hp(ktory);
}

Staly_przejsciowy::Staly_przejsciowy():ktory(0)
{
         czym_jest=38; HP = max_hp(ktory);
}

void Staly_przejsciowy::zapisz(std::ofstream *a)
{

}













short WLampa::latwopalnosc(){return 60;}

WLampa::~WLampa(){}

what_happened WLampa::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         wydaj_dzwiek(false,3, x,y,czym_jest);
         int a;if((a=bycie_uderzanym_jak_drzewo(HP,obrazenia,25))==0)
         {smierc(); swiat->zwroc_taka_plansze_TYLKO(px, py, pz)->zaktualizuj_widoki(); return dead;} else HP=a; return success;
}

int WLampa::get_co_to() {return 5000 + ktore - 1;}

void WLampa::zapisz(std::ofstream *a) {}

WLampa::WLampa(WLampa_przejsciowa* a,int xx, int yy,int ppx,int ppy,int ppz):Objekt_martwy(39)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=3501; px=ppx;py=ppy;pz=ppz; HP=a->HP; ktore = a->ktore;
}

WLampa::WLampa(int xx, int yy,int ppx,int ppy,int ppz, short ktore):Objekt_martwy(39)
{
         x=xx;y=yy;nie_wykonal_ruchu=true;wykonuje_ruch=false;wysokosc=1;
         co_to=3501; px=ppx;py=ppy;pz=ppz; HP=25; this->ktore = ktore;
}

WLampa_przejsciowa::WLampa_przejsciowa(WLampa*a)
{
         czym_jest=39; HP=a->HP; ktore = a->ktore;
}

WLampa_przejsciowa::~WLampa_przejsciowa(){}

WLampa_przejsciowa::WLampa_przejsciowa() {czym_jest=39;}

void WLampa_przejsciowa::zapisz(std::ofstream *a) {}




