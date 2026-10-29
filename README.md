# System Rezerwacji Pojazdów

## User Stories

### User Story 1 (Tworzenie / transakcja)
**Jako** Klient  
**chcę** wypożyczyć wybrany samochód na określony termin,  
**aby** móc z niego korzystać w wybranym przedziale czasu.  
**Kryterium akceptacji:** System tworzy nowy obiekt Rezerwacja z podpiętą PozycjąRezerwacji, przypisuje rezerwację do klienta i oznacza pojazd jako niedostępny.

### User Story 2 (Zarządcza / administracyjna)
**Jako** Pracownik Obsługi  
**chcę** dodać nowy samochód do oferty wypożyczalni,  
**aby** poszerzyć flotę dostępną dla klientów.  
**Kryterium akceptacji:** Po weryfikacji uprawnień pracownika do systemu zostaje dodany nowy obiekt Pojazd z uzupełnioną ceną za dzień, kaucją i numerem rejestracyjnym.

### User Story 3 (Zarządcza / administracyjna)
**Jako** Pracownik Obsługi  
**chcę** usunąć uszkodzony lub wycofany samochód z floty,  
**aby** klienci nie mogli go zarezerwować.  
**Kryterium akceptacji:** Po sprawdzeniu uprawnień pracownika pojazd o podanym ID zostaje trwale wykreślony z listy pojazdów w systemie.

### User Story 4 (Wyszukiwanie / przeglądanie)
**Jako** Klient  
**chcę** sprawdzić listę dostępnych samochodów,  
**aby** wybrać auto gotowe do wynajęcia.  
**Kryterium akceptacji:** System weryfikuje pole dostepnosc w obiektach Pojazd i zwraca klientowi tylko te samochody, które są aktualnie wolne.

### User Story 5 (Logika biznesowa)
**Jako** Klient  
**chcę** poznać łączną kwotę do zapłaty za okres rezerwacji,  
**aby** opłacić wynajem wybraną metodą płatności.  
**Kryterium akceptacji:** System oblicza cenę mnożąc liczbę dni z rezerwacji przez cenę za dzień z przypisanego pojazdu oraz dolicza kaucję.

### User Story 6 (Logika biznesowa)
**Jako** Pracownik Obsługi  
**chcę**, aby system naliczył karę w przypadku opóźnionego zwrotu auta,  
**aby** rozliczyć klienta za przekroczenie ustalonego terminu.  
**Kryterium akceptacji:** Jeśli faktyczna data zwrotu wprowadzona przez pracownika jest późniejsza niż ustalony termin, system wylicza opłatę karną i aktualizuje pole kara w rezerwacji.

## Use Cases
### Use Case 1 (Wyszukaj pojazd)
**Aktorzy:** Klient, Pracownik Obsługi
**Opis:** Klient przeszukuje katalog systemu, podając model i markę, aby sprawdzić jego dostępność.
**Powiązanie z user stories:** 4

### Use Case 2 (Sprawdź historię rezerwacji)
**Aktorzy:** Klient
**Opis:** Klient podaje swoje dane, aby sprawdzić swoje poprzednie lub bieżące rezerwacje.
**Powiązanie z user stories:** 1

### Use Case 3 (Dodaj pojazd)
**Aktorzy:** Pracownik Obsługi
**Opis:** Pracownik wprowadza do systemu nowy pojazd, podając jego markę, model i numer rejestracyjny, co poszerza listę pojazdów.
**Powiązanie z user stories:** 2

### Use Case 4 (Usuń pojazd)
**Aktorzy:** Pracownik Obsługi
**Opis:** Pracownik usuwa pojazd wprowadzając jego numer rejestracyjny, co zmniejsza listę pojazdów
**Powiązanie z user stories:** 3

### Use Case 5 (Poznaj kwotę rezerwacji)
**Aktorzy:** Klient
**Opis:** Klient wybiera pojazd oraz dostępną datę rezerwacji, a system oblicza kwotę do zapłaty.
**Powiązanie z user stories:** 5

### Use Case 6 (Nalicz karę za opóźniony zwrot pojazdu)
**Aktorzy:** Pracownik Obsługi
**Opis:** Pracownik wprowadza do systemu faktyczną datę zwrotu pojazdu. Jeśli data ta przekracza ustalony termin, system automatycznie wylicza opłatę karną za opóźnienie i aktualizuje to pole w rezerwacji w celu rozliczenia klienta.
**Powiązanie z user stories:** 6