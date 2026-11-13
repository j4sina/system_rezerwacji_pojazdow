#include "../include/Klient.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace
{
string naMaleLitery(string s)
{
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return s;
}
} // namespace

Klient::Klient(int id, string imie, string nazwisko)
    : Osoba(id, imie, nazwisko)
{
}

bool Klient::sprawdzUprawnienia() const
{
    cout << "Uprawnienia Klienta zweryfikowane (dostep do rezerwacji)." << endl;
    return true;
}

void Klient::wyszukajPojazd(const vector<shared_ptr<Pojazd>> &katalog, const string &szukanaMarka) const
{
    cout << "Wyniki wyszukiwania dla marki: " << szukanaMarka << ":\n";
    bool znaleziono = false;
    string szukanaLower = naMaleLitery(szukanaMarka);

    for (const auto &pojazd : katalog)
    {
        if (naMaleLitery(pojazd->getMarka()) == szukanaLower)
        {
            if (pojazd->getDostepnosc())
            {
                cout << "- Pojazd ID: " << pojazd->getIdPojazdu()
                     << " (" << pojazd->getMarka() << " " << pojazd->getModel() << ")"
                     << " jest DOSTEPNY (Cena: " << pojazd->getCenaZaDzien() << " PLN/dzien)\n";
                znaleziono = true;
            }
        }
    }

    if (!znaleziono)
    {
        cout << "- Brak dostepnych pojazdow spelniajacych kryteria.\n";
    }
}

void Klient::dodajDoHistorii(const Rezerwacja &rezerwacja)
{
    historia_rezerwacji_.push_back(rezerwacja);
}

void Klient::zaktualizujRezerwacje(const Rezerwacja &rezerwacja)
{
    for (auto &rez : historia_rezerwacji_)
    {
        if (rez.getIdRezerwacji() == rezerwacja.getIdRezerwacji())
        {
            rez = rezerwacja;
            return;
        }
    }
}

void Klient::sprawdzHistorieRezerwacji() const
{
    cout << "\n--- Historia rezerwacji klienta ---\n";
    if (historia_rezerwacji_.empty())
    {
        cout << "Brak przypisanych rezerwacji.\n";
        return;
    }

    // Wypisywanie kazdej rezerwacji nalezacej do klienta
    for (const auto &rez : historia_rezerwacji_)
    {
        cout << "- Rezerwacja ID: " << rez.getIdRezerwacji()
             << " | Kwota: " << rez.obliczKoszt() << " PLN"
             << " | Zwrocono: " << (rez.isZwrocono() ? "TAK" : "NIE")
             << " | Kara: " << rez.getKara() << " PLN\n";
    }
}