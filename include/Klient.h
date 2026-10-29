#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "osoba.h"
#include <vector>
#include "Pojazd.h"
#include "Rezerwacja.h"

using namespace std;

class Klient : public Osoba
{
public:
    Klient(int id, string imie, string nazwisko);

    bool sprawdzaUprawnienia() const override;

    void wyszukajPojazd(const std::vector<std::shared_ptr<Pojazd>> &katalog, const std::string &szukanaMarka, const std::string &szukanyModel) const;
    void dodajDoHistorii(const Rezerwacja &rezerwacja);
    void sprawdzHistorieRezerwacji() const;

private:
    std::vector<Rezerwacja> historia_rezerwacji_;
};
