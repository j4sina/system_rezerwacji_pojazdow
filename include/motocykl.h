#pragma once

#include "Pojazd.h"
#include <string>

using namespace std;

class Motocykl : public Pojazd
{
public:
    Motocykl(int id_pojazdu,
             const string &marka,
             const string &model,
             const string &nr_rejestracyjny,
             double cena_za_dzien,
             double kaucja);

    double obliczOplate(int dni) const override;
};