#include "Klient.h"
#include <iostream>

Klient::Klient(int id, string imie, string nazwisko)
    : Osoba(id, imie, nazwisko)
{
}

bool Klient::sprawdzaUprawnienia() const
{
    cout << "Uprawnienia Klienta zweryfikowane (dostep do rezerwacji)." << endl;
    return true;
}