#include "../include/Platnosc.h"
#include <iostream>

Platnosc::Platnosc()
    : id_platnosci_(0),
      sposob_platnosci_(SposobPlatnosci::KARTA),
      termin_platnosci_(""),
      cena_(0.0)
{
}

Platnosc::Platnosc(int id_platnosci, SposobPlatnosci sposob_platnosci, string termin_platnosci, double cena)
    : id_platnosci_(id_platnosci),
      sposob_platnosci_(sposob_platnosci),
      termin_platnosci_(termin_platnosci),
      cena_(cena)
{
}

void Platnosc::zarejestrujPlatnosc()
{
    string nazwaMetody;
    switch (sposob_platnosci_)
    {
    case SposobPlatnosci::KARTA:
        nazwaMetody = "Karta platnicza";
        break;
    case SposobPlatnosci::BLIK:
        nazwaMetody = "BLIK";
        break;
    case SposobPlatnosci::GOTOWKA:
        nazwaMetody = "Gotowka";
        break;
    }

    std::cout << "[Platnosc] Zarejestrowano pomyslnie platnosc ID: " << id_platnosci_
              << " na kwote: " << cena_ << " PLN (metoda: " << nazwaMetody << ").\n";
}

int Platnosc::getIdPlatnosci() const
{
    return id_platnosci_;
}

double Platnosc::getCena() const
{
    return cena_;
}