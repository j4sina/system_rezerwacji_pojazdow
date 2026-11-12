#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "Osoba.h"
#include <vector>
#include "Pojazd.h"
#include "Rezerwacja.h"

using namespace std;

class Klient : public Osoba
{
public:
    Klient(int id, string imie, string nazwisko);

    bool sprawdzaUprawnienia() const override;

    void wyszukajPojazd(const vector<shared_ptr<Pojazd>> &katalog, const string &szukanaMarka, const string &szukanyModel) const;
    void dodajDoHistorii(const Rezerwacja &rezerwacja);
    void zaktualizujRezerwacje(const Rezerwacja &rezerwacja);
    void sprawdzHistorieRezerwacji() const;

private:
    vector<Rezerwacja> historia_rezerwacji_;
};
