#include "../include/SystemRezerwacji.h"
#include <iostream>

SystemRezerwacji::SystemRezerwacji()
    : nastepne_id_rezerwacji_(1)
{
}

void SystemRezerwacji::dodajKlienta(std::shared_ptr<Klient> klient)
{
    klienci_.push_back(klient);
}

void SystemRezerwacji::dodajPracownika(std::shared_ptr<PracownikObslugi> pracownik)
{
    pracownicy_.push_back(pracownik);
}

void SystemRezerwacji::dodajPojazd(std::shared_ptr<Pojazd> pojazd)
{
    flota_.push_back(pojazd);
}

std::shared_ptr<Pojazd> SystemRezerwacji::znajdzPojazd(int idPojazdu) const
{
    for (const auto &p : flota_)
    {
        if (p->getIdPojazdu() == idPojazdu)
        {
            return p;
        }
    }
    return nullptr;
}

std::shared_ptr<Klient> SystemRezerwacji::znajdzKlienta(int idKlienta) const
{
    for (const auto &k : klienci_)
    {
        if (k->getId() == idKlienta)
        {
            return k;
        }
    }
    return nullptr;
}

std::shared_ptr<PracownikObslugi> SystemRezerwacji::znajdzPracownika(int idPracownika) const
{
    for (const auto &pr : pracownicy_)
    {
        if (pr->getId() == idPracownika)
        {
            return pr;
        }
    }
    return nullptr;
}

bool SystemRezerwacji::wypozycz(int idKlienta, int idPojazdu, const Date &dataRezerwacji, const Date &terminZwrotu)
{
    auto pojazd = znajdzPojazd(idPojazdu);
    auto klient = znajdzKlienta(idKlienta);

    if (!pojazd || !klient)
    {
        std::cout << "[System] Blad: Niepoprawne ID klienta lub pojazdu.\n";
        return false;
    }

    if (!pojazd->getDostepnosc())
    {
        std::cout << "[System] Pojazd jest aktualnie NIEDOSTEPNY.\n";
        return false;
    }

    if (!klient->sprawdzaUprawnienia())
    {
        std::cout << "[System] Klient nie posiada uprawnien do rezerwacji.\n";
        return false;
    }

    int dniStart = dataRezerwacji.rok * 365 + dataRezerwacji.miesiac * 30 + dataRezerwacji.dzien;
    int dniKoniec = terminZwrotu.rok * 365 + terminZwrotu.miesiac * 30 + terminZwrotu.dzien;
    int iloscDni = dniKoniec - dniStart;
    if (iloscDni <= 0)
        iloscDni = 1;

    PozycjaRezerwacji pozycja(pojazd);

    Rezerwacja rezerwacja(nastepne_id_rezerwacji_++, dataRezerwacji, terminZwrotu, iloscDni);

    rezerwacja.dodajPozycje(pozycja);

    float koszt = rezerwacja.obliczKoszt();

    pojazd->setDostepnosc(false);
    rezerwacja.setPotwierdzono(true);

    klient->dodajDoHistorii(rezerwacja);
    rezerwacje_.push_back(rezerwacja);

    std::cout << "[System] Rezerwacja zakonczona sukcesem! ID Rezerwacji: "
              << rezerwacja.getIdRezerwacji()
              << " | Laczny koszt (z kaucja): " << koszt << " PLN\n";

    return true;
}

bool SystemRezerwacji::pracownikDodajPojazd(int idPracownika, std::shared_ptr<Pojazd> nowyPojazd)
{
    (void)idPracownika;
    (void)nowyPojazd;
    return false;
}
bool SystemRezerwacji::pracownikUsunPojazd(int idPracownika, int idPojazdu)
{
    (void)idPracownika;
    (void)idPojazdu;
    return false;
}
void SystemRezerwacji::wyswietlDostepnePojazdy() const
{
}
bool SystemRezerwacji::przyjmijZwrot(int idRezerwacji, const Date &faktycznaDataZwrotu)
{
    (void)idRezerwacji;
    (void)faktycznaDataZwrotu;
    return false;
}