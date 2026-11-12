#pragma once

#include <string>

using namespace std;

class Pojazd
{
public:
    Pojazd(int id_pojazdu,
           const string &marka,
           const string &model,
           const string &nr_rejestracyjny,
           double cena_za_dzien,
           double kaucja);

    virtual ~Pojazd() = default;

    virtual double obliczOplate(int dni) const = 0;

    int getIdPojazdu() const;
    double getCenaZaDzien() const;
    double getKaucja() const;
    bool getDostepnosc() const;
    void setDostepnosc(bool dostepnosc);
    const string &getMarka() const;
    const string &getModel() const;
    const string &getNrRejestracyjny() const;

private:
    int id_pojazdu_;
    string marka_;
    string model_;
    string nr_rejestracyjny_;
    double cena_za_dzien_;
    double kaucja_;
    bool dostepnosc_;
};
