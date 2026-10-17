#pragma once

#include <string>
#include <iostream>
#include "osoba.h"
// #include "Rezerwacja.h"

using namespace std;

class Klient : public Osoba {
public:
    Klient(int id, string imie, string nazwisko);

    bool sprawdzaUprawnienia() const override;
};