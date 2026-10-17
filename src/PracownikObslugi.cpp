#include "../include/PracownikObslugi.h"

PracownikObslugi::PracownikObslugi(int id, const string &imie, const string &nazwisko,
                                   const string &id_pracownika, const Date &data_zatrudnienia,
                                   float pensja)
    : Osoba(id, imie, nazwisko),
      id_pracownika_(id_pracownika),
      data_zatrudnienia_(data_zatrudnienia),
      pensja_(pensja) {
}

bool PracownikObslugi::sprawdzaUprawnienia() const {
    // Pracownik obslugi posiada uprawnienia do zarzadzania flota
    return true;
}

string PracownikObslugi::getIdPracownika() const {
    return id_pracownika_;
}

Date PracownikObslugi::getDataZatrudnienia() const {
    return data_zatrudnienia_;
}

float PracownikObslugi::getPensja() const {
    return pensja_;
}
