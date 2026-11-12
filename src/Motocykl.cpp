#include "../include/Motocykl.h"

Motocykl::Motocykl(int id_pojazdu,
                   const std::string &marka,
                   const std::string &model,
                   const std::string &nr_rejestracyjny,
                   double cena_za_dzien,
                   double kaucja)
    : Pojazd(id_pojazdu, marka, model, nr_rejestracyjny, cena_za_dzien, kaucja)
{
}

double Motocykl::obliczOplate(int dni) const
{
    double koszt = getCenaZaDzien() * dni;
    return koszt;
}