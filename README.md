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

### Use Case 1 (Wypożycz pojazd / Złóż rezerwację)
**Aktorzy:** Klient  
**Opis:** Klient tworzy rezerwację wybranego pojazdu na dany termin. Wymaga zalogowania się na konto oraz obliczenia kwoty wynajmu.  
**Powiązanie z user stories:** 1

### Use Case 2 (Dodaj pojazd)
**Aktorzy:** Pracownik Obsługi  
**Opis:** Pracownik wprowadza do systemu nowy pojazd, podając jego markę, model, numer rejestracyjny, cenę dobową i kaucję.  
**Powiązanie z user stories:** 2

### Use Case 3 (Usuń pojazd)
**Aktorzy:** Pracownik Obsługi  
**Opis:** Pracownik usuwa wycofany lub uszkodzony pojazd na podstawie jego identyfikatora, co usuwa go z oferty.  
**Powiązanie z user stories:** 3

### Use Case 4 (Wyszukaj pojazd)
**Aktorzy:** Osoba (Klient, Pracownik Obsługi)  
**Opis:** Użytkownik przegląda ofertę floty i filtruje pojazdy w celu znalezienia wolnych egzemplarzy.  
**Powiązanie z user stories:** 4

### Use Case 5 (Poznaj kwotę rezerwacji)
**Aktorzy:** Klient  
**Opis:** Klient wybiera pojazd oraz czas trwania wynajmu, a system wylicza całkowity koszt rezerwacji z uwzględnieniem kaucji.  
**Powiązanie z user stories:** 5

### Use Case 6 (Przyjmij zwrot i nalicz karę)
**Aktorzy:** Pracownik Obsługi  
**Opis:** Pracownik rejestruje fizyczny zwrot pojazdu. W przypadku przekroczenia terminu zwrotu, system automatycznie rozszerza proces o naliczenie kary umownej.  
**Powiązanie z user stories:** 6

### Use Case 7 (Zaloguj się na konto)
**Aktorzy:** Osoba (Klient, Pracownik Obsługi)  
**Opis:** Użytkownik podaje login i hasło w celu autoryzacji dostępu do chronionych operacji w systemie.  
**Powiązanie z user stories:** -

### Use Case 8 (Sprawdź historię rezerwacji)
**Aktorzy:** Klient  
**Opis:** Klient sprawdza listę swoich bieżących oraz archiwalnych rezerwacji po zalogowaniu na konto.  
**Powiązanie z user stories:** -
