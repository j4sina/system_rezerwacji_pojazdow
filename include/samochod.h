#pragma once

#include "pojazd.h"

class Samochod : public Pojazd
{
public:
    Samochod(int id_pojazdu,
             const std::string &marka,
             const std::string &model,
             const std::string &nr_rejestracyjny,
             double cena_za_dzien,
             double kaucja);

    double obliczOplate(int dni) const override;
};