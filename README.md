### Organizacja plików projektu (tak na wypadek)

Jeśli pliki `.cpp` i `.hpp` mają znajdować się w oddzielnych folderach:

* `src/` – tu trafiają pliki źródłowe `.cpp`.
* `include/` – tu lądują pliki nagłówkowe `.hpp`.

Wtedy w pliku `.cpp` dołączasz nagłówek w ten sposób:
```cpp
#include "../include/mini_vector.hpp"
```

### Unique_ptr

```cpp
template<typename T>
class vector {
  std::unique_ptr<T[]> data;
  void push_back(const T& val);
};
```

Kiedy tworzysz obiekt przez `new`, musisz pamiętać o `delete`. Jeśli zapomnisz – masz wyciek pamięci.
Unique_ptr robi to automatycznie. Gdy obiekt vector przestaje istnieć (kończy się jego zasięg), `std::unique_ptr` sam "sprząta" pamięć, której używał.
Słowo unique oznacza, że tylko jeden wskaźnik na raz może posiadać dany zasób.
Nawiasy kwadratowe informują kompilator, że ten wskaźnik nie zarządza jednym pojedynczym obiektem, ale całą tablicą obiektów.
Jeśli stworzyłeś `vector<int>`, to tutaj T staje się `int`.

### Szablony

```cpp
pair(T t, U u) : t(std::move(t)), u(std::move(u)) {}
```

* Bez `std::move`: Kompilator musiałby zrobić drugą kopię. To tak, jakbyś miał dokument w ręku, podszedł do kserokopiarki, zrobił kopię i włożył ją do segregatora, a oryginał wyrzucił do kosza sekundę później (bo funkcja się kończy). To strata czasu i papieru.
* Z `std::move`: Mówisz kompilatorowi: „Ej, te lokalne zmienne t i u i tak za chwilę znikną, bo kończy się konstruktor. Nie kopiuj ich. Po prostu zabierz im zawartość i daj moim polom w klasie”.

```cpp
template<typename T>
void swap(T& a, T& b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}
```

* T / U: To typy danych, które zdefiniowałeś w szablonie. Jeśli Twoja para to `pair<int, string>`, to `first()` zwróci `int`, a `second()` zwróci `string`.
* `&` (Referencja): To jest tu najważniejsze. Funkcja nie zwraca kopii tego, co jest w środku, ale oryginał. Gdyby nie było `&`, funkcja robiłaby kserokopię danych. Jeśli Twoim danym byłoby np. zdjęcie o rozmiarze 10MB, każde wywołanie `first()` zajmowałoby nową pamięć i czas procesora. Dzięki & dostajesz "bezpośredni wgląd" do zmiennej wewnątrz obiektu.

### Variant

```cpp
std::variant<int, float, bool> v;
v = 3;      // Teraz v trzyma inta
v = 2.0f;   // Teraz v trzyma float (stara wartość int zostaje nadpisana)
v = true;   // Teraz v trzyma bool
```

`std::variant` dynamicznie zmienia swój "stan". Gdy przypisujesz nową wartość innego typu, stara jest niszczona, a nowa zajmuje jej miejsce w pamięci.

```cpp
if (std::holds_alternative<bool>(v)) { ... }
```

To funkcja, która zwraca `true`, jeśli w wariancie aktualnie znajduje się typ podany w nawiasach ostrych. Zapobiega to błędom w trakcie działania programu.

```cpp
std::get<bool>(v) = false;
```

`std::get<T>` daje Ci dostęp do wartości. Możesz ją odczytać lub – tak jak w przykładzie – przypisać nową wartość do tego samego typu.
Uwaga: Jeśli użyjesz `std::get<int>`, a wariant aktualnie trzyma `bool`, program rzuci wyjątek (`std::bad_variant_access`).

* Domyślna konstrukcja: Jeśli napiszesz `std::variant<int, float> v` i nic nie przypiszesz, wariant automatycznie "stworzy" pierwszy typ z listy (czyli tutaj `int` o wartości 0).
* Metoda `.index()`: Każdy typ w wariancie ma swój numer (licząc od zera).
* W `std::variant<int, float, bool>`: `int` ma indeks 0, `float` ma 1, a `bool` ma 2.
* Wywołanie `v.index()` powie Ci, który "slot" jest aktualnie zajęty.

Oto notatka o **`std::optional`** przygotowana dokładnie w takim samym stylu, jak Twoja notatka o `variant`. Dzięki temu będziesz mieć spójne materiały do nauki.

### Optional

```cpp
std::optional<int> opt;           // Puste pudełko (domyślnie std::nullopt)
opt = 5;                          // Teraz pudełko zawiera int o wartości 5
opt = std::nullopt;               // Pudełko znów jest puste
```

`std::optional` to tzw. **typ sumacyjny**, ponieważ liczba jego stanów to liczba stanów danego typu + 1 (dodatkowy stan "nic", czyli `null`). Pozwala bezpiecznie przechowywać wartość lub informację o jej braku bez używania wskaźników.

```cpp
if (opt.has_value()) { ... }      // Zwraca true, jeśli w środku coś jest
if (opt) { ... }                  // Skrócony zapis sprawdzania (działa tak samo)
```

Metoda `has_value()` (lub samo użycie zmiennej w `if`) pozwala sprawdzić, czy pudełko jest pełne, zanim spróbujemy się do niego dobrać.

```cpp
int x = opt.value();              // Zwraca wartość lub rzuca wyjątek
int y = *opt;                     // Zwraca wartość bez sprawdzania (szybciej, ale mniej bezpiecznie)
int z = opt.value_or(0);          // Zwraca wartość, a jeśli pusto - zwraca 0
```

`std::optional` daje kilka sposobów na wyciągnięcie danych:

* `.value()`: Bezpieczne. Jeśli pudełko jest puste, program rzuci wyjątek `std::bad_optional_access`.
* `operator*`: Działa jak przy wskaźnikach. Jest szybki, ale jeśli pudełko jest puste, zachowanie programu jest nieprzewidywalne (tzw. Undefined Behavior).
* `.value_or(domyślna)`: Bardzo przydatne – pozwala ustalić "plan awaryjny", jeśli wartości nie ma.

```cpp
opt.reset();                      // Czyści optional, niszcząc obiekt w środku
```

Metoda `.reset()` sprawia, że wariant staje się pusty (`std::nullopt`). Jeśli w środku był obiekt, zostaje dla niego wywołany destruktor.

* Cykl życia: Kiedy wkładasz obiekt do `optional`, tworzona jest jego **kopia** wewnątrz pudełka. Oryginał i kopia to dwa osobne byty.
* Bezpieczeństwo: Używamy go zamiast "magicznych wartości" (np. zamiast zwracać `-1`, gdy nie znaleziono elementu, lepiej zwrócić `std::nullopt`).

### List

```cpp
std::list<int> l = {10, 20};
l.emplace_back(30);           // tworzy 30 na koncu bez kopiowania oryginału
auto it = l.begin();          // ustawia iterator na pierwszy element (10)
std::advance(it, 2);          // przesuwa iterator o 2 pozycje (teraz wskazuje na 30)
l.emplace(it, 25);            // wstawia 25 przed elementem, na który wskazuje it
it = l.erase(it);             // usuwa element (30) i zwraca iterator na następny (l.end())
```

Lista to ciąg węzłów rozrzuconych w pamięci, gdzie każdy zna adres swojego sąsiada. Ponieważ elementy nie leżą obok siebie, nie działa dostęp przez `l[i]`. Do konkretnego miejsca docieramy tylko przesuwając iterator krok po kroku.

Nawigacja i modyfikacja:

* `std::advance(it, n)` - przesuwa iterator o n kroków (skacze po węzłach).
* `std::next(it)` / `std::prev(it)` - zwracają iterator o krok dalej lub wcześniej bez modyfikowania it.
* `erase(it)` - zawsze zwraca iterator do elementu znajdującego się za tym usuniętym. Należy go przypisać (`it = l.erase(it)`), aby móc dalej bezpiecznie korzystać z pętli.
* `emplace_back` / `emplace` - są wydajniejsze od push, bo budują obiekt bezpośrednio w pamięci listy, zamiast tworzyć go wcześniej i kopiować.
* `end()` - to nie jest ostatni element, tylko punkt za końcem listy. Ostatni element to `--end()`.

```cpp
l.sort();                                  // l.sort() zamiast std::sort
l.unique();                                // usuwa sąsiadujące duplikaty (najpierw posortuj!)
l.remove(10);                              // usuwa wszystkie dziesiątki z całej listy
l.remove_if([](int x){ return x > 100; }); // usuwa elementy spełniające warunek
```

* Sortowanie: To najczęstszy błąd. Nie możesz użyć standardowego algorytmu `std::sort(l.begin(), l.end()`), ponieważ on wymaga dostępu swobodnego (takiego jak w wektorze). Lista ma swoją własną, wbudowaną metodę `l.sort()`, która jest zoptymalizowana pod kątem węzłów.
* Splice (magia listy): `l.splice(it, inna_lista)` pozwala błyskawicznie przenieść elementy z jednej listy do drugiej. Nie kopiuje danych, tylko "przepina" wskaźniki węzłów. To operacja, której nie da się zrobić tak wydajnie na wektorze.
* Stabilność iteratorów: W liście, dopóki nie usuniesz konkretnego elementu, na który wskazuje Twój iterator, pozostaje on ważny. Dodawanie miliona innych elementów dookoła nic nie zmienia. W wektorze dodanie jednego elementu może "przesunąć" całą pamięć i zepsuć wszystkie iteratory.
* Kiedy nie używać: Jeśli Twój algorytm polega głównie na skakaniu do losowych indeksów (np. co trzeci element), lista będzie tragicznie wolna przez brak `l[i]`. Wtedy lepszy będzie wektor.
