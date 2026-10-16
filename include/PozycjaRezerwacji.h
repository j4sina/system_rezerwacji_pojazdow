#pragma once

#include <memory>
#include "Pojazd.h"

class PozycjaRezerwacji
{
public:
    explicit PozycjaRezerwacji(std::shared_ptr<Pojazd> pojazd);

    std::shared_ptr<Pojazd> getPojazd() const;

private:
    std::shared_ptr<Pojazd> pojazd_;
};
