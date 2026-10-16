#ifndef KLIENT_H
#define KLIENT_H

#include <string>
#include <iostream>
#include "osoba.h"

using namespace std;

class Klient : public Osoba {
public:
    Klient(int id, string imie, string nazwisko);

    bool sprawdzaUprawnienia() const override;
};

#endif