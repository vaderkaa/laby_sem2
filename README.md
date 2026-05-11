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
Jeśli stworzyłeś `vector<int>`, to tutaj T staje się int.

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
* & (Referencja): To jest tu najważniejsze. Funkcja nie zwraca kopii tego, co jest w środku, ale oryginał. Gdyby nie było &, funkcja robiłaby kserokopię danych. Jeśli Twoim danym byłoby np. zdjęcie o rozmiarze 10MB, każde wywołanie `first()` zajmowałoby nową pamięć i czas procesora. Dzięki & dostajesz "bezpośredni wgląd" do zmiennej wewnątrz obiektu.

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
