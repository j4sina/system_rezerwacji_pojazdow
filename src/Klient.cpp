#include "Klient.h"
#include <iostream>

Klient::Klient(int id, string imie, string nazwisko)
    : Osoba(id, imie, nazwisko)
{
}

bool Klient::sprawdzaUprawnienia() const
{
    cout << "Uprawnienia Klienta zweryfikowane (dostep do rezerwacji)." << endl;
    return true;
}

void Klient::wyszukajPojazd(const std::vector<std::shared_ptr<Pojazd>> &katalog, const string &szukanaMarka, const string &szukanyModel) const
{
    cout << "Wyniki wyszukiwania dla: " << szukanaMarka << " " << szukanyModel << ":\n";
    bool znaleziono = false;

    for (const auto &pojazd : katalog)
    {
        if (pojazd->getMarka() == szukanaMarka && pojazd->getModel() == szukanyModel)
        {
            if (pojazd->getDostepnosc())
            {
                cout << "- Pojazd ID: " << pojazd->getIdPojazdu() << " jest DOSTEPNY (Cena: "
                     << pojazd->getCenaZaDzien() << " PLN/dzien)\n";
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

void Klient::sprawdzHistorieRezerwacji() const
{
    std::cout << "\n--- Historia rezerwacji klienta ---\n";
    if (historia_rezerwacji_.empty())
    {
        std::cout << "Brak przypisanych rezerwacji.\n";
        return;
    }

    // Wypisywanie kazdej rezerwacji nalezacej do klienta
    for (const auto &rez : historia_rezerwacji_)
    {
        std::cout << "- Rezerwacja ID: " << rez.getIdRezerwacji()
                  << " | Kwota: " << rez.obliczKoszt() << " PLN"
                  << " | Zwrocono: " << (rez.isZwrocono() ? "TAK" : "NIE")
                  << " | Kara: " << rez.getKara() << " PLN\n";
    }
}