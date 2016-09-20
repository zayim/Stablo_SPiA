#include "Stablo.h"
#include <iostream>
using namespace std;
stablo::stablo()
{
    korijen=najveci=najmanji=0;
}
void stablo::unisti(cvor* tekuci)
{
    if (tekuci)
    {
        unisti(tekuci->lijevi);
        unisti(tekuci->desni);
        delete tekuci;
    }
}
stablo::~stablo()
{
    unisti(korijen);
}
void stablo::umetni(int broj)
{
    // umetanje u prazno stablo
    if (!korijen)
        korijen=najveci=najmanji=new cvor(broj,0,0,0,0,0);

    else
    {
        // umetanje u stablo
        cvor *tekuci=korijen,*dijete;
        cvor *zadnjeLijevo=0, *zadnjeDesno=0;

        if (korijen->element >= broj)
        {
            dijete=korijen->lijevi;
            zadnjeLijevo=korijen;
        }
        else
        {
            dijete=korijen->desni;
            zadnjeDesno=korijen;
        }

        while (dijete)
        {
            tekuci=dijete;
            if (tekuci->element >= broj)
            {
                dijete=tekuci->lijevi;
                zadnjeLijevo=tekuci;
            }
            else
            {
                dijete=tekuci->desni;
                zadnjeDesno=tekuci;
            }
        }

        cvor *pomocni=new cvor(broj,tekuci,0,0,zadnjeDesno,zadnjeLijevo);
        if (tekuci->element >= broj) tekuci->lijevi=pomocni;
        else tekuci->desni=pomocni;

        //updateovanje liste
        // ako ima samo jedan element
        if (najveci==najmanji)
        {
            if (broj > najveci->element)
            {
                najveci=pomocni;
                najmanji->sljedeci=najveci;
            }
            else
            {
                najmanji=pomocni;
                najveci->prethodni=najmanji;
            }
        }
        // ako ima vise od jednog elementa
        else
        {
            if (broj > najveci->element)
                najveci=pomocni;
            if (broj < najmanji->element)
                najmanji=pomocni;

            if (zadnjeDesno) zadnjeDesno->sljedeci=pomocni;
            if (zadnjeLijevo) zadnjeLijevo->prethodni=pomocni;
        }
    }

}

void stablo::izbrisi (cvor *zaBrisanje)
{
    if (!zaBrisanje) return;
    bool korijen_=true;
    cvor *roditelj=0;
    bool lijevoDijete=false;

    if (zaBrisanje!=korijen)
    {
        roditelj=zaBrisanje->roditelj;
        lijevoDijete = roditelj->lijevi==zaBrisanje;
        korijen_=false;
    }

    // ako nema djece
    if (!zaBrisanje->lijevi && !zaBrisanje->desni)
    {
        if (korijen_)
        {
            delete zaBrisanje;
            korijen=najveci=najmanji=0;
            return;
        }
        else
        {
            if (lijevoDijete) roditelj->lijevi=0;
            else roditelj->desni=0;
        }
    }
    // ako ima samo lijevo dijete
    else if (!zaBrisanje->desni)
    {
        if (korijen_)
        {
            korijen=zaBrisanje->lijevi;
            korijen->roditelj=0;

        }
        else
        {
            if (lijevoDijete) roditelj->lijevi=zaBrisanje->lijevi;
            else roditelj->desni=zaBrisanje->lijevi;
            zaBrisanje->lijevi->roditelj=roditelj;
        }

    }
    // ako ima samo desno dijete
    else if (!zaBrisanje->lijevi)
    {
        if (korijen_)
        {
            korijen=zaBrisanje->desni;
            korijen->roditelj=0;
        }
        else
        {
            if (lijevoDijete) roditelj->lijevi=zaBrisanje->desni;
            else roditelj->desni=zaBrisanje->desni;
            zaBrisanje->desni->roditelj=roditelj;
        }
    }
    // ako ima i lijevo i desno dijete
    else
    {
        cvor *najdesniji=zaBrisanje->lijevi, *pomocni=najdesniji->desni;

        while (pomocni)
        {
            najdesniji=pomocni;
            pomocni=pomocni->desni;
        }

        if (korijen_)
        {
            najdesniji->roditelj->desni=najdesniji->lijevi;
            najdesniji->lijevi->roditelj=najdesniji->roditelj;

            najdesniji->roditelj=0;
            najdesniji->lijevi=zaBrisanje->lijevi;
            najdesniji->desni=zaBrisanje->desni;

            korijen=najdesniji;
        }
        else
        {
            if (lijevoDijete) roditelj->lijevi=najdesniji;
            else roditelj->desni=najdesniji;

            najdesniji->roditelj->desni=najdesniji->lijevi;
            if (najdesniji->lijevi) najdesniji->lijevi->roditelj=najdesniji->roditelj;

            najdesniji->roditelj=roditelj;
            najdesniji->lijevi=zaBrisanje->lijevi;
            najdesniji->desni=zaBrisanje->desni;
        }
    }


    //// brisanje iz liste
    if (zaBrisanje==najmanji) najmanji=zaBrisanje->sljedeci;
    if (zaBrisanje==najveci) najveci=zaBrisanje->prethodni;

    if (zaBrisanje->prethodni) zaBrisanje->prethodni->sljedeci=zaBrisanje->sljedeci;
    if (zaBrisanje->sljedeci) zaBrisanje->sljedeci->prethodni=zaBrisanje->prethodni;

    delete zaBrisanje;
}

void stablo::izbrisi(iterator it)
{
    cvor *zaBrisanje=it.trenutni;
    if (zaBrisanje)
    {
        it.trenutni=it.trenutni->sljedeci;
        izbrisi(zaBrisanje);
    }
}

bool stablo::izbrisi(int broj)
{
    iterator it=find(broj);
    if (it==end()) return false;
    izbrisi(it);
    return true;
}

bool stablo::prazno()
{
    return !korijen;
}

void stablo::ispisiCvor(cvor *tekuci)
{
    cout << "(" << tekuci->element << ") ";
}

stablo::iterator :: iterator() : trenutni(0), prijeTrenutnog(0) {}
stablo::iterator :: iterator(cvor *tekuci) : trenutni(tekuci), prijeTrenutnog( tekuci ? tekuci->prethodni : 0) {}
stablo::iterator :: iterator(cvor *c1, cvor *c2) : trenutni(c2), prijeTrenutnog(c1) {}
stablo::iterator :: iterator(const iterator &it) : trenutni(it.trenutni), prijeTrenutnog(it.prijeTrenutnog) {}
stablo::iterator& stablo::iterator::operator=(const iterator &it)
{
    if (&it == this) return *this;
    trenutni=it.trenutni;
    prijeTrenutnog=it.prijeTrenutnog;
    return *this;
}

stablo::iterator& stablo::iterator::operator++()
{
    if (trenutni)
    {
        prijeTrenutnog=trenutni;
        trenutni=trenutni->sljedeci;
    }

    return *this;
}

stablo::iterator stablo::iterator::operator++(int)
{
    iterator pomocni(trenutni);

    if (trenutni)
    {
        prijeTrenutnog=trenutni;
        trenutni=trenutni->sljedeci;
    }

    return pomocni;
}

stablo::iterator& stablo::iterator::operator--()
{
    if (trenutni==0)
    {
        trenutni=prijeTrenutnog;
        if (prijeTrenutnog) prijeTrenutnog=prijeTrenutnog->prethodni;
    }

    else if (prijeTrenutnog)
    {
        trenutni=prijeTrenutnog;
        prijeTrenutnog=trenutni->prethodni;
    }

    return *this;
}

stablo::iterator stablo::iterator::operator--(int)
{
    iterator pomocni(trenutni);

    if (trenutni==0)
    {
        trenutni=prijeTrenutnog;
        if (prijeTrenutnog) prijeTrenutnog=prijeTrenutnog->prethodni;
    }

    else if (prijeTrenutnog)
    {
        trenutni=prijeTrenutnog;
        prijeTrenutnog=trenutni->prethodni;
    }

    return pomocni;
}

stablo::iterator& stablo::iterator::operator+=(int n)
{
    while (n)
    {
        if (!trenutni) throw "Greska kod operatora +=, nedovoljno elemenata!";
        prijeTrenutnog=trenutni;
        trenutni=trenutni->sljedeci;
        n--;
    }

    return *this;
}

stablo::iterator& stablo::iterator::operator-=(int n)
{
    while (n)
    {
        if (!prijeTrenutnog) throw "Greska kod operatora -=, nedovoljno elemenata!";
        trenutni=prijeTrenutnog;
        prijeTrenutnog=prijeTrenutnog->prethodni;
        n--;
    }

    return *this;
}

int stablo::iterator::operator* () const
{
    if(!trenutni) throw "Pristupate nul-pokazivacu!";
    return trenutni->element;
}

bool stablo::iterator::operator== (const iterator &it) const
{
    return (trenutni == it.trenutni && prijeTrenutnog==it.prijeTrenutnog);
}

bool stablo::iterator::operator!= (const iterator &it) const
{
    return (trenutni != it.trenutni || prijeTrenutnog!=it.prijeTrenutnog);
}

stablo::iterator stablo::begin()
{
    return najmanji;
}

stablo::iterator stablo::end()
{
    return iterator(najveci,0);
}

stablo::iterator stablo::find(int broj)
{
    if (!korijen) return end();
    cvor *tekuci=korijen;

    while (tekuci)
    {
        if (tekuci->element==broj) return tekuci;
        else if (broj < tekuci->element) tekuci=tekuci->lijevi;
        else tekuci=tekuci->desni;
    }

    return end();
}

///// METODE ZA OBILAZAK STABLA
void stablo::preOrder(void(*f)(cvor*), cvor *tekuci)
{
     if (tekuci)
     {
         f(tekuci);
         preOrder(f,tekuci->lijevi);
         preOrder(f,tekuci->desni);
     }
}

void stablo::preOrder(void(*f)(int), cvor *tekuci)
{
     if (tekuci)
     {
         f(tekuci->element);
         preOrder(f,tekuci->lijevi);
         preOrder(f,tekuci->desni);
     }
}

void stablo::preOrder(void(*f)(cvor*))
{
    preOrder(f,korijen);
}

void stablo::inOrder(void(*f)(cvor*), cvor *tekuci)
{
     if (tekuci)
     {
         inOrder(f,tekuci->lijevi);
         f(tekuci);
         inOrder(f,tekuci->desni);
     }
}

void stablo::inOrder(void(*f)(int), cvor *tekuci)
{
     if (tekuci)
     {
         inOrder(f,tekuci->lijevi);
         f(tekuci->element);
         inOrder(f,tekuci->desni);
     }
}

void stablo::inOrder(void(*f)(cvor*))
{
    inOrder(f,korijen);
}

void stablo::postOrder(void(*f)(cvor*), cvor *tekuci)
{
     if (tekuci)
     {
         postOrder(f,tekuci->lijevi);
         postOrder(f,tekuci->desni);
         f(tekuci);
     }
}

void stablo::postOrder(void(*f)(int), cvor *tekuci)
{
     if (tekuci)
     {
         postOrder(f,tekuci->lijevi);
         postOrder(f,tekuci->desni);
         f(tekuci->element);
     }
}

void stablo::postOrder(void(*f)(cvor*))
{
    postOrder(f,korijen);
}
/////// KRAJ METODI ZA OBILAZAK STABLA
