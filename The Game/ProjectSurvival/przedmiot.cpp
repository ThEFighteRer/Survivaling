#include "przedmiot.h"

void Skrzynka::init()
{
         if(x==0 && y==0)zawartosc=NULL; else {zawartosc=new Przedmiot**[y]; for(int i=0; i<y;++i) zawartosc[i]=new Przedmiot*[x];
         for(int i=0; i<y; ++i){for(int j=0;j<x;++j){zawartosc[i][j]=NULL;}}}
         ++wersja;
}

Skrzynka::Skrzynka(int xx, int yy) : x(xx), y(yy)
{
         init();
}

Skrzynka::Skrzynka(Kontener<Item> *a,int xx, int yy) : x(xx), y(yy)
{
         init();
         for(int i=0; i<a->ilosc; ++i)
         {
                 wloz_przedmiot(new Przedmiot(a->obiekt[i]));
         }
}

Skrzynka* Skrzynka::zamien_itemy_na_skrzynke(Kontener<Item> *a,int xx, int yy)
{
         Skrzynka*b=new Skrzynka(a,xx,yy); delete a; return b;
}

Skrzynka::~Skrzynka()
{
         if(mutex) al_lock_mutex(mutex);
         for(int i=items.ilosc-1; i>-1; --i)
         {
                  Przedmiot *p=items.obiekt[i];
                  wyjmij_przedmiot(p);
                  p->usun_calego();
         }

         for(int i=0; i<y;++i) delete [] zawartosc[i];
         delete [] zawartosc;

         //++wersja;
         if(mutex) al_unlock_mutex(mutex);
}

bool Skrzynka::wyjmij_przedmiot(Przedmiot*a)
{
         items.usun_objekt(a);
         switch(a->typ_wielkosci())
         {
                  case 1:zawartosc[a->y][a->x]=NULL;break;
                  case 2:zawartosc[a->y][a->x]=NULL;zawartosc[a->y+1][a->x]=NULL;break;
                  case 3:for(int i=a->x;i<a->x+2;++i){for(int j=a->y;j<a->y+8;++j){zawartosc[j][i]=NULL;}}break;
                  case 4:for(int i=a->x;i<a->x+9;++i){for(int j=a->y;j<a->y+6;++j){zawartosc[j][i]=NULL;}}break;
                  case 5:for(int i=a->x;i<a->x+2;++i){for(int j=a->y;j<a->y+6;++j){zawartosc[j][i]=NULL;}}break;
                  case 6:for(int i=a->x;i<a->x+9;++i){for(int j=a->y;j<a->y+3;++j){zawartosc[j][i]=NULL;}}break;
                  case 7:for(int i=a->x;i<a->x+1;++i){for(int j=a->y;j<a->y+8;++j){zawartosc[j][i]=NULL;}}break;
                  case 8:for(int i=a->x;i<a->x+2;++i){for(int j=a->y;j<a->y+2;++j){zawartosc[j][i]=NULL;}}break;
                  case 9:for(int i=a->x;i<a->x+2;++i){for(int j=a->y;j<a->y+1;++j){zawartosc[j][i]=NULL;}}break;
                  case 10:for(int i=a->x;i<a->x+2;++i){for(int j=a->y;j<a->y+11;++j){zawartosc[j][i]=NULL;}}break;
                  case 11:for(int i=a->x;i<a->x+9;++i){for(int j=a->y;j<a->y+2;++j){zawartosc[j][i]=NULL;}}break;
                  case 12:for(int i=a->x;i<a->x+1;++i){for(int j=a->y;j<a->y+8;++j){zawartosc[j][i]=NULL;}}break;
                  case 13:for(int i=a->x;i<a->x+1;++i){for(int j=a->y;j<a->y+5;++j){zawartosc[j][i]=NULL;}}break;
                  case 14:for(int i=a->x;i<a->x+1;++i){for(int j=a->y;j<a->y+4;++j){zawartosc[j][i]=NULL;}}break;
                  case 15:for(int i=a->x;i<a->x+3;++i){for(int j=a->y;j<a->y+2;++j){zawartosc[j][i]=NULL;}}break;
                  case 16:for(int i=a->x;i<a->x+6;++i){for(int j=a->y;j<a->y+1;++j){zawartosc[j][i]=NULL;}}break;
                  default: {std::cout<<"ja nie wiem jak wyjac ten przedmiot"<<'\n'; throw "ja nie wiem jak wyjac ten przedmiot";}
         }
         ++wersja;return true;
}

Przedmiot *Skrzynka::zwroc_przedmiot(Item *a)
{
         if(mutex) al_lock_mutex(mutex);
         for(short i=0; i<items.ilosc; ++i)
                  if(items.obiekt[i]->item==a)
                  {
                           if(mutex) al_unlock_mutex(mutex);
                           return items.obiekt[i];
                  }
         if(mutex) al_unlock_mutex(mutex);
         return NULL;
}

bool Skrzynka::wloz_przedmiot(int xx, int yy, Przedmiot*a)
{
         if(mutex) al_lock_mutex(mutex);
         if(xx<0 || xx>=x || yy<0 || yy>=y) {if(mutex) al_unlock_mutex(mutex); return false;}

         items.dodaj_obiekt(a); int aa,bb;
         if(false)
         {
                  tu:
                           if(mutex) al_unlock_mutex(mutex);
                           return true;
         }
         switch(a->typ_wielkosci())
         {
                  case 1: if(zawartosc[yy][xx]==NULL) {zawartosc[yy][xx]=a; a->y=yy; a->x=xx; ++wersja;goto tu;} break;
                  case 2: if(yy+1<y && zawartosc[yy][xx]==NULL && zawartosc[yy+1][xx]==NULL) {zawartosc[yy][xx]=a;zawartosc[yy+1][xx]=a; a->y=yy; a->x=xx; ++wersja;goto tu;} break;
                  case 3: if(xx+1<x && yy+7<y){bool zle=false;for(int i=xx;i<xx+2;++i){for(int j=yy;j<yy+8;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+2;++i){for(int j=yy;j<yy+8;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 4: if(xx+8<x && yy+5<y){bool zle=false;for(int i=xx;i<xx+9;++i){for(int j=yy;j<yy+6;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+9;++i){for(int j=yy;j<yy+6;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 5: if(xx+1<x && yy+5<y){bool zle=false;for(int i=xx;i<xx+2;++i){for(int j=yy;j<yy+6;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+2;++i){for(int j=yy;j<yy+6;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 6: if(xx+8<x && yy+2<y){bool zle=false;for(int i=xx;i<xx+9;++i){for(int j=yy;j<yy+3;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+9;++i){for(int j=yy;j<yy+3;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 7: aa=1,bb=8;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;;}break;
                  case 8: aa=2,bb=2;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 9: aa=2,bb=1;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 10: aa=2,bb=11;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 11: aa=9,bb=2;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 12: aa=1,bb=8;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 13: aa=1,bb=5;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;}break;
                  case 14: aa=1,bb=4;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;;}break;
                  case 15: aa=3,bb=2;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;;}break;
                  case 16: aa=1,bb=6;if(xx+aa-1<x && yy+bb-1<y){bool zle=false;for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){if(zawartosc[j][i]!=NULL)
                  {zle=true;break;}}if(zle)break;} if(!zle)for(int i=xx;i<xx+aa;++i){for(int j=yy;j<yy+bb;++j){zawartosc[j][i]=a;}}else break; a->y=yy; a->x=xx;++wersja;goto tu;;}break;
                  default: {std::cout<<"ja nie wiem jak wlozyc ten przedmiot"<<a->item->czym_jest<<'\n'; throw "ja nie wiem jak wlozyc ten przedmiot";}
         }
         items.usun_objekt(a);
         if(mutex) al_unlock_mutex(mutex);
         return false;
}

bool Skrzynka::wloz_przedmiot(Przedmiot*a)
{
         if(mutex) al_lock_mutex(mutex);
         if(false)
         {
                  tuu:
                           if(mutex) al_unlock_mutex(mutex);
                           return true;
         }
         switch(a->typ_wielkosci())
         {
                  case 1: for(int i=0;i<y;++i){for(int j=0;j<x;++j){if(zawartosc[i][j]==NULL) {wloz_przedmiot(j,i,a);goto tuu;}}} break;
                  case 2: for(int i=0;i<=y-2;++i){for(int j=0;j<x;++j){if(zawartosc[i][j]==NULL && zawartosc[i+1][j]==NULL) {wloz_przedmiot(j,i,a);goto tuu;}}} break;
                  case 3: for(int i=0;i<=y-8;++i){for(int j=0;j<=x-2;++j){if(wloz_przedmiot(j, i, a)) goto tuu;;}} break;
                  case 4: for(int i=0;i<=y-6;++i){for(int j=0;j<=x-9;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 5: for(int i=0;i<=y-6;++i){for(int j=0;j<=x-2;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 6: for(int i=0;i<=y-3;++i){for(int j=0;j<=x-9;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 7: for(int i=0;i<=y-1;++i){for(int j=0;j<=x-8;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 8: for(int i=0;i<=y-2;++i){for(int j=0;j<=x-2;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 9: for(int i=0;i<=y-1;++i){for(int j=0;j<=x-2;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 10: for(int i=0;i<=y-11;++i){for(int j=0;j<=x-2;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 11: for(int i=0;i<=y-2;++i){for(int j=0;j<=x-9;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 12: for(int i=0;i<=y-8;++i){for(int j=0;j<=x-1;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 13: for(int i=0;i<=y-5;++i){for(int j=0;j<=x-1;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 14: for(int i=0;i<=y-4;++i){for(int j=0;j<=x-1;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 15: for(int i=0;i<=y-2;++i){for(int j=0;j<=x-3;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  case 16: for(int i=0;i<=y-6;++i){for(int j=0;j<=x-1;++j){if(wloz_przedmiot(j, i, a)) goto tuu;}} break;
                  default: {std::cout<<"ja nie wiem jak wlozyc ten przedmiot"<<'\n'; throw "ja nie wiem jak wlozyc ten przedmiot";}
         }
         if(mutex) al_unlock_mutex(mutex);
         return false;
}

Przedmiot* Skrzynka::przedmiot(int xx, int yy)
{
         if(yy<0 || yy>=y || xx<0 || xx>=x) return NULL;
         return zawartosc[yy][xx];
}

Kontener<Item>* Skrzynka::lista_itemow()
{
         if(mutex) al_lock_mutex(mutex);
         Kontener<Item>*a=new Kontener<Item>();
         for(int i=0;i<items.ilosc;i++) a->dodaj_obiekt(items.obiekt[i]->item);
         if(mutex) al_unlock_mutex(mutex);
         return a;
}

void Skrzynka::wyjmij_wszystko_z_usunieciem_tylko_oslonki_itemow_czyli_przedmiotow()
{
         if(mutex) al_lock_mutex(mutex);
         for(int i=items.ilosc-1;i>-1;--i)
         {
                  Przedmiot *a=items.obiekt[i];
                  wyjmij_przedmiot(a);
                  delete a; ///on nie usuwa itemow
         }
         if(mutex) al_unlock_mutex(mutex);
}

std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>> Skrzynka::raport_obrazkowy()
{
         if(mutex) al_lock_mutex(mutex);
         std::vector<std::pair<int, punkt>> aaa(items.ilosc);
         for(short i=0; i<items.ilosc; ++i)
                  aaa[i] = std::pair<int, punkt>(items.obiekt[i]->item->get_co_to(), punkt(items.obiekt[i]->x, items.obiekt[i]->y));
         if(mutex) al_unlock_mutex(mutex);
         return std::pair<std::vector<std::pair<int, punkt>>,std::pair<int, int>>(aaa, std::pair<int, int>(x, y));
}

void Skrzynka::usun_mutex()
{
         if(mutex)
         {
                  al_lock_mutex(mutex);
                  ALLEGRO_MUTEX *a = mutex;
                  mutex = NULL;
                  al_unlock_mutex(a);
         }
}

void Skrzynka::ustanow_mutex(ALLEGRO_MUTEX *m)
{
         mutex = m;
}

Kontener<Item>* Skrzynka::zamien_skrzynke_na_itemy(Skrzynka *a)
{
         Kontener<Item>*b=a->lista_itemow();
         a->wyjmij_wszystko_z_usunieciem_tylko_oslonki_itemow_czyli_przedmiotow();
         delete a;
         return b;
}

Przedmiot::Przedmiot(Item *item)
{
         this->item=item;
}

Przedmiot::~Przedmiot()
{
         ///nie moze usuwac itemow
}

void Przedmiot::usun_calego()
{
         delete item; delete this;
}

int Przedmiot::get_co_to()
{
         if(item!=NULL) return item->get_co_to(); else return -1;
}

int Przedmiot::typ_wielkosci()
{
         if(item!=NULL) return item->typ_wielkosci(); else return -1;
}

bool Item::mozna_do_plecaka()
{
         return !jest_plecakiem() && czym_jest!=4009 && czym_jest!=4012;
}

bool Przedmiot::jest_plecakiem(){return item->czym_jest>=3000 && item->czym_jest<4000;}
bool Przedmiot::jest_kapeluszem(){return item->czym_jest>=5000 && item->czym_jest<5500;}
bool Przedmiot::jest_korpusem(){return item->czym_jest>=5500 && item->czym_jest<6000;}
bool Przedmiot::jest_spodniami(){return item->czym_jest>=6000 && item->czym_jest<6500;}
bool Przedmiot::jest_butami(){return item->czym_jest>=6500 && item->czym_jest<7000;}
bool Przedmiot::jest_rekawicami(){return item->czym_jest>=7000 && item->czym_jest<7500;}
bool Przedmiot::jest_bronia(){return item->czym_jest>=4000 && item->czym_jest<4999;}
bool Przedmiot::jest_bronia_na_ramie(){return item->czym_jest>=4000 && item->czym_jest<4499;}
bool Przedmiot::jest_ubraniem(){return item->czym_jest>=5000 && item->czym_jest<7500;}

bool Item::jest_plecakiem(){if(this==NULL)return false;return czym_jest>=3000 &&czym_jest<4000;}
bool Item::jest_kapeluszem(){if(this==NULL)return false;return czym_jest>=5000 && czym_jest<5500;}
bool Item::jest_korpusem(){if(this==NULL)return false;return czym_jest>=5500 && czym_jest<6000;}
bool Item::jest_spodniami(){if(this==NULL)return false;return czym_jest>=6000 && czym_jest<6500;}
bool Item::jest_butami(){if(this==NULL)return false;return czym_jest>=6500 && czym_jest<7000;}
bool Item::jest_rekawicami(){if(this==NULL)return false;return czym_jest>=7000 && czym_jest<7500;}
bool Item::jest_bronia(){if(this==NULL)return false;return czym_jest>=4000 && czym_jest<4999;}
bool Item::jest_bronia_na_ramie(){if(this==NULL)return false;return czym_jest>=4000 && czym_jest<4499;}
bool Item::jest_ubraniem(){if(this==NULL)return false;return czym_jest>=5000 && czym_jest<7500;}
bool Item::jest_mala_bronia(){if(this==NULL)return false;return czym_jest>=4500 && czym_jest<5000;}
bool Item::jest_kluczem(){if(this==NULL)return false; return czym_jest==8010 || czym_jest==8011 || czym_jest==8012;}
bool Item::jest_klodkom(){if(this==NULL)return false; return czym_jest==8007 || czym_jest==8008 || czym_jest==8009;}

int Item::typ_wielkosci()
{
         switch(czym_jest)
         {
                  case 2001: case 2006: case 3001: case 4501: case 5001: case 2007: case 8001: case 6003: case 5002:
                           case 2002:case 3002:case 3003:case 3004:case 3005:case 3006:case 2102:case 2103:case 2104:
                                    case 8017: case 8004: case 4502: case 4503: case 4009: case 4012: case 8018: case 8020: return 1;
                  case 4251: case 4252: case 4255: case 4253: return 6;
                  case 4004: return 3;
                  case 4005: return 5;
                  case 2101: case 2003:case 2004:case 2005:case 8022: case 8003:case 8019: case 2008: case 2009: case 2010: case 2201: case 2202: case 2020: return 2;
                  case 4006: return 10;
                  case 6505: case 4752: case 4751:case 8002:return 8;
                  case 6504:case 6503:case 6502:case 6501:case 6004: case 6002:case 6001:case 5503:case 5502:case 5501:
                           case 4753: case 2013: case 2014: return 9;
                  case 4256: case 4254: case 4260: return 11;
                  case 4003: return 12;
                  case 4007: return 14;
                  case 4008: return 13;
                  case 8006: case 4011: return 15;
                  case 4010: return 16;
                  default:return 1;///std::cout<<"Nie wiem jak duze to jest"; throw "n";///UWAGA OPCJA WYKORZYSTANA
         }
}
int Item::get_co_to()
{
         if(this==NULL) return 0;
         if(czym_jest==8010 || czym_jest==8011 || czym_jest==8012) return czym_jest+(((Klucz*)this)->do_czego!=NULL)*4;
         if(czym_jest==4252) {if(((Bron*)this)->mag>0)return 4251; else return czym_jest;}
         if(czym_jest==4752) {if(((Bron*)this)->mag>0)return 4751; else return czym_jest;}
         if(czym_jest==4255) {if(((Bron*)this)->mag>0)return 4253; else return czym_jest;}
         if(czym_jest==4256) {if(((Bron*)this)->mag>0)return 4254; else return czym_jest;}
         return czym_jest;
}

Item* Item::stworz_obiekt(int co)
{
         Item*a;
         if(co==2022) return new Konsumpcjum(co, 10);
         if(co==2021) return new Konsumpcjum(co, 5);
         if(co==2201 || co==2202) return new Konsumpcjum(co, 0);
         if(co==2203) return new Konsumpcjum(co, 60);
         if(co==8010 || co==8011 || co==8012) return new Klucz(co);
         if(co==8007 || co==8008 || co==8009) return new Klodka(co);
         if(co>=3000 && co<4000) {a=new Plecak(co);return a;}
         if(co==2012) return new Konsumpcjum(co, 50);
         if(co==2014) return new Konsumpcjum(co, 130);
         else if(co>=5000 && co<7500)  {a=new Ubranie(co);return a;}
         else if(co>=4000 && co<5000) {a=new Bron(co);return a;}
         else if(co>=2000 && co<3000)
                  {if(co==2101)a=new Konsumpcjum(co,32);
                  else if(co==2102)a=new Konsumpcjum(co,18);
                  else if(co==2103)a=new Konsumpcjum(co,6);
                  else if(co==2104)a=new Konsumpcjum(co,5);

                  else a=new Konsumpcjum(co,1);
                  return a;
                  }
         else if(co==8017)return new Konsumpcjum(co,20);
         else if(co==8018)return new Konsumpcjum(co,20);
                  else return new Inne(co);
         //else throw "n";
}

bool Item::jest_bronia_palna()
{return (czym_jest>4250&&czym_jest<4500)||(czym_jest>4750&&czym_jest<5000);}

bool Item::jest_bronia_biala()
{return (czym_jest>4000&&czym_jest<4250)||(czym_jest>4500&&czym_jest<4750);}

bool Item::jest_konsumpcjum()
{
         return czym_jest>2000 && czym_jest<3000;
}

int Item::wartosc_ataku_rzucanego()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 4009: return losuj(20, 40);
                  case 4012: return losuj(5, 60);
                  default:
                  switch(typ_wielkosci())
                  {
                           case 1: return losuj(1,3);
                           case 2: return losuj(2,7);
                           case 3: return losuj(10,15);
                           case 4: return losuj(15,20);
                           case 5: return losuj(2,9);
                           case 6: return losuj(15,23);
                           case 7: return losuj(13,18);
                           case 8: return losuj(3,8);
                           case 9: return losuj(2,7);
                           case 10: return losuj(9,14);
                           case 11: return losuj(15,25);
                           case 12: return losuj(10,13);
                           case 13: return losuj(10,13);
                           case 14: return losuj(10,13);
                           case 16: return losuj(10,13);
                           default:return losuj(0,3);
                  }
         }
}

bool Item::mozna_do_kieszeni()
{
         if(this==NULL) return 0;
         if(jest_plecakiem() || czym_jest == 4009 || czym_jest==4012) return false;
         switch(typ_wielkosci())
         {
                  case 1:case 2:case 9:case 8:return true;
                  case 3: case 4: case 5: case 6: case 7:  case 10:case 11: case 12:case 13:case 14: case 15: case 16: return false;
                  default:return true;
         }
}

Item* Item::wylosuj_item(int szansa_na_ubranie, int szansa_na_plecak, int szansa_na_bron,int szansa_na_inne,int szansa_na_jedzenie,int szansa_na_medykamenty)
{
         int los=losuj(1, szansa_na_ubranie+szansa_na_plecak+szansa_na_bron+szansa_na_inne+szansa_na_jedzenie+szansa_na_medykamenty);
         if(los<=szansa_na_ubranie)
         {
                  switch(losuj(1,5))
                  {
                           case 1: return stworz_obiekt(5000+losuj(1,2));
                           case 2: return stworz_obiekt(5500+losuj(1,3));
                           case 3: return stworz_obiekt(6000+losuj(1,4));
                           case 4: return stworz_obiekt(6500+losuj(1,5));
                           case 5: return stworz_obiekt(5000+losuj(1,2));
                  }
         }
         else if(los<=szansa_na_plecak+szansa_na_ubranie)
         {
                  return stworz_obiekt(3000+losuj(1,6));
         }
         else if(los<=szansa_na_bron+szansa_na_plecak+szansa_na_ubranie)
         {
                  int los=losuj(1,12);
                  if(los<=6)///biala
                  {
                           switch(losuj(1,9))
                           {
                                    case 1: return stworz_obiekt(4003);
                                    case 2: return stworz_obiekt(4005);
                                    case 3: return stworz_obiekt(4006);
                                    case 4: return stworz_obiekt(4007);
                                    case 5: return stworz_obiekt(4008);
                                    case 6: return stworz_obiekt(4502);
                                    case 7: return stworz_obiekt(4503);
                                    case 8: case 9: return stworz_obiekt(4011);
                           }
                  }
                  else if(los<=9)///amunicja
                  {
                           if(!losuj(0, 10))return stworz_obiekt(2100+losuj(1,4));
                           else return stworz_obiekt(8018);
                  }
                  else///palna
                  {
                           switch(losuj(1, 5))
                           {
                                    case 1: return stworz_obiekt(4252);
                                    case 2: return stworz_obiekt(4256);
                                    case 3: return stworz_obiekt(4752);
                                    case 4: return stworz_obiekt(4753);
                                    case 5: return stworz_obiekt(4260);
                           }
                  }
         }
         else if(los<=szansa_na_inne+szansa_na_bron+szansa_na_plecak+szansa_na_ubranie)
         {
                  switch(losuj(1,8))
                  {
                           case 1: return stworz_obiekt(8001);
                           case 2: return stworz_obiekt(8003);
                           case 3: return stworz_obiekt(8017);
                           case 4: return stworz_obiekt(8021);
                           case 5: return stworz_obiekt(8023);
                           case 6: return stworz_obiekt(8020);
                           case 7: return stworz_obiekt(2202);
                           case 8: return stworz_obiekt(2203);
                  }
         }
         else if(los<=szansa_na_jedzenie+szansa_na_bron+szansa_na_inne+szansa_na_plecak+szansa_na_ubranie)
         {
                  if(losuj(1,12)==1) return stworz_obiekt(2005);
                  else switch(losuj(1,3))
                  {
                           case 1: return stworz_obiekt(2001);
                           case 2: return stworz_obiekt(2006);
                           case 3: return stworz_obiekt(2020);
                  }
         }
         else if(los<=szansa_na_medykamenty+szansa_na_bron+szansa_na_jedzenie+szansa_na_inne+szansa_na_plecak+szansa_na_ubranie)
         {
                  switch(losuj(1,5))
                  {
                           case 1: return stworz_obiekt(2007);
                           case 2: return stworz_obiekt(8024);
                           case 3: return stworz_obiekt(8025);
                           case 4: return stworz_obiekt(2008);
                           case 5: return stworz_obiekt(2022);
                  }
         }
         else {return stworz_obiekt(2007);}
}

Item** Item::wylosuj_liste_itemow(int szansa_na_ubranie,int szansa_na_plecak,int szansa_na_bron,int szansa_na_inne,int szansa_na_jedzenie,int szansa_na_medykamenty)
{
         short ile = 0; Item** a = new Item*[7];
         if(losuj(1, 100) <= szansa_na_ubranie)
         {
                  switch(losuj(1,5))
                  {
                           case 1: a[ile++]= stworz_obiekt(5000+losuj(1,2)); break;
                           case 2: a[ile++]= stworz_obiekt(5500+losuj(1,3)); break;
                           case 3: a[ile++]= stworz_obiekt(6000+losuj(1,4)); break;
                           case 4: a[ile++]= stworz_obiekt(6500+losuj(1,5)); break;
                           case 5: a[ile++]= stworz_obiekt(5000+losuj(1,2)); break;
                  }
         }
         if(losuj(1,100) <= szansa_na_plecak) a[ile++] = stworz_obiekt(3000+losuj(1,6));
         if(losuj(1,100) <= szansa_na_inne)
                  switch(losuj(1,8))
                  {
                           case 1: a[ile++] = stworz_obiekt(8001); break;
                           case 2: a[ile++] = stworz_obiekt(8003); break;
                           case 3: a[ile++] = stworz_obiekt(8017); break;
                           case 4: a[ile++] = stworz_obiekt(8021); break;
                           case 5: a[ile++] = stworz_obiekt(8023); break;
                           case 6: a[ile++] = stworz_obiekt(8020); break;
                           case 7: a[ile++] = stworz_obiekt(2202); break;
                           case 8: a[ile++] = stworz_obiekt(2203); break;
                  }
         if(losuj(1,100) <= szansa_na_jedzenie)
         {
                  if(losuj(1,12)==1) a[ile++] = stworz_obiekt(2005);
                  else switch(losuj(1,3))
                  {
                           case 1: a[ile++] = stworz_obiekt(2001); break;
                           case 2: a[ile++] = stworz_obiekt(2006); break;
                           case 3: a[ile++] = stworz_obiekt(2020); break;
                  }
         }
         if(losuj(1,100) <= szansa_na_medykamenty)
         {
                  switch(losuj(1,5))
                  {
                           case 1: a[ile++] = stworz_obiekt(2007);break;
                           case 2: a[ile++] = stworz_obiekt(8024);break;
                           case 3: a[ile++] = stworz_obiekt(8025);break;
                           case 4: a[ile++] = stworz_obiekt(2008);break;
                           case 5: a[ile++] = stworz_obiekt(2022);break;
                  }
         }
         if(losuj(1,100) <= szansa_na_bron)
         {
                  short los=losuj(1,11);
                  if(los<=6)///biala
                  {
                           switch(losuj(1,8))
                           {
                                    case 1: a[ile++] = stworz_obiekt(4003); break;
                                    case 2: a[ile++] = stworz_obiekt(4005); break;
                                    case 3: a[ile++] = stworz_obiekt(4006); break;
                                    case 4: a[ile++] = stworz_obiekt(4007); break;
                                    case 5: a[ile++] = stworz_obiekt(4008); break;
                                    case 6: a[ile++] = stworz_obiekt(4502); break;
                                    case 7: a[ile++] = stworz_obiekt(4503); break;
                                    case 8: a[ile++] = stworz_obiekt(4011); break;
                           }
                  }
                  else if(los<9)///amunicja
                  {
                           a[ile++] = stworz_obiekt(2100+losuj(1,4));
                  }
                  else///palna
                  {
                           switch(losuj(1,5))
                           {
                                    case 1: a[ile++] = stworz_obiekt(4252); if(losuj(1,2) == 1) a[ile++] = stworz_obiekt(2101); break;
                                    case 2: a[ile++] = stworz_obiekt(4256); if(losuj(1,2) == 1) a[ile++] = stworz_obiekt(2104); break;
                                    case 3: a[ile++] = stworz_obiekt(4752); if(losuj(1,2) == 1) a[ile++] = stworz_obiekt(2102); break;
                                    case 4: a[ile++] = stworz_obiekt(4753); if(losuj(1,2) == 1) a[ile++] = stworz_obiekt(2103); break;
                                    case 5: a[ile++] = stworz_obiekt(4260); if(losuj(1,2) == 1) a[ile++] = stworz_obiekt(2103); break;
                           }
                  }
         }
         Item **g = new Item*[ile + 1];
         for(short i = 0; i<ile; ++i) g[i] = a[i];
         g[ile] = NULL;
         delete [] a;
         return g;
}

Item* Item::wylosuj_item(char skad)
{
        return wylosuj_item(25,5,10,10,35,15);
}

Ubranie::Ubranie(int ktore)
{
         czym_jest=ktore;
}

Ubranie::~Ubranie()
{

}

int Ubranie::cieplo()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 5001: return 6;
                  case 5002: return 3;
                  case 5501: return 5;
                  case 5502: return 7;
                  case 5503: return 7;
                  case 6001: return 6;
                  case 6002: return 5;
                  case 6003: return 1;
                  case 6004: return 3;
                  case 6501: return 3;
                  case 6502: return 2;
                  case 6503: return 4;
                  case 6504: return 3;
                  case 6505: return 6;
                  default: return 0;
         }
}

int Ubranie::ochrona()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 5001: return 20;
                  case 5002: return 10;
                  case 5501: return 33;
                  case 5502: return 25;
                  case 5503: return 33;
                  case 6001: return 26;
                  case 6002: return 20;
                  case 6003: return 4;
                  case 6004: return 9;
                  case 6501: return 40;
                  case 6502: return 42;
                  case 6503: return 33;
                  case 6504: return 45;
                  case 6505: return 40;
                  default: return 0;
         }
}

int Ubranie::kamuflaz()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 5001: return 3;
                  case 5002: return -2;
                  case 5501: return 3;
                  case 5502: return 0;
                  case 5503: return -5;
                  case 6001: return 0;
                  case 6002: return 6;
                  case 6003: return -2;
                  case 6004: return 3;
                  case 6501: return -2;
                  case 6502: return 0;
                  case 6503: return 2;
                  case 6504: return 3;
                  case 6505: return 3;
                  default: return 0;
         }
}

bool Ubranie::wykorzystaj()
{
         if(this==NULL) return false;
         if(wytrzymalosc>1) {--wytrzymalosc;return false;}
         else return true;
}

short Ubranie::obrazenia_butow()
{
         if(this==NULL) return losuj(4, 7);
         if(!jest_butami()) return 0;
         switch(czym_jest)
         {
                  case 6501: return losuj(8, 12);
                  case 6502: return losuj(14, 20);
                  case 6503: return losuj(8, 12);
                  case 6504: return losuj(8, 12);
                  case 6505: return losuj(8,  12);

                  default: return losuj(8, 12);
         }
}

Konsumpcjum::Konsumpcjum(int ktore,int pozostalo_uz)
{
         czym_jest=ktore;pozostalo_uzyc=pozostalo_uz;
}

Konsumpcjum::~Konsumpcjum()
{

}

bool Konsumpcjum::wykorzystaj()
{
         --pozostalo_uzyc;
         if(pozostalo_uzyc<=0) return true;
         return false;
}

Plecak::Plecak(int ktore)
{
         czym_jest=ktore;
         switch(ktore)
         {
                  case 3001: s=new Skrzynka(6,4); break;
                  case 3002: s=new Skrzynka(9,9); break;
                  case 3003: s=new Skrzynka(8,7); break;
                  case 3004: s=new Skrzynka(9,4); break;
                  case 3005: s=new Skrzynka(9,13); break;
                  case 3006: s=new Skrzynka(9,11); break;
                  default: s=new Skrzynka(0,0); break;
         }
}

Plecak::~Plecak()
{
         delete s;
}

int Plecak::kamuflaz()
{
         if(this==NULL) return losuj(1,6);
         switch(czym_jest)
         {
                  case 3001: return -4; break;
                  case 3002: return 7; break;
                  case 3003: return 0; break;
                  case 3004: return 2; break;
                  case 3005: return -2; break;
                  case 3006: return 5; break;
         }
}

Bron::Bron(int ktore)
{
         czym_jest=ktore;
         switch(czym_jest)
         {
                  case 4006: wytrzymalosc=35;break;
                  case 4003: wytrzymalosc=30;break;
                  case 4004: wytrzymalosc=45;break;
                  case 4010: wytrzymalosc=5;break;
                  case 4011: wytrzymalosc=30;break;
                  case 4501: wytrzymalosc=20;break;
                  case 4005: wytrzymalosc=30;break;
                  case 4007: wytrzymalosc=50;break;
                  case 4008: wytrzymalosc=30;break;
                  case 4009: wytrzymalosc=30;break;
                  case 4012: wytrzymalosc=5;break;
                  case 4502: wytrzymalosc=30;break;
                  case 4503: wytrzymalosc=30;break;

                  case 4255: wytrzymalosc=1;break;
                  case 4256: wytrzymalosc=1;break;
                  case 4252: wytrzymalosc=1;break;
                  case 4752: wytrzymalosc=1;break;
                  case 4753: wytrzymalosc=1;break;
                  case 4260: wytrzymalosc=1;break;
         }
}

Bron::~Bron()
{

}

struct punkt Bron::obrazenia()
{
         struct punkt a;
         if(this==NULL) {a.x=1;a.y=6;}
         else
         switch(czym_jest)
         {
                  case 4006: a.x=46;a.y=60;break;
                  case 4003: a.x=25;a.y=30;break;
                  case 4004: a.x=30;a.y=37;break;
                  case 4010: a.x=15;a.y=30;break;
                  case 4011: a.x=25;a.y=35;break;
                  case 4501: a.x=10;a.y=15;break;
                  case 4005: a.x=45;a.y=50;break;
                  case 4007: a.x=25;a.y=30;break;
                  case 4008: a.x=35;a.y=40;break;
                  case 4009: a.x=35;a.y=40;break;
                  case 4012: a.x=5;a.y=40;break;
                  case 4502: a.x=5;a.y=15;break;
                  case 4503: a.x=13;a.y=22;break;

                  case 4255: a.x=60;a.y=80;break;
                  case 4256: a.x=55;a.y=70;break;
                  case 4252: a.x=20;a.y=25;break;
                  case 4752: a.x=17;a.y=25;break;
                  case 4753: a.x=35;a.y=45;break;
                  case 4260: a.x=60;a.y=90;break;
         }
         return a;
}

int Bron::get_obrazenia()
{
         return losuj(obrazenia().x,obrazenia().y);
}

bool Bron::dwureczna()
{
         if(this==NULL) return true;
         if(czym_jest>4500) return false;
         else return true;
}

int Bron::get_szansa()
{
         if(this==NULL) return 60;
         switch(czym_jest)
         {
                  case 4006: return 90;
                  case 4003: return 80;
                  case 4004: return 80;
                  case 4010: return 85;
                  case 4011: return 55;
                  case 4501: return 95;
                  case 4500: return 70;
                  case 4007: return 80;
                  case 4008: return 90;
                  case 4009: return 90;
                  case 4012: return 95;
                  case 4502: return 70;
                  case 4503: return 90;
                  case 4005: return 75;

                  case 4255: return 100;
                  case 4256: return 95;
                  case 4252: return 85;
                  case 4752: return 90;
                  case 4753: return 85;
                  case 4260: return 80;
                  default: return 0;
         }
}

int Bron::get_krytyk()
{
         if(this==NULL) return 3;
         switch(czym_jest)
         {
                  case 4006: return 20;
                  case 4003: return 15;
                  case 4004: return 20;
                  case 4010: return 5;
                  case 4011: return 5;
                  case 4501: return 40;
                  case 4500: return 10;
                  case 4007: return 10;
                  case 4008: return 30;
                  case 4009: return 20;
                  case 4012: return 5;
                  case 4502: return 15;
                  case 4503: return 30;

                  case 4255: return 50;
                  case 4256: return 40;
                  case 4252: return 15;
                  case 4752: return 20;
                  case 4753: return 10;
                  case 4260: return 20;
                  default: return 0;
         }
}

struct punkt Bron::blok()
{
         struct punkt a;
         if(this==NULL) {a.x=0;a.y=8;}
         else
         switch(czym_jest)
         {
                  case 4006: a.x=60;a.y=80;break;
                  case 4003: a.x=35;a.y=45;break;
                  case 4004: a.x=40;a.y=45;break;
                  case 4010: a.x=10;a.y=15;break;
                  case 4011: a.x=10;a.y=25;break;
                  case 4501: a.x=10;a.y=15;break;
                  case 4005: a.x=30;a.y=35;break;
                  case 4007: a.x=30;a.y=35;break;
                  case 4008: a.x=15;a.y=20;break;
                  case 4009: a.x=10;a.y=15;break;
                  case 4012: a.x=0;a.y=5;break;
                  case 4502: a.x=0;a.y=8;break;
                  case 4503: a.x=2;a.y=8;break;
                  default : a.x=0;a.y=0;break;
         }
         return a;
};

int Bron::get_blok()
{
         return losuj(blok().x, blok().y);
}

int Bron::UB()
{
         int a=20; ///korekta
         if(this==NULL) return 30+a;
         switch(czym_jest)
         {
                  case 4006: return -30+a;
                  case 4003: return 0+a;
                  case 4004: return 0+a;
                  case 4010: return 10+a;
                  case 4011: return a;
                  case 4501: return 30+a;
                  case 4500: return -10+a;
                  case 4007: return 0+a;
                  case 4008:case 4009: case 4012: return 0+a;
                  case 4502: return 30+a;
                  case 4503: return 30+a;

                  case 4255: return -30+a;
                  case 4256: return -30+a;
                  case 4252: return -15+a;
                  case 4752: return 20+a;
                  case 4753: return 20+a;
                  case 4260: return -10+a;
                  default: return 0;
         }
}

int Bron::KB()
{
         int a=0;
         if(this==NULL) return 30;
         switch(czym_jest)
         {
                  case 4006: return -20;
                  case 4003: return 0;
                  case 4004: return 0;
                  case 4010: return 10;
                  case 4011: return 20;
                  case 4501: return 30;
                  case 4500: return -10;
                  case 4007: return 10+a;
                  case 4008: case 4009: case 4012: return 10+a;
                  case 4502: return 30+a;
                  case 4503: return 30+a;

                  case 4255: return -30;
                  case 4256: return -30;
                  case 4252: return -15;
                  case 4752: return 20;
                  case 4753: return 20;
                  case 4260: return -10;
                  default: return 0;
         }
}

bool Bron::wykorzystaj()///true jesli wykorzystany
{
         if(this==NULL) return false;
         if(wytrzymalosc<2) return true;
         --wytrzymalosc;return false;
}

int Bron::ilosc_strzalow_w_serii()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 4255: return 1;
                  case 4256: return 1;
                  case 4252: return 4;
                  case 4752: return 2;
                  case 4753: return 1;
                  case 4260: return 1;
                  default: return 0;
         }
}

int Bron::grubosc_strzalu()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 4255: return 3;
                  case 4256: return 3;
                  case 4252: return 1;
                  case 4752: return 1;
                  case 4753: return 3;
                  case 4260: return 5;
                  default: return 0;
         }
}

int Bron::glosnosc_broni()
{
         if(this==NULL) return 0;
         switch(czym_jest)
         {
                  case 4255: return 10;
                  case 4256: return 10;
                  case 4252: return 7;
                  case 4752: return 6;
                  case 4753: return 8;
                  case 4260: return 8;
                  default: return 10;
         }
}

Zapis::Zapis(char*a, short b)
{
         bytes = a; ile=b;
}
Zapis::Zapis()
{

}
Zapis::~Zapis()
{
         delete [] bytes;
}
char* Zapis::get_bytes()
{
         return bytes;
}
short Zapis::how_many()
{
         return ile;
}

Zapis Skrzynka::zapisz()
{
         if(items.ilosc==0)
         {
                  char* pom = new char[4];
                  for(short t=0;t<4;++t) pom[t]=0;
                  return Zapis(pom, 4);
         }
         else
         {
                  int wielkosc = 0;
                  Zapis *z = new Zapis[items.ilosc];
                  for(short t=0;t<items.ilosc;++t) {z[t] = items.obiekt[t]->zapis(); wielkosc+=z[t].how_many();}
                  char* pom = new char[4+wielkosc];

                  for(short t=0;t<4;++t) pom[t] = ((char*)&items.ilosc)[t];
                  int akt = 4;
                  for(short t=0;t<items.ilosc;++t)
                  {
                           for(short g=0; g<z[t].how_many(); ++g)
                                    pom[akt++] = z[t].get_bytes()[g];
                  }
                  return Zapis(pom, akt);
         }
}

char* Skrzynka::wczytaj(char* zapis)
{
         int wielkosc = 0;
         for(short t=0;t<4;++t) ((char*)&wielkosc)[t] = zapis[t];
         zapis += 4;
         if(wielkosc!=0)
         {
                  for(short h=0; h<wielkosc; ++h)
                  {
                           Przedmiot *a = new Przedmiot;
                           zapis = a->wczytaj(zapis);
                           wloz_przedmiot(a->x, a->y, a);
                  }
         }
         return zapis;
}

int Skrzynka::ile_zajmie_bajtow()
{
         short ilosc=0;
         for(short g=0; g<items.ilosc; ++g)
                  ilosc+=items.obiekt[g]->ile_zajmie_bajtow();
         return ilosc;
}

int Item::ile_zajmie_bajtow()
{
         if(this==NULL) return 8;
         if(jest_plecakiem())
         {
                  return 8+((Plecak*)this)->s->ile_zajmie_bajtow();
         }
         else return 8;
}

char* Przedmiot::wczytaj(char *zapis)
{
         std::pair<Item*, char*> rez = Item::stworz_obiekt(zapis);
         zapis = rez.second;
         item = rez.first;
         x = zapis[0];
         y = zapis[1];
         return zapis+2;
}

Zapis Przedmiot::zapis()
{
         Zapis a = item->zapis();
         char* d = new char[a.how_many()+2];
         for(short t=0;t<a.how_many();++t) d[t] = a.get_bytes()[t];
         d[a.how_many()]=x;
         d[a.how_many()+1]=y;
         return Zapis(d, a.how_many()+2);
}

int Przedmiot::ile_zajmie_bajtow()
{
         return item->ile_zajmie_bajtow() + 2;
}

std::pair<Item*, char*> Item::stworz_obiekt(char *ktory)
{
         int co;
         for(short t=0;t<4;++t) ((char*)&co)[t] = ktory[t];

         if(co==0) return std::pair<Item*, char*>(NULL, ktory+8);

         Item* a = stworz_obiekt(co);
         if(a->jest_bronia())
         {
                  short w;
                  for(short t=0;t<2;++t) ((char*)&w)[t] = ktory[t+4];
                  ((Bron*)a)->wytrzymalosc = w;
                  for(short t=0;t<2;++t) ((char*)&w)[t] = ktory[t+6];
                  ((Bron*)a)->mag = w;
                  ktory+=8;
         }
         else if(a->jest_konsumpcjum())
         {
                  short w;
                  for(short t=0;t<2;++t) ((char*)&w)[t] = ktory[t+4];
                  ((Konsumpcjum*)a)->pozostalo_uzyc = w;
                  ktory+=8;
         }
         else if(a->jest_ubraniem())
         {
                  short w;
                  for(short t=0;t<2;++t) ((char*)&w)[t] = ktory[t+4];
                  ((Ubranie*)a)->wytrzymalosc = w;
                  ktory+=8;
         }
         else if(a->jest_plecakiem())
         {
                  ktory = ((Plecak*)a)->s->wczytaj(ktory+4);
         }
         else
         {
                  ktory +=8;
         }

         return std::pair<Item*, char*>(a, ktory);
}

Zapis Bron::zapis()
{
         char *c = new char[8];
         for(short t=0;t<4;++t) c[t] = ((char*)&czym_jest)[t];
         for(short t=0;t<2;++t) c[t+4] = ((char*)&wytrzymalosc)[t];
         for(short t=0;t<2;++t) c[t+6] = ((char*)&mag)[t];
         return Zapis(c, 8);
}

Zapis Konsumpcjum::zapis()
{
         char *c = new char[8];
         for(short t=0;t<4;++t) c[t] = ((char*)&czym_jest)[t];
         for(short t=0;t<2;++t) c[t+4] = ((char*)&pozostalo_uzyc)[t];
         for(short t=0;t<2;++t) c[t+6]=0;
         return Zapis(c, 8);
}

Zapis Ubranie::zapis()
{
         char *c = new char[8];
         for(short t=0;t<4;++t) c[t] = ((char*)&czym_jest)[t];
         for(short t=0;t<2;++t) c[t+4] = ((char*)&wytrzymalosc)[t];
         for(short t=0;t<2;++t) c[t+6]=0;
         return Zapis(c, 8);
}

Zapis Plecak::zapis()///zapisujemy przedmioty
{
         Zapis a = s->zapisz();
         char* d = new char[a.how_many()+4];
         for(short t=0;t<a.how_many();++t) d[t+4] = a.get_bytes()[t];
         for(short t=0;t<4;++t) d[t] = ((char*)&czym_jest)[t];
         return Zapis(d, a.how_many()+4);
}

Zapis Inne::zapis()
{
         char *c = new char[8];
         for(short t=0;t<4;++t) c[t] = ((char*)&czym_jest)[t];
         for(short t=0;t<4;++t) c[t] = c[4+t]=0;
         return Zapis(c, 8);
}

Zapis Klucz::zapis()
{
         char *c = new char[8];
         for(short t=0;t<4;++t) c[t] = ((char*)&czym_jest)[t];
         for(short t=0;t<4;++t) c[t] = c[4+t]=0;
         return Zapis(c, 8);
}

Zapis Klodka::zapis()
{
         char *c = new char[8];
         for(short t=0;t<4;++t) c[t] = ((char*)&czym_jest)[t];
         for(short t=0;t<4;++t) c[t] = c[4+t]=0;
         return Zapis(c, 8);
}

Inne::Inne(int co)
{
         czym_jest=co;
}

Klucz::Klucz(int co)
{
         czym_jest=co;
}

Klucz::Klucz(int co,Klodka*do_cz)
{
         czym_jest=co;do_czego=do_cz;
}

Klodka::Klodka(int co)
{
         czym_jest=co;
         switch(co)
         {
                  case 8007: HP=300; break;
                  case 8008: HP=250; break;
                  case 8009: HP=200; break;
         }
}

int Klodka::max_hp()
{
         switch(czym_jest)
         {
                  case 8007: return 300;case 8008: return 250;case 8009: return 200;
         }
}


















Crafting_recipes::Crafting_recipes()
{
         ile_kategorii = 3;short *wiersze = new short[200];
         kategoria = new Przepis**[ile_kategorii+1]; kategoria[ile_kategorii] = NULL;

         for(short y=0; y<ile_kategorii; ++y)
         {
                  Przepis **a = daj_liste_przepisow(y);
                  short h=0;
                  double suma_wierszy = 0;
                  float aktualny_wiersz = 0;
                  for(short h=0; a[h]!=NULL; ++h)
                  {
                           wiersze[h] = a[h]->potrzebne_wiersze(rozmiary(0, y));
                           short j = 1*((double)wiersze[h]) + 0.5;
                           if(aktualny_wiersz+j<=8)
                           {
                                    suma_wierszy += j;
                                    aktualny_wiersz +=j;
                           }
                           else
                           {
                                    suma_wierszy +=11-aktualny_wiersz;
                                    suma_wierszy += j;
                                    aktualny_wiersz=j;
                           }
                           /*wiersze[h] = a[h]->potrzebne_wiersze(rozmiary(0, y));
                           suma_wierszy += 1*((double)wiersze[h]) + 0.5;*/
                  }

                  short ilosc_stron = int(suma_wierszy/11) + ((int(suma_wierszy)%11)>0 ? 1 : 0);
                  kategoria[y] = new Przepis *[ilosc_stron+1];
                  kategoria[y][ilosc_stron] = NULL;

                  short ktora_str = 0;
                  float licznik_wierszy = 0;
                  short *ilosci_itemow_na_stronie = new short[ilosc_stron]; for(short k=0;k<ilosc_stron;++k) ilosci_itemow_na_stronie[k]=0;
                  for(short k=0; a[k]!=NULL; ++k)
                  {

                           if(licznik_wierszy+float(wiersze[k])+0.5<=11)
                           {
                                    ilosci_itemow_na_stronie[ktora_str]++; licznik_wierszy+=wiersze[k]+0.5;
                           }
                           else
                           {
                                    licznik_wierszy = wiersze[k]+0.5; ktora_str++; ilosci_itemow_na_stronie[ktora_str]++;
                           }
                  }
                  for(short k=0;k<ilosc_stron;++k)
                  {
                           kategoria[y][k]=new Przepis[ilosci_itemow_na_stronie[k]+1];
                           kategoria[y][k][ilosci_itemow_na_stronie[k]].ilosc_substratow = -1;
                  }

                  short ktory_item = 0;
                  for(short k=0; k<ilosc_stron; ++k)
                  {
                           for(h=0; h<ilosci_itemow_na_stronie[k]; ++h)
                           {
                                    kategoria[y][k][h].przenies(a[ktory_item++]);
                           }
                  }

                  for(h=0; a[h]!=NULL; ++h)
                  {
                           delete a[h];
                  }
                  delete a[h];
                  delete [] a;
                  delete [] ilosci_itemow_na_stronie;

         }
         delete [] wiersze;
}

Przepis* Crafting_recipes::daj_strone_z_kategorii(short strona, short kat)
{
         if(kat<ile_kategorii && kat>=0 && jest_taka_strona_z_tej_kategorii(strona, kat))
                  return kategoria[kat][strona];
         else
         {
                  std::cout<<"NIE MA TAKIEJ DAJ STRONE Z KATEGORII"<<strona<<" "<<kat; throw "D";
         }
}

bool Crafting_recipes::jest_taka_strona_z_tej_kategorii(short strona, short kat)
{
         for(short t=0; kategoria[t]!=NULL; ++t)
         {
                  if(t==kat)
                  {
                           for(short y=0; kategoria[t][y]!=NULL; ++y)
                           {
                                    if(y==strona) return true;
                           }
                           return false;
                  }
         }
         return false;
}

int* stworz_inty(short a, short ile) {int *g = new int[1]; ((short*)g)[0]=a;((short*)g)[1]=ile; return g;}
int* stworz_inty(short a, short ile, short b, short ilee) {int *g = new int[2];  ((short*)g)[0]=a;((short*)g)[1]=ile;  ((short*)g)[2]=b;((short*)g)[3]=ilee; return g;}
int* stworz_inty(short a, short ile, short b, short ilee, short c, short ileee) {int *g = new int[3]; ((short*)g)[0]=a;((short*)g)[1]=ile;  ((short*)g)[2]=b;((short*)g)[3]=ilee;  ((short*)g)[4]=c;((short*)g)[5]=ileee;  return g;}

short obj_craft(short nr, bool otoczenie)
{
         return (nr|=(otoczenie ? (1<<14) : 0))|(1<<15);
}

Przepis** Crafting_recipes::daj_liste_przepisow(short kategoria)///ostatni null
{///Przepis(int *subs, int *obj, int *kat, int *rez, int*umj, short sub, short ob, short ka, short re, short um);
         if(kategoria == 0)
         {
                  Przepis **t = new Przepis*[3];
                  t[2] = NULL;
                  t[0] = new Przepis(stworz_inty(4256, 1, 8003, 1),0,0,0,stworz_inty(4255, 1),2,0,0,0,1);
                  t[1] = new Przepis(stworz_inty(4255, 1),0,0,0,stworz_inty(4256, 1, 8003, 1),1,0,0,0,2);
                  return t;
         }
         else if(kategoria == 1)
         {
                  Przepis **t = new Przepis*[10];
                  t[0] = new Przepis(stworz_inty(8002, 3),0,0,0,stworz_inty(obj_craft(24, false), 1),1,0,0,0,1);
                  t[1] = new Przepis(stworz_inty(2010, 1),stworz_inty(-24, 1), 0,0,stworz_inty(2004, 1),1,1,0,0,1);
                  t[2] = new Przepis(stworz_inty(2009, 1),stworz_inty(-24, 1), 0,0,stworz_inty(2003, 1),1,1,0,0,1);
                  t[3] = new Przepis(stworz_inty(2011, 1),stworz_inty(-24, 1), stworz_inty(4010, 1),0,stworz_inty(2012, 1),1,1,1,0,1);
                  t[4] = new Przepis(stworz_inty(2011, 1),stworz_inty(-24, 1), stworz_inty(4011, 1),0,stworz_inty(2012, 1),1,1,1,0,1);
                  t[5] = new Przepis(stworz_inty(2013, 1),stworz_inty(-24, 1), stworz_inty(4011, 1),0,stworz_inty(2014, 1),1,1,1,0,1);
                  t[6] = new Przepis(stworz_inty(2011, 1, 8021, 1),stworz_inty(-24, 1), stworz_inty(4010, 1),0,stworz_inty(2012, 1),2,1,1,0,1);
                  t[7] = new Przepis(stworz_inty(2011, 1, 8021, 1),stworz_inty(-24, 1), stworz_inty(4011, 1),0,stworz_inty(2012, 1),2,1,1,0,1);
                  t[8] = new Przepis(stworz_inty(2013, 1, 8021, 2),stworz_inty(-24, 1), stworz_inty(4011, 1),0,stworz_inty(2014, 1),2,1,1,0,1);
                  t[9] = NULL;
                  return t;
         }
         else if(kategoria == 2)
         {
                  Przepis **t = new Przepis*[5];
                  t[0] = new Przepis(stworz_inty(4003, 1, 8023, 1),0,0,0,stworz_inty(4004, 1, 10001, 12),2,0,0,0,2);
                  t[1] = new Przepis(stworz_inty(2005, 1, 8023, 1),0,0,0,stworz_inty(8022, 1),2,0,0,0,1);
                  t[2] = new Przepis(stworz_inty(8022, 1),0,0,0,stworz_inty(2005, 1, 8023, 1),1,0,0,0,2);
                  t[3] = new Przepis(stworz_inty(2008, 1, 8020, 1),0,stworz_inty(8017, 1),0,stworz_inty(8019, 1),2,0,1,0,1);
                  t[4] = NULL;
                  return t;
         }
         else if(kategoria == 3)
         {
                  Przepis **t = new Przepis*[2];
                  t[0] = new Przepis(stworz_inty(2202, 1, 2203, 1),0,0,0,stworz_inty(2202, 1),2,0,0,0,1);
                  t[1] = NULL;
                  return t;
         }

         std::cout<<"niezdefiniowany kategoiria w daj_liste-przemdiotow"; throw "D";
}

rozmiary_tabeli Crafting_recipes::rozmiary(short strona, short kategoria)
{
        switch(kategoria)
        {
                case 0: return rozmiary_tabeli(4,1,1,1,3);
                case 1: return rozmiary_tabeli(5,1,1,1,2);
                case 2: return rozmiary_tabeli(5,1,1,1,2);

            default : break;
        }
        return rozmiary_tabeli(4,1,1,1,3);
         {std::cout<<"niezdefiniowany rozmiar w rozmiary::CraftingRecipes"; throw "D";}

}

Crafting_recipes::~Crafting_recipes()
{
         delete [] ile_w_kategorii;
         for(short k=0; kategoria[k]!=NULL; ++k)
         {
                  for(short h=0; kategoria[k][h]!=NULL; ++h)
                  {
                           delete [] kategoria[k][h];
                  }
                  delete [] kategoria[k];
         }
         delete [] kategoria;
}





bool Item::jest_ostrzem()
{
         if(this==NULL) return false;
         return czym_jest==4005 || czym_jest==4008 || czym_jest==4501 || czym_jest==4502;
}









