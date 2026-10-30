#include "../include/Pojazd.h"

Pojazd::Pojazd(int id_pojazdu,
               const std::string &marka,
               const std::string &model,
               const std::string &nr_rejestracyjny,
               double cena_za_dzien,
               double kaucja)
    : id_pojazdu_(id_pojazdu),
      marka_(marka),
      model_(model),
      nr_rejestracyjny_(nr_rejestracyjny),
      cena_za_dzien_(cena_za_dzien),
      kaucja_(kaucja),
      dostepnosc_(true)
{
}

int Pojazd::getIdPojazdu() const
{
    return id_pojazdu_;
}

double Pojazd::getCenaZaDzien() const
{
    return cena_za_dzien_;
}

double Pojazd::getKaucja() const
{
    return kaucja_;
}

bool Pojazd::getDostepnosc() const
{
    return dostepnosc_;
}

void Pojazd::setDostepnosc(bool dostepnosc)
{
    dostepnosc_ = dostepnosc;
}

const std::string &Pojazd::getMarka() const
{
    return marka_;
}

const std::string &Pojazd::getModel() const
{
    return model_;
}

const std::string &Pojazd::getNrRejestracyjny() const
{
    return nr_rejestracyjny_;
}