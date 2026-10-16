#ifndef PLATNOSC_H
#define PLATNOSC_H

#include <iostream>

using namespace std;

enum class SposobPlatnosci {
    KARTA,
    BLIK,
    GOTOWKA
};

class Platnosc {
public:
    Platnosc(int id_platnosci, SposobPlatnosci sposob_platnosci, string termin_platnosci, double cena);

    void zarejestrujPlatnosc();

    int getIdPlatnosci() const;
    double getCena() const;

private:
    int id_platnosci_;
    SposobPlatnosci sposob_platnosci_;
    string termin_platnosci_;
    double cena_;
};

#endif