// Tester curenja memorije V1.2
// (C) Zeljko Juric, 2010
// Prirodno-matematicki fakultet, odsjek za matematiku
// Sarajevo, Bosna i Hercegovina

// Prije koristenja, obavezno procitati upute za upotrebu

#ifndef TEST_CURENJA_H
#define TEST_CURENJA_H

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <exception>
#include <new>

#define UKLJUCI_OBAVJESTAVANJE  __Tester__::treba_obavjestavati = true
#define ISKLJUCI_OBAVJESTAVANJE __Tester__::treba_obavjestavati = false
 
namespace __Tester__ {
  typedef unsigned long ULong; 
  struct Info {
    void *adresa;
    long linija;
    std::size_t velicina;
    bool da_li_je_niz;
    Info *veza;
  } *mapa_alokacija(0);
  int broj_alokacija(0), broj_dealokacija(0);
  long sumarno_alocirano(0), sumarno_dealocirano(0), trenutno_alocirano(0), 
    max_alocirano(0);
  bool treba_obavjestavati(false);
  void *Alokacija(long linija, std::size_t velicina, bool da_li_je_niz) {
    void *adresa(std::malloc(velicina));
    if(!adresa) throw std::bad_alloc();
    if(linija != -1) {
      broj_alokacija++;
      sumarno_alocirano += velicina; trenutno_alocirano += velicina;
      if(trenutno_alocirano > max_alocirano) max_alocirano = trenutno_alocirano;
      if(treba_obavjestavati) {
        if(linija == -2) std::printf(">>> Interno se alocira ");
        else std::printf(">>> U %ld. liniji programa alocira se ", linija);
        std::printf("%lu bajta na adresi %p\n", (ULong)velicina, adresa);
      }
    }
    Info info = {adresa, linija, velicina, da_li_je_niz, mapa_alokacija};
    if(!(mapa_alokacija = (Info*)std::malloc(sizeof(Info)))) 
       throw std::bad_alloc(); 
    *mapa_alokacija = info;
    return adresa;
  }
  void Dealokacija(void *pok, bool da_li_je_niz) {
    Info *tekuci(mapa_alokacija), *prethodni(0);
    for(; tekuci && tekuci->adresa != pok; tekuci = tekuci->veza)
      prethodni = tekuci;           
    if(tekuci) {
      if(tekuci->linija != -1) {
        std::size_t velicina(tekuci->velicina);
        broj_dealokacija++;
        sumarno_dealocirano += velicina; trenutno_alocirano -= velicina;
        if(treba_obavjestavati) {
          std::printf(">>> Oslobadja se %lu bajta na adresi %p\n", 
            (ULong)velicina, pok);
        }
        if(da_li_je_niz != tekuci->da_li_je_niz)
          std::printf("*** GRESKA: Oslobadjanje na adresi %p %s trebalo "
            "izvesti sa delete[]!\n", pok, da_li_je_niz ? "nije" : "je");
      }
      if(prethodni) prethodni->veza = tekuci->veza;                   
      else mapa_alokacija = tekuci->veza;
      std::free(tekuci); std::free(pok);     
    }
    else if(pok) {
      const std::size_t pomak(sizeof(std::size_t)); 
      void *pok1((char*)pok + (da_li_je_niz ? pomak : -pomak));
      for(tekuci = mapa_alokacija; tekuci && tekuci->adresa != pok1; 
        tekuci = tekuci->veza);
      if(tekuci)
        std::printf("*** GRESKA: Oslobadjanje na adresi %p %s trebalo "
          "izvesti sa delete[]!\n", pok1, da_li_je_niz ? "nije" : "je");
      else              
        printf("*** GRESKA: Pokusavate osloboditi vec oslobodjen prostor "
          "na adresi %p!\n", pok);       
    }  
  }
  void Terminator();
  struct Reporter {
    void (*stari_terminator)();
    Reporter() : stari_terminator(std::set_terminate(Terminator)) {}
    ~Reporter() {
      std::printf("\n\n+--------------------+\n| ZAVRSNI IZVJESTAJ: |\n"
        "+--------------------+\n\nUkupan broj alokacija: %d\nUkupan broj "
        "dealokacija: %d\nUkupna kolicina izvrsenih alokacija u bajtima: %ld\n"
        "Ukupna kolicina izvrsenih dealokacija u bajtima: %ld\nMaksimalno "
        "zauzece memorije tokom rada programa u bajtima: %ld\nZauzece memorije "
        "po zavrsetku programa u bajtima: %ld\n", broj_alokacija,
        broj_dealokacija, sumarno_alocirano, sumarno_dealocirano, 
        max_alocirano, trenutno_alocirano); 
      if(mapa_alokacija) {
        std::printf("\n\nNE VALJA! IMATE CURENJA MEMORIJE NA SLJEDECIM "
          "MJESTIMA:\n");
        for(Info *tekuci = mapa_alokacija; tekuci; tekuci = tekuci->veza)
          if(tekuci->linija == -2)
            std::printf(" - Adresa %p, %lu bajta, interno alocirano\n",
              tekuci->adresa, (ULong)tekuci->velicina);
          else
            std::printf(" - Adresa %p, %lu bajta, alocirano u %ld. liniji"
              " programa\n", tekuci->adresa, (ULong)tekuci->velicina, 
              tekuci->linija);
        std::printf("\n");
      }
      else
        std::printf("\n\nBRAVO! NEMA NIGDJE CURENJA MEMORIJE\n\n");
      std::system("PAUSE");
    }  
  } reporter;
  void Terminator() {
    reporter.Reporter::~Reporter();
    reporter.stari_terminator();
  }   
}

void *operator new(std::size_t velicina, long linija) throw(std::bad_alloc) {
  return __Tester__::Alokacija(linija, velicina, false);
}

void* operator new[](std::size_t velicina, long linija) throw(std::bad_alloc) {
  return __Tester__::Alokacija(linija, velicina, true);
}

void *operator new(std::size_t velicina) throw(std::bad_alloc) {
  return __Tester__::Alokacija(-2, velicina, false); 
}                                                    // Hvata interne alokacije

void* operator new[](std::size_t velicina) throw(std::bad_alloc) {
  return __Tester__::Alokacija(-2, velicina, true);
}

void operator delete(void *pok) throw() {
  __Tester__::Dealokacija(pok, false);
}
 
void operator delete[](void* pok) throw() {
  __Tester__::Dealokacija(pok, true);   
}

void operator delete(void *pok, long) throw() {    // placement delete!!!
  __Tester__::Dealokacija(pok, false);
}
 
void operator delete[](void* pok, long) throw() {
  __Tester__::Dealokacija(pok, true);   
}

#define new new(__LINE__)
 
#endif
