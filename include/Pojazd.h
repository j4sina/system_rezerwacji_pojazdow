#pragma once

#include <string>

using namespace std;

class Pojazd {
public:
    Pojazd(int id_pojazdu, string marka, string model, string nr_rejestracyjny, double cena_za_dzien, double kaucja);

    bool sprawdźDostępność() const;

    int getIdPojazdu() const;
    double getCenaZaDzien() const;
    double getKaucja() const;
    bool getDostepnosc() const;
    void setDostepnosc(bool dostepnosc);

private:
    int id_pojazdu_;
    string marka_;
    string model_;
    string nr_rejestracyjny_;
    double cena_za_dzien_;
    double kaucja_;
    bool dostepnosc_;
};