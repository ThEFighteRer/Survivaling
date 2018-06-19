#include "structy.h"





specyfikacja_menu::specyfikacja_menu(specyfikacja_menu **item,int ilosc,int ktore)
{
         this->ilosc=ilosc; this->ktore=ktore; this->item=item;
}

specyfikacja_menu::specyfikacja_menu()
{

}

specyfikacja_menu::~ specyfikacja_menu()
{
         for(int i=0; i<ilosc; ++i) delete item[i];
         delete [] item;
         item=NULL;
}







void Przepis::init(int *subs, int *obj, int *kat, int*umj, int *rez, short sub, short ob, short ka, short um, short re)
{
         substraty = subs; objekty_w_poblizu = obj; katalizatory = kat; rezultaty = rez; skills = umj;
         ilosc_substratow = sub; ilosc_objektow_w_poblizu = ob; ilosc_katalizatorow = ka; ilosc_rezultatow = re; ilosc_umiejetnosci = um;
}

Przepis::Przepis()
{

}

Przepis::Przepis(int *subs, int *obj, int *kat, int*umj, int *rez, short sub, short ob, short ka, short um, short re)
{
         init(subs, obj, kat, umj, rez, sub, ob, ka, um, re);
}

Przepis::Przepis(short k, int *subs, int *obj, int *kat, int*umj, int *rez, short sub, short ob, short ka, short um, short re)
{
         koszt = k; init(subs, obj, kat, umj, rez, sub, ob, ka, um, re);
}

void Przepis::przenies(Przepis *a)
{
         init(a->substraty, a->objekty_w_poblizu, a->katalizatory, a->skills, a->rezultaty, a->ilosc_substratow, a->ilosc_objektow_w_poblizu, a->ilosc_katalizatorow, a->ilosc_umiejetnosci, a->ilosc_rezultatow);
         koszt = a->koszt;
         a->ilosc_substratow = 0, a->ilosc_objektow_w_poblizu = 0, a->ilosc_katalizatorow = 0, a->ilosc_rezultatow = 0; a->ilosc_umiejetnosci;
         a->substraty = NULL; a->objekty_w_poblizu = NULL; a->katalizatory = NULL; a->rezultaty = NULL; a->skills = NULL;
}

Przepis::~Przepis()
{
         ///delete [] substraty; delete [] objekty_w_poblizu; delete [] katalizatory; delete [] rezultaty; delete [] skills;
         ///nie mozemy ich usuwac bo w pewnej chwili sa tworzone w tablicy w rzedzie i wtedy wlasnie rozwalaja nam nasze wskazniki
         ///a usunac musimy je i tak na sam koniec dzialania programu, wiec nie bedziemy kombinowac, niech jadro wyzwoli co ma wolne byc ;)
}

short Przepis::potrzebne_wiersze(rozmiary_tabeli rozmiary)
{
         short a=ilosc_substratow,b=ilosc_objektow_w_poblizu,c=ilosc_katalizatorow,d = ilosc_umiejetnosci, e=ilosc_rezultatow;
         short wiersze;
         if((a!=0 && rozmiary.I==0)||(b!=0 && rozmiary.II==0)||(c!=0 && rozmiary.III==0)||(d!=0 && rozmiary.IV==0)||(e!=0 && rozmiary.V==0)) {std::cout<<"nie ma kolumny dla rekordu Przepis::potrzebne wiersze"; throw "G";}
         for(wiersze = 0;a>0 || b>0 || c>0 || d>0 || e>0; wiersze++)
         {
                  a-=rozmiary.I; b-=rozmiary.II; c-=rozmiary.III; d-=rozmiary.IV; e-=rozmiary.V;
         }
         return wiersze;
}

short Przepis::potrzebne_wiersze_na_atrybut(rozmiary_tabeli rozmiary, short ktora)
{
         short atr = 0, wiersze = 0, a;
         switch(ktora)
         {
                  case 0: atr=ilosc_substratow; a=rozmiary.I; break;
                  case 1: atr=ilosc_objektow_w_poblizu; a=rozmiary.II; break;
                  case 2: atr=ilosc_katalizatorow; a=rozmiary.III; break;
                  case 3: atr=ilosc_umiejetnosci; a=rozmiary.IV; break;
                  case 4: atr=ilosc_rezultatow; a=rozmiary.V; break;
         }
         if(atr!=0 && a==0) {std::cout<<"nie ma kolumny dla rekordu Przepis::potrzebne_wiersze_na_atrybut"; throw "G";}
         for(wiersze=0; atr>0; ++wiersze)
         {
                  atr-=a;
         }
         return wiersze;
}

bool f=false;
int losuj(int min, int max)
{
         //if(b==NULL) b=new losowania();
         //b->last=(b->a*b->last+b->c)%b->m;
         //return abs((b->last))%(max-min+1)+min;
         //return randomInteger(min, max);
         if(f==false) {srand(time(NULL));f=true;}
         return rand()%(max-min+1)+min;
}














