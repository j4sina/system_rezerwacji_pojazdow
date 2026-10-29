#include "../include/PracownikObslugi.h"
#include <algorithm>
#include <iostream>

PracownikObslugi::PracownikObslugi(int id, const string &imie, const string &nazwisko,
                                   const string &id_pracownika, const Date &data_zatrudnienia,
                                   float pensja)
    : Osoba(id, imie, nazwisko),
      id_pracownika_(id_pracownika),
      data_zatrudnienia_(data_zatrudnienia),
      pensja_(pensja)
{
}

bool PracownikObslugi::sprawdzaUprawnienia() const
{
    // Pracownik obslugi posiada uprawnienia do zarzadzania flota
    return true;
}

string PracownikObslugi::getIdPracownika() const
{
    return id_pracownika_;
}

Date PracownikObslugi::getDataZatrudnienia() const
{
    return data_zatrudnienia_;
}

float PracownikObslugi::getPensja() const
{
    return pensja_;
}

void PracownikObslugi::dodajPojazd(std::vector<std::shared_ptr<Pojazd>> &flota, std::shared_ptr<Pojazd> nowyPojazd)
{
    flota.push_back(nowyPojazd);
    std::cout << "Pracownik dodal do floty pojazd: " << nowyPojazd->getMarka()
              << " " << nowyPojazd->getModel() << " (ID: " << nowyPojazd->getIdPojazdu() << ").\n";
}

void PracownikObslugi::usunPojazd(std::vector<std::shared_ptr<Pojazd>> &flota, int idPojazdu)
{
    auto it = std::remove_if(flota.begin(), flota.end(),
                             [idPojazdu](const std::shared_ptr<Pojazd> &p)
                             {
                                 return p->getIdPojazdu() == idPojazdu;
                             });

    if (it != flota.end())
    {
        flota.erase(it, flota.end());
        std::cout << "Pracownik pomyslnie usunal pojazd o ID: " << idPojazdu << " z systemu.\n";
    }
    else
    {
        std::cout << "Blad: Nie znaleziono we flocie pojazdu o ID " << idPojazdu << ".\n";
    }
}