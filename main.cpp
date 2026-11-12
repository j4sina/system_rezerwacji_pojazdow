#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "include/Date.h"
#include "include/Klient.h"
#include "include/Motocykl.h"
#include "include/Osoba.h"
#include "include/Platnosc.h"
#include "include/Pojazd.h"
#include "include/PracownikObslugi.h"
#include "include/Samochod.h"
#include "include/SystemRezerwacji.h"

using namespace std;

namespace
{
void wyczyscBuforWejscia()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int wczytajInt(const string &komunikat)
{
    int wartosc = 0;
    while (true)
    {
        cout << komunikat;
        if (cin >> wartosc)
        {
            return wartosc;
        }
        cout << "Niepoprawna liczba. Sprobuj ponownie.\n";
        wyczyscBuforWejscia();
    }
}

double wczytajDouble(const string &komunikat)
{
    double wartosc = 0.0;
    while (true)
    {
        cout << komunikat;
        if (cin >> wartosc)
        {
            return wartosc;
        }
        cout << "Niepoprawna wartosc. Sprobuj ponownie.\n";
        wyczyscBuforWejscia();
    }
}

Date wczytajDate(const string &naglowek)
{
    cout << naglowek << "\n";
    int d = wczytajInt("  Dzien: ");
    int m = wczytajInt("  Miesiac: ");
    int r = wczytajInt("  Rok: ");
    return Date(d, m, r);
}

void zainicjujDaneStartowe(SystemRezerwacji &system)
{
    auto klient1 = make_shared<Klient>(1, "Jan", "Kowalski");
    klient1->setLogin("jan");
    klient1->setHaslo("1234");
    system.dodajKlienta(klient1);

    auto klient2 = make_shared<Klient>(2, "Marek", "Zielinski");
    klient2->setLogin("marek");
    klient2->setHaslo("abcd");
    system.dodajKlienta(klient2);

    auto pracownik = make_shared<PracownikObslugi>(
        100, "Anna", "Nowak", "PRAC-01", Date(1, 3, 2024), 6500.0f);
    pracownik->setLogin("anna");
    pracownik->setHaslo("admin");
    system.dodajPracownika(pracownik);

    system.dodajPojazd(make_shared<Samochod>(1, "Toyota", "Corolla", "PO1234A", 180.0, 500.0));
    system.dodajPojazd(make_shared<Samochod>(2, "Skoda", "Octavia", "PO5678B", 200.0, 600.0));
    system.dodajPojazd(make_shared<Motocykl>(3, "Yamaha", "MT-07", "PO9999C", 140.0, 400.0));
}

void uruchomMenuInteraktywne(SystemRezerwacji &system)
{
    shared_ptr<Osoba> zalogowanaOsoba = nullptr;
    int wybor = -1;

    while (wybor != 0)
    {
        auto zalogowanyPracownik = dynamic_pointer_cast<PracownikObslugi>(zalogowanaOsoba);

        cout << "\n================ MENU SYSTEMU REZERWACJI ================\n";
        if (zalogowanaOsoba)
        {
            cout << "Zalogowano jako: " << zalogowanaOsoba->getImie() << " "
                      << zalogowanaOsoba->getNazwisko() << " (ID: " << zalogowanaOsoba->getId() << ")\n";
        }
        else
        {
            cout << "Status: Niezalogowany (konta demo: jan/1234, marek/abcd, anna/admin)\n";
        }
        cout << "---------------------------------------------------------\n";
        if (!zalogowanaOsoba)
        {
            cout << "1. Zaloguj sie na konto\n";
        }
        cout << "2. Wyswietl dostepne pojazdy\n";
        cout << "3. Wyszukaj pojazd po marce\n";
        if (!zalogowanyPracownik)
        {
            cout << "4. Wypozycz pojazd i poznaj koszt\n";
            cout << "5. Oplac rezerwacje\n";
            cout << "6. Sprawdz historie rezerwacji klienta\n";
        }
        if (zalogowanyPracownik)
        {
            cout << "7. Dodaj pojazd do floty\n";
            cout << "8. Usun pojazd z floty\n";
            cout << "9. Przyjmij zwrot pojazdu i nalicz kare\n";
        }
        if (zalogowanaOsoba)
        {
            cout << "10. Wyloguj sie\n";
        }
        cout << "0. Wyjscie\n";

        wybor = wczytajInt("Wybierz opcje: ");

        switch (wybor)
        {
        case 1:
        {
            if (zalogowanaOsoba)
            {
                cout << "Nieznana opcja.\n";
                break;
            }
            string login;
            string haslo;
            cout << "Login: ";
            cin >> login;
            cout << "Haslo: ";
            cin >> haslo;
            auto osoba = system.zalogujUzytkownika(login, haslo);
            if (osoba)
            {
                zalogowanaOsoba = osoba;
            }
            break;
        }
        case 2:
            system.wyswietlDostepnePojazdy();
            break;
        case 3:
        {
            string marka;
            cout << "Podaj marke: ";
            cin >> marka;
            auto klient = dynamic_pointer_cast<Klient>(zalogowanaOsoba);
            if (!klient)
            {
                klient = system.znajdzKlienta(1);
            }
            if (klient)
            {
                klient->wyszukajPojazd(system.getFlota(), marka);
            }
            break;
        }
        case 4:
        {
            auto klient = dynamic_pointer_cast<Klient>(zalogowanaOsoba);
            if (!klient)
            {
                cout << "[System] Musisz byc zalogowany jako Klient, aby wypozyczyc pojazd.\n";
                break;
            }
            int idPojazdu = wczytajInt("Podaj ID pojazdu do wypozyczenia: ");
            Date dataStart = wczytajDate("Data rozpoczecia rezerwacji:");
            Date terminZwrotu = wczytajDate("Planowany termin zwrotu:");
            system.wypozycz(klient->getId(), idPojazdu, dataStart, terminZwrotu);
            break;
        }
        case 5:
        {
            int idRez = wczytajInt("Podaj ID rezerwacji do oplacenia: ");
            int metoda = wczytajInt("Wybierz metode platnosci (1-Karta, 2-BLIK, 3-Gotowka): ");
            SposobPlatnosci sposob = SposobPlatnosci::KARTA;
            if (metoda == 2)
            {
                sposob = SposobPlatnosci::BLIK;
            }
            else if (metoda == 3)
            {
                sposob = SposobPlatnosci::GOTOWKA;
            }
            string termin;
            cout << "Podaj date platnosci (np. 12.11.2026): ";
            cin >> termin;
            system.oplacRezerwacje(idRez, sposob, termin);
            break;
        }
        case 6:
        {
            auto klient = dynamic_pointer_cast<Klient>(zalogowanaOsoba);
            if (!klient)
            {
                cout << "[System] Musisz byc zalogowany jako Klient, aby sprawdzic historie.\n";
                break;
            }
            klient->sprawdzHistorieRezerwacji();
            break;
        }
        case 7:
        {
            if (!zalogowanyPracownik)
            {
                cout << "Nieznana opcja.\n";
                break;
            }
            int typ = wczytajInt("Typ pojazdu (1-Samochod, 2-Motocykl): ");
            int idPoj = wczytajInt("ID nowego pojazdu: ");
            string marka;
            string model;
            string nrRej;
            cout << "Marka: ";
            cin >> marka;
            cout << "Model: ";
            cin >> model;
            cout << "Nr rejestracyjny: ";
            cin >> nrRej;
            double cena = wczytajDouble("Cena za dzien (PLN): ");
            double kaucja = wczytajDouble("Kaucja (PLN): ");

            shared_ptr<Pojazd> nowyPojazd;
            if (typ == 2)
            {
                nowyPojazd = make_shared<Motocykl>(idPoj, marka, model, nrRej, cena, kaucja);
            }
            else
            {
                nowyPojazd = make_shared<Samochod>(idPoj, marka, model, nrRej, cena, kaucja);
            }
            system.pracownikDodajPojazd(zalogowanyPracownik->getId(), nowyPojazd);
            break;
        }
        case 8:
        {
            if (!zalogowanyPracownik)
            {
                cout << "Nieznana opcja.\n";
                break;
            }
            int idPoj = wczytajInt("Podaj ID pojazdu do usuniecia: ");
            system.pracownikUsunPojazd(zalogowanyPracownik->getId(), idPoj);
            break;
        }
        case 9:
        {
            if (!zalogowanyPracownik)
            {
                cout << "Nieznana opcja.\n";
                break;
            }
            int idRez = wczytajInt("Podaj ID rezerwacji do zwrotu: ");
            Date dataZwrotu = wczytajDate("Podaj faktyczna date zwrotu:");
            system.przyjmijZwrot(zalogowanyPracownik->getId(), idRez, dataZwrotu);
            break;
        }
        case 10:
            if (zalogowanaOsoba)
            {
                zalogowanaOsoba->wyloguj();
                cout << "[System] Wylogowano uzytkownika.\n";
                zalogowanaOsoba = nullptr;
            }
            else
            {
                cout << "[System] Nikt nie jest aktualnie zalogowany.\n";
            }
            break;
        case 0:
            break;
        default:
            cout << "Nieznana opcja.\n";
            break;
        }
    }
}
} // namespace

int main()
{
    SystemRezerwacji system;
    zainicjujDaneStartowe(system);
    uruchomMenuInteraktywne(system);

    return 0;
}
