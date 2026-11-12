#include "../include/Motocykl.h"

using namespace std;

Motocykl::Motocykl(int id_pojazdu,
                   const string &marka,
                   const string &model,
                   const string &nr_rejestracyjny,
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