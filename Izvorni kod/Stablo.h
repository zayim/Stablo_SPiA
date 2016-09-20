#ifndef STABLO
#define STABLO
class stablo
{
    struct cvor
    {
        int element;
        cvor *roditelj, *lijevi, *desni;
        cvor *prethodni, *sljedeci;

        cvor (int element, cvor* roditelj, cvor* lijevi, cvor* desni, cvor* prethodni, cvor* sljedeci)
        {
            this->element=element;      this->desni=desni;
            this->roditelj=roditelj;    this->prethodni=prethodni;
            this->lijevi=lijevi;        this->sljedeci=sljedeci;
        }
    };

    cvor *korijen, *najveci, *najmanji;
    void izbrisi (cvor *zaBrisanje);
    void unisti(cvor *tekuci);
    void preOrder(void(*f)(int), cvor *tekuci);
    void inOrder(void(*f)(int), cvor *tekuci);
    void postOrder(void(*f)(int), cvor *tekuci);
    void preOrder(void(*f)(cvor*), cvor *tekuci);
    void inOrder(void(*f)(cvor*), cvor *tekuci);
    void postOrder(void(*f)(cvor*), cvor *tekuci);
    stablo(const stablo&);
    stablo& operator=(const stablo&);

    public:

    class iterator
    {
        cvor* trenutni;
        cvor* prijeTrenutnog;

        public:
        iterator();
        iterator(cvor* tekuci);
        iterator(cvor *c1, cvor *c2);
        iterator(const iterator &it);
        iterator& operator=(const iterator &it);
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(int n);
        iterator& operator-=(int n);
        int operator*() const;
        bool operator==(const iterator &it) const;
        bool operator!=(const iterator &it) const;
        friend class stablo;
    };

    stablo();
    ~stablo();
    void umetni(int broj);
    bool izbrisi(int broj);
    void izbrisi(iterator it);
    bool prazno();
    iterator begin();
    iterator end();
    iterator find(int broj);
    void preOrder(void(*f)(int));
    void inOrder(void(*f)(int));
    void postOrder(void(*f)(int));
    void preOrder(void(*f)(cvor*));
    void inOrder(void(*f)(cvor*));
    void postOrder(void(*f)(cvor*));
    static void ispisiCvor(cvor *tekuci);
};
#endif
