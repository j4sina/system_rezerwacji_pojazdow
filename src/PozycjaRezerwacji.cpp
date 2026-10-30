#include "../include/PozycjaRezerwacji.h"

PozycjaRezerwacji::PozycjaRezerwacji(std::shared_ptr<Pojazd> pojazd)
    : pojazd_(pojazd)
{
}

std::shared_ptr<Pojazd> PozycjaRezerwacji::getPojazd() const
{
    return pojazd_;
}