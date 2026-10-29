#include "../include/Osoba.h"

Osoba::Osoba(int id, const string imie, const string nazwisko)
    : id_(id), imie_(imie), nazwisko_(nazwisko), login_(""), haslo_(""), czy_zalogowany_(false) {
}

Osoba::Osoba(int id, const string imie, const string nazwisko, const string login, const string haslo)
    : id_(id), imie_(imie), nazwisko_(nazwisko), login_(login), haslo_(haslo), czy_zalogowany_(false) {
}

bool Osoba::zaloguj(const string login, const string haslo) {
    if (login_ == login && haslo_ == haslo && !login_.empty()) {
        czy_zalogowany_ = true;
        return true;
    }
    return false;
}

void Osoba::wyloguj() {
    czy_zalogowany_ = false;
}

bool Osoba::czyZalogowany() const {
    return czy_zalogowany_;
}

int Osoba::getId() const {
    return id_;
}

string Osoba::getImie() const {
    return imie_;
}

string Osoba::getNazwisko() const {
    return nazwisko_;
}

string Osoba::getLogin() const {
    return login_;
}

void Osoba::setLogin(const string login) {
    login_ = login;
}

void Osoba::setHaslo(const string haslo) {
    haslo_ = haslo;
}
