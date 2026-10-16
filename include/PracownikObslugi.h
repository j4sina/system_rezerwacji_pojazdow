#pragma once

#include <string>
#include "Osoba.h"

using namespace std;

class PracownikObslugi : public Osoba
{
public:
    PracownikObslugi(int id, const string &imie, const string &nazwisko,
                     const string &id_pracownika, const Date &data_zatrudnienia,
                     float pensja);

    bool sprawdzUprawnienia() override;

    string getIdPracownika() const;
    Date getDataZatrudnienia() const;
    float getPensja() const;

private:
    string id_pracownika_;
    Date data_zatrudnienia_;
    float pensja_;
};
