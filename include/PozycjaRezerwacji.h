#pragma once

#include <memory>
#include "Pojazd.h"

using namespace std;

class PozycjaRezerwacji
{
public:
    explicit PozycjaRezerwacji(shared_ptr<Pojazd> pojazd);

    shared_ptr<Pojazd> getPojazd() const;

private:
    shared_ptr<Pojazd> pojazd_;
};
