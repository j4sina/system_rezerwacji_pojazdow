#include "../include/SystemRezerwacji.h"
#include <iostream>

SystemRezerwacji::SystemRezerwacji()
    : nastepne_id_rezerwacji_(1),
      nastepne_id_platnosci_(1)
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

std::shared_ptr<Osoba> SystemRezerwacji::zalogujUzytkownika(const std::string &login, const std::string &haslo)
{
    for (const auto &klient : klienci_)
    {
        if (klient->zaloguj(login, haslo))
        {
            std::cout << "[System] Zalogowano klienta: " << klient->getImie()
                      << " " << klient->getNazwisko() << " (ID: " << klient->getId() << ").\n";
            return klient;
        }
    }

    for (const auto &pracownik : pracownicy_)
    {
        if (pracownik->zaloguj(login, haslo))
        {
            std::cout << "[System] Zalogowano pracownika: " << pracownik->getImie()
                      << " " << pracownik->getNazwisko() << " (ID: " << pracownik->getId() << ").\n";
            return pracownik;
        }
    }

    std::cout << "[System] Blad logowania: Niepoprawny login lub haslo.\n";
    return nullptr;
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

    if (!klient->czyZalogowany())
    {
        std::cout << "[System] Blad: Klient musi byc zalogowany, aby dokonac rezerwacji.\n";
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
    {
        iloscDni = 1;
    }

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

bool SystemRezerwacji::oplacRezerwacje(int idRezerwacji, SposobPlatnosci sposob, const std::string &terminPlatnosci)
{
    for (auto &rez : rezerwacje_)
    {
        if (rez.getIdRezerwacji() == idRezerwacji)
        {
            double kwota = static_cast<double>(rez.obliczKoszt()) + static_cast<double>(rez.getKara());
            Platnosc platnosc(nastepne_id_platnosci_++, sposob, terminPlatnosci, kwota);
            platnosc.zarejestrujPlatnosc();
            rez.setPlatnosc(platnosc);

            for (const auto &k : klienci_)
            {
                k->zaktualizujRezerwacje(rez);
            }
            return true;
        }
    }

    std::cout << "[System] Blad: Nie znaleziono rezerwacji o ID: " << idRezerwacji << ".\n";
    return false;
}

bool SystemRezerwacji::pracownikDodajPojazd(int idPracownika, std::shared_ptr<Pojazd> nowyPojazd)
{
    auto pracownik = znajdzPracownika(idPracownika);
    if (!pracownik)
    {
        std::cout << "[System] Blad: Nie znaleziono pracownika o ID " << idPracownika << ".\n";
        return false;
    }

    if (!pracownik->czyZalogowany())
    {
        std::cout << "[System] Blad: Pracownik musi byc zalogowany, aby dodac pojazd.\n";
        return false;
    }

    if (!pracownik->sprawdzaUprawnienia())
    {
        std::cout << "[System] Blad: Brak uprawnien pracownika do zarzadzania flota.\n";
        return false;
    }

    if (!nowyPojazd)
    {
        std::cout << "[System] Blad: Przekazano pusty obiekt pojazdu.\n";
        return false;
    }

    if (znajdzPojazd(nowyPojazd->getIdPojazdu()) != nullptr)
    {
        std::cout << "[System] Blad: Pojazd o ID " << nowyPojazd->getIdPojazdu() << " juz istnieje we flocie.\n";
        return false;
    }

    pracownik->dodajPojazd(flota_, nowyPojazd);
    return true;
}

bool SystemRezerwacji::pracownikUsunPojazd(int idPracownika, int idPojazdu)
{
    auto pracownik = znajdzPracownika(idPracownika);
    if (!pracownik)
    {
        std::cout << "[System] Blad: Nie znaleziono pracownika o ID " << idPracownika << ".\n";
        return false;
    }

    if (!pracownik->czyZalogowany())
    {
        std::cout << "[System] Blad: Pracownik musi byc zalogowany, aby usunac pojazd.\n";
        return false;
    }

    if (!pracownik->sprawdzaUprawnienia())
    {
        std::cout << "[System] Blad: Brak uprawnien pracownika do zarzadzania flota.\n";
        return false;
    }

    if (znajdzPojazd(idPojazdu) == nullptr)
    {
        std::cout << "[System] Blad: Nie znaleziono we flocie pojazdu o ID " << idPojazdu << ".\n";
        return false;
    }

    pracownik->usunPojazd(flota_, idPojazdu);
    return true;
}

std::vector<std::shared_ptr<Pojazd>> SystemRezerwacji::wyszukajDostepnePojazdy() const
{
    std::vector<std::shared_ptr<Pojazd>> dostepne;
    for (const auto &p : flota_)
    {
        if (p->getDostepnosc())
        {
            dostepne.push_back(p);
        }
    }
    return dostepne;
}

void SystemRezerwacji::wyswietlDostepnePojazdy() const
{
    auto dostepne = wyszukajDostepnePojazdy();
    std::cout << "\n--- Dostepne pojazdy we flocie ---\n";
    if (dostepne.empty())
    {
        std::cout << "Brak dostepnych pojazdow.\n";
        return;
    }

    for (const auto &p : dostepne)
    {
        std::cout << "- ID: " << p->getIdPojazdu()
                  << " | " << p->getMarka() << " " << p->getModel()
                  << " | Nr rej.: " << p->getNrRejestracyjny()
                  << " | Cena/dzien: " << p->getCenaZaDzien() << " PLN"
                  << " | Kaucja: " << p->getKaucja() << " PLN\n";
    }
}

bool SystemRezerwacji::przyjmijZwrot(int idRezerwacji, const Date &faktycznaDataZwrotu)
{
    for (auto &rez : rezerwacje_)
    {
        if (rez.getIdRezerwacji() == idRezerwacji)
        {
            if (rez.isZwrocono())
            {
                std::cout << "[System] Rezerwacja ID: " << idRezerwacji << " zostala juz zwrocona.\n";
                return false;
            }

            float kara = rez.naliczKare(faktycznaDataZwrotu);

            for (const auto &poz : rez.getPozycje())
            {
                if (poz.getPojazd())
                {
                    poz.getPojazd()->setDostepnosc(true);
                }
            }

            for (const auto &k : klienci_)
            {
                k->zaktualizujRezerwacje(rez);
            }

            std::cout << "[System] Przyjeto zwrot dla rezerwacji ID: " << idRezerwacji
                      << " | Naliczona kara: " << kara << " PLN\n";
            return true;
        }
    }

    std::cout << "[System] Blad: Nie znaleziono rezerwacji o ID: " << idRezerwacji << ".\n";
    return false;
}

bool SystemRezerwacji::przyjmijZwrot(int idPracownika, int idRezerwacji, const Date &faktycznaDataZwrotu)
{
    auto pracownik = znajdzPracownika(idPracownika);
    if (!pracownik)
    {
        std::cout << "[System] Blad: Nie znaleziono pracownika o ID " << idPracownika << ".\n";
        return false;
    }

    if (!pracownik->czyZalogowany())
    {
        std::cout << "[System] Blad: Pracownik musi byc zalogowany, aby przyjac zwrot.\n";
        return false;
    }

    if (!pracownik->sprawdzaUprawnienia())
    {
        std::cout << "[System] Blad: Brak uprawnien pracownika.\n";
        return false;
    }

    return przyjmijZwrot(idRezerwacji, faktycznaDataZwrotu);
}

const std::vector<std::shared_ptr<Pojazd>> &SystemRezerwacji::getFlota() const
{
    return flota_;
}

const std::vector<Rezerwacja> &SystemRezerwacji::getRezerwacje() const
{
    return rezerwacje_;
}

int SystemRezerwacji::getOstatnieIdRezerwacji() const
{
    return nastepne_id_rezerwacji_ - 1;
}
