#include "../include/PozycjaRezerwacji.h"

using namespace std;

PozycjaRezerwacji::PozycjaRezerwacji(shared_ptr<Pojazd> pojazd)
    : pojazd_(pojazd)
{
}

shared_ptr<Pojazd> PozycjaRezerwacji::getPojazd() const
{
    return pojazd_;
}