#include "swiat.h"
#include <windows.h>

Gracz :: Gracz():Objekt_zywy(10)
{
         wykonuje_ruch=false;
         wysokosc=1; if(postawa=='r') wysokosc=3; else if(postawa=='s') wysokosc=2;
}

void Gracz::ogrzej_sie_od_zrodel_ognia()
{
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px, py, pz);
         for(short f=x-1; f<=x+1; ++f)
         {
                  for(short g=y-1; g<=y+1; ++g)
                  {
                           if(Strefa::w_planszy(f, g))
                           {
                                    if(p->srodowisko[g][f]!=NULL)
                                    {
                                             if((p->srodowisko[g][f]->stan&1)==1)
                                                      dodaj_cieplo(10);
                                             if(p->srodowisko[g][f]->wierzch() && p->srodowisko[g][f]->wierzch()->czym_jest==24 && ((Ognisko*)p->srodowisko[g][f]->wierzch())->getPaliSie())
                                                      dodaj_cieplo(10);
                                    }
                                    if(p->otoczenie[g][f]!=NULL && (p->otoczenie[g][f]->stan&1)==1)
                                             dodaj_cieplo(10);
                           }
                  }
         }
         if(p->srodowisko[y][x]!=NULL && (p->srodowisko[y][x]->stan&1)==1)
                  dodaj_cieplo(40);
}

bool Gracz::zaktualizuj_po_rundzie()///jesli martwy to zwroc false
{
         if(*Objekt::args->godmode) return true;

         short pogoda = swiat->pogoda;
         if(pozostalo_snu>1) return true;

         ogrzej_sie_od_zrodel_ognia();

         if(woda_a>0) --woda_a; else {if(!odejmij_hp_z_powodu_niedozywienia()){return false;}else if(!odejmij_hp_z_powodu_niedozywienia()){return false;};}
         if(jedzenie_a>0) --jedzenie_a; else {if(!odejmij_hp_z_powodu_niedozywienia()){return false;}else if(!odejmij_hp_z_powodu_niedozywienia()){return false;};}
         if(energia_a>0) --energia_a;
         if(ocieplenie()<pogoda*10) {if(cieplo_a>0){--cieplo_a;} else if(!odejmij_hp_z_powodu_niedozywienia()){return false;}}else if(cieplo_a<cieplo_max)++cieplo_a;

         //oszolomieni.wywal_wszystkie_objekty();
         int ile_zal_kond=(woda_a>0)+p_ruchu/5;
         if(kondycja==0 && ile_zal_kond==0) ile_zal_kond+=1;
         if(kondycja+ile_zal_kond>18) kondycja=18;
         else kondycja+=ile_zal_kond;
         p_ruchu=10;

         if(pozostalo_snu==1) return true; ///zeby nie bylo oszukiwania podczas przetrzymywania
         if(jedzenie_a>150 && woda_a>150 && cieplo_a>150) {if(leczenie<40)++leczenie;} else if(leczenie>0) --leczenie;
         if(leczenie>=30)
         {
                  leczenie-=30;
                  if(klatka_a<klatka_max){++klatka_a;}
                  if(brzuch_a<brzuch_max){++brzuch_a;}
                  if(l_ramie_a<l_ramie_max){++l_ramie_a;}
                  if(p_ramie_a<p_ramie_max){++p_ramie_a;}
                  if(l_dlon_a<l_dlon_max){++l_dlon_a;}
                  if(p_dlon_a<p_dlon_max){++p_dlon_a;}
                  if(l_udo_a<l_udo_max){++l_udo_a;}
                  if(p_udo_a<p_udo_max){++p_udo_a;}
                  if(l_golen_a<l_golen_max){++l_golen_a;}
                  if(p_golen_a<p_golen_max){++p_golen_a;}
         }
         return true;
}

bool Gracz::gracz_widzi_do_konca_w_strone(char strona)
{
         Gracz*g=swiat->aktualny;Plansza*p=swiat->aktualna;
         switch(strona)
         {
                  case 'p':if(g->x+g->zasieg_wzroku()<21 || swiat->zwroc_taka_plansze(px+1, py, pz)==NULL){return false;}break;
                  case 'l':if(g->x-g->zasieg_wzroku()>-1 || swiat->zwroc_taka_plansze(px-1, py, pz)==NULL)return false;break;
                  case 'g':if(g->y-g->zasieg_wzroku()>-1 || swiat->zwroc_taka_plansze(px, py-1, pz)==NULL)return false;break;
                  case 'd':if(g->y+g->zasieg_wzroku()<13 || swiat->zwroc_taka_plansze(px, py+1, pz)==NULL)return false;break;
         }
         if(strona=='p' || strona=='l'){
                  int start=g->x;if(strona=='p') ++start; else --start;
                  while((strona=='p'&&start<21)||(strona=='l'&&start>-1)){
                           if(p->otoczenie[g->y][start]!=NULL && p->otoczenie[g->y][start]->wysokosc>=g->wysokosc) {return false;}
                           if(strona=='p') ++start; else --start;
                  }
                  if(strona=='p' && swiat->zwroc_taka_plansze(g->px+1,g->py,g->pz) && swiat->zwroc_taka_plansze(g->px+1,g->py,g->pz)->otoczenie[g->y][0]!=NULL&&swiat->zwroc_taka_plansze(g->px+1,g->py,g->pz)->otoczenie[g->y][0]->wysokosc>=g->wysokosc){return false;}
                  else if(strona=='l' && swiat->zwroc_taka_plansze(g->px-1,g->py,g->pz) && swiat->zwroc_taka_plansze(g->px-1,g->py,g->pz)->otoczenie[g->y][20]!=NULL&&swiat->zwroc_taka_plansze(g->px-1,g->py,g->pz)->otoczenie[g->y][20]->wysokosc>=g->wysokosc)return false;
                  }
         else if(strona=='g' || strona=='d'){
                  int start=g->y;if(strona=='d') ++start; else --start;
                  while((strona=='d'&&start<13)||(strona=='g'&&start>-1)){
                           if(p->otoczenie[start][g->x]!=NULL && p->otoczenie[start][g->x]->wysokosc>=g->wysokosc) return false;
                           if(strona=='d') ++start; else --start;
                  }
                  if(strona=='d' && swiat->zwroc_taka_plansze(g->px,g->py+1,g->pz) && swiat->zwroc_taka_plansze(g->px,g->py+1,g->pz)->otoczenie[0][g->x]!=NULL&&swiat->zwroc_taka_plansze(g->px,g->py+1,g->pz)->otoczenie[0][g->x]->wysokosc>=g->wysokosc)return false;
                  if(strona=='g' && swiat->zwroc_taka_plansze(g->px,g->py-1,g->pz) && swiat->zwroc_taka_plansze(g->px,g->py-1,g->pz)->otoczenie[12][g->x]!=NULL&&swiat->zwroc_taka_plansze(g->px,g->py-1,g->pz)->otoczenie[12][g->x]->wysokosc>=g->wysokosc)return false;
                  }
         return true;
}

int* Gracz::worn_items_graphics()
{
         al_lock_mutex(mutex_itemow_zalozonych);
         graph[0] = p_buty ? p_buty->get_co_to() : 0;
         graph[1] = p_plecak ? p_plecak->get_co_to() : 0;
         graph[2] = p_glowa ? p_glowa->get_co_to() : 0;
         graph[3] = p_spodnie ? p_spodnie->get_co_to() : 0;
         graph[4] = p_ramie ? p_ramie->get_co_to() : 0;
         graph[5] = p_rece ? p_rece->get_co_to() : 0;
         graph[6] = p_rekawice ? p_rekawice->get_co_to() : 0;
         graph[7] = p_korpus ? p_korpus->get_co_to() : 0;
         graph[8] = ilosc_kieszeni>'0' ? (p_kieszenl ? p_kieszenl->get_co_to() : 0) : 0;
         graph[9] = ilosc_kieszeni>'1' ? (p_kieszenp ? p_kieszenp->get_co_to() : 0) : 0;
         al_unlock_mutex(mutex_itemow_zalozonych);
         return graph;
}

void Gracz::zaktualizuj_przed_runda()
{
         al_lock_mutex(mutex_blokow); al_lock_mutex(mutex_unikow); al_lock_mutex(mutex_skupien);
         zablokowani.clear();
         uniknieci.clear();
         skupieni.clear();
         al_unlock_mutex(mutex_blokow); al_unlock_mutex(mutex_unikow); al_unlock_mutex(mutex_skupien);
}

std::vector<punkt> Gracz::blokowani()
{
         al_lock_mutex(mutex_blokow);
         std::vector<punkt> aaa(zablokowani.size());
         short int i=0;
         for(std::list<std::pair<Objekt*, short>>::iterator it = zablokowani.begin(); it!=zablokowani.end(); ++it)
         {
                  aaa[i++] = punkt((*it).first->x, (*it).first->y);
         }
         al_unlock_mutex(mutex_blokow);
         return aaa;
}

std::vector<punkt> Gracz::unikani()
{
         al_lock_mutex(mutex_unikow);
         std::vector<punkt> aaa(uniknieci.size());
         short int i=0;
         for(std::list<Objekt*>::iterator it = uniknieci.begin(); it!=uniknieci.end(); ++it)
         {
                  aaa[i++] = punkt((*it)->x, (*it)->y);
         }
         al_unlock_mutex(mutex_unikow);
         return aaa;
}

std::vector<punkt> Gracz::skupiani()
{
         al_lock_mutex(mutex_skupien);
         std::vector<punkt> aaa(skupieni.size());
         short int i=0;
         for(std::list<Objekt*>::iterator it = skupieni.begin(); it!=skupieni.end(); ++it)
         {
                  aaa[i++] = punkt((*it)->x, (*it)->y);
         }
         al_unlock_mutex(mutex_skupien);
         return aaa;
}

bool Gracz::jest_wsrod_blokow(Objekt *a)
{
         al_lock_mutex(mutex_blokow);
         for(std::list<std::pair<Objekt*, short>>::iterator it = zablokowani.begin(); it!=zablokowani.end(); ++it)
         {
                  if(a==(*it).first) {al_unlock_mutex(mutex_blokow); return true;}
         }
         al_unlock_mutex(mutex_blokow);
         return false;
}

bool Gracz::jest_wsrod_unikow(Objekt *a)
{
         al_lock_mutex(mutex_unikow);
         for(std::list<Objekt*>::iterator it = uniknieci.begin(); it!=uniknieci.end(); ++it)
         {
                  if(a==(*it)) {al_unlock_mutex(mutex_unikow); return true;}
         }
         al_unlock_mutex(mutex_unikow);
         return false;
}

bool Gracz::jest_wsrod_skupien(Objekt *a)
{
         al_lock_mutex(mutex_skupien);
         for(std::list<Objekt*>::iterator it = skupieni.begin(); it!=skupieni.end(); ++it)
         {
                  if(a==(*it)) {al_unlock_mutex(mutex_skupien); return true;}
         }
         al_unlock_mutex(mutex_skupien);
         return false;
}

void Gracz::dodaj_blok(Objekt *a, short blok)
{
         al_lock_mutex(mutex_blokow);
         zablokowani.push_back(std::pair<Objekt*, short>(a, blok));
         al_unlock_mutex(mutex_blokow);
}

void Gracz::dodaj_unik(Objekt *a)
{
         al_lock_mutex(mutex_unikow);
         uniknieci.push_back(a);
         al_unlock_mutex(mutex_unikow);
}

void Gracz::dodaj_skupienie(Objekt *a)
{
         al_lock_mutex(mutex_skupien);
         skupieni.push_back(a);
         al_unlock_mutex(mutex_skupien);
}

short Gracz::ile_bloku(Objekt *a)
{
         al_lock_mutex(mutex_blokow);
         for(std::list<std::pair<Objekt*, short>>::iterator it = zablokowani.begin(); it!=zablokowani.end(); ++it)
         {
                  if(a==(*it).first) {short h = (*it).second; al_unlock_mutex(mutex_blokow); return h;}
         }
         al_unlock_mutex(mutex_blokow);
         return 0;
}

int Gracz::zasieg_wzroku()
{
         int a=0;
         if(p_rece!=NULL && p_rece->czym_jest==8001) a+=8;
         else if(p_rece!=NULL && (p_rece->czym_jest==4255 ||  p_rece->czym_jest==4256)) a+=7;
         return 3+a;
}

int Gracz :: get_co_to()
{
         int a;
         if(otwiera) return 30;
         if(gwizdze) return 31;
         if(krzyczy) return 32;
         switch(postawa) {case 'r': a=10; break; case 's': a=16; break; case 'c': a=24; break;}
         switch(zwrot) {case 'd': a+=0;break; case 'g': a+=1;break; case 'l': a+=2;break; case 'p': a+=3;break;}
         return a;
}

void Gracz::uslysz_dzwiek(int dx,int dy,int rodzaj){}

void Gracz::uslysz_dzwiek(Plansza *a,int rodzaj){}

int najmniej_jeden(int a){if(a<1)return 1; else return a;}

int Gracz::uzycie_ubrania(Item **ubr, int obrazenia, char f)
{
         int a=0; if(f=='k') {a+=((Ubranie*)(p_glowa))->ochrona();if(p_glowa && ((p_glowa))->wykorzystaj()) { Item*a=((Ubranie*)(p_glowa));p_glowa=NULL;delete a;} }
         obrazenia=najmniej_jeden(obrazenia*(100-((Ubranie*)(*ubr))->ochrona()-a)/100);if(*ubr && ((Ubranie*)(*ubr))->wykorzystaj()){Item*a=((Ubranie*)(*ubr));*ubr=NULL;delete a;}return obrazenia;
}

short Gracz::stan_nog()
{
         bool A=l_udo_a<5,B=p_udo_a<5,C=l_golen_a<5,D=p_golen_a<5;
         if((A&&C&&(B||D))||(B&&D&&(A||C))) return 1; ///tylko crawl i za 7
         else if((A&&C)||(B&&D)) return 2; ///tylko crawl
         else if((A&&B)||(A&&D)||(C&&B)||(C&&D)) return 3;///bieganie za 5 sneak za 6 crawl za 7
         else if(A||B||C||D) return 4;///bieganie za 4
         return 0;
}

short Gracz::wart_zajecia()
{
         return 4;
}

int Gracz::obrazenia(Bron *b)
{
         float wsp = postawa == 'r' ? 1 : (postawa == 's' ? 0.8 : 0.6);
         return wsp * b->get_obrazenia()*(70+(b->dwureczna() ? l_ramie_a+p_ramie_a+p_dlon_a+l_dlon_a : 15+(l_ramie_a+l_dlon_a>p_dlon_a+p_ramie_a ? l_ramie_a+l_dlon_a : p_dlon_a+p_ramie_a)))/100;
}

int Gracz::szansa(Bron *b)
{
         return b->get_szansa()*(70+(b->dwureczna() ? l_ramie_a+p_ramie_a+p_dlon_a+l_dlon_a : 15+(l_ramie_a+l_dlon_a>p_dlon_a+p_ramie_a ? l_ramie_a+l_dlon_a : p_dlon_a+p_ramie_a)))/100;
}

what_happened Gracz::zostan_uderzony(int obrazenia, int kto, int ekstra, short wsp_zajecia)
{
         if(*Objekt::args->godmode) return success;
         if(this==NULL) {std::cout<<"NULL na Gracz::zostan_uderzony"; return dead;}
         p_ruchu -= wsp_zajecia; if(p_ruchu<3) p_ruchu=3;
         int aaa=losuj(1,10); bool br=false;
         if(kto==-3) aaa = losuj(9, 10);
         else if(kto==-4) aaa = losuj(7, 10);

         while(1)
         {
                  switch(aaa)
                  {
                           case 1:if(klatka_a>0){obrazenia=uzycie_ubrania(&p_korpus, obrazenia,'k');if(klatka_a-obrazenia<=0) klatka_a=0;else klatka_a-=obrazenia; br=true;break;}
                           case 2:if(brzuch_a>0){obrazenia=uzycie_ubrania(&p_korpus, obrazenia);if(brzuch_a-obrazenia<=0) brzuch_a=0;else brzuch_a-=obrazenia; br=true;break;}
                           case 3:if(l_ramie_a>0){obrazenia=uzycie_ubrania(&p_korpus, obrazenia);if(l_ramie_a-obrazenia<=0) l_ramie_a=0;else l_ramie_a-=obrazenia; br=true;break;}
                           case 4:if(p_ramie_a>0){obrazenia=uzycie_ubrania(&p_korpus, obrazenia);if(p_ramie_a-obrazenia<=0) p_ramie_a=0;else p_ramie_a-=obrazenia; br=true;break;}
                           case 5:if(l_dlon_a>0){obrazenia=uzycie_ubrania(&p_rekawice, obrazenia);if(l_dlon_a-obrazenia<=0) l_dlon_a=0;else l_dlon_a-=obrazenia; br=true;break;}
                           case 6:if(p_dlon_a>0){obrazenia=uzycie_ubrania(&p_rekawice, obrazenia);if(p_dlon_a-obrazenia<=0) p_dlon_a=0;else p_dlon_a-=obrazenia; br=true;break;}
                           case 7:if(l_udo_a>0){obrazenia=uzycie_ubrania(&p_spodnie, obrazenia);if(l_udo_a-obrazenia<=0) l_udo_a=0;else l_udo_a-=obrazenia; br=true;break;}
                           case 8:if(p_udo_a>0){obrazenia=uzycie_ubrania(&p_spodnie, obrazenia);if(p_udo_a-obrazenia<=0) p_udo_a=0;else p_udo_a-=obrazenia; br=true;break;}
                           case 9:if(l_golen_a>0){obrazenia=uzycie_ubrania(&p_buty, obrazenia);if(l_golen_a-obrazenia<=0) l_golen_a=0;else l_golen_a-=obrazenia; br=true;break;}
                           case 10:if(p_golen_a>0){obrazenia=uzycie_ubrania(&p_buty, obrazenia);if(p_golen_a-obrazenia<=0) p_golen_a=0;else p_golen_a-=obrazenia; br=true;break;}
                  }
                  if(br)break; aaa=1;br=true;
         }
         animacja_damage(obrazenia);
         if(czy_zyje())
         {
                  if(stan_nog()==1 || stan_nog()==2) postawa='c';
         }
         else return dead;
         return success;
}

bool Gracz::rusz_sie()
{
         throw "gracz jest obiektem !?";
}

void Gracz::patrz(){}

void Gracz :: zapisz(std::ofstream *ofs)
{

}

void Gracz::dzwiek_przesuniecia(int xx, int yy)
{
         if(postawa=='r')wydaj_dzwiek(false, 2, xx,yy,10);
}

void Gracz::strzel(Objekt*a)
{
         if(mozna_strzelic(a))
         {
                  animacja_strzalu(x+args->X_kratka/2, y+args->Y_kratka/2, a->x+args->X_kratka/2, a->y+args->Y_kratka/2, 1);
         }
}

bool Gracz::odejmij_hp_z_powodu_niedozywienia()
{
         if(klatka_a<brzuch_a) --klatka_a; else --brzuch_a;
         return czy_zyje();
}

bool Gracz::czy_zyje()
{
         if(klatka_a<=0 || brzuch_a<=0)
         {
                  args->otwarte_menu_anatomii=true;Sleep(3000);args->otwarte_menu_anatomii=true;

                  Plansza*p=swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
                  przestan_byc_ofiara(1);
                  if(pozostalo_snu<=0)p->otoczenie[y][x]=NULL; ///czy on wgl jest na planszy
                  Srodowisko::dodaj_objekt((new Zwloki(czym_jest,0,x,y,px,py,pz)),x,y,p);
                  p->zaktualizuj_widoki(x,y,x,y);

                  if(p->ziemia[y][x]==NULL) p->ziemia[y][x]=new Kontener<Item>();
                  Kontener<Item>*poz=new Kontener<Item>;
                  poz->dodaj_obiekt(p_rece);poz->dodaj_obiekt(p_korpus);poz->dodaj_obiekt(p_spodnie);poz->dodaj_obiekt(p_buty);poz->dodaj_obiekt(p_rekawice);
                  poz->dodaj_obiekt(p_kieszenp);poz->dodaj_obiekt(p_kieszenl);poz->dodaj_obiekt(p_ramie);poz->dodaj_obiekt(p_glowa);poz->dodaj_obiekt(p_plecak);
                  p->ziemia[y][x]->dodaj_obiekty(poz); poz->wywal_wszystkie_objekty(); delete poz;
                  p_glowa=NULL;p_korpus=NULL;p_spodnie=NULL;p_buty=NULL;p_ramie=NULL;p_plecak=NULL;p_rece=NULL;p_rekawice=NULL;p_kieszenl=NULL;p_kieszenp=NULL;
                  if(p->ziemia[y][x]->ilosc==0) {Kontener<Item>* a=p->ziemia[y][x];p->ziemia[y][x]=NULL; delete a;}

                  if(swiat->aktualny==this) swiat->aktualny=NULL;
                  swiat->gracz->usun_objekt(this);

                  int r=swiat->promien_obszaru_zywego;

                  for(int i=px-r;i<=px+r;++i)
                  {
                           for(int j=py-r-1;j<=py+r+1;++j)
                           {
                                    if(i>-1 && j>-1 && i<swiat->w_x && j<swiat->w_y)
                                    {
                                             if(swiat->zwroc_taka_plansze(i,j,pz) && !swiat->w_zasiegu_gracza(i,j,pz))
                                             {
                                                      swiat->stworz_strefe(i,j,pz);
                                             }
                                    }
                           }
                  }
                  smierc();
                  return false;
         }
         return true;
}

bool Gracz::wstan_ze_snu()
{
         pozostalo_snu = 0;

         ///najpierw tam gdzie stal
         ///potem prostopadle
         ///potem ukosy
         ///potem lez dalej
         px = gdzie_spi->px; pz = gdzie_spi->pz; py = gdzie_spi->py;
         Plansza *pl = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         if(pl->otoczenie[y][x]==NULL && zaraz_obok(x,y,gdzie_spi->x,gdzie_spi->y))
         {
                  pl->otoczenie[y][x] = this;
         }
         else if(Strefa::w_planszy(gdzie_spi->x+1, gdzie_spi->y) && pl->otoczenie[gdzie_spi->y][gdzie_spi->x+1]==NULL)
         {x = gdzie_spi->x+1; pl->otoczenie[y][x] = this;}
         else if(Strefa::w_planszy(gdzie_spi->x-1, gdzie_spi->y) && pl->otoczenie[gdzie_spi->y][gdzie_spi->x-1]==NULL)
         {x = gdzie_spi->x-1; pl->otoczenie[y][x] = this;}
         else if(Strefa::w_planszy(gdzie_spi->x, gdzie_spi->y+1) && pl->otoczenie[gdzie_spi->y+1][gdzie_spi->x]==NULL)
         {x = gdzie_spi->y+1; pl->otoczenie[y][x] = this;}
         else if(Strefa::w_planszy(gdzie_spi->x, gdzie_spi->y-1) && pl->otoczenie[gdzie_spi->y-1][gdzie_spi->x]==NULL)
         {x = gdzie_spi->y-1; pl->otoczenie[y][x] = this;}

         else if(Strefa::w_planszy(gdzie_spi->x-1, gdzie_spi->y-1) && pl->otoczenie[gdzie_spi->y-1][gdzie_spi->x-1]==NULL)
         {x = gdzie_spi->x-1; y = gdzie_spi->y-1; pl->otoczenie[y][x] = this;}
         else if(Strefa::w_planszy(gdzie_spi->x+1, gdzie_spi->y+1) && pl->otoczenie[gdzie_spi->y+1][gdzie_spi->x+1]==NULL)
         {x = gdzie_spi->x+1; y = gdzie_spi->y+1; pl->otoczenie[y][x] = this;}
         else if(Strefa::w_planszy(gdzie_spi->x-1, gdzie_spi->y+1) && pl->otoczenie[gdzie_spi->y+1][gdzie_spi->x-1]==NULL)
         {x = gdzie_spi->x-1; y = gdzie_spi->y+1; pl->otoczenie[y][x] = this;}
         else if(Strefa::w_planszy(gdzie_spi->x+1, gdzie_spi->y-1) && pl->otoczenie[gdzie_spi->y-1][gdzie_spi->x+1]==NULL)
         {x = gdzie_spi->x+1; y = gdzie_spi->y-1; pl->otoczenie[y][x] = this;}

         else
         {
                  pozostalo_snu = 1; return false;
         }
         ukryty = false;
         if(gdzie_spi->czym_jest) ((Szalas*)gdzie_spi)->kto_spi = NULL;
         pl->ma_gracza = true;
         wyjdz_animacja(gdzie_spi->x, gdzie_spi->y);
         gdzie_spi = NULL;
         return true;
}

Gracz::~Gracz()
{
         al_destroy_mutex(mutex_blokow);
         al_destroy_mutex(mutex_unikow);
         al_destroy_mutex(mutex_skupien);
}

int Gracz::kamuflaz()
{
         return ((Ubranie*)p_glowa)->kamuflaz()+((Ubranie*)p_korpus)->kamuflaz()+((Ubranie*)p_spodnie)->kamuflaz()
         +((Ubranie*)p_buty)->kamuflaz()+((Ubranie*)p_rekawice)->kamuflaz()+((Plecak*)p_plecak)->kamuflaz();
}

int Gracz::ocieplenie()
{
         return ((Ubranie*)p_glowa)->cieplo()+((Ubranie*)p_korpus)->cieplo()+((Ubranie*)p_spodnie)->cieplo()
         +((Ubranie*)p_buty)->cieplo()+((Ubranie*)p_rekawice)->cieplo();
}

void Gracz::dostan_item(Item*a)
{
         if(a==NULL) return;
         if(p_rece==NULL) {p_rece=a; return;}
         Przedmiot *b=new Przedmiot(a);
         if(a->mozna_do_plecaka() && p_plecak!=NULL && ((Plecak*)p_plecak)->s->wloz_przedmiot(b)) return; else {delete b;}
         swiat->zwroc_taka_plansze_TYLKO(px,py,pz)->rzuc_na_ziemie(x,y,a);
}

short Gracz::latwopalnosc() {return 0;}

bool Gracz::posiada_przedmiot(int jaki, short w_ilosci, bool patrz_na_ziemie)
{
         short ilosc = 0;
         if(p_rece!=NULL && p_rece->czym_jest==jaki) ilosc++;
         if(jaki>5000 && jaki<7500)
         {
                  if(p_glowa!=NULL && p_glowa->czym_jest==jaki) ilosc++;
                  if(p_korpus!=NULL && p_korpus->czym_jest==jaki) ilosc++;
                  if(p_spodnie!=NULL && p_spodnie->czym_jest==jaki) ilosc++;
                  if(p_buty!=NULL && p_buty->czym_jest==jaki) ilosc++;
                  if(p_rekawice!=NULL && p_rekawice->czym_jest==jaki) ilosc++;
         }
         if(p_ramie!=NULL && p_ramie->czym_jest==jaki) ilosc++;
         if(p_kieszenl!=NULL && p_kieszenl->czym_jest==jaki) ilosc++;
         if(p_kieszenp!=NULL && p_kieszenp->czym_jest==jaki) ilosc++;

         if(p_plecak!=NULL)
         {
                  //if(p_plecak->czym_jest==jaki) ilosc++;
                  //else
                  {
                           Skrzynka *s = ((Plecak*)p_plecak)->s;
                           for(short i=0; i<s->lista_itemow()->ilosc; ++i)
                           {
                                    if(s->lista_itemow()->obiekt[i]->czym_jest == jaki)
                                             ilosc++;
                           }
                  }
         }
         if(patrz_na_ziemie)
         {
                  if(otwarta!=NULL)
                  {
                           for(short i=0; i<otwarta->lista_itemow()->ilosc; ++i)
                                    if(otwarta->lista_itemow()->obiekt[i]->czym_jest == jaki)
                                             ilosc++;
                  }
         }
         return ilosc >= w_ilosci;
}

Item** Gracz::odbierz_przedmiot(int jaki, short w_ilosci, bool z_ziemii_tez)
{
         if(!posiada_przedmiot(jaki, w_ilosci, z_ziemii_tez)) return NULL;

         Item **tab = new Item*[w_ilosci+1];
         tab[w_ilosci] = NULL;
         short licznik = 0;

         if(p_rece!=NULL && p_rece->czym_jest==jaki) {tab[licznik++] = p_rece; p_rece=NULL; if(licznik==w_ilosci) return tab;}
         if(jaki>5000 && jaki<7500)
         {
                  if(p_glowa!=NULL && p_glowa->czym_jest==jaki) {tab[licznik++] = p_rece; p_rece=NULL; if(licznik==w_ilosci) return tab;}
                  if(p_korpus!=NULL && p_korpus->czym_jest==jaki) {tab[licznik++] = p_korpus; p_korpus=NULL; if(licznik==w_ilosci) return tab;}
                  if(p_spodnie!=NULL && p_spodnie->czym_jest==jaki) {tab[licznik++] = p_spodnie; p_spodnie=NULL; if(licznik==w_ilosci) return tab;}
                  if(p_buty!=NULL && p_buty->czym_jest==jaki) {tab[licznik++] = p_buty; p_buty=NULL; if(licznik==w_ilosci) return tab;}
                  if(p_rekawice!=NULL && p_rekawice->czym_jest==jaki) {tab[licznik++] = p_rekawice; p_rekawice=NULL; if(licznik==w_ilosci) return tab;}
         }
         if(p_ramie!=NULL && p_ramie->czym_jest==jaki) {tab[licznik++] = p_ramie; p_ramie=NULL; if(licznik==w_ilosci) return tab;}
         if(p_kieszenl!=NULL && p_kieszenl->czym_jest==jaki) {tab[licznik++] = p_kieszenl; p_kieszenl=NULL; if(licznik==w_ilosci) return tab;}
         if(p_kieszenp!=NULL && p_kieszenp->czym_jest==jaki) {tab[licznik++] = p_kieszenp; p_kieszenp=NULL; if(licznik==w_ilosci) return tab;}

         if(p_plecak!=NULL)
         {
                  if(p_plecak->czym_jest==jaki) {tab[licznik++] = p_plecak; p_plecak=NULL; if(licznik==w_ilosci) return tab;}
                  else
                  {
                           Skrzynka *s = ((Plecak*)p_plecak)->s;
                           for(short i=0; i<s->lista_itemow()->ilosc; ++i)
                           {
                                    if(s->lista_itemow()->obiekt[i]->czym_jest == jaki)
                                    {
                                             tab[licznik++] = s->lista_itemow()->obiekt[i];
                                             Przedmiot *aaa = s->zwroc_przedmiot(s->lista_itemow()->obiekt[i]);
                                             s->wyjmij_przedmiot(aaa); delete aaa;
                                             if(licznik==w_ilosci) return tab;
                                    }
                           }
                  }
         }
         if(z_ziemii_tez)
         {
                  if(otwarta!=NULL)
                  {
                           for(short i=0; i<otwarta->lista_itemow()->ilosc; ++i)
                                    if(otwarta->lista_itemow()->obiekt[i]->czym_jest == jaki)
                                    {
                                             tab[licznik++] = otwarta->lista_itemow()->obiekt[i];
                                             Przedmiot *aaa = otwarta->zwroc_przedmiot(otwarta->lista_itemow()->obiekt[i]);
                                             otwarta->wyjmij_przedmiot(aaa); delete aaa;
                                             if(licznik==w_ilosci) return tab;
                                    }
                  }
         }
         return tab;
}

bool Gracz::ma_umiejetnosc(short jaka)
{
         return false;
}

bool Gracz::jest_obok_objektu(short jakiego)
{
         short t = jakiego;
         if(jakiego<0)
         {
                  switch(jakiego)
                  {
                           default: jakiego*=-1;
                  }
         }
         Plansza *p = swiat->zwroc_taka_plansze_TYLKO(px,py,pz);
         for(short i=x-1; i<=x+1; ++i)
         {
                  for(short j=y-1; j<=y+1; ++j)
                  {
                           if(Strefa::w_planszy(i, j))
                           {
                                    if(p->otoczenie[j][i]!=NULL && p->otoczenie[j][i]->czym_jest==jakiego)
                                    {
                                             switch(t)
                                             {
                                                      default: return true;
                                             }
                                    }
                                    else if(p->srodowisko[j][i]!=NULL && p->srodowisko[j][i]->wierzch()!=NULL && p->srodowisko[j][i]->wierzch()->czym_jest==jakiego)
                                    {
                                             switch(t)
                                             {
                                                      case -24:
                                                      {
                                                               if(((Ognisko*)p->srodowisko[j][i]->wierzch())->getPaliSie())
                                                                        return true;
                                                               else break;
                                                      }
                                                      default: return true;
                                             }
                                    }
                           }
                  }
         }
         return false;
}

void Gracz::wykorzystaj_item(short jaki)
{

}









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



