#include "../include/Osoba.h"

Osoba::Osoba(int id, const string imie, const string nazwisko)
    : id_(id), imie_(imie), nazwisko_(nazwisko) {
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
