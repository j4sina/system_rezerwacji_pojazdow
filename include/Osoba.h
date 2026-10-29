#pragma once

#include <iostream>
using namespace std;

class Osoba {
public:
    Osoba(int id, const string imie, const string nazwisko);
    Osoba(int id, const string imie, const string nazwisko, const string login, const string haslo);
    virtual ~Osoba() = default;

    virtual bool sprawdzaUprawnienia() const = 0;

    bool zaloguj(const string login, const string haslo);
    void wyloguj();
    bool czyZalogowany() const;

    int getId() const;
    string getImie() const;
    string getNazwisko() const;
    string getLogin() const;

    void setLogin(const string login);
    void setHaslo(const string haslo);

private:
    int id_;
    string imie_;
    string nazwisko_;
    string login_;
    string haslo_;
    bool czy_zalogowany_;
};
