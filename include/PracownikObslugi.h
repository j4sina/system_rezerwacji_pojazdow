#pragma once

#include <string>
#include "Osoba.h"
#include "Date.h"

class PracownikObslugi : public Osoba
{
public:
    PracownikObslugi(int id, const std::string &imie, const std::string &nazwisko,
                     const std::string &id_pracownika, const Date &data_zatrudnienia,
                     float pensja);

    bool sprawdzUprawnienia() override;

    std::string getIdPracownika() const;
    Date getDataZatrudnienia() const;
    float getPensja() const;

private:
    std::string id_pracownika_;
    Date data_zatrudnienia_;
    float pensja_;
};
