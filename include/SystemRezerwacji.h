#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Pojazd.h"
#include "Klient.h"
#include "PracownikObslugi.h"
#include "Rezerwacja.h"
#include "Date.h"

class SystemRezerwacji
{
public:
    SystemRezerwacji();

    void dodajKlienta(std::shared_ptr<Klient> klient);
    void dodajPracownika(std::shared_ptr<PracownikObslugi> pracownik);
    void dodajPojazd(std::shared_ptr<Pojazd> pojazd);

    bool pracownikDodajPojazd(int idPracownika, std::shared_ptr<Pojazd> nowyPojazd);

    bool pracownikUsunPojazd(int idPracownika, int idPojazdu);

    void wyswietlDostepnePojazdy() const;

    bool wypozycz(int idKlienta, int idPojazdu, const Date &dataRezerwacji, const Date &terminZwrotu);

    bool przyjmijZwrot(int idRezerwacji, const Date &faktycznaDataZwrotu);

    std::shared_ptr<Pojazd> znajdzPojazd(int idPojazdu) const;
    std::shared_ptr<Klient> znajdzKlienta(int idKlienta) const;
    std::shared_ptr<PracownikObslugi> znajdzPracownika(int idPracownika) const;

private:
    std::vector<std::shared_ptr<Pojazd>> flota_;
    std::vector<std::shared_ptr<Klient>> klienci_;
    std::vector<std::shared_ptr<PracownikObslugi>> pracownicy_;
    std::vector<Rezerwacja> rezerwacje_;
    int nastepne_id_rezerwacji_;
};