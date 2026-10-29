#pragma once
#include <memory>
#include <string>
#include "Osoba.h"
#include "Date.h"
#include <vector>
#include "Pojazd.h"

using namespace std;

class PracownikObslugi : public Osoba
{
public:
    PracownikObslugi(int id, const string &imie, const string &nazwisko,
                     const string &id_pracownika, const Date &data_zatrudnienia,
                     float pensja);

    bool sprawdzaUprawnienia() const override;

    string getIdPracownika() const;
    Date getDataZatrudnienia() const;
    float getPensja() const;

    void dodajPojazd(std::vector<std::shared_ptr<Pojazd>> &flota, std::shared_ptr<Pojazd> nowyPojazd);
    void usunPojazd(std::vector<std::shared_ptr<Pojazd>> &flota, int idPojazdu);

private:
    string id_pracownika_;
    Date data_zatrudnienia_;
    float pensja_;
};
