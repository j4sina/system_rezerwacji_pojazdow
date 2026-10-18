#pragma once

#include <string>

class Pojazd
{
public:
    Pojazd(int id_pojazdu,
           const std::string &marka,
           const std::string &model,
           const std::string &nr_rejestracyjny,
           double cena_za_dzien,
           double kaucja);

    virtual ~Pojazd() = default;

    virtual double obliczOplate(int dni) const = 0;

    int getIdPojazdu() const;
    double getCenaZaDzien() const;
    double getKaucja() const;
    bool getDostepnosc() const;
    void setDostepnosc(bool dostepnosc);
    const std::string &getMarka() const;
    const std::string &getModel() const;
    const std::string &getNrRejestracyjny() const;

private:
    int id_pojazdu_;
    std::string marka_;
    std::string model_;
    std::string nr_rejestracyjny_;
    double cena_za_dzien_;
    double kaucja_;
    bool dostepnosc_;
};
