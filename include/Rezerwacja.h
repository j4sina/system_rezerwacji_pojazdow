#pragma once

#include <vector>
#include "Date.h"
#include "PozycjaRezerwacji.h"
#include "Platnosc.h"

class Rezerwacja
{
public:
    Rezerwacja(int id_rezerwacji, const Date &data_rezerwacji,
               const Date &termin_zwrotu, int ilosc_dni);

    void dodajPozycje(const PozycjaRezerwacji &pozycja);
    float obliczKoszt() const;
    float naliczKare(const Date &faktyczna_data_zwrotu);

    int getIdRezerwacji() const;
    bool isPotwierdzono() const;
    void setPotwierdzono(bool potwierdzono);
    bool isZwrocono() const;
    void setZwrocono(bool zwrocono);
    Date getTerminZwrotu() const;
    float getKara() const;
    const std::vector<PozycjaRezerwacji> &getPozycje() const;
    void setPlatnosc(const Platnosc &platnosc);

private:
    Date data_rezerwacji_;
    Date data_zwrotu_;
    int ilosc_dni_;
    std::vector<PozycjaRezerwacji> pozycje_;
    int id_rezerwacji_;
    bool potwierdzono_;
    bool zwrocono_;
    Date termin_zwrotu_;
    float kara_;
    Platnosc platnosc_;
};
