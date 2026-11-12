#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Pojazd.h"
#include "Klient.h"
#include "PracownikObslugi.h"
#include "Rezerwacja.h"
#include "Date.h"

using namespace std;

class SystemRezerwacji
{
public:
    SystemRezerwacji();

    void dodajKlienta(shared_ptr<Klient> klient);
    void dodajPracownika(shared_ptr<PracownikObslugi> pracownik);
    void dodajPojazd(shared_ptr<Pojazd> pojazd);

    shared_ptr<Osoba> zalogujUzytkownika(const string &login, const string &haslo);

    bool pracownikDodajPojazd(int idPracownika, shared_ptr<Pojazd> nowyPojazd);
    bool pracownikUsunPojazd(int idPracownika, int idPojazdu);

    vector<shared_ptr<Pojazd>> wyszukajDostepnePojazdy() const;
    void wyswietlDostepnePojazdy() const;

    bool wypozycz(int idKlienta, int idPojazdu, const Date &dataRezerwacji, const Date &terminZwrotu);
    bool oplacRezerwacje(int idRezerwacji, SposobPlatnosci sposob, const string &terminPlatnosci);

    bool przyjmijZwrot(int idRezerwacji, const Date &faktycznaDataZwrotu);
    bool przyjmijZwrot(int idPracownika, int idRezerwacji, const Date &faktycznaDataZwrotu);

    shared_ptr<Pojazd> znajdzPojazd(int idPojazdu) const;
    shared_ptr<Klient> znajdzKlienta(int idKlienta) const;
    shared_ptr<PracownikObslugi> znajdzPracownika(int idPracownika) const;

    const vector<shared_ptr<Pojazd>> &getFlota() const;
    const vector<Rezerwacja> &getRezerwacje() const;
    int getOstatnieIdRezerwacji() const;

private:
    vector<shared_ptr<Pojazd>> flota_;
    vector<shared_ptr<Klient>> klienci_;
    vector<shared_ptr<PracownikObslugi>> pracownicy_;
    vector<Rezerwacja> rezerwacje_;
    int nastepne_id_rezerwacji_;
    int nastepne_id_platnosci_;
};
