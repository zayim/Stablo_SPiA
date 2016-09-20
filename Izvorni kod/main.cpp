#include "Stablo.h"
#include <iostream>
#include <cstdlib>
#include "TestCurenja.h"
using namespace std;
int main()
{
    try
    {
        stablo x;

        int izbor=1,broj;

        while (true)
        {
            system("clear");
            cout << "ODABERITE OPCIJU" << endl;
            cout << " 1.  Umetni" << endl;
            cout << " 10. Unesi vise od jednog elementa" << endl;
            cout << " 2.  Izbrisi" << endl;
            cout << " 3.  Trazi" << endl;
            cout << " 4.  Ispisi PreOrder" << endl;
            cout << " 5.  Ispisi InOrder" << endl;
            cout << " 6.  Ispisi PostOrder" << endl;
            cout << " 7.  Ispisi najmanji element (metoda begin)" << endl;
            cout << " 8.  Ispisi najveci element (metoda end)" << endl;
            cout << " 9.  Ispisi sortirano (koristeci iteratore)" << endl;
            cout << " 0.  Kraj programa" << endl;
            cout << "?: "; cin >> izbor;

            system("clear");
            if (izbor == 1)
            {
                cout << "Unesite cijeli broj: ";
                cin >> broj;
                x.umetni(broj);
                cout << "Uspjesno umetnuto!" << endl;
            }
            else if (izbor == 10)
            {
                cout << "Unesite cijele brojeve (0 za kraj): " << endl;
                broj=1;
                while (broj)
                {
                    cin >> broj;
                    if (broj) x.umetni(broj);
                }
                cout << "Uspjesno umetnuto!" << endl;
            }
            else if (izbor == 2)
            {
                cout << "Unesite cijeli broj: ";
                cin >> broj;
                if (x.izbrisi(broj)) cout << "Uspjesno izbrisan!" << endl;
                else cout << "Broja nije ni bilo!" << endl;
            }
            else if (izbor == 3)
            {
                cout << "Unesite cijeli broj: ";
                cin >> broj;
                stablo::iterator it=x.find(broj);
                if (it!=x.end()) cout << "Broj " << *it << " se nalazi u stablu!" << endl;
                else cout << "Broj se ne nalazi u stablu!" << endl;
            }
            else if (izbor == 4)
            {
                cout << "Elementi stabla u preOrder poretku: " << endl;
                x.preOrder(stablo::ispisiCvor);
                cout << endl;
            }
            else if (izbor == 5)
            {
                cout << "Elementi stabla u inOrder poretku: " << endl;
                x.inOrder(stablo::ispisiCvor);
                cout << endl;
            }
            else if (izbor == 6)
            {
                cout << "Elementi stabla u postOrder poretku: " << endl;
                x.postOrder(stablo::ispisiCvor);
                cout << endl;
            }
            else if (izbor == 7)
            {
                cout << "Najmanji element stabla (pomocu metode begin koja vraca iterator): " << *(x.begin()) << endl;
            }
            else if (izbor == 8)
            {
                cout << "Najveci element stabla (pomocu metode end koja vraca iterator): " << *(--x.end()) << endl;
            }
            else if (izbor == 9)
            {
                cout << "Soritrani elementi stabla (pomocu iteratora, begin, end i petlje: " << endl;
                for (stablo::iterator it=x.begin(); it!=x.end(); it++)
                    cout << *it << " ";
                cout << endl;
            }
            else if (izbor == 0)
            {
                system("clear");
                cout << "Odabrali ste Kraj programa!" << endl;
                return 0;
            }
            cin.get();
            cin.get();
        }
    }
    catch(const char poruka[])
    {
        cout << poruka << endl;
    }

    return 0;
}
