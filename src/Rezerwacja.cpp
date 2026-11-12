#include "../include/Rezerwacja.h"
#include <iostream>

using namespace std;

Rezerwacja::Rezerwacja(int id_rezerwacji, const Date &data_rezerwacji,
                       const Date &termin_zwrotu, int ilosc_dni)
    : data_rezerwacji_(data_rezerwacji),
      data_zwrotu_(termin_zwrotu),
      ilosc_dni_(ilosc_dni),
      id_rezerwacji_(id_rezerwacji),
      potwierdzono_(false),
      zwrocono_(false),
      termin_zwrotu_(termin_zwrotu),
      kara_(0.0f)
{
}

void Rezerwacja::dodajPozycje(const PozycjaRezerwacji &pozycja)
{
    pozycje_.push_back(pozycja);
}

float Rezerwacja::obliczKoszt() const
{
    float suma = 0.0f;
    for (const auto &poz : pozycje_)
    {
        float kosztWynajmu = static_cast<float>(poz.getPojazd()->obliczOplate(ilosc_dni_));
        float kaucja = static_cast<float>(poz.getPojazd()->getKaucja());
        suma += kosztWynajmu + kaucja;
    }
    return suma;
}

float Rezerwacja::naliczKare(const Date &faktyczna_data_zwrotu)
{
    data_zwrotu_ = faktyczna_data_zwrotu;
    zwrocono_ = true;

    const float STAWKA_KARY_DZIEN = 150.0f;

    int dniUstalonyTermin = termin_zwrotu_.rok * 365 + termin_zwrotu_.miesiac * 30 + termin_zwrotu_.dzien;
    int dniFaktycznyZwrot = faktyczna_data_zwrotu.rok * 365 + faktyczna_data_zwrotu.miesiac * 30 + faktyczna_data_zwrotu.dzien;
    int dniSpoznienia = dniFaktycznyZwrot - dniUstalonyTermin;

    if (dniSpoznienia > 0)
    {
        kara_ = static_cast<float>(dniSpoznienia) * STAWKA_KARY_DZIEN;
    }
    else
    {
        kara_ = 0.0f;
    }

    return kara_;
}

int Rezerwacja::getIdRezerwacji() const
{
    return id_rezerwacji_;
}

bool Rezerwacja::isPotwierdzono() const
{
    return potwierdzono_;
}

void Rezerwacja::setPotwierdzono(bool potwierdzono)
{
    potwierdzono_ = potwierdzono;
}

bool Rezerwacja::isZwrocono() const
{
    return zwrocono_;
}

void Rezerwacja::setZwrocono(bool zwrocono)
{
    zwrocono_ = zwrocono;
}

Date Rezerwacja::getTerminZwrotu() const
{
    return termin_zwrotu_;
}

float Rezerwacja::getKara() const
{
    return kara_;
}

const vector<PozycjaRezerwacji> &Rezerwacja::getPozycje() const
{
    return pozycje_;
}

void Rezerwacja::setPlatnosc(const Platnosc &platnosc)
{
    platnosc_ = platnosc;
}