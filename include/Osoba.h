#pragma once

#include <iostream>
using namespace std;

class Osoba {
public:
    Osoba(int id, const string imie, const string nazwisko);
    virtual ~Osoba() = default;

    virtual bool sprawdzaUprawnienia() const = 0;

    int getId() const;
    string getImie() const;
    string getNazwisko() const;

private:
    int id_;
    string imie_;
    string nazwisko_;
};